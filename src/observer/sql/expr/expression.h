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
// Created by Wangyunlai on 2022/07/05.
//

#pragma once

#include <string.h>
#include "sql/stmt/select_stmt.h"
#include "storage/common/field.h"
#include "sql/expr/tuple_cell.h"

class Tuple;

enum class ExprType {
  NONE,
  FIELD,
  VALUE,
  SUB_QUERY,
  VALUE_SET,
};

class Expression
{
public: 
  Expression() = default;
  virtual ~Expression() = default;
  
  virtual RC get_value(const Tuple &tuple, TupleCell &cell) const = 0;
  virtual ExprType type() const = 0;
};

class FieldExpr : public Expression
{
public:
  FieldExpr() = default;
  FieldExpr(const Table *table, const FieldMeta *field) : field_(table, field)
  {}

  virtual ~FieldExpr() = default;

  ExprType type() const override
  {
    return ExprType::FIELD;
  }

  Field &field()
  {
    return field_;
  }

  const Field &field() const
  {
    return field_;
  }

  const char *table_name() const
  {
    return field_.table_name();
  }

  const char *field_name() const
  {
    return field_.field_name();
  }

  RC get_value(const Tuple &tuple, TupleCell &cell) const override;
  
private:
  Field field_;
};

class ValueExpr : public Expression
{
public:
  ValueExpr() = default;
  ValueExpr(const Value &value) : tuple_cell_(value.type, (char *)value.data)
  {
    if (value.type == CHARS) {
      tuple_cell_.set_length(strlen((const char *)value.data));
    }
  }

  virtual ~ValueExpr() = default;

  RC get_value(const Tuple &tuple, TupleCell & cell) const override;
  ExprType type() const override
  {
    return ExprType::VALUE;
  }

  void get_tuple_cell(TupleCell &cell) const {
    cell = tuple_cell_;
  }

// private:
  TupleCell tuple_cell_;
};

class SubQueryExpr: public Expression
{
public:
  SubQueryExpr(SelectStmt *select_stmt): select_stmt_(select_stmt) {}
  ExprType type() const override
  {
    return ExprType::SUB_QUERY;
  }

  RC get_value(const Tuple &tuple, TupleCell & cell) const override;

  RC check_contain_or_exist(Tuple *parent_tuple, bool check_contain, TupleCell *left_cell, bool &res);
  RC check_not_contain_or_exist(Tuple *parent_tuple, bool check_contain, TupleCell *left_cell, bool &res);

  // void add_parent_tuple(Tuple *parent_tuple);
private:
  SelectStmt *select_stmt_ = nullptr;
  // Tuple *parent_tuple_ = nullptr;
};

class ValueSetExpr: public Expression
{
public:
  ValueSetExpr(const std::vector<Value> &value_set): value_set_(value_set) {}

  ExprType type() const override
  {
    return ExprType::VALUE_SET;
  }

  RC get_value(const Tuple &tuple, TupleCell & cell) const override {
    return RC::UNIMPLENMENT;
  }

  const std::vector<Value> &get_value_set() const {
    return value_set_;
  }

  bool check_contain(TupleCell &other_tuple_cell) const;
  bool check_not_contain(TupleCell &other_tuple_cell) const;
  bool check_contain(Value &other_value) const;
private:
  std::vector<Value> value_set_;
};