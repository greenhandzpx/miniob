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
// Created by Wangyunlai on 2022/5/22.
//

#pragma once

#include "rc.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/stmt.h"

class Table;

class UpdateStmt : public Stmt
{
public:

  UpdateStmt() = default;
  // UpdateStmt(Table *table, Value *values, int value_amount);
  // UpdateStmt(Table *table, const Value *values, int value_amount, FilterStmt *filter_stmt, const char *attribute_name);


  // *************************************************upselect*********************************************************
  UpdateStmt(Table *table, Value *values, int value_amount, FilterStmt *filter_stmt, char **attribute_name, const size_t values_num);
  // *************************************************upselect*********************************************************

public:
  static RC create(Db *db, const Updates &update_sql, Stmt *&stmt);

public:
  Table *table() const {return table_;}
  const Value *values() const { return values_; }
  int value_amount() const { return value_amount_; }
  StmtType type() const override { return StmtType::UPDATE; }
  FilterStmt *filter_stmt() const { return filter_stmt_; }
  // const char *attribute_name() const { return attribute_name_; }

  // *************************************************upselect*********************************************************
  const char *attribute_name(int i) const { return attribute_name_[i]; }
  size_t values_num() { return values_num_; }
  // *************************************************upselect*********************************************************


private:
  Table *table_ = nullptr;
  const Value *values_ = nullptr;
  int value_amount_ = 0;
  FilterStmt *filter_stmt_ = nullptr;
  // const char *attribute_name_;

  // *************************************************upselect*********************************************************
  char **attribute_name_;
  size_t values_num_;
  // *************************************************upselect*********************************************************
};





