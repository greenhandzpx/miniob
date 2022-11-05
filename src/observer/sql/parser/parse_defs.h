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

#ifndef __OBSERVER_SQL_PARSER_PARSE_DEFS_H__
#define __OBSERVER_SQL_PARSER_PARSE_DEFS_H__

#include <stddef.h>

#define MAX_NUM 20
#define MAX_REL_NAME 20
#define MAX_ATTR_NAME 20
#define MAX_ERROR_MESSAGE 20
#define MAX_DATA 50

//属性结构体
typedef struct RelAttr{
  char *relation_name;   // relation name (may be NULL) 表名
  char *attribute_name;  // attribute name              属性名
  char *alias_name;      // 属性的别名
} RelAttr;


typedef enum {
  Comparison,  // select * from t where a > b;
  Contain,     // select * from t where a in (select b from t2)
  NotContain,
  Exists,      // select * from t where exists (select * from t2 where t2.id > t.id)
  NotExists,
} FilterType;

typedef enum {
  EQUAL_TO,     //"="     0
  LESS_EQUAL,   //"<="    1
  NOT_EQUAL,    //"<>"    2
  LESS_THAN,    //"<"     3
  GREAT_EQUAL,  //">="    4
  GREAT_THAN,   //">"     5
  //***************************like*******************************
  LIKE_OP,      //"like"  6
  NOT_LIKE_OP,  //"not like"  7
  //***************************like*******************************
  LOGICAL_IS,
  LOGICAL_IS_NOT,

  NO_OP
} CompOp;

typedef enum {
  NO_AGGREGATION_OP,
  COUNT_OP,
  AVG_OP,
  MAX_OP,
  MIN_OP,
  SUM_OP,
} AggregationOp;

//************************************************************func********************************************************************
typedef enum {
  NO_FUNCTION_OP,
  LENGTH_OP,
  ROUND_OP,
  DATE_FORMAT_OP,
} FunctionOp;
//************************************************************func********************************************************************

//属性值类型
typedef enum
{
  UNDEFINED,
  CHARS,
  INTS,
  FLOATS,
  DATES,
  TEXTS,
  NULLS
} AttrType;

//属性值
typedef struct _Value {
  AttrType type;  // type of value
  void *data;     // value
} Value;

struct Selects;

//***********************************************************func****************************************************************
typedef struct FuncAttrCon {
  RelAttr* attr;
  Value value;
  FunctionOp funcop;
  Value args_value;
} FuncAttrCon;
//***********************************************************func****************************************************************

typedef struct _Condition {
  int left_is_sub_query;
  int left_is_attr;    // TRUE if left-hand side is an attribute
                       // 1时，操作符左边是属性名，0时，是属性值
  // int left_is_nothing;  // when the condition type is `Exists`
  Value left_value;    // left-hand side value if left_is_attr = FALSE
  RelAttr left_attr;   // left-hand side attribute
  struct Selects *left_select; // right-hand side sub query(i.e. select query)

  //*****************************************************func*************************************************************
  FunctionOp left_funcop;
  Value left_args_value;
  //*****************************************************func*************************************************************

  // int is_comp;         // is comparison condition
  // int is_in;           // is in condition

  FilterType condition_type;
  CompOp comp;         // comparison operator

  int right_is_sub_query;
  int right_is_attr;   // TRUE if right-hand side is an attribute
  int right_is_set;    // TRUE if right-hand side is a set(like (2, 4, 5, 9))
                       // 1时，操作符右边是属性名，0时，是属性值
  struct Selects *right_select; // right-hand side sub query(i.e. select query)
  RelAttr right_attr;  // right-hand side attribute if right_is_attr = TRUE 右边的属性
  Value right_value_set[MAX_NUM];
  size_t right_value_set_num;
  Value right_value;   // right-hand side value if right_is_attr = FALSE

  //*****************************************************func*************************************************************
  FunctionOp right_funcop;
  Value right_args_value;

  int isfunc;
  //*****************************************************func*************************************************************

  int is_and;  // TRUE if: conditino1 and condition2 (condition2 refers to this condition)
} Condition;

// having子句专用无敌condition
typedef struct _having_condition
{
  AggregationOp aggr;
  RelAttr attr;
  CompOp cmpOp;
  Value value;
} Having_Condition;

typedef struct having_filter {
  size_t value_idx;
  CompOp cmpop;
  Value right_value;
} Having_Filter;

// struct of select
typedef struct Selects {
  size_t attr_num;                // Length of attrs in Select clause
  RelAttr attributes[MAX_NUM];    // attrs in Select clause
  size_t relation_num;            // Length of relations in Fro clause
  char *relations[MAX_NUM];       // relations in From clause
  char *relation_alias[MAX_NUM];
  size_t condition_num;           // Length of conditions in Where clause
  Condition conditions[MAX_NUM];  // conditions in Where clause

  size_t aggregation_num;
  size_t aggregation_attr_num;
  AggregationOp aggregation_ops[MAX_NUM];
  char *aggregation_alias[MAX_NUM];
  size_t aggrops_idx_in_fields[MAX_NUM];
  RelAttr aggregation_attrs[MAX_NUM];
  
  size_t order_attr_num;
  RelAttr order_attrs[MAX_NUM];    // attrs in order by
  int is_asc[MAX_NUM];                      // is order by asc
  int is_order;                    // 是否排序

  size_t group_attr_num;
  RelAttr group_attrs[MAX_NUM];
  int is_group;
  size_t having_condition_num;
  Having_Condition having_conditions[MAX_NUM];
  int is_having; 

  //*****************************************************func*************************************************************
  FunctionOp function_ops[MAX_NUM];
  Value function_value1[MAX_NUM];
  Value function_value2[MAX_NUM];
  int isfunc;
  int isvaluefunc;

  //*****************************************************func*************************************************************

} Selects;

// struct of insert
typedef struct {
  char *relation_name;    // Relation to insert into
  // size_t value_num;       // Length of values
  // Value values[MAX_NUM];  // values to insert
  size_t tuple_num;
  size_t value_num[MAX_NUM];       // Length of values
  // Value values[MAX_NUM][MAX_NUM];  // values to insert
  Value tuples[MAX_NUM][MAX_NUM];  // values to insert
} Inserts;

// struct of delete
typedef struct {
  char *relation_name;            // Relation to delete from
  size_t condition_num;           // Length of conditions in Where clause
  Condition conditions[MAX_NUM];  // conditions in Where clause
} Deletes;

// struct of update
typedef struct {
  char *relation_name;            // Relation to update
  // char *attribute_name;           // Attribute to update
  // Value value;                    // update value

  // ****************************************upselect****************************************
  char **attribute_names;           // Attribute to update
  Value* values;                    // update value
  size_t values_num;                // values num
  struct Selects **select_vec;    // for update select
  // ****************************************upselect****************************************

  
  size_t condition_num;           // Length of conditions in Where clause
  Condition conditions[MAX_NUM];  // conditions in Where clause
} Updates;

typedef struct {
  char *name;     // Attribute name
  AttrType type;  // Type of attribute
  size_t length;  // Length of attribute
  int is_nullable; // use int to store nullable, 1 = true, 0 = false
} AttrInfo;

// struct of craete_table
typedef struct {
  char *relation_name;           // Relation name
  size_t attribute_count;        // Length of attribute
  AttrInfo attributes[MAX_NUM];  // attributes
} CreateTable;

// struct of drop_table
typedef struct {
  char *relation_name;  // Relation name
} DropTable;

// struct of show index
typedef struct {
  char *relation_name;  // Relation name
} ShowIndex;

// struct of create_index
typedef struct {
  char *index_name;      // Index name
  char *relation_name;   // Relation name
  char *attribute_name[MAX_NUM];  // Attribute name
  size_t attribute_num;
  int  unique;
} CreateIndex;

// struct of  drop_index
typedef struct {
  const char *index_name;  // Index name
} DropIndex;

typedef struct {
  const char *relation_name;
} DescTable;

typedef struct {
  const char *relation_name;
  const char *file_name;
} LoadData;

union Queries {
  Selects selection;
  Inserts insertion;
  Deletes deletion;
  Updates update;
  CreateTable create_table;
  DropTable drop_table;
  CreateIndex create_index;
  DropIndex drop_index;
  DescTable desc_table;
  LoadData load_data;
  ShowIndex show_index;
  char *errors;
};

// 修改yacc中相关数字编码为宏定义
enum SqlCommandFlag {
  SCF_ERROR = 0,
  SCF_SELECT,
  SCF_INSERT,
  SCF_UPDATE,
  SCF_DELETE,
  SCF_CREATE_TABLE,
  SCF_DROP_TABLE,
  SCF_CREATE_INDEX,
  SCF_DROP_INDEX,
  SCF_SYNC,
  SCF_SHOW_TABLES,
  SCF_SHOW_INDEX,
  SCF_DESC_TABLE,
  SCF_BEGIN,
  SCF_COMMIT,
  SCF_CLOG_SYNC,
  SCF_ROLLBACK,
  SCF_LOAD_DATA,
  SCF_HELP,
  SCF_EXIT,
  SCF_INVALID_DATE
};
// struct of flag and sql_struct
typedef struct Query {
  enum SqlCommandFlag flag;
  union Queries sstr;
} Query;

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

void relation_attr_init(RelAttr *relation_attr, const char *relation_name, const char *attribute_name);
void relation_attr_destroy(RelAttr *relation_attr);

void value_init_integer(Value *value, int v);
void value_init_float(Value *value, float v);
void value_init_string(Value *value, const char *v);
int value_init_date(Value *value, const char *v);
void value_init_null(Value *value);
void value_destroy(Value *value);

void condition_init(Condition *condition, FilterType condition_type, CompOp comp, int left_is_attr, int left_is_sub_query, RelAttr *left_attr, Value *left_value, 
    Selects *left_select, int right_is_attr, int right_is_sub_query, int right_is_set, RelAttr *right_attr, Value *right_value, Selects *right_select, Value *value_set, 
    size_t value_set_num);

//***********************************************************func****************************************************************
void condition_init_func(Condition *condition, FilterType condition_type, CompOp comp, int left_is_attr, int left_is_sub_query, RelAttr *left_attr, Value *left_value, 
    Selects *left_select, int right_is_attr, int right_is_sub_query, int right_is_set, RelAttr *right_attr, Value *right_value, Selects *right_select, Value *value_set, 
    size_t value_set_num, FuncAttrCon* left_func_attr, FuncAttrCon* right_func_attr);
//***********************************************************func****************************************************************
void condition_destroy(Condition *condition);

void having_condition_init(Having_Condition *condition, AggregationOp aggr, CompOp cmpop, Value *value, RelAttr *attr);
void having_condition_destroy(Having_Condition *condition);

void attr_info_init(AttrInfo *attr_info, const char *name, AttrType type, size_t length, int is_nullable);
void attr_info_destroy(AttrInfo *attr_info);

void selects_init(Selects *selects, ...);
void selects_append_attribute(Selects *selects, RelAttr *rel_attr);
void selects_append_relation(Selects *selects, const char *relation_name, const char *relation_alias);
void selects_append_aggregation_op(Selects *selects, AggregationOp aggregation_op);
void selects_append_conditions(Selects *selects, Condition conditions[], size_t condition_num);
void selects_append_aggrattr(Selects *selects, RelAttr *rel_attr);
//******************************************func******************************************************
void selects_append_funcop(Selects *selects, FunctionOp function_op);
// first args
void selects_append_funcvalue1(Selects *selects, Value * value);
// second args
void selects_append_funcvalue2(Selects *selects, Value * value);

void selects_modify_alias_name(Selects *selects, char *attr_name);

char* value2string(Value * value);
//******************************************func******************************************************
void selects_append_orderattr(Selects *selects, RelAttr *rel_attr, int is_asc);
void selects_append_groupattr(Selects *selects, RelAttr *rel_attr);
void selects_append_havingcondition(Selects *selects, Having_Condition *condition); 
void selects_set_order(Selects *selects, int order);
void selects_set_group(Selects *selects, int group);
void selects_set_having(Selects *selects, int having);
void selects_destroy(Selects *selects);

// void inserts_init(Inserts *inserts, const char *relation_name, Value values[], size_t value_num);
void inserts_init(Inserts *inserts, const char *relation_name, Value tuples[][MAX_NUM], size_t tuple_num, size_t value_num[]);
void inserts_destroy(Inserts *inserts);

void deletes_init_relation(Deletes *deletes, const char *relation_name);
void deletes_set_conditions(Deletes *deletes, Condition conditions[], size_t condition_num);
void deletes_destroy(Deletes *deletes);

// void updates_init(Updates *updates, const char *relation_name, const char *attribute_name, Value *value,
//     Condition conditions[], size_t condition_num);

// ****************************************upselect****************************************
void updates_init(Updates *updates, const char *relation_name, const char *attribute_name[], Value *values, size_t values_num,
    Condition conditions[], size_t condition_num, Selects *select_vec[]);
// ****************************************upselect****************************************
void updates_destroy(Updates *updates);

void create_table_append_attribute(CreateTable *create_table, AttrInfo *attr_info);
void create_table_init_name(CreateTable *create_table, const char *relation_name);
void create_table_destroy(CreateTable *create_table);

void drop_table_init(DropTable *drop_table, const char *relation_name);
void drop_table_destroy(DropTable *drop_table);

void show_index_init(ShowIndex *show_index, const char *relation_name);
void show_index_destroy(ShowIndex *show_index);

void create_index_init(
    CreateIndex *create_index, const char *index_name, const char *relation_name, const char *attr_name, int is_unique);
void create_index_append_attribute(CreateIndex *create_index, const char *attr_name);
void create_index_destroy(CreateIndex *create_index);

void drop_index_init(DropIndex *drop_index, const char *index_name);
void drop_index_destroy(DropIndex *drop_index);

void desc_table_init(DescTable *desc_table, const char *relation_name);
void desc_table_destroy(DescTable *desc_table);

void load_data_init(LoadData *load_data, const char *relation_name, const char *file_name);
void load_data_destroy(LoadData *load_data);

void query_init(Query *query);
Query *query_create();  // create and init
void query_reset(Query *query);
void query_destroy(Query *query);  // reset and delete

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // __OBSERVER_SQL_PARSER_PARSE_DEFS_H__
