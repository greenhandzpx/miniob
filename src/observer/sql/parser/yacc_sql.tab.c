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
  size_t from_length;

  size_t tuple_num;
  size_t value_num[MAX_NUM];       // Length of values
  Value tuples[MAX_NUM][MAX_NUM];  // values to insert

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


#line 145 "yacc_sql.tab.c"

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
  YYSYMBOL_NUMBER = 65,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 66,                     /* FLOAT  */
  YYSYMBOL_ID = 67,                        /* ID  */
  YYSYMBOL_PATH = 68,                      /* PATH  */
  YYSYMBOL_SSS = 69,                       /* SSS  */
  YYSYMBOL_STAR = 70,                      /* STAR  */
  YYSYMBOL_STRING_V = 71,                  /* STRING_V  */
  YYSYMBOL_DATE_STR = 72,                  /* DATE_STR  */
  YYSYMBOL_NULLVALUE = 73,                 /* NULLVALUE  */
  YYSYMBOL_YYACCEPT = 74,                  /* $accept  */
  YYSYMBOL_commands = 75,                  /* commands  */
  YYSYMBOL_command = 76,                   /* command  */
  YYSYMBOL_exit = 77,                      /* exit  */
  YYSYMBOL_help = 78,                      /* help  */
  YYSYMBOL_sync = 79,                      /* sync  */
  YYSYMBOL_begin = 80,                     /* begin  */
  YYSYMBOL_commit = 81,                    /* commit  */
  YYSYMBOL_rollback = 82,                  /* rollback  */
  YYSYMBOL_drop_table = 83,                /* drop_table  */
  YYSYMBOL_show_tables = 84,               /* show_tables  */
  YYSYMBOL_show_index = 85,                /* show_index  */
  YYSYMBOL_desc_table = 86,                /* desc_table  */
  YYSYMBOL_create_index = 87,              /* create_index  */
  YYSYMBOL_unique_option = 88,             /* unique_option  */
  YYSYMBOL_index_attr_list = 89,           /* index_attr_list  */
  YYSYMBOL_drop_index = 90,                /* drop_index  */
  YYSYMBOL_create_table = 91,              /* create_table  */
  YYSYMBOL_attr_def_list = 92,             /* attr_def_list  */
  YYSYMBOL_attr_def = 93,                  /* attr_def  */
  YYSYMBOL_number = 94,                    /* number  */
  YYSYMBOL_type = 95,                      /* type  */
  YYSYMBOL_ID_get = 96,                    /* ID_get  */
  YYSYMBOL_NONULL = 97,                    /* NONULL  */
  YYSYMBOL_insert = 98,                    /* insert  */
  YYSYMBOL_tuple = 99,                     /* tuple  */
  YYSYMBOL_tuple_list = 100,               /* tuple_list  */
  YYSYMBOL_value_list = 101,               /* value_list  */
  YYSYMBOL_value = 102,                    /* value  */
  YYSYMBOL_delete = 103,                   /* delete  */
  YYSYMBOL_update = 104,                   /* update  */
  YYSYMBOL_select = 105,                   /* select  */
  YYSYMBOL_select_query = 106,             /* select_query  */
  YYSYMBOL_select_attr = 107,              /* select_attr  */
  YYSYMBOL_aggregate_attr = 108,           /* aggregate_attr  */
  YYSYMBOL_aggregation_field_attr = 109,   /* aggregation_field_attr  */
  YYSYMBOL_aggrattr_list = 110,            /* aggrattr_list  */
  YYSYMBOL_aggregate_op = 111,             /* aggregate_op  */
  YYSYMBOL_aggregate_attr_list = 112,      /* aggregate_attr_list  */
  YYSYMBOL_attr_list = 113,                /* attr_list  */
  YYSYMBOL_rel_list = 114,                 /* rel_list  */
  YYSYMBOL_on_list = 115,                  /* on_list  */
  YYSYMBOL_where = 116,                    /* where  */
  YYSYMBOL_group = 117,                    /* group  */
  YYSYMBOL_group_attrs = 118,              /* group_attrs  */
  YYSYMBOL_group_attr_list = 119,          /* group_attr_list  */
  YYSYMBOL_group_attr = 120,               /* group_attr  */
  YYSYMBOL_having = 121,                   /* having  */
  YYSYMBOL_having_condition_list = 122,    /* having_condition_list  */
  YYSYMBOL_having_condition = 123,         /* having_condition  */
  YYSYMBOL_order = 124,                    /* order  */
  YYSYMBOL_order_attr = 125,               /* order_attr  */
  YYSYMBOL_order_attr_list = 126,          /* order_attr_list  */
  YYSYMBOL_asc = 127,                      /* asc  */
  YYSYMBOL_condition_list = 128,           /* condition_list  */
  YYSYMBOL_condition = 129,                /* condition  */
  YYSYMBOL_sub_query = 130,                /* sub_query  */
  YYSYMBOL_N = 131,                        /* N  */
  YYSYMBOL_comOp = 132,                    /* comOp  */
  YYSYMBOL_load_data = 133                 /* load_data  */
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
#define YYLAST   408

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  60
/* YYNRULES -- Number of rules.  */
#define YYNRULES  181
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  416

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   328


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
      65,    66,    67,    68,    69,    70,    71,    72,    73
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   177,   177,   179,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   204,   209,   214,   220,   226,   232,   238,   244,
     250,   257,   264,   270,   272,   284,   286,   291,   298,   307,
     309,   313,   324,   335,   346,   359,   362,   363,   364,   365,
     366,   369,   376,   377,   383,   401,   406,   408,   411,   413,
     418,   423,   428,   434,   450,   457,   467,   478,   481,   501,
     506,   511,   516,   524,   539,   548,   550,   559,   568,   577,
     588,   589,   596,   603,   610,   620,   621,   622,   623,   624,
     627,   629,   632,   637,   642,   647,   654,   656,   663,   670,
     675,   680,   682,   685,   690,   692,   696,   698,   704,   707,
     713,   718,   719,   726,   731,   739,   742,   748,   749,   758,
     759,   766,   773,   780,   787,   794,   801,   808,   815,   822,
     829,   836,   843,   850,   857,   864,   871,   878,   885,   892,
     902,   905,   911,   916,   921,   926,   933,   935,   940,   945,
     950,   957,   958,   961,   963,   968,   990,  1011,  1032,  1055,
    1077,  1099,  1119,  1128,  1137,  1148,  1159,  1167,  1174,  1184,
    1192,  1210,  1211,  1212,  1213,  1214,  1215,  1216,  1217,  1218,
    1219,  1223
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
  "ASC", "GROUP", "HAVING", "NUMBER", "FLOAT", "ID", "PATH", "SSS", "STAR",
  "STRING_V", "DATE_STR", "NULLVALUE", "$accept", "commands", "command",
  "exit", "help", "sync", "begin", "commit", "rollback", "drop_table",
  "show_tables", "show_index", "desc_table", "create_index",
  "unique_option", "index_attr_list", "drop_index", "create_table",
  "attr_def_list", "attr_def", "number", "type", "ID_get", "NONULL",
  "insert", "tuple", "tuple_list", "value_list", "value", "delete",
  "update", "select", "select_query", "select_attr", "aggregate_attr",
  "aggregation_field_attr", "aggrattr_list", "aggregate_op",
  "aggregate_attr_list", "attr_list", "rel_list", "on_list", "where",
  "group", "group_attrs", "group_attr_list", "group_attr", "having",
  "having_condition_list", "having_condition", "order", "order_attr",
  "order_attr_list", "asc", "condition_list", "condition", "sub_query",
  "N", "comOp", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-305)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -305,   109,  -305,    11,   102,   111,   -53,   118,    33,    -8,
      26,   -23,    85,    92,    99,   139,   140,   100,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305,   146,  -305,    90,  -305,
     156,    91,   108,  -305,  -305,  -305,  -305,  -305,     1,   148,
     144,   162,   205,   186,   226,   202,  -305,   155,   185,   225,
    -305,  -305,  -305,  -305,  -305,   243,  -305,   248,   220,   286,
     287,   135,   -30,  -305,  -305,   229,   121,  -305,   -10,  -305,
    -305,   236,   273,   274,   241,   240,   244,   276,  -305,  -305,
      62,   162,   148,   148,    -6,    72,   148,   162,    75,   292,
     296,   311,   299,   219,   313,   277,   288,  -305,   301,   193,
     253,    19,  -305,  -305,  -305,  -305,   254,   268,   274,    77,
    -305,  -305,  -305,    78,   107,  -305,  -305,  -305,  -305,   233,
     305,   308,   269,  -305,  -305,   110,  -305,  -305,  -305,   168,
     293,  -305,   233,   320,   244,   312,  -305,  -305,  -305,  -305,
    -305,    34,   314,   148,   148,    -6,   261,   270,   148,   148,
      76,   292,   292,   292,   316,   299,   328,  -305,  -305,   308,
     265,  -305,  -305,  -305,  -305,  -305,  -305,   278,   319,  -305,
     150,   190,   280,   228,   219,  -305,   274,   271,   301,   336,
     275,  -305,   272,  -305,   279,  -305,  -305,  -305,   306,   282,
     281,  -305,  -305,   112,  -305,  -305,  -305,  -305,   233,   327,
     305,  -305,   338,  -305,   168,  -305,   233,  -305,   332,  -305,
    -305,  -305,   321,  -305,   293,   346,   348,  -305,  -305,  -305,
     335,  -305,   337,   219,    -6,   289,   297,  -305,   292,   292,
     316,  -305,  -305,   340,     2,   316,   233,  -305,   294,  -305,
    -305,  -305,    69,   295,   342,   293,  -305,   324,   290,   345,
     298,  -305,  -305,  -305,  -305,   331,  -305,  -305,   347,   316,
    -305,  -305,  -305,   337,   363,  -305,   300,    83,  -305,   289,
    -305,    -1,  -305,   302,  -305,   351,  -305,  -305,  -305,   354,
     355,   356,   357,   358,   359,   345,   360,   309,  -305,   360,
    -305,  -305,   123,   129,   163,   173,   177,    83,  -305,  -305,
     315,  -305,    14,  -305,    -2,   362,     6,   364,    12,   366,
      67,   367,    68,   368,   359,    10,   360,   360,   168,   181,
     168,   168,   191,   168,   168,   209,   168,   168,   211,   168,
     168,   213,   168,  -305,   360,   322,   360,  -305,  -305,   233,
     369,   370,   233,   233,   371,   373,   233,   233,   374,   375,
     233,   233,   376,   377,   233,   233,   378,   379,   233,  -305,
      15,  -305,  -305,   168,   168,  -305,  -305,   168,   168,  -305,
    -305,   168,   168,  -305,  -305,   168,   168,  -305,  -305,   168,
     168,  -305,   360,   360,   233,   233,   233,   233,   233,   233,
     233,   233,   233,   233,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,  -305
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
       0,     0,     0,    85,    86,    87,    88,    89,    96,    96,
       0,    90,     0,     0,     0,     0,    24,     0,     0,     0,
      25,    26,    27,    23,    22,     0,    67,     0,     0,     0,
       0,     0,     0,    70,    69,     0,     0,    73,    75,    31,
      29,     0,     0,   106,     0,     0,     0,     0,    28,    37,
      96,    90,    96,    96,   101,    96,    96,    90,    80,    80,
       0,     0,     0,     0,     0,     0,     0,    51,    39,     0,
       0,     0,    97,   100,    71,    72,     0,     0,   106,     0,
      93,    92,    91,     0,     0,    77,    76,    74,    30,     0,
      56,     0,     0,    60,    61,     0,    62,    63,    64,     0,
     153,    65,     0,     0,     0,     0,    46,    47,    48,    49,
      50,    52,     0,    96,    96,   101,     0,   108,    96,    96,
      80,    80,    80,    80,    58,     0,     0,   170,   167,     0,
       0,   171,   172,   173,   174,   175,   176,   177,     0,   179,
       0,     0,     0,     0,     0,   107,   106,     0,    39,     0,
       0,    44,     0,    43,     0,    98,    99,   102,   104,     0,
     140,    94,    95,     0,    82,    81,    78,    79,     0,     0,
      56,    54,     0,   168,     0,   178,   170,   162,     0,   180,
     157,   155,   158,   156,   153,     0,     0,    40,    38,    45,
       0,    53,    35,     0,   101,     0,     0,    68,    80,    80,
      58,    55,    57,     0,     0,    58,   170,   163,     0,   154,
      66,   181,    52,     0,     0,   153,   103,   113,   115,   111,
       0,    83,    84,    59,   169,     0,   159,   166,     0,    58,
     160,    42,    41,    35,     0,   105,     0,   119,   109,     0,
     110,   151,   141,     0,   164,     0,    36,    32,   114,     0,
       0,     0,     0,     0,   117,   111,   146,     0,   152,   146,
     161,   165,     0,     0,     0,     0,     0,   119,   116,   112,
       0,   144,   151,   142,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   117,   151,   146,   146,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   118,   146,     0,   146,   145,   143,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   148,
     151,   147,   120,     0,     0,   121,   124,     0,     0,   125,
     128,     0,     0,   129,   132,     0,     0,   133,   136,     0,
       0,   137,   146,   146,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   150,   149,   122,   123,   126,   127,
     130,   131,   134,   135,   138,   139
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,  -305,
    -305,  -305,  -305,  -305,  -305,   124,  -305,  -305,   187,   255,
    -305,  -305,  -305,   128,  -305,   235,   188,  -214,  -129,  -305,
    -305,  -305,   189,  -305,    27,  -305,   -98,  -305,   -59,   -47,
    -151,  -305,  -113,  -305,  -305,   113,   125,  -305,    79,    95,
    -305,  -305,  -293,  -304,  -213,  -174,  -162,  -305,  -136,  -305
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    40,   254,    30,    31,   145,   108,
     230,   151,   109,   193,    32,   130,   166,   209,   139,    33,
      34,    35,    36,    50,    51,   100,   125,    52,    77,    73,
     118,   234,   104,   200,   258,   280,   259,   278,   308,   294,
     237,   282,   311,   299,   185,   140,   168,   212,   181,    37
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     164,   126,    74,   183,   197,   157,   313,   213,   327,   296,
     224,   249,   116,   186,    53,   328,   217,    38,   167,    71,
     344,   346,    57,   331,   326,   392,   263,   329,   297,   334,
      72,   268,   113,   347,   348,   332,    56,    92,   122,   345,
      93,   335,   275,   112,    59,   114,   115,   117,   120,   121,
     190,   369,   221,   371,   223,   285,   247,    98,    58,   255,
      99,   298,   204,   205,   206,   207,   393,   133,   134,   265,
      39,   136,   298,   225,   137,   138,   298,   298,   244,   240,
      71,   191,   267,   256,   337,   340,   153,   245,    60,   154,
      71,   111,   192,   123,   123,    61,   338,   341,    91,   404,
     405,   119,    62,    97,   124,   203,   195,   196,    41,     2,
      42,   201,   202,     3,     4,   266,   271,   269,     5,     6,
       7,     8,     9,    10,    11,    54,    55,   192,    12,    13,
      14,   289,   290,   291,   292,   293,    15,    16,    65,   170,
     261,   262,    63,    64,   158,   160,    17,   159,   161,    66,
     171,   172,   173,   174,   175,   176,   177,    67,    69,    43,
      44,    45,    46,    47,    68,   178,    71,   179,   180,    43,
      44,    45,    46,    47,   162,    70,    75,   163,    48,   238,
      76,    49,   239,    43,    44,    45,    46,    47,    95,    79,
     314,    96,   349,   315,   352,   353,   316,   356,   357,   317,
     360,   361,    90,   364,   365,   218,   368,   219,   171,   172,
     173,   174,   175,   176,   177,   146,   147,   148,   149,   150,
     372,    78,    82,   375,   376,   179,   182,   379,   380,    80,
     318,   383,   384,   319,    81,   387,   388,   394,   395,   391,
     320,   396,   397,   321,   322,   398,   399,   323,   350,   400,
     401,   351,    83,   402,   403,   133,   134,   220,   354,   136,
      84,   355,   137,   138,    86,   406,   407,   408,   409,   410,
     411,   412,   413,   414,   415,   131,   358,   132,   362,   359,
     366,   363,    85,   367,   133,   134,   135,    87,   136,    88,
      89,   137,   138,   133,   134,   222,    94,   136,   133,   134,
     137,   138,   136,   101,   102,   137,   138,   103,   105,   106,
     123,   107,   110,   127,   128,   129,   141,   142,   143,   144,
     152,   155,   156,   165,   167,   169,   187,   184,   198,   189,
     194,   211,   214,   199,   208,   216,   215,   219,   226,   228,
     229,   236,   233,   235,   241,   231,   232,     5,   246,   250,
     248,   251,   252,   276,   277,   253,   257,   264,   260,   274,
     283,   270,   273,   279,   284,   281,   287,   288,   301,   300,
     302,   303,   304,   305,   306,   227,   312,   307,   310,   330,
     272,   333,   325,   336,   339,   342,   373,   374,   377,   370,
     378,   381,   382,   385,   386,   389,   390,   286,   242,   188,
     210,   243,   324,   343,   295,     0,     0,     0,   309
};

static const yytype_int16 yycheck[] =
{
     129,    99,    49,   139,   155,   118,   299,   169,   312,    10,
     184,   224,    18,   142,    67,    17,   178,     6,    16,    18,
      10,   325,    30,    17,    10,    10,   240,    29,    29,    17,
      29,   245,    91,   326,   327,    29,     3,    67,    97,    29,
      70,    29,   255,    90,    67,    92,    93,    53,    95,    96,
      16,   344,   181,   346,   183,   269,   218,    67,    32,   233,
      70,    62,   160,   161,   162,   163,   370,    65,    66,    67,
      59,    69,    62,   186,    72,    73,    62,    62,   214,   208,
      18,    47,   244,   234,    17,    17,    67,   216,     3,    70,
      18,    29,    58,    18,    18,     3,    29,    29,    71,   392,
     393,    29,     3,    76,    29,    29,   153,   154,     6,     0,
       8,   158,   159,     4,     5,   244,    47,   246,     9,    10,
      11,    12,    13,    14,    15,     7,     8,    58,    19,    20,
      21,    48,    49,    50,    51,    52,    27,    28,    38,    29,
     238,   239,     3,     3,    67,    67,    37,    70,    70,     3,
      40,    41,    42,    43,    44,    45,    46,    67,    67,    48,
      49,    50,    51,    52,     8,    55,    18,    57,    58,    48,
      49,    50,    51,    52,    67,    67,    32,    70,    67,    67,
      18,    70,    70,    48,    49,    50,    51,    52,    67,     3,
      67,    70,   328,    70,   330,   331,    67,   333,   334,    70,
     336,   337,    67,   339,   340,    55,   342,    57,    40,    41,
      42,    43,    44,    45,    46,    22,    23,    24,    25,    26,
     349,    16,    67,   352,   353,    57,    58,   356,   357,     3,
      67,   360,   361,    70,    32,   364,   365,   373,   374,   368,
      67,   377,   378,    70,    67,   381,   382,    70,    67,   385,
     386,    70,    67,   389,   390,    65,    66,    67,    67,    69,
      35,    70,    72,    73,    16,   394,   395,   396,   397,   398,
     399,   400,   401,   402,   403,    56,    67,    58,    67,    70,
      67,    70,    39,    70,    65,    66,    67,    67,    69,     3,
       3,    72,    73,    65,    66,    67,    67,    69,    65,    66,
      72,    73,    69,    67,    31,    72,    73,    33,    67,    69,
      18,    67,    36,    17,     3,    16,     3,    40,    30,    18,
      67,    67,    54,    18,    16,    56,     6,    34,    67,    17,
      16,     3,    67,    63,    18,    16,    58,    57,    67,     3,
      65,    60,    36,    61,    17,    73,    67,     9,    16,     3,
      29,     3,    17,    29,    64,    18,    67,    17,    61,    17,
      29,    67,    67,    18,    17,    67,     3,    67,    17,    67,
      16,    16,    16,    16,    16,   188,    67,    18,    18,    17,
     252,    17,    67,    17,    17,    17,    17,    17,    17,    67,
      17,    17,    17,    17,    17,    17,    17,   273,   210,   144,
     165,   212,   307,   324,   279,    -1,    -1,    -1,   295
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    75,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    19,    20,    21,    27,    28,    37,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      90,    91,    98,   103,   104,   105,   106,   133,     6,    59,
      88,     6,     8,    48,    49,    50,    51,    52,    67,    70,
     107,   108,   111,    67,     7,     8,     3,    30,    32,    67,
       3,     3,     3,     3,     3,    38,     3,    67,     8,    67,
      67,    18,    29,   113,   113,    32,    18,   112,    16,     3,
       3,    32,    67,    67,    35,    39,    16,    67,     3,     3,
      67,   108,    67,    70,    67,    67,    70,   108,    67,    70,
     109,    67,    31,    33,   116,    67,    69,    67,    93,    96,
      36,    29,   113,   112,   113,   113,    18,    53,   114,    29,
     113,   113,   112,    18,    29,   110,   110,    17,     3,    16,
      99,    56,    58,    65,    66,    67,    69,    72,    73,   102,
     129,     3,    40,    30,    18,    92,    22,    23,    24,    25,
      26,    95,    67,    67,    70,    67,    54,   116,    67,    70,
      67,    70,    67,    70,   102,    18,   100,    16,   130,    56,
      29,    40,    41,    42,    43,    44,    45,    46,    55,    57,
      58,   132,    58,   132,    34,   128,   102,     6,    93,    17,
      16,    47,    58,    97,    16,   113,   113,   114,    67,    63,
     117,   113,   113,    29,   110,   110,   110,   110,    18,   101,
      99,     3,   131,   130,    67,    58,    16,   130,    55,    57,
      67,   102,    67,   102,   129,   116,    67,    92,     3,    65,
      94,    73,    67,    36,   115,    61,    60,   124,    67,    70,
     102,    17,   100,   106,   132,   102,    16,   130,    29,   128,
       3,     3,    17,    18,    89,   129,   114,    67,   118,   120,
      61,   110,   110,   101,    17,    67,   102,   130,   101,   102,
      67,    47,    97,    67,    17,   128,    29,    64,   121,    18,
     119,    67,   125,    29,    17,   101,    89,     3,    67,    48,
      49,    50,    51,    52,   123,   120,    10,    29,    62,   127,
      67,    17,    16,    16,    16,    16,    16,    18,   122,   119,
      18,   126,    67,   126,    67,    70,    67,    70,    67,    70,
      67,    70,    67,    70,   123,    67,    10,   127,    17,    29,
      17,    17,    29,    17,    17,    29,    17,    17,    29,    17,
      17,    29,    17,   122,    10,    29,   127,   126,   126,   132,
      67,    70,   132,   132,    67,    70,   132,   132,    67,    70,
     132,   132,    67,    70,   132,   132,    67,    70,   132,   126,
      67,   126,   102,    17,    17,   102,   102,    17,    17,   102,
     102,    17,    17,   102,   102,    17,    17,   102,   102,    17,
      17,   102,    10,   127,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   126,   126,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    74,    75,    75,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    88,    89,    89,    90,    91,    92,
      92,    93,    93,    93,    93,    94,    95,    95,    95,    95,
      95,    96,    97,    97,    98,    99,   100,   100,   101,   101,
     102,   102,   102,   102,   102,   103,   104,   105,   106,   107,
     107,   107,   107,   107,   108,   109,   109,   109,   109,   109,
     110,   110,   110,   110,   110,   111,   111,   111,   111,   111,
     112,   112,   112,   112,   112,   112,   113,   113,   113,   113,
     113,   114,   114,   114,   115,   115,   116,   116,   117,   117,
     118,   119,   119,   120,   120,   121,   121,   122,   122,   123,
     123,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     124,   124,   125,   125,   125,   125,   126,   126,   126,   126,
     126,   127,   127,   128,   128,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   130,
     131,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   133
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
       1,     1,     1,     1,     1,     5,     8,     2,     8,     2,
       2,     4,     4,     2,     4,     0,     2,     2,     4,     4,
       0,     3,     3,     5,     5,     1,     1,     1,     1,     1,
       0,     3,     3,     3,     5,     5,     0,     3,     5,     5,
       3,     0,     3,     5,     0,     3,     0,     3,     0,     4,
       2,     0,     3,     1,     3,     0,     3,     0,     3,     0,
       6,     6,     8,     8,     6,     6,     8,     8,     6,     6,
       8,     8,     6,     6,     8,     8,     6,     6,     8,     8,
       0,     3,     3,     5,     3,     5,     0,     4,     4,     6,
       6,     0,     1,     0,     3,     3,     3,     3,     3,     5,
       5,     7,     3,     4,     6,     7,     5,     2,     3,     4,
       0,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       2,     8
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
#line 204 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1555 "yacc_sql.tab.c"
    break;

  case 23: /* help: HELP SEMICOLON  */
#line 209 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1563 "yacc_sql.tab.c"
    break;

  case 24: /* sync: SYNC SEMICOLON  */
#line 214 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1571 "yacc_sql.tab.c"
    break;

  case 25: /* begin: TRX_BEGIN SEMICOLON  */
#line 220 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1579 "yacc_sql.tab.c"
    break;

  case 26: /* commit: TRX_COMMIT SEMICOLON  */
#line 226 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1587 "yacc_sql.tab.c"
    break;

  case 27: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 232 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1595 "yacc_sql.tab.c"
    break;

  case 28: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 238 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1604 "yacc_sql.tab.c"
    break;

  case 29: /* show_tables: SHOW TABLES SEMICOLON  */
#line 244 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1612 "yacc_sql.tab.c"
    break;

  case 30: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 250 "yacc_sql.y"
                                     {
		CONTEXT->ssql->flag = SCF_SHOW_INDEX;
		show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
	}
#line 1621 "yacc_sql.tab.c"
    break;

  case 31: /* desc_table: DESC ID SEMICOLON  */
#line 257 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1630 "yacc_sql.tab.c"
    break;

  case 32: /* create_index: CREATE unique_option INDEX ID ON ID LBRACE ID index_attr_list RBRACE SEMICOLON  */
#line 265 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), (yyvsp[-3].string), CONTEXT->unique);
		}
#line 1639 "yacc_sql.tab.c"
    break;

  case 34: /* unique_option: UNIQUE  */
#line 272 "yacc_sql.y"
                 {
		CONTEXT->unique = 1;
	}
#line 1647 "yacc_sql.tab.c"
    break;

  case 36: /* index_attr_list: COMMA ID index_attr_list  */
#line 286 "yacc_sql.y"
                                   {
		create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[-1].string));
	}
#line 1655 "yacc_sql.tab.c"
    break;

  case 37: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 292 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1664 "yacc_sql.tab.c"
    break;

  case 38: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 299 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1676 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 309 "yacc_sql.y"
                                   {    }
#line 1682 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def: ID_get type LBRACE number RBRACE NONULL  */
#line 314 "yacc_sql.y"
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
#line 1697 "yacc_sql.tab.c"
    break;

  case 42: /* attr_def: ID_get type LBRACE number RBRACE NULLABLE  */
#line 325 "yacc_sql.y"
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
#line 1712 "yacc_sql.tab.c"
    break;

  case 43: /* attr_def: ID_get type NONULL  */
#line 336 "yacc_sql.y"
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
#line 1727 "yacc_sql.tab.c"
    break;

  case 44: /* attr_def: ID_get type NULLABLE  */
#line 347 "yacc_sql.y"
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
#line 1742 "yacc_sql.tab.c"
    break;

  case 45: /* number: NUMBER  */
#line 359 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1748 "yacc_sql.tab.c"
    break;

  case 46: /* type: INT_T  */
#line 362 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1754 "yacc_sql.tab.c"
    break;

  case 47: /* type: STRING_T  */
#line 363 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1760 "yacc_sql.tab.c"
    break;

  case 48: /* type: TEXT_T  */
#line 364 "yacc_sql.y"
                    {(yyval.number)=TEXTS; }
#line 1766 "yacc_sql.tab.c"
    break;

  case 49: /* type: FLOAT_T  */
#line 365 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1772 "yacc_sql.tab.c"
    break;

  case 50: /* type: DATE_T  */
#line 366 "yacc_sql.y"
                    {(yyval.number)=DATES;}
#line 1778 "yacc_sql.tab.c"
    break;

  case 51: /* ID_get: ID  */
#line 370 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1787 "yacc_sql.tab.c"
    break;

  case 54: /* insert: INSERT INTO ID VALUES tuple tuple_list SEMICOLON  */
#line 384 "yacc_sql.y"
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
#line 1807 "yacc_sql.tab.c"
    break;

  case 55: /* tuple: LBRACE value value_list RBRACE  */
#line 401 "yacc_sql.y"
                                       {
		CONTEXT->tuple_num++;
		printf("yacc: tuple num %d\n", CONTEXT->tuple_num);
	}
#line 1816 "yacc_sql.tab.c"
    break;

  case 57: /* tuple_list: COMMA tuple tuple_list  */
#line 408 "yacc_sql.y"
                                 {
	}
#line 1823 "yacc_sql.tab.c"
    break;

  case 59: /* value_list: COMMA value value_list  */
#line 413 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1831 "yacc_sql.tab.c"
    break;

  case 60: /* value: NUMBER  */
#line 418 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
  		value_init_integer(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], (yyvsp[0].number));
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
#line 1841 "yacc_sql.tab.c"
    break;

  case 61: /* value: FLOAT  */
#line 423 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		value_init_float(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], (yyvsp[0].floats));
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
#line 1851 "yacc_sql.tab.c"
    break;

  case 62: /* value: SSS  */
#line 428 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		value_init_string(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], (yyvsp[0].string));
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
#line 1862 "yacc_sql.tab.c"
    break;

  case 63: /* value: DATE_STR  */
#line 434 "yacc_sql.y"
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
#line 1883 "yacc_sql.tab.c"
    break;

  case 64: /* value: NULLVALUE  */
#line 450 "yacc_sql.y"
                   {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
		value_init_null(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++]);
	}
#line 1892 "yacc_sql.tab.c"
    break;

  case 65: /* delete: DELETE FROM ID where SEMICOLON  */
#line 458 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1904 "yacc_sql.tab.c"
    break;

  case 66: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 468 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1916 "yacc_sql.tab.c"
    break;

  case 68: /* select_query: SELECT select_attr FROM ID rel_list where group order  */
#line 482 "yacc_sql.y"
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
#line 1937 "yacc_sql.tab.c"
    break;

  case 69: /* select_attr: STAR attr_list  */
#line 501 "yacc_sql.y"
                   {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1947 "yacc_sql.tab.c"
    break;

  case 70: /* select_attr: ID attr_list  */
#line 506 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1957 "yacc_sql.tab.c"
    break;

  case 71: /* select_attr: ID DOT ID attr_list  */
#line 511 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1967 "yacc_sql.tab.c"
    break;

  case 72: /* select_attr: ID DOT STAR attr_list  */
#line 516 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			// CONTEXT->aggregation_op = NO_AGGREGATE_OP;
			// selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_op);
			// selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, AggregationOp::NO_AGGREGATE_OP);
		}
#line 1980 "yacc_sql.tab.c"
    break;

  case 73: /* select_attr: aggregate_attr aggregate_attr_list  */
#line 524 "yacc_sql.y"
                                             {
			
	}
#line 1988 "yacc_sql.tab.c"
    break;

  case 74: /* aggregate_attr: aggregate_op LBRACE aggregation_field_attr RBRACE  */
#line 539 "yacc_sql.y"
                                                          {
		// RelAttr attr;
		// relation_attr_init(&attr, NULL, $3);
		// printf("aggregation: get a attr %s\n", $3);
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		// selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		// CONTEXT->aggregation_num++;	
	}
#line 2001 "yacc_sql.tab.c"
    break;

  case 76: /* aggregation_field_attr: STAR aggrattr_list  */
#line 550 "yacc_sql.y"
                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		printf("aggregation: get a attr *\n");
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
#line 2015 "yacc_sql.tab.c"
    break;

  case 77: /* aggregation_field_attr: ID aggrattr_list  */
#line 559 "yacc_sql.y"
                           {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		printf("aggregation: get a attr %s\n", (yyvsp[-1].string));
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
#line 2029 "yacc_sql.tab.c"
    break;

  case 78: /* aggregation_field_attr: ID DOT ID aggrattr_list  */
#line 568 "yacc_sql.y"
                                  {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		printf("aggregation: get a attr %s\n", (yyvsp[-3].string));
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
#line 2043 "yacc_sql.tab.c"
    break;

  case 79: /* aggregation_field_attr: ID DOT STAR aggrattr_list  */
#line 577 "yacc_sql.y"
                                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), "*");
		printf("aggregation: get a attr %s\n", (yyvsp[-3].string));
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
#line 2057 "yacc_sql.tab.c"
    break;

  case 81: /* aggrattr_list: COMMA STAR aggrattr_list  */
#line 589 "yacc_sql.y"
                                   {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		printf("aggregation: get a attr *\n");
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2069 "yacc_sql.tab.c"
    break;

  case 82: /* aggrattr_list: COMMA ID aggrattr_list  */
#line 596 "yacc_sql.y"
                                 {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		printf("aggregation: get a attr %s\n", (yyvsp[-1].string));
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2081 "yacc_sql.tab.c"
    break;

  case 83: /* aggrattr_list: COMMA ID DOT ID aggrattr_list  */
#line 603 "yacc_sql.y"
                                        {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		printf("aggregation: get a attr %s\n", (yyvsp[-3].string));
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2093 "yacc_sql.tab.c"
    break;

  case 84: /* aggrattr_list: COMMA ID DOT STAR aggrattr_list  */
#line 610 "yacc_sql.y"
                                          {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), "*");
		printf("aggregation: get a attr %s\n", (yyvsp[-3].string));
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2105 "yacc_sql.tab.c"
    break;

  case 85: /* aggregate_op: COUNT  */
#line 620 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = COUNT_OP; }
#line 2111 "yacc_sql.tab.c"
    break;

  case 86: /* aggregate_op: AVG  */
#line 621 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = AVG_OP; }
#line 2117 "yacc_sql.tab.c"
    break;

  case 87: /* aggregate_op: MAX  */
#line 622 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = MAX_OP; }
#line 2123 "yacc_sql.tab.c"
    break;

  case 88: /* aggregate_op: MIN  */
#line 623 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = MIN_OP; }
#line 2129 "yacc_sql.tab.c"
    break;

  case 89: /* aggregate_op: SUM  */
#line 624 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = SUM_OP; }
#line 2135 "yacc_sql.tab.c"
    break;

  case 91: /* aggregate_attr_list: COMMA aggregate_attr aggregate_attr_list  */
#line 629 "yacc_sql.y"
                                                  {

	}
#line 2143 "yacc_sql.tab.c"
    break;

  case 92: /* aggregate_attr_list: COMMA STAR attr_list  */
#line 632 "yacc_sql.y"
                               {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2153 "yacc_sql.tab.c"
    break;

  case 93: /* aggregate_attr_list: COMMA ID attr_list  */
#line 637 "yacc_sql.y"
                            {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2163 "yacc_sql.tab.c"
    break;

  case 94: /* aggregate_attr_list: COMMA ID DOT ID attr_list  */
#line 642 "yacc_sql.y"
                                    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2173 "yacc_sql.tab.c"
    break;

  case 95: /* aggregate_attr_list: COMMA ID DOT STAR attr_list  */
#line 647 "yacc_sql.y"
                                      {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2183 "yacc_sql.tab.c"
    break;

  case 97: /* attr_list: COMMA ID attr_list  */
#line 656 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 2195 "yacc_sql.tab.c"
    break;

  case 98: /* attr_list: COMMA ID DOT ID attr_list  */
#line 663 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 2207 "yacc_sql.tab.c"
    break;

  case 99: /* attr_list: COMMA ID DOT STAR attr_list  */
#line 670 "yacc_sql.y"
                                      {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2217 "yacc_sql.tab.c"
    break;

  case 100: /* attr_list: COMMA aggregate_attr aggregate_attr_list  */
#line 675 "yacc_sql.y"
                                                   {

	}
#line 2225 "yacc_sql.tab.c"
    break;

  case 102: /* rel_list: COMMA ID rel_list  */
#line 682 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 2233 "yacc_sql.tab.c"
    break;

  case 103: /* rel_list: INNER JOIN ID on_list rel_list  */
#line 685 "yacc_sql.y"
                                         {
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string));
	}
#line 2241 "yacc_sql.tab.c"
    break;

  case 105: /* on_list: ON condition condition_list  */
#line 692 "yacc_sql.y"
                                      {

	}
#line 2249 "yacc_sql.tab.c"
    break;

  case 107: /* where: WHERE condition condition_list  */
#line 698 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2257 "yacc_sql.tab.c"
    break;

  case 108: /* group: %empty  */
#line 704 "yacc_sql.y"
        {
		selects_set_group(&CONTEXT->ssql->sstr.selection, 0);
	}
#line 2265 "yacc_sql.tab.c"
    break;

  case 109: /* group: GROUP BY group_attrs having  */
#line 707 "yacc_sql.y"
                                      {
		selects_set_group(&CONTEXT->ssql->sstr.selection, 1);
	}
#line 2273 "yacc_sql.tab.c"
    break;

  case 110: /* group_attrs: group_attr group_attr_list  */
#line 713 "yacc_sql.y"
                                   {
		// 递归。最新秒杀升级版。
	}
#line 2281 "yacc_sql.tab.c"
    break;

  case 112: /* group_attr_list: COMMA group_attr group_attr_list  */
#line 719 "yacc_sql.y"
                                           {
		// 递归。最新秒杀升级版。
	}
#line 2289 "yacc_sql.tab.c"
    break;

  case 113: /* group_attr: ID  */
#line 726 "yacc_sql.y"
           {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[0].string));
		selects_append_groupattr(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2299 "yacc_sql.tab.c"
    break;

  case 114: /* group_attr: ID DOT ID  */
#line 731 "yacc_sql.y"
                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
		selects_append_groupattr(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2309 "yacc_sql.tab.c"
    break;

  case 115: /* having: %empty  */
#line 739 "yacc_sql.y"
        {
		selects_set_having(&CONTEXT->ssql->sstr.selection, 0);
	}
#line 2317 "yacc_sql.tab.c"
    break;

  case 116: /* having: HAVING having_condition having_condition_list  */
#line 742 "yacc_sql.y"
                                                        {
		// 递归
		selects_set_having(&CONTEXT->ssql->sstr.selection, 1);
	}
#line 2326 "yacc_sql.tab.c"
    break;

  case 118: /* having_condition_list: COMMA having_condition having_condition_list  */
#line 749 "yacc_sql.y"
                                                      {
		// 递归
	}
#line 2334 "yacc_sql.tab.c"
    break;

  case 120: /* having_condition: COUNT LBRACE ID RBRACE comOp value  */
#line 759 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, COUNT_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2346 "yacc_sql.tab.c"
    break;

  case 121: /* having_condition: COUNT LBRACE STAR RBRACE comOp value  */
#line 766 "yacc_sql.y"
                                               {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		Having_Condition condition;
		having_condition_init(&condition, COUNT_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2358 "yacc_sql.tab.c"
    break;

  case 122: /* having_condition: COUNT LBRACE ID DOT ID RBRACE comOp value  */
#line 773 "yacc_sql.y"
                                                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, COUNT_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2370 "yacc_sql.tab.c"
    break;

  case 123: /* having_condition: COUNT LBRACE ID DOT STAR RBRACE comOp value  */
#line 780 "yacc_sql.y"
                                                      {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), "*");
		Having_Condition condition;
		having_condition_init(&condition, COUNT_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2382 "yacc_sql.tab.c"
    break;

  case 124: /* having_condition: AVG LBRACE ID RBRACE comOp value  */
#line 787 "yacc_sql.y"
                                           {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, AVG_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2394 "yacc_sql.tab.c"
    break;

  case 125: /* having_condition: AVG LBRACE STAR RBRACE comOp value  */
#line 794 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		Having_Condition condition;
		having_condition_init(&condition, AVG_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2406 "yacc_sql.tab.c"
    break;

  case 126: /* having_condition: AVG LBRACE ID DOT ID RBRACE comOp value  */
#line 801 "yacc_sql.y"
                                                  {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, AVG_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2418 "yacc_sql.tab.c"
    break;

  case 127: /* having_condition: AVG LBRACE ID DOT STAR RBRACE comOp value  */
#line 808 "yacc_sql.y"
                                                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), "*");
		Having_Condition condition;
		having_condition_init(&condition, AVG_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2430 "yacc_sql.tab.c"
    break;

  case 128: /* having_condition: MAX LBRACE ID RBRACE comOp value  */
#line 815 "yacc_sql.y"
                                           {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, MAX_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2442 "yacc_sql.tab.c"
    break;

  case 129: /* having_condition: MAX LBRACE STAR RBRACE comOp value  */
#line 822 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		Having_Condition condition;
		having_condition_init(&condition, MAX_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2454 "yacc_sql.tab.c"
    break;

  case 130: /* having_condition: MAX LBRACE ID DOT ID RBRACE comOp value  */
#line 829 "yacc_sql.y"
                                                  {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, MAX_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2466 "yacc_sql.tab.c"
    break;

  case 131: /* having_condition: MAX LBRACE ID DOT STAR RBRACE comOp value  */
#line 836 "yacc_sql.y"
                                                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), "*");
		Having_Condition condition;
		having_condition_init(&condition, MAX_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2478 "yacc_sql.tab.c"
    break;

  case 132: /* having_condition: MIN LBRACE ID RBRACE comOp value  */
#line 843 "yacc_sql.y"
                                           {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, MIN_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2490 "yacc_sql.tab.c"
    break;

  case 133: /* having_condition: MIN LBRACE STAR RBRACE comOp value  */
#line 850 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		Having_Condition condition;
		having_condition_init(&condition, MIN_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2502 "yacc_sql.tab.c"
    break;

  case 134: /* having_condition: MIN LBRACE ID DOT ID RBRACE comOp value  */
#line 857 "yacc_sql.y"
                                                  {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, MIN_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2514 "yacc_sql.tab.c"
    break;

  case 135: /* having_condition: MIN LBRACE ID DOT STAR RBRACE comOp value  */
#line 864 "yacc_sql.y"
                                                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), "*");
		Having_Condition condition;
		having_condition_init(&condition, MIN_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2526 "yacc_sql.tab.c"
    break;

  case 136: /* having_condition: SUM LBRACE ID RBRACE comOp value  */
#line 871 "yacc_sql.y"
                                           {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, SUM_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2538 "yacc_sql.tab.c"
    break;

  case 137: /* having_condition: SUM LBRACE STAR RBRACE comOp value  */
#line 878 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "$3");
		Having_Condition condition;
		having_condition_init(&condition, SUM_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2550 "yacc_sql.tab.c"
    break;

  case 138: /* having_condition: SUM LBRACE ID DOT ID RBRACE comOp value  */
#line 885 "yacc_sql.y"
                                                  {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, SUM_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2562 "yacc_sql.tab.c"
    break;

  case 139: /* having_condition: SUM LBRACE ID DOT STAR RBRACE comOp value  */
#line 892 "yacc_sql.y"
                                                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), "*");
		Having_Condition condition;
		having_condition_init(&condition, SUM_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 2574 "yacc_sql.tab.c"
    break;

  case 140: /* order: %empty  */
#line 902 "yacc_sql.y"
        {
		selects_set_order(&CONTEXT->ssql->sstr.selection, 0);
	}
#line 2582 "yacc_sql.tab.c"
    break;

  case 141: /* order: ORDER BY order_attr  */
#line 905 "yacc_sql.y"
                              {
		selects_set_order(&CONTEXT->ssql->sstr.selection, 1);
	}
#line 2590 "yacc_sql.tab.c"
    break;

  case 142: /* order_attr: ID asc order_attr_list  */
#line 911 "yacc_sql.y"
                               {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
		}
#line 2600 "yacc_sql.tab.c"
    break;

  case 143: /* order_attr: ID DOT ID asc order_attr_list  */
#line 916 "yacc_sql.y"
                                        {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
		}
#line 2610 "yacc_sql.tab.c"
    break;

  case 144: /* order_attr: ID DESC order_attr_list  */
#line 921 "yacc_sql.y"
                                  {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
		}
#line 2620 "yacc_sql.tab.c"
    break;

  case 145: /* order_attr: ID DOT ID DESC order_attr_list  */
#line 926 "yacc_sql.y"
                                         {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
		}
#line 2630 "yacc_sql.tab.c"
    break;

  case 147: /* order_attr_list: COMMA ID asc order_attr_list  */
#line 935 "yacc_sql.y"
                                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
      }
#line 2640 "yacc_sql.tab.c"
    break;

  case 148: /* order_attr_list: COMMA ID DESC order_attr_list  */
#line 940 "yacc_sql.y"
                                    {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
      }
#line 2650 "yacc_sql.tab.c"
    break;

  case 149: /* order_attr_list: COMMA ID DOT ID asc order_attr_list  */
#line 945 "yacc_sql.y"
                                          {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
  	  }
#line 2660 "yacc_sql.tab.c"
    break;

  case 150: /* order_attr_list: COMMA ID DOT ID DESC order_attr_list  */
#line 950 "yacc_sql.y"
                                           {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
  	  }
#line 2670 "yacc_sql.tab.c"
    break;

  case 154: /* condition_list: AND condition condition_list  */
#line 963 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2678 "yacc_sql.tab.c"
    break;

  case 155: /* condition: ID comOp value  */
#line 969 "yacc_sql.y"
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
#line 2704 "yacc_sql.tab.c"
    break;

  case 156: /* condition: value comOp value  */
#line 991 "yacc_sql.y"
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
#line 2729 "yacc_sql.tab.c"
    break;

  case 157: /* condition: ID comOp ID  */
#line 1012 "yacc_sql.y"
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
#line 2754 "yacc_sql.tab.c"
    break;

  case 158: /* condition: value comOp ID  */
#line 1033 "yacc_sql.y"
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
#line 2781 "yacc_sql.tab.c"
    break;

  case 159: /* condition: ID DOT ID comOp value  */
#line 1056 "yacc_sql.y"
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
#line 2807 "yacc_sql.tab.c"
    break;

  case 160: /* condition: value comOp ID DOT ID  */
#line 1078 "yacc_sql.y"
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
#line 2833 "yacc_sql.tab.c"
    break;

  case 161: /* condition: ID DOT ID comOp ID DOT ID  */
#line 1100 "yacc_sql.y"
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
#line 2857 "yacc_sql.tab.c"
    break;

  case 162: /* condition: ID IN sub_query  */
#line 1119 "yacc_sql.y"
                          {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

		Condition condition;
		condition_init(&condition, Contain, CONTEXT->comp, 1, &left_attr, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		
	}
#line 2871 "yacc_sql.tab.c"
    break;

  case 163: /* condition: ID NOT IN sub_query  */
#line 1128 "yacc_sql.y"
                              {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-3].string));

		Condition condition;
		condition_init(&condition, NotContain, CONTEXT->comp, 1, &left_attr, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 2885 "yacc_sql.tab.c"
    break;

  case 164: /* condition: ID IN LBRACE value value_list RBRACE  */
#line 1137 "yacc_sql.y"
                                               {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-5].string));

		Condition condition;
		condition_init(&condition, Contain, CONTEXT->comp, 1, &left_attr, NULL, 0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, 
			CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length = 0;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 2901 "yacc_sql.tab.c"
    break;

  case 165: /* condition: ID NOT IN LBRACE value value_list RBRACE  */
#line 1148 "yacc_sql.y"
                                                   {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-6].string));

		Condition condition;
		condition_init(&condition, NotContain, CONTEXT->comp, 1, &left_attr, NULL, 0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, 
			CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length = 0;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 2917 "yacc_sql.tab.c"
    break;

  case 166: /* condition: ID DOT ID comOp sub_query  */
#line 1159 "yacc_sql.y"
                                    {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));

		Condition condition;
		condition_init(&condition, Comparison, CONTEXT->comp, 1, &left_attr, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2930 "yacc_sql.tab.c"
    break;

  case 167: /* condition: EXISTS sub_query  */
#line 1167 "yacc_sql.y"
                           {

		Condition condition;
		condition_init(&condition, Exists, CONTEXT->comp, 0, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 2942 "yacc_sql.tab.c"
    break;

  case 168: /* condition: NOT EXISTS sub_query  */
#line 1174 "yacc_sql.y"
                               {

		Condition condition;
		condition_init(&condition, NotExists, CONTEXT->comp, 0, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 2954 "yacc_sql.tab.c"
    break;

  case 169: /* sub_query: LBRACE N select_query RBRACE  */
#line 1184 "yacc_sql.y"
                                     {
		// TODO support complex sub query
		ParserContext *old_context = CONTEXT->last_context;
		old_context->sub_query = CONTEXT->ssql;
		*CONTEXT = *old_context;
		printf("sub query addr %p\n", old_context->sub_query);
		printf("swap back old context\n");
	}
#line 2967 "yacc_sql.tab.c"
    break;

  case 170: /* N: %empty  */
#line 1192 "yacc_sql.y"
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
#line 2987 "yacc_sql.tab.c"
    break;

  case 171: /* comOp: EQ  */
#line 1210 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2993 "yacc_sql.tab.c"
    break;

  case 172: /* comOp: LT  */
#line 1211 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2999 "yacc_sql.tab.c"
    break;

  case 173: /* comOp: GT  */
#line 1212 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 3005 "yacc_sql.tab.c"
    break;

  case 174: /* comOp: LE  */
#line 1213 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 3011 "yacc_sql.tab.c"
    break;

  case 175: /* comOp: GE  */
#line 1214 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 3017 "yacc_sql.tab.c"
    break;

  case 176: /* comOp: NE  */
#line 1215 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 3023 "yacc_sql.tab.c"
    break;

  case 177: /* comOp: IS  */
#line 1216 "yacc_sql.y"
             { CONTEXT->comp = LOGICAL_IS; }
#line 3029 "yacc_sql.tab.c"
    break;

  case 178: /* comOp: IS NOT  */
#line 1217 "yacc_sql.y"
                 {CONTEXT->comp = LOGICAL_IS_NOT; }
#line 3035 "yacc_sql.tab.c"
    break;

  case 179: /* comOp: LIKE  */
#line 1218 "yacc_sql.y"
               { CONTEXT->comp = LIKE_OP; }
#line 3041 "yacc_sql.tab.c"
    break;

  case 180: /* comOp: NOT LIKE  */
#line 1219 "yacc_sql.y"
                   { CONTEXT->comp = NOT_LIKE_OP; }
#line 3047 "yacc_sql.tab.c"
    break;

  case 181: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 1224 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 3056 "yacc_sql.tab.c"
    break;


#line 3060 "yacc_sql.tab.c"

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

#line 1229 "yacc_sql.y"

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
