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

#include "common/log/log.h"
#include "sql/operator/predicate_operator.h"
#include "storage/record/record.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/common/field.h"

RC PredicateOperator::open()
{
  // if (children_.size() != 1) {
  //   LOG_WARN("predicate operator must has one child");
  //   return RC::INTERNAL;
  // }
  RC rc = RC::SUCCESS;
  for (auto child: children_) {
    if (RC::SUCCESS != (rc = child->open())) {
      return rc;
    }
  }

  return RC::SUCCESS;
}

RC PredicateOperator::next()
{
  RC rc = RC::SUCCESS;

  if (children_.size() == 1) {
    Operator *oper = children_[0];

    while (RC::SUCCESS == (rc = oper->next())) {
      Tuple *tuple = oper->current_tuple();
      if (nullptr == tuple) {
        rc = RC::INTERNAL;
        LOG_WARN("failed to get tuple from operator");
        break;
      }

      if (do_predicate(static_cast<RowTuple &>(*tuple))) {
        return rc;
      }
    }
    return rc;
  }

  while (RC::SUCCESS == (rc = next_when_multi_tables())) {
    if (current_tuple_ != nullptr) {
      // free last current tuple
      delete current_tuple_;
    }
    printf("get a new composite tuple\n");
    current_tuple_ = new CompositeTuple(tuple_stack_);
    // Tuple *tuple = current_tuple();
    if (nullptr == current_tuple_) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get tuple from operator");
      break;
    }

    if (do_predicate(static_cast<CompositeTuple &>(*current_tuple_))) {
      return rc;
    }
  }
  return rc;
}

RC PredicateOperator::next_when_multi_tables() {
  RC rc = RC::SUCCESS;

  if (tuple_stack_.size() != children_.size()) {
    // this must be the first time to call 
    if (tuple_stack_.size() != 0) {
      LOG_WARN("something error happens");
      return RC::INTERNAL;
    }
    for (auto child: children_) {
      if (child->next() != RC::SUCCESS) {
        LOG_WARN("shouldn't be empty table in predicate chilren");
        return RC::INTERNAL;
      }
      tuple_stack_.push_back(child->current_tuple());
    }
    return rc;
  }

  int n = children_.size();
  int i = n - 1;
  tuple_stack_.pop_back();
  while (i >= 0 && (rc = children_[i]->next()) != RC::SUCCESS) {
    printf("nothing in this node, i: %d\n", i);
    tuple_stack_.pop_back();
    children_[i]->close();
    --i;
  }
  if (i < 0) {
    return rc;
  }

  tuple_stack_.push_back(children_[i]->current_tuple());
  ++i;
  for (; i < n; ++i) {
    children_[i]->open();
    assert((rc = children_[i]->next()) == RC::SUCCESS);
    tuple_stack_.push_back(children_[i]->current_tuple());
  }
  return rc;
}

bool PredicateOperator::do_predicate(Tuple &tuple)
{
  if (filter_stmt_ == nullptr || filter_stmt_->filter_units().empty()) {
    return true;
  }

  for (const FilterUnit *filter_unit : filter_stmt_->filter_units()) {
    Expression *left_expr = filter_unit->left();
    Expression *right_expr = filter_unit->right();
    CompOp comp = filter_unit->comp();
    TupleCell left_cell;
    TupleCell right_cell;
    left_expr->get_value(tuple, left_cell);
    right_expr->get_value(tuple, right_cell);

    const int compare = left_cell.compare(right_cell);
    bool filter_result = false;
    switch (comp) {
    case EQUAL_TO: {
      filter_result = (0 == compare); 
    } break;
    case LESS_EQUAL: {
      filter_result = (compare <= 0); 
    } break;
    case NOT_EQUAL: {
      filter_result = (compare != 0);
    } break;
    case LESS_THAN: {
      filter_result = (compare < 0);
    } break;
    case GREAT_EQUAL: {
      filter_result = (compare >= 0);
    } break;
    case GREAT_THAN: {
      filter_result = (compare > 0);
    } break;
    // *****************************like*************************************
    case LIKE_OP: {
      filter_result = left_cell.fuzzy_query_compare(right_cell);
    } break;

    case NOT_LIKE_OP: {
      filter_result = !left_cell.fuzzy_query_compare(right_cell);
    } break;
    // *****************************like*************************************
    default: {
      LOG_WARN("invalid compare type: %d", comp);
    } break;
    }
    if (!filter_result) {
      return false;
    }
  }
  return true;
}

Tuple * PredicateOperator::current_tuple()
{
  // merge multiple table tuples to one tuple
  if (children_.size() == 1) {
    return children_[0]->current_tuple();
  }
  // TODO memory leak
  return current_tuple_;
  // return new CompositeTuple(tuple_stack_);
}

RC PredicateOperator::close()
{
  for (auto child: children_) {
    child->close();
  }
  // children_[0]->close();
  return RC::SUCCESS;
}


// int PredicateOperator::tuple_cell_num() const
// {
//   return children_[0]->tuple_cell_num();
// }
// RC PredicateOperator::tuple_cell_spec_at(int index, TupleCellSpec &spec) const
// {
//   return children_[0]->tuple_cell_spec_at(index, spec);
// }
