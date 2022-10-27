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

#include "sql/expr/expression.h"
#include "common/log/log.h"
#include "sql/expr/tuple_cell.h"
#include "sql/operator/predicate_operator.h"
#include "sql/operator/project_operator.h"
#include "sql/operator/table_scan_operator.h"
// #include "sql/expr/tuple.h"
#include "sql/executor/execute_stage.h"


RC FieldExpr::get_value(const Tuple &tuple, TupleCell &cell) const
{
  return tuple.find_cell(field_, cell);
}

RC ValueExpr::get_value(const Tuple &tuple, TupleCell & cell) const
{
  cell = tuple_cell_;
  return RC::SUCCESS;
}

RC SubQueryExpr::get_value(const Tuple &tuple, TupleCell & cell) const {

  RC rc;
  PredicateOperator pred_oper(select_stmt_->filter_stmt());

  std::vector<Operator *> scan_opers(select_stmt_->tables().size());
  for (int i = 0; i< scan_opers.size(); ++i) {
    printf("add scan oper %d\n", i);
    scan_opers[i] = ExecuteStage::try_to_create_index_scan_operator(select_stmt_->filter_stmt());
    if (nullptr == scan_opers[i]) {
      // TODO memory leak
      scan_opers[i] = new TableScanOperator(select_stmt_->tables()[i]);
    }
    pred_oper.add_child(scan_opers[i]);
  }

  pred_oper.set_parent_tuple(const_cast<Tuple*>(&tuple));

  ProjectOperator project_oper;
  project_oper.add_child(&pred_oper);

  bool is_single_table = select_stmt_->tables().size() == 1;

  for (const Field &field : select_stmt_->query_fields()) {
    if (field.meta() == nullptr) {
      continue;
    }
    project_oper.add_projection(field.table(), field.meta(), is_single_table);
  }
  rc = project_oper.open();

  Tuple *tmp_tuple;

  int cnt = 0;
  while ((rc = ExecuteStage::normal_select_handler(select_stmt_, tmp_tuple, project_oper)) == RC::SUCCESS) {
    if (cnt == 1 || tmp_tuple->cell_num() != 1) {
      // when invoking get_value of a sub query expression
      // the result must be exactly only one row
      LOG_WARN("more than one result of the sub query");
      printf("more than one result of the sub query\n");
      return RC::GENERIC_ERROR;
    }
    cnt = 1;
    return tmp_tuple->cell_at(0, cell);
  }

  // no result of this sub query
  LOG_WARN("no result of the sub query");
  printf("no result of the sub query\n");
  return RC::GENERIC_ERROR;
}



bool SubQueryExpr::check_contain_or_exist(Tuple *parent_tuple, bool check_contain, TupleCell *left_cell) {

  printf("sub query: start query\n");

  // std::vector<Tuple*> tuple_set;
  RC rc;
  PredicateOperator pred_oper(select_stmt_->filter_stmt());

  std::vector<Operator *> scan_opers(select_stmt_->tables().size());
  for (int i = 0; i< scan_opers.size(); ++i) {
    printf("add scan oper %d\n", i);
    scan_opers[i] = ExecuteStage::try_to_create_index_scan_operator(select_stmt_->filter_stmt());
    if (nullptr == scan_opers[i]) {
      // TODO memory leak
      scan_opers[i] = new TableScanOperator(select_stmt_->tables()[i]);
    }
    pred_oper.add_child(scan_opers[i]);
  }

  pred_oper.set_parent_tuple(parent_tuple);

  ProjectOperator project_oper;
  project_oper.add_child(&pred_oper);

  bool is_single_table = select_stmt_->tables().size() == 1;

  for (const Field &field : select_stmt_->query_fields()) {
    if (field.meta() == nullptr) {
      continue;
    }
    project_oper.add_projection(field.table(), field.meta(), is_single_table);
  }
  rc = project_oper.open();

  Tuple *tuple;
  bool check_exist = !check_contain;
  while ((rc = ExecuteStage::normal_select_handler(select_stmt_, tuple, project_oper)) == RC::SUCCESS) {
    printf("sub_query:do_select: get a tuple\n");
    // tuple_set.push_back(tuple);
    TupleCell tmp_cell;
    if (tuple->cell_at(0, tmp_cell) != RC::SUCCESS) {
      LOG_WARN("sub query tuple get cell wrong");
      return false;
    }
    if (check_exist) {
      // check exist
      if(tmp_cell.attr_type() == AttrType::NULLS) {
        // loop until find a tuple that isn't NULL
        continue;
      }
      return true;
    }

    // check contain
    if (tuple->cell_num() != 1) {
      // the sub query must select only one field
      // TODO: not sure
      return false;
    }
    if(left_cell->attr_type() == AttrType::NULLS || tmp_cell.attr_type() == AttrType::NULLS) {
      // loop until find a tuple that isn't NULL
      continue;
    }
    int cmp = left_cell->compare(tmp_cell);
    if (cmp == 0) {
      return true;
    }
  }
  
  return false;

  // if (!check_contain) {
  //   // check exist
  //   return !tuple_set.empty();
  // }

  // // check contain
  // assert(left_cell != nullptr);
  // bool exists = false;
  // for (Tuple *tmp_tuple: tuple_set) {
  //   // auto tmp_tuple = dynamic_cast<ProjectTuple*>(dummy_tuple);
  //   if (tmp_tuple->cell_num() != 1) {
  //     // the sub query must select only one field
  //     // TODO: not sure
  //     return false;
  //   }
  //   TupleCell tmp_cell;
  //   if (tmp_tuple->cell_at(0, tmp_cell) != RC::SUCCESS) {
  //     LOG_WARN("sub query tuple get cell wrong");
  //     return false;
  //   }
  //   int cmp = left_cell->compare(tmp_cell);
  //   if (cmp != 0) {
  //     continue; 
  //   }
  //   exists = true;
  //   break; 
  // }
  // return exists;
}

bool SubQueryExpr::check_not_contain_or_exist(Tuple *parent_tuple, bool check_contain, TupleCell *left_cell) {

  printf("sub query: start query\n");

  // std::vector<Tuple*> tuple_set;
  RC rc;
  PredicateOperator pred_oper(select_stmt_->filter_stmt());

  std::vector<Operator *> scan_opers(select_stmt_->tables().size());
  for (int i = 0; i< scan_opers.size(); ++i) {
    printf("add scan oper %d\n", i);
    scan_opers[i] = ExecuteStage::try_to_create_index_scan_operator(select_stmt_->filter_stmt());
    if (nullptr == scan_opers[i]) {
      // TODO memory leak
      scan_opers[i] = new TableScanOperator(select_stmt_->tables()[i]);
    }
    pred_oper.add_child(scan_opers[i]);
  }

  pred_oper.set_parent_tuple(parent_tuple);

  ProjectOperator project_oper;
  project_oper.add_child(&pred_oper);

  bool is_single_table = select_stmt_->tables().size() == 1;

  for (const Field &field : select_stmt_->query_fields()) {
    if (field.meta() == nullptr) {
      continue;
    }
    project_oper.add_projection(field.table(), field.meta(), is_single_table);
  }
  rc = project_oper.open();

  Tuple *tuple;

  bool check_exist = !check_contain;
  
  while ((rc = ExecuteStage::normal_select_handler(select_stmt_, tuple, project_oper)) == RC::SUCCESS) {
    printf("sub_query:do_select: get a tuple\n");
    // tuple_set.push_back(tuple);
    TupleCell tmp_cell;
    if (tuple->cell_at(0, tmp_cell) != RC::SUCCESS) {
      LOG_WARN("sub query tuple get cell wrong");
      return false;
    }

    if (check_exist) {
      // check not exist
      return false;
    }
    // check not contain
    if(tmp_cell.attr_type() == AttrType::NULLS) {
      return false;
    }
    int cmp = left_cell->compare(tmp_cell);
    if (cmp == 0) {
      return false;
    }
  }
  return true;

}

// void SubQueryExpr::add_parent_tuple(Tuple *parent_tuple) {
//   parent_tuple_ = parent_tuple;
// }


bool ValueSetExpr::check_contain(TupleCell &other_tuple_cell) const {
  for (auto &value: value_set_) {
    TupleCell tmp = TupleCell(value.type, (char *)value.data);
    if (tmp.attr_type() == AttrType::NULLS) {
      continue;
    }
    if (other_tuple_cell.compare(tmp) == 0) {
      printf("value set expr: find an equal value\n");
      return true;
    }
  }
  return false;
}


bool ValueSetExpr::check_not_contain(TupleCell &other_tuple_cell) const {
  for (auto &value: value_set_) {
    TupleCell tmp = TupleCell(value.type, (char *)value.data);
    if (tmp.attr_type() == AttrType::NULLS || other_tuple_cell.compare(tmp) == 0) {
      printf("value set expr: find an equal value\n");
      return false;
    }
  }
  return false;
}
bool ValueSetExpr::check_contain(Value &other_value) const {
  // TODO
  assert(false);
  return true;
}