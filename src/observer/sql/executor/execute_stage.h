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
// Created by Longda on 2021/4/13.
//

#ifndef __OBSERVER_SQL_EXECUTE_STAGE_H__
#define __OBSERVER_SQL_EXECUTE_STAGE_H__

#include "common/seda/stage.h"
#include "sql/expr/tuple.h"
#include "sql/operator/index_scan_operator.h"
#include "sql/operator/project_operator.h"
#include "sql/parser/parse.h"
#include "rc.h"
#include "sql/parser/parse_defs.h"
#include <vector>

class SQLStageEvent;
class SessionEvent;
class SelectStmt;

class ExecuteStage : public common::Stage {
public:
  ~ExecuteStage();
  static Stage *make_stage(const std::string &tag);

protected:
  // common function
  ExecuteStage(const char *tag);
  bool set_properties() override;

  bool initialize() override;
  void cleanup() override;
  void handle_event(common::StageEvent *event) override;
  void callback_event(common::StageEvent *event, common::CallbackContext *context) override;

  void handle_request(common::StageEvent *event);
  RC do_help(SQLStageEvent *session_event);
  RC do_create_table(SQLStageEvent *sql_event);
  RC do_create_index(SQLStageEvent *sql_event);
  RC do_show_tables(SQLStageEvent *sql_event);
  RC do_show_index(SQLStageEvent *sql_event);
  RC do_desc_table(SQLStageEvent *sql_event);
  RC do_select(SQLStageEvent *sql_event);
  RC do_insert(SQLStageEvent *sql_event);
  RC do_delete(SQLStageEvent *sql_event);
  RC do_update(SQLStageEvent *sql_event);
  RC do_begin(SQLStageEvent *sql_event);
  RC do_commit(SQLStageEvent *sql_event);
  RC do_clog_sync(SQLStageEvent *sql_event);

public:
  static IndexScanOperator *try_to_create_index_scan_operator(FilterStmt *filter_stmt);
  /**
    get a tuple at a time
  */
  static RC normal_select_handler(SelectStmt *select_stmt, Tuple *&tuple, ProjectOperator &project_oper);
  /**
    get values(the size of which is the num of aggregation op)
  */
  static RC aggregation_select_handler(SelectStmt *select_stmt, std::vector<Value> &values, ProjectOperator &project_oper);

  // order 老的 需要取所有tuple
  // static RC order_comp(Tuple *tuple1, Tuple *tuple2, std::vector<std::pair<Field, bool>> &order_fields, int &cmp);

  // order 存所有tuplecell的版本
  static RC order_comp(std::vector<TupleCell> &cells1, std::vector<TupleCell> &cells2, std::vector<std::pair<Field, bool>> &order_fields, int &cmp);

protected:
private:
  Stage *default_storage_stage_ = nullptr;
  Stage *mem_storage_stage_ = nullptr;
};

#endif  //__OBSERVER_SQL_EXECUTE_STAGE_H__
