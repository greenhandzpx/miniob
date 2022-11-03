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

#include "sql/stmt/update_stmt.h"
#include "common/log/log.h"
#include "sql/parser/parse_defs.h"
#include "storage/common/db.h"

// *************************************************upselect*********************************************************
#include "sql/operator/project_operator.h"
#include "sql/operator/predicate_operator.h"
#include "sql/executor/execute_stage.h"
#include "sql/operator/table_scan_operator.h"
// *************************************************upselect*********************************************************

// UpdateStmt::UpdateStmt(Table *table, Value *values, int value_amount)
//   : table_ (table), values_(values), value_amount_(value_amount)
// UpdateStmt::UpdateStmt(Table *table, const Value *values, int value_amount, FilterStmt *filter_stmt, const char *attribute_name)
//   : table_ (table), values_(values), value_amount_(value_amount), filter_stmt_(filter_stmt), attribute_name_(attribute_name)
// {}

// RC UpdateStmt::create(Db *db, const Updates &update, Stmt *&stmt)
// {
//   // TODO
//   // stmt = nullptr;
//   // return RC::INTERNAL;
  
//   const char *table_name = update.relation_name;
//   if (nullptr == db || nullptr == table_name) {
//     LOG_WARN("invalid argument. db=%p, table_name=%p", 
//              db, table_name);
//     return RC::INVALID_ARGUMENT;
//   }

//   // check whether the table exists
//   Table *table = db->find_table(table_name);
//   if (nullptr == table) {
//     LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
//     return RC::SCHEMA_TABLE_NOT_EXIST;
//   }

//   std::unordered_map<std::string, Table *> table_map;
//   table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));

//   FilterStmt *filter_stmt = nullptr;
//   RC rc = FilterStmt::create(db, table, &table_map,
// 			     update.conditions, update.condition_num, filter_stmt);
//   if (rc != RC::SUCCESS) {
//     LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
//     return rc;
//   }

//   stmt = new UpdateStmt(table, &update.value, 1, filter_stmt, update.attribute_name);
//   return rc;
// }


UpdateStmt::UpdateStmt(Table *table, 
                        Value *values,
                        int value_amount, 
                        FilterStmt *filter_stmt, 
                        char **attribute_name, 
                        size_t values_num)
            : table_ (table), 
              values_(values),
              value_amount_(value_amount), 
              filter_stmt_(filter_stmt), 
              attribute_name_(attribute_name), 
              values_num_(values_num)
{}
 // *************************************************upselect*********************************************************

RC UpdateStmt::create(Db *db, const Updates &update, Stmt *&stmt)
{
  const char *table_name = update.relation_name;
  if (nullptr == db || nullptr == table_name) {
    LOG_WARN("invalid argument. db=%p, table_name=%p", 
             db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));

  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(db, table, &table_map,
			     update.conditions, update.condition_num, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }


  stmt = new UpdateStmt(table, update.values, 1, filter_stmt, const_cast<char **>(update.attribute_names), update.values_num);
  UpdateStmt* u_stmt = dynamic_cast<UpdateStmt*>(stmt);
  Stmt* sstmt;

  for (int i = 0; i < update.values_num; i++) {
    if (update.select_vec[i] == nullptr) continue;
    // 0. check if table names are same to update's
    for (int a = 0; a < update.select_vec[i]->relation_num; a++) {
      if (strcmp(update.select_vec[i]->relations[a], table_name) == 0) {
        printf("You can not specify target table '%s' for update in FROM clause\n", table_name);
        return RC::SUB_SAME_TABLE;
      }
    }
    // 1. create select_stmt
    if (RC::SUCCESS != (rc = SelectStmt::create(db, *(update.select_vec[i]), sstmt, nullptr))) {
      LOG_WARN("update-select: create sub query failed");
      printf("update-select: create sub query failed\n");
      return RC::GENERIC_ERROR;
    }
    auto s_stmt = dynamic_cast<SelectStmt*>(sstmt);
    // 2. create project_oper
    PredicateOperator pred_oper(s_stmt->filter_stmt());
    std::vector<Operator *> scan_opers(s_stmt->tables().size());
    for (int j = 0; j< scan_opers.size(); ++j) {
      printf("add scan oper %d\n", j);
      scan_opers[j] = ExecuteStage::try_to_create_index_scan_operator(s_stmt->filter_stmt());

      if (nullptr == scan_opers[j]) {
        scan_opers[j] = new TableScanOperator(s_stmt->tables()[j]);
      }
      pred_oper.add_child(scan_opers[j]);
    }
    ProjectOperator project_oper;
    project_oper.add_child(&pred_oper);
    bool is_single_table = s_stmt->tables().size() == 1;
    for (const Field &field : s_stmt->query_fields()) {
      if (field.meta() == nullptr) {
        continue;
      }
      project_oper.add_projection(field.table(), field.meta(), is_single_table);
    }
    rc = project_oper.open();
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to open operator");
      return rc;
    }

    // 3. do select
    if (!s_stmt->aggregation_ops().empty()) {
      // aggregation
      std::vector<Value> values(s_stmt->aggregation_ops().size());
      printf("select aggregation: op size %zu\n", values.size());
      if (RC::SUCCESS != (rc = ExecuteStage::aggregation_select_handler(s_stmt, values, project_oper))) {
        return rc;
      }

      if (values.size() != 1) {
        printf("Subquery returns more than 1 row\n");
        rc = RC::SUB_ROW_ERROR;
        return rc;
      }

      *const_cast<Value*>(&u_stmt->values_[i]) = values[0];

    } else {
      // normal select
      Tuple *tuple;
      int j = 0;
      TupleCell cell;
      while ((rc = ExecuteStage::normal_select_handler(s_stmt, tuple, project_oper)) == RC::SUCCESS) {
        // printf("tuple1:");
        // tuple_to_string(std::cout, *tuple);
        // printf("\n");
        tuple->cell_at(0, cell);
        if (tuple->cell_num() != 1) {
          printf("Operand should contain 1 column(s)\n");
          rc = RC::SUB_COL_ERROR;
          return rc;
        }
        j++;
        if (j > 1) {
          printf("Subquery returns more than 1 row\n");
          rc = RC::SUB_ROW_ERROR;
          return rc;
        }
      }
      
      if (j == 0) {
        printf("Subquery returns less than 1 row\n");
        rc = RC::SUB_ROW_ERROR;
        return rc;
      }
      
      // printf("tuple2:");
      // tuple_to_string(std::cout, *tuple);
      // printf("\n");

      // tuple->cell_at(0, cell);

      const_cast<Value*>(&u_stmt->values_[i])->type = cell.attr_type();

      if (cell.attr_type() != NULLS) {
        size_t len;
        if (cell.attr_type() == INTS) {
          len = sizeof(int);
        } else if (cell.attr_type() == CHARS) {
          len = strlen((char*)cell.data());
        } else if (cell.attr_type() == FLOATS) {
          len = sizeof(float);
        } else {
          // todo
          LOG_WARN("bad type in update stmt");
          return RC::SUB_BAD_TYPE;
        }
        if (cell.attr_type() == CHARS) {
          // if (strcmp((const char*)cell.data(), "N01") == 0|| strcmp((const char*)cell.data(), "n01") == 0) {
          //   strcpy((char *)cell.data(), "n2");
          // }
          const_cast<Value*>(&u_stmt->values_[i])->data = strdup(cell.data());
        } else {
          const_cast<Value*>(&u_stmt->values_[i])->data = malloc(len);
          memcpy(const_cast<Value*>(&u_stmt->values_[i])->data, (void*)cell.data(), len);
        }

      }
      
    }
  }

  return RC::SUCCESS;
}






