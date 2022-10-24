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

#include <cstring>
#include <limits>
#include <string>
#include <sstream>
#include <iomanip>

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
  auto aggregation_ops = select_stmt->aggregation_ops();
  for (int i = 0; i < aggregation_ops.size(); ++i) {
    AggregationOp aggregation_op = aggregation_ops[i];
    if (i != 0) {
      os << " | ";
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
    size_t n = select_stmt->query_fields().size();
    printf("n : %zu\n", n);
    if (select_stmt->query_fields()[n-i-1].meta() == nullptr) {
      os << "*)";
    } else {
      os << select_stmt->query_fields()[n-i-1].meta()->name() << ")";
    }
  }
  os << '\n';
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

IndexScanOperator *ExecuteStage::try_to_create_index_scan_operator(FilterStmt *filter_stmt)
{
  const std::vector<FilterUnit *> &filter_units = filter_stmt->filter_units();
  printf("like filter length is %d \n", filter_units.size());
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
    if (filter_unit->comp() == NOT_EQUAL) {
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

  for (size_t i = 0; i < values.size(); ++i) {
    if (aggregation_ops[i] == COUNT_OP) {
      values[i].type = AttrType::INTS;
      values[i].data = new int;
      *static_cast<int*>(values[i].data) = 0;

    } else if (aggregation_ops[i] == AVG_OP || aggregation_ops[i] == SUM_OP){
      values[i].type = AttrType::FLOATS;
      values[i].data = new float;
      *static_cast<float*>(values[i].data) = 0;

    } else {
      size_t n = select_stmt->query_fields().size();
      if (i >= select_stmt->query_fields().size()) {
        LOG_ERROR("aggregation: field count doesn't match the op count");
        return RC::MISMATCH;
      }
      switch (select_stmt->query_fields()[n-i-1].attr_type()) {
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

  int cnt = 0;

  while ((rc = project_oper.next()) == RC::SUCCESS) {
    // get current record
    // write to response
    Tuple * tuple = project_oper.current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get current record. rc=%s", strrc(rc));
      break;
    }

    cnt++;

    for (int i = 0; i < aggregation_ops.size(); ++i) {
      TupleCell cell;

      size_t n = select_stmt->query_fields().size();
      if (select_stmt->query_fields()[n-i-1].meta() != nullptr && tuple->find_cell(select_stmt->query_fields()[n-i-1], cell) != RC::SUCCESS) {
        LOG_WARN("cannot get the cell value");
        break;
      }

      AggregationOp aggregation_op = aggregation_ops[i];
      switch (aggregation_op) {
        case COUNT_OP: {
          *static_cast<int *>(values[i].data) += 1;
        } break;

        case SUM_OP:
        case AVG_OP: {
          if (cell.attr_type() == AttrType::INTS) {
            *static_cast<float*>(values[i].data) += *reinterpret_cast<const int*>(cell.data());
          } else if (cell.attr_type() == AttrType::FLOATS) {
            *static_cast<float*>(values[i].data) += *reinterpret_cast<const float*>(cell.data());
          } else if (cell.attr_type() == AttrType::CHARS) {
            float tmp;
            string2float(cell.data(), &tmp);
            *static_cast<float*>(values[i].data) += tmp;
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
    if (aggregation_ops[i] == AVG_OP) {
        if (values[i].type == AttrType::INTS) {
          *static_cast<float*>(values[i].data) /= cnt;
        } else if (values[i].type == AttrType::FLOATS) {
          *static_cast<float*>(values[i].data) /= cnt;
        } else {
          LOG_WARN("unsupported attr type");
          return RC::SCHEMA_FIELD_NAME_ILLEGAL;
        }
    }
  }


  return rc;
}

RC ExecuteStage::do_select(SQLStageEvent *sql_event)
{
  SelectStmt *select_stmt = (SelectStmt *)(sql_event->stmt());
  SessionEvent *session_event = sql_event->session_event();
  RC rc = RC::SUCCESS;

  // Operator *scan_oper = try_to_create_index_scan_operator(select_stmt->filter_stmt());
  // if (nullptr == scan_oper) {
  //   scan_oper = new TableScanOperator(select_stmt->tables()[0]);
  // }

  // DEFER([&] () {delete scan_oper;});

  PredicateOperator pred_oper(select_stmt->filter_stmt());

  std::vector<Operator *> scan_opers(select_stmt->tables().size());
  for (int i = 0; i< scan_opers.size(); ++i) {
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
  rc = project_oper.open();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open operator");
    return rc;
  }


  std::stringstream ss;

  if (!select_stmt->aggregation_ops().empty()) {

    // aggregation 

    print_aggregation_header(ss, select_stmt);
    std::vector<Value> values(select_stmt->aggregation_ops().size());
    printf("select aggregation: op size %zu\n", values.size());
    if (RC::SUCCESS != (rc = aggregation_select_handler(select_stmt, values, project_oper))) {
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
    
    print_tuple_header(ss, project_oper);
    Tuple *tuple;
    while ((rc = normal_select_handler(select_stmt, tuple, project_oper)) == RC::SUCCESS) {
      printf("do_select: get a tuple\n");
      tuple_to_string(ss, *tuple);
      ss << std::endl;
    }
  }

  session_event->set_response(ss.str());
  return rc;
}


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
  auto size = indexes.size();
  ss << "TABLE | NON_UNIQUE | KEY_NAME | SEQ_IN_INDEX | COLUMN_NAME" << std::endl;
  for (const auto & index : indexes) {
    size_t n = index->index_meta().field().size();
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
    printf("is not trx multi\n");
    trx->next_current_id();
    session_event->set_response("SUCCESS\n");
  } else {
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
    session_event->set_response("SUCCESS\n");
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

      trx->next_current_id();
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
