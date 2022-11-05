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

#include "util/util.h"

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
  while (RC::SUCCESS == (rc = next_when_multi_tables())) {
    if (parent_tuple_ != nullptr) {
      if (current_tuple_->size() > children_.size()) {
        current_tuple_->pop_back();
      }
      printf("sub query has a parent tuple\n");
      current_tuple_->push_back(parent_tuple_);
    }
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

  /**
    Since we now need to suppport `AND` and `OR`,
    we cannot return as soon as we get a condition that hasn't been met
    because we need to wait to see whether there is any condition that is met
    between `OR`
  */
  bool has_not_met = false;  
  int idx = 0;
  for (const FilterUnit *filter_unit : filter_stmt_->filter_units()) {

    //********************************************************func********************************************************
    Expression *left_expr;
    Expression *right_expr;
    
    if (filter_stmt_->hasfunc_ == 1) {
      

      Expression *left_expr_res = filter_unit->left();
      Expression *right_expr_res = filter_unit->right();
      
      Value left_arg = filter_stmt_->left_arg_[idx];
      FunctionOp left_func = filter_stmt_->left_op[idx]; 
      Value right_arg = filter_stmt_->right_arg_[idx]; 
      FunctionOp right_func = filter_stmt_->right_op[idx]; 
      idx++;

      TupleCell left_cell;
      TupleCell right_cell;
      RC rc;
      int left_index = -1, right_index = -1;

      if (left_expr_res->type() == ExprType::FIELD) {
        if (RC::SUCCESS != (rc = tuple.find_cell(dynamic_cast<FieldExpr*>(left_expr_res)->field(), left_cell, left_index))) {
          return rc;
        }
      } else {
        if (RC::SUCCESS != (rc = left_expr_res->get_value(tuple, left_cell))) {
          res = false;
          return rc;
        }
      }

      if (right_expr_res->type() == ExprType::FIELD) {
        if (RC::SUCCESS != (rc = tuple.find_cell(dynamic_cast<FieldExpr*>(right_expr_res)->field(), right_cell, right_index))) {
          return rc;
        }
      } else {
        if (RC::SUCCESS != (rc = right_expr_res->get_value(tuple, right_cell))) {
          res = false;
          return rc;
        }
      }

      if (left_func == LENGTH_OP) {
        left_expr = new ValueExpr;
        int *data = (int*)malloc(sizeof(int));
        if (left_cell.attr_type() != CHARS) {
          printf("panic1\n");
          return RC::MISS_TYPE;
        }
        *data = strlen((char*)left_cell.data());
        dynamic_cast<ValueExpr*>(left_expr)->tuple_cell_ = TupleCell(INTS, (char*)data);
      } else if (left_func == ROUND_OP) {
        left_expr = new ValueExpr;
        float *data = (float*)malloc(sizeof(float));
        if (left_cell.attr_type() != FLOATS || left_arg.type != INTS && left_arg.type != UNDEFINED) {
          printf("panic2\n");
          return RC::MISS_TYPE;
        }
        if (left_arg.type == INTS) {
          *data = round(*(float*)left_cell.data(), *(int*)left_arg.data);
        } else {
          *data = round1(*(float*)left_cell.data());
        }
        
        dynamic_cast<ValueExpr*>(left_expr)->tuple_cell_ = TupleCell(FLOATS, (char*)data);
      } else if (left_func == DATE_FORMAT_OP) {
        left_expr = new ValueExpr;
        char *data = (char*)malloc(15);
        if (left_arg.type != CHARS) {
          printf("panic3\n");
          return RC::MISS_TYPE;
        }
        data = date_format(*(int*)left_cell.data(), (char*)left_arg.data);
        dynamic_cast<ValueExpr*>(left_expr)->tuple_cell_ = TupleCell(INTS, (char*)data);
      } else {
        left_expr = left_expr_res;
      }

      if (right_func == LENGTH_OP) {
        right_expr = new ValueExpr;
        int *data = (int*)malloc(sizeof(int));
        if (right_cell.attr_type() != CHARS) {
          printf("panic1\n");
          return RC::MISS_TYPE;
        }
        *data = strlen((char*)right_cell.data());
        dynamic_cast<ValueExpr*>(right_expr)->tuple_cell_ = TupleCell(INTS, (char*)data);
      } else if (right_func == ROUND_OP) {
        right_expr = new ValueExpr;
        float *data = (float*)malloc(sizeof(float));
        if (right_cell.attr_type() != FLOATS || right_arg.type != INTS) {
          printf("panic2\n");
          return RC::MISS_TYPE;
        }
        *data = round(*(float*)right_cell.data(), *(int*)right_arg.data);
        dynamic_cast<ValueExpr*>(right_expr)->tuple_cell_ = TupleCell(FLOATS, (char*)data);
      } else if (right_func == DATE_FORMAT_OP) {
        right_expr = new ValueExpr;
        char *data = (char*)malloc(15);
        if (right_arg.type != CHARS) {
          printf("panic3\n");
          return RC::MISS_TYPE;
        }
        data = date_format(*(int*)right_cell.data(), (char*)right_arg.data);
        dynamic_cast<ValueExpr*>(right_expr)->tuple_cell_ = TupleCell(INTS, (char*)data);
      } else {
        right_expr = right_expr_res;
      }

      
    } else {
      left_expr = filter_unit->left();
      right_expr = filter_unit->right();
    }
    //********************************************************func********************************************************


    if (has_not_met) {
      // we should iterate until find a `OR` condition
      if (filter_unit->get_and()) {
        continue;
      } 
      has_not_met = false;
    } else {
      if (!filter_unit->get_and()) {
        res = true;
        return RC::SUCCESS;
      }
    }

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
            if (!res) {
              has_not_met = true;
            }
          } else if (comp == LOGICAL_IS_NOT) {
            res = left_cell.attr_type() != right_cell.attr_type();
            if (!res) {
              has_not_met = true;
            }
            // return RC::SUCCESS;
          } else {
            res = false;
            has_not_met = true;
            // return RC::SUCCESS;
          }
          break;
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
          if ((left_index != -1 || right_index != -1)) {
            
            // accelerate the iteration of multiple children case(used for inner-join )

            /**
              The following is to find whether there is an `OR` condition,
              if so, we shouldn't accelerate. 
            */
            bool has_or = false;
            auto filter_units = filter_stmt_->filter_units();
            for (int i = 0; i < filter_stmt_->filter_units().size(); ++i) {
              if (!filter_units[i]->get_and()) {
                has_or = true;
                break;
              }
            }
            if (has_or) {
              has_not_met = true;
              break;
            }

            int target_index = left_index > right_index ? left_index : right_index;

            if (target_index == children_.size()) {
              // this tuple is from parent;
              // shouldn't accelerate
              res = false;
              has_not_met = true;
              break;
              // return RC::SUCCESS;
            }
            has_accelerated_ = true;

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
              has_not_met = true;
              // return RC::SUCCESS;
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
          has_not_met = true;
          // return RC::SUCCESS;
        }
      } break;

      case Contain: {
        TupleCell left_cell;
        left_expr->get_value(tuple, left_cell);

        // 左值为null,返回false
        if (left_cell.attr_type() == AttrType::NULLS) {
          res = false;
          has_not_met = true;
          break;
          // return RC::SUCCESS;
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
          has_not_met = true;
          // return RC::SUCCESS;
        }
      } break;
      case NotContain: {
        TupleCell left_cell;
        left_expr->get_value(tuple, left_cell);
        
        // 左值为null,返回false
        if (left_cell.attr_type() == AttrType::NULLS) {
          res = false;
          has_not_met = true;
          break;
          // return RC::SUCCESS;
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
          has_not_met = true;
          // return RC::SUCCESS;
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
            has_not_met = true;
            // return RC::SUCCESS;
          }
        } else {
          if (filter_unit->get_type() == NotExists) {
            res = false;
            has_not_met = true;
            // return RC::SUCCESS;
          }
        }
      } break;

    }

  }

  if (has_not_met) {
    res = false;
  } else {
    res = true;
  }
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
