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
// Created by WangYunlai on 2022/6/27.
//

#pragma once

#include "sql/expr/tuple.h"
#include "sql/operator/operator.h"
#include <string>
#include <unordered_map>

class FilterStmt;

/**
 * PredicateOperator 用于单个表中的记录过滤
 * 如果是多个表数据过滤，比如join条件的过滤，需要设计新的predicate或者扩展:w
 */
class PredicateOperator : public Operator
{
public:
  PredicateOperator(FilterStmt *filter_stmt)
    : filter_stmt_(filter_stmt)
  {}

  virtual ~PredicateOperator() = default;

  RC set_parent_tuple(Tuple *parent_tuple) {
    parent_tuple_ = parent_tuple;
    return RC::SUCCESS;
  }

  RC open() override;
  RC next() override;
  RC close() override;

  RC next_when_multi_tables();

  Tuple * current_tuple() override;
  //int tuple_cell_num() const override;
  //RC tuple_cell_spec_at(int index, TupleCellSpec &spec) const override;
private:
  RC do_predicate(CompositeTuple &tuple, bool &res);
private:
  FilterStmt *filter_stmt_ = nullptr;
  std::vector<Tuple *> tuple_stack_;
  int stk_top_ = 0;
  CompositeTuple *current_tuple_ = nullptr;
  // simple sub query
  Tuple *parent_tuple_ = nullptr;
  bool is_over_ = false;
  bool has_accelerated_ = false;
  // // table name -> index in the tuple stack(i.e. chilren -> index in the tuple stack)
  // std::unordered_map<std::string, int> table_to_idx_;
};
