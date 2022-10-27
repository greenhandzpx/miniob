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
#include "sql/executor/execute_stage.h"
#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include "sql/operator/predicate_operator.h"
#include "sql/parser/parse_defs.h"
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

  // if (children_.size() == 1) {
  //   Operator *oper = children_[0];

  //   while (RC::SUCCESS == (rc = oper->next())) {
  //     Tuple *tuple = oper->current_tuple();
  //     if (nullptr == tuple) {
  //       rc = RC::INTERNAL;
  //       LOG_WARN("failed to get tuple from operator");
  //       break;
  //     }

  //     if (do_predicate(static_cast<RowTuple &>(*tuple))) {
  //       return rc;
  //     }
  //   }
  //   return rc;
  // }

  while (RC::SUCCESS == (rc = next_when_multi_tables())) {
    // if (current_tuple_ != nullptr) {
    //   // free last current tuple
    //   delete current_tuple_;
    // }
    if (parent_tuple_ != nullptr) {
      if (current_tuple_->size() > children_.size()) {
        current_tuple_->pop_back();
      }
      printf("sub query has a parent tuple\n");
      current_tuple_->push_back(parent_tuple_);
      // tuple_stack_.push_back(parent_tuple_);
    }
    // printf("get a new composite tuple\n");
    // current_tuple_ = new CompositeTuple(tuple_stack_);

    // Tuple *tuple = current_tuple();
    if (nullptr == current_tuple_) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get tuple from operator");
      break;
    }

    bool res;
    if (RC::SUCCESS != (rc = do_predicate(*current_tuple_, res))) {
      return rc;
    }
    if (res) {
      return rc;
    }

    if (parent_tuple_ != nullptr) {
      current_tuple_->pop_back();
      // tuple_stack_.pop_back();
    }
  }
  return rc;
}

RC PredicateOperator::next_when_multi_tables() {
  if (is_over_) {
    return RC::RECORD_EOF;
  }

  if (has_accelerated_) {
    return RC::SUCCESS;
  }

  RC rc = RC::SUCCESS;

  int target_tuple_num = children_.size() + (parent_tuple_ ? 1 : 0);
  if (tuple_stack_.size() != target_tuple_num) {
    // this must be the first time to call 
    // if (tuple_stack_.size() != 0) {
    //   LOG_WARN("something error happens");
    //   return RC::INTERNAL;
    // }
    for (auto child: children_) {
      if (child->next() != RC::SUCCESS) {
        LOG_WARN("shouldn't be empty table in predicate chilren");
        return RC::RECORD_EOF;
      }
      tuple_stack_.push_back(child->current_tuple());
      stk_top_++;
    }
    current_tuple_ = new CompositeTuple(tuple_stack_);

    return rc;
  }

  int n = children_.size();
  int i = n - 1;
  // tuple_stack_.pop_back();
  while (i >= 0 && (rc = children_[i]->next()) != RC::SUCCESS) {
    // if (i <= 3) {
    //   printf("nothing in this node, i: %d\n", i);
    // }
    // tuple_stack_.pop_back();
    stk_top_--;
    children_[i]->close();
    --i;
  }
  if (i < 0) {
    // zpx:
    // here means that all tuples have been traveled,
    // then we open all children, because later on the outside will
    // close the predicate operator, which means that the chilren will be
    // closed again, so we open them in advance.
    // note that this is just a work around, which may be able to be optimized
    for (int i = 0; i < children_.size(); ++i) {
      children_[i]->open();
    }
    return rc;
  }

  stk_top_++;
  // tuple_stack_.push_back(children_[i]->current_tuple());
  ++i;
  for (; i < n; ++i) {
    children_[i]->open();
    assert((rc = children_[i]->next()) == RC::SUCCESS);
    // tuple_stack_.push_back(children_[i]->current_tuple());
    stk_top_++;
  }
  return rc;
}

RC PredicateOperator::do_predicate(CompositeTuple &tuple, bool &res)
// bool PredicateOperator::do_predicate(CompositeTuple &tuple)
{
  has_accelerated_ = false;
  if (filter_stmt_ == nullptr || filter_stmt_->filter_units().empty()) {
    res = true;
    return RC::SUCCESS;
  }

  for (const FilterUnit *filter_unit : filter_stmt_->filter_units()) {
    Expression *left_expr = filter_unit->left();
    Expression *right_expr = filter_unit->right();


    switch (filter_unit->get_type()) {
      case Comparison: {

        CompOp comp = filter_unit->comp();
        TupleCell left_cell;
        TupleCell right_cell;
        int left_index = -1, right_index = -1;
        RC rc;
        if (left_expr->type() == ExprType::FIELD) {
          if (RC::SUCCESS != (rc = tuple.find_cell(dynamic_cast<FieldExpr*>(left_expr)->field(), left_cell, left_index))) {
            return rc;
          }
        } else {
          if (RC::SUCCESS != (rc = left_expr->get_value(tuple, left_cell))) {
            res = false;
            return rc;
          }
        }
        if (right_expr->type() == ExprType::FIELD) {
          if (RC::SUCCESS != (rc = tuple.find_cell(dynamic_cast<FieldExpr*>(right_expr)->field(), right_cell, right_index))) {
            return rc;
          }
        } else {
          if (RC::SUCCESS != (rc = right_expr->get_value(tuple, right_cell))) {
            res = false;
            return rc;
          }
        }

        // is null 和 is not null 的逻辑判断
        if (left_cell.attr_type() == AttrType::NULLS || right_cell.attr_type() == AttrType::NULLS) {
          if (comp == LOGICAL_IS) {
            res = left_cell.attr_type() == right_cell.attr_type();
            return RC::SUCCESS;
          } else if (comp == LOGICAL_IS_NOT) {
            res = left_cell.attr_type() != right_cell.attr_type();
            return RC::SUCCESS;
          } else {
            res = false;
            return RC::SUCCESS;
          }
        }

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
          printf("like   %s to %s\n", left_cell.data(), right_cell.data());
          printf("like %d\n", filter_result);
        } break;

        case NOT_LIKE_OP: {
          filter_result = !left_cell.fuzzy_query_compare(right_cell);
          printf("not like   %s to %s\n", left_cell.data(), right_cell.data());
          printf("not like %d\n", filter_result);
        } break;
        // *****************************like*************************************
        default: {
          LOG_WARN("invalid compare type: %d", comp);
        } break;
        }

        if (!filter_result) {
          if (left_index != -1 || right_index != -1) {

            int target_index = left_index > right_index ? left_index : right_index;

            if (target_index == children_.size()) {
              // this tuple is from parent;
              res = false;
              return RC::SUCCESS;
            }
            has_accelerated_ = true;

            // if (target_index == children_.size() - 1) {
            //   return false;
            // } else {
            //   has_accelerated_ = true; 
            // }
            // printf("hhh\n");
            // tuple_to_string(std::cout, *current_tuple_);
            // std::cout << std::endl;
            // if (target_index == 1) {
            //   printf("hhh\n");
            //   tuple_to_string(std::cout, *current_tuple_);
            //   std::cout << std::endl;
            // }
            int tmp = target_index;
            int n = children_.size();
            RC rc;
            for (int i = tmp + 1; i < children_.size(); ++i) {
              // printf("close %d\n", i);
              children_[i]->close();
            }
            while (tmp >= 0 && (rc = children_[tmp]->next()) != RC::SUCCESS) {
              // printf("no value tmp %d\n", tmp);
              children_[tmp]->close();
              --tmp;
            }
            if (tmp < 0) {
              for (int i = 0; i < children_.size(); ++i) {
                children_[i]->open();
              }
              is_over_ = true;
              res = false;
              return RC::SUCCESS;
            }
            ++tmp;
            for (; tmp < n; ++tmp) {
              children_[tmp]->open();
              // printf("open %d\n", tmp);
              assert((rc = children_[tmp]->next()) == RC::SUCCESS);
              while((rc = children_[tmp]->next()) == RC::SUCCESS);
              children_[tmp]->close();
              children_[tmp]->open();
              children_[tmp]->next();
            }
            // printf("ddd\n");
            // tuple_to_string(std::cout, *current_tuple_);
            // std::cout << std::endl;
            // if (children_[target_index]->next() == RC::SUCCESS) {
            //   for (int i = target_index + 1; i < children_.size(); ++i) {
            //     children_[i]->close();
            //     children_[i]->open();
            //   }
            // }
          }          
          res = false;
          return RC::SUCCESS;
        }
      } break;

      case Contain: {
        TupleCell left_cell;
        left_expr->get_value(tuple, left_cell);
        
        // 左值为null,返回false
        if (left_cell.attr_type() == AttrType::NULLS) {
          res = false;
          return RC::SUCCESS;
        }

        auto right_sub_query_expr = dynamic_cast<SubQueryExpr*>(right_expr);

        bool exists; 
        RC rc;
        if (right_sub_query_expr) {
          if (RC::SUCCESS != (rc = right_sub_query_expr->check_contain_or_exist(&tuple, true, &left_cell, exists))) {
            return rc;
          }
        } else {
          auto right_value_set_expr = dynamic_cast<ValueSetExpr*>(right_expr);
          printf("predicate operator: check contain(value set)\n");
          exists = right_value_set_expr->check_contain(left_cell);
        }

        if (!exists) {
          res = false;
          return RC::SUCCESS;
        }
      } break;
      case NotContain: {
        TupleCell left_cell;
        left_expr->get_value(tuple, left_cell);
        
        // 左值为null,返回false
        if (left_cell.attr_type() == AttrType::NULLS) {
          res = false;
          return RC::SUCCESS;
        }

        auto right_sub_query_expr = dynamic_cast<SubQueryExpr*>(right_expr);

        bool notct; 
        RC rc;
        if (right_sub_query_expr) {
          if (RC::SUCCESS != (rc = right_sub_query_expr->check_not_contain_or_exist(&tuple, true, &left_cell, notct))) {
            return rc;
          }
        } else {
          auto right_value_set_expr = dynamic_cast<ValueSetExpr*>(right_expr);
          printf("predicate operator: check contain(value set)\n");
          notct = right_value_set_expr->check_not_contain(left_cell);
        }

        if (!notct) {
          res = false;
          return RC::SUCCESS;
        }
      } break;

      case Exists: 
      case NotExists: {

        auto right_sub_query_expr = dynamic_cast<SubQueryExpr*>(right_expr);

        bool exists; 
        RC rc; 
        if (RC::SUCCESS != (rc = right_sub_query_expr->check_contain_or_exist(&tuple, false, nullptr, exists))) {
          return rc;
        }

        if (!exists) {
          if (filter_unit->get_type() == Exists) {
            res = false;
            return RC::SUCCESS;
          }
        } else {
          if (filter_unit->get_type() == NotExists) {
            res = false;
            return RC::SUCCESS;
          }
        }
      } break;

    }

  }
  res = true;
  return RC::SUCCESS;
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
