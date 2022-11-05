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

#include "rc.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/expr/expression.h"
#include "sql/operator/predicate_operator.h"
#include "sql/operator/project_operator.h"
#include "sql/operator/table_scan_operator.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/executor/execute_stage.h"
#include "storage/common/db.h"
#include "storage/common/table.h"

FilterStmt::~FilterStmt()
{
  for (FilterUnit *unit : filter_units_) {
    delete unit;
  }
  filter_units_.clear();
}

RC FilterStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
		      const Condition *conditions, int condition_num,
		      FilterStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt = nullptr;

  FilterStmt *tmp_stmt = new FilterStmt();
  for (int i = 0; i < condition_num; i++) {
    FilterUnit *filter_unit = nullptr;
    rc = create_filter_unit(db, default_table, tables, conditions[i], filter_unit);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->filter_units_.push_back(filter_unit);
//**************************************************func******************************************************
    tmp_stmt->left_arg_.push_back(conditions[i].left_args_value);
    tmp_stmt->left_op.push_back(conditions[i].left_funcop);
    tmp_stmt->right_arg_.push_back(conditions[i].right_args_value);
    tmp_stmt->right_op.push_back(conditions[i].right_funcop);

    if (conditions[i].isfunc == 1) tmp_stmt->hasfunc_ = 1;
  }
//**************************************************func******************************************************
  stmt = tmp_stmt;
  return rc;
}

RC get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
		       const RelAttr &attr, Table *&table, const FieldMeta *&field)
{
  if (common::is_blank(attr.relation_name)) {
    table = default_table;
  } else if (nullptr != tables) {
    auto iter = tables->find(std::string(attr.relation_name));
    if (iter != tables->end()) {
      table = iter->second;
    }
  } else {
    table = db->find_table(attr.relation_name);
  }
  if (nullptr == table) {
    LOG_WARN("No such table: attr.relation_name: %s", attr.relation_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  field = table->table_meta().field(attr.attribute_name);
  if (nullptr == field) {
    LOG_WARN("no such field in table: table %s, field %s", table->name(), attr.attribute_name);
    table = nullptr;
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  return RC::SUCCESS;
}

RC FilterStmt::create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
				  const Condition &condition, FilterUnit *&filter_unit)
{
  RC rc = RC::SUCCESS;
  
  CompOp comp = condition.comp;
  if (comp < EQUAL_TO || comp >= NO_OP) {
    LOG_WARN("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }

  Expression *left = nullptr;
  Expression *right = nullptr;
  if (condition.left_is_attr) {
    Table *table = nullptr;
    const FieldMeta *field = nullptr;
    rc = get_table_and_field(db, default_table, tables, condition.left_attr, table, field);  
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }
    left = new FieldExpr(table, field);
  } else if (condition.left_is_sub_query) {
    assert(condition.left_select != nullptr);
    Stmt *stmt;
    std::vector<std::pair<std::string, Table*>> parent_tables(tables->begin(), tables->end());
    // if ((rc = SelectStmt::create(db, *condition.right_select, stmt)) != RC::SUCCESS) {
    //   return rc;
    // }
    if ((rc = SelectStmt::create(db, *condition.left_select, stmt, &parent_tables)) != RC::SUCCESS) {
      return rc;
    }

    SelectStmt *select_stmt = reinterpret_cast<SelectStmt*>(stmt);

    left = new SubQueryExpr(select_stmt); 

  } else {
    left = new ValueExpr(condition.left_value);
  }

  if (condition.right_is_attr) {

    Table *table = nullptr;
    const FieldMeta *field = nullptr;
    rc = get_table_and_field(db, default_table, tables, condition.right_attr, table, field);  
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      delete left;
      return rc;
    }
    right = new FieldExpr(table, field);

  } else if (condition.right_is_sub_query) {  

    assert(condition.right_select != nullptr);
    Stmt *stmt;
    std::vector<std::pair<std::string, Table*>> parent_tables(tables->begin(), tables->end());
    // if ((rc = SelectStmt::create(db, *condition.right_select, stmt)) != RC::SUCCESS) {
    //   return rc;
    // }
    if ((rc = SelectStmt::create(db, *condition.right_select, stmt, &parent_tables)) != RC::SUCCESS) {
      return rc;
    }

    SelectStmt *select_stmt = reinterpret_cast<SelectStmt*>(stmt);


    /**
      in complex sub query, aggregation cannot be computed at this time, since the aggregation
      may alse need the tuple come from the parent (f**k complex sub query)
    */
    right = new SubQueryExpr(select_stmt); 

    // if (select_stmt->aggregation_ops().size() > 0) {

    //   // if the sub query is aggregation, we can compute the result at first
    //   // in order not to compute it repeatly later on

    //   if (select_stmt->aggregation_ops().size() != 1) {
    //     // TODO: not sure 
    //     return RC::GENERIC_ERROR;
    //   }

    //   PredicateOperator pred_oper(select_stmt->filter_stmt());

    //   std::vector<Operator *> scan_opers(select_stmt->tables().size());
    //   for (int i = scan_opers.size()-1; i >= 0; --i) {
    //     // scan_opers[i] = try_to_create_index_scan_operator(select_stmt->filter_stmt());
    //     if (nullptr == scan_opers[i]) {
    //       scan_opers[i] = new TableScanOperator(select_stmt->tables()[i]);
    //     }
    //     printf("%d scan op table %s\n", i, select_stmt->tables()[i]->name());
    //     pred_oper.add_child(scan_opers[i]);
    //   }

    //   // TODO memory leak (scan_opers)

    //   ProjectOperator project_oper;
    //   project_oper.add_child(&pred_oper);
    //   bool is_single_table = select_stmt->tables().size() == 1;
    //   // for (int i = select_stmt->query_fields().size()-1; i >= 0; --i) {
    //   //   project_oper.add_projection(select_stmt->query_fields()[i].table(), select_stmt->query_fields()[i].meta(), is_single_table);
    //   // }
    //   for (const Field &field : select_stmt->query_fields()) {
    //     project_oper.add_projection(field.table(), field.meta(), is_single_table);
    //   }
    //   rc = project_oper.open();
    //   if (rc != RC::SUCCESS) {
    //     LOG_WARN("failed to open operator");
    //     return rc;
    //   }

    //   std::vector<Value> values(select_stmt->aggregation_ops().size());
    //   // Value value;
    //   ExecuteStage::aggregation_select_handler(dynamic_cast<SelectStmt*>(select_stmt), values, project_oper);
    //   right = new ValueExpr(values[0]);

    // } else {

    //   // if the sub query is normal select, compute the tuple set every time
    //   // we get a tuple from the parent query(and put it into the sub query)

    //   right = new SubQueryExpr(select_stmt); 
    // }

  } else if (condition.right_is_set) {

    // select * from t where id in (1, 3, 4, 6);

    std::vector<Value> value_set(condition.right_value_set_num);
    for (int i = 0; i < value_set.size(); ++i) {
      value_set[i] = condition.right_value_set[i];
    }
    right = new ValueSetExpr(value_set);

  } else {

    right = new ValueExpr(condition.right_value);
  }

  filter_unit = new FilterUnit;
  filter_unit->set_comp(comp);
  filter_unit->set_left(left);
  filter_unit->set_right(right);
  filter_unit->set_type(condition.condition_type);
  filter_unit->set_and(condition.is_and);

  // 检查两个类型是否能够比较
  return rc;
}
