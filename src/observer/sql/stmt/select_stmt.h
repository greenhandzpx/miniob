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
// Created by Wangyunlai on 2022/6/5.
//

#pragma once

#include <vector>

#include "rc.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include "storage/common/field.h"

class FieldMeta;
class FilterStmt;
class Db;
class Table;

class SelectStmt : public Stmt
{
public:

  SelectStmt() = default;
  ~SelectStmt() override;

  StmtType type() const override { return StmtType::SELECT; }
public:
  // static RC create(Db *db, const Selects &select_sql, Stmt *&stmt);
  static RC create(Db *db, Selects &select_sql, Stmt *&stmt, std::vector<std::pair<std::string, Table*>> *parent_tables);

public:
  const std::vector<Table *> &tables() const { return tables_; }
  const std::vector<Field> &query_fields() const { return query_fields_; }
  const std::vector<Field> &aggr_fields() const { return aggr_fields_; }
  const std::vector<Field> &group_fields() const { return group_fields_; }
  const std::vector<Field> &having_fields() const { return having_fields_; }
  FilterStmt *filter_stmt() const { return filter_stmt_; }
  const std::vector<AggregationOp> &aggregation_ops() const { return aggregation_ops_; }
  const std::vector<char *> &aggregation_alias() const { return aggregation_alias_; }
  const std::vector<AggregationOp> &having_ops() const { return having_ops_; }
  const std::vector<std::pair<Field, bool>> &order_fields() const { return order_fields_; }
  const std::vector<size_t> &arggrops_idx_in_fields() const { return aggrops_idx_in_fields_; }
  const bool order() const { return order_; }
  const bool group() const { return group_; }
  const bool having() const { return having_; }
  const std::vector<Having_Filter> having_filters() const { return having_filters_; }

private:
  std::vector<Field> query_fields_;
  std::vector<Table *> tables_;
  FilterStmt *filter_stmt_ = nullptr;
  std::vector<Field> aggr_fields_;
  std::vector<AggregationOp> aggregation_ops_;
  std::vector<char *> aggregation_alias_;
  std::vector<size_t> aggrops_idx_in_fields_;
  std::vector<std::pair<Field, bool>> order_fields_;
  std::vector<Field> group_fields_;
  std::vector<having_filter> having_filters_;
  std::vector<Field> having_fields_;
  std::vector<AggregationOp> having_ops_;
  bool order_;
  bool group_;
  bool having_;

//*******************************************func****************************************************
  public:
  FunctionOp function_ops_[MAX_NUM];
  Value function_value1_[MAX_NUM];
  Value function_value2_[MAX_NUM];
  size_t attr_num_;
  int isfunc_;
  int isvaluefunc_;
  //*******************************************func****************************************************
};

