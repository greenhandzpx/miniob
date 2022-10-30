/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

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


#line 152 "yacc_sql.tab.c"

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

#include "yacc_sql.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
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
  YYSYMBOL_GROUP = 63,                     /* GROUP  */
  YYSYMBOL_HAVING = 64,                    /* HAVING  */
  YYSYMBOL_OR = 65,                        /* OR  */
  YYSYMBOL_NUMBER = 66,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 67,                     /* FLOAT  */
  YYSYMBOL_ID = 68,                        /* ID  */
  YYSYMBOL_PATH = 69,                      /* PATH  */
  YYSYMBOL_SSS = 70,                       /* SSS  */
  YYSYMBOL_STAR = 71,                      /* STAR  */
  YYSYMBOL_STRING_V = 72,                  /* STRING_V  */
  YYSYMBOL_DATE_STR = 73,                  /* DATE_STR  */
  YYSYMBOL_NULLVALUE = 74,                 /* NULLVALUE  */
  YYSYMBOL_YYACCEPT = 75,                  /* $accept  */
  YYSYMBOL_commands = 76,                  /* commands  */
  YYSYMBOL_command = 77,                   /* command  */
  YYSYMBOL_exit = 78,                      /* exit  */
  YYSYMBOL_help = 79,                      /* help  */
  YYSYMBOL_sync = 80,                      /* sync  */
  YYSYMBOL_begin = 81,                     /* begin  */
  YYSYMBOL_commit = 82,                    /* commit  */
  YYSYMBOL_rollback = 83,                  /* rollback  */
  YYSYMBOL_drop_table = 84,                /* drop_table  */
  YYSYMBOL_show_tables = 85,               /* show_tables  */
  YYSYMBOL_show_index = 86,                /* show_index  */
  YYSYMBOL_desc_table = 87,                /* desc_table  */
  YYSYMBOL_create_index = 88,              /* create_index  */
  YYSYMBOL_unique_option = 89,             /* unique_option  */
  YYSYMBOL_index_attr_list = 90,           /* index_attr_list  */
  YYSYMBOL_drop_index = 91,                /* drop_index  */
  YYSYMBOL_create_table = 92,              /* create_table  */
  YYSYMBOL_attr_def_list = 93,             /* attr_def_list  */
  YYSYMBOL_attr_def = 94,                  /* attr_def  */
  YYSYMBOL_number = 95,                    /* number  */
  YYSYMBOL_type = 96,                      /* type  */
  YYSYMBOL_ID_get = 97,                    /* ID_get  */
  YYSYMBOL_NONULL = 98,                    /* NONULL  */
  YYSYMBOL_insert = 99,                    /* insert  */
  YYSYMBOL_tuple = 100,                    /* tuple  */
  YYSYMBOL_tuple_list = 101,               /* tuple_list  */
  YYSYMBOL_value_list = 102,               /* value_list  */
  YYSYMBOL_value = 103,                    /* value  */
  YYSYMBOL_delete = 104,                   /* delete  */
  YYSYMBOL_update = 105,                   /* update  */
  YYSYMBOL_assign = 106,                   /* assign  */
  YYSYMBOL_assign_list = 107,              /* assign_list  */
  YYSYMBOL_select = 108,                   /* select  */
  YYSYMBOL_select_query = 109,             /* select_query  */
  YYSYMBOL_select_attr = 110,              /* select_attr  */
  YYSYMBOL_aggregate_attr = 111,           /* aggregate_attr  */
  YYSYMBOL_aggregation_field_attr = 112,   /* aggregation_field_attr  */
  YYSYMBOL_aggrattr_list = 113,            /* aggrattr_list  */
  YYSYMBOL_aggregate_op = 114,             /* aggregate_op  */
  YYSYMBOL_aggregate_attr_list = 115,      /* aggregate_attr_list  */
  YYSYMBOL_attr_list = 116,                /* attr_list  */
  YYSYMBOL_rel_list = 117,                 /* rel_list  */
  YYSYMBOL_on_list = 118,                  /* on_list  */
  YYSYMBOL_where = 119,                    /* where  */
  YYSYMBOL_group = 120,                    /* group  */
  YYSYMBOL_group_attrs = 121,              /* group_attrs  */
  YYSYMBOL_group_attr_list = 122,          /* group_attr_list  */
  YYSYMBOL_group_attr = 123,               /* group_attr  */
  YYSYMBOL_having = 124,                   /* having  */
  YYSYMBOL_having_condition_list = 125,    /* having_condition_list  */
  YYSYMBOL_having_condition = 126,         /* having_condition  */
  YYSYMBOL_order = 127,                    /* order  */
  YYSYMBOL_order_attr = 128,               /* order_attr  */
  YYSYMBOL_order_attr_list = 129,          /* order_attr_list  */
  YYSYMBOL_asc = 130,                      /* asc  */
  YYSYMBOL_condition_list = 131,           /* condition_list  */
  YYSYMBOL_condition = 132,                /* condition  */
  YYSYMBOL_sub_query = 133,                /* sub_query  */
  YYSYMBOL_N = 134,                        /* N  */
  YYSYMBOL_comOp = 135,                    /* comOp  */
  YYSYMBOL_load_data = 136                 /* load_data  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYLAST   450

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  75
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  62
/* YYNRULES -- Number of rules.  */
#define YYNRULES  194
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  445

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   329


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   186,   186,   188,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   213,   218,   223,   229,   235,   241,   247,   253,
     259,   266,   273,   279,   281,   293,   295,   300,   307,   316,
     318,   322,   333,   344,   355,   368,   371,   372,   373,   374,
     375,   378,   385,   386,   392,   410,   415,   417,   420,   422,
     427,   432,   437,   443,   459,   466,   477,   490,   494,   503,
     505,   509,   512,   532,   537,   542,   547,   555,   570,   579,
     581,   590,   599,   608,   619,   620,   627,   634,   641,   651,
     652,   653,   654,   655,   658,   660,   663,   668,   673,   678,
     685,   687,   694,   701,   706,   711,   713,   716,   721,   723,
     727,   729,   735,   738,   744,   749,   750,   757,   762,   770,
     773,   779,   780,   789,   790,   797,   804,   811,   818,   825,
     832,   839,   846,   853,   860,   867,   874,   881,   888,   895,
     902,   909,   916,   923,   933,   936,   942,   947,   952,   957,
     964,   966,   971,   976,   981,   988,   989,   992,   994,  1003,
    1014,  1036,  1057,  1078,  1101,  1123,  1145,  1165,  1174,  1183,
    1192,  1201,  1212,  1223,  1234,  1245,  1253,  1261,  1285,  1308,
    1314,  1321,  1331,  1344,  1362,  1363,  1364,  1365,  1366,  1367,
    1368,  1369,  1370,  1371,  1375
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "TABLE", "TABLES", "INDEX", "SELECT", "DESC", "SHOW", "SYNC",
  "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "TEXT_T", "FLOAT_T",
  "DATE_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE",
  "AND", "SET", "ON", "LOAD", "DATA", "INFILE", "EQ", "LT", "GT", "LE",
  "GE", "NE", "IS", "NULLABLE", "COUNT", "AVG", "MAX", "MIN", "SUM",
  "INNER", "JOIN", "IN", "EXISTS", "LIKE", "NOT", "UNIQUE", "ORDER", "BY",
  "ASC", "GROUP", "HAVING", "OR", "NUMBER", "FLOAT", "ID", "PATH", "SSS",
  "STAR", "STRING_V", "DATE_STR", "NULLVALUE", "$accept", "commands",
  "command", "exit", "help", "sync", "begin", "commit", "rollback",
  "drop_table", "show_tables", "show_index", "desc_table", "create_index",
  "unique_option", "index_attr_list", "drop_index", "create_table",
  "attr_def_list", "attr_def", "number", "type", "ID_get", "NONULL",
  "insert", "tuple", "tuple_list", "value_list", "value", "delete",
  "update", "assign", "assign_list", "select", "select_query",
  "select_attr", "aggregate_attr", "aggregation_field_attr",
  "aggrattr_list", "aggregate_op", "aggregate_attr_list", "attr_list",
  "rel_list", "on_list", "where", "group", "group_attrs",
  "group_attr_list", "group_attr", "having", "having_condition_list",
  "having_condition", "order", "order_attr", "order_attr_list", "asc",
  "condition_list", "condition", "sub_query", "N", "comOp", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-329)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -329,   157,  -329,     7,   239,    74,   -47,   136,    34,    33,
      45,    47,   113,   147,   155,   161,   170,   121,  -329,  -329,
    -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,
    -329,  -329,  -329,  -329,  -329,  -329,   171,  -329,   127,  -329,
     178,   129,   137,  -329,  -329,  -329,  -329,  -329,     2,   194,
     187,   217,   220,   250,   259,   222,  -329,   208,   216,   282,
    -329,  -329,  -329,  -329,  -329,   246,  -329,   308,   257,   328,
     331,   189,    68,  -329,  -329,   269,   140,  -329,   125,  -329,
    -329,   273,   312,   311,   277,   276,   279,   313,  -329,  -329,
       5,   217,   194,   194,     1,    91,   194,   217,   119,   330,
     333,   348,   336,     6,   350,   314,   337,   326,  -329,   339,
     266,   290,   138,  -329,  -329,  -329,  -329,   291,   306,   311,
     139,  -329,  -329,  -329,   146,   150,  -329,  -329,  -329,  -329,
     213,   343,  -329,   346,   307,  -329,  -329,   158,  -329,  -329,
    -329,   270,    67,   270,  -329,    37,   277,   311,   358,   279,
     349,  -329,  -329,  -329,  -329,  -329,    -7,   351,   194,   194,
       1,   297,   305,   194,   194,   120,   330,   330,   330,   352,
     336,   366,   362,  -329,   346,   304,  -329,  -329,  -329,  -329,
    -329,  -329,   315,   359,  -329,   108,    16,   317,   176,     6,
       6,  -329,    10,  -329,  -329,   337,   373,   309,   339,   375,
     316,  -329,   310,  -329,   318,  -329,  -329,  -329,   344,   320,
     319,  -329,  -329,   156,  -329,  -329,  -329,  -329,   213,   368,
     343,  -329,   370,  -329,   263,  -329,   213,  -329,   367,  -329,
    -329,  -329,  -329,   360,  -329,    67,    67,   361,  -329,  -329,
    -329,   385,  -329,  -329,  -329,   374,  -329,   376,     6,     1,
     324,   332,  -329,   330,   330,   352,  -329,  -329,  -329,   379,
     285,    25,   352,   213,  -329,   329,  -329,  -329,   334,  -329,
      93,   335,   381,    67,  -329,   371,   340,   378,   338,  -329,
    -329,  -329,   213,  -329,   383,   372,  -329,  -329,   388,   352,
    -329,  -329,  -329,  -329,   376,   404,  -329,   341,   131,  -329,
     324,  -329,    92,  -329,   352,   213,  -329,   342,  -329,   391,
    -329,  -329,  -329,   395,   396,   397,   398,   399,   400,   378,
     401,   353,  -329,   401,   403,   352,  -329,  -329,   162,   190,
     200,   204,   251,   131,  -329,  -329,   354,  -329,    23,  -329,
    -329,   406,    -5,   407,    13,   408,   112,   409,   117,   410,
     118,   411,   400,    98,   401,   401,  -329,   270,   255,   270,
     270,   261,   270,   270,   262,   270,   270,   267,   270,   270,
     268,   270,  -329,   401,   363,   401,  -329,  -329,   213,   412,
     413,   213,   213,   415,   416,   213,   213,   417,   418,   213,
     213,   419,   420,   213,   213,   421,   422,   213,  -329,    38,
    -329,  -329,   270,   270,  -329,  -329,   270,   270,  -329,  -329,
     270,   270,  -329,  -329,   270,   270,  -329,  -329,   270,   270,
    -329,   401,   401,   213,   213,   213,   213,   213,   213,   213,
     213,   213,   213,  -329,  -329,  -329,  -329,  -329,  -329,  -329,
    -329,  -329,  -329,  -329,  -329
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
       0,     0,     0,    89,    90,    91,    92,    93,   100,   100,
       0,    94,     0,     0,     0,     0,    24,     0,     0,     0,
      25,    26,    27,    23,    22,     0,    71,     0,     0,     0,
       0,     0,     0,    74,    73,     0,     0,    77,    79,    31,
      29,     0,     0,   110,     0,     0,     0,     0,    28,    37,
     100,    94,   100,   100,   105,   100,   100,    94,    84,    84,
       0,     0,     0,     0,     0,     0,    69,     0,    51,    39,
       0,     0,     0,   101,   104,    75,    76,     0,     0,   110,
       0,    97,    96,    95,     0,     0,    81,    80,    78,    30,
       0,    56,   183,     0,     0,    60,    61,     0,    62,    63,
      64,     0,   157,     0,    65,     0,     0,   110,     0,     0,
       0,    46,    47,    48,    49,    50,    52,     0,   100,   100,
     105,     0,   112,   100,   100,    84,    84,    84,    84,    58,
       0,     0,     0,   180,     0,     0,   184,   185,   186,   187,
     188,   189,   190,     0,   192,     0,     0,     0,     0,     0,
       0,   111,     0,    67,    68,    69,     0,     0,    39,     0,
       0,    44,     0,    43,     0,   102,   103,   106,   108,     0,
     144,    98,    99,     0,    86,    85,    82,    83,     0,     0,
      56,    54,     0,   181,     0,   191,   183,   167,     0,   193,
     162,   160,   176,   163,   161,   157,   157,   178,   179,    70,
      66,     0,    40,    38,    45,     0,    53,    35,     0,   105,
       0,     0,    72,    84,    84,    58,    55,    57,   182,     0,
       0,     0,    58,   183,   168,     0,   158,   159,     0,   194,
      52,     0,     0,   157,   107,   117,   119,   115,     0,    87,
      88,    59,   183,   169,     0,     0,   164,   175,     0,    58,
     165,   177,    42,    41,    35,     0,   109,     0,   123,   113,
       0,   114,   155,   145,    58,   183,   170,     0,   171,     0,
      36,    32,   118,     0,     0,     0,     0,     0,   121,   115,
     150,     0,   156,   150,     0,    58,   166,   172,     0,     0,
       0,     0,     0,   123,   120,   116,     0,   148,   155,   146,
     173,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   121,   155,   150,   150,   174,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   122,   150,     0,   150,   149,   147,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   152,   155,
     151,   124,     0,     0,   125,   128,     0,     0,   129,   132,
       0,     0,   133,   136,     0,     0,   137,   140,     0,     0,
     141,   150,   150,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   154,   153,   126,   127,   130,   131,   134,
     135,   138,   139,   142,   143
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,  -329,
    -329,  -329,  -329,  -329,  -329,   122,  -329,  -329,   219,   292,
    -329,  -329,  -329,   172,  -329,   274,   223,  -244,  -130,  -329,
    -329,   294,   252,  -329,   278,  -329,    43,  -329,   -98,  -329,
     -62,   -46,  -155,  -329,  -111,  -329,  -329,   126,   148,  -329,
      94,   116,  -329,  -329,  -316,  -328,  -208,  -173,  -131,  -329,
    -137,  -329
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    40,   272,    30,    31,   150,   109,
     245,   156,   110,   203,    32,   131,   171,   219,   141,    33,
      34,   106,   147,    35,    36,    50,    51,   100,   126,    52,
      77,    73,   119,   249,   104,   210,   276,   301,   277,   299,
     334,   318,   252,   303,   337,   323,   191,   142,   143,   172,
     186,    37
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     169,   127,   173,    74,   188,   207,   192,   339,   162,   200,
     355,   281,   357,    38,   194,   193,   235,   236,   288,   117,
      71,    53,   132,    71,   358,   375,   132,   266,   267,   114,
     360,    72,   132,   354,   112,   123,   196,    56,   376,   377,
     201,   132,   361,   223,   113,   309,   115,   116,   421,   121,
     122,   202,   227,   132,   118,   232,   231,   398,   234,   400,
     324,   238,   133,    57,   134,   296,    39,   214,   215,   216,
     217,   422,   135,   136,   137,   273,   138,    58,   237,   139,
     140,   341,   135,   136,   230,   322,   138,   261,   255,   139,
     140,   135,   136,   285,   274,   138,   262,   264,   139,   140,
     322,   189,   320,   135,   136,   433,   434,   138,   373,    71,
     139,   140,   205,   206,    91,    59,    60,   211,   212,    97,
     120,   321,    43,    44,    45,    46,    47,   374,   283,   363,
     287,   286,   190,   289,   366,   369,    92,   124,   124,    93,
     292,   364,    48,    54,    55,    49,   367,   370,   125,   213,
      61,   202,   304,   306,   322,   279,   280,     2,    62,    65,
     322,     3,     4,   228,    63,   229,     5,     6,     7,     8,
       9,    10,    11,    64,    66,   325,    12,    13,    14,   313,
     314,   315,   316,   317,    15,    16,    68,   175,    43,    44,
      45,    46,    47,    98,    17,    67,    99,    69,   176,   177,
     178,   179,   180,   181,   182,    70,   158,   163,    95,   159,
     164,    96,    71,   183,   165,   184,   185,   166,   167,    75,
     378,   168,   381,   382,   253,   385,   386,   254,   389,   390,
     342,   393,   394,   343,   397,    76,    78,    43,    44,    45,
      46,    47,   135,   136,   233,    41,   138,    42,   401,   139,
     140,   404,   405,    79,    81,   408,   409,    90,   344,   412,
     413,   345,    80,   416,   417,   423,   424,   420,   346,   425,
     426,   347,   348,   427,   428,   349,    82,   429,   430,   135,
     136,   431,   432,   138,    83,    85,   139,   140,   151,   152,
     153,   154,   155,   435,   436,   437,   438,   439,   440,   441,
     442,   443,   444,   176,   177,   178,   179,   180,   181,   182,
     176,   177,   178,   179,   180,   181,   182,    84,   259,   350,
     184,   260,   351,   379,    86,    87,   380,   184,   187,   383,
     387,    88,   384,   388,    89,   391,   395,    94,   392,   396,
     284,   101,   229,   102,   103,   105,   107,   108,   124,   111,
     128,   129,   130,   144,   145,   146,   148,   149,   157,   160,
     161,   170,   132,   174,   197,   208,   199,   204,   209,   221,
     218,     5,   224,   225,   229,   226,   240,   241,   243,   251,
     248,   250,   244,   263,   246,   256,   247,   258,   269,   265,
     268,   270,   275,   278,   271,   282,   300,   290,   295,   305,
     297,   307,   291,   294,   298,   308,   302,   311,   327,   312,
     326,   328,   329,   330,   331,   332,   310,   242,   333,   336,
     340,   338,   353,   356,   359,   362,   365,   368,   371,   402,
     403,   399,   406,   407,   410,   411,   414,   415,   418,   419,
     195,   198,   293,   257,   220,   335,   372,   239,   319,   352,
     222
};

static const yytype_int16 yycheck[] =
{
     130,    99,   133,    49,   141,   160,   143,   323,   119,    16,
     338,   255,    17,     6,   145,   145,   189,   190,   262,    18,
      18,    68,    16,    18,    29,   353,    16,   235,   236,    91,
      17,    29,    16,    10,    29,    97,   147,     3,   354,   355,
      47,    16,    29,   174,    90,   289,    92,    93,    10,    95,
      96,    58,   183,    16,    53,   186,   186,   373,   188,   375,
     304,   192,    56,    30,    58,   273,    59,   165,   166,   167,
     168,   399,    66,    67,    68,   248,    70,    32,    68,    73,
      74,   325,    66,    67,    68,    62,    70,   224,   218,    73,
      74,    66,    67,    68,   249,    70,   226,   228,    73,    74,
      62,    34,    10,    66,    67,   421,   422,    70,    10,    18,
      73,    74,   158,   159,    71,    68,     3,   163,   164,    76,
      29,    29,    48,    49,    50,    51,    52,    29,   259,    17,
     261,   261,    65,   263,    17,    17,    68,    18,    18,    71,
      47,    29,    68,     7,     8,    71,    29,    29,    29,    29,
       3,    58,   282,   284,    62,   253,   254,     0,     3,    38,
      62,     4,     5,    55,     3,    57,     9,    10,    11,    12,
      13,    14,    15,     3,     3,   305,    19,    20,    21,    48,
      49,    50,    51,    52,    27,    28,     8,    29,    48,    49,
      50,    51,    52,    68,    37,    68,    71,    68,    40,    41,
      42,    43,    44,    45,    46,    68,    68,    68,    68,    71,
      71,    71,    18,    55,    68,    57,    58,    71,    68,    32,
     357,    71,   359,   360,    68,   362,   363,    71,   365,   366,
      68,   368,   369,    71,   371,    18,    16,    48,    49,    50,
      51,    52,    66,    67,    68,     6,    70,     8,   378,    73,
      74,   381,   382,     3,    32,   385,   386,    68,    68,   389,
     390,    71,     3,   393,   394,   402,   403,   397,    68,   406,
     407,    71,    68,   410,   411,    71,    68,   414,   415,    66,
      67,   418,   419,    70,    68,    39,    73,    74,    22,    23,
      24,    25,    26,   423,   424,   425,   426,   427,   428,   429,
     430,   431,   432,    40,    41,    42,    43,    44,    45,    46,
      40,    41,    42,    43,    44,    45,    46,    35,    55,    68,
      57,    58,    71,    68,    16,    68,    71,    57,    58,    68,
      68,     3,    71,    71,     3,    68,    68,    68,    71,    71,
      55,    68,    57,    31,    33,    68,    70,    68,    18,    36,
      17,     3,    16,     3,    40,    18,    30,    18,    68,    68,
      54,    18,    16,    56,     6,    68,    17,    16,    63,     3,
      18,     9,    68,    58,    57,    16,     3,    68,     3,    60,
      36,    61,    66,    16,    74,    17,    68,    17,     3,    29,
      29,    17,    68,    61,    18,    16,    18,    68,    17,    16,
      29,    29,    68,    68,    64,    17,    68,     3,    17,    68,
      68,    16,    16,    16,    16,    16,   294,   198,    18,    18,
      17,    68,    68,    17,    17,    17,    17,    17,    17,    17,
      17,    68,    17,    17,    17,    17,    17,    17,    17,    17,
     146,   149,   270,   220,   170,   319,   352,   195,   300,   333,
     172
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    76,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    19,    20,    21,    27,    28,    37,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      91,    92,    99,   104,   105,   108,   109,   136,     6,    59,
      89,     6,     8,    48,    49,    50,    51,    52,    68,    71,
     110,   111,   114,    68,     7,     8,     3,    30,    32,    68,
       3,     3,     3,     3,     3,    38,     3,    68,     8,    68,
      68,    18,    29,   116,   116,    32,    18,   115,    16,     3,
       3,    32,    68,    68,    35,    39,    16,    68,     3,     3,
      68,   111,    68,    71,    68,    68,    71,   111,    68,    71,
     112,    68,    31,    33,   119,    68,   106,    70,    68,    94,
      97,    36,    29,   116,   115,   116,   116,    18,    53,   117,
      29,   116,   116,   115,    18,    29,   113,   113,    17,     3,
      16,   100,    16,    56,    58,    66,    67,    68,    70,    73,
      74,   103,   132,   133,     3,    40,    18,   107,    30,    18,
      93,    22,    23,    24,    25,    26,    96,    68,    68,    71,
      68,    54,   119,    68,    71,    68,    71,    68,    71,   103,
      18,   101,   134,   133,    56,    29,    40,    41,    42,    43,
      44,    45,    46,    55,    57,    58,   135,    58,   135,    34,
      65,   131,   135,   103,   133,   106,   119,     6,    94,    17,
      16,    47,    58,    98,    16,   116,   116,   117,    68,    63,
     120,   116,   116,    29,   113,   113,   113,   113,    18,   102,
     100,     3,   109,   133,    68,    58,    16,   133,    55,    57,
      68,   103,   133,    68,   103,   132,   132,    68,   133,   107,
       3,    68,    93,     3,    66,    95,    74,    68,    36,   118,
      61,    60,   127,    68,    71,   103,    17,   101,    17,    55,
      58,   135,   103,    16,   133,    29,   131,   131,    29,     3,
      17,    18,    90,   132,   117,    68,   121,   123,    61,   113,
     113,   102,    16,   133,    55,    68,   103,   133,   102,   103,
      68,    68,    47,    98,    68,    17,   131,    29,    64,   124,
      18,   122,    68,   128,   103,    16,   133,    29,    17,   102,
      90,     3,    68,    48,    49,    50,    51,    52,   126,   123,
      10,    29,    62,   130,   102,   103,    68,    17,    16,    16,
      16,    16,    16,    18,   125,   122,    18,   129,    68,   129,
      17,   102,    68,    71,    68,    71,    68,    71,    68,    71,
      68,    71,   126,    68,    10,   130,    17,    17,    29,    17,
      17,    29,    17,    17,    29,    17,    17,    29,    17,    17,
      29,    17,   125,    10,    29,   130,   129,   129,   135,    68,
      71,   135,   135,    68,    71,   135,   135,    68,    71,   135,
     135,    68,    71,   135,   135,    68,    71,   135,   129,    68,
     129,   103,    17,    17,   103,   103,    17,    17,   103,   103,
      17,    17,   103,   103,    17,    17,   103,   103,    17,    17,
     103,    10,   130,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   129,   129,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    75,    76,    76,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    89,    90,    90,    91,    92,    93,
      93,    94,    94,    94,    94,    95,    96,    96,    96,    96,
      96,    97,    98,    98,    99,   100,   101,   101,   102,   102,
     103,   103,   103,   103,   103,   104,   105,   106,   106,   107,
     107,   108,   109,   110,   110,   110,   110,   110,   111,   112,
     112,   112,   112,   112,   113,   113,   113,   113,   113,   114,
     114,   114,   114,   114,   115,   115,   115,   115,   115,   115,
     116,   116,   116,   116,   116,   117,   117,   117,   118,   118,
     119,   119,   120,   120,   121,   122,   122,   123,   123,   124,
     124,   125,   125,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   127,   127,   128,   128,   128,   128,
     129,   129,   129,   129,   129,   130,   130,   131,   131,   131,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   133,   134,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   136
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     4,     3,
       5,     3,    11,     0,     1,     0,     3,     4,     8,     0,
       3,     6,     6,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     2,     7,     4,     0,     3,     0,     3,
       1,     1,     1,     1,     1,     5,     7,     3,     3,     0,
       3,     2,     8,     2,     2,     4,     4,     2,     4,     0,
       2,     2,     4,     4,     0,     3,     3,     5,     5,     1,
       1,     1,     1,     1,     0,     3,     3,     3,     5,     5,
       0,     3,     5,     5,     3,     0,     3,     5,     0,     3,
       0,     3,     0,     4,     2,     0,     3,     1,     3,     0,
       3,     0,     3,     0,     6,     6,     8,     8,     6,     6,
       8,     8,     6,     6,     8,     8,     6,     6,     8,     8,
       6,     6,     8,     8,     0,     3,     3,     5,     3,     5,
       0,     4,     4,     6,     6,     0,     1,     0,     3,     3,
       3,     3,     3,     3,     5,     5,     7,     3,     4,     5,
       6,     6,     7,     8,     9,     5,     3,     5,     3,     3,
       2,     3,     4,     0,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     2,     8
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, scanner);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, void *scanner)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], scanner);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, void *scanner)
{
  YY_USE (yyvaluep);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  case 22: /* exit: EXIT SEMICOLON  */
#line 213 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1589 "yacc_sql.tab.c"
    break;

  case 23: /* help: HELP SEMICOLON  */
#line 218 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1597 "yacc_sql.tab.c"
    break;

  case 24: /* sync: SYNC SEMICOLON  */
#line 223 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1605 "yacc_sql.tab.c"
    break;

  case 25: /* begin: TRX_BEGIN SEMICOLON  */
#line 229 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1613 "yacc_sql.tab.c"
    break;

  case 26: /* commit: TRX_COMMIT SEMICOLON  */
#line 235 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1621 "yacc_sql.tab.c"
    break;

  case 27: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 241 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1629 "yacc_sql.tab.c"
    break;

  case 28: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 247 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1638 "yacc_sql.tab.c"
    break;

  case 29: /* show_tables: SHOW TABLES SEMICOLON  */
#line 253 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1646 "yacc_sql.tab.c"
    break;

  case 30: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 259 "yacc_sql.y"
                                     {
		CONTEXT->ssql->flag = SCF_SHOW_INDEX;
		show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
	}
#line 1655 "yacc_sql.tab.c"
    break;

  case 31: /* desc_table: DESC ID SEMICOLON  */
#line 266 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1664 "yacc_sql.tab.c"
    break;

  case 32: /* create_index: CREATE unique_option INDEX ID ON ID LBRACE ID index_attr_list RBRACE SEMICOLON  */
#line 274 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), (yyvsp[-3].string), CONTEXT->unique);
		}
#line 1673 "yacc_sql.tab.c"
    break;

  case 34: /* unique_option: UNIQUE  */
#line 281 "yacc_sql.y"
                 {
		CONTEXT->unique = 1;
	}
#line 1681 "yacc_sql.tab.c"
    break;

  case 36: /* index_attr_list: COMMA ID index_attr_list  */
#line 295 "yacc_sql.y"
                                   {
		create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[-1].string));
	}
#line 1689 "yacc_sql.tab.c"
    break;

  case 37: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 301 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1698 "yacc_sql.tab.c"
    break;

  case 38: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 308 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1710 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 318 "yacc_sql.y"
                                   {    }
#line 1716 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def: ID_get type LBRACE number RBRACE NONULL  */
#line 323 "yacc_sql.y"
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
#line 1731 "yacc_sql.tab.c"
    break;

  case 42: /* attr_def: ID_get type LBRACE number RBRACE NULLABLE  */
#line 334 "yacc_sql.y"
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
#line 1746 "yacc_sql.tab.c"
    break;

  case 43: /* attr_def: ID_get type NONULL  */
#line 345 "yacc_sql.y"
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
#line 1761 "yacc_sql.tab.c"
    break;

  case 44: /* attr_def: ID_get type NULLABLE  */
#line 356 "yacc_sql.y"
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
#line 1776 "yacc_sql.tab.c"
    break;

  case 45: /* number: NUMBER  */
#line 368 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1782 "yacc_sql.tab.c"
    break;

  case 46: /* type: INT_T  */
#line 371 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1788 "yacc_sql.tab.c"
    break;

  case 47: /* type: STRING_T  */
#line 372 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1794 "yacc_sql.tab.c"
    break;

  case 48: /* type: TEXT_T  */
#line 373 "yacc_sql.y"
                    {(yyval.number)=TEXTS; }
#line 1800 "yacc_sql.tab.c"
    break;

  case 49: /* type: FLOAT_T  */
#line 374 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1806 "yacc_sql.tab.c"
    break;

  case 50: /* type: DATE_T  */
#line 375 "yacc_sql.y"
                    {(yyval.number)=DATES;}
#line 1812 "yacc_sql.tab.c"
    break;

  case 51: /* ID_get: ID  */
#line 379 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1821 "yacc_sql.tab.c"
    break;

  case 54: /* insert: INSERT INTO ID VALUES tuple tuple_list SEMICOLON  */
#line 393 "yacc_sql.y"
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
#line 1841 "yacc_sql.tab.c"
    break;

  case 55: /* tuple: LBRACE value value_list RBRACE  */
#line 410 "yacc_sql.y"
                                       {
		CONTEXT->tuple_num++;
		printf("yacc: tuple num %d\n", CONTEXT->tuple_num);
	}
#line 1850 "yacc_sql.tab.c"
    break;

  case 57: /* tuple_list: COMMA tuple tuple_list  */
#line 417 "yacc_sql.y"
                                 {
	}
#line 1857 "yacc_sql.tab.c"
    break;

  case 59: /* value_list: COMMA value value_list  */
#line 422 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1865 "yacc_sql.tab.c"
    break;

  case 60: /* value: NUMBER  */
#line 427 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
  		value_init_integer(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], (yyvsp[0].number));
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
#line 1875 "yacc_sql.tab.c"
    break;

  case 61: /* value: FLOAT  */
#line 432 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		value_init_float(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], (yyvsp[0].floats));
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
#line 1885 "yacc_sql.tab.c"
    break;

  case 62: /* value: SSS  */
#line 437 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		value_init_string(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], (yyvsp[0].string));
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
#line 1896 "yacc_sql.tab.c"
    break;

  case 63: /* value: DATE_STR  */
#line 443 "yacc_sql.y"
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
#line 1917 "yacc_sql.tab.c"
    break;

  case 64: /* value: NULLVALUE  */
#line 459 "yacc_sql.y"
                   {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
		value_init_null(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++]);
	}
#line 1926 "yacc_sql.tab.c"
    break;

  case 65: /* delete: DELETE FROM ID where SEMICOLON  */
#line 467 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
			CONTEXT->last_conditino_seqno = 0;
    }
#line 1939 "yacc_sql.tab.c"
    break;

  case 66: /* update: UPDATE ID SET assign assign_list where SEMICOLON  */
#line 478 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-5].string), CONTEXT->attribute_name, CONTEXT->values, CONTEXT->upselect_num,
					CONTEXT->conditions, CONTEXT->condition_length, CONTEXT->upselect_vec);
			CONTEXT->condition_length = 0;
			CONTEXT->last_conditino_seqno = 0;
			CONTEXT->value_length = 0;
			CONTEXT->upselect_num = 0;
		}
#line 1953 "yacc_sql.tab.c"
    break;

  case 67: /* assign: ID EQ value  */
#line 490 "yacc_sql.y"
                    {
		CONTEXT->upselect_num++;
		CONTEXT->attribute_name[CONTEXT->value_length - 1] = (yyvsp[-2].string);
	}
#line 1962 "yacc_sql.tab.c"
    break;

  case 68: /* assign: ID EQ sub_query  */
#line 494 "yacc_sql.y"
                          {
		CONTEXT->upselect_num++;
		CONTEXT->value_length++;
		CONTEXT->attribute_name[CONTEXT->value_length - 1] = (yyvsp[-2].string);
		CONTEXT->upselect_vec[CONTEXT->value_length - 1] = &CONTEXT->sub_query->sstr.selection;
	}
#line 1973 "yacc_sql.tab.c"
    break;

  case 72: /* select_query: SELECT select_attr FROM ID rel_list where group order  */
#line 513 "yacc_sql.y"
                {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-4].string));

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
#line 1994 "yacc_sql.tab.c"
    break;

  case 73: /* select_attr: STAR attr_list  */
#line 532 "yacc_sql.y"
                   {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2004 "yacc_sql.tab.c"
    break;

  case 74: /* select_attr: ID attr_list  */
#line 537 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2014 "yacc_sql.tab.c"
    break;

  case 75: /* select_attr: ID DOT ID attr_list  */
#line 542 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2024 "yacc_sql.tab.c"
    break;

  case 76: /* select_attr: ID DOT STAR attr_list  */
#line 547 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			// CONTEXT->aggregation_op = NO_AGGREGATE_OP;
			// selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_op);
			// selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, AggregationOp::NO_AGGREGATE_OP);
		}
#line 2037 "yacc_sql.tab.c"
    break;

  case 77: /* select_attr: aggregate_attr aggregate_attr_list  */
#line 555 "yacc_sql.y"
                                             {
			
	}
#line 2045 "yacc_sql.tab.c"
    break;

  case 78: /* aggregate_attr: aggregate_op LBRACE aggregation_field_attr RBRACE  */
#line 570 "yacc_sql.y"
                                                          {
		// RelAttr attr;
		// relation_attr_init(&attr, NULL, $3);
		// printf("aggregation: get a attr %s\n", $3);
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		// selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		// CONTEXT->aggregation_num++;	
	}
#line 2058 "yacc_sql.tab.c"
    break;

  case 80: /* aggregation_field_attr: STAR aggrattr_list  */
#line 581 "yacc_sql.y"
                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		printf("aggregation: get a attr *\n");
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
#line 2072 "yacc_sql.tab.c"
    break;

  case 81: /* aggregation_field_attr: ID aggrattr_list  */
#line 590 "yacc_sql.y"
                           {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		printf("aggregation: get a attr %s\n", (yyvsp[-1].string));
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
#line 2086 "yacc_sql.tab.c"
    break;

  case 82: /* aggregation_field_attr: ID DOT ID aggrattr_list  */
#line 599 "yacc_sql.y"
                                  {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		printf("aggregation: get a attr %s\n", (yyvsp[-3].string));
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
#line 2100 "yacc_sql.tab.c"
    break;

  case 83: /* aggregation_field_attr: ID DOT STAR aggrattr_list  */
#line 608 "yacc_sql.y"
                                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), "*");
		printf("aggregation: get a attr %s\n", (yyvsp[-3].string));
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
#line 2114 "yacc_sql.tab.c"
    break;

  case 85: /* aggrattr_list: COMMA STAR aggrattr_list  */
#line 620 "yacc_sql.y"
                                   {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		printf("aggregation: get a attr *\n");
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2126 "yacc_sql.tab.c"
    break;

  case 86: /* aggrattr_list: COMMA ID aggrattr_list  */
#line 627 "yacc_sql.y"
                                 {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		printf("aggregation: get a attr %s\n", (yyvsp[-1].string));
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2138 "yacc_sql.tab.c"
    break;

  case 87: /* aggrattr_list: COMMA ID DOT ID aggrattr_list  */
#line 634 "yacc_sql.y"
                                        {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		printf("aggregation: get a attr %s\n", (yyvsp[-3].string));
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2150 "yacc_sql.tab.c"
    break;

  case 88: /* aggrattr_list: COMMA ID DOT STAR aggrattr_list  */
#line 641 "yacc_sql.y"
                                          {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), "*");
		printf("aggregation: get a attr %s\n", (yyvsp[-3].string));
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2162 "yacc_sql.tab.c"
    break;

  case 89: /* aggregate_op: COUNT  */
#line 651 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = COUNT_OP; }
#line 2168 "yacc_sql.tab.c"
    break;

  case 90: /* aggregate_op: AVG  */
#line 652 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = AVG_OP; }
#line 2174 "yacc_sql.tab.c"
    break;

  case 91: /* aggregate_op: MAX  */
#line 653 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = MAX_OP; }
#line 2180 "yacc_sql.tab.c"
    break;

  case 92: /* aggregate_op: MIN  */
#line 654 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = MIN_OP; }
#line 2186 "yacc_sql.tab.c"
    break;

  case 93: /* aggregate_op: SUM  */
#line 655 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = SUM_OP; }
#line 2192 "yacc_sql.tab.c"
    break;

  case 95: /* aggregate_attr_list: COMMA aggregate_attr aggregate_attr_list  */
#line 660 "yacc_sql.y"
                                                  {

	}
#line 2200 "yacc_sql.tab.c"
    break;

  case 96: /* aggregate_attr_list: COMMA STAR attr_list  */
#line 663 "yacc_sql.y"
                               {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2210 "yacc_sql.tab.c"
    break;

  case 97: /* aggregate_attr_list: COMMA ID attr_list  */
#line 668 "yacc_sql.y"
                            {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2220 "yacc_sql.tab.c"
    break;

  case 98: /* aggregate_attr_list: COMMA ID DOT ID attr_list  */
#line 673 "yacc_sql.y"
                                    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2230 "yacc_sql.tab.c"
    break;

  case 99: /* aggregate_attr_list: COMMA ID DOT STAR attr_list  */
#line 678 "yacc_sql.y"
                                      {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2240 "yacc_sql.tab.c"
    break;

  case 101: /* attr_list: COMMA ID attr_list  */
#line 687 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 2252 "yacc_sql.tab.c"
    break;

  case 102: /* attr_list: COMMA ID DOT ID attr_list  */
#line 694 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 2264 "yacc_sql.tab.c"
    break;

  case 103: /* attr_list: COMMA ID DOT STAR attr_list  */
#line 701 "yacc_sql.y"
                                      {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2274 "yacc_sql.tab.c"
    break;

  case 104: /* attr_list: COMMA aggregate_attr aggregate_attr_list  */
#line 706 "yacc_sql.y"
                                                   {

	}
#line 2282 "yacc_sql.tab.c"
    break;

  case 106: /* rel_list: COMMA ID rel_list  */
#line 713 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 2290 "yacc_sql.tab.c"
    break;

  case 107: /* rel_list: INNER JOIN ID on_list rel_list  */
#line 716 "yacc_sql.y"
                                         {
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string));
	}
#line 2298 "yacc_sql.tab.c"
    break;

  case 109: /* on_list: ON condition condition_list  */
#line 723 "yacc_sql.y"
                                      {

	}
#line 2306 "yacc_sql.tab.c"
    break;

  case 111: /* where: WHERE condition condition_list  */
#line 729 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2314 "yacc_sql.tab.c"
    break;

  case 112: /* group: %empty  */
#line 735 "yacc_sql.y"
        {
		selects_set_group(&CONTEXT->ssql->sstr.selection, 0);
	}
#line 2322 "yacc_sql.tab.c"
    break;

  case 113: /* group: GROUP BY group_attrs having  */
#line 738 "yacc_sql.y"
                                      {
		selects_set_group(&CONTEXT->ssql->sstr.selection, 1);
	}
#line 2330 "yacc_sql.tab.c"
    break;

  case 114: /* group_attrs: group_attr group_attr_list  */
#line 744 "yacc_sql.y"
                                   {
		// 递归。最新秒杀升级版。
	}
#line 2338 "yacc_sql.tab.c"
    break;

  case 116: /* group_attr_list: COMMA group_attr group_attr_list  */
#line 750 "yacc_sql.y"
                                           {
		// 递归。最新秒杀升级版。
	}
#line 2346 "yacc_sql.tab.c"
    break;

  case 117: /* group_attr: ID  */
#line 757 "yacc_sql.y"
           {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[0].string));
		selects_append_groupattr(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2356 "yacc_sql.tab.c"
    break;

  case 118: /* group_attr: ID DOT ID  */
#line 762 "yacc_sql.y"
                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
		selects_append_groupattr(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2366 "yacc_sql.tab.c"
    break;

  case 119: /* having: %empty  */
#line 770 "yacc_sql.y"
        {
		selects_set_having(&CONTEXT->ssql->sstr.selection, 0);
	}
#line 2374 "yacc_sql.tab.c"
    break;

  case 120: /* having: HAVING having_condition having_condition_list  */
#line 773 "yacc_sql.y"
                                                        {
		// 递归
		selects_set_having(&CONTEXT->ssql->sstr.selection, 1);
	}
#line 2383 "yacc_sql.tab.c"
    break;

  case 122: /* having_condition_list: COMMA having_condition having_condition_list  */
#line 780 "yacc_sql.y"
                                                      {
		// 递归
	}
#line 2391 "yacc_sql.tab.c"
    break;

  case 124: /* having_condition: COUNT LBRACE ID RBRACE comOp value  */
#line 790 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, COUNT_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2403 "yacc_sql.tab.c"
    break;

  case 125: /* having_condition: COUNT LBRACE STAR RBRACE comOp value  */
#line 797 "yacc_sql.y"
                                               {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		Having_Condition condition;
		having_condition_init(&condition, COUNT_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2415 "yacc_sql.tab.c"
    break;

  case 126: /* having_condition: COUNT LBRACE ID DOT ID RBRACE comOp value  */
#line 804 "yacc_sql.y"
                                                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, COUNT_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2427 "yacc_sql.tab.c"
    break;

  case 127: /* having_condition: COUNT LBRACE ID DOT STAR RBRACE comOp value  */
#line 811 "yacc_sql.y"
                                                      {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), "*");
		Having_Condition condition;
		having_condition_init(&condition, COUNT_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2439 "yacc_sql.tab.c"
    break;

  case 128: /* having_condition: AVG LBRACE ID RBRACE comOp value  */
#line 818 "yacc_sql.y"
                                           {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, AVG_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2451 "yacc_sql.tab.c"
    break;

  case 129: /* having_condition: AVG LBRACE STAR RBRACE comOp value  */
#line 825 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		Having_Condition condition;
		having_condition_init(&condition, AVG_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2463 "yacc_sql.tab.c"
    break;

  case 130: /* having_condition: AVG LBRACE ID DOT ID RBRACE comOp value  */
#line 832 "yacc_sql.y"
                                                  {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, AVG_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2475 "yacc_sql.tab.c"
    break;

  case 131: /* having_condition: AVG LBRACE ID DOT STAR RBRACE comOp value  */
#line 839 "yacc_sql.y"
                                                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), "*");
		Having_Condition condition;
		having_condition_init(&condition, AVG_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2487 "yacc_sql.tab.c"
    break;

  case 132: /* having_condition: MAX LBRACE ID RBRACE comOp value  */
#line 846 "yacc_sql.y"
                                           {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, MAX_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2499 "yacc_sql.tab.c"
    break;

  case 133: /* having_condition: MAX LBRACE STAR RBRACE comOp value  */
#line 853 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		Having_Condition condition;
		having_condition_init(&condition, MAX_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2511 "yacc_sql.tab.c"
    break;

  case 134: /* having_condition: MAX LBRACE ID DOT ID RBRACE comOp value  */
#line 860 "yacc_sql.y"
                                                  {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, MAX_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2523 "yacc_sql.tab.c"
    break;

  case 135: /* having_condition: MAX LBRACE ID DOT STAR RBRACE comOp value  */
#line 867 "yacc_sql.y"
                                                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), "*");
		Having_Condition condition;
		having_condition_init(&condition, MAX_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2535 "yacc_sql.tab.c"
    break;

  case 136: /* having_condition: MIN LBRACE ID RBRACE comOp value  */
#line 874 "yacc_sql.y"
                                           {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, MIN_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2547 "yacc_sql.tab.c"
    break;

  case 137: /* having_condition: MIN LBRACE STAR RBRACE comOp value  */
#line 881 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		Having_Condition condition;
		having_condition_init(&condition, MIN_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2559 "yacc_sql.tab.c"
    break;

  case 138: /* having_condition: MIN LBRACE ID DOT ID RBRACE comOp value  */
#line 888 "yacc_sql.y"
                                                  {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, MIN_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2571 "yacc_sql.tab.c"
    break;

  case 139: /* having_condition: MIN LBRACE ID DOT STAR RBRACE comOp value  */
#line 895 "yacc_sql.y"
                                                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), "*");
		Having_Condition condition;
		having_condition_init(&condition, MIN_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2583 "yacc_sql.tab.c"
    break;

  case 140: /* having_condition: SUM LBRACE ID RBRACE comOp value  */
#line 902 "yacc_sql.y"
                                           {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, SUM_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2595 "yacc_sql.tab.c"
    break;

  case 141: /* having_condition: SUM LBRACE STAR RBRACE comOp value  */
#line 909 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "$3");
		Having_Condition condition;
		having_condition_init(&condition, SUM_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2607 "yacc_sql.tab.c"
    break;

  case 142: /* having_condition: SUM LBRACE ID DOT ID RBRACE comOp value  */
#line 916 "yacc_sql.y"
                                                  {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, SUM_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2619 "yacc_sql.tab.c"
    break;

  case 143: /* having_condition: SUM LBRACE ID DOT STAR RBRACE comOp value  */
#line 923 "yacc_sql.y"
                                                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), "*");
		Having_Condition condition;
		having_condition_init(&condition, SUM_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2631 "yacc_sql.tab.c"
    break;

  case 144: /* order: %empty  */
#line 933 "yacc_sql.y"
        {
		selects_set_order(&CONTEXT->ssql->sstr.selection, 0);
	}
#line 2639 "yacc_sql.tab.c"
    break;

  case 145: /* order: ORDER BY order_attr  */
#line 936 "yacc_sql.y"
                              {
		selects_set_order(&CONTEXT->ssql->sstr.selection, 1);
	}
#line 2647 "yacc_sql.tab.c"
    break;

  case 146: /* order_attr: ID asc order_attr_list  */
#line 942 "yacc_sql.y"
                               {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
		}
#line 2657 "yacc_sql.tab.c"
    break;

  case 147: /* order_attr: ID DOT ID asc order_attr_list  */
#line 947 "yacc_sql.y"
                                        {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
		}
#line 2667 "yacc_sql.tab.c"
    break;

  case 148: /* order_attr: ID DESC order_attr_list  */
#line 952 "yacc_sql.y"
                                  {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
		}
#line 2677 "yacc_sql.tab.c"
    break;

  case 149: /* order_attr: ID DOT ID DESC order_attr_list  */
#line 957 "yacc_sql.y"
                                         {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
		}
#line 2687 "yacc_sql.tab.c"
    break;

  case 151: /* order_attr_list: COMMA ID asc order_attr_list  */
#line 966 "yacc_sql.y"
                                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
      }
#line 2697 "yacc_sql.tab.c"
    break;

  case 152: /* order_attr_list: COMMA ID DESC order_attr_list  */
#line 971 "yacc_sql.y"
                                    {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
      }
#line 2707 "yacc_sql.tab.c"
    break;

  case 153: /* order_attr_list: COMMA ID DOT ID asc order_attr_list  */
#line 976 "yacc_sql.y"
                                          {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
  	  }
#line 2717 "yacc_sql.tab.c"
    break;

  case 154: /* order_attr_list: COMMA ID DOT ID DESC order_attr_list  */
#line 981 "yacc_sql.y"
                                           {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
  	  }
#line 2727 "yacc_sql.tab.c"
    break;

  case 158: /* condition_list: AND condition condition_list  */
#line 994 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
				if (CONTEXT->last_conditino_seqno == 0) {
					CONTEXT->last_conditino_seqno = CONTEXT->condition_length;
				}
				CONTEXT->conditions[CONTEXT->last_conditino_seqno-1].is_and = 1;
				CONTEXT->last_conditino_seqno--;
				printf("get an and condition: seqno %d\n", CONTEXT->last_conditino_seqno);
			}
#line 2741 "yacc_sql.tab.c"
    break;

  case 159: /* condition_list: OR condition condition_list  */
#line 1003 "yacc_sql.y"
                                  {
				if (CONTEXT->last_conditino_seqno == 0) {
					CONTEXT->last_conditino_seqno = CONTEXT->condition_length;
				}
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
				CONTEXT->conditions[CONTEXT->last_conditino_seqno-1].is_and = 0;
				CONTEXT->last_conditino_seqno--;
				printf("get an or condition: seqno %d\n", CONTEXT->last_conditino_seqno);
			}
#line 2755 "yacc_sql.tab.c"
    break;

  case 160: /* condition: ID comOp value  */
#line 1015 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

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
#line 2781 "yacc_sql.tab.c"
    break;

  case 161: /* condition: value comOp value  */
#line 1037 "yacc_sql.y"
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
#line 2806 "yacc_sql.tab.c"
    break;

  case 162: /* condition: ID comOp ID  */
#line 1058 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

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
#line 2831 "yacc_sql.tab.c"
    break;

  case 163: /* condition: value comOp ID  */
#line 1079 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

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
#line 2858 "yacc_sql.tab.c"
    break;

  case 164: /* condition: ID DOT ID comOp value  */
#line 1102 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
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
#line 2884 "yacc_sql.tab.c"
    break;

  case 165: /* condition: value comOp ID DOT ID  */
#line 1124 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

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
#line 2910 "yacc_sql.tab.c"
    break;

  case 166: /* condition: ID DOT ID comOp ID DOT ID  */
#line 1146 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

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
#line 2934 "yacc_sql.tab.c"
    break;

  case 167: /* condition: ID IN sub_query  */
#line 1165 "yacc_sql.y"
                          {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

		Condition condition;
		condition_init(&condition, Contain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		
	}
#line 2948 "yacc_sql.tab.c"
    break;

  case 168: /* condition: ID NOT IN sub_query  */
#line 1174 "yacc_sql.y"
                              {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-3].string));

		Condition condition;
		condition_init(&condition, NotContain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 2962 "yacc_sql.tab.c"
    break;

  case 169: /* condition: ID DOT ID IN sub_query  */
#line 1183 "yacc_sql.y"
                                 {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));

		Condition condition;
		condition_init(&condition, Contain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		
	}
#line 2976 "yacc_sql.tab.c"
    break;

  case 170: /* condition: ID DOT ID NOT IN sub_query  */
#line 1192 "yacc_sql.y"
                                     {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-5].string), (yyvsp[-3].string));

		Condition condition;
		condition_init(&condition, NotContain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 2990 "yacc_sql.tab.c"
    break;

  case 171: /* condition: ID IN LBRACE value value_list RBRACE  */
#line 1201 "yacc_sql.y"
                                               {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-5].string));

		Condition condition;
		condition_init(&condition, Contain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, 
			CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length = 0;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 3006 "yacc_sql.tab.c"
    break;

  case 172: /* condition: ID NOT IN LBRACE value value_list RBRACE  */
#line 1212 "yacc_sql.y"
                                                   {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-6].string));

		Condition condition;
		condition_init(&condition, NotContain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, 
			CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length = 0;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 3022 "yacc_sql.tab.c"
    break;

  case 173: /* condition: ID DOT ID IN LBRACE value value_list RBRACE  */
#line 1223 "yacc_sql.y"
                                                      {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-7].string), (yyvsp[-5].string));

		Condition condition;
		condition_init(&condition, Contain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, 
			CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length = 0;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 3038 "yacc_sql.tab.c"
    break;

  case 174: /* condition: ID DOT ID NOT IN LBRACE value value_list RBRACE  */
#line 1234 "yacc_sql.y"
                                                          {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-8].string), (yyvsp[-6].string));

		Condition condition;
		condition_init(&condition, NotContain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, 
			CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length = 0;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 3054 "yacc_sql.tab.c"
    break;

  case 175: /* condition: ID DOT ID comOp sub_query  */
#line 1245 "yacc_sql.y"
                                    {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));

		Condition condition;
		condition_init(&condition, Comparison, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 3067 "yacc_sql.tab.c"
    break;

  case 176: /* condition: ID comOp sub_query  */
#line 1253 "yacc_sql.y"
                             {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

		Condition condition;
		condition_init(&condition, Comparison, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 3080 "yacc_sql.tab.c"
    break;

  case 177: /* condition: sub_query comOp ID DOT ID  */
#line 1261 "yacc_sql.y"
                                    {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-2].string), (yyvsp[0].string));

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
#line 3109 "yacc_sql.tab.c"
    break;

  case 178: /* condition: sub_query comOp ID  */
#line 1285 "yacc_sql.y"
                             {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[0].string));

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
#line 3137 "yacc_sql.tab.c"
    break;

  case 179: /* condition: sub_query comOp sub_query  */
#line 1308 "yacc_sql.y"
                                    {
		Condition condition;
		condition_init(&condition, Comparison, CONTEXT->comp, 0, 1, NULL, NULL, &CONTEXT->left_sub_query->sstr.selection, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 3148 "yacc_sql.tab.c"
    break;

  case 180: /* condition: EXISTS sub_query  */
#line 1314 "yacc_sql.y"
                           {

		Condition condition;
		condition_init(&condition, Exists, CONTEXT->comp, 0, 0, NULL, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 3160 "yacc_sql.tab.c"
    break;

  case 181: /* condition: NOT EXISTS sub_query  */
#line 1321 "yacc_sql.y"
                               {

		Condition condition;
		condition_init(&condition, NotExists, CONTEXT->comp, 0, 0, NULL, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 3172 "yacc_sql.tab.c"
    break;

  case 182: /* sub_query: LBRACE N select_query RBRACE  */
#line 1331 "yacc_sql.y"
                                     {
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
	}
#line 3190 "yacc_sql.tab.c"
    break;

  case 183: /* N: %empty  */
#line 1344 "yacc_sql.y"
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
	// old_context->last_context = CONTEXT->last_context;
	CONTEXT->last_context = old_context;
	printf("swap out old context addr %p\n", old_context);
}
#line 3210 "yacc_sql.tab.c"
    break;

  case 184: /* comOp: EQ  */
#line 1362 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 3216 "yacc_sql.tab.c"
    break;

  case 185: /* comOp: LT  */
#line 1363 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 3222 "yacc_sql.tab.c"
    break;

  case 186: /* comOp: GT  */
#line 1364 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 3228 "yacc_sql.tab.c"
    break;

  case 187: /* comOp: LE  */
#line 1365 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 3234 "yacc_sql.tab.c"
    break;

  case 188: /* comOp: GE  */
#line 1366 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 3240 "yacc_sql.tab.c"
    break;

  case 189: /* comOp: NE  */
#line 1367 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 3246 "yacc_sql.tab.c"
    break;

  case 190: /* comOp: IS  */
#line 1368 "yacc_sql.y"
             { CONTEXT->comp = LOGICAL_IS; }
#line 3252 "yacc_sql.tab.c"
    break;

  case 191: /* comOp: IS NOT  */
#line 1369 "yacc_sql.y"
                 {CONTEXT->comp = LOGICAL_IS_NOT; }
#line 3258 "yacc_sql.tab.c"
    break;

  case 192: /* comOp: LIKE  */
#line 1370 "yacc_sql.y"
               { CONTEXT->comp = LIKE_OP; }
#line 3264 "yacc_sql.tab.c"
    break;

  case 193: /* comOp: NOT LIKE  */
#line 1371 "yacc_sql.y"
                   { CONTEXT->comp = NOT_LIKE_OP; }
#line 3270 "yacc_sql.tab.c"
    break;

  case 194: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 1376 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 3279 "yacc_sql.tab.c"
    break;


#line 3283 "yacc_sql.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (scanner, YY_("syntax error"));
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1381 "yacc_sql.y"

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
