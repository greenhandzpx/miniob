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

void SubQueryExpr::start_query(Tuple *parent_tuple, std::vector<Tuple*> &tuple_set) {

  printf("sub query: start query\n");

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
  while ((rc = ExecuteStage::normal_select_handler(select_stmt_, tuple, project_oper)) == RC::SUCCESS) {
    printf("sub_query:do_select: get a tuple\n");
    tuple_set.push_back(tuple);
  }


}

// void SubQueryExpr::add_parent_tuple(Tuple *parent_tuple) {
//   parent_tuple_ = parent_tuple;
// }