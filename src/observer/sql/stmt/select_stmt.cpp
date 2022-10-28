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
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "rc.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/filter_stmt.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/common/db.h"
#include "storage/common/table.h"

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

static void wildcard_fields(Table *table, std::vector<Field> &field_metas)
{
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    field_metas.push_back(Field(table, table_meta.field(i)));
  }
}

RC SelectStmt::create(Db *db, const Selects &select_sql, Stmt *&stmt, std::vector<std::pair<std::string, Table*>> *parent_tables)
// RC SelectStmt::create(Db *db, const Selects &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  if (select_sql.attr_num == 0 && select_sql.aggregation_attr_num == 0) {
    return GENERIC_ERROR;
  }

  bool order = select_sql.is_order == 1 ? true : false;

  // collect tables in `from` statement
  std::vector<Table *> tables;
  std::unordered_map<std::string, Table *> table_map;

  if (parent_tables != nullptr) {
    // add the parent tables into the table map(when sub query)
    for (auto &table: *parent_tables) {
      table_map.insert(table);
    }
  }
  
  for (size_t i = 0; i < select_sql.relation_num; i++) {
    const char *table_name = select_sql.relations[i];
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table*>(table_name, table));
  }

  
  // collect query fields in `select` statement
  std::vector<Field> query_fields;
  for (int i = select_sql.attr_num - 1; i >= 0; i--) {
    const RelAttr &relation_attr = select_sql.attributes[i];

    if (common::is_blank(relation_attr.relation_name) && 0 == strcmp(relation_attr.attribute_name, "*")) {

      // select * from t1, t2

      if (select_sql.aggregation_num > 0) {
        // if this is an aggregation op
        // then it must be COUNT
        // and we just push an empty field
        if (select_sql.aggregation_ops[i] != COUNT_OP) {
          return RC::GENERIC_ERROR;
        }

        query_fields.push_back(Field());
      } else {

        for (Table *table : tables) {
          wildcard_fields(table, query_fields);
        }

      }


    } else if (!common::is_blank(relation_attr.relation_name)) { // TODO

      // select t1.id from t1, t2
      // select t1.* from t1, t2

      const char *table_name = relation_attr.relation_name;
      const char *field_name = relation_attr.attribute_name;

      if (0 == strcmp(table_name, "*")) {
        if (0 != strcmp(field_name, "*")) {
          LOG_WARN("invalid field name while table is *. attr=%s", field_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        for (Table *table : tables) {
          wildcard_fields(table, query_fields);
        }
      } else {
        auto iter = table_map.find(table_name);
        if (iter == table_map.end()) {
          LOG_WARN("no such table in from list: %s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table *table = iter->second;
        if (0 == strcmp(field_name, "*")) {
          wildcard_fields(table, query_fields);
        } else {
          const FieldMeta *field_meta = table->table_meta().field(field_name);
          if (nullptr == field_meta) {
            LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
            return RC::SCHEMA_FIELD_MISSING;
          }

        query_fields.push_back(Field(table, field_meta));
        }
      }
    } else {

      // select id from t1

      if (tables.size() != 1) {
        LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name);
        return RC::SCHEMA_FIELD_MISSING;
      }

      Table *table = tables[0];
      const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name);
      if (nullptr == field_meta) {
        LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name);
        return RC::SCHEMA_FIELD_MISSING;
      }

      query_fields.push_back(Field(table, field_meta));
    }
  }

  // collect order fields in `order` statement
  std::vector<std::pair<Field, bool>> order_fields;
  if (order) {
    for (int i = select_sql.order_attr_num - 1; i >= 0; i--) {
      const RelAttr &relation_attr = select_sql.order_attrs[i];
      bool asc = select_sql.is_asc[i] == 1 ? true : false;
      if (0 == strcmp(relation_attr.attribute_name, "*")) {
        return RC::GENERIC_ERROR;
      } else if (!common::is_blank(relation_attr.relation_name)) { // TODO

        // order by t1.id

        const char *table_name = relation_attr.relation_name;
        const char *field_name = relation_attr.attribute_name;

        // if (0 == strcmp(table_name, "*")) {
        //   if (0 != strcmp(field_name, "*")) {
        //     LOG_WARN("invalid field name while table is *. attr=%s", field_name);
        //     return RC::SCHEMA_FIELD_MISSING;
        //   }
        //   for (Table *table : tables) {
        //     wildcard_fields(table, query_fields);
        //   }
        // } else {
        auto iter = table_map.find(table_name);
        if (iter == table_map.end()) {
          LOG_WARN("no such table in from list: %s", table_name);
            return RC::SCHEMA_FIELD_MISSING;
        }
        Table *table = iter->second;
        // if (0 == strcmp(field_name, "*")) {
        //   wildcard_fields(table, query_fields);
        // } else {
        const FieldMeta *field_meta = table->table_meta().field(field_name);
        if (nullptr == field_meta) {
          LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
            return RC::SCHEMA_FIELD_MISSING;
        }
        order_fields.push_back(std::make_pair(Field(table, field_meta), asc));
          // }
        // }
      } else {

        // order by id

        if (tables.size() != 1) {
          LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name);
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table *table = tables[0];
        const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name);
        if (nullptr == field_meta) {
          LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name);
          return RC::SCHEMA_FIELD_MISSING;
        }

        order_fields.push_back(std::make_pair(Field(table, field_meta), asc));
      }
    }

  }

  std::vector<Field> group_fields;
  bool group = select_sql.is_group == 1 ? true : false;
  // group 有问题 写完aggr再重写
  
  if (select_sql.aggregation_num > 0 && select_sql.aggregation_num != select_sql.aggregation_attr_num) {
    /**
      We will have one field corresponding to one aggregation function,
      so the num of fields must be equal to the num of aggregation function
      error case like: select avg(id1, id2) from t1;
    */
    printf("aggregation_num_is %d but aggregation_attr_num is %d\n", select_sql.aggregation_num, select_sql.aggregation_attr_num);
    return RC::GENERIC_ERROR;
  }

  std::vector<Field> aggr_fields;
  for (int i = select_sql.aggregation_attr_num - 1; i >= 0; --i) {
    const RelAttr &relation_attr = select_sql.aggregation_attrs[i];
    if (common::is_blank(relation_attr.relation_name) && 0 == strcmp(relation_attr.attribute_name, "*")) {

      // select count(*)

      if (select_sql.aggregation_num > 0) {
        // if this is an aggregation op
        // then it must be COUNT
        // and we just push an empty field

        // 一个聚合函数中包含多列 或者聚合操作不为count(*)
        if (select_sql.aggregation_ops[i] != COUNT_OP) {
          return RC::GENERIC_ERROR;
        }

        aggr_fields.push_back(Field());
      }
    } else if (!common::is_blank(relation_attr.relation_name)) { // TODO

      // select t1.id from t1, t2
      // select t1.* from t1, t2

      const char *table_name = relation_attr.relation_name;
      const char *field_name = relation_attr.attribute_name;

      if (0 == strcmp(table_name, "*")) {
        printf("aggr on *.id / *.*\n");
        return RC::SCHEMA_FIELD_MISSING;
        // if (0 != strcmp(field_name, "*")) {
        //   LOG_WARN("invalid field name while table is *. attr=%s", field_name);
        //   return RC::SCHEMA_FIELD_MISSING;
        // }
        // aggr_fields.push_back(Field());
      } else {
        auto iter = table_map.find(table_name);
        if (iter == table_map.end()) {
          LOG_WARN("no such table in from list: %s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table *table = iter->second;
        if (0 == strcmp(field_name, "*")) {
          // wildcard_fields(table, query_fields);
          if (select_sql.aggregation_ops[i] == COUNT_OP) {
            aggr_fields.push_back(Field(table, nullptr));
          }
        } else {
          const FieldMeta *field_meta = table->table_meta().field(field_name);
          if (nullptr == field_meta) {
            LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
            return RC::SCHEMA_FIELD_MISSING;
          }

          aggr_fields.push_back(Field(table, field_meta));
        }
      }
    } else {

      // select id from t1

      if (tables.size() != 1) {
        LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name);
        return RC::SCHEMA_FIELD_MISSING;
      }

      Table *table = tables[0];
      const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name);
      if (nullptr == field_meta) {
        LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name);
        return RC::SCHEMA_FIELD_MISSING;
      }

      aggr_fields.push_back(Field(table, field_meta));
    }
  }


  LOG_INFO("got %d tables in from stmt and %d fields in query stmt", tables.size(), query_fields.size());

  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(db, default_table, &table_map,
           select_sql.conditions, select_sql.condition_num, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  std::vector<AggregationOp> aggregation_ops(select_sql.aggregation_num);
  size_t n = query_fields.size();
  for (int i = 0; i < select_sql.aggregation_num; ++i) {
    aggregation_ops[i] = select_sql.aggregation_ops[i];
    // if (aggregation_ops[i] == AVG_OP || aggregation_ops[i] == SUM_OP) {
    //   if (query_fields[n-i-1].attr_type() == AttrType::CHARS || 
    //       query_fields[n-i-1].attr_type() == AttrType::DATES) {
    //     return RC::GENERIC_ERROR;
    //   } 
    // }
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();
  select_stmt->tables_.swap(tables);
  select_stmt->query_fields_.swap(query_fields);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->aggregation_ops_ = aggregation_ops;
  stmt = select_stmt;
  select_stmt->order_ = order;
  select_stmt->aggr_fields_.swap(aggr_fields);
  if (order) {
    select_stmt->order_fields_.swap(order_fields);
  }
  select_stmt->group_ = group;
  if (group) {
    select_stmt->group_fields_.swap(group_fields);
  }
  return RC::SUCCESS;
}
