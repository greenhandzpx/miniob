/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


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

  Query *sub_query;
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


#line 148 "yacc_sql.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_YACC_SQL_TAB_H_INCLUDED
# define YY_YY_YACC_SQL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SEMICOLON = 258,
    CREATE = 259,
    DROP = 260,
    TABLE = 261,
    TABLES = 262,
    INDEX = 263,
    SELECT = 264,
    DESC = 265,
    SHOW = 266,
    SYNC = 267,
    INSERT = 268,
    DELETE = 269,
    UPDATE = 270,
    LBRACE = 271,
    RBRACE = 272,
    COMMA = 273,
    TRX_BEGIN = 274,
    TRX_COMMIT = 275,
    TRX_ROLLBACK = 276,
    INT_T = 277,
    STRING_T = 278,
    TEXT_T = 279,
    FLOAT_T = 280,
    DATE_T = 281,
    HELP = 282,
    EXIT = 283,
    DOT = 284,
    INTO = 285,
    VALUES = 286,
    FROM = 287,
    WHERE = 288,
    AND = 289,
    SET = 290,
    ON = 291,
    LOAD = 292,
    DATA = 293,
    INFILE = 294,
    EQ = 295,
    LT = 296,
    GT = 297,
    LE = 298,
    GE = 299,
    NE = 300,
    IS = 301,
    NULLABLE = 302,
    COUNT = 303,
    AVG = 304,
    MAX = 305,
    MIN = 306,
    SUM = 307,
    INNER = 308,
    JOIN = 309,
    IN = 310,
    EXISTS = 311,
    LIKE = 312,
    NOT = 313,
    UNIQUE = 314,
    NUMBER = 315,
    FLOAT = 316,
    ID = 317,
    PATH = 318,
    SSS = 319,
    STAR = 320,
    STRING_V = 321,
    DATE_STR = 322,
    NULLVALUE = 323
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
<<<<<<< HEAD
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_TABLES = 7,                     /* TABLES  */
  YYSYMBOL_INDEX = 8,                      /* INDEX  */
  YYSYMBOL_SELECT = 9,                     /* SELECT  */
  YYSYMBOL_DESC = 10,                      /* DESC  */
  YYSYMBOL_SHOW = 11,                      /* SHOW  */
  YYSYMBOL_SYNC = 12,                      /* SYNC  */
  YYSYMBOL_INSERT = 13,                    /* INSERT  */
  YYSYMBOL_DELETE = 14,                    /* DELETE  */
  YYSYMBOL_UPDATE = 15,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 16,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 17,                    /* RBRACE  */
  YYSYMBOL_COMMA = 18,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 19,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 20,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 21,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 22,                     /* INT_T  */
  YYSYMBOL_STRING_T = 23,                  /* STRING_T  */
  YYSYMBOL_TEXT_T = 24,                    /* TEXT_T  */
  YYSYMBOL_FLOAT_T = 25,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 26,                    /* DATE_T  */
  YYSYMBOL_HELP = 27,                      /* HELP  */
  YYSYMBOL_EXIT = 28,                      /* EXIT  */
  YYSYMBOL_DOT = 29,                       /* DOT  */
  YYSYMBOL_INTO = 30,                      /* INTO  */
  YYSYMBOL_VALUES = 31,                    /* VALUES  */
  YYSYMBOL_FROM = 32,                      /* FROM  */
  YYSYMBOL_WHERE = 33,                     /* WHERE  */
  YYSYMBOL_AND = 34,                       /* AND  */
  YYSYMBOL_SET = 35,                       /* SET  */
  YYSYMBOL_ON = 36,                        /* ON  */
  YYSYMBOL_LOAD = 37,                      /* LOAD  */
  YYSYMBOL_DATA = 38,                      /* DATA  */
  YYSYMBOL_INFILE = 39,                    /* INFILE  */
  YYSYMBOL_EQ = 40,                        /* EQ  */
  YYSYMBOL_LT = 41,                        /* LT  */
  YYSYMBOL_GT = 42,                        /* GT  */
  YYSYMBOL_LE = 43,                        /* LE  */
  YYSYMBOL_GE = 44,                        /* GE  */
  YYSYMBOL_NE = 45,                        /* NE  */
  YYSYMBOL_IS = 46,                        /* IS  */
  YYSYMBOL_NULLABLE = 47,                  /* NULLABLE  */
  YYSYMBOL_COUNT = 48,                     /* COUNT  */
  YYSYMBOL_AVG = 49,                       /* AVG  */
  YYSYMBOL_MAX = 50,                       /* MAX  */
  YYSYMBOL_MIN = 51,                       /* MIN  */
  YYSYMBOL_SUM = 52,                       /* SUM  */
  YYSYMBOL_INNER = 53,                     /* INNER  */
  YYSYMBOL_JOIN = 54,                      /* JOIN  */
  YYSYMBOL_IN = 55,                        /* IN  */
  YYSYMBOL_EXISTS = 56,                    /* EXISTS  */
  YYSYMBOL_LIKE = 57,                      /* LIKE  */
  YYSYMBOL_NOT = 58,                       /* NOT  */
  YYSYMBOL_UNIQUE = 59,                    /* UNIQUE  */
  YYSYMBOL_ORDER = 60,                     /* ORDER  */
  YYSYMBOL_BY = 61,                        /* BY  */
  YYSYMBOL_ASC = 62,                       /* ASC  */
  YYSYMBOL_NUMBER = 63,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 64,                     /* FLOAT  */
  YYSYMBOL_ID = 65,                        /* ID  */
  YYSYMBOL_PATH = 66,                      /* PATH  */
  YYSYMBOL_SSS = 67,                       /* SSS  */
  YYSYMBOL_STAR = 68,                      /* STAR  */
  YYSYMBOL_STRING_V = 69,                  /* STRING_V  */
  YYSYMBOL_DATE_STR = 70,                  /* DATE_STR  */
  YYSYMBOL_NULLVALUE = 71,                 /* NULLVALUE  */
  YYSYMBOL_YYACCEPT = 72,                  /* $accept  */
  YYSYMBOL_commands = 73,                  /* commands  */
  YYSYMBOL_command = 74,                   /* command  */
  YYSYMBOL_exit = 75,                      /* exit  */
  YYSYMBOL_help = 76,                      /* help  */
  YYSYMBOL_sync = 77,                      /* sync  */
  YYSYMBOL_begin = 78,                     /* begin  */
  YYSYMBOL_commit = 79,                    /* commit  */
  YYSYMBOL_rollback = 80,                  /* rollback  */
  YYSYMBOL_drop_table = 81,                /* drop_table  */
  YYSYMBOL_show_tables = 82,               /* show_tables  */
  YYSYMBOL_show_index = 83,                /* show_index  */
  YYSYMBOL_desc_table = 84,                /* desc_table  */
  YYSYMBOL_create_index = 85,              /* create_index  */
  YYSYMBOL_unique_option = 86,             /* unique_option  */
  YYSYMBOL_index_attr_list = 87,           /* index_attr_list  */
  YYSYMBOL_drop_index = 88,                /* drop_index  */
  YYSYMBOL_create_table = 89,              /* create_table  */
  YYSYMBOL_attr_def_list = 90,             /* attr_def_list  */
  YYSYMBOL_attr_def = 91,                  /* attr_def  */
  YYSYMBOL_number = 92,                    /* number  */
  YYSYMBOL_type = 93,                      /* type  */
  YYSYMBOL_ID_get = 94,                    /* ID_get  */
  YYSYMBOL_NONULL = 95,                    /* NONULL  */
  YYSYMBOL_insert = 96,                    /* insert  */
  YYSYMBOL_tuple = 97,                     /* tuple  */
  YYSYMBOL_tuple_list = 98,                /* tuple_list  */
  YYSYMBOL_value_list = 99,                /* value_list  */
  YYSYMBOL_value = 100,                    /* value  */
  YYSYMBOL_delete = 101,                   /* delete  */
  YYSYMBOL_update = 102,                   /* update  */
  YYSYMBOL_select = 103,                   /* select  */
  YYSYMBOL_select_query = 104,             /* select_query  */
  YYSYMBOL_select_attr = 105,              /* select_attr  */
  YYSYMBOL_aggregate_attr = 106,           /* aggregate_attr  */
  YYSYMBOL_aggregation_field_attr = 107,   /* aggregation_field_attr  */
  YYSYMBOL_aggregate_op = 108,             /* aggregate_op  */
  YYSYMBOL_aggregate_attr_list = 109,      /* aggregate_attr_list  */
  YYSYMBOL_attr_list = 110,                /* attr_list  */
  YYSYMBOL_rel_list = 111,                 /* rel_list  */
  YYSYMBOL_on_list = 112,                  /* on_list  */
  YYSYMBOL_where = 113,                    /* where  */
  YYSYMBOL_order = 114,                    /* order  */
  YYSYMBOL_order_attr = 115,               /* order_attr  */
  YYSYMBOL_order_attr_list = 116,          /* order_attr_list  */
  YYSYMBOL_asc = 117,                      /* asc  */
  YYSYMBOL_condition_list = 118,           /* condition_list  */
  YYSYMBOL_condition = 119,                /* condition  */
  YYSYMBOL_sub_query = 120,                /* sub_query  */
  YYSYMBOL_N = 121,                        /* N  */
  YYSYMBOL_comOp = 122,                    /* comOp  */
  YYSYMBOL_load_data = 123                 /* load_data  */
=======
#line 147 "yacc_sql.y"

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
	char *position;

#line 279 "yacc_sql.tab.c"

>>>>>>> updatesel
};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void *scanner);

#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
<<<<<<< HEAD
#define YYLAST   282
=======
#define YYLAST   265
>>>>>>> updatesel

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  72
/* YYNNTS -- Number of nonterminals.  */
<<<<<<< HEAD
#define YYNNTS  52
/* YYNRULES -- Number of rules.  */
#define YYNRULES  142
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  287

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   326
=======
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  133
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  265

#define YYUNDEFTOK  2
#define YYMAXUTOK   323
>>>>>>> updatesel


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   175,   175,   177,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   202,   207,   212,   218,   224,   230,   236,   242,
     248,   255,   262,   268,   270,   282,   284,   289,   296,   305,
     307,   311,   322,   333,   344,   357,   360,   361,   362,   363,
     364,   367,   374,   375,   381,   399,   404,   406,   409,   411,
<<<<<<< HEAD
     416,   421,   426,   432,   448,   455,   465,   476,   479,   499,
     504,   509,   514,   522,   537,   546,   548,   556,   566,   567,
     568,   569,   570,   573,   575,   579,   584,   589,   594,   601,
     603,   610,   617,   623,   628,   630,   633,   638,   640,   644,
     646,   652,   655,   661,   666,   671,   676,   683,   685,   690,
     695,   700,   707,   708,   711,   713,   718,   740,   761,   782,
     805,   827,   849,   869,   878,   887,   897,   907,   915,   922,
     932,   940,   958,   959,   960,   961,   962,   963,   964,   965,
     966,   967,   971
=======
     416,   421,   426,   432,   448,   455,   465,   477,   481,   490,
     492,   496,   499,   519,   524,   529,   534,   542,   557,   566,
     568,   576,   586,   587,   588,   589,   590,   593,   595,   599,
     604,   609,   614,   621,   623,   630,   637,   643,   648,   650,
     653,   658,   660,   664,   666,   670,   672,   677,   699,   720,
     741,   764,   786,   808,   828,   837,   846,   856,   866,   874,
     881,   891,   899,   917,   918,   919,   920,   921,   922,   923,
     924,   925,   926,   930
>>>>>>> updatesel
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
<<<<<<< HEAD
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "TABLE", "TABLES", "INDEX", "SELECT", "DESC", "SHOW", "SYNC",
  "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "TEXT_T", "FLOAT_T",
  "DATE_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE",
  "AND", "SET", "ON", "LOAD", "DATA", "INFILE", "EQ", "LT", "GT", "LE",
  "GE", "NE", "IS", "NULLABLE", "COUNT", "AVG", "MAX", "MIN", "SUM",
  "INNER", "JOIN", "IN", "EXISTS", "LIKE", "NOT", "UNIQUE", "ORDER", "BY",
  "ASC", "NUMBER", "FLOAT", "ID", "PATH", "SSS", "STAR", "STRING_V",
  "DATE_STR", "NULLVALUE", "$accept", "commands", "command", "exit",
  "help", "sync", "begin", "commit", "rollback", "drop_table",
  "show_tables", "show_index", "desc_table", "create_index",
  "unique_option", "index_attr_list", "drop_index", "create_table",
  "attr_def_list", "attr_def", "number", "type", "ID_get", "NONULL",
  "insert", "tuple", "tuple_list", "value_list", "value", "delete",
  "update", "select", "select_query", "select_attr", "aggregate_attr",
  "aggregation_field_attr", "aggregate_op", "aggregate_attr_list",
  "attr_list", "rel_list", "on_list", "where", "order", "order_attr",
  "order_attr_list", "asc", "condition_list", "condition", "sub_query",
  "N", "comOp", "load_data", YY_NULLPTR
=======
  "$end", "error", "$undefined", "SEMICOLON", "CREATE", "DROP", "TABLE",
  "TABLES", "INDEX", "SELECT", "DESC", "SHOW", "SYNC", "INSERT", "DELETE",
  "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN", "TRX_COMMIT",
  "TRX_ROLLBACK", "INT_T", "STRING_T", "TEXT_T", "FLOAT_T", "DATE_T",
  "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "SET",
  "ON", "LOAD", "DATA", "INFILE", "EQ", "LT", "GT", "LE", "GE", "NE", "IS",
  "NULLABLE", "COUNT", "AVG", "MAX", "MIN", "SUM", "INNER", "JOIN", "IN",
  "EXISTS", "LIKE", "NOT", "UNIQUE", "NUMBER", "FLOAT", "ID", "PATH",
  "SSS", "STAR", "STRING_V", "DATE_STR", "NULLVALUE", "$accept",
  "commands", "command", "exit", "help", "sync", "begin", "commit",
  "rollback", "drop_table", "show_tables", "show_index", "desc_table",
  "create_index", "unique_option", "index_attr_list", "drop_index",
  "create_table", "attr_def_list", "attr_def", "number", "type", "ID_get",
  "NONULL", "insert", "tuple", "tuple_list", "value_list", "value",
  "delete", "update", "assign", "assign_list", "select", "select_query",
  "select_attr", "aggregate_attr", "aggregation_field_attr",
  "aggregate_op", "aggregate_attr_list", "attr_list", "rel_list",
  "on_list", "where", "condition_list", "condition", "sub_query", "N",
  "comOp", "load_data", YY_NULLPTR
>>>>>>> updatesel
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323
};
# endif

<<<<<<< HEAD
#define YYPACT_NINF (-248)
=======
#define YYPACT_NINF (-214)
>>>>>>> updatesel

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
<<<<<<< HEAD
    -248,    80,  -248,     5,    33,    70,   -47,    74,    30,    47,
      28,    22,    85,    94,   100,   120,   133,    58,  -248,  -248,
    -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,
    -248,  -248,  -248,  -248,  -248,  -248,   134,  -248,   101,  -248,
     151,   107,   108,  -248,  -248,  -248,  -248,  -248,     1,   147,
     149,   170,   179,   193,   201,   173,  -248,   141,   142,   174,
    -248,  -248,  -248,  -248,  -248,   169,  -248,   194,   146,   209,
     210,   105,    11,  -248,  -248,   150,    93,  -248,    18,  -248,
    -248,   152,   183,   185,   154,   153,   156,   180,  -248,  -248,
       2,   147,   147,   147,    14,     8,   170,   170,   147,   147,
     205,   220,   208,   104,   222,   186,   197,  -248,   211,   177,
     163,    60,  -248,  -248,  -248,  -248,   165,   178,   185,   114,
    -248,  -248,  -248,  -248,  -248,  -248,  -248,   127,   213,   217,
     181,  -248,  -248,    69,  -248,  -248,  -248,   106,   200,  -248,
     127,   229,   156,   219,  -248,  -248,  -248,  -248,  -248,    -4,
     223,   147,   147,    14,   175,   182,   170,   170,   225,   208,
     235,  -248,  -248,   217,   176,  -248,  -248,  -248,  -248,  -248,
    -248,   187,   228,  -248,    77,   113,   189,   122,   104,  -248,
     185,   184,   211,   244,   188,  -248,   190,  -248,   191,  -248,
    -248,  -248,   212,   192,  -248,  -248,  -248,   127,   233,   213,
    -248,   243,  -248,   106,  -248,   127,  -248,   238,  -248,  -248,
    -248,   226,  -248,   200,   254,   255,  -248,  -248,  -248,   242,
    -248,   245,   104,    14,   195,   225,  -248,  -248,   247,    -8,
     225,   127,  -248,   202,  -248,  -248,  -248,   -20,   203,   248,
     200,  -248,    -1,  -248,  -248,  -248,   237,  -248,  -248,   252,
     225,  -248,  -248,  -248,   245,   259,  -248,   253,   207,  -248,
     253,   214,  -248,   256,  -248,  -248,   215,  -248,    12,  -248,
    -248,  -248,     7,   253,   253,   253,   216,   253,  -248,  -248,
    -248,    13,  -248,   253,   253,  -248,  -248
=======
    -214,   108,  -214,     2,   140,    82,   -39,    35,    29,    30,
      45,    18,    88,    92,    96,   103,   112,    78,  -214,  -214,
    -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,
    -214,  -214,  -214,  -214,  -214,  -214,   121,  -214,    63,  -214,
     142,    91,   105,  -214,  -214,  -214,  -214,  -214,    -1,   138,
     133,   150,   156,   170,   175,   153,  -214,   124,   132,   160,
    -214,  -214,  -214,  -214,  -214,   157,  -214,   181,   136,   196,
     197,    16,   -38,  -214,  -214,   139,   109,  -214,   -28,  -214,
    -214,   141,   171,   172,   144,   143,   146,   168,  -214,  -214,
       0,   138,   138,   138,    -4,     1,   150,   150,   138,   138,
     192,   207,   195,    36,   209,   173,   198,   184,  -214,   199,
     167,   158,   -21,  -214,  -214,  -214,  -214,   159,   161,   172,
      49,  -214,  -214,  -214,  -214,  -214,  -214,  -214,   120,   200,
     203,   166,  -214,  -214,    97,  -214,  -214,  -214,    44,   189,
    -214,    15,   144,   172,   218,   146,   208,  -214,  -214,  -214,
    -214,  -214,    -7,   210,   138,   138,    -4,   165,  -214,   150,
     150,   211,   195,   225,  -214,  -214,   203,   169,  -214,  -214,
    -214,  -214,  -214,  -214,   174,   214,  -214,    94,   102,   176,
     115,    36,  -214,  -214,  -214,   198,   231,   177,   199,   232,
     178,  -214,   179,  -214,   180,  -214,  -214,  -214,   201,  -214,
    -214,   120,   219,   200,  -214,   234,  -214,    44,  -214,   120,
    -214,   224,  -214,  -214,  -214,   212,  -214,   189,  -214,  -214,
     241,  -214,  -214,  -214,   228,  -214,   230,    36,    -4,   211,
    -214,  -214,   229,    -5,   211,   120,  -214,   187,  -214,  -214,
     -25,   188,   235,   189,  -214,  -214,  -214,   222,  -214,  -214,
     236,   211,  -214,  -214,  -214,   230,   251,  -214,   193,  -214,
     239,  -214,  -214,  -214,  -214
>>>>>>> updatesel
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,    33,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    21,
      20,    15,    16,    17,    18,     9,    10,    11,    12,    13,
      14,     8,     5,     7,     6,     4,     0,    19,     0,    34,
<<<<<<< HEAD
       0,     0,     0,    78,    79,    80,    81,    82,    89,    89,
       0,    83,     0,     0,     0,     0,    24,     0,     0,     0,
      25,    26,    27,    23,    22,     0,    67,     0,     0,     0,
       0,     0,     0,    70,    69,     0,     0,    73,    75,    31,
      29,     0,     0,    99,     0,     0,     0,     0,    28,    37,
      89,    89,    89,    89,    94,    83,    83,    83,    89,    89,
       0,     0,     0,     0,     0,     0,     0,    51,    39,     0,
       0,     0,    90,    93,    71,    72,     0,     0,    99,     0,
      86,    85,    84,    77,    76,    74,    30,     0,    56,     0,
       0,    60,    61,     0,    62,    63,    64,     0,   114,    65,
       0,     0,     0,     0,    46,    47,    48,    49,    50,    52,
       0,    89,    89,    94,     0,   101,    83,    83,    58,     0,
       0,   131,   128,     0,     0,   132,   133,   134,   135,   136,
     137,   138,     0,   140,     0,     0,     0,     0,     0,   100,
      99,     0,    39,     0,     0,    44,     0,    43,     0,    91,
      92,    95,    97,     0,    68,    87,    88,     0,     0,    56,
      54,     0,   129,     0,   139,   131,   123,     0,   141,   118,
     116,   119,   117,   114,     0,     0,    40,    38,    45,     0,
      53,    35,     0,    94,     0,    58,    55,    57,     0,     0,
      58,   131,   124,     0,   115,    66,   142,    52,     0,     0,
     114,    96,   112,   102,    59,   130,     0,   120,   127,     0,
      58,   121,    42,    41,    35,     0,    98,   107,     0,   113,
     107,     0,   125,     0,    36,    32,     0,   105,   112,   103,
     122,   126,   112,   107,   107,   107,     0,   107,   106,   104,
     109,   112,   108,   107,   107,   111,   110
=======
       0,     0,     0,    82,    83,    84,    85,    86,    93,    93,
       0,    87,     0,     0,     0,     0,    24,     0,     0,     0,
      25,    26,    27,    23,    22,     0,    71,     0,     0,     0,
       0,     0,     0,    74,    73,     0,     0,    77,    79,    31,
      29,     0,     0,   103,     0,     0,     0,     0,    28,    37,
      93,    93,    93,    93,    98,    87,    87,    87,    93,    93,
       0,     0,     0,     0,     0,     0,    69,     0,    51,    39,
       0,     0,     0,    94,    97,    75,    76,     0,     0,   103,
       0,    90,    89,    88,    81,    80,    78,    30,     0,    56,
       0,     0,    60,    61,     0,    62,    63,    64,     0,   105,
      65,     0,     0,   103,     0,     0,     0,    46,    47,    48,
      49,    50,    52,     0,    93,    93,    98,     0,    72,    87,
      87,    58,     0,     0,   122,   119,     0,     0,   123,   124,
     125,   126,   127,   128,   129,     0,   131,     0,     0,     0,
       0,     0,   104,    67,    68,    69,     0,     0,    39,     0,
       0,    44,     0,    43,     0,    95,    96,    99,   101,    91,
      92,     0,     0,    56,    54,     0,   120,     0,   130,   122,
     114,     0,   132,   109,   107,   110,   108,   105,    70,    66,
       0,    40,    38,    45,     0,    53,    35,     0,    98,    58,
      55,    57,     0,     0,    58,   122,   115,     0,   106,   133,
      52,     0,     0,   105,   100,    59,   121,     0,   111,   118,
       0,    58,   112,    42,    41,    35,     0,   102,     0,   116,
       0,    36,    32,   113,   117
>>>>>>> updatesel
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
<<<<<<< HEAD
    -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,
    -248,  -248,  -248,  -248,  -248,    16,  -248,  -248,    92,   135,
    -248,  -248,  -248,    38,  -248,   117,    79,  -201,  -127,  -248,
    -248,  -248,    81,  -248,   -36,  -248,  -248,   -91,   -46,  -152,
    -248,  -108,  -248,  -248,  -144,  -247,  -198,  -164,  -156,  -248,
    -135,  -248
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    40,   239,    30,    31,   143,   108,
     219,   149,   109,   187,    32,   128,   160,   198,   137,    33,
      34,    35,    36,    50,    51,   100,    52,    77,    73,   118,
     223,   104,   194,   243,   267,   260,   179,   138,   162,   201,
     175,    37
=======
    -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,
    -214,  -214,  -214,  -214,  -214,     3,  -214,  -214,    69,   114,
    -214,  -214,  -214,    20,  -214,    99,    59,  -213,  -128,  -214,
    -214,   122,    80,  -214,    58,  -214,   -51,  -214,  -214,   -90,
     -45,  -154,  -214,  -104,  -207,  -169,  -140,  -214,  -135,  -214
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    40,   242,    30,    31,   146,   109,
     224,   152,   110,   193,    32,   129,   163,   202,   138,    33,
      34,   106,   143,    35,    36,    50,    51,   100,    52,    77,
      73,   119,   228,   104,   182,   139,   165,   205,   178,    37
>>>>>>> updatesel
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
<<<<<<< HEAD
     158,   191,   177,    74,   120,   121,   122,   202,   161,   257,
     155,    38,   184,   180,   213,   234,   206,   275,    53,    71,
      71,   274,   273,   283,   244,   277,    76,   252,   258,   249,
      72,   111,   116,    56,   284,    91,   276,   119,   186,    41,
      97,    42,   256,   185,   112,   113,   114,   115,   210,   263,
     212,   232,   123,   124,   186,   131,   132,   246,   240,   134,
      58,   259,   135,   136,    39,   195,   196,   117,   229,   259,
     225,   241,   214,   248,   259,   259,    92,    57,   230,    93,
       2,    54,    55,    98,     3,     4,    99,    59,    60,     5,
       6,     7,     8,     9,    10,    11,    65,    61,   164,    12,
      13,    14,   247,    62,   250,   189,   190,    15,    16,   165,
     166,   167,   168,   169,   170,   171,   269,    17,    43,    44,
      45,    46,    47,    63,   172,   151,   173,   174,   152,   278,
     279,   280,   207,   282,   208,    48,    64,    66,    49,   285,
     286,    43,    44,    45,    46,    47,   165,   166,   167,   168,
     169,   170,   171,    43,    44,    45,    46,    47,    95,    68,
     129,    96,   130,   173,   176,    71,    67,   131,   132,   133,
      90,   134,    69,    70,   135,   136,   131,   132,   209,   156,
     134,    75,   157,   135,   136,   131,   132,   211,    76,   134,
     131,   132,   135,   136,   134,    78,    79,   135,   136,   144,
     145,   146,   147,   148,    80,    81,    82,    83,    85,    84,
      86,    87,    88,    89,   102,    94,   110,   101,   103,   105,
     106,   107,   125,   126,   127,   139,   140,   141,   150,   142,
     153,   159,   154,   161,   178,   181,   183,   163,   200,   188,
     192,   203,   193,   197,   205,   204,   208,   217,   222,   215,
     226,   218,     5,   224,   231,   233,   221,   235,   236,   237,
     242,   220,   265,   238,   245,   255,   261,   251,   254,   262,
     264,   266,   268,   271,   216,   253,   199,   182,   227,   270,
     272,   281,   228
=======
     161,   184,   197,   180,    74,   121,   122,   123,    38,   190,
     238,   164,   217,   183,   117,   158,   245,    71,    71,    76,
      91,   250,   253,    53,    92,    97,   206,    93,    72,   112,
     120,   164,    56,   192,    98,   210,   257,    99,   260,   186,
     191,   154,    54,    55,   155,   113,   114,   115,   116,   118,
     214,   192,   216,   124,   125,   132,   133,   247,   243,   135,
      57,    39,   136,   137,    43,    44,    45,    46,    47,   199,
     200,   236,   233,   229,   244,   132,   133,    58,    90,   135,
      59,   234,   136,   137,   168,   169,   170,   171,   172,   173,
     174,    60,   130,   249,   131,    61,   132,   133,   134,    62,
     135,   176,   179,   136,   137,   248,    63,   251,     2,   195,
     196,   159,     3,     4,   160,    64,    65,     5,     6,     7,
       8,     9,    10,    11,    66,    67,   167,    12,    13,    14,
      43,    44,    45,    46,    47,    15,    16,   168,   169,   170,
     171,   172,   173,   174,    48,    17,    41,    49,    42,   211,
      68,   212,   175,    69,   176,   177,    71,    43,    44,    45,
      46,    47,   132,   133,   213,    75,   135,    70,    76,   136,
     137,    95,    78,    79,    96,   132,   133,   215,    80,   135,
     132,   133,   136,   137,   135,    81,    82,   136,   137,   147,
     148,   149,   150,   151,    83,    84,    85,    86,    87,    88,
      89,    94,   102,   101,   111,   103,   105,   107,   108,   126,
     127,   128,   140,   141,   144,   157,   142,   145,   162,   164,
     153,   156,   166,   181,   187,   189,   194,   198,   204,   201,
     209,   207,   208,   212,   219,   222,   230,   227,   223,   220,
     235,   237,   226,     5,   239,   240,   246,   225,   241,   252,
     255,   258,   256,   259,   262,   263,   264,   221,   261,   188,
     254,   203,   231,   232,   185,   218
>>>>>>> updatesel
};

static const yytype_int16 yycheck[] =
{
<<<<<<< HEAD
     127,   153,   137,    49,    95,    96,    97,   163,    16,    10,
     118,     6,    16,   140,   178,   213,   172,    10,    65,    18,
      18,   268,    10,    10,   225,   272,    18,    47,    29,   230,
      29,    29,    18,     3,   281,    71,    29,    29,    58,     6,
      76,     8,   240,    47,    90,    91,    92,    93,   175,   250,
     177,   207,    98,    99,    58,    63,    64,    65,   222,    67,
      32,    62,    70,    71,    59,   156,   157,    53,   203,    62,
     197,   223,   180,   229,    62,    62,    65,    30,   205,    68,
       0,     7,     8,    65,     4,     5,    68,    65,     3,     9,
      10,    11,    12,    13,    14,    15,    38,     3,    29,    19,
      20,    21,   229,     3,   231,   151,   152,    27,    28,    40,
      41,    42,    43,    44,    45,    46,   260,    37,    48,    49,
      50,    51,    52,     3,    55,    65,    57,    58,    68,   273,
     274,   275,    55,   277,    57,    65,     3,     3,    68,   283,
     284,    48,    49,    50,    51,    52,    40,    41,    42,    43,
      44,    45,    46,    48,    49,    50,    51,    52,    65,     8,
      56,    68,    58,    57,    58,    18,    65,    63,    64,    65,
      65,    67,    65,    65,    70,    71,    63,    64,    65,    65,
      67,    32,    68,    70,    71,    63,    64,    65,    18,    67,
      63,    64,    70,    71,    67,    16,     3,    70,    71,    22,
      23,    24,    25,    26,     3,    32,    65,    65,    39,    35,
      16,    65,     3,     3,    31,    65,    36,    65,    33,    65,
      67,    65,    17,     3,    16,     3,    40,    30,    65,    18,
      65,    18,    54,    16,    34,     6,    17,    56,     3,    16,
      65,    65,    60,    18,    16,    58,    57,     3,    36,    65,
      17,    63,     9,    61,    16,    29,    65,     3,     3,    17,
      65,    71,     3,    18,    17,    17,    29,    65,    65,    17,
     254,    18,    65,    17,   182,   237,   159,   142,   199,    65,
      65,    65,   201
=======
     128,   141,   156,   138,    49,    95,    96,    97,     6,    16,
     217,    16,   181,   141,    18,   119,   229,    18,    18,    18,
      71,   234,    47,    62,    62,    76,   166,    65,    29,    29,
      29,    16,     3,    58,    62,   175,   243,    65,   251,   143,
      47,    62,     7,     8,    65,    90,    91,    92,    93,    53,
     178,    58,   180,    98,    99,    60,    61,    62,   227,    64,
      30,    59,    67,    68,    48,    49,    50,    51,    52,   159,
     160,   211,   207,   201,   228,    60,    61,    32,    62,    64,
      62,   209,    67,    68,    40,    41,    42,    43,    44,    45,
      46,     3,    56,   233,    58,     3,    60,    61,    62,     3,
      64,    57,    58,    67,    68,   233,     3,   235,     0,   154,
     155,    62,     4,     5,    65,     3,    38,     9,    10,    11,
      12,    13,    14,    15,     3,    62,    29,    19,    20,    21,
      48,    49,    50,    51,    52,    27,    28,    40,    41,    42,
      43,    44,    45,    46,    62,    37,     6,    65,     8,    55,
       8,    57,    55,    62,    57,    58,    18,    48,    49,    50,
      51,    52,    60,    61,    62,    32,    64,    62,    18,    67,
      68,    62,    16,     3,    65,    60,    61,    62,     3,    64,
      60,    61,    67,    68,    64,    32,    62,    67,    68,    22,
      23,    24,    25,    26,    62,    35,    39,    16,    62,     3,
       3,    62,    31,    62,    36,    33,    62,    64,    62,    17,
       3,    16,     3,    40,    30,    54,    18,    18,    18,    16,
      62,    62,    56,    34,     6,    17,    16,    62,     3,    18,
      16,    62,    58,    57,     3,     3,    17,    36,    60,    62,
      16,    29,    62,     9,     3,    17,    17,    68,    18,    62,
      62,    29,    17,    17,     3,    62,    17,   188,   255,   145,
     240,   162,   203,   205,   142,   185
>>>>>>> updatesel
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
<<<<<<< HEAD
       0,    73,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    19,    20,    21,    27,    28,    37,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      88,    89,    96,   101,   102,   103,   104,   123,     6,    59,
      86,     6,     8,    48,    49,    50,    51,    52,    65,    68,
     105,   106,   108,    65,     7,     8,     3,    30,    32,    65,
       3,     3,     3,     3,     3,    38,     3,    65,     8,    65,
      65,    18,    29,   110,   110,    32,    18,   109,    16,     3,
       3,    32,    65,    65,    35,    39,    16,    65,     3,     3,
      65,   106,    65,    68,    65,    65,    68,   106,    65,    68,
     107,    65,    31,    33,   113,    65,    67,    65,    91,    94,
      36,    29,   110,   110,   110,   110,    18,    53,   111,    29,
     109,   109,   109,   110,   110,    17,     3,    16,    97,    56,
      58,    63,    64,    65,    67,    70,    71,   100,   119,     3,
      40,    30,    18,    90,    22,    23,    24,    25,    26,    93,
      65,    65,    68,    65,    54,   113,    65,    68,   100,    18,
      98,    16,   120,    56,    29,    40,    41,    42,    43,    44,
      45,    46,    55,    57,    58,   122,    58,   122,    34,   118,
     100,     6,    91,    17,    16,    47,    58,    95,    16,   110,
     110,   111,    65,    60,   114,   109,   109,    18,    99,    97,
       3,   121,   120,    65,    58,    16,   120,    55,    57,    65,
     100,    65,   100,   119,   113,    65,    90,     3,    63,    92,
      71,    65,    36,   112,    61,   100,    17,    98,   104,   122,
     100,    16,   120,    29,   118,     3,     3,    17,    18,    87,
     119,   111,    65,   115,    99,    17,    65,   100,   120,    99,
     100,    65,    47,    95,    65,    17,   118,    10,    29,    62,
     117,    29,    17,    99,    87,     3,    18,   116,    65,   116,
      65,    17,    65,    10,   117,    10,    29,   117,   116,   116,
     116,    65,   116,    10,   117,   116,   116
=======
       0,    70,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    19,    20,    21,    27,    28,    37,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      85,    86,    93,    98,    99,   102,   103,   118,     6,    59,
      83,     6,     8,    48,    49,    50,    51,    52,    62,    65,
     104,   105,   107,    62,     7,     8,     3,    30,    32,    62,
       3,     3,     3,     3,     3,    38,     3,    62,     8,    62,
      62,    18,    29,   109,   109,    32,    18,   108,    16,     3,
       3,    32,    62,    62,    35,    39,    16,    62,     3,     3,
      62,   105,    62,    65,    62,    62,    65,   105,    62,    65,
     106,    62,    31,    33,   112,    62,   100,    64,    62,    88,
      91,    36,    29,   109,   109,   109,   109,    18,    53,   110,
      29,   108,   108,   108,   109,   109,    17,     3,    16,    94,
      56,    58,    60,    61,    62,    64,    67,    68,    97,   114,
       3,    40,    18,   101,    30,    18,    87,    22,    23,    24,
      25,    26,    90,    62,    62,    65,    62,    54,   112,    62,
      65,    97,    18,    95,    16,   115,    56,    29,    40,    41,
      42,    43,    44,    45,    46,    55,    57,    58,   117,    58,
     117,    34,   113,    97,   115,   100,   112,     6,    88,    17,
      16,    47,    58,    92,    16,   109,   109,   110,    62,   108,
     108,    18,    96,    94,     3,   116,   115,    62,    58,    16,
     115,    55,    57,    62,    97,    62,    97,   114,   101,     3,
      62,    87,     3,    60,    89,    68,    62,    36,   111,    97,
      17,    95,   103,   117,    97,    16,   115,    29,   113,     3,
      17,    18,    84,   114,   110,    96,    17,    62,    97,   115,
      96,    97,    62,    47,    92,    62,    17,   113,    29,    17,
      96,    84,     3,    62,    17
>>>>>>> updatesel
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
<<<<<<< HEAD
       0,    72,    73,    73,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    86,    87,    87,    88,    89,    90,
      90,    91,    91,    91,    91,    92,    93,    93,    93,    93,
      93,    94,    95,    95,    96,    97,    98,    98,    99,    99,
     100,   100,   100,   100,   100,   101,   102,   103,   104,   105,
     105,   105,   105,   105,   106,   107,   107,   107,   108,   108,
     108,   108,   108,   109,   109,   109,   109,   109,   109,   110,
     110,   110,   110,   110,   111,   111,   111,   112,   112,   113,
     113,   114,   114,   115,   115,   115,   115,   116,   116,   116,
     116,   116,   117,   117,   118,   118,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     120,   121,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   123
=======
       0,    69,    70,    70,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    83,    84,    84,    85,    86,    87,
      87,    88,    88,    88,    88,    89,    90,    90,    90,    90,
      90,    91,    92,    92,    93,    94,    95,    95,    96,    96,
      97,    97,    97,    97,    97,    98,    99,   100,   100,   101,
     101,   102,   103,   104,   104,   104,   104,   104,   105,   106,
     106,   106,   107,   107,   107,   107,   107,   108,   108,   108,
     108,   108,   108,   109,   109,   109,   109,   109,   110,   110,
     110,   111,   111,   112,   112,   113,   113,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   115,   116,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   118
>>>>>>> updatesel
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     4,     3,
       5,     3,    11,     0,     1,     0,     3,     4,     8,     0,
       3,     6,     6,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     2,     7,     4,     0,     3,     0,     3,
<<<<<<< HEAD
       1,     1,     1,     1,     1,     5,     8,     2,     7,     2,
       2,     4,     4,     2,     4,     0,     2,     2,     1,     1,
       1,     1,     1,     0,     3,     3,     3,     5,     5,     0,
       3,     5,     5,     3,     0,     3,     5,     0,     3,     0,
       3,     0,     3,     3,     5,     3,     5,     0,     4,     4,
       6,     6,     0,     1,     0,     3,     3,     3,     3,     3,
       5,     5,     7,     3,     4,     6,     7,     5,     2,     3,
       4,     0,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     2,     8
=======
       1,     1,     1,     1,     1,     5,     7,     3,     3,     0,
       3,     2,     6,     2,     2,     4,     4,     2,     4,     0,
       2,     2,     1,     1,     1,     1,     1,     0,     3,     3,
       3,     5,     5,     0,     3,     5,     5,     3,     0,     3,
       5,     0,     3,     0,     3,     0,     3,     3,     3,     3,
       3,     5,     5,     7,     3,     4,     6,     7,     5,     2,
       3,     4,     0,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     2,     8
>>>>>>> updatesel
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule, void *scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              , scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, void *scanner)
{
  YYUSE (yyvaluep);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
<<<<<<< HEAD
  case 22: /* exit: EXIT SEMICOLON  */
=======
  case 22:
>>>>>>> updatesel
#line 202 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
<<<<<<< HEAD
#line 1468 "yacc_sql.tab.c"
    break;

  case 23: /* help: HELP SEMICOLON  */
=======
#line 1655 "yacc_sql.tab.c"
    break;

  case 23:
>>>>>>> updatesel
#line 207 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
<<<<<<< HEAD
#line 1476 "yacc_sql.tab.c"
    break;

  case 24: /* sync: SYNC SEMICOLON  */
=======
#line 1663 "yacc_sql.tab.c"
    break;

  case 24:
>>>>>>> updatesel
#line 212 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
<<<<<<< HEAD
#line 1484 "yacc_sql.tab.c"
    break;

  case 25: /* begin: TRX_BEGIN SEMICOLON  */
=======
#line 1671 "yacc_sql.tab.c"
    break;

  case 25:
>>>>>>> updatesel
#line 218 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
<<<<<<< HEAD
#line 1492 "yacc_sql.tab.c"
    break;

  case 26: /* commit: TRX_COMMIT SEMICOLON  */
=======
#line 1679 "yacc_sql.tab.c"
    break;

  case 26:
>>>>>>> updatesel
#line 224 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
<<<<<<< HEAD
#line 1500 "yacc_sql.tab.c"
    break;

  case 27: /* rollback: TRX_ROLLBACK SEMICOLON  */
=======
#line 1687 "yacc_sql.tab.c"
    break;

  case 27:
>>>>>>> updatesel
#line 230 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
<<<<<<< HEAD
#line 1508 "yacc_sql.tab.c"
    break;

  case 28: /* drop_table: DROP TABLE ID SEMICOLON  */
=======
#line 1695 "yacc_sql.tab.c"
    break;

  case 28:
>>>>>>> updatesel
#line 236 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
<<<<<<< HEAD
#line 1517 "yacc_sql.tab.c"
    break;

  case 29: /* show_tables: SHOW TABLES SEMICOLON  */
=======
#line 1704 "yacc_sql.tab.c"
    break;

  case 29:
>>>>>>> updatesel
#line 242 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
<<<<<<< HEAD
#line 1525 "yacc_sql.tab.c"
    break;

  case 30: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
=======
#line 1712 "yacc_sql.tab.c"
    break;

  case 30:
>>>>>>> updatesel
#line 248 "yacc_sql.y"
                                     {
		CONTEXT->ssql->flag = SCF_SHOW_INDEX;
		show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
	}
<<<<<<< HEAD
#line 1534 "yacc_sql.tab.c"
    break;

  case 31: /* desc_table: DESC ID SEMICOLON  */
=======
#line 1721 "yacc_sql.tab.c"
    break;

  case 31:
>>>>>>> updatesel
#line 255 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
<<<<<<< HEAD
#line 1543 "yacc_sql.tab.c"
    break;

  case 32: /* create_index: CREATE unique_option INDEX ID ON ID LBRACE ID index_attr_list RBRACE SEMICOLON  */
=======
#line 1730 "yacc_sql.tab.c"
    break;

  case 32:
>>>>>>> updatesel
#line 263 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), (yyvsp[-3].string), CONTEXT->unique);
		}
<<<<<<< HEAD
#line 1552 "yacc_sql.tab.c"
    break;

  case 34: /* unique_option: UNIQUE  */
=======
#line 1739 "yacc_sql.tab.c"
    break;

  case 34:
>>>>>>> updatesel
#line 270 "yacc_sql.y"
                 {
		CONTEXT->unique = 1;
	}
<<<<<<< HEAD
#line 1560 "yacc_sql.tab.c"
    break;

  case 36: /* index_attr_list: COMMA ID index_attr_list  */
=======
#line 1747 "yacc_sql.tab.c"
    break;

  case 36:
>>>>>>> updatesel
#line 284 "yacc_sql.y"
                                   {
		create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[-1].string));
	}
<<<<<<< HEAD
#line 1568 "yacc_sql.tab.c"
    break;

  case 37: /* drop_index: DROP INDEX ID SEMICOLON  */
=======
#line 1755 "yacc_sql.tab.c"
    break;

  case 37:
>>>>>>> updatesel
#line 290 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
<<<<<<< HEAD
#line 1577 "yacc_sql.tab.c"
    break;

  case 38: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
=======
#line 1764 "yacc_sql.tab.c"
    break;

  case 38:
>>>>>>> updatesel
#line 297 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
<<<<<<< HEAD
#line 1589 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 307 "yacc_sql.y"
                                   {    }
#line 1595 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def: ID_get type LBRACE number RBRACE NONULL  */
=======
#line 1776 "yacc_sql.tab.c"
    break;

  case 40:
#line 307 "yacc_sql.y"
                                   {    }
#line 1782 "yacc_sql.tab.c"
    break;

  case 41:
>>>>>>> updatesel
#line 312 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-4].number), (yyvsp[-2].number), 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
<<<<<<< HEAD
#line 1610 "yacc_sql.tab.c"
    break;

  case 42: /* attr_def: ID_get type LBRACE number RBRACE NULLABLE  */
=======
#line 1797 "yacc_sql.tab.c"
    break;

  case 42:
>>>>>>> updatesel
#line 323 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-4].number), (yyvsp[-2].number), 1);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
<<<<<<< HEAD
#line 1625 "yacc_sql.tab.c"
    break;

  case 43: /* attr_def: ID_get type NONULL  */
=======
#line 1812 "yacc_sql.tab.c"
    break;

  case 43:
>>>>>>> updatesel
#line 334 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
<<<<<<< HEAD
#line 1640 "yacc_sql.tab.c"
    break;

  case 44: /* attr_def: ID_get type NULLABLE  */
=======
#line 1827 "yacc_sql.tab.c"
    break;

  case 44:
>>>>>>> updatesel
#line 345 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, 1);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
<<<<<<< HEAD
#line 1655 "yacc_sql.tab.c"
    break;

  case 45: /* number: NUMBER  */
#line 357 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1661 "yacc_sql.tab.c"
    break;

  case 46: /* type: INT_T  */
#line 360 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1667 "yacc_sql.tab.c"
    break;

  case 47: /* type: STRING_T  */
#line 361 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1673 "yacc_sql.tab.c"
    break;

  case 48: /* type: TEXT_T  */
#line 362 "yacc_sql.y"
                    {(yyval.number)=TEXTS; }
#line 1679 "yacc_sql.tab.c"
    break;

  case 49: /* type: FLOAT_T  */
#line 363 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1685 "yacc_sql.tab.c"
    break;

  case 50: /* type: DATE_T  */
#line 364 "yacc_sql.y"
                    {(yyval.number)=DATES;}
#line 1691 "yacc_sql.tab.c"
    break;

  case 51: /* ID_get: ID  */
=======
#line 1842 "yacc_sql.tab.c"
    break;

  case 45:
#line 357 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1848 "yacc_sql.tab.c"
    break;

  case 46:
#line 360 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1854 "yacc_sql.tab.c"
    break;

  case 47:
#line 361 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1860 "yacc_sql.tab.c"
    break;

  case 48:
#line 362 "yacc_sql.y"
                    {(yyval.number)=TEXTS; }
#line 1866 "yacc_sql.tab.c"
    break;

  case 49:
#line 363 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1872 "yacc_sql.tab.c"
    break;

  case 50:
#line 364 "yacc_sql.y"
                    {(yyval.number)=DATES;}
#line 1878 "yacc_sql.tab.c"
    break;

  case 51:
>>>>>>> updatesel
#line 368 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
<<<<<<< HEAD
#line 1700 "yacc_sql.tab.c"
    break;

  case 54: /* insert: INSERT INTO ID VALUES tuple tuple_list SEMICOLON  */
=======
#line 1887 "yacc_sql.tab.c"
    break;

  case 54:
>>>>>>> updatesel
#line 382 "yacc_sql.y"
                {
			// CONTEXT->values[CONTEXT->value_length++] = *$6;

			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			// CONTEXT->ssql->sstr.insertion.relation_name = $3;
			// CONTEXT->ssql->sstr.insertion.value_num = CONTEXT->value_length;
			// for(i = 0; i < CONTEXT->value_length; i++){
			// 	CONTEXT->ssql->sstr.insertion.values[i] = CONTEXT->values[i];
      // }
			// inserts_init(&CONTEXT->ssql->sstr.insertion, $3, CONTEXT->values, CONTEXT->value_length);
			inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string), CONTEXT->tuples, CONTEXT->tuple_num, CONTEXT->value_num);

      //临时变量清零
	  CONTEXT->tuple_num = 0;
    }
<<<<<<< HEAD
#line 1720 "yacc_sql.tab.c"
    break;

  case 55: /* tuple: LBRACE value value_list RBRACE  */
=======
#line 1907 "yacc_sql.tab.c"
    break;

  case 55:
>>>>>>> updatesel
#line 399 "yacc_sql.y"
                                       {
		CONTEXT->tuple_num++;
		printf("yacc: tuple num %d\n", CONTEXT->tuple_num);
	}
<<<<<<< HEAD
#line 1729 "yacc_sql.tab.c"
    break;

  case 57: /* tuple_list: COMMA tuple tuple_list  */
#line 406 "yacc_sql.y"
                                 {
	}
#line 1736 "yacc_sql.tab.c"
    break;

  case 59: /* value_list: COMMA value value_list  */
=======
#line 1916 "yacc_sql.tab.c"
    break;

  case 57:
#line 406 "yacc_sql.y"
                                 {
	}
#line 1923 "yacc_sql.tab.c"
    break;

  case 59:
>>>>>>> updatesel
#line 411 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
<<<<<<< HEAD
#line 1744 "yacc_sql.tab.c"
    break;

  case 60: /* value: NUMBER  */
=======
#line 1931 "yacc_sql.tab.c"
    break;

  case 60:
>>>>>>> updatesel
#line 416 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
  		value_init_integer(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], (yyvsp[0].number));
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
<<<<<<< HEAD
#line 1754 "yacc_sql.tab.c"
    break;

  case 61: /* value: FLOAT  */
=======
#line 1941 "yacc_sql.tab.c"
    break;

  case 61:
>>>>>>> updatesel
#line 421 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		value_init_float(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], (yyvsp[0].floats));
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
<<<<<<< HEAD
#line 1764 "yacc_sql.tab.c"
    break;

  case 62: /* value: SSS  */
=======
#line 1951 "yacc_sql.tab.c"
    break;

  case 62:
>>>>>>> updatesel
#line 426 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		value_init_string(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], (yyvsp[0].string));
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
<<<<<<< HEAD
#line 1775 "yacc_sql.tab.c"
    break;

  case 63: /* value: DATE_STR  */
=======
#line 1962 "yacc_sql.tab.c"
    break;

  case 63:
>>>>>>> updatesel
#line 432 "yacc_sql.y"
                  {
		(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		// CONTEXT->value_length += value_init_date(&CONTEXT->values[CONTEXT->value_length], $1);
		// if (value_init_date(&CONTEXT->values[CONTEXT->value_length++], $1) == 0) {
		// 	CONTEXT->value_length -= 1;
		// 	CONTEXT->ssql->flag = SCF_INVALID_DATE;
		// 	return 0;
		// }
		if (value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string)) == 0 ||
  			value_init_date(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], (yyvsp[0].string)) == 0) {
			CONTEXT->value_length -= 1;
			CONTEXT->value_num[CONTEXT->tuple_num] -= 1;
			CONTEXT->ssql->flag = SCF_INVALID_DATE;
			return 0;
		}
	}
<<<<<<< HEAD
#line 1796 "yacc_sql.tab.c"
    break;

  case 64: /* value: NULLVALUE  */
=======
#line 1983 "yacc_sql.tab.c"
    break;

  case 64:
>>>>>>> updatesel
#line 448 "yacc_sql.y"
                   {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
		value_init_null(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++]);
	}
<<<<<<< HEAD
#line 1805 "yacc_sql.tab.c"
    break;

  case 65: /* delete: DELETE FROM ID where SEMICOLON  */
=======
#line 1992 "yacc_sql.tab.c"
    break;

  case 65:
>>>>>>> updatesel
#line 456 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
<<<<<<< HEAD
#line 1817 "yacc_sql.tab.c"
    break;

  case 66: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
=======
#line 2004 "yacc_sql.tab.c"
    break;

  case 66:
>>>>>>> updatesel
#line 466 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-5].string), CONTEXT->attribute_name, CONTEXT->values, CONTEXT->upselect_num,
					CONTEXT->conditions, CONTEXT->condition_length, CONTEXT->upselect_vec);
			CONTEXT->condition_length = 0;
			CONTEXT->value_length = 0;
			CONTEXT->upselect_num = 0;
		}
<<<<<<< HEAD
#line 1829 "yacc_sql.tab.c"
    break;

  case 68: /* select_query: SELECT select_attr FROM ID rel_list where order  */
#line 480 "yacc_sql.y"
=======
#line 2017 "yacc_sql.tab.c"
    break;

  case 67:
#line 477 "yacc_sql.y"
                    {
		CONTEXT->upselect_num++;
		CONTEXT->attribute_name[CONTEXT->value_length - 1] = (yyvsp[-2].string);
	}
#line 2026 "yacc_sql.tab.c"
    break;

  case 68:
#line 481 "yacc_sql.y"
                          {
		CONTEXT->upselect_num++;
		CONTEXT->value_length++;
		CONTEXT->attribute_name[CONTEXT->value_length - 1] = (yyvsp[-2].string);
		CONTEXT->upselect_vec[CONTEXT->value_length - 1] = &CONTEXT->sub_query->sstr.selection;
	}
#line 2037 "yacc_sql.tab.c"
    break;

  case 72:
#line 500 "yacc_sql.y"
>>>>>>> updatesel
                {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-3].string));

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
<<<<<<< HEAD
#line 1850 "yacc_sql.tab.c"
    break;

  case 69: /* select_attr: STAR attr_list  */
#line 499 "yacc_sql.y"
=======
#line 2058 "yacc_sql.tab.c"
    break;

  case 73:
#line 519 "yacc_sql.y"
>>>>>>> updatesel
                   {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
<<<<<<< HEAD
#line 1860 "yacc_sql.tab.c"
    break;

  case 70: /* select_attr: ID attr_list  */
#line 504 "yacc_sql.y"
=======
#line 2068 "yacc_sql.tab.c"
    break;

  case 74:
#line 524 "yacc_sql.y"
>>>>>>> updatesel
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
<<<<<<< HEAD
#line 1870 "yacc_sql.tab.c"
    break;

  case 71: /* select_attr: ID DOT ID attr_list  */
#line 509 "yacc_sql.y"
=======
#line 2078 "yacc_sql.tab.c"
    break;

  case 75:
#line 529 "yacc_sql.y"
>>>>>>> updatesel
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
<<<<<<< HEAD
#line 1880 "yacc_sql.tab.c"
    break;

  case 72: /* select_attr: ID DOT STAR attr_list  */
#line 514 "yacc_sql.y"
=======
#line 2088 "yacc_sql.tab.c"
    break;

  case 76:
#line 534 "yacc_sql.y"
>>>>>>> updatesel
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			// CONTEXT->aggregation_op = NO_AGGREGATE_OP;
			// selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_op);
			// selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, AggregationOp::NO_AGGREGATE_OP);
		}
<<<<<<< HEAD
#line 1893 "yacc_sql.tab.c"
    break;

  case 73: /* select_attr: aggregate_attr aggregate_attr_list  */
#line 522 "yacc_sql.y"
                                             {
			
	}
#line 1901 "yacc_sql.tab.c"
    break;

  case 74: /* aggregate_attr: aggregate_op LBRACE aggregation_field_attr RBRACE  */
#line 537 "yacc_sql.y"
=======
#line 2101 "yacc_sql.tab.c"
    break;

  case 77:
#line 542 "yacc_sql.y"
                                             {
			
	}
#line 2109 "yacc_sql.tab.c"
    break;

  case 78:
#line 557 "yacc_sql.y"
>>>>>>> updatesel
                                                          {
		// RelAttr attr;
		// relation_attr_init(&attr, NULL, $3);
		// printf("aggregation: get a attr %s\n", $3);
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		// selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		// CONTEXT->aggregation_num++;	
	}
<<<<<<< HEAD
#line 1914 "yacc_sql.tab.c"
    break;

  case 76: /* aggregation_field_attr: STAR attr_list  */
#line 548 "yacc_sql.y"
=======
#line 2122 "yacc_sql.tab.c"
    break;

  case 80:
#line 568 "yacc_sql.y"
>>>>>>> updatesel
                         {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		printf("aggregation: get a attr *\n");
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
<<<<<<< HEAD
#line 1927 "yacc_sql.tab.c"
    break;

  case 77: /* aggregation_field_attr: ID attr_list  */
#line 556 "yacc_sql.y"
=======
#line 2135 "yacc_sql.tab.c"
    break;

  case 81:
#line 576 "yacc_sql.y"
>>>>>>> updatesel
                       {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		printf("aggregation: get a attr %s\n", (yyvsp[-1].string));
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
<<<<<<< HEAD
#line 1940 "yacc_sql.tab.c"
    break;

  case 78: /* aggregate_op: COUNT  */
#line 566 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = COUNT_OP; }
#line 1946 "yacc_sql.tab.c"
    break;

  case 79: /* aggregate_op: AVG  */
#line 567 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = AVG_OP; }
#line 1952 "yacc_sql.tab.c"
    break;

  case 80: /* aggregate_op: MAX  */
#line 568 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = MAX_OP; }
#line 1958 "yacc_sql.tab.c"
    break;

  case 81: /* aggregate_op: MIN  */
#line 569 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = MIN_OP; }
#line 1964 "yacc_sql.tab.c"
    break;

  case 82: /* aggregate_op: SUM  */
#line 570 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = SUM_OP; }
#line 1970 "yacc_sql.tab.c"
    break;

  case 84: /* aggregate_attr_list: COMMA aggregate_attr aggregate_attr_list  */
#line 575 "yacc_sql.y"
                                                  {

	}
#line 1978 "yacc_sql.tab.c"
    break;

  case 85: /* aggregate_attr_list: COMMA STAR aggregate_attr_list  */
#line 579 "yacc_sql.y"
=======
#line 2148 "yacc_sql.tab.c"
    break;

  case 82:
#line 586 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = COUNT_OP; }
#line 2154 "yacc_sql.tab.c"
    break;

  case 83:
#line 587 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = AVG_OP; }
#line 2160 "yacc_sql.tab.c"
    break;

  case 84:
#line 588 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = MAX_OP; }
#line 2166 "yacc_sql.tab.c"
    break;

  case 85:
#line 589 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = MIN_OP; }
#line 2172 "yacc_sql.tab.c"
    break;

  case 86:
#line 590 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = SUM_OP; }
#line 2178 "yacc_sql.tab.c"
    break;

  case 88:
#line 595 "yacc_sql.y"
                                                  {

	}
#line 2186 "yacc_sql.tab.c"
    break;

  case 89:
#line 599 "yacc_sql.y"
>>>>>>> updatesel
                                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
<<<<<<< HEAD
#line 1988 "yacc_sql.tab.c"
    break;

  case 86: /* aggregate_attr_list: COMMA ID aggregate_attr_list  */
#line 584 "yacc_sql.y"
=======
#line 2196 "yacc_sql.tab.c"
    break;

  case 90:
#line 604 "yacc_sql.y"
>>>>>>> updatesel
                                      {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
<<<<<<< HEAD
#line 1998 "yacc_sql.tab.c"
    break;

  case 87: /* aggregate_attr_list: COMMA ID DOT ID aggregate_attr_list  */
#line 589 "yacc_sql.y"
=======
#line 2206 "yacc_sql.tab.c"
    break;

  case 91:
#line 609 "yacc_sql.y"
>>>>>>> updatesel
                                               {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
<<<<<<< HEAD
#line 2008 "yacc_sql.tab.c"
    break;

  case 88: /* aggregate_attr_list: COMMA ID DOT STAR aggregate_attr_list  */
#line 594 "yacc_sql.y"
=======
#line 2216 "yacc_sql.tab.c"
    break;

  case 92:
#line 614 "yacc_sql.y"
>>>>>>> updatesel
                                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
<<<<<<< HEAD
#line 2018 "yacc_sql.tab.c"
    break;

  case 90: /* attr_list: COMMA ID attr_list  */
#line 603 "yacc_sql.y"
=======
#line 2226 "yacc_sql.tab.c"
    break;

  case 94:
#line 623 "yacc_sql.y"
>>>>>>> updatesel
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
<<<<<<< HEAD
#line 2030 "yacc_sql.tab.c"
    break;

  case 91: /* attr_list: COMMA ID DOT ID attr_list  */
#line 610 "yacc_sql.y"
=======
#line 2238 "yacc_sql.tab.c"
    break;

  case 95:
#line 630 "yacc_sql.y"
>>>>>>> updatesel
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
<<<<<<< HEAD
#line 2042 "yacc_sql.tab.c"
    break;

  case 92: /* attr_list: COMMA ID DOT STAR attr_list  */
#line 617 "yacc_sql.y"
=======
#line 2250 "yacc_sql.tab.c"
    break;

  case 96:
#line 637 "yacc_sql.y"
>>>>>>> updatesel
                                      {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
<<<<<<< HEAD
#line 2052 "yacc_sql.tab.c"
    break;

  case 93: /* attr_list: COMMA aggregate_attr attr_list  */
#line 623 "yacc_sql.y"
                                         {

	}
#line 2060 "yacc_sql.tab.c"
    break;

  case 95: /* rel_list: COMMA ID rel_list  */
#line 630 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 2068 "yacc_sql.tab.c"
    break;

  case 96: /* rel_list: INNER JOIN ID on_list rel_list  */
#line 633 "yacc_sql.y"
                                         {
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string));
	}
#line 2076 "yacc_sql.tab.c"
    break;

  case 98: /* on_list: ON condition condition_list  */
#line 640 "yacc_sql.y"
                                      {

	}
#line 2084 "yacc_sql.tab.c"
    break;

  case 100: /* where: WHERE condition condition_list  */
#line 646 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2092 "yacc_sql.tab.c"
    break;

  case 101: /* order: %empty  */
#line 652 "yacc_sql.y"
        {
		selects_set_order(&CONTEXT->ssql->sstr.selection, 0);
	}
#line 2100 "yacc_sql.tab.c"
    break;

  case 102: /* order: ORDER BY order_attr  */
#line 655 "yacc_sql.y"
                              {
		selects_set_order(&CONTEXT->ssql->sstr.selection, 1);
	}
#line 2108 "yacc_sql.tab.c"
    break;

  case 103: /* order_attr: ID asc order_attr_list  */
#line 661 "yacc_sql.y"
                               {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
		}
#line 2118 "yacc_sql.tab.c"
    break;

  case 104: /* order_attr: ID DOT ID asc order_attr_list  */
#line 666 "yacc_sql.y"
                                        {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
		}
#line 2128 "yacc_sql.tab.c"
    break;

  case 105: /* order_attr: ID DESC order_attr_list  */
#line 671 "yacc_sql.y"
                                  {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
		}
#line 2138 "yacc_sql.tab.c"
    break;

  case 106: /* order_attr: ID DOT ID DESC order_attr_list  */
#line 676 "yacc_sql.y"
                                         {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
		}
#line 2148 "yacc_sql.tab.c"
    break;

  case 108: /* order_attr_list: COMMA ID asc order_attr_list  */
#line 685 "yacc_sql.y"
                                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
      }
#line 2158 "yacc_sql.tab.c"
    break;

  case 109: /* order_attr_list: COMMA ID DESC order_attr_list  */
#line 690 "yacc_sql.y"
                                    {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
      }
#line 2168 "yacc_sql.tab.c"
    break;

  case 110: /* order_attr_list: COMMA ID DOT ID asc order_attr_list  */
#line 695 "yacc_sql.y"
                                          {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
  	  }
#line 2178 "yacc_sql.tab.c"
    break;

  case 111: /* order_attr_list: COMMA ID DOT ID DESC order_attr_list  */
#line 700 "yacc_sql.y"
                                           {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
  	  }
#line 2188 "yacc_sql.tab.c"
    break;

  case 115: /* condition_list: AND condition condition_list  */
#line 713 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2196 "yacc_sql.tab.c"
    break;

  case 116: /* condition: ID comOp value  */
#line 719 "yacc_sql.y"
=======
#line 2260 "yacc_sql.tab.c"
    break;

  case 97:
#line 643 "yacc_sql.y"
                                         {

	}
#line 2268 "yacc_sql.tab.c"
    break;

  case 99:
#line 650 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 2276 "yacc_sql.tab.c"
    break;

  case 100:
#line 653 "yacc_sql.y"
                                         {
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string));
	}
#line 2284 "yacc_sql.tab.c"
    break;

  case 102:
#line 660 "yacc_sql.y"
                                      {

	}
#line 2292 "yacc_sql.tab.c"
    break;

  case 104:
#line 666 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2300 "yacc_sql.tab.c"
    break;

  case 106:
#line 672 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2308 "yacc_sql.tab.c"
    break;

  case 107:
#line 678 "yacc_sql.y"
>>>>>>> updatesel
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			// condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			condition_init(&condition, Comparison, CONTEXT->comp, 1, &left_attr, NULL, 0, 0, 0, NULL, right_value, NULL, NULL, 0);
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
<<<<<<< HEAD
#line 2222 "yacc_sql.tab.c"
    break;

  case 117: /* condition: value comOp value  */
#line 741 "yacc_sql.y"
=======
#line 2334 "yacc_sql.tab.c"
    break;

  case 108:
#line 700 "yacc_sql.y"
>>>>>>> updatesel
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			// condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
			condition_init(&condition, Comparison, CONTEXT->comp, 0, NULL, left_value, 0, 0, 0, NULL, right_value, NULL, NULL, 0);
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
<<<<<<< HEAD
#line 2247 "yacc_sql.tab.c"
    break;

  case 118: /* condition: ID comOp ID  */
#line 762 "yacc_sql.y"
=======
#line 2359 "yacc_sql.tab.c"
    break;

  case 109:
#line 721 "yacc_sql.y"
>>>>>>> updatesel
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			// condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			condition_init(&condition, Comparison, CONTEXT->comp, 1, &left_attr, NULL, 1, 0, 0, &right_attr, NULL, NULL, NULL, 0);
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
<<<<<<< HEAD
#line 2272 "yacc_sql.tab.c"
    break;

  case 119: /* condition: value comOp ID  */
#line 783 "yacc_sql.y"
=======
#line 2384 "yacc_sql.tab.c"
    break;

  case 110:
#line 742 "yacc_sql.y"
>>>>>>> updatesel
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			// condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			condition_init(&condition, Comparison, CONTEXT->comp, 0, NULL, left_value, 1, 0, 0, &right_attr, NULL, NULL, NULL, 0);
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
<<<<<<< HEAD
#line 2299 "yacc_sql.tab.c"
    break;

  case 120: /* condition: ID DOT ID comOp value  */
#line 806 "yacc_sql.y"
=======
#line 2411 "yacc_sql.tab.c"
    break;

  case 111:
#line 765 "yacc_sql.y"
>>>>>>> updatesel
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			// condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			condition_init(&condition, Comparison, CONTEXT->comp, 1, &left_attr, NULL, 0, 0, 0, NULL, right_value, NULL, NULL, 0);
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
<<<<<<< HEAD
#line 2325 "yacc_sql.tab.c"
    break;

  case 121: /* condition: value comOp ID DOT ID  */
#line 828 "yacc_sql.y"
=======
#line 2437 "yacc_sql.tab.c"
    break;

  case 112:
#line 787 "yacc_sql.y"
>>>>>>> updatesel
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			// condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			condition_init(&condition, Comparison, CONTEXT->comp, 0, NULL, left_value, 1, 0, 0, &right_attr, NULL, NULL, NULL, 0);
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
<<<<<<< HEAD
#line 2351 "yacc_sql.tab.c"
    break;

  case 122: /* condition: ID DOT ID comOp ID DOT ID  */
#line 850 "yacc_sql.y"
=======
#line 2463 "yacc_sql.tab.c"
    break;

  case 113:
#line 809 "yacc_sql.y"
>>>>>>> updatesel
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			// condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			condition_init(&condition, Comparison, CONTEXT->comp, 1, &left_attr, NULL, 1, 0, 0, &right_attr, NULL, NULL, NULL, 0);
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
<<<<<<< HEAD
#line 2375 "yacc_sql.tab.c"
    break;

  case 123: /* condition: ID IN sub_query  */
#line 869 "yacc_sql.y"
=======
#line 2487 "yacc_sql.tab.c"
    break;

  case 114:
#line 828 "yacc_sql.y"
>>>>>>> updatesel
                          {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

		Condition condition;
		condition_init(&condition, Contain, CONTEXT->comp, 1, &left_attr, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		
	}
<<<<<<< HEAD
#line 2389 "yacc_sql.tab.c"
    break;

  case 124: /* condition: ID NOT IN sub_query  */
#line 878 "yacc_sql.y"
=======
#line 2501 "yacc_sql.tab.c"
    break;

  case 115:
#line 837 "yacc_sql.y"
>>>>>>> updatesel
                              {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-3].string));

		Condition condition;
		condition_init(&condition, NotContain, CONTEXT->comp, 1, &left_attr, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
<<<<<<< HEAD
#line 2403 "yacc_sql.tab.c"
    break;

  case 125: /* condition: ID IN LBRACE value value_list RBRACE  */
#line 887 "yacc_sql.y"
=======
#line 2515 "yacc_sql.tab.c"
    break;

  case 116:
#line 846 "yacc_sql.y"
>>>>>>> updatesel
                                               {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-5].string));

		Condition condition;
		condition_init(&condition, Contain, CONTEXT->comp, 1, &left_attr, NULL, 0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, 
			CONTEXT->values, CONTEXT->value_length);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
<<<<<<< HEAD
#line 2418 "yacc_sql.tab.c"
    break;

  case 126: /* condition: ID NOT IN LBRACE value value_list RBRACE  */
#line 897 "yacc_sql.y"
=======
#line 2530 "yacc_sql.tab.c"
    break;

  case 117:
#line 856 "yacc_sql.y"
>>>>>>> updatesel
                                                   {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-6].string));

		Condition condition;
		condition_init(&condition, NotContain, CONTEXT->comp, 1, &left_attr, NULL, 0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, 
			CONTEXT->values, CONTEXT->value_length);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
<<<<<<< HEAD
#line 2433 "yacc_sql.tab.c"
    break;

  case 127: /* condition: ID DOT ID comOp sub_query  */
#line 907 "yacc_sql.y"
=======
#line 2545 "yacc_sql.tab.c"
    break;

  case 118:
#line 866 "yacc_sql.y"
>>>>>>> updatesel
                                    {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));

		Condition condition;
		condition_init(&condition, Comparison, CONTEXT->comp, 1, &left_attr, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
<<<<<<< HEAD
#line 2446 "yacc_sql.tab.c"
    break;

  case 128: /* condition: EXISTS sub_query  */
#line 915 "yacc_sql.y"
=======
#line 2558 "yacc_sql.tab.c"
    break;

  case 119:
#line 874 "yacc_sql.y"
>>>>>>> updatesel
                           {

		Condition condition;
		condition_init(&condition, Exists, CONTEXT->comp, 0, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
<<<<<<< HEAD
#line 2458 "yacc_sql.tab.c"
    break;

  case 129: /* condition: NOT EXISTS sub_query  */
#line 922 "yacc_sql.y"
=======
#line 2570 "yacc_sql.tab.c"
    break;

  case 120:
#line 881 "yacc_sql.y"
>>>>>>> updatesel
                               {

		Condition condition;
		condition_init(&condition, NotExists, CONTEXT->comp, 0, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
<<<<<<< HEAD
#line 2470 "yacc_sql.tab.c"
    break;

  case 130: /* sub_query: LBRACE N select_query RBRACE  */
#line 932 "yacc_sql.y"
=======
#line 2582 "yacc_sql.tab.c"
    break;

  case 121:
#line 891 "yacc_sql.y"
>>>>>>> updatesel
                                     {
		// TODO support complex sub query
		ParserContext *old_context = CONTEXT->last_context;
		old_context->sub_query = CONTEXT->ssql;
		*CONTEXT = *old_context;
		printf("sub query addr %p\n", old_context->sub_query);
		printf("swap back old context\n");
	}
<<<<<<< HEAD
#line 2483 "yacc_sql.tab.c"
    break;

  case 131: /* N: %empty  */
#line 940 "yacc_sql.y"
=======
#line 2595 "yacc_sql.tab.c"
    break;

  case 122:
#line 899 "yacc_sql.y"
>>>>>>> updatesel
               {
	// create a new context
	ParserContext *old_context = (ParserContext *)malloc(sizeof(ParserContext));
	ParserContext tmp = *old_context;
	*old_context = *CONTEXT;
	*CONTEXT = tmp; 
	memset(CONTEXT, 0, sizeof(*CONTEXT));
	CONTEXT->ssql = (Query *)malloc(sizeof(Query));
	memset(CONTEXT->ssql, 0, sizeof(Query));
	
	printf("SWAP OUT sub query addr %p\n", CONTEXT->ssql);
	old_context->last_context = CONTEXT->last_context;
	CONTEXT->last_context = old_context;
	printf("swap out old context\n");
}
<<<<<<< HEAD
#line 2503 "yacc_sql.tab.c"
    break;

  case 132: /* comOp: EQ  */
#line 958 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2509 "yacc_sql.tab.c"
    break;

  case 133: /* comOp: LT  */
#line 959 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2515 "yacc_sql.tab.c"
    break;

  case 134: /* comOp: GT  */
#line 960 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2521 "yacc_sql.tab.c"
    break;

  case 135: /* comOp: LE  */
#line 961 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2527 "yacc_sql.tab.c"
    break;

  case 136: /* comOp: GE  */
#line 962 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2533 "yacc_sql.tab.c"
    break;

  case 137: /* comOp: NE  */
#line 963 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2539 "yacc_sql.tab.c"
    break;

  case 138: /* comOp: IS  */
#line 964 "yacc_sql.y"
             { CONTEXT->comp = LOGICAL_IS; }
#line 2545 "yacc_sql.tab.c"
    break;

  case 139: /* comOp: IS NOT  */
#line 965 "yacc_sql.y"
                 {CONTEXT->comp = LOGICAL_IS_NOT; }
#line 2551 "yacc_sql.tab.c"
    break;

  case 140: /* comOp: LIKE  */
#line 966 "yacc_sql.y"
               { CONTEXT->comp = LIKE_OP; }
#line 2557 "yacc_sql.tab.c"
    break;

  case 141: /* comOp: NOT LIKE  */
#line 967 "yacc_sql.y"
                   { CONTEXT->comp = NOT_LIKE_OP; }
#line 2563 "yacc_sql.tab.c"
    break;

  case 142: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 972 "yacc_sql.y"
=======
#line 2615 "yacc_sql.tab.c"
    break;

  case 123:
#line 917 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2621 "yacc_sql.tab.c"
    break;

  case 124:
#line 918 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2627 "yacc_sql.tab.c"
    break;

  case 125:
#line 919 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2633 "yacc_sql.tab.c"
    break;

  case 126:
#line 920 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2639 "yacc_sql.tab.c"
    break;

  case 127:
#line 921 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2645 "yacc_sql.tab.c"
    break;

  case 128:
#line 922 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2651 "yacc_sql.tab.c"
    break;

  case 129:
#line 923 "yacc_sql.y"
             { CONTEXT->comp = LOGICAL_IS; }
#line 2657 "yacc_sql.tab.c"
    break;

  case 130:
#line 924 "yacc_sql.y"
                 {CONTEXT->comp = LOGICAL_IS_NOT; }
#line 2663 "yacc_sql.tab.c"
    break;

  case 131:
#line 925 "yacc_sql.y"
               { CONTEXT->comp = LIKE_OP; }
#line 2669 "yacc_sql.tab.c"
    break;

  case 132:
#line 926 "yacc_sql.y"
                   { CONTEXT->comp = NOT_LIKE_OP; }
#line 2675 "yacc_sql.tab.c"
    break;

  case 133:
#line 931 "yacc_sql.y"
>>>>>>> updatesel
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
<<<<<<< HEAD
#line 2572 "yacc_sql.tab.c"
    break;


#line 2576 "yacc_sql.tab.c"
=======
#line 2684 "yacc_sql.tab.c"
    break;


#line 2688 "yacc_sql.tab.c"
>>>>>>> updatesel

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (scanner, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (scanner, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
<<<<<<< HEAD

#line 977 "yacc_sql.y"
=======
#line 936 "yacc_sql.y"
>>>>>>> updatesel

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
