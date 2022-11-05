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
// Created by Meiyi 
//

#include <mutex>
#include "parse_defs.h"
#include "sql/parser/parse.h"
#include "rc.h"
#include "common/log/log.h"
#include "sql/parser/parse_defs.h"



RC parse(char *st, Query *sqln);

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
void relation_attr_init(RelAttr *relation_attr, const char *relation_name, const char *attribute_name)
{
  if (relation_name != nullptr) {
    relation_attr->relation_name = strdup(relation_name);
  } else {
    relation_attr->relation_name = nullptr;
  }
  relation_attr->attribute_name = strdup(attribute_name);
  relation_attr->alias_name = nullptr;
}

void relation_attr_destroy(RelAttr *relation_attr)
{
  free(relation_attr->relation_name);
  free(relation_attr->attribute_name);
  relation_attr->relation_name = nullptr;
  relation_attr->attribute_name = nullptr;
}

void value_init_integer(Value *value, int v)
{
  value->type = INTS;
  value->data = malloc(sizeof(v));
  memcpy(value->data, &v, sizeof(v));
}
void value_init_float(Value *value, float v)
{
  value->type = FLOATS;
  value->data = malloc(sizeof(v));
  memcpy(value->data, &v, sizeof(v));
}
void value_init_string(Value *value, const char *v)
{
  value->type = CHARS;
  value->data = strdup(v);
}
void value_init_null(Value *value) {
  value->type = NULLS;
  value->data = strdup("null");
}
void value_destroy(Value *value)
{
  value->type = UNDEFINED;
  free(value->data);
  value->data = nullptr;
}
bool check_date(int y, int m, int d)
{
    static int mon[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool leap = (y%400==0 || (y%100 && y%4==0));
    return y > 0
        && (m > 0)&&(m <= 12)
        && (d > 0)&&(d <= ((m==2 && leap)?1:0) + mon[m]);
}
int value_init_date(Value* value, const char* v) {
  int y,m,d;
  sscanf(v, "%d-%d-%d", &y, &m, &d); //not check return value eq 3, lex guarantee
  bool b = check_date(y,m,d);
  if(!b) {
    return 0;  // date invalid
  }
  value->type = DATES;
  int dv = y*10000+m*100+d;
  value->data = malloc(sizeof(dv)); //TODO:check malloc failure
  memcpy(value->data, &dv, sizeof(dv));
  return 1;
}

void condition_init(Condition *condition, FilterType condition_type, CompOp comp, int left_is_attr, int left_is_sub_query, RelAttr *left_attr, Value *left_value,
    Selects *left_select, int right_is_attr, int right_is_sub_query, int right_is_set, RelAttr *right_attr, Value *right_value, Selects *right_select, Value *value_set, 
    size_t value_set_num)
// void condition_init(Condition *condition, FilterType condition_type, CompOp comp, int left_is_attr, RelAttr *left_attr, Value *left_value,
//     int right_is_attr, int right_is_sub_query, RelAttr *right_attr, Value *right_value, Selects *right_select)
{
  printf("condition init: type %d\n", condition_type);
  condition->condition_type = condition_type;
  condition->comp = comp;
  condition->left_is_attr = left_is_attr;
  condition->left_is_sub_query = left_is_sub_query;
  condition->right_is_attr = right_is_attr;
  condition->right_is_sub_query = right_is_sub_query;
  condition->right_is_set = right_is_set;
  condition->is_and = 1;

  if (condition_type != Exists && condition_type != NotExists) {
    if (left_is_attr) {
      condition->left_attr = *left_attr;
    } else if (left_is_sub_query) {
      condition->left_select = left_select;
    } else {
      condition->left_value = *left_value;
    }
  }

  if (right_is_attr) {
    condition->right_attr = *right_attr;
  } else if (right_is_sub_query) {
    condition->right_select = right_select;
  } else if (right_is_set) {
    condition->right_value_set_num = value_set_num;
    for (int i = 0; i < value_set_num; ++i) {
      condition->right_value_set[i] = value_set[i];
    }
  } else {
    condition->right_value = *right_value;
  }
}

//*******************************************************func***************************************************************

void condition_init_func(Condition *condition, FilterType condition_type, CompOp comp, 

    int left_is_attr, int left_is_sub_query, RelAttr *left_attr, Value *left_value, Selects *left_select, 
    int right_is_attr, int right_is_sub_query, int right_is_set, RelAttr *right_attr, Value *right_value, Selects *right_select, 
    Value *value_set, size_t value_set_num, 
    FuncAttrCon* left_func_attr, FuncAttrCon* right_func_attr)

{
  condition->condition_type = condition_type;
  condition->comp = comp;
  if (left_func_attr != NULL && right_func_attr != NULL) {
    
    condition->left_is_attr = left_func_attr->value.type == UNDEFINED;
    condition->left_is_sub_query = 0;
    condition->right_is_attr = right_func_attr->value.type == UNDEFINED;
    condition->right_is_sub_query = 0;
    condition->right_is_set = 0;
    condition->is_and = 1;

    condition->left_args_value = left_func_attr->args_value;
    condition->left_funcop = left_func_attr->funcop;

    if (condition->left_is_attr) {
      condition->left_attr = *left_func_attr->attr;
    } else {
      condition->left_value = left_func_attr->value;
    }
  

    condition->right_args_value = right_func_attr->args_value;
    condition->right_funcop = right_func_attr->funcop;

    if (condition->right_is_attr) {
      condition->right_attr = *right_func_attr->attr;
    } else {
      condition->right_value = right_func_attr->value;
    }

  } else if (left_func_attr != NULL && right_func_attr == NULL) {

    condition->left_is_attr = left_func_attr->value.type == UNDEFINED;
    condition->left_is_sub_query = 0;
    condition->right_is_attr = right_is_attr;
    condition->right_is_sub_query = right_is_sub_query;
    condition->right_is_set = right_is_set;
    condition->is_and = 1;
    
    condition->left_args_value = left_func_attr->args_value;
    condition->left_funcop = left_func_attr->funcop;

    if (condition->left_is_attr) {
      condition->left_attr = *left_func_attr->attr;
    } else {
      condition->left_value = left_func_attr->value;
    }

    if (right_is_attr) {
      condition->right_attr = *right_attr;
    } else if (right_is_sub_query) {
      condition->right_select = right_select;
    } else if (right_is_set) {
      condition->right_value_set_num = value_set_num;
      for (int i = 0; i < value_set_num; ++i) {
        condition->right_value_set[i] = value_set[i];
      }
    } else {
      condition->right_value = *right_value;
    }

  } else if (left_func_attr == NULL && right_func_attr != NULL) {

    condition->left_is_attr = left_is_attr;
    condition->left_is_sub_query = left_is_sub_query;
    condition->right_is_attr = right_func_attr->value.type == UNDEFINED;
    condition->right_is_sub_query = 0;
    condition->right_is_set = 0;
    condition->is_and = 1;
    
    if (left_is_attr) {
      condition->left_attr = *left_attr;
    } else if (left_is_sub_query) {
      condition->left_select = left_select;
    } else {
      condition->left_value = *left_value;
    }

    condition->right_args_value = right_func_attr->args_value;
    condition->right_funcop = right_func_attr->funcop;
    
    if (condition->right_is_attr) {
      condition->right_attr = *right_func_attr->attr;
    } else {
      condition->right_value = right_func_attr->value;
    }

  } else {
    printf("panic!!!!!!!! in condition_init_func\n");
  }
}

//*******************************************************func***************************************************************
void condition_destroy(Condition *condition)
{
  if (condition->condition_type != Exists &&
      condition->condition_type != NotExists) {
    if (condition->left_is_attr) {
      relation_attr_destroy(&condition->left_attr);
    } else if (condition->left_is_sub_query) {
      // TODO: memory leak
    } else  {
      value_destroy(&condition->left_value);
    }
  }
  
  if (condition->right_is_attr) {
    relation_attr_destroy(&condition->right_attr);
  } else if (condition->right_is_sub_query) {
      // TODO: memory leak
  } else if (condition->right_is_set) {
  }  else {
    value_destroy(&condition->right_value);
  }
}

void having_condition_init(Having_Condition *condition, AggregationOp aggr, CompOp cmpop, Value *value, RelAttr *attr) {
  condition->aggr = aggr;
  condition->cmpOp = cmpop;
  condition->value = *value;
  condition->attr = *attr;
}

void having_condition_destroy(Having_Condition *condition) {
  free(condition);
}

void attr_info_init(AttrInfo *attr_info, const char *name, AttrType type, size_t length, int is_nullable)
{
  attr_info->name = strdup(name);
  if (type == TEXTS) {
    attr_info->type = CHARS;
    attr_info->length = 4096;
  } else {
    attr_info->type = type;
    attr_info->length = length;
  }
  attr_info->is_nullable = is_nullable;
}
void attr_info_destroy(AttrInfo *attr_info)
{
  free(attr_info->name);
  attr_info->name = nullptr;
}

void selects_init(Selects *selects, ...);
void selects_append_attribute(Selects *selects, RelAttr *rel_attr)
{
  //******************************************func******************************************************
  selects->function_ops[selects->attr_num] = NO_FUNCTION_OP;
  selects->function_value1[selects->attr_num].type = UNDEFINED;
  selects->function_value2[selects->attr_num].type = UNDEFINED;
  //******************************************func******************************************************
  selects->attributes[selects->attr_num++] = *rel_attr;
  printf("attr_num = %d\n", selects->attr_num);
}

//**********************************************************func******************************************************************
void selects_append_funcop(Selects *selects, FunctionOp function_op)
{
  selects->function_ops[selects->attr_num - 1] = function_op;
  selects->isfunc = 1;
}

void selects_append_funcvalue1(Selects *selects, Value * value)
{
  
  if (value == 0) selects->function_value1[selects->attr_num - 1].type = UNDEFINED;
  else selects->function_value1[selects->attr_num - 1] = *value;
}

void selects_append_funcvalue2(Selects *selects, Value * value)
{
  if (value == 0) selects->function_value2[selects->attr_num - 1].type = UNDEFINED;
  else selects->function_value2[selects->attr_num - 1] = *value;
}

void selects_modify_alias_name(Selects *selects, char *attr_name) {
  selects->attributes[selects->attr_num - 1].alias_name = attr_name;
}

char* value2string(Value * value) {
  char* res = (char*)malloc(30);
  memset((void*)res, 30, 0);

  if (value->type == INTS) {
    sprintf(res, "%d", *(int*)value->data);
  } else if (value->type = CHARS) {
    strcpy(res, "\'");
    // strcat(res, "\'");
    strcat(res, (char*)value->data);
    strcat(res, "\'");
  } else if (value->type = FLOATS) {
    sprintf(res, "%f", *(float*)value->data);
  } else {
    printf("do not support %d to char* in value2string, panic\n", value->type);
    while(1);
  }
 
  return res;
}
//**********************************************************func******************************************************************
void selects_append_aggregation_op(Selects *selects, AggregationOp aggregation_op)
{
  selects->aggrops_idx_in_fields[selects->aggregation_num] = selects->aggregation_num + selects->attr_num;
  selects->aggregation_ops[selects->aggregation_num++] = aggregation_op;
}
void selects_append_relation(Selects *selects, const char *relation_name, const char *relation_alias)
{
  // selects->relations[selects->relation_num++] = strdup(relation_name);
  printf("append a relation %s\n", relation_name);
  // adjust the order
  // TODO optimize
  selects->relation_num++;

  for (int i = selects->relation_num - 1; i > 0; --i) {
    selects->relations[i] = selects->relations[i-1];
    selects->relation_alias[i] = selects->relation_alias[i-1];
  }
  if (relation_name != NULL) {
    selects->relations[0] = strdup(relation_name);
  } else {
    selects->relations[0] = NULL;
  }
  
  if (relation_alias) {
    selects->relation_alias[0] = strdup(relation_alias);
  } else {
    selects->relation_alias[0] = NULL;
  }
}

void selects_append_conditions(Selects *selects, Condition conditions[], size_t condition_num)
{
  assert(condition_num <= sizeof(selects->conditions) / sizeof(selects->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    selects->conditions[i] = conditions[i];
  }
  selects->condition_num = condition_num;
}

void selects_append_aggrattr(Selects *selects, RelAttr *rel_attr) {
  selects->aggregation_attrs[selects->aggregation_attr_num++] = *rel_attr;
}

void selects_append_orderattr(Selects *selects, RelAttr *rel_attr, int is_asc) {
  selects->order_attrs[selects->order_attr_num] = *rel_attr;
  selects->is_asc[selects->order_attr_num++] = is_asc;
}

void selects_append_groupattr(Selects *selects, RelAttr *rel_attr) {
  selects->group_attrs[selects->group_attr_num++] = *rel_attr;
}

void selects_append_havingcondition(Selects *selects, Having_Condition *condition) {
  selects->having_conditions[selects->having_condition_num++] = *condition;
}

void selects_set_order(Selects *selects, int order) {
  selects->is_order = order;
}

void selects_set_group(Selects *selects, int group) {
  printf("select set group %d\n", group);
  selects->is_group = group;
}

void selects_set_having(Selects *selects, int having) {
  selects->is_having = having;
}

void selects_destroy(Selects *selects)
{
  for (size_t i = 0; i < selects->attr_num; i++) {
    relation_attr_destroy(&selects->attributes[i]);
  }
  selects->attr_num = 0;

  for (size_t i = 0; i < selects->relation_num; i++) {
    free(selects->relations[i]);
    selects->relations[i] = NULL;
  }
  selects->relation_num = 0;

  for (size_t i = 0; i < selects->condition_num; i++) {
    condition_destroy(&selects->conditions[i]);
  }
  selects->condition_num = 0;
}

// void inserts_init(Inserts *inserts, const char *relation_name, Value values[], size_t value_num)
void inserts_init(Inserts *inserts, const char *relation_name, Value tuples[][MAX_NUM], size_t tuple_num, size_t value_num[])
{
  // assert(value_num <= sizeof(inserts->values) / sizeof(inserts->values[0]));
  for (int i = 0; i < tuple_num; ++i) {
    assert(value_num[i] <= sizeof(inserts->tuples[i]) / sizeof(inserts->tuples[i][0]));

    for (size_t k = 0; k < value_num[i]; ++k) {
      // printf("copy insert value\n");
      printf("insert parse: value type: %d\n", tuples[i][k].type);
      inserts->tuples[i][k] = tuples[i][k];
    }
    inserts->value_num[i] = value_num[i];
  } 

  inserts->tuple_num = tuple_num;

  inserts->relation_name = strdup(relation_name);

}
void inserts_destroy(Inserts *inserts)
{
  free(inserts->relation_name);
  inserts->relation_name = nullptr;

  for (size_t k = 0; k < inserts->tuple_num; ++k) {
    for (size_t i = 0; i < inserts->value_num[k]; i++) {
      value_destroy(&inserts->tuples[k][i]);
    }
  }
  inserts->tuple_num = 0;
}

void deletes_init_relation(Deletes *deletes, const char *relation_name)
{
  deletes->relation_name = strdup(relation_name);
}

void deletes_set_conditions(Deletes *deletes, Condition conditions[], size_t condition_num)
{
  assert(condition_num <= sizeof(deletes->conditions) / sizeof(deletes->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    deletes->conditions[i] = conditions[i];
  }
  deletes->condition_num = condition_num;
}
void deletes_destroy(Deletes *deletes)
{
  for (size_t i = 0; i < deletes->condition_num; i++) {
    condition_destroy(&deletes->conditions[i]);
  }
  deletes->condition_num = 0;
  free(deletes->relation_name);
  deletes->relation_name = nullptr;
}


// void updates_init(Updates *updates, const char *relation_name, const char *attribute_name, Value *value,
//     Condition conditions[], size_t condition_num)
// {
//   updates->relation_name = strdup(relation_name);
//   updates->attribute_name = strdup(attribute_name);
//   updates->value = *value;

//   assert(condition_num <= sizeof(updates->conditions) / sizeof(updates->conditions[0]));
//   for (size_t i = 0; i < condition_num; i++) {
//     updates->conditions[i] = conditions[i];
//   }
//   updates->condition_num = condition_num;
// }

// void updates_destroy(Updates *updates)
// {
//   free(updates->relation_name);
//   free(updates->attribute_name);
//   updates->relation_name = nullptr;
//   updates->attribute_name = nullptr;

//   value_destroy(&updates->value);

//   for (size_t i = 0; i < updates->condition_num; i++) {
//     condition_destroy(&updates->conditions[i]);
//   }
//   updates->condition_num = 0;
// }

// ***********************************************upselect********************************************************

void updates_init(Updates *updates, const char *relation_name, const char* attribute_names[], Value* values, size_t values_num,
    Condition conditions[], size_t condition_num, Selects *select_vec[])
{
  updates->relation_name = strdup(relation_name);

  updates->attribute_names = (char**)malloc(values_num * sizeof(char*));
  updates->values = (Value*)malloc(values_num * sizeof(Value));
  updates->select_vec = (Selects**)malloc(values_num * sizeof(Selects*));
  for (size_t i = 0; i < values_num; i++) {
    updates->select_vec[i] = nullptr;
  }

  updates->values_num = values_num;
  
  
  for (size_t i = 0; i < values_num; i++) {
    updates->attribute_names[i] = strdup(attribute_names[i]);
    if (select_vec[i] != nullptr) {
      updates->select_vec[i] = select_vec[i];
    } else {
      updates->values[i] = values[i];
    }
  }

  assert(condition_num <= sizeof(updates->conditions) / sizeof(updates->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    updates->conditions[i] = conditions[i];
  }
  updates->condition_num = condition_num;
}


void updates_destroy(Updates *updates)
{
  free(updates->relation_name);
  updates->relation_name = nullptr;

  for (size_t i = 0; i < updates->values_num; i++) {
    free(updates->attribute_names[i]);
  }

  free(updates->values);
  updates->values = nullptr;
  free(updates->select_vec);
  updates->select_vec = nullptr;
  free(updates->attribute_names);
  updates->attribute_names = nullptr;

  for (size_t i = 0; i < updates->condition_num; i++) {
    condition_destroy(&updates->conditions[i]);
  }
  updates->condition_num = 0;
}




// ***********************************************upselect********************************************************

void create_table_append_attribute(CreateTable *create_table, AttrInfo *attr_info)
{
  create_table->attributes[create_table->attribute_count++] = *attr_info;
}

void create_table_init_name(CreateTable *create_table, const char *relation_name)
{
  create_table->relation_name = strdup(relation_name);
}

void create_table_destroy(CreateTable *create_table)
{
  for (size_t i = 0; i < create_table->attribute_count; i++) {
    attr_info_destroy(&create_table->attributes[i]);
  }
  create_table->attribute_count = 0;
  free(create_table->relation_name);
  create_table->relation_name = nullptr;
}

void drop_table_init(DropTable *drop_table, const char *relation_name)
{
  drop_table->relation_name = strdup(relation_name);
}

void drop_table_destroy(DropTable *drop_table)
{
  free(drop_table->relation_name);
  drop_table->relation_name = nullptr;
}

void show_index_init(ShowIndex *show_index, const char *relation_name)
{
  show_index->relation_name = strdup(relation_name);
}

void show_index_destroy(ShowIndex *show_index)
{
  free(show_index->relation_name);
  show_index->relation_name = nullptr;
}

void create_index_init(
    CreateIndex *create_index, const char *index_name, const char *relation_name, const char *attr_name, int is_unique)
{
  create_index->index_name = strdup(index_name);
  create_index->relation_name = strdup(relation_name);
  // create_index->attribute_name[create_index->attribute_num++] = strdup(attr_name);
  create_index->attribute_num++;
  for (int i = create_index->attribute_num - 1; i > 0; --i) {
    create_index->attribute_name[i] = create_index->attribute_name[i-1];
  }
  create_index->attribute_name[0] = strdup(attr_name);
  create_index->unique = is_unique;
}

void create_index_append_attribute(CreateIndex *create_index, const char *attr_name)
{
  create_index->attribute_num++;
  for (int i = create_index->attribute_num - 1; i > 0; --i) {
    create_index->attribute_name[i] = create_index->attribute_name[i-1];
  }
  create_index->attribute_name[0] = strdup(attr_name);
  for (int i = 0; i < create_index->attribute_num; ++i) {
    printf("attr %s", create_index->attribute_name[i]);
  }
}

void create_index_destroy(CreateIndex *create_index)
{
  free(create_index->index_name);
  free(create_index->relation_name);

  create_index->index_name = nullptr;
  create_index->relation_name = nullptr;
  for (int i = 0; i < create_index->attribute_num; ++i) {
    free(create_index->attribute_name[i]);
    create_index->attribute_name[i] = nullptr;
  }
}

void drop_index_init(DropIndex *drop_index, const char *index_name)
{
  drop_index->index_name = strdup(index_name);
}

void drop_index_destroy(DropIndex *drop_index)
{
  free((char *)drop_index->index_name);
  drop_index->index_name = nullptr;
}

void desc_table_init(DescTable *desc_table, const char *relation_name)
{
  desc_table->relation_name = strdup(relation_name);
}

void desc_table_destroy(DescTable *desc_table)
{
  free((char *)desc_table->relation_name);
  desc_table->relation_name = nullptr;
}

void load_data_init(LoadData *load_data, const char *relation_name, const char *file_name)
{
  load_data->relation_name = strdup(relation_name);

  if (file_name[0] == '\'' || file_name[0] == '\"') {
    file_name++;
  }
  char *dup_file_name = strdup(file_name);
  int len = strlen(dup_file_name);
  if (dup_file_name[len - 1] == '\'' || dup_file_name[len - 1] == '\"') {
    dup_file_name[len - 1] = 0;
  }
  load_data->file_name = dup_file_name;
}

void load_data_destroy(LoadData *load_data)
{
  free((char *)load_data->relation_name);
  free((char *)load_data->file_name);
  load_data->relation_name = nullptr;
  load_data->file_name = nullptr;
}

void query_init(Query *query)
{
  query->flag = SCF_ERROR;
  memset(&query->sstr, 0, sizeof(query->sstr));
}

Query *query_create()
{
  Query *query = (Query *)malloc(sizeof(Query));
  if (nullptr == query) {
    LOG_ERROR("Failed to alloc memroy for query. size=%ld", sizeof(Query));
    return nullptr;
  }

  query_init(query);
  return query;
}

void query_reset(Query *query)
{
  switch (query->flag) {
    case SCF_SELECT: {
      selects_destroy(&query->sstr.selection);
    } break;
    case SCF_INSERT: {
      inserts_destroy(&query->sstr.insertion);
    } break;
    case SCF_DELETE: {
      deletes_destroy(&query->sstr.deletion);
    } break;
    case SCF_UPDATE: {
      updates_destroy(&query->sstr.update);
    } break;
    case SCF_CREATE_TABLE: {
      create_table_destroy(&query->sstr.create_table);
    } break;
    case SCF_DROP_TABLE: {
      drop_table_destroy(&query->sstr.drop_table);
    } break;
    case SCF_CREATE_INDEX: {
      create_index_destroy(&query->sstr.create_index);
    } break;
    case SCF_DROP_INDEX: {
      drop_index_destroy(&query->sstr.drop_index);
    } break;
    case SCF_SYNC: {

    } break;
    case SCF_SHOW_TABLES:
      break;

    case SCF_DESC_TABLE: {
      desc_table_destroy(&query->sstr.desc_table);
    } break;

    case SCF_LOAD_DATA: {
      load_data_destroy(&query->sstr.load_data);
    } break;
    case SCF_CLOG_SYNC:
    case SCF_BEGIN:
    case SCF_COMMIT:
    case SCF_ROLLBACK:
    case SCF_HELP:
    case SCF_EXIT:
    case SCF_ERROR:
      break;
  }
}

void query_destroy(Query *query)
{
  query_reset(query);
  free(query);
}
#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

////////////////////////////////////////////////////////////////////////////////

extern "C" int sql_parse(const char *st, Query *sqls);

RC parse(const char *st, Query *sqln)
{
  sql_parse(st, sqln);

  if (sqln->flag == SCF_ERROR)
    return SQL_SYNTAX;
  else if (sqln->flag == SCF_INVALID_DATE)
    return INVALID_DATE_IN_PARSE;
  else {
    return SUCCESS;
  }
}