#include "common/log/log.h"
#include "sql/operator/update_operator.h"
#include "sql/parser/parse_defs.h"
#include "storage/record/record.h"
#include "storage/common/table.h"
#include "storage/trx/trx.h"
#include "sql/stmt/update_stmt.h"

RC UpdateOperator::open()
{
  if (children_.size() != 1) {
    LOG_WARN("update operator must has 1 child");
    return RC::INTERNAL;
  }

  Operator *child = children_[0];
  RC rc = child->open();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  Table *table = update_stmt_->table();
  while (RC::SUCCESS == (rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    Record &record = row_tuple->record();


    // find the record's field that needs updating
    const TableMeta table_meta = table->table_meta();
    const FieldMeta *field = table_meta.field(update_stmt_->attribute_name());
    if (field == nullptr) {
      // the field doesn't exist
      LOG_ERROR("Invalid field name=%s", update_stmt_->attribute_name());
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }

    const Value &value = update_stmt_->values()[0];
    if (field->type() != value.type) {
      LOG_ERROR("Invalid value type. table name =%s, field name=%s, type=%d, but given=%d",
          table_meta.name(),
          field->name(),
          field->type(),
          value.type);
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }

    // delete old index 
    rc = table->delete_entry_of_indexes(record.data(), record.rid(), false); 

    size_t copy_len = field->len();
    if (field->type() == CHARS) {
      const size_t data_len = strlen((const char *)value.data);
      if (copy_len > data_len) {
        copy_len = data_len + 1;
      }
    }

    // // update new index
    // rc = insert_entry_of_indexes(record->data(), record->rid());
    // if (rc != RC::SUCCESS) {
    //   LOG_ERROR("Failed to delete indexes of record (rid=%d.%d). rc=%d:%s",
    //               record->rid().page_num, record->rid().slot_num, rc, strrc(rc));
    // } else {
    //   // update the record
    //   rc = record_handler_->update_record(record);
    // }

    // modify the field in the record data
    memcpy(record.data() + field->offset(), value.data, copy_len);

    rc = table->update_record(trx_, &record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to update record: %s", strrc(rc));
      return rc;
    }
  }
  return RC::SUCCESS;
}

RC UpdateOperator::next()
{
  return RC::RECORD_EOF;
}

RC UpdateOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}