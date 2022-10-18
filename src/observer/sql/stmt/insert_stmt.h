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
#include "sql/stmt/stmt.h"
#include <vector>

class Table;
class Db;

class InsertStmt : public Stmt
{
public:

  InsertStmt() = default;
  // InsertStmt(Table *table, const Value *values, int value_amount);
  InsertStmt(Table *table, std::vector<const Value *> &tuples, const size_t *value_num, size_t tuple_num);

  StmtType type() const override {
    return StmtType::INSERT;
  }
public:
  static RC create(Db *db, const Inserts &insert_sql, Stmt *&stmt);

public:
  Table *table() const {return table_;}
  // const Value *values() const { return values_; }
  // int value_amount() const { return value_amount_; }
  std::vector<const Value*> tuples() const { return tuples_; }
  size_t tuple_amount() const { return tuple_num_; }
  const size_t *value_amount() const { return value_num_; }

private:
  Table *table_ = nullptr;
  // const Value *values_ = nullptr;
  // int value_amount_ = 0;
  std::vector<const Value *> tuples_;
  size_t tuple_num_ = 0;
  const size_t *value_num_ = nullptr;
};

