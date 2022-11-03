#include "common/log/log.h"
#include "sql/operator/update_operator.h"
#include "sql/parser/parse_defs.h"
#include "storage/record/record.h"
#include "storage/common/table.h"
#include "storage/trx/trx.h"
#include "sql/stmt/update_stmt.h"

//***************************************************************upelect************************************************************
#include "util/util.h"
#include <string>

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
    
    int len = update_stmt_->values_num();

    for (int i = 0; i < len; i++) {
      const FieldMeta *field = table_meta.field(update_stmt_->attribute_name(i));
      if (field == nullptr) {
        // the field doesn't exist
        LOG_ERROR("Invalid field name=%s", update_stmt_->attribute_name(i));
        return RC::SCHEMA_FIELD_NOT_EXIST;
      }

      const Value *value = &update_stmt_->values()[i];

      if (field->type() != value->type && value->type != AttrType::NULLS) {

        // ******************************typecast*********************************
        if (value->type == AttrType::CHARS && field->type() == AttrType::INTS) {
          float num = 0;
          Value* v = const_cast<Value*>(value);
          std::string str = static_cast<char*>(v->data);
          string2float(str, &num);
          if (num - (float)((int)num) >= 0.5) num += 1;
          v->type = AttrType::INTS;
          *((int*)(v->data)) = (int)num;
        } else if (value->type == AttrType::CHARS && field->type() == AttrType::FLOATS) {
          float num = 0;
          Value* v = const_cast<Value*>(value);
          std::string str = static_cast<char*>(v->data);
          string2float(str, &num);
          v->type = AttrType::FLOATS;
          *((float*)(v->data)) = num;
        } else if (value->type == AttrType::INTS && field->type() == AttrType::FLOATS) {
          Value* v = const_cast<Value*>(value);
          int* num = static_cast<int*>(v->data);
          float n = (float)*num;
          float* fnum = static_cast<float*>(v->data);
          *fnum = n;
          v->type = AttrType::FLOATS;
        } else if (value->type == AttrType::INTS && field->type() == AttrType::CHARS) {
          Value* v = const_cast<Value*>(value);
          int* num = static_cast<int*>(v->data);
          char* str = static_cast<char*>(v->data);

          std::string num_str = std::to_string(*num);
          char* s = const_cast<char*>(num_str.data());
          // char* s = const_cast<char*>(std::to_string(*num).data());
          for ( int i = 0; s[i] != '\0'; i++) {
            str[i] = s[i];
          }
          v->type = CHARS;

        } else if (value->type == AttrType::FLOATS && field->type() == AttrType::INTS) {
          Value* v = const_cast<Value*>(value);
          float* num = static_cast<float*>(v->data);
          int n = (int)*num;
          if (*num - (float)n >= 0.5) n += 1;
          int* inum = static_cast<int*>(v->data);
          *inum = n;
          v->type = AttrType::INTS;

        } else if (value->type == AttrType::FLOATS && field->type() == AttrType::CHARS) {
          Value* v = const_cast<Value*>(value);
          float* num = static_cast<float*>(v->data);
          char* str = static_cast<char*>(v->data);

          char* s = const_cast<char*>(double2string(*num).data());
          for ( int i = 0; s[i] != '\0'; i++) {
            str[i] = s[i];
          }
          v->type = CHARS;

        // **********************************typecast******************************************
        } else {
          LOG_ERROR("Invalid value type. table name =%s, field name=%s, type=%d, but given=%d",
              table_meta.name(),
              field->name(),
              field->type(),
              value->type);
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
        }
      }


      if (!field->nullable() && value->type == AttrType::NULLS) {
        return RC::NULL_OP_ON_NON_NULLABLE;
      }

      // delete old index 
      rc = table->delete_entry_of_indexes(record.data(), record.rid(), false); 


      size_t copy_len = field->len();
      if (field->type() == CHARS) {
        // if (strcmp((const char*)value.data, "N01") == 0|| strcmp((const char*)value.data, "n01") == 0) {
        //   strcpy((char *)value.data, "ddd");
        // }
        const size_t data_len = strlen((const char *)value->data);
        if (copy_len > data_len) {
          copy_len = data_len + 1;
        }
      }

      if (value->type == AttrType::NULLS) {
        if (!field->nullable()) {
          LOG_WARN("shouldn't set a field a NULL value since the field isn't nullable");
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
        }
      } else {
        // modify the field in the record data
        memcpy(record.data() + field->offset(), value->data, copy_len);
      }

      // set null
      int null_bit = 1 << table_meta.get_field_place(field->name());
      if (field->nullable() && value->type == AttrType::NULLS) {
        *(int *)(record.data() + NULLMAP_OFFSET) |= null_bit;
      } else {
        *(int *)(record.data() + NULLMAP_OFFSET) &= ~null_bit;
      }

      rc = table->update_record(trx_, &record);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to update record: %s", strrc(rc));
        return rc;
      }

    }
    
  }
  return RC::SUCCESS;
}


//***************************************************************upelect************************************************************



RC UpdateOperator::next()
{
  return RC::RECORD_EOF;
}

RC UpdateOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}



// const FieldMeta *field = table_meta.field(update_stmt_->attribute_name(0));
//     if (field == nullptr) {
//       // the field doesn't exist
//       LOG_ERROR("Invalid field name=%s", update_stmt_->attribute_name(0));
//       return RC::SCHEMA_FIELD_NOT_EXIST;
//     }

//     const Value &value = update_stmt_->values()[0];
//     if (field->type() != value.type && value.type != AttrType::NULLS) {
//       LOG_ERROR("Invalid value type. table name =%s, field name=%s, type=%d, but given=%d",
//           table_meta.name(),
//           field->name(),
//           field->type(),
//           value.type);
//       return RC::SCHEMA_FIELD_TYPE_MISMATCH;
//     }

//     if (!field->nullable() && value.type == AttrType::NULLS) {
//       return RC::NULL_OP_ON_NON_NULLABLE;
//     }

//     // delete old index 
//     rc = table->delete_entry_of_indexes(record.data(), record.rid(), false); 

//     size_t copy_len = field->len();
//     if (field->type() == CHARS) {
//       const size_t data_len = strlen((const char *)value.data);
//       if (copy_len > data_len) {
//         copy_len = data_len + 1;
//       }
//     }

    
//     // modify the field in the record data
//     memcpy(record.data() + field->offset(), value.data, copy_len);

//     // set null
//     int null_bit = 1 << table_meta.get_field_place(field->name());
//     if (field->nullable() && value.type == AttrType::NULLS) {
//       *(int *)(record.data() + NULLMAP_OFFSET) |= null_bit;
//     } else {
//       *(int *)(record.data() + NULLMAP_OFFSET) &= ~null_bit;
//     }

//     rc = table->update_record(trx_, &record);
//     if (rc != RC::SUCCESS) {
//       LOG_WARN("failed to update record: %s", strrc(rc));
//       return rc;
//     }



// size_t len = update_stmt_->values_num();
    
//     for (int i = 0; i < len; i++) {
//       const FieldMeta *field = table_meta.field(update_stmt_->attribute_name(i));
//       if (field == nullptr) {
//         // the field doesn't exist
//         printf("Invalid field name=%s", update_stmt_->attribute_name(i));
//         return RC::SCHEMA_FIELD_NOT_EXIST;
//       }

//       const Value* value;
     
//       value = &update_stmt_->values()[i];
      
//       if (field->type() != value->type) {
//         if (value->type == AttrType::CHARS && field->type() == AttrType::INTS) {
//           float num = 0;
//           Value* v = const_cast<Value*>(value);
//           std::string str = static_cast<char*>(v->data);
//           string2float(str, &num);
//           if (num - (float)((int)num) >= 0.5) num += 1;
//           v->type = AttrType::INTS;
//           *((int*)(v->data)) = (int)num;
//         } else if (value->type == AttrType::CHARS && field->type() == AttrType::FLOATS) {
//           float num = 0;
//           Value* v = const_cast<Value*>(value);
//           std::string str = static_cast<char*>(v->data);
//           string2float(str, &num);
//           v->type = AttrType::FLOATS;
//           *((float*)(v->data)) = num;
//         } else if (value->type == AttrType::INTS && field->type() == AttrType::FLOATS) {
//           Value* v = const_cast<Value*>(value);
//           int* num = static_cast<int*>(v->data);
//           float n = (float)*num;
//           float* fnum = static_cast<float*>(v->data);
//           *fnum = n;
//           v->type = AttrType::FLOATS;
//         } else if (value->type == AttrType::INTS && field->type() == AttrType::CHARS) {
//           Value* v = const_cast<Value*>(value);
//           int* num = static_cast<int*>(v->data);
//           char* str = static_cast<char*>(v->data);

//           char* s = const_cast<char*>(std::to_string(*num).data());
//           for ( int i = 0; s[i] != '\0'; i++) {
//             str[i] = s[i];
//           }
//           v->type = CHARS;

//         } else if (value->type == AttrType::FLOATS && field->type() == AttrType::INTS) {
//           Value* v = const_cast<Value*>(value);
//           float* num = static_cast<float*>(v->data);
//           int n = (int)*num;
//           if (*num - (float)n >= 0.5) n += 1;
//           int* inum = static_cast<int*>(v->data);
//           *inum = n;
//           v->type = AttrType::INTS;

//         } else if (value->type == AttrType::FLOATS && field->type() == AttrType::CHARS) {
//           Value* v = const_cast<Value*>(value);
//           float* num = static_cast<float*>(v->data);
//           char* str = static_cast<char*>(v->data);

//           char* s = const_cast<char*>(double2string(*num).data());
//           for ( int i = 0; s[i] != '\0'; i++) {
//             str[i] = s[i];
//           }
//           v->type = CHARS;
//         } else {
//           printf("Invalid value type. table name =%s, field name=%s, type=%d, but given=%d",
//             table_meta.name(),
//             field->name(),
//             field->type(),
//             value->type);
//           return RC::SCHEMA_FIELD_TYPE_MISMATCH;
//         }
//       }

//       // delete old index 
//       rc = table->delete_entry_of_indexes(record.data(), record.rid(), false); 

//       size_t copy_len = field->len();
//       if (field->type() == CHARS) {
//         const size_t data_len = strlen((const char *)value->data);
//         if (copy_len > data_len) {
//           copy_len = data_len + 1;
//         }
//       }

//       // modify the field in the record data
//       memcpy(record.data() + field->offset(), value->data, copy_len);
//       rc = table->update_record(trx_, &record);
//       if (rc != RC::SUCCESS) {
//         LOG_WARN("failed to update record: %s", strrc(rc));
//         return rc;
//       }

//       // set null
//       int null_bit = 1 << table_meta.get_field_place(field->name());
//       if (field->nullable() && value->type == AttrType::NULLS) {
//         *(int *)(record.data() + NULLMAP_OFFSET) |= null_bit;
//       } else {
//         *(int *)(record.data() + NULLMAP_OFFSET) &= ~null_bit;
//       }

//       rc = table->update_record(trx_, &record);
//       if (rc != RC::SUCCESS) {
//         LOG_WARN("failed to update record: %s", strrc(rc));
//         return rc;
//       }

//     }