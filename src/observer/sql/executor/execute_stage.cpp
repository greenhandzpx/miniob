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
// Created by Meiyi & Longda on 2021/4/13.
//

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>

#include "execute_stage.h"


#include "common/io/io.h"
#include "common/log/log.h"
#include "common/lang/defer.h"
#include "common/seda/timer_stage.h"
#include "common/lang/string.h"
#include "rc.h"
#include "session/session.h"
#include "event/storage_event.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "sql/expr/tuple.h"
#include "sql/expr/tuple_cell.h"
#include "sql/operator/table_scan_operator.h"
#include "sql/operator/index_scan_operator.h"
#include "sql/operator/predicate_operator.h"
#include "sql/operator/delete_operator.h"
#include "sql/operator/project_operator.h"
#include "sql/operator/update_operator.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/update_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/common/table.h"
#include "storage/common/field.h"
#include "storage/index/index.h"
#include "storage/default/default_handler.h"
#include "storage/common/condition_filter.h"
#include "storage/trx/trx.h"
#include "storage/clog/clog.h"
#include "util/comparator.h"
#include "util/util.h"
using namespace common;

//RC create_selection_executor(
//   Trx *trx, const Selects &selects, const char *db, const char *table_name, SelectExeNode &select_node);

//! Constructor
ExecuteStage::ExecuteStage(const char *tag) : Stage(tag)
{}

//! Destructor
ExecuteStage::~ExecuteStage()
{}

//! Parse properties, instantiate a stage object
Stage *ExecuteStage::make_stage(const std::string &tag)
{
  ExecuteStage *stage = new (std::nothrow) ExecuteStage(tag.c_str());
  if (stage == nullptr) {
    LOG_ERROR("new ExecuteStage failed");
    return nullptr;
  }
  stage->set_properties();
  return stage;
}

//! Set properties for this object set in stage specific properties
bool ExecuteStage::set_properties()
{
  //  std::string stageNameStr(stageName);
  //  std::map<std::string, std::string> section = theGlobalProperties()->get(
  //    stageNameStr);
  //
  //  std::map<std::string, std::string>::iterator it;
  //
  //  std::string key;

  return true;
}

//! Initialize stage params and validate outputs
bool ExecuteStage::initialize()
{
  LOG_TRACE("Enter");

  std::list<Stage *>::iterator stgp = next_stage_list_.begin();
  default_storage_stage_ = *(stgp++);
  mem_storage_stage_ = *(stgp++);

  LOG_TRACE("Exit");
  return true;
}

//! Cleanup after disconnection
void ExecuteStage::cleanup()
{
  LOG_TRACE("Enter");

  LOG_TRACE("Exit");
}

void ExecuteStage::handle_event(StageEvent *event)
{
  LOG_TRACE("Enter\n");

  handle_request(event);

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::callback_event(StageEvent *event, CallbackContext *context)
{
  LOG_TRACE("Enter\n");

  // here finish read all data from disk or network, but do nothing here.

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::handle_request(common::StageEvent *event)
{
  SQLStageEvent *sql_event = static_cast<SQLStageEvent *>(event);
  SessionEvent *session_event = sql_event->session_event();
  Stmt *stmt = sql_event->stmt();
  Session *session = session_event->session();
  Query *sql = sql_event->query();

  if (stmt != nullptr) {
    switch (stmt->type()) {
    case StmtType::SELECT: {
      do_select(sql_event);
    } break;
    case StmtType::INSERT: {
      do_insert(sql_event);
    } break;
    case StmtType::UPDATE: {
      //do_update((UpdateStmt *)stmt, session_event);
      do_update(sql_event);
    } break;
    case StmtType::DELETE: {
      do_delete(sql_event);
    } break;
    default: {
      LOG_WARN("should not happen. please implenment");
    } break;
    }
  } else {
    switch (sql->flag) {
    case SCF_HELP: {
      do_help(sql_event);
    } break;
    case SCF_CREATE_TABLE: {
      do_create_table(sql_event);
    } break;
    case SCF_CREATE_INDEX: {
      do_create_index(sql_event);
    } break;
    case SCF_SHOW_TABLES: {
      do_show_tables(sql_event);
    } break;
    case SCF_DESC_TABLE: {
      do_desc_table(sql_event);
    } break;
    case SCF_SHOW_INDEX: {
      do_show_index(sql_event);
    } break;

    case SCF_DROP_TABLE:
    case SCF_DROP_INDEX:
    case SCF_LOAD_DATA: {
      default_storage_stage_->handle_event(event);
    } break;
    case SCF_SYNC: {
      /*
      RC rc = DefaultHandler::get_default().sync();
      session_event->set_response(strrc(rc));
      */
    } break;
    case SCF_BEGIN: {
      do_begin(sql_event);
      /*
      session_event->set_response("SUCCESS\n");
      */
    } break;
    case SCF_COMMIT: {
      do_commit(sql_event);
      /*
      Trx *trx = session->current_trx();
      RC rc = trx->commit();
      session->set_trx_multi_operation_mode(false);
      session_event->set_response(strrc(rc));
      */
    } break;
    case SCF_CLOG_SYNC: {
      do_clog_sync(sql_event);
    }
    case SCF_ROLLBACK: {
      Trx *trx = session_event->get_client()->session->current_trx();
      RC rc = trx->rollback();
      session->set_trx_multi_operation_mode(false);
      session_event->set_response(strrc(rc));
    } break;
    case SCF_EXIT: {
      // do nothing
      const char *response = "Unsupported\n";
      session_event->set_response(response);
    } break;
    default: {
      LOG_ERROR("Unsupported command=%d\n", sql->flag);
    }
    }
  }
}

void end_trx_if_need(Session *session, Trx *trx, bool all_right)
{
  if (!session->is_trx_multi_operation_mode()) {
    if (all_right) {
      trx->commit();
    } else {
      trx->rollback();
    }
  }
}

void print_aggregation_header(std::ostream &os, SelectStmt *select_stmt) {
  auto query_field = select_stmt->query_fields();
  auto aggregation_ops = select_stmt->aggregation_ops();
  auto aggregation_alias = select_stmt->aggregation_alias();

  auto aggrops_idx_in_fields = select_stmt->arggrops_idx_in_fields();
  auto sum = aggregation_ops.size() + query_field.size();
  int querycnt = 0, aggropscnt = 0;
  for (int i = 0; i < sum; ++i) {
    while (i < aggrops_idx_in_fields[aggropscnt]) {
      if (i != 0) {
        os << " | ";
      }
      if (select_stmt->tables().size() != 1) {
        os << query_field[querycnt].table_name() << ".";
      }
      os << query_field[querycnt].field_name();
      querycnt++;
      ++i;
    }
    AggregationOp aggregation_op = aggregation_ops[aggropscnt];
    char * alias = aggregation_alias[aggropscnt];
    if (i != 0) {
      os << " | ";
    }
    if (alias) {
      os << alias;
      aggropscnt++;
      continue;
    }
    switch (aggregation_op) {
      case COUNT_OP: {
        os << "COUNT(";
      } break;
      case AVG_OP: {
        os << "AVG(";
      } break;
      case SUM_OP: {
        os << "SUM(";
      } break;
      case MAX_OP: {
        os << "MAX(";
      } break;
      case MIN_OP: {
        os << "MIN(";
      } break;
      default: break;
    }
    size_t n = select_stmt->aggr_fields().size();
    printf("n : %zu\n", n);
    if (select_stmt->tables().size() != 1) {
        os << select_stmt->aggr_fields()[n-aggropscnt-1].table_name() << ".";
    }
    if (select_stmt->aggr_fields()[n-aggropscnt-1].meta() == nullptr) {
      os << "*)";
    } else {
      os << select_stmt->aggr_fields()[n-aggropscnt-1].meta()->name() << ")";
    }
    aggropscnt++;
  }
  os << '\n';
}

void res_print_tuple_header(std::ostream &os, const ProjectOperator &oper)
{
  const int cell_num = oper.tuple_cell_num();
  const TupleCellSpec *cell_spec = nullptr;
  for (int i = 0; i < cell_num; i++) {
    oper.tuple_cell_spec_at(cell_num - 1 - i, cell_spec);
    if (i != 0) {
      os << " | ";
    }

    if (cell_spec->alias()) {
      os << cell_spec->alias();
    }
  }

  if (cell_num > 0) {
    os << '\n';
  }
}

void print_tuple_header(std::ostream &os, const ProjectOperator &oper)
{
  const int cell_num = oper.tuple_cell_num();
  const TupleCellSpec *cell_spec = nullptr;
  for (int i = 0; i < cell_num; i++) {
    oper.tuple_cell_spec_at(i, cell_spec);
    if (i != 0) {
      os << " | ";
    }

    if (cell_spec->alias()) {
      os << cell_spec->alias();
    }
  }

  if (cell_num > 0) {
    os << '\n';
  }
}

void tuple_to_string(std::ostream &os, const Tuple &tuple)
{
  TupleCell cell;
  RC rc = RC::SUCCESS;
  bool first_field = true;
  for (int i = 0; i < tuple.cell_num(); i++) {
    rc = tuple.cell_at(i, cell);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to fetch field of cell. index=%d, rc=%s", i, strrc(rc));
      break;
    }

    if (!first_field) {
      os << " | ";
    } else {
      first_field = false;
    }
    cell.to_string(os);
  }
}

void value_to_string(std::ostream &os, Value *values, int length)
{
  bool first_field = true;
  for (int i = length - 1; i >= 0; i--) {
    Value v = values[i];

    if (!first_field) {
      os << " | ";
    } else {
      first_field = false;
    }
    
    switch (v.type) {
      case INTS: {
        os << *(int *)v.data;
      } break;
      case DATES: {
        int value = *(int*)v.data;
        char buf[16] = {0};
        snprintf(buf,sizeof(buf),"%04d-%02d-%02d",value/10000,    (value%10000)/100,value%100); // 注意这里月份和天数，不足两位时需要填充0
        os << buf;
      } break;
      case FLOATS: {
        float f = *(float*)v.data;
        os << double2string(f);
      } break;
      case CHARS: {
        for (int i = 0; ((char*)v.data)[i] != '\0'; i++) {
          os << ((char*)v.data)[i];
        }
      } break;
      
      default: {
        LOG_WARN("unsupported attr type: %d", v.type);
      } break;
    }

  }
}

IndexScanOperator *ExecuteStage::try_to_create_index_scan_operator(FilterStmt *filter_stmt)
{
  const std::vector<FilterUnit *> &filter_units = filter_stmt->filter_units();
  if (filter_units.empty() ) {
    return nullptr;
  }

  // 在所有过滤条件中，找到字段与值做比较的条件，然后判断字段是否可以使用索引
  // 如果是多列索引，这里的处理需要更复杂。
  // 这里的查找规则是比较简单的，就是尽量找到使用相等比较的索引
  // 如果没有就找范围比较的，但是直接排除不等比较的索引查询. (你知道为什么?)
  const FilterUnit *better_filter = nullptr;
  for (const FilterUnit * filter_unit : filter_units) {
    if (filter_unit->get_type() != Comparison) {
      // TODO: optimize
      continue;
    }
    if (filter_unit->comp() == NOT_EQUAL || filter_unit->comp() == LOGICAL_IS_NOT || filter_unit->comp() == LOGICAL_IS) {
      continue;
    }

    // **************************like***********************************
    // puzzy query should not use index to search
    if (filter_unit->comp() == LIKE_OP || filter_unit->comp() == NOT_LIKE_OP) {
      continue;
    }
    // **************************like***************************

    Expression *left = filter_unit->left();
    Expression *right = filter_unit->right();

    // **************************typecast***********************************
    //value和value比较不应该走索引

    if (left->type() == ExprType::VALUE && right->type() == ExprType::VALUE) {
      continue;
    }
    // **************************typecast***************************


    bool can_find_by_index = false;
    if (left->type() == ExprType::FIELD && right->type() == ExprType::VALUE) {
      can_find_by_index = true;
    } else if (left->type() == ExprType::VALUE && right->type() == ExprType::FIELD) {
      std::swap(left, right);
      can_find_by_index = true;
    }
    if (!can_find_by_index) {
      continue;
    }
    FieldExpr &left_field_expr = *(FieldExpr *)left;
    const Field &field = left_field_expr.field();
    const Table *table = field.table();
    Index *index = table->find_index_by_field(field.field_name());
    if (index != nullptr) {
      if (better_filter == nullptr) {
        better_filter = filter_unit;
      } else if (filter_unit->comp() == EQUAL_TO) {
        better_filter = filter_unit;
    	  break;
      }
    }
  }

  if (better_filter == nullptr) {
    return nullptr;
  }

  Expression *left = better_filter->left();
  Expression *right = better_filter->right();
  CompOp comp = better_filter->comp();
  if (left->type() == ExprType::VALUE && right->type() == ExprType::FIELD) {
    std::swap(left, right);
    switch (comp) {
    case EQUAL_TO:    { comp = EQUAL_TO; }    break;
    case LESS_EQUAL:  { comp = GREAT_THAN; }  break;
    case NOT_EQUAL:   { comp = NOT_EQUAL; }   break;
    case LESS_THAN:   { comp = GREAT_EQUAL; } break;
    case GREAT_EQUAL: { comp = LESS_THAN; }   break;
    case GREAT_THAN:  { comp = LESS_EQUAL; }  break;
    case LOGICAL_IS_NOT :     {comp = LOGICAL_IS_NOT;} break;
    case LOGICAL_IS :     {comp = LOGICAL_IS;} break;
    default: {
    	LOG_WARN("should not happen");
    }
    }
  }


  FieldExpr &left_field_expr = *(FieldExpr *)left;
  const Field &field = left_field_expr.field();
  const Table *table = field.table();
  Index *index = table->find_index_by_field(field.field_name());
  assert(index != nullptr);

  ValueExpr &right_value_expr = *(ValueExpr *)right;
  TupleCell value;
  right_value_expr.get_tuple_cell(value);

  const TupleCell *left_cell = nullptr;
  const TupleCell *right_cell = nullptr;
  bool left_inclusive = false;
  bool right_inclusive = false;

  switch (comp) {
  case EQUAL_TO: {
    left_cell = &value;
    right_cell = &value;
    left_inclusive = true;
    right_inclusive = true;
  } break;

  case LESS_EQUAL: {
    left_cell = nullptr;
    left_inclusive = false;
    right_cell = &value;
    right_inclusive = true;
  } break;

  case LESS_THAN: {
    left_cell = nullptr;
    left_inclusive = false;
    right_cell = &value;
    right_inclusive = false;
  } break;

  case GREAT_EQUAL: {
    left_cell = &value;
    left_inclusive = true;
    right_cell = nullptr;
    right_inclusive = false;
  } break;

  case GREAT_THAN: {
    left_cell = &value;
    left_inclusive = false;
    right_cell = nullptr;
    right_inclusive = false;
  } break;

  default: {
    LOG_WARN("should not happen. comp=%d", comp);
  } break;
  }

  IndexScanOperator *oper = new IndexScanOperator(table, index,
       left_cell, left_inclusive, right_cell, right_inclusive);

  LOG_INFO("use index for scan: %s in table %s", index->index_meta().name(), table->name());
  return oper;
}

RC ExecuteStage::normal_select_handler(SelectStmt *select_stmt, Tuple *&tuple, ProjectOperator &project_oper) {

  RC rc;

  if ((rc = project_oper.next()) == RC::SUCCESS) {
    tuple = project_oper.current_tuple();


    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get current record. rc=%s", strrc(rc));
    } 
    
  } else if (rc == RC::RECORD_EOF) {
    project_oper.close();
  } else {
    LOG_WARN("something wrong while iterate operator. rc=%s", strrc(rc));
    project_oper.close();
  }
  return rc;
}

RC ExecuteStage::aggregation_select_handler(SelectStmt *select_stmt, std::vector<Value> &values, ProjectOperator &project_oper) {

  RC rc;

  auto aggregation_ops = select_stmt->aggregation_ops();  

  printf("aggregation op size %d, values size %d\n", aggregation_ops.size(), values.size());

  for (size_t i = 0; i < values.size(); ++i) {
    if (aggregation_ops[i] == COUNT_OP) {
      values[i].type = AttrType::INTS;
      values[i].data = new int;
      *static_cast<int*>(values[i].data) = 0;

    } else if (aggregation_ops[i] == AVG_OP || aggregation_ops[i] == SUM_OP){
      values[i].type = AttrType::FLOATS;
      values[i].data = nullptr;
      // values[i].data = new float;
      // *static_cast<float*>(values[i].data) = 0;

    } else {
      size_t n = select_stmt->aggr_fields().size();
      if (i >= select_stmt->aggr_fields().size()) {
        LOG_ERROR("aggregation: field count doesn't match the op count");
        return RC::MISMATCH;
      }
      switch (select_stmt->aggr_fields()[n-i-1].attr_type()) {
        case AttrType::FLOATS: {
          values[i].type = AttrType::FLOATS;
          values[i].data = nullptr;
          // values[i].data = new float; 
          // if (aggregation_ops[i] == MAX_OP) {
          //   *static_cast<float*>(values[i].data) = std::numeric_limits<float>::min();
          // } else if (aggregation_ops[i] == MIN_OP) {
          //   *static_cast<float*>(values[i].data) = std::numeric_limits<float>::max();
          // } else {
          //   *static_cast<float*>(values[i].data) = 0;
          // }
        }
        break;
        case AttrType::DATES: {
          values[i].type = AttrType::DATES;
          values[i].data = nullptr;
        } break;
        case AttrType::INTS: {
          values[i].type = AttrType::INTS;
          values[i].data = nullptr;
          // values[i].data = new int; 
          // if (aggregation_ops[i] == MAX_OP) {
          //   *static_cast<int*>(values[i].data) = std::numeric_limits<int>::min();
          // } else if (aggregation_ops[i] == MIN_OP) {
          //   *static_cast<int*>(values[i].data) = std::numeric_limits<int>::max();
          // } else {
          //   *static_cast<int*>(values[i].data) = 0;
          // }
        }
        break;
        // case AttrType::DATES:  ; // TODO
        // case AttrType::CHARS:  ; // TODO
        case AttrType::CHARS: {
          values[i].type = AttrType::CHARS;
          values[i].data = nullptr;
        } 
        break;
        default: {
          LOG_WARN("undefined value type");
          return RC::GENERIC_ERROR;
        }
      }
    }
  }

  std::vector<int> divs(aggregation_ops.size());
  while ((rc = project_oper.next()) == RC::SUCCESS) {
    // get current record
    // write to response
    Tuple * tuple = project_oper.current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get current record. rc=%s", strrc(rc));
      break;
    }

    for (int i = 0; i < aggregation_ops.size(); ++i) {
      TupleCell cell;

      size_t n = select_stmt->aggr_fields().size();
      if (select_stmt->aggr_fields()[n-i-1].meta() != nullptr && tuple->find_cell(select_stmt->aggr_fields()[n-i-1], cell) != RC::SUCCESS) {
        LOG_WARN("cannot get the cell value");
        break;
      }

      if (cell.attr_type() == AttrType::NULLS) {
        continue;
      }
      divs[i]++;

      AggregationOp aggregation_op = aggregation_ops[i];
      switch (aggregation_op) {
        case COUNT_OP: {
          // if (cell.attr_type() != AttrType::NULLS) {
            *static_cast<int *>(values[i].data) += 1;
          // }
        } break;

        case SUM_OP:
        case AVG_OP: {
          // if (values[i].data == nullptr && cell.attr_type() != AttrType::NULLS) {
          if (values[i].data == nullptr) {
            values[i].data = new float(0);
          }
          if (cell.attr_type() == AttrType::INTS) {
            *static_cast<float*>(values[i].data) += *reinterpret_cast<const int*>(cell.data());
          } else if (cell.attr_type() == AttrType::FLOATS) {
            *static_cast<float*>(values[i].data) += *reinterpret_cast<const float*>(cell.data());
          } else if (cell.attr_type() == AttrType::CHARS) {
            float tmp;
            string2float(cell.data(), &tmp);
            *static_cast<float*>(values[i].data) += tmp;
          // } else if (cell.attr_type() != AttrType::NULLS) {
          } else {
            LOG_WARN("unsupported attr type");
            return RC::SCHEMA_FIELD_NAME_ILLEGAL;
          }
        } break;

        case MAX_OP: {
          if (cell.attr_type() == AttrType::INTS || cell.attr_type() == AttrType::DATES) {
            if (values[i].data == nullptr) {
              // first time
              values[i].data = new int(*(int *)cell.data());
            } else {
              if (compare_int((void *)cell.data(), values[i].data) > 0) {
                *static_cast<int*>(values[i].data) = *reinterpret_cast<const int *>(cell.data());
              }
            }
          } else if (cell.attr_type() == AttrType::FLOATS) {
            if (values[i].data == nullptr) {
              // first time
              values[i].data = new float(*(float *)cell.data());
            } else {
              if (compare_float((void *)cell.data(), values[i].data) > 0) {
                *static_cast<float*>(values[i].data) = *reinterpret_cast<const float *>(cell.data());
              }
            }
          } else if (cell.attr_type() == AttrType::CHARS) {
            if (values[i].data == nullptr) {
              values[i].data = strdup(cell.data());
            } else if (compare_string(values[i].data, strlen((const char*)(values[i].data)), (void*)cell.data(), strlen((cell.data()))) < 0) {
              // TODO: memory leak
              values[i].data = strdup(cell.data());
            }
          }
        } break;
        
        case MIN_OP: {
          if (cell.attr_type() == AttrType::INTS || cell.attr_type() == AttrType::DATES) {
            if (values[i].data == nullptr) {
              // first time
              values[i].data = new int(*(int *)cell.data());
            } else {
              if (compare_int(values[i].data, (void *)cell.data()) > 0) {
                *static_cast<int*>(values[i].data) = *reinterpret_cast<const int *>(cell.data());
              }
            }
          } else if (cell.attr_type() == AttrType::FLOATS) {
            if (values[i].data == nullptr) {
              // first time
              values[i].data = new float(*(float *)cell.data());
            } else {
              if (compare_float(values[i].data, (void *)cell.data()) > 0) {
                *static_cast<float*>(values[i].data) = *reinterpret_cast<const float *>(cell.data());
              }
            }
          } else if (cell.attr_type() == AttrType::CHARS) {
            if (values[i].data == nullptr) {
              values[i].data = strdup(cell.data());
            } else if (compare_string(values[i].data, strlen((const char*)(values[i].data)), (void*)cell.data(), strlen((cell.data()))) > 0) {
              values[i].data = strdup(cell.data());
            }
          }

        } break;
        default: {
          LOG_WARN("unsupported aggregation op");
          return RC::GENERIC_ERROR;
        }
      }
    }
  }

  if (rc != RC::RECORD_EOF) {
    LOG_WARN("something wrong while iterate operator. rc=%s", strrc(rc));
    project_oper.close();
  } else {
    rc = project_oper.close();
  }

  for (int i = 0; i < values.size(); ++i) {
    if (values[i].data == nullptr) {
      values[i].type = AttrType::NULLS;
      continue;
    }
    if (aggregation_ops[i] == AVG_OP) {
        if (values[i].type == AttrType::INTS) {
          *static_cast<float*>(values[i].data) /= divs[i];
        } else if (values[i].type == AttrType::FLOATS) {
          *static_cast<float*>(values[i].data) /= divs[i];
        } else {
          LOG_WARN("unsupported attr type");
          return RC::SCHEMA_FIELD_NAME_ILLEGAL;
        }
    }
  }


  return rc;
}

RC ExecuteStage::group_select_handler(SelectStmt *select_stmt, std::vector<std::vector<Value>> &values, ProjectOperator &project_oper) {
  RC rc;

  auto aggregation_ops = select_stmt->aggregation_ops();
  auto query_fields = select_stmt->query_fields();
  auto aggr_fields = select_stmt->aggr_fields();
  auto group_fields = select_stmt->group_fields();
  auto aggr_idxs = select_stmt->arggrops_idx_in_fields();
  auto query_size = query_fields.size();
  auto aggr_size = aggr_fields.size();
  auto group_size = group_fields.size();
  auto having_fields = select_stmt->having_fields();
  auto having_size = having_fields.size();
  auto having_filters = select_stmt->having_filters();
  auto having_ops = select_stmt->having_ops();
  std::vector<GroupKey> groups;
  std::vector<std::vector<Value>> having_values;
  // 分组,同时初始化values数组
  while ((rc = project_oper.next()) == RC::SUCCESS) {
    Tuple *tuple = project_oper.current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get current record. rc = %s", strrc(rc));
      return rc;
    }
    std::vector<TupleCell> group;
    group.resize(group_size);
    for (int c = 0; c < group_size; ++c) {
      TupleCell cell;
      if (group_fields[group_size - c - 1].meta() != nullptr && tuple->find_cell(group_fields[group_size - c -1], cell) != RC::SUCCESS) {
        LOG_WARN("cannot get the cell value\n");
        return RC::INTERNAL;
      }
      group[c] = cell;
    }
    GroupKey key(group);
    if (std::find(groups.begin(), groups.end(), key) == groups.end()) {
      groups.push_back(key);
      std::vector<Value> vals;
      int queryfieldcnt = 0, aggrfieldcnt = 0;
      for (int c = 0; c < query_size + aggr_size; ++c) {
        TupleCell cell;
        while (c < aggr_idxs[aggrfieldcnt]) {
          Value v;
          if (query_fields[queryfieldcnt].meta() != nullptr && tuple->find_cell(query_fields[queryfieldcnt], cell) != RC::SUCCESS) {
            LOG_WARN("cannot get the cell value\n");
            break;
          }
          v.type = cell.attr_type();
          if (v.type != AttrType::NULLS) {
            v.data = (void *)malloc(cell.length());
            memcpy(v.data, cell.data(), cell.length());
          }
          vals.push_back(v);
          ++queryfieldcnt;
          ++c;
        }
        if (aggr_fields[aggr_size - aggrfieldcnt - 1].meta() != nullptr && tuple->find_cell(aggr_fields[aggr_size - aggrfieldcnt - 1], cell) != RC::SUCCESS) {
          LOG_WARN("cannot get the cell value");
          break;
        }
        Value aggrv;
        if (aggregation_ops[aggrfieldcnt] == COUNT_OP) {
          aggrv.type = INTS;
          aggrv.data = new int;
          *static_cast<int *>(aggrv.data) = 0;
        } else if (aggregation_ops[aggrfieldcnt] == SUM_OP || aggregation_ops[aggrfieldcnt] == AVG_OP) {
          aggrv.type = FLOATS;
          aggrv.data = nullptr;
        } else {
          aggrv.type = aggr_fields[aggr_size - aggrfieldcnt -1].attr_type();
          aggrv.data = nullptr;
        }
        vals.push_back(aggrv);
        aggrfieldcnt++;
      }
      values.push_back(vals);

      // having 操作
      std::vector<Value> having_vals;
      for (int i = 0; i < having_size; ++i) {
        TupleCell cell;
        if (having_fields[having_size-i-1].meta() != nullptr && tuple->find_cell(having_fields[having_size-i-1], cell) != RC::SUCCESS) {
          LOG_WARN("cannot get the cell value");
          break;
        }
        Value having_v;
        if (having_ops[i] == COUNT_OP) {
          having_v.type = INTS;
          having_v.data = new int;
          *static_cast<int *>(having_v.data) = 0;
        } else if (having_ops[i] == SUM_OP || having_ops[i] == AVG_OP) {
          having_v.type = FLOATS;
          having_v.data = nullptr;
        } else {
          having_v.type = having_fields[having_size-i-1].attr_type();
          having_v.data = nullptr;
        }
        having_vals.push_back(having_v);
      }
      having_values.push_back(having_vals);


    }
  }
  if (rc != RC::RECORD_EOF) {
    LOG_WARN("something wrong while iterate operator. rc=%s", strrc(rc));
    project_oper.close();
  } else {
    rc = project_oper.close();
  }

  // 妈妈的直接再建一次 project_oper1再扫一次

  PredicateOperator pred_oper(select_stmt->filter_stmt());
  std::vector<Operator *> scan_opers(select_stmt->tables().size());
  for (int i = 0; i < scan_opers.size(); ++i) {
    printf("add scan oper %d\n", i);
    scan_opers[i] = try_to_create_index_scan_operator(select_stmt->filter_stmt());
    
    if (nullptr == scan_opers[i]) {
      // TODO memory leak
      scan_opers[i] = new TableScanOperator(select_stmt->tables()[i]);
    }
    pred_oper.add_child(scan_opers[i]);
  }
  ProjectOperator project_oper1;
  project_oper1.add_child(&pred_oper);
  bool is_single_table = select_stmt->tables().size() == 1;
  for (const Field &field : select_stmt->query_fields()) {
    if (field.meta() == nullptr) {
      continue;
    }
    project_oper1.add_projection(field.table(), field.meta(), is_single_table);
  }
  for (const Field &field : select_stmt->aggr_fields()) {
    if (field.meta() == nullptr) {
      continue;
    }
    project_oper.add_projection(field.table(), field.meta(), is_single_table);
  }
  for (const Field &field : select_stmt->having_fields()) {
    if (field.meta() == nullptr) {
      continue;
    }
    project_oper.add_projection(field.table(), field.meta(), is_single_table);
  }
  std::vector<std::vector<size_t>> having_divs(having_values.size(), std::vector<size_t>(having_ops.size()));
  std::vector<std::vector<int>> divs(groups.size(), std::vector<int>(aggr_size, 0));
  // 开始扫描运算
  rc = project_oper1.open();
  while ((rc = project_oper1.next()) == RC::SUCCESS) {
    Tuple *tuple = project_oper1.current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get current record. rc = %s", strrc(rc));
      return rc;
    }

    std::vector<TupleCell> group;
    group.resize(group_size);
    for (int c = 0; c < group_size; ++c) {
      TupleCell cell;
      if (group_fields[group_size - c - 1].meta() != nullptr && tuple->find_cell(group_fields[group_size - c -1], cell) != RC::SUCCESS) {
        LOG_WARN("cannot get the cell value\n");
        return RC::INTERNAL;
      }
      group[c] = cell;
    }
    GroupKey key(group);
    
    auto it = std::find(groups.begin(), groups.end(), key);
    if (it != groups.end()) {
      int groupid = it - groups.begin();
      for (int i = 0; i < aggr_size; i++) {
        TupleCell tuplecell;
        int idx = aggr_idxs[i];
        if (aggr_fields[aggr_size - i - 1].meta() != nullptr && tuple->find_cell(aggr_fields[aggr_size - i - 1], tuplecell) != RC::SUCCESS) {
          LOG_WARN("cannot get the cell value");
          return RC::INTERNAL;
        }
        if (tuplecell.attr_type() == AttrType::NULLS) {
          continue;
        }
        divs[groupid][i] ++;
        switch (aggregation_ops[i]) {
          case COUNT_OP: {
            // if (cell.attr_type() != AttrType::NULLS) {
              *static_cast<int *>(values[groupid][idx].data) += 1;
            // }
          } break;

          case SUM_OP:
          case AVG_OP: {
            // if (values[i].data == nullptr && cell.attr_type() != AttrType::NULLS) {
            if (values[groupid][idx].data == nullptr) {
              values[groupid][idx].data = new float(0);
            }
            if (tuplecell.attr_type() == AttrType::INTS) {
              *static_cast<float*>(values[groupid][idx].data) += *reinterpret_cast<const int*>(tuplecell.data());
            } else if (tuplecell.attr_type() == AttrType::FLOATS) {
              *static_cast<float*>(values[groupid][idx].data) += *reinterpret_cast<const float*>(tuplecell.data());
            } else if (tuplecell.attr_type() == AttrType::CHARS) {
              float tmp;
              string2float(tuplecell.data(), &tmp);
              *static_cast<float*>(values[groupid][idx].data) += tmp;
            // } else if (cell.attr_type() != AttrType::NULLS) {
            } else {
              LOG_WARN("unsupported attr type");
              return RC::SCHEMA_FIELD_NAME_ILLEGAL;
            }
          } break;

          case MAX_OP: {
            if (tuplecell.attr_type() == AttrType::INTS || tuplecell.attr_type() == AttrType::DATES) {
              if (values[groupid][idx].data == nullptr) {
                // first time
                values[groupid][idx].data = new int(*(int *)tuplecell.data());
              } else {
                if (compare_int((void *)tuplecell.data(), values[groupid][idx].data) > 0) {
                  *static_cast<int*>(values[groupid][idx].data) = *reinterpret_cast<const int *>(tuplecell.data());
                }
              }
            } else if (tuplecell.attr_type() == AttrType::FLOATS) {
              if (values[groupid][idx].data == nullptr) {
                // first time
                values[groupid][idx].data = new float(*(float *)tuplecell.data());
              } else {
                if (compare_float((void *)tuplecell.data(), values[groupid][idx].data) > 0) {
                  *static_cast<float*>(values[groupid][idx].data) = *reinterpret_cast<const float *>(tuplecell.data());
                }
              }
            } else if (tuplecell.attr_type() == AttrType::CHARS) {
              if (values[groupid][idx].data == nullptr) {
                values[groupid][idx].data = strdup(tuplecell.data());
              } else if (compare_string(values[groupid][idx].data, strlen((const char*)(values[groupid][idx].data)), (void*)tuplecell.data(), strlen((tuplecell.data()))) < 0) {
                // TODO: memory leak
                values[groupid][idx].data = strdup(tuplecell.data());
              }
            }
          } break;
          
          case MIN_OP: {
            if (tuplecell.attr_type() == AttrType::INTS || tuplecell.attr_type() == AttrType::DATES) {
              if (values[groupid][idx].data == nullptr) {
                // first time
                values[groupid][idx].data = new int(*(int *)tuplecell.data());
              } else {
                if (compare_int(values[groupid][idx].data, (void *)tuplecell.data()) > 0) {
                  *static_cast<int*>(values[groupid][idx].data) = *reinterpret_cast<const int *>(tuplecell.data());
                }
              }
            } else if (tuplecell.attr_type() == AttrType::FLOATS) {
              if (values[groupid][idx].data == nullptr) {
                // first time
                values[groupid][idx].data = new float(*(float *)tuplecell.data());
              } else {
                if (compare_float(values[groupid][idx].data, (void *)tuplecell.data()) > 0) {
                  *static_cast<float*>(values[groupid][idx].data) = *reinterpret_cast<const float *>(tuplecell.data());
                }
              }
            } else if (tuplecell.attr_type() == AttrType::CHARS) {
              if (values[groupid][idx].data == nullptr) {
                values[groupid][idx].data = strdup(tuplecell.data());
              } else if (compare_string(values[groupid][idx].data, strlen((const char*)(values[groupid][idx].data)), (void*)tuplecell.data(), strlen((tuplecell.data()))) > 0) {
                values[groupid][idx].data = strdup(tuplecell.data());
              }
            }

          } break;
          default: {
            LOG_WARN("unsupported aggregation op");
            return RC::GENERIC_ERROR;
          }
        }
      }
      for (int i = 0; i < having_size; i++) {
        TupleCell tuplecell;
        if (having_fields[having_size - i - 1].meta() != nullptr && tuple->find_cell(having_fields[having_size - i - 1], tuplecell) != RC::SUCCESS) {
          LOG_WARN("cannot get the cell value");
          return RC::INTERNAL;
        }
        if (tuplecell.attr_type() == AttrType::NULLS) {
          continue;
        }
        having_divs[groupid][i]++;
        switch (having_ops[i]) {
          case COUNT_OP: {
            // if (cell.attr_type() != AttrType::NULLS) {
              *static_cast<int *>(having_values[groupid][i].data) += 1;
            // }
          } break;

          case SUM_OP:
          case AVG_OP: {
            // if (values[i].data == nullptr && cell.attr_type() != AttrType::NULLS) {
            if (having_values[groupid][i].data == nullptr) {
              having_values[groupid][i].data = new float(0);
            }
            if (tuplecell.attr_type() == AttrType::INTS) {
              *static_cast<float*>(having_values[groupid][i].data) += *reinterpret_cast<const int*>(tuplecell.data());
            } else if (tuplecell.attr_type() == AttrType::FLOATS) {
              *static_cast<float*>(having_values[groupid][i].data) += *reinterpret_cast<const float*>(tuplecell.data());
            } else if (tuplecell.attr_type() == AttrType::CHARS) {
              float tmp;
              string2float(tuplecell.data(), &tmp);
              *static_cast<float*>(having_values[groupid][i].data) += tmp;
            // } else if (cell.attr_type() != AttrType::NULLS) {
            } else {
              LOG_WARN("unsupported attr type");
              return RC::SCHEMA_FIELD_NAME_ILLEGAL;
            }
          } break;

          case MAX_OP: {
            if (tuplecell.attr_type() == AttrType::INTS || tuplecell.attr_type() == AttrType::DATES) {
              if (having_values[groupid][i].data == nullptr) {
                // first time
                having_values[groupid][i].data = new int(*(int *)tuplecell.data());
              } else {
                if (compare_int((void *)tuplecell.data(), having_values[groupid][i].data) > 0) {
                  *static_cast<int*>(having_values[groupid][i].data) = *reinterpret_cast<const int *>(tuplecell.data());
                }
              }
            } else if (tuplecell.attr_type() == AttrType::FLOATS) {
              if (having_values[groupid][i].data == nullptr) {
                // first time
                having_values[groupid][i].data = new float(*(float *)tuplecell.data());
              } else {
                if (compare_float((void *)tuplecell.data(), having_values[groupid][i].data) > 0) {
                  *static_cast<float*>(having_values[groupid][i].data) = *reinterpret_cast<const float *>(tuplecell.data());
                }
              }
            } else if (tuplecell.attr_type() == AttrType::CHARS) {
              if (having_values[groupid][i].data == nullptr) {
                having_values[groupid][i].data = strdup(tuplecell.data());
              } else if (compare_string(having_values[groupid][i].data, strlen((const char*)(having_values[groupid][i].data)), (void*)tuplecell.data(), strlen((tuplecell.data()))) < 0) {
                // TODO: memory leak
                having_values[groupid][i].data = strdup(tuplecell.data());
              }
            }
          } break;
          
          case MIN_OP: {
            if (tuplecell.attr_type() == AttrType::INTS || tuplecell.attr_type() == AttrType::DATES) {
              if (having_values[groupid][i].data == nullptr) {
                // first time
                having_values[groupid][i].data = new int(*(int *)tuplecell.data());
              } else {
                if (compare_int(having_values[groupid][i].data, (void *)tuplecell.data()) > 0) {
                  *static_cast<int*>(having_values[groupid][i].data) = *reinterpret_cast<const int *>(tuplecell.data());
                }
              }
            } else if (tuplecell.attr_type() == AttrType::FLOATS) {
              if (having_values[groupid][i].data == nullptr) {
                // first time
                having_values[groupid][i].data = new float(*(float *)tuplecell.data());
              } else {
                if (compare_float(having_values[groupid][i].data, (void *)tuplecell.data()) > 0) {
                  *static_cast<float*>(having_values[groupid][i].data) = *reinterpret_cast<const float *>(tuplecell.data());
                }
              }
            } else if (tuplecell.attr_type() == AttrType::CHARS) {
              if (having_values[groupid][i].data == nullptr) {
                having_values[groupid][i].data = strdup(tuplecell.data());
              } else if (compare_string(having_values[groupid][i].data, strlen((const char*)(having_values[groupid][i].data)), (void*)tuplecell.data(), strlen((tuplecell.data()))) > 0) {
                having_values[groupid][i].data = strdup(tuplecell.data());
              }
            }

          } break;
          default: {
            LOG_WARN("unsupported aggregation op");
            return RC::GENERIC_ERROR;
          }
        }
      }
    }
  }
  if (rc != RC::RECORD_EOF) {
    LOG_WARN("something wrong while iterate operator. rc=%s", strrc(rc));
    project_oper1.close();
  } else {
    rc = project_oper1.close();
  }
  int gid = 0;
  for (auto vs : values) {
    for (int i = 0; i < aggr_size; ++i) {
      int idx = aggr_idxs[i];
      if (vs[idx].data == nullptr) {
        vs[idx].type = AttrType::NULLS;
        continue;
      }
      if (aggregation_ops[i] == AVG_OP) {
        if (vs[idx].type == AttrType::INTS) {
          *static_cast<float*>(vs[idx].data) /= divs[gid][i];
        } else if (vs[idx].type == AttrType::FLOATS) {
          *static_cast<float*>(vs[idx].data) /= divs[gid][i];
        } else {
          LOG_WARN("unsupported attr type");
          return RC::SCHEMA_FIELD_NAME_ILLEGAL;
        }
      }
    }
    gid++;
  }
  int gid1 = 0;
  for (auto vs : having_values) {
    for (int i = 0; i < having_size; ++i) {
      if (vs[i].data == nullptr) {
        vs[i].type = AttrType::NULLS;
        continue;
      }
      if (having_ops[i] == AVG_OP) {
        if (vs[i].type == AttrType::INTS) {
          *static_cast<float*>(vs[i].data) /= divs[gid1][i];
        } else if (vs[i].type == AttrType::FLOATS) {
          *static_cast<float*>(vs[i].data) /= divs[gid1][i];
        } else {
          LOG_WARN("unsupported attr type");
          return RC::SCHEMA_FIELD_NAME_ILLEGAL;
        }
      }
    }
    gid1++;
  }

  // having
  // if (select_stmt->having()) {
  //   std::vector<std::vector<Value>> ass;
  //   for (auto filter : having_filters) {
  //     auto idx = filter.value_idx;
  //     for (auto vs : values) {
  //       if (having_cmp(vs[idx], filter.right_value, filter.cmpop)) {
  //         ass.push_back(vs);
  //       }
  //     }
  //   }
  //   values.swap(ass);
  // }
  if (select_stmt->having()) {
    std::vector<std::vector<Value>> ass;
    for (int i = 0; i < having_size; ++i) {
      auto filter = having_filters[i];
      for (int j = 0; j < having_values.size(); ++j) {
        auto vs = having_values[j];
        if (having_cmp(vs[i], filter.right_value, filter.cmpop)) {
          ass.push_back(values[j]);
        }
      }
    }
    values.swap(ass);
  }

  return rc;
}

bool having_cmp(Value v1, Value v2, CompOp cmp) {
  if (v1.type == NULLS || v2.type == NULLS) {
    return false;
  }
  float vl1, vl2;
  if (v1.type == INTS) {
    vl1 = static_cast<float>(*static_cast<int *>(v1.data));
  } else if (v1.type == FLOATS) {
    vl1 = *static_cast<float *>(v1.data);
  }
  if (v2.type == INTS) {
    vl2 = static_cast<float>(*static_cast<int *>(v2.data));
  } else if (v2.type == FLOATS) {
    vl2 = *static_cast<float *>(v2.data);
  }
  if (cmp == CompOp::GREAT_THAN) {
    return vl1 > vl2;
  } else if (cmp == CompOp::GREAT_EQUAL) {
    return vl1 >= vl2;
  } else if (cmp == CompOp::EQUAL_TO) {
    return vl1 == vl2;
  } else if (cmp == CompOp::LESS_EQUAL) {
    return vl1 <= vl2;
  } else if (cmp == CompOp::LESS_THAN) {
    return vl1 < vl2;
  } else if (cmp == CompOp::NOT_EQUAL) {
    return vl1 != vl2;
  }
}

RC ExecuteStage::do_select(SQLStageEvent *sql_event)
{
  SelectStmt *select_stmt = (SelectStmt *)(sql_event->stmt());
  SessionEvent *session_event = sql_event->session_event();
  RC rc = RC::SUCCESS;

  PredicateOperator pred_oper(select_stmt->filter_stmt());

  std::vector<Operator *> scan_opers(select_stmt->tables().size());
  for (int i = 0; i < scan_opers.size(); ++i) {
    printf("add scan oper %d\n", i);
    scan_opers[i] = try_to_create_index_scan_operator(select_stmt->filter_stmt());
    
    if (nullptr == scan_opers[i]) {
       // TODO memory leak
      scan_opers[i] = new TableScanOperator(select_stmt->tables()[i]);
    }
    pred_oper.add_child(scan_opers[i]);
  }


  ProjectOperator project_oper;
  project_oper.add_child(&pred_oper);

  bool is_single_table = select_stmt->tables().size() == 1;

  for (const Field &field : select_stmt->query_fields()) {
    if (field.meta() == nullptr) {
      continue;
    }

    project_oper.add_projection(field.table(), field.meta(), is_single_table);
  }
  for (const Field &field : select_stmt->aggr_fields()) {
    if (field.meta() == nullptr) {
      continue;
    }
    project_oper.add_projection(field.table(), field.meta(), is_single_table);
  }
  for (const Field &field : select_stmt->having_fields()) {
    if (field.meta() == nullptr) {
      continue;
    }
    project_oper.add_projection(field.table(), field.meta(), is_single_table);
  }
  rc = project_oper.open();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open operator");
    for (int i = 0; i < scan_opers.size(); ++i) {
      delete scan_opers[i];
    }
    return rc;
  }


  std::stringstream ss;

  if (select_stmt->group()) {
    print_aggregation_header(ss, select_stmt);
    std::vector<std::vector<Value>> values;
    if (RC::SUCCESS != (rc = group_select_handler(select_stmt, values, project_oper))) {
      for (int i = 0; i < scan_opers.size(); ++i) {
        delete scan_opers[i];
      }
      return rc;
    }
    for (auto vs : values) {
      bool first_value = true;
      for (int i = 0; i < vs.size(); ++i) {
        auto value = vs[i];
        if (first_value) {
          first_value = false;
        } else {
          ss << " | ";
        }

        if (value.type == AttrType::NULLS) {
          ss << "NULL";
        }

        if (value.type == AttrType::INTS) {
          ss << *static_cast<int *>(value.data);
          delete static_cast<int *>(value.data);

        } else if (value.type == AttrType::FLOATS) {
          ss << double2string(*static_cast<float *>(value.data));
          delete static_cast<float *>(value.data);

        } else if (value.type == AttrType::CHARS) {
          ss << (const char *)(value.data);
          delete (const char *)value.data;

        } else if (value.type == AttrType::DATES) {
          int value_int = *(int*)value.data;
          char buf[16] = {0};
          snprintf(buf,sizeof(buf),"%04d-%02d-%02d",value_int/10000, (value_int%10000)/100,value_int%100); // 注意这里月份和天数，不足两位时需要填充0
          ss << buf;
        }
      }
      ss << std::endl;
    } 
  } else if (!select_stmt->aggregation_ops().empty()) {

    // aggregation 

    print_aggregation_header(ss, select_stmt);
    std::vector<Value> values(select_stmt->aggregation_ops().size());
    printf("select aggregation: op size %zu\n", values.size());
    if (RC::SUCCESS != (rc = aggregation_select_handler(select_stmt, values, project_oper))) {
      for (int i = 0; i < scan_opers.size(); ++i) {
        delete scan_opers[i];
      }
      // something wrong happened when iterating the tuples
      LOG_WARN("something wrong happened when iterating the tuples");
      session_event->set_response("FAILURE\n");
      return rc;
    }
    
    bool first_value = true;
    for (int i = 0; i < values.size(); ++i) {
      auto value = values[i];
      if (first_value) {
        first_value = false;
      } else {
        ss << " | ";
      }

      if (value.type == AttrType::NULLS) {
        ss << "NULL";
      }

      if (value.type == AttrType::INTS) {
        ss << *static_cast<int *>(value.data);
        delete static_cast<int *>(value.data);

      } else if (value.type == AttrType::FLOATS) {
        ss << double2string(*static_cast<float *>(value.data));
        delete static_cast<float *>(value.data);

      } else if (value.type == AttrType::CHARS) {
        ss << (const char *)(value.data);
        delete (const char *)value.data;

      } else if (value.type == AttrType::DATES) {
        int value_int = *(int*)value.data;
        char buf[16] = {0};
        snprintf(buf,sizeof(buf),"%04d-%02d-%02d",value_int/10000, (value_int%10000)/100,value_int%100); // 注意这里月份和天数，不足两位时需要填充0
        ss << buf;
      }
    }
    ss << std::endl;

  } else {
    
    // normal select 
    // if (select_stmt->isvaluefunc_ == 0) {
        print_tuple_header(ss, project_oper);
    // } else {
    //     res_print_tuple_header(ss, project_oper);
    // }
    // print_tuple_header(ss, project_oper);
    // order by
    Tuple *tuple;
    if (select_stmt->order()) {
      std::vector<std::pair<Field, bool>> order_fields = select_stmt->order_fields();
      std::vector<std::pair<std::string, std::vector<TupleCell>>> ss_tuples;
      while ((rc = normal_select_handler(select_stmt,tuple, project_oper)) == RC::SUCCESS) {
        std::stringstream tmpss;
        tuple_to_string(tmpss, *tuple);
        tmpss << std::endl;
        // 记录比较所需的tuplecell
        std::vector<TupleCell> tmpcell;
        for (const auto &fb : order_fields) {
          Field field = fb.first;
          TupleCell cell;
          if (tuple->find_cell(field, cell) != RC::SUCCESS) {
            return RC::GENERIC_ERROR;
          }
          tmpcell.push_back(cell);
        }
        ss_tuples.push_back(std::make_pair(tmpss.str(), tmpcell));
      }

      if (rc != RC::RECORD_EOF) {
        // something wrong happened when iterating the tuples
        session_event->set_response("FAILURE\n");
        return rc;
      }
      
      auto size = ss_tuples.size();
      for (int i = 0; i < size; ++i) {
        auto candidate_it = ss_tuples.begin();
        // std::vector<std::pair<std::string, std::vector<TupleCell>>>::iterator candidate_it = ss_tuples.begin();
        for (auto it = ++ss_tuples.begin(); it != ss_tuples.end(); it++) {
          int cmp = 0;
          // cmp <= 0选前，否则选后
          if (order_comp(candidate_it->second, it->second, order_fields, cmp) != RC::SUCCESS) {
            return RC::GENERIC_ERROR;
          }
          if (cmp > 0) {
            candidate_it = it;
          }
        }
        ss << candidate_it->first;
        ss_tuples.erase(candidate_it);
      }
    } else {
      // ************************************************func********************************************************
      if (select_stmt->isvaluefunc_ == 1) {
        
        value_to_string(ss, select_stmt->function_value1_, select_stmt->attr_num_);
        ss << std::endl;
      } else {
        while ((rc = normal_select_handler(select_stmt, tuple, project_oper)) == RC::SUCCESS) {
          printf("do_select: get a tuple\n");

          if (select_stmt->isfunc_ == 0) {
            tuple_to_string(ss, *tuple);
          } else {

            std::vector<std::pair<int, TupleCellSpec *>> modify;
            TupleCellSpec * oold = new TupleCellSpec;
            for (int a = 0; a < select_stmt->attr_num_; a++) {
              if (select_stmt->function_ops_[a] == NO_FUNCTION_OP) {
                continue;
              }

              else if (select_stmt->function_value1_[a].type != UNDEFINED) {
                auto res_tuple = dynamic_cast<ProjectTuple*>(tuple);
                if (res_tuple == nullptr) return RC::MISS_TYPE;
                rc =  res_tuple->modify_cell_spec_at(select_stmt->attr_num_ - a - 1, &select_stmt->function_value1_[a], modify, oold);
              } 

              else {

                TupleCell cell;
                rc = tuple->cell_at(select_stmt->attr_num_ - a - 1, cell);

                Value *v = new Value;
                v->data = malloc(30);
                if (select_stmt->function_ops_[a] == LENGTH_OP) {
                  // printf("1111111111111111111111111 \n", select_stmt->attr_num_);
                  if (cell.attr_type() != CHARS) {
                    printf("panic1 %d\n", cell.attr_type());
                    return RC::MISS_TYPE;
                  }
                  v->type = INTS;
                  *(int*)v->data = strlen((char*)cell.data_);
                } else if (select_stmt->function_ops_[a] == ROUND_OP) {
                  // printf("222222222222222222222222222\n");
                  if (cell.attr_type() != FLOATS || select_stmt->function_value2_[a].type != INTS && select_stmt->function_value2_[a].type != UNDEFINED) {
                    printf("panic2\n");
                    return RC::MISS_TYPE;
                  }
                  v->type = FLOATS;
                  if (select_stmt->function_value2_[a].type == INTS) {
                    *(float*)v->data = round(*(float*)cell.data_, *(int*)(select_stmt->function_value2_[a].data));
                  } else {
                    *(float*)v->data = round1(*(float*)cell.data_);
                  }
                  
                } else if (select_stmt->function_ops_[a] == DATE_FORMAT_OP) {
                  // printf("33333333333333333333333333333333\n");
                  if (cell.attr_type() != DATES) {
                    printf("panic3\n");
                    return RC::MISS_TYPE;
                  }
                  v->type = CHARS;
                  v->data = date_format(*(int*)cell.data_, (char*)select_stmt->function_value2_[a].data);
                } else {
                  printf("panic4\n");
                  return RC::MISS_TYPE;
                }

                auto res_tuple = dynamic_cast<ProjectTuple*>(tuple);
                if (res_tuple == nullptr) return RC::MISS_TYPE;
                rc = res_tuple->modify_cell_spec_at(select_stmt->attr_num_ - a - 1, v, modify, oold);
              }

            }
            auto res_tuple = dynamic_cast<ProjectTuple*>(tuple);
            if (res_tuple == nullptr) return RC::MISS_TYPE;
            // std::reverse(res_tuple->speces_.begin(), res_tuple->speces_.end());
            tuple_to_string(ss, *tuple);
            // std::reverse(res_tuple->speces_.begin(), res_tuple->speces_.end());

            // auto res_tuple = dynamic_cast<ProjectTuple*>(tuple);
            // if (res_tuple == nullptr) return RC::MISS_TYPE;

            while (!modify.empty()) {
              std::pair<int, TupleCellSpec *> pa = modify[modify.size() - 1];
              modify.pop_back();
              res_tuple->speces_[pa.first] = pa.second;
            }
            // res_tuple->speces_[0] = oold;
          }



          ss << std::endl;
        }

        if (rc != RC::RECORD_EOF) {
          // something wrong happened when iterating the tuples
          LOG_WARN("something wrong happened when iterating the tuples");
          session_event->set_response("FAILURE\n");
          return rc;
        }
      }
      // ************************************************func********************************************************
      
      
    }
  }

  session_event->set_response(ss.str());
  for (int i = 0; i < scan_opers.size(); ++i) {
    delete scan_opers[i];
  }
  return rc;
}

RC ExecuteStage::order_comp(std::vector<TupleCell> &cells1, std::vector<TupleCell> &cells2, std::vector<std::pair<Field, bool>> &order_fields, int &cmp) {
  auto size = order_fields.size();
  for (int i = 0; i < size; i++) {
    if (cells2[i].attr_type() == AttrType::NULLS) {
      if (order_fields[i].second) {
        cmp = 2222;
      } else {
        cmp = -2222;
      }
      return RC::SUCCESS;
    }
    if (cells1[i].attr_type() == AttrType::NULLS) {
      if (order_fields[i].second) {
        cmp = -1111;
      } else {
        cmp = 1111;
      }
      return RC::SUCCESS;
    }
    if ((cmp = cells1[i].compare(cells2[i])) != 0) {
      if (!order_fields[i].second) {
        cmp = -cmp;
      }
      return RC::SUCCESS;
    }
  }
  cmp = 0;
  return RC::SUCCESS;
}

// RC ExecuteStage::order_comp(Tuple *tuple1, Tuple *tuple2, std::vector<std::pair<Field, bool>> &order_fields, int &cmp) {
//   TupleCell cell1, cell2;
//   for (const auto & fb : order_fields) {
//     Field field = fb.first;
//     bool is_esc = fb.second;
//     if (tuple1->find_cell(field, cell1) != RC::SUCCESS || tuple2->find_cell(field, cell2) != RC::SUCCESS) {
//       return RC::GENERIC_ERROR;
//     }
//     if ((cmp = cell1.compare(cell2)) != 0) {
//       if (!is_esc) {
//         cmp = -cmp;  
//       }
//       return RC::SUCCESS;
//     }
//   }
//   return RC::SUCCESS;
// }

RC ExecuteStage::do_help(SQLStageEvent *sql_event)
{
  SessionEvent *session_event = sql_event->session_event();
  const char *response = "show tables;\n"
                         "desc `table name`;\n"
                         "create table `table name` (`column name` `column type`, ...);\n"
                         "create index `index name` on `table` (`column`);\n"
                         "insert into `table` values(`value1`,`value2`);\n"
                         "update `table` set column=value [where `column`=`value`];\n"
                         "delete from `table` [where `column`=`value`];\n"
                         "select [ * | `columns` ] from `table`;\n";
  session_event->set_response(response);
  return RC::SUCCESS;
}

RC ExecuteStage::do_create_table(SQLStageEvent *sql_event)
{
  const CreateTable &create_table = sql_event->query()->sstr.create_table;
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();
  RC rc = db->create_table(create_table.relation_name,
			create_table.attribute_count, create_table.attributes);
  if (rc == RC::SUCCESS) {
    session_event->set_response("SUCCESS\n");
  } else {
    session_event->set_response("FAILURE\n");
  }
  return rc;
}

RC ExecuteStage::do_create_index(SQLStageEvent *sql_event)
{
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();
  const CreateIndex &create_index = sql_event->query()->sstr.create_index;
  Table *table = db->find_table(create_index.relation_name);
  if (nullptr == table) {
    session_event->set_response("FAILURE\n");
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  std::vector<const char*> attribute_names;
  for (int i = 0; i < create_index.attribute_num; ++i) {
    attribute_names.push_back(create_index.attribute_name[i]);
  }
  RC rc = table->create_index(nullptr, create_index.index_name, attribute_names, create_index.unique);
  sql_event->session_event()->set_response(rc == RC::SUCCESS ? "SUCCESS\n" : "FAILURE\n");
  return rc;
}

RC ExecuteStage::do_show_tables(SQLStageEvent *sql_event)
{
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();
  std::vector<std::string> all_tables;
  db->all_tables(all_tables);
  if (all_tables.empty()) {
    session_event->set_response("No table\n");
  } else {
    std::stringstream ss;
    for (const auto &table : all_tables) {
      ss << table << std::endl;
    }
    session_event->set_response(ss.str().c_str());
  }
  return RC::SUCCESS;
}

RC ExecuteStage::do_show_index(SQLStageEvent *sql_event) {
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();
  Table *table = db->find_table(sql_event->query()->sstr.show_index.relation_name);
  if (nullptr == table) {
    session_event->set_response("FAILURE\n");
    return RC::INTERNAL;
  }
  std::vector<Index *> indexes = table->all_indexes();
  std::stringstream ss;
  ss << "TABLE | NON_UNIQUE | KEY_NAME | SEQ_IN_INDEX | COLUMN_NAME" << std::endl;
  for (const auto & index : indexes) {
    for (int i = 0; i < index->index_meta().field().size(); ++i) {
      ss << table->name() << " | ";
      //// 此处需要添加unique后修改，暂时无脑输入1。non-unique时为1，unique时为0
      bool unique = index->index_meta().unique();
      if (unique) {
        ss << 0 << " | ";
      } else {
        ss << 1 << " | ";
      }
      if (nullptr == index) {
        session_event->set_response("FAILURE\n");
        return RC::INTERNAL;
      }
      //// 此处暂无多列索引故无脑输入1。支持多列索引后再改为该列在多列索引中的位置。
      ss << index->index_meta().name() << " | " << i+1 << " | " << index->index_meta().field()[i] << std::endl;
    }
  }
  session_event->set_response(ss.str().c_str());
  return RC::SUCCESS;
}

RC ExecuteStage::do_desc_table(SQLStageEvent *sql_event)
{
  Query *query = sql_event->query();
  Db *db = sql_event->session_event()->session()->get_current_db();
  const char *table_name = query->sstr.desc_table.relation_name;
  Table *table = db->find_table(table_name);
  std::stringstream ss;
  if (table != nullptr) {
    table->table_meta().desc(ss);
  } else {
    ss << "No such table: " << table_name << std::endl;
  }
  sql_event->session_event()->set_response(ss.str().c_str());
  return RC::SUCCESS;
}

RC ExecuteStage::do_insert(SQLStageEvent *sql_event)
{
  Stmt *stmt = sql_event->stmt();
  SessionEvent *session_event = sql_event->session_event();
  Session *session = session_event->session();
  Db *db = session->get_current_db();
  Trx *trx = session->current_trx();
  CLogManager *clog_manager = db->get_clog_manager();

  if (stmt == nullptr) {
    LOG_WARN("cannot find statement");
    return RC::GENERIC_ERROR;
  }

  InsertStmt *insert_stmt = (InsertStmt *)stmt;
  Table *table = insert_stmt->table();

  RC rc = RC::SUCCESS;
  printf("tuple amount %zu\n", insert_stmt->tuple_amount());
  for (int i = 0; i < insert_stmt->tuple_amount(); ++i) {
    rc = table->insert_record(trx, insert_stmt->value_amount()[i], insert_stmt->tuples()[i]);
    if (rc == RC::SUCCESS) {
      continue;
    } else {
      printf("fail to insert\n");
      session_event->set_response("FAILURE\n");
      return rc;
    }
  }

  if (!session->is_trx_multi_operation_mode()) {
    CLogRecord *clog_record = nullptr;
    rc = clog_manager->clog_gen_record(CLogType::REDO_MTR_COMMIT, trx->get_current_id(), clog_record);
    if (rc != RC::SUCCESS || clog_record == nullptr) {
      session_event->set_response("FAILURE\n");
      return rc;
    }

    rc = clog_manager->clog_append_record(clog_record);
    if (rc != RC::SUCCESS) {
      session_event->set_response("FAILURE\n");
      return rc;
    } 
    printf("insert is not in trx multi mode\n");
    trx->next_current_id();
    session_event->set_response("SUCCESS\n");
  } else {
    printf("insert is in trx multi op mode\n");
    session_event->set_response("SUCCESS\n");
  }

  session_event->set_response("SUCCESS\n");


  return rc;
}

RC ExecuteStage::do_update(SQLStageEvent *sql_event)
{
  Stmt *stmt = sql_event->stmt();
  SessionEvent *session_event = sql_event->session_event();

  if (stmt == nullptr) {
    LOG_WARN("cannot find statement");
    return RC::GENERIC_ERROR;
  }

  Session *session = session_event->session();
  Db *db = session->get_current_db();
  Trx *trx = session->current_trx();
  CLogManager *clog_manager = db->get_clog_manager();
  UpdateStmt *update_stmt = dynamic_cast<UpdateStmt *>(stmt);

  TableScanOperator scan_oper(update_stmt->table());
  PredicateOperator pred_oper(update_stmt->filter_stmt());
  pred_oper.add_child(&scan_oper);
  UpdateOperator update_oper(update_stmt, trx);
  update_oper.add_child(&pred_oper);

  RC rc = update_oper.open();
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
  } else {

    if (!session->is_trx_multi_operation_mode()) {

      printf("update is not in trx multi op mode\n");

      CLogRecord *clog_record = nullptr;
      rc = clog_manager->clog_gen_record(CLogType::REDO_MTR_COMMIT, trx->get_current_id(), clog_record);
      if (rc != RC::SUCCESS || clog_record == nullptr) {
        session_event->set_response("FAILURE\n");
        return rc;
      }

      rc = clog_manager->clog_append_record(clog_record);
      if (rc != RC::SUCCESS) {
        session_event->set_response("FAILURE\n");
        return rc;
      } 

      trx->next_current_id();
      session_event->set_response("SUCCESS\n");
    } else {
      printf("update is in trx multi op mode\n");
      session_event->set_response("SUCCESS\n");

    }
  }

  // const Updates &updates = sql_event->query()->sstr.update;
  // Table *table = update_stmt->table();

  // int updated_count;
  // RC rc = table->update_record(trx, updates.attribute_name, &updates.value,
  //   updates.condition_num, updates.conditions, &updated_count);
  // if (rc == RC::SUCCESS) {
  //   session_event->set_response("SUCCESS\n");
  //   if (!session->is_trx_multi_operation_mode()) {
  //     CLogRecord *clog_record = nullptr;
  //     rc = clog_manager->clog_gen_record(CLogType::REDO_MTR_COMMIT, trx->get_current_id(), clog_record);
  //     if (rc != RC::SUCCESS || clog_record == nullptr) {
  //       session_event->set_response("FAILURE\n");
  //       return rc;
  //     }

  //     rc = clog_manager->clog_append_record(clog_record);
  //     if (rc != RC::SUCCESS) {
  //       session_event->set_response("FAILURE\n");
  //       return rc;
  //     } 

  //     trx->next_current_id();
  //     session_event->set_response("SUCCESS\n");
  //   }
  // } else {
  //   session_event->set_response("FAILURE\n");
  // }
  return rc;
}

RC ExecuteStage::do_delete(SQLStageEvent *sql_event)
{
  Stmt *stmt = sql_event->stmt();
  SessionEvent *session_event = sql_event->session_event();
  Session *session = session_event->session();
  Db *db = session->get_current_db();
  Trx *trx = session->current_trx();
  CLogManager *clog_manager = db->get_clog_manager();

  if (stmt == nullptr) {
    LOG_WARN("cannot find statement");
    return RC::GENERIC_ERROR;
  }

  DeleteStmt *delete_stmt = (DeleteStmt *)stmt;
  TableScanOperator scan_oper(delete_stmt->table());
  PredicateOperator pred_oper(delete_stmt->filter_stmt());
  pred_oper.add_child(&scan_oper);
  DeleteOperator delete_oper(delete_stmt, trx);
  delete_oper.add_child(&pred_oper);

  RC rc = delete_oper.open();
  if (rc != RC::SUCCESS) {
    // char res[100];
    // sprintf(res, "11%s", strrc(rc));
    // session_event->set_response(res);
    session_event->set_response("FAILURE\n");
  } else {
    session_event->set_response("SUCCESS\n");
    if (!session->is_trx_multi_operation_mode()) {
      CLogRecord *clog_record = nullptr;
      rc = clog_manager->clog_gen_record(CLogType::REDO_MTR_COMMIT, trx->get_current_id(), clog_record);
      if (rc != RC::SUCCESS || clog_record == nullptr) {
        // char res[100];
        // sprintf(res, "33%s", strrc(rc));
        // session_event->set_response("res");
        session_event->set_response("FAILURE\n");
        return rc;
      }

      rc = clog_manager->clog_append_record(clog_record);
      if (rc != RC::SUCCESS) {
        // char res[100];
        // sprintf(res, "22%s", strrc(rc));
        // session_event->set_response("res");
        session_event->set_response("FAILURE\n");
        return rc;
      } 

      trx->next_current_id();
      session_event->set_response("SUCCESS\n");
    }
  }
  return rc;
}

RC ExecuteStage::do_begin(SQLStageEvent *sql_event)
{
  RC rc = RC::SUCCESS;
  SessionEvent *session_event = sql_event->session_event();
  Session *session = session_event->session();
  Db *db = session->get_current_db();
  Trx *trx = session->current_trx();
  CLogManager *clog_manager = db->get_clog_manager();

  session->set_trx_multi_operation_mode(true);

  CLogRecord *clog_record = nullptr;
  rc = clog_manager->clog_gen_record(CLogType::REDO_MTR_BEGIN, trx->get_current_id(), clog_record);
  if (rc != RC::SUCCESS || clog_record == nullptr) {
    session_event->set_response("FAILURE\n");
    return rc;
  }

  rc = clog_manager->clog_append_record(clog_record);
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
  } else {
    session_event->set_response("SUCCESS\n");
  }

  return rc;
}

RC ExecuteStage::do_commit(SQLStageEvent *sql_event)
{
  RC rc = RC::SUCCESS;
  SessionEvent *session_event = sql_event->session_event();
  Session *session = session_event->session();
  Db *db = session->get_current_db();
  Trx *trx = session->current_trx();
  CLogManager *clog_manager = db->get_clog_manager();

  session->set_trx_multi_operation_mode(false);

  CLogRecord *clog_record = nullptr;
  rc = clog_manager->clog_gen_record(CLogType::REDO_MTR_COMMIT, trx->get_current_id(), clog_record);
  if (rc != RC::SUCCESS || clog_record == nullptr) {
    session_event->set_response("FAILURE\n");
    return rc;
  }

  rc = clog_manager->clog_append_record(clog_record);
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
  } else {
    session_event->set_response("SUCCESS\n");
  }

  trx->next_current_id();

  return rc;
}

RC ExecuteStage::do_clog_sync(SQLStageEvent *sql_event)
{
  RC rc = RC::SUCCESS;
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();
  CLogManager *clog_manager = db->get_clog_manager();

  rc = clog_manager->clog_sync();
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
  } else {
    session_event->set_response("SUCCESS\n");
  }

  return rc;
}
