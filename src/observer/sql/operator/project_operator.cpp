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
// Created by WangYunlai on 2022/07/01.
//

#include "common/log/log.h"
#include "sql/operator/project_operator.h"
#include "storage/record/record.h"
#include "storage/common/table.h"

RC ProjectOperator::open()
{
  if (children_.size() != 1) {
    LOG_WARN("project operator must has 1 child");
    return RC::INTERNAL;
  }

  Operator *child = children_[0];
  RC rc = child->open();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  return RC::SUCCESS;
}

RC ProjectOperator::next()
{
  return children_[0]->next();
}

RC ProjectOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}
Tuple *ProjectOperator::current_tuple()
{
  tuple_.set_tuple(children_[0]->current_tuple());
  // printf("tuple addr %p\n", &tuple_);
  return &tuple_;
}

void ProjectOperator::add_projection(const Table *table, const FieldMeta *field_meta, bool is_single_table)
{
  // 对单表来说，展示的(alias) 字段总是字段名称，
  // 对多表查询来说，展示的alias 需要带表名字
  TupleCellSpec *spec = new TupleCellSpec(new FieldExpr(table, field_meta));
  if (field_meta->has_alias()) {
    // the field has alias, then just print the alias no matter wether this is multi tables or not
    printf("column alias %s\n", field_meta->get_alias());
    spec->set_alias(strdup(field_meta->get_alias()));
    // then remove the alias
    const_cast<FieldMeta *>(field_meta)->set_alias("");
  } else {
    if (is_single_table) {
      if (field_meta->has_alias()) {
        spec->set_alias(field_meta->get_alias());
      } else {
        spec->set_alias(field_meta->name());
      }
    } else {
      // TODO memory leak
      std::string *res = new std::string;
      std::string table_name;
      if (table->table_meta().has_alias()) {
        table_name = table->table_meta().get_alias();
        printf("table has alias : %s\n", table_name.c_str());
      } else {
        table_name = table->name();
      }
      std::string field_name;
      if (field_meta->has_alias()) {
        field_name = field_meta->get_alias();
      } else {
        field_name = field_meta->name();
      }
      *res += table_name + "." + field_name;
      printf("column alias %s\n", res->c_str());
      spec->set_alias(res->c_str());
    }
  }

  tuple_.add_cell_spec(spec);
}

RC ProjectOperator::tuple_cell_spec_at(int index, const TupleCellSpec *&spec) const
{
  return tuple_.cell_spec_at(index, spec);
}
