/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2021/5/14.
//

#pragma once

#include <memory>
#include <vector>

#include "common/log/log.h"
#include "sql/parser/parse.h"
#include "sql/expr/tuple_cell.h"
#include "sql/expr/expression.h"
#include "storage/record/record.h"

class Table;

class TupleCellSpec {
public:
  TupleCellSpec() = default;
  TupleCellSpec(Expression *expr) : expression_(expr)
  {}

  ~TupleCellSpec()
  {
    if (expression_) {
      delete expression_;
      expression_ = nullptr;
    }
  }

  void set_alias(const char *alias)
  {
    this->alias_ = alias;
  }
  const char *alias() const
  {
    return alias_;
  }

  Expression *expression() const
  {
    return expression_;
  }
  Expression *expression_ = nullptr;

private:
  const char *alias_ = nullptr;
};

class Tuple {
public:
  Tuple() = default;
  virtual ~Tuple() = default;

  virtual int cell_num() const = 0;
  virtual RC cell_at(int index, TupleCell &cell) const = 0;
  virtual RC find_cell(const Field &field, TupleCell &cell) const = 0;

  virtual RC cell_spec_at(int index, const TupleCellSpec *&spec) const = 0;
};

class RowTuple : public Tuple {
public:
  RowTuple() = default;
  virtual ~RowTuple()
  {
    for (TupleCellSpec *spec : speces_) {
      delete spec;
    }
    speces_.clear();
  }

  void set_record(Record *record)
  {
    this->record_ = record;
  }

  void set_schema(const Table *table, const std::vector<FieldMeta> *fields)
  {
    table_ = table;
    this->speces_.reserve(fields->size());
    for (const FieldMeta &field : *fields) {
      speces_.push_back(new TupleCellSpec(new FieldExpr(table, &field)));
    }
  }

  int cell_num() const override
  {
    return speces_.size();
  }

  RC cell_at(int index, TupleCell &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }
    const TupleCellSpec *spec = speces_[index];
    FieldExpr *field_expr = (FieldExpr *)spec->expression();
    const FieldMeta *field_meta = field_expr->field().meta();
    int null_map = *(int *)(record_->data() + NULLMAP_OFFSET);
    // 暂时直接减2（sys_fields的大小)
    if ((null_map & (1 << index - 2)) && field_meta->nullable()) {
      cell.set_type(AttrType::NULLS);
    } else {
      cell.set_type(field_meta->type());
    }
    cell.set_data(this->record_->data() + field_meta->offset());
    cell.set_length(field_meta->len());
    return RC::SUCCESS;
  }

  RC find_cell(const Field &field, TupleCell &cell) const override
  {
    const char *table_name = field.table_name();
    if (0 != strcmp(table_name, table_->name())) {
      return RC::NOTFOUND;
    }

    const char *field_name = field.field_name();
    for (size_t i = 0; i < speces_.size(); ++i) {
      const FieldExpr *field_expr = (const FieldExpr *)speces_[i]->expression();
      const Field &field = field_expr->field();
      if (0 == strcmp(field_name, field.field_name())) {
        return cell_at(i, cell);
      }
    }
    return RC::NOTFOUND;
  }

  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }
    spec = speces_[index];
    return RC::SUCCESS;
  }

  Record &record()
  {
    return *record_;
  }

  const Record &record() const
  {
    return *record_;
  }

private:
  Record *record_ = nullptr;
  const Table *table_ = nullptr;
  std::vector<TupleCellSpec *> speces_;
};
/**
  merge multiple tuples to one tuple
*/
class CompositeTuple : public Tuple {
public:
  CompositeTuple(const std::vector<Tuple *> &tuples) : tuples_(tuples)
  {
    for (int i = 0; i < tuples_.size(); ++i) {
      cell_num_ += tuples_[i]->cell_num();
    }
  }

  int cell_num() const override
  {
    return cell_num_;
  }

  RC cell_at(int index, TupleCell &cell) const override
  {
    for (Tuple *tuple : tuples_) {
      if (tuple->cell_at(index, cell) == RC::SUCCESS) {
        return RC::SUCCESS;
      }
      index -= tuple->cell_num();
    }
    return RC::INVALID_ARGUMENT;
  }

  RC find_cell(const Field &field, TupleCell &cell) const override
  {
    for (Tuple *tuple : tuples_) {
      if (tuple->find_cell(field, cell) == RC::SUCCESS) {
        return RC::SUCCESS;
      }
    }
    return RC::NOTFOUND;
  }

  RC find_cell(const Field &field, TupleCell &cell, int &index) const
  {
    for (int i = 0; i < tuples_.size(); ++i) {
      Tuple *tuple = tuples_[i];
      if (tuple->find_cell(field, cell) == RC::SUCCESS) {
        index = i;
        return RC::SUCCESS;
      }
    }
    return RC::NOTFOUND;
  }

  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    for (Tuple *tuple : tuples_) {
      if (tuple->cell_spec_at(index, spec) == RC::SUCCESS) {
        return RC::SUCCESS;
      }
      index -= tuple->cell_num();
    }
    return RC::INVALID_ARGUMENT;
  }

  void push_back(Tuple *tuple)
  {
    tuples_.push_back(tuple);
  }

  void set_tuple_by_index(int index, Tuple *tuple)
  {
    if (index < 0 || index >= tuples_.size()) {
      return;
    }
    tuples_[index] = tuple;
  }

  void pop_back()
  {
    if (tuples_.empty()) {
      return;
    }
    tuples_.pop_back();
  }

  size_t size()
  {
    return tuples_.size();
  }

private:
  int cell_num_ = 0;
  std::vector<Tuple *> tuples_;
};

class ProjectTuple : public Tuple {
public:
  ProjectTuple() = default;
  virtual ~ProjectTuple()
  {
    printf("desctruct a project tuple\n");
    for (TupleCellSpec *spec : speces_) {
      delete spec;
    }
    speces_.clear();
  }

  void set_tuple(Tuple *tuple)
  {
    this->tuple_ = tuple;
  }

  void add_cell_spec(TupleCellSpec *spec)
  {
    speces_.push_back(spec);
  }
  int cell_num() const override
  {
    return speces_.size();
  }

  RC cell_at(int index, TupleCell &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      return RC::GENERIC_ERROR;
    }
    if (tuple_ == nullptr) {
      return RC::GENERIC_ERROR;
    }

    const TupleCellSpec *spec = speces_[index];
    return spec->expression()->get_value(*tuple_, cell);
  }

  RC find_cell(const Field &field, TupleCell &cell) const override
  {
    return tuple_->find_cell(field, cell);
  }
  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      return RC::NOTFOUND;
    }
    spec = speces_[index];
    return RC::SUCCESS;
  }

  //**********************************************func************************************************

  RC modify_cell_spec_at(int index, Value *value, std::vector<std::pair<int, TupleCellSpec *>>& modify, TupleCellSpec *oold)
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      return RC::NOTFOUND;
    }

    TupleCellSpec *old = new TupleCellSpec;
    *old = *speces_[index];
    *oold = *old;
    speces_[index] = new TupleCellSpec;
    speces_[index]->expression_ = new ValueExpr;
    

    auto spec = speces_[index];
    ValueExpr *v_expr = dynamic_cast<ValueExpr *>(spec->expression_);

    if (value->type == INTS || value->type == DATES) {
      v_expr->tuple_cell_.length_ = sizeof(int);
    } else if (value->type == FLOATS) {
      v_expr->tuple_cell_.length_ = sizeof(float);
    } else if (value->type == CHARS) {
      v_expr->tuple_cell_.length_ = strlen((char*)value->data);
    } else {
      return RC::NOTFOUND;
    }

    v_expr->tuple_cell_.attr_type_ = value->type;
    v_expr->tuple_cell_.data_ = (char*)value->data;
    
    modify.push_back({index, old});
    return RC::SUCCESS;
  }

  //**********************************************func************************************************
// private:
  std::vector<TupleCellSpec *> speces_;
  Tuple *tuple_ = nullptr;
};
