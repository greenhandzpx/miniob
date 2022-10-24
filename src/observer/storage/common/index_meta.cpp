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
// Created by Meiyi & Wangyunlai.wyl on 2021/5/18.
//

#include "storage/common/index_meta.h"
#include "storage/common/field_meta.h"
#include "storage/common/table_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "rc.h"
#include "json/json.h"
#include <json/value.h>

const static Json::StaticString FIELD_NAME("name");
const static Json::StaticString FIELD_FIELD_NAME("field_name");
const static Json::StaticString FIELD_UNIQUE("unique");

RC IndexMeta::init(const char *name, std::vector<const FieldMeta*> &field, bool is_unique)
{
  if (common::is_blank(name)) {
    LOG_ERROR("Failed to init index, name is empty.");
    return RC::INVALID_ARGUMENT;
  }

  name_ = name;
  for (int i = 0; i < field.size(); ++i) {
    field_.push_back(field[i]->name());
  }
  unique_ = is_unique;
  return RC::SUCCESS;
}

void IndexMeta::to_json(Json::Value &json_value) const
{
  json_value[FIELD_NAME] = name_;
  // json_value[FIELD_FIELD_NAME] = field_;
  for (int i = 0; i < field_.size(); ++i) {
    json_value[FIELD_FIELD_NAME].append(field_[i]);
  }
  json_value[FIELD_UNIQUE] = unique_;
}

RC IndexMeta::from_json(const TableMeta &table, const Json::Value &json_value, IndexMeta &index)
{
  const Json::Value &name_value = json_value[FIELD_NAME];
  const Json::Value &field_value = json_value[FIELD_FIELD_NAME];
  const Json::Value &unique_value = json_value[FIELD_UNIQUE];
  if (!name_value.isString()) {
    LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }

  if (!field_value.isArray()) {
    LOG_ERROR("Field name of index [%s] is not an array. json value=%s",
        name_value.asCString(),
        field_value.toStyledString().c_str());
    return RC::GENERIC_ERROR;

  }
  // if (!field_value.isString()) {
  //   LOG_ERROR("Field name of index [%s] is not a string. json value=%s",
  //       name_value.asCString(),
  //       field_value.toStyledString().c_str());
  //   return RC::GENERIC_ERROR;
  // }

  std::vector<const FieldMeta *> fields(field_value.size());
  for (int i = 0; i < field_value.size(); ++i) {
    fields[i] = table.field(field_value[i].asCString());
    if (nullptr == fields[i]) {
      LOG_ERROR("Deserialize index [%s]: no such field: %s", name_value.asCString(), field_value.asCString());
      return RC::SCHEMA_FIELD_MISSING;
    }
    
  }
  return index.init(name_value.asCString(), fields, unique_value.asBool());
}

const char *IndexMeta::name() const
{
  return name_.c_str();
}

std::vector<const char *> IndexMeta::field() const
{
  std::vector<const char*> res;
  for (auto &field: field_) {
    // printf("f: %s, field size: %d\n", field.c_str(), field_.size());
    res.push_back(field.c_str());
  }
  return res;
  // return field_.c_str();
}

bool IndexMeta::unique() const
{
  return unique_;
}

void IndexMeta::desc(std::ostream &os) const
{
  os << "index name=" << name_ << ", field=";
  for (auto &field: field_) {
    os << field << " ";
  }
}