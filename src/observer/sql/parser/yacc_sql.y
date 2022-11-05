
%{

#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ParserContext {
  Query * ssql;
  size_t select_length;
  size_t condition_length;
  size_t last_conditino_seqno;
  size_t from_length;

  size_t tuple_num;
  size_t value_num[MAX_NUM];       // Length of values
  Value tuples[MAX_NUM][MAX_NUM];  // values to insert

  Selects* upselect_vec[MAX_NUM];  // upselect
  size_t upselect_num;             // upselect
  char* attribute_name[MAX_NUM];   // upselect

  size_t value_length;
  Value values[MAX_NUM];      
  Condition conditions[MAX_NUM];
  CompOp comp;
  char id[MAX_NUM];
  
  AggregationOp aggregation_ops[MAX_NUM];
  size_t aggregation_num;
  size_t last_aggregation_seqno;

  Query *sub_query;
  Query *left_sub_query; // used for select * from (sub query) > (sub_query);
  struct ParserContext *last_context;  // when encounting a sub query, the old context will be placed here(like a stack)
  
  int unique;
} ParserContext;

//获取子串
char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
{
  char *sp = malloc(sizeof(char) * (n2 - n1 + 2));
  int i, j = 0;
  for (i = n1; i <= n2; i++) {
    sp[j++] = s[i];
  }
  sp[j] = 0;
  return sp;
}

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;
  context->condition_length = 0;
  context->last_conditino_seqno = 0;
  context->from_length = 0;
  context->select_length = 0;
  context->value_length = 0;
//   context->ssql->sstr.insertion.value_num = 0;
  for (int i = 0; i < MAX_NUM; ++i) {
  	context->ssql->sstr.insertion.value_num[i] = 0;
  }
  printf("parse sql failed. error=%s", str);

}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)

%}

%define api.pure full
%lex-param { yyscan_t scanner }
%parse-param { void *scanner }

//标识tokens
%token  SEMICOLON
        CREATE
        DROP
        TABLE
        TABLES
        INDEX
        SELECT
        DESC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
		TEXT_T
        FLOAT_T
		DATE_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
        SET
        ON
        LOAD
        DATA
        INFILE
        EQ
        LT
        GT
        LE
        GE
        NE
		IS
		NULLABLE

		COUNT
		AVG
		MAX
		MIN
		SUM
		/* UNEQ */
		INNER
		JOIN

		IN 
		EXISTS

		LIKE
		NOT
		UNIQUE

		ORDER
		BY
		ASC
		GROUP
		HAVING

		OR

		AS

		LENGTH
		ROUND
		DATE_FORMAT

%union {
  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
  char *position;
  struct FuncAttrCon *FuncAttrCon1;
  struct RelAttr *relAttr;
}

%token <number> NUMBER
%token <floats> FLOAT 
%token <string> ID
%token <string> PATH
%token <string> SSS
%token <string> STAR
%token <string> STRING_V
%token <string> DATE_STR
%token <string> NULLVALUE
//非终结符

%type <number> type;
%type <condition1> condition;
%type <value1> value;
%type <number> number;
%type <string> function_field_attr;
%type <FuncAttrCon1> funcCp
%type <relAttr> funcCp_field_attr

%%

commands:		//commands or sqls. parser starts here.
    /* empty */
    | commands command
    ;

command:
	  select  
	| insert
	| update
	| delete
	| create_table
	| drop_table
	| show_tables
	| show_index
	| desc_table
	| create_index	
	| drop_index
	| sync
	| begin
	| commit
	| rollback
	| load_data
	| help
	| exit
    ;

exit:			
    EXIT SEMICOLON {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    };

help:
    HELP SEMICOLON {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    };

sync:
    SYNC SEMICOLON {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
    ;

begin:
    TRX_BEGIN SEMICOLON {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
    ;

commit:
    TRX_COMMIT SEMICOLON {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
    ;

rollback:
    TRX_ROLLBACK SEMICOLON {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
    ;

drop_table:		/*drop table 语句的语法解析树*/
    DROP TABLE ID SEMICOLON {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, $3);
    };

show_tables:
    SHOW TABLES SEMICOLON {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
    ;

show_index:
	SHOW INDEX FROM ID SEMICOLON {
		CONTEXT->ssql->flag = SCF_SHOW_INDEX;
		show_index_init(&CONTEXT->ssql->sstr.show_index, $4);
	}
	;

desc_table:
    DESC ID SEMICOLON {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, $2);
    }
    ;

create_index:		/*create index 语句的语法解析树*/
    CREATE unique_option INDEX ID ON ID LBRACE ID index_attr_list RBRACE SEMICOLON 
		{
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, $4, $6, $8, CONTEXT->unique);
		}
    ;
unique_option:
	/* empty */
	| UNIQUE {
		CONTEXT->unique = 1;
	};

/* /* create_unique_index:		create index 语句的语法解析树 */
    /* CREATE INDEX ID ON ID LBRACE ID index_attr_list RBRACE SEMICOLON 
		{
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, $3, $5, $7, 1);
		}
    ; */ 

index_attr_list:
	/* empty */
	| COMMA ID index_attr_list {
		create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, $2);
	}

drop_index:			/*drop index 语句的语法解析树*/
    DROP INDEX ID  SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, $3);
		}
    ;
create_table:		/*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, $3);
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
    ;
attr_def_list:
    /* empty */
    | COMMA attr_def attr_def_list {    }
    ;
    
attr_def:
    ID_get type LBRACE number RBRACE NONULL
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, $4, 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
    |ID_get type LBRACE number RBRACE NULLABLE
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, $4, 1);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
    |ID_get type NONULL
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, 4, 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
    |ID_get type NULLABLE
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, 4, 1);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
    ;
number:
		NUMBER {$$ = $1;}
		;
type:
	INT_T { $$=INTS; }
       | STRING_T { $$=CHARS; }
	   | TEXT_T {$$=TEXTS; }
       | FLOAT_T { $$=FLOATS; }
	   | DATE_T {$$=DATES;}
       ;
ID_get:
	ID 
	{
		char *temp=$1; 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
	;

NONULL:
	| NOT NULLVALUE
	;

	
insert:				/*insert   语句的语法解析树*/
    /* INSERT INTO ID VALUES LBRACE value value_list RBRACE tuple_list SEMICOLON  */
    INSERT INTO ID VALUES tuple tuple_list SEMICOLON 
		{
			// CONTEXT->values[CONTEXT->value_length++] = *$6;

			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			// CONTEXT->ssql->sstr.insertion.relation_name = $3;
			// CONTEXT->ssql->sstr.insertion.value_num = CONTEXT->value_length;
			// for(i = 0; i < CONTEXT->value_length; i++){
			// 	CONTEXT->ssql->sstr.insertion.values[i] = CONTEXT->values[i];
      // }
			// inserts_init(&CONTEXT->ssql->sstr.insertion, $3, CONTEXT->values, CONTEXT->value_length);
			inserts_init(&CONTEXT->ssql->sstr.insertion, $3, CONTEXT->tuples, CONTEXT->tuple_num, CONTEXT->value_num);

      //临时变量清零
	  CONTEXT->tuple_num = 0;
    };

tuple:
	LBRACE value value_list RBRACE {
		CONTEXT->tuple_num++;
		printf("yacc: tuple num %d\n", CONTEXT->tuple_num);
	};

tuple_list:
	/* empty */
	| COMMA tuple tuple_list {
	};

value_list:
    /* empty */
    | COMMA value value_list  { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
    ;
value:
    NUMBER{	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], $1);
  		value_init_integer(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], $1);
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
    |FLOAT{
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], $1);
		value_init_float(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], $1);
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
    |SSS {
			$1 = substr($1,1,strlen($1)-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], $1);
		value_init_string(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], $1);
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
	|DATE_STR {
		$1 = substr($1,1,strlen($1)-2);
  		// CONTEXT->value_length += value_init_date(&CONTEXT->values[CONTEXT->value_length], $1);
		// if (value_init_date(&CONTEXT->values[CONTEXT->value_length++], $1) == 0) {
		// 	CONTEXT->value_length -= 1;
		// 	CONTEXT->ssql->flag = SCF_INVALID_DATE;
		// 	return 0;
		// }
		if (value_init_date(&CONTEXT->values[CONTEXT->value_length++], $1) == 0 ||
  			value_init_date(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], $1) == 0) {
			CONTEXT->value_length -= 1;
			CONTEXT->value_num[CONTEXT->tuple_num] -= 1;
			CONTEXT->ssql->flag = SCF_INVALID_DATE;
			return 0;
		}
	}
	|NULLVALUE {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
		value_init_null(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++]);
	}
    ;
    
delete:		/*  delete 语句的语法解析树*/
    DELETE FROM ID where SEMICOLON 
		{
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, $3);
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
			CONTEXT->last_conditino_seqno = 0;
    }
    ;
update:			/*  update 语句的语法解析树*/
    UPDATE ID SET assign assign_list where SEMICOLON
		{
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			updates_init(&CONTEXT->ssql->sstr.update, $2, CONTEXT->attribute_name, CONTEXT->values, CONTEXT->upselect_num,
					CONTEXT->conditions, CONTEXT->condition_length, CONTEXT->upselect_vec);
			CONTEXT->condition_length = 0;
			CONTEXT->last_conditino_seqno = 0;
			CONTEXT->value_length = 0;
			CONTEXT->upselect_num = 0;
		}
    ;

assign:         /*   assignment in update*/
	ID EQ value {
		CONTEXT->upselect_num++;
		CONTEXT->attribute_name[CONTEXT->value_length - 1] = $1;
	}
	| ID EQ sub_query {
		CONTEXT->upselect_num++;
		CONTEXT->value_length++;
		CONTEXT->attribute_name[CONTEXT->value_length - 1] = $1;
		CONTEXT->upselect_vec[CONTEXT->value_length - 1] = &CONTEXT->sub_query->sstr.selection;
	}
	;


assign_list:
	/* empty */
	| COMMA assign assign_list;


select:
	select_query SEMICOLON;

select_query:				/*  select 语句的语法解析树*/
    SELECT select_attr FROM ID rel_list where group order
		{
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, $4, NULL);

			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
			CONTEXT->tuple_num = 0;
	}
	| SELECT select_attr FROM ID as_option ID rel_list where order
		{
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, $4, $6);

			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
			CONTEXT->tuple_num = 0;
	}
	| SELECT select_attr
		{
			CONTEXT->ssql->sstr.selection.isvaluefunc = 1;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, NULL, NULL);
			CONTEXT->ssql->flag=SCF_SELECT;//"select";

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
			CONTEXT->tuple_num = 0;
		}
	;


select_attr:
    STAR attr_list {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
    | STAR as_option ID attr_list {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			attr.alias_name = $3;
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
	| ID attr_list {
			RelAttr attr;
			relation_attr_init(&attr, NULL, $1);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
    | ID as_option ID attr_list {
		printf("                     %s\n", $3);
			RelAttr attr;
			relation_attr_init(&attr, NULL, $1);
			attr.alias_name = $3;
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}

  	| ID DOT ID attr_list {
			RelAttr attr;
			relation_attr_init(&attr, $1, $3);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
	

	| func_attr attr_list {
		}
	
	


  	| ID DOT ID as_option ID attr_list {
			RelAttr attr;
			relation_attr_init(&attr, $1, $3);
			attr.alias_name = $5;
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
	| ID DOT STAR attr_list {
			RelAttr attr;
			relation_attr_init(&attr, $1, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			// CONTEXT->aggregation_op = NO_AGGREGATE_OP;
			// selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_op);
			// selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, AggregationOp::NO_AGGREGATE_OP);
		}
	| aggregate_attr aggregate_attr_list {
		if (CONTEXT->last_aggregation_seqno == 0) {
			CONTEXT->last_aggregation_seqno = CONTEXT->aggregation_num;
		}		
		CONTEXT->ssql->sstr.selection.aggregation_alias[CONTEXT->last_aggregation_seqno-1] = NULL;
		CONTEXT->last_aggregation_seqno--;
	}
	| aggregate_attr as_option ID aggregate_attr_list {
		if (CONTEXT->last_aggregation_seqno == 0) {
			CONTEXT->last_aggregation_seqno = CONTEXT->aggregation_num;
		}		
		CONTEXT->ssql->sstr.selection.aggregation_alias[CONTEXT->last_aggregation_seqno-1] = $3;
		CONTEXT->last_aggregation_seqno--;
	}
	
    ;

as_option:
	/* empty */
	| AS;

func_attr: 
	LENGTH LBRACE function_field_attr RBRACE {
		selects_append_funcop(&CONTEXT->ssql->sstr.selection, LENGTH_OP);
		selects_append_funcvalue2(&CONTEXT->ssql->sstr.selection, 0);
		char* attr_name = (char*)malloc(strlen("length(") + strlen($3) + strlen(")") + 1);
		memset(attr_name, strlen("length(") + strlen($3) + strlen(")") + 1, 0);

		//strcat(attr_name, "length(");
		strcpy(attr_name, "length(");
		strcat(attr_name, $3);
		strcat(attr_name, ")");
		strcat(attr_name, "\0");

		selects_modify_alias_name(&CONTEXT->ssql->sstr.selection, attr_name);
		printf("func name %s\n", attr_name);
	}
	| ROUND LBRACE function_field_attr COMMA value RBRACE {
		selects_append_funcop(&CONTEXT->ssql->sstr.selection, ROUND_OP);
		selects_append_funcvalue2(&CONTEXT->ssql->sstr.selection, &CONTEXT->values[CONTEXT->value_length - 1]);
		
		char * value_string = value2string(&CONTEXT->values[CONTEXT->value_length - 1]);

		char* attr_name = (char*)malloc(strlen("round(") + strlen($3) + strlen(",") + strlen(value_string) + strlen(")") + 1);
		memset(attr_name, strlen("round(") + strlen($3) + strlen(",") + strlen(value_string) + strlen(")") + 1, 0);

		//strcat(attr_name, "round(");
		strcpy(attr_name, "round(");
		strcat(attr_name, $3);
		strcat(attr_name, ",");
		strcat(attr_name, "\0");
		
		strcat(attr_name, value_string);
		strcat(attr_name, ")");

		selects_modify_alias_name(&CONTEXT->ssql->sstr.selection, attr_name);
		printf("func name %s\n", attr_name);
	}
	| ROUND LBRACE function_field_attr RBRACE {
		selects_append_funcop(&CONTEXT->ssql->sstr.selection, ROUND_OP);
		selects_append_funcvalue2(&CONTEXT->ssql->sstr.selection, 0);
		char* attr_name = (char*)malloc(strlen("round(") + strlen($3) + strlen(")") + 1);
		memset(attr_name, strlen("round(") + strlen($3) + strlen(")") + 1, 0);

		//strcat(attr_name, "round(");
		strcpy(attr_name, "round(");
		strcat(attr_name, $3);
		strcat(attr_name, ")");
		strcat(attr_name, "\0");

		selects_modify_alias_name(&CONTEXT->ssql->sstr.selection, attr_name);
		printf("func name %s\n", attr_name);
	}
	| DATE_FORMAT LBRACE function_field_attr COMMA value RBRACE {
		selects_append_funcop(&CONTEXT->ssql->sstr.selection, DATE_FORMAT_OP);
		selects_append_funcvalue2(&CONTEXT->ssql->sstr.selection, &CONTEXT->values[CONTEXT->value_length - 1]);

		char * value_string = value2string(&CONTEXT->values[CONTEXT->value_length - 1]);
		char* attr_name = (char*)malloc(strlen("date_format(") + strlen($3) + strlen(",") + strlen(value_string) + strlen(")") + 1);
		memset(attr_name, strlen("date_format(") + strlen($3) + strlen(",") + strlen(value_string) + strlen(")") + 1, 0);
		
		//strcat(attr_name, "date_format(");
		strcpy(attr_name, "date_format(");
		strcat(attr_name, $3);
		strcat(attr_name, ",");
		strcat(attr_name, value_string);
		strcat(attr_name, ")");
		strcat(attr_name, "\0");

		selects_modify_alias_name(&CONTEXT->ssql->sstr.selection, attr_name);
		printf("func name %s\n", attr_name);
	}

	| LENGTH LBRACE function_field_attr RBRACE as_option ID {
		selects_append_funcop(&CONTEXT->ssql->sstr.selection, LENGTH_OP);
		selects_append_funcvalue2(&CONTEXT->ssql->sstr.selection, 0);

		//char* attr_name = (char*)malloc(strlen("length(") + strlen($3) + strlen(")") + 1);
		//memset(attr_name, strlen("length(") + strlen($3) + strlen(")") + 1, 0);

		//strcat(attr_name, "length(");
		//strcat(attr_name, $3);
		//strcat(attr_name, ")");
		//strcat(attr_name, "\0");

		selects_modify_alias_name(&CONTEXT->ssql->sstr.selection, $6);
		//printf("func name %s\n", attr_name);
	}
	| ROUND LBRACE function_field_attr COMMA value RBRACE as_option ID {
		selects_append_funcop(&CONTEXT->ssql->sstr.selection, ROUND_OP);
		selects_append_funcvalue2(&CONTEXT->ssql->sstr.selection, &CONTEXT->values[CONTEXT->value_length - 1]);
		
		//char * value_string = value2string(&CONTEXT->values[CONTEXT->value_length - 1]);
		//char* attr_name = (char*)malloc(strlen("round(") + strlen($3) + strlen(",") + strlen(value_string) + strlen(")") + 1);
		//memset(attr_name, strlen("round(") + strlen($3) + strlen(",") + strlen(value_string) + strlen(")") + 1, 0);

		//strcat(attr_name, "round(");
		//strcat(attr_name, $3);
		//strcat(attr_name, ",");
		//strcat(attr_name, "\0");
		
		//strcat(attr_name, value_string);
		//strcat(attr_name, ")");

		selects_modify_alias_name(&CONTEXT->ssql->sstr.selection, $8);
		//printf("func name %s\n", attr_name);
	}
	| ROUND LBRACE function_field_attr RBRACE as_option ID {
		selects_append_funcop(&CONTEXT->ssql->sstr.selection, ROUND_OP);
		selects_append_funcvalue2(&CONTEXT->ssql->sstr.selection, 0);

		selects_modify_alias_name(&CONTEXT->ssql->sstr.selection, $6);
		//printf("func name %s\n", attr_name);
	}
	| DATE_FORMAT LBRACE function_field_attr COMMA value RBRACE as_option ID {
		selects_append_funcop(&CONTEXT->ssql->sstr.selection, DATE_FORMAT_OP);
		selects_append_funcvalue2(&CONTEXT->ssql->sstr.selection, &CONTEXT->values[CONTEXT->value_length - 1]);

		//char * value_string = value2string(&CONTEXT->values[CONTEXT->value_length - 1]);
		//char* attr_name = (char*)malloc(strlen("date_format(") + strlen($3) + strlen(",") + strlen(value_string) + strlen(")") + 1);
		//memset(attr_name, strlen("date_format(") + strlen($3) + strlen(",") + strlen(value_string) + strlen(")") + 1, 0);
		
		//strcat(attr_name, "date_format(");
		//strcat(attr_name, $3);
		//strcat(attr_name, ",");
		//strcat(attr_name, value_string);
		//strcat(attr_name, ")");
		//strcat(attr_name, "\0");

		selects_modify_alias_name(&CONTEXT->ssql->sstr.selection, $8);
		//printf("func name %s\n", attr_name);
	};

	

function_field_attr:
	value {
		RelAttr attr;
		attr.relation_name = NULL;
		attr.attribute_name = NULL;
		attr.alias_name = NULL;    
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_funcvalue1(&CONTEXT->ssql->sstr.selection, &CONTEXT->values[CONTEXT->value_length - 1]);

		$$ = value2string(&CONTEXT->values[CONTEXT->value_length - 1]);
	}
	| ID {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $1);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_funcvalue1(&CONTEXT->ssql->sstr.selection, 0);
		$$ = $1;
		
	}
	| ID DOT ID {
		RelAttr attr;
		relation_attr_init(&attr, $1, $3);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_funcvalue1(&CONTEXT->ssql->sstr.selection, NULL);

		$$ = (char*)malloc(strlen($1) + 1 + strlen($3));
		strcat($$, $1);
		strcat($$, ".");
		strcat($$, $3);
	};

aggregate_attr:
	/* aggregate_op LBRACE STAR RBRACE {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		printf("aggregation: get a attr *\n");
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	} 
	|  */
	aggregate_op LBRACE aggregation_field_attr RBRACE {
		// RelAttr attr;
		// relation_attr_init(&attr, NULL, $3);
		// printf("aggregation: get a attr %s\n", $3);
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		// selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		// CONTEXT->aggregation_num++;	
	};

aggregation_field_attr:
	/* empty */
	| STAR aggrattr_list {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		printf("aggregation: get a attr *\n");
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
	| ID aggrattr_list {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $1);
		printf("aggregation: get a attr %s\n", $1);
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
	| ID DOT ID aggrattr_list {
		RelAttr attr;
		relation_attr_init(&attr, $1, $3);
		printf("aggregation: get a attr %s\n", $1);
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
	| ID DOT STAR aggrattr_list {
		RelAttr attr;
		relation_attr_init(&attr, $1, "*");
		printf("aggregation: get a attr %s\n", $1);
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
	;

aggrattr_list:
	| COMMA STAR aggrattr_list {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		printf("aggregation: get a attr *\n");
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
	}
	| COMMA ID aggrattr_list {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $2);
		printf("aggregation: get a attr %s\n", $2);
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
	}
	| COMMA ID DOT ID aggrattr_list {
		RelAttr attr;
		relation_attr_init(&attr, $2, $4);
		printf("aggregation: get a attr %s\n", $2);
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
	}
	| COMMA ID DOT STAR aggrattr_list {
		RelAttr attr;
		relation_attr_init(&attr, $2, "*");
		printf("aggregation: get a attr %s\n", $2);
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
	}
	;

aggregate_op: 
	  COUNT { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = COUNT_OP; }
	| AVG   { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = AVG_OP; }
	| MAX   { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = MAX_OP; }
	| MIN   { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = MIN_OP; }
	| SUM   { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = SUM_OP; };

aggregate_attr_list:
	/* empty */
	|COMMA aggregate_attr aggregate_attr_list {
		if (CONTEXT->last_aggregation_seqno == 0) {
			CONTEXT->last_aggregation_seqno = CONTEXT->aggregation_num;
		}		
		CONTEXT->ssql->sstr.selection.aggregation_alias[CONTEXT->last_aggregation_seqno-1] = NULL;
		CONTEXT->last_aggregation_seqno--;
	}
	|COMMA aggregate_attr as_option ID aggregate_attr_list {
		if (CONTEXT->last_aggregation_seqno == 0) {
			CONTEXT->last_aggregation_seqno = CONTEXT->aggregation_num;
		}		
		CONTEXT->ssql->sstr.selection.aggregation_alias[CONTEXT->last_aggregation_seqno-1] = $4;
		CONTEXT->last_aggregation_seqno--;
	}
	| COMMA STAR attr_list {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
	| COMMA ID attr_list{
			RelAttr attr;
			relation_attr_init(&attr, NULL, $2);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
	| COMMA ID DOT ID attr_list {
			RelAttr attr;
			relation_attr_init(&attr, $2, $4);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
	| COMMA ID DOT STAR attr_list {
			RelAttr attr;
			relation_attr_init(&attr, $2, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	};

attr_list:
    /* empty */
    | COMMA ID attr_list {
			RelAttr attr;
			relation_attr_init(&attr, NULL, $2);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
    | COMMA ID as_option ID attr_list {
		printf("                     %s\n", $4);
			RelAttr attr;
			relation_attr_init(&attr, NULL, $2);
			attr.alias_name = $4;
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }

	| COMMA func_attr attr_list {
		
		}


    | COMMA ID DOT ID attr_list {
			RelAttr attr;
			relation_attr_init(&attr, $2, $4);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
    | COMMA ID DOT ID as_option ID attr_list {
			RelAttr attr;
			relation_attr_init(&attr, $2, $4);
			attr.alias_name = $6;
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
	| COMMA ID DOT STAR attr_list {
			RelAttr attr;
			relation_attr_init(&attr, $2, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	} 
	| COMMA aggregate_attr aggregate_attr_list {

	}
  	;



rel_list:
    /* empty */
    | COMMA ID rel_list {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, $2, NULL);
		  }
    | COMMA ID as_option ID rel_list {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, $2, $4);
		  }
	| INNER JOIN ID on_list rel_list {
				selects_append_relation(&CONTEXT->ssql->sstr.selection, $3, NULL);
	}
	| INNER JOIN ID as_option ID on_list rel_list {
				selects_append_relation(&CONTEXT->ssql->sstr.selection, $3, $5);
	}
    ;

on_list:
	/*  empty */
	| ON condition condition_list {

	};

where:
    /* empty */ 
    | WHERE condition condition_list {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
    ;

condition_list:
    /* empty */
    | AND condition condition_list {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
				if (CONTEXT->last_conditino_seqno == 0) {
					CONTEXT->last_conditino_seqno = CONTEXT->condition_length;
				}
				CONTEXT->conditions[CONTEXT->last_conditino_seqno-1].is_and = 1;
				CONTEXT->last_conditino_seqno--;
				printf("get an and condition: seqno %d\n", CONTEXT->last_conditino_seqno);
			}
    | OR condition condition_list {
				if (CONTEXT->last_conditino_seqno == 0) {
					CONTEXT->last_conditino_seqno = CONTEXT->condition_length;
				}
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
				CONTEXT->conditions[CONTEXT->last_conditino_seqno-1].is_and = 0;
				CONTEXT->last_conditino_seqno--;
				printf("get an or condition: seqno %d\n", CONTEXT->last_conditino_seqno);
			}
    ;

funcCp: 
	LENGTH LBRACE funcCp_field_attr RBRACE {
		FuncAttrCon* ff = (FuncAttrCon*)malloc(sizeof(FuncAttrCon));
		ff->funcop = LENGTH_OP;
		ff->args_value.type = 0;
		ff->attr = $3;
		if ($3 == NULL) {
			ff->value = CONTEXT->values[CONTEXT->value_length - 1];
		} else {
			ff->value.type = UNDEFINED;
		}
		$$ = ff;
		
	}
	| ROUND LBRACE funcCp_field_attr RBRACE {
		FuncAttrCon* ff = (FuncAttrCon*)malloc(sizeof(FuncAttrCon));
		ff->funcop = ROUND_OP;
		ff->args_value.type = 0;
		ff->attr = $3;
		if ($3 == NULL) {
			ff->value = CONTEXT->values[CONTEXT->value_length - 1];
		} else {
			ff->value.type = UNDEFINED;
		}
		$$ = ff;
		
	}
	| ROUND LBRACE funcCp_field_attr COMMA value RBRACE {
		FuncAttrCon* ff = (FuncAttrCon*)malloc(sizeof(FuncAttrCon));
		ff->funcop = ROUND_OP;
		ff->args_value = CONTEXT->values[CONTEXT->value_length - 1];
		ff->attr = $3;
		if ($3 == NULL) {
			ff->value = CONTEXT->values[CONTEXT->value_length - 2];
		} else {
			ff->value.type = UNDEFINED;
		}
		$$ = ff;
	}
	| DATE_FORMAT LBRACE funcCp_field_attr COMMA value RBRACE {
		FuncAttrCon* ff = (FuncAttrCon*)malloc(sizeof(FuncAttrCon));
		ff->funcop = DATE_FORMAT_OP;
		ff->args_value = CONTEXT->values[CONTEXT->value_length - 1];
		ff->attr = $3;
		if ($3 == NULL) {
			ff->value = CONTEXT->values[CONTEXT->value_length - 2];
		} else {
			ff->value.type = UNDEFINED;
		}
		$$ = ff;
	};

funcCp_field_attr:
	value {
		$$ = NULL;
	}
	| ID {
		RelAttr* attr = (RelAttr*)malloc(sizeof(RelAttr));
		relation_attr_init(attr, NULL, $1);
		$$ = attr;
		
	}
	| ID DOT ID {
		RelAttr* attr = (RelAttr*)malloc(sizeof(RelAttr));
		relation_attr_init(attr, $1, $3);
		$$ = attr;
	};


condition:
    ID comOp value 
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $1);

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			// condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			condition_init(&condition, Comparison, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 0, 0, NULL, right_value, NULL, NULL, 0);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name = NULL;
			// $$->left_attr.attribute_name= $1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
	|value comOp value 
		{
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			// condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
			condition_init(&condition, Comparison, CONTEXT->comp, 0, 0, NULL, left_value, NULL, 0, 0, 0, NULL, right_value, NULL, NULL, 0);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

	}
	
	|ID comOp ID 
	{
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $1);
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, $3);

			Condition condition;
			condition_init(&condition, Comparison, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 1, 0, 0, &right_attr, NULL, NULL, NULL, 0);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}

	| ID comOp funcCp
	{
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, $1);
		FuncAttrCon* right_func_attr = $3;
		Condition condition;
		condition_init_func(&condition, Comparison, CONTEXT->comp, 
							1, 0, &left_attr, NULL, NULL,   
		                    0, 0, 0, NULL, NULL, NULL, NULL, 0,  
						    NULL, right_func_attr);
		condition.isfunc = 1;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		printf("a\n");
	}

	| ID DOT ID comOp funcCp
	{
		RelAttr left_attr;
		relation_attr_init(&left_attr, $3, $1);
		FuncAttrCon* right_func_attr = $3;
		Condition condition;
		condition_init_func(&condition, Comparison, CONTEXT->comp, 
							1, 0, &left_attr, NULL, NULL,  
							0, 0, 0, NULL, NULL, NULL, NULL, 0,  
							NULL, right_func_attr);
		condition.isfunc = 1;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		printf("b\n");
	}

	| value comOp funcCp
	{
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
		FuncAttrCon* right_func_attr = $3;

		Condition condition;
		condition_init_func(&condition, Comparison, CONTEXT->comp, 
							0, 0, NULL, left_value, NULL, 
							1, 0, 0, NULL, NULL, NULL, NULL, 0,  
							NULL, right_func_attr);
		condition.isfunc = 1;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		printf("c\n");
	}

	| funcCp comOp ID
	{
		FuncAttrCon* left_func_attr = $1;
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, $3);
		Condition condition;
		condition_init_func(&condition, Comparison, CONTEXT->comp, 1, 0, NULL, NULL, NULL, 
							1, 0, 0, &right_attr, NULL, NULL, NULL, 0,  
							left_func_attr, NULL);
		condition.isfunc = 1;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		printf("d\n");
	}

	| funcCp comOp ID DOT ID
	{	
		FuncAttrCon* left_func_attr = $1;
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, $3);
		Condition condition;
		condition_init_func(&condition, Comparison, CONTEXT->comp, 1, 0, NULL, NULL, NULL, 
							1, 0, 0, &right_attr, NULL, NULL, NULL, 0,  
							left_func_attr, NULL);
		condition.isfunc = 1;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		printf("e\n");
	}

	| funcCp comOp value
	{
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
		FuncAttrCon* left_func_attr = $1;

		Condition condition;
		condition_init_func(&condition, Comparison, CONTEXT->comp, 1, 0, NULL, NULL, NULL, 
							0, 0, 0, NULL, right_value, NULL, NULL, 0,
							left_func_attr, NULL);
		condition.isfunc = 1;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		printf("f\n");
	}
	| funcCp comOp funcCp
	{
		FuncAttrCon* left_func_attr = $1;
		FuncAttrCon* right_func_attr = $3;
		Condition condition;
		condition_init_func(&condition, Comparison, CONTEXT->comp, 1, 0, NULL, NULL, NULL, 
							1, 0, 0, NULL, NULL, NULL, NULL, 0,   
							left_func_attr, right_func_attr);
		condition.isfunc = 1;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		printf("g\n");
	}
	| funcCp IN sub_query
	{
		FuncAttrCon* left_func_attr = $1;
		Condition condition;
		condition_init_func(&condition, Contain, CONTEXT->comp, 
							1, 0, NULL, NULL, NULL, 
							0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0,
							left_func_attr, NULL);
		condition.isfunc = 1;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		printf("h\n");
	}
	| funcCp NOT IN sub_query
	{
		FuncAttrCon* left_func_attr = $1;
		Condition condition;
		condition_init_func(&condition, NotContain, CONTEXT->comp, 
							1, 0, NULL, NULL, NULL, 
							0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0,
							left_func_attr, NULL);
		condition.isfunc = 1;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		printf("i\n");
	}
	| funcCp IN LBRACE value value_list RBRACE
	{
		FuncAttrCon* left_func_attr = $1;
		Condition condition;
		condition_init_func(&condition, Contain, CONTEXT->comp, 
							1, 0, NULL, NULL, NULL, 
							0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, CONTEXT->values, CONTEXT->value_length,
							left_func_attr, NULL);
		CONTEXT->value_length = 0;
		condition.isfunc = 1;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		printf("j\n");
	}
	| funcCp NOT IN LBRACE value value_list RBRACE
	{
		FuncAttrCon* left_func_attr = $1;
		Condition condition;
		condition_init_func(&condition, NotContain, CONTEXT->comp, 
							1, 0, NULL, NULL, NULL, 
							0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, CONTEXT->values, CONTEXT->value_length,
							left_func_attr, NULL);
		CONTEXT->value_length = 0;
		condition.isfunc = 1;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		printf("k\n");
	}


	|ID comOp ID DOT ID
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $1);
			RelAttr right_attr;
			relation_attr_init(&right_attr, $3, $5);

			Condition condition;
			// condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			condition_init(&condition, Comparison, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 1, 0, 0, &right_attr, NULL, NULL, NULL, 0);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
	|ID DOT ID comOp ID 
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, $1, $3);
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, $5);

			Condition condition;
			// condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			condition_init(&condition, Comparison, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 1, 0, 0, &right_attr, NULL, NULL, NULL, 0);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
    |value comOp ID
		{
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, $3);

			Condition condition;
			// condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			condition_init(&condition, Comparison, CONTEXT->comp, 0, 0, NULL, left_value, NULL, 1, 0, 0, &right_attr, NULL, NULL, NULL, 0);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp=CONTEXT->comp;
			
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;
		
		}
    |ID DOT ID comOp value
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, $1, $3);
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			// condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			condition_init(&condition, Comparison, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 0, 0, NULL, right_value, NULL, NULL, 0);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp=CONTEXT->comp;
			// $$->right_is_attr = 0;   //属性值
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=NULL;
			// $$->right_value =*$5;			
							}
    |value comOp ID DOT ID
		{
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, $3, $5);

			Condition condition;
			// condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			condition_init(&condition, Comparison, CONTEXT->comp, 0, 0, NULL, left_value, NULL, 1, 0, 0, &right_attr, NULL, NULL, NULL, 0);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;//属性值
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;//属性
			// $$->right_attr.relation_name = $3;
			// $$->right_attr.attribute_name = $5;
									}
    |ID DOT ID comOp ID DOT ID
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, $1, $3);
			RelAttr right_attr;
			relation_attr_init(&right_attr, $5, $7);

			Condition condition;
			// condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			condition_init(&condition, Comparison, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 1, 0, 0, &right_attr, NULL, NULL, NULL, 0);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
	| ID IN sub_query {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, $1);

		Condition condition;
		condition_init(&condition, Contain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		
	}
	| ID NOT IN sub_query {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, $1);

		Condition condition;
		condition_init(&condition, NotContain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
	| ID DOT ID IN sub_query {
		RelAttr left_attr;
		relation_attr_init(&left_attr, $1, $3);

		Condition condition;
		condition_init(&condition, Contain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		
	}
	| ID DOT ID NOT IN sub_query {
		RelAttr left_attr;
		relation_attr_init(&left_attr, $1, $3);

		Condition condition;
		condition_init(&condition, NotContain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
	| ID IN LBRACE value value_list RBRACE {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, $1);

		Condition condition;
		condition_init(&condition, Contain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, 
			CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length = 0;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
	| ID NOT IN LBRACE value value_list RBRACE {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, $1);

		Condition condition;
		condition_init(&condition, NotContain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, 
			CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length = 0;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
	| ID DOT ID IN LBRACE value value_list RBRACE {
		RelAttr left_attr;
		relation_attr_init(&left_attr, $1, $3);

		Condition condition;
		condition_init(&condition, Contain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, 
			CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length = 0;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
	| ID DOT ID NOT IN LBRACE value value_list RBRACE {
		RelAttr left_attr;
		relation_attr_init(&left_attr, $1, $3);

		Condition condition;
		condition_init(&condition, NotContain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, 
			CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length = 0;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
	| ID DOT ID comOp sub_query {
		RelAttr left_attr;
		relation_attr_init(&left_attr, $1, $3);

		Condition condition;
		condition_init(&condition, Comparison, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
	| ID comOp sub_query {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, $1);

		Condition condition;
		condition_init(&condition, Comparison, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
	| sub_query comOp ID DOT ID {
		RelAttr left_attr;
		relation_attr_init(&left_attr, $3, $5);

		switch (CONTEXT->comp) {
			case LESS_EQUAL: {
				CONTEXT->comp = GREAT_EQUAL;
			} break;
			case LESS_THAN: {
				CONTEXT->comp = GREAT_THAN;
			} break;
			case GREAT_EQUAL: {
				CONTEXT->comp = LESS_EQUAL;
			} break;
			case GREAT_THAN: {
				CONTEXT->comp = LESS_THAN;
			} break;
			default: break;
		}

		Condition condition;
		condition_init(&condition, Comparison, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
	| sub_query comOp ID {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, $3);

		switch (CONTEXT->comp) {
			case LESS_EQUAL: {
				CONTEXT->comp = GREAT_EQUAL;
			} break;
			case LESS_THAN: {
				CONTEXT->comp = GREAT_THAN;
			} break;
			case GREAT_EQUAL: {
				CONTEXT->comp = LESS_EQUAL;
			} break;
			case GREAT_THAN: {
				CONTEXT->comp = LESS_THAN;
			} break;
			default: break;
		}
		Condition condition;
		condition_init(&condition, Comparison, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
	| sub_query comOp sub_query {
		Condition condition;
		condition_init(&condition, Comparison, CONTEXT->comp, 0, 1, NULL, NULL, &CONTEXT->left_sub_query->sstr.selection, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
	| EXISTS sub_query {

		Condition condition;
		condition_init(&condition, Exists, CONTEXT->comp, 0, 0, NULL, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
	| NOT EXISTS sub_query {

		Condition condition;
		condition_init(&condition, NotExists, CONTEXT->comp, 0, 0, NULL, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
    ;


group:
	{
		selects_set_group(&CONTEXT->ssql->sstr.selection, 0);
	}
	| GROUP BY group_attrs having {
		selects_set_group(&CONTEXT->ssql->sstr.selection, 1);
	}
	;

group_attrs:
	group_attr group_attr_list {
		// 递归。最新秒杀升级版。
	}
	;

group_attr_list:
	| COMMA group_attr group_attr_list {
		// 递归。最新秒杀升级版。
	}
	;

// 只在此处添加attr就行。这就是最新秒杀升级版的含金量!
group_attr: 
	ID {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $1);
		selects_append_groupattr(&CONTEXT->ssql->sstr.selection, &attr);
	}
	| ID DOT ID {
		RelAttr attr;
		relation_attr_init(&attr, $1, $3);
		selects_append_groupattr(&CONTEXT->ssql->sstr.selection, &attr);
	}
	;

having:
	{
		selects_set_having(&CONTEXT->ssql->sstr.selection, 0);
	}
	| HAVING having_condition having_condition_list {
		// 递归
		selects_set_having(&CONTEXT->ssql->sstr.selection, 1);
	}
	;

having_condition_list:
	| COMMA having_condition having_condition_list{
		// 递归
	}
	;

// 题目 having 只有 having aggr(id) comOp value这种操作，所以写起来大大滴简单了，直接五种暴力穷举秒杀。（秒杀个锤锤，不止五种）
// 使用 having 语句专属的无敌史诗级简化having_condition存储筛选条件
// 暂时cv大法暴力粘贴穷举，有时间再爆改。

having_condition:
	| COUNT LBRACE ID RBRACE comOp value {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $3);
		Having_Condition condition;
		having_condition_init(&condition, COUNT_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
	| COUNT LBRACE STAR RBRACE comOp value {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		Having_Condition condition;
		having_condition_init(&condition, COUNT_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
	| COUNT LBRACE ID DOT ID RBRACE comOp value {
		RelAttr attr;
		relation_attr_init(&attr, $3, $5);
		Having_Condition condition;
		having_condition_init(&condition, COUNT_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
	| COUNT LBRACE ID DOT STAR RBRACE comOp value {
		RelAttr attr;
		relation_attr_init(&attr, $3, "*");
		Having_Condition condition;
		having_condition_init(&condition, COUNT_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
	| AVG LBRACE ID RBRACE comOp value {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $3);
		Having_Condition condition;
		having_condition_init(&condition, AVG_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
	| AVG LBRACE STAR RBRACE comOp value {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		Having_Condition condition;
		having_condition_init(&condition, AVG_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
	| AVG LBRACE ID DOT ID RBRACE comOp value {
		RelAttr attr;
		relation_attr_init(&attr, $3, $5);
		Having_Condition condition;
		having_condition_init(&condition, AVG_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
	| AVG LBRACE ID DOT STAR RBRACE comOp value {
		RelAttr attr;
		relation_attr_init(&attr, $3, "*");
		Having_Condition condition;
		having_condition_init(&condition, AVG_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
	| MAX LBRACE ID RBRACE comOp value {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $3);
		Having_Condition condition;
		having_condition_init(&condition, MAX_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
	| MAX LBRACE STAR RBRACE comOp value {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		Having_Condition condition;
		having_condition_init(&condition, MAX_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
	| MAX LBRACE ID DOT ID RBRACE comOp value {
		RelAttr attr;
		relation_attr_init(&attr, $3, $5);
		Having_Condition condition;
		having_condition_init(&condition, MAX_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
	| MAX LBRACE ID DOT STAR RBRACE comOp value {
		RelAttr attr;
		relation_attr_init(&attr, $3, "*");
		Having_Condition condition;
		having_condition_init(&condition, MAX_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
	| MIN LBRACE ID RBRACE comOp value {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $3);
		Having_Condition condition;
		having_condition_init(&condition, MIN_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
	| MIN LBRACE STAR RBRACE comOp value {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		Having_Condition condition;
		having_condition_init(&condition, MIN_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
	| MIN LBRACE ID DOT ID RBRACE comOp value {
		RelAttr attr;
		relation_attr_init(&attr, $3, $5);
		Having_Condition condition;
		having_condition_init(&condition, MIN_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
	| MIN LBRACE ID DOT STAR RBRACE comOp value {
		RelAttr attr;
		relation_attr_init(&attr, $3, "*");
		Having_Condition condition;
		having_condition_init(&condition, MIN_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
	| SUM LBRACE ID RBRACE comOp value {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $3);
		Having_Condition condition;
		having_condition_init(&condition, SUM_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
	| SUM LBRACE STAR RBRACE comOp value {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "$3");
		Having_Condition condition;
		having_condition_init(&condition, SUM_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
	| SUM LBRACE ID DOT ID RBRACE comOp value {
		RelAttr attr;
		relation_attr_init(&attr, $3, $5);
		Having_Condition condition;
		having_condition_init(&condition, SUM_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
	| SUM LBRACE ID DOT STAR RBRACE comOp value {
		RelAttr attr;
		relation_attr_init(&attr, $3, "*");
		Having_Condition condition;
		having_condition_init(&condition, SUM_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
	;

order:
	{
		selects_set_order(&CONTEXT->ssql->sstr.selection, 0);
	}
	| ORDER BY order_attr {
		selects_set_order(&CONTEXT->ssql->sstr.selection, 1);
	}
	;

order_attr:
	ID asc order_attr_list {
			RelAttr attr;
			relation_attr_init(&attr, NULL, $1);
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
		}
  	| ID DOT ID asc order_attr_list {
			RelAttr attr;
			relation_attr_init(&attr, $1, $3);
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
		}
	| ID DESC order_attr_list {
			RelAttr attr;
			relation_attr_init(&attr, NULL, $1);
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
		}
	| ID DOT ID DESC order_attr_list {
			RelAttr attr;
			relation_attr_init(&attr, $1, $3);
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
		}
    ;

order_attr_list:
    /* empty */
    | COMMA ID asc order_attr_list {
			RelAttr attr;
			relation_attr_init(&attr, NULL, $2);
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
      }
    | COMMA ID DESC order_attr_list {
			RelAttr attr;
			relation_attr_init(&attr, NULL, $2);
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
      }
    | COMMA ID DOT ID asc order_attr_list {
			RelAttr attr;
			relation_attr_init(&attr, $2, $4);
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
  	  }
    | COMMA ID DOT ID DESC order_attr_list {
			RelAttr attr;
			relation_attr_init(&attr, $2, $4);
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
  	  }
  	;

asc:
	| ASC
	;


sub_query:
	LBRACE N select_query RBRACE {
		// TODO support complex sub query
		ParserContext *old_context = CONTEXT->last_context;
		printf("swap back old context addr %p\n", CONTEXT->last_context);
		if (old_context->sub_query) {
			old_context->left_sub_query = old_context->sub_query;
			old_context->sub_query = CONTEXT->ssql;
		} else {
			old_context->sub_query = CONTEXT->ssql;
		}
		*CONTEXT = *old_context;
		printf("sub query addr %p\n", old_context->sub_query);
	};
N: /* empty */ {
	// create a new context
	ParserContext *old_context = (ParserContext *)malloc(sizeof(ParserContext));
	ParserContext tmp = *old_context;
	*old_context = *CONTEXT;
	*CONTEXT = tmp; 
	memset(CONTEXT, 0, sizeof(*CONTEXT));
	CONTEXT->ssql = (Query *)malloc(sizeof(Query));
	memset(CONTEXT->ssql, 0, sizeof(Query));
	
	printf("SWAP OUT sub query addr %p\n", CONTEXT->ssql);
	// old_context->last_context = CONTEXT->last_context;
	CONTEXT->last_context = old_context;
	printf("swap out old context addr %p\n", old_context);
};


comOp:
  	  EQ { CONTEXT->comp = EQUAL_TO; }
    | LT { CONTEXT->comp = LESS_THAN; }
    | GT { CONTEXT->comp = GREAT_THAN; }
    | LE { CONTEXT->comp = LESS_EQUAL; }
    | GE { CONTEXT->comp = GREAT_EQUAL; }
    | NE { CONTEXT->comp = NOT_EQUAL; }
	| IS { CONTEXT->comp = LOGICAL_IS; }
	| IS NOT {CONTEXT->comp = LOGICAL_IS_NOT; }
	| LIKE { CONTEXT->comp = LIKE_OP; }
	| NOT LIKE { CONTEXT->comp = NOT_LIKE_OP; }
    ;

load_data:
		LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON
		{
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, $7, $4);
		}
		;
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
