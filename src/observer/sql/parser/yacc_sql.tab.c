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


#line 153 "yacc_sql.tab.c"

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
  YYSYMBOL_OR = 63,                        /* OR  */
  YYSYMBOL_AS = 64,                        /* AS  */
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
  YYSYMBOL_assign = 105,                   /* assign  */
  YYSYMBOL_assign_list = 106,              /* assign_list  */
  YYSYMBOL_select = 107,                   /* select  */
  YYSYMBOL_select_query = 108,             /* select_query  */
  YYSYMBOL_select_attr = 109,              /* select_attr  */
  YYSYMBOL_as_option = 110,                /* as_option  */
  YYSYMBOL_aggregate_attr = 111,           /* aggregate_attr  */
  YYSYMBOL_aggregation_field_attr = 112,   /* aggregation_field_attr  */
  YYSYMBOL_aggregate_op = 113,             /* aggregate_op  */
  YYSYMBOL_aggregate_attr_list = 114,      /* aggregate_attr_list  */
  YYSYMBOL_attr_list = 115,                /* attr_list  */
  YYSYMBOL_rel_list = 116,                 /* rel_list  */
  YYSYMBOL_on_list = 117,                  /* on_list  */
  YYSYMBOL_where = 118,                    /* where  */
  YYSYMBOL_order = 119,                    /* order  */
  YYSYMBOL_order_attr = 120,               /* order_attr  */
  YYSYMBOL_order_attr_list = 121,          /* order_attr_list  */
  YYSYMBOL_asc = 122,                      /* asc  */
  YYSYMBOL_condition_list = 123,           /* condition_list  */
  YYSYMBOL_condition = 124,                /* condition  */
  YYSYMBOL_sub_query = 125,                /* sub_query  */
  YYSYMBOL_N = 126,                        /* N  */
  YYSYMBOL_comOp = 127,                    /* comOp  */
  YYSYMBOL_load_data = 128                 /* load_data  */
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
#define YYLAST   383

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  169
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  352

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
       0,   187,   187,   189,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   214,   219,   224,   230,   236,   242,   248,   254,
     260,   267,   274,   280,   282,   294,   296,   301,   308,   317,
     319,   323,   334,   345,   356,   369,   372,   373,   374,   375,
     376,   379,   386,   387,   393,   411,   416,   418,   421,   423,
     428,   433,   438,   444,   460,   467,   478,   491,   495,   504,
     506,   510,   513,   530,   550,   555,   560,   566,   571,   577,
     585,   592,   601,   603,   615,   624,   626,   634,   642,   652,
     653,   654,   655,   656,   659,   661,   668,   676,   681,   686,
     691,   698,   700,   707,   715,   722,   730,   736,   741,   743,
     746,   749,   752,   757,   759,   763,   765,   771,   774,   780,
     785,   790,   795,   802,   804,   809,   814,   819,   826,   827,
     830,   832,   841,   852,   874,   895,   916,   937,   958,   981,
    1003,  1025,  1045,  1054,  1063,  1072,  1081,  1092,  1103,  1114,
    1125,  1133,  1141,  1165,  1188,  1194,  1201,  1211,  1224,  1242,
    1243,  1244,  1245,  1246,  1247,  1248,  1249,  1250,  1251,  1255
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
  "ASC", "OR", "AS", "NUMBER", "FLOAT", "ID", "PATH", "SSS", "STAR",
  "STRING_V", "DATE_STR", "NULLVALUE", "$accept", "commands", "command",
  "exit", "help", "sync", "begin", "commit", "rollback", "drop_table",
  "show_tables", "show_index", "desc_table", "create_index",
  "unique_option", "index_attr_list", "drop_index", "create_table",
  "attr_def_list", "attr_def", "number", "type", "ID_get", "NONULL",
  "insert", "tuple", "tuple_list", "value_list", "value", "delete",
  "update", "assign", "assign_list", "select", "select_query",
  "select_attr", "as_option", "aggregate_attr", "aggregation_field_attr",
  "aggregate_op", "aggregate_attr_list", "attr_list", "rel_list",
  "on_list", "where", "order", "order_attr", "order_attr_list", "asc",
  "condition_list", "condition", "sub_query", "N", "comOp", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-255)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-102)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -255,   171,  -255,     7,    31,   153,   -56,   142,    17,   -11,
      35,   -34,    81,   113,   125,   135,   151,    61,  -255,  -255,
    -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,
    -255,  -255,  -255,  -255,  -255,  -255,   161,  -255,    66,  -255,
     160,   102,   107,  -255,  -255,  -255,  -255,  -255,   124,   177,
     146,   108,   173,   193,   204,   178,  -255,   144,   148,   181,
    -255,  -255,  -255,  -255,  -255,   182,  -255,   209,   175,   242,
     250,   200,    27,  -255,   187,  -255,  -255,   190,   188,   199,
    -255,    88,  -255,  -255,   206,   197,   223,   208,   230,   221,
     264,  -255,  -255,    12,   177,   129,   177,   177,    51,     0,
     283,   108,   283,    96,   177,   285,   300,   288,    16,   302,
     266,   289,   278,  -255,   291,   246,   243,   130,   244,  -255,
    -255,   245,  -255,  -255,  -255,   247,   259,   248,   223,   139,
    -255,  -255,   249,  -255,  -255,   251,  -255,  -255,  -255,  -255,
     225,   299,  -255,   303,   265,  -255,  -255,   189,  -255,  -255,
    -255,   238,   -27,   238,  -255,    94,   208,   223,   314,   221,
     305,  -255,  -255,  -255,  -255,  -255,   115,   307,    60,   177,
     177,   177,    51,   257,    20,   267,   283,   283,   283,   177,
     308,   288,   322,   319,  -255,   303,   262,  -255,  -255,  -255,
    -255,  -255,  -255,   272,   315,  -255,   167,    40,   275,   220,
      16,    16,  -255,     1,  -255,  -255,   289,   330,   268,   291,
     331,   271,  -255,   269,  -255,   270,   273,  -255,  -255,  -255,
    -255,   274,  -255,   -24,   223,   277,  -255,  -255,  -255,  -255,
    -255,   225,   326,   299,  -255,   327,  -255,   219,  -255,   225,
    -255,   323,  -255,   316,  -255,  -255,   317,  -255,   -27,   -27,
     318,  -255,  -255,  -255,   345,  -255,  -255,  -255,   332,  -255,
     333,   177,    20,    16,   286,    20,   267,   287,   308,  -255,
    -255,  -255,   334,   186,    79,   308,   225,  -255,   290,   292,
    -255,  -255,   293,  -255,    76,   294,   335,  -255,  -255,   -27,
     320,  -255,  -255,    13,  -255,  -255,   225,  -255,   339,   329,
    -255,  -255,   346,   308,  -255,  -255,  -255,  -255,  -255,   333,
     359,  -255,    20,   347,   297,  -255,   347,   308,   225,  -255,
     301,  -255,   349,  -255,  -255,  -255,   304,  -255,    18,  -255,
     350,   308,  -255,  -255,    24,   347,   347,  -255,   352,   347,
     306,   347,  -255,  -255,  -255,  -255,    25,  -255,   347,   347,
    -255,  -255
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
       0,     0,     0,    89,    90,    91,    92,    93,    82,   101,
       0,    82,     0,     0,     0,     0,    24,     0,     0,     0,
      25,    26,    27,    23,    22,     0,    71,     0,     0,     0,
       0,     0,     0,    83,     0,    75,    74,     0,     0,     0,
      80,    85,    31,    29,     0,     0,   115,     0,     0,     0,
       0,    28,    37,   101,   101,    82,   101,   101,   108,    94,
      94,    82,    94,   101,   101,     0,     0,     0,     0,     0,
       0,    69,     0,    51,    39,     0,     0,     0,     0,   102,
     107,     0,    77,    79,    76,     0,     0,     0,   115,     0,
      98,    97,     0,    95,    81,     0,    87,    86,    84,    30,
       0,    56,   158,     0,     0,    60,    61,     0,    62,    63,
      64,     0,   130,     0,    65,     0,     0,   115,     0,     0,
       0,    46,    47,    48,    49,    50,    52,     0,   101,   101,
     101,   101,   108,     0,   108,   117,    94,    94,    94,   101,
      58,     0,     0,     0,   155,     0,     0,   159,   160,   161,
     162,   163,   164,   165,     0,   167,     0,     0,     0,     0,
       0,     0,   116,     0,    67,    68,    69,     0,     0,    39,
       0,     0,    44,     0,    43,     0,     0,   104,   106,   103,
      78,     0,   109,   113,   115,     0,    72,    99,   100,    96,
      88,     0,     0,    56,    54,     0,   156,     0,   166,   158,
     142,     0,   168,   135,   133,   151,   138,   134,   130,   130,
     153,   154,    70,    66,     0,    40,    38,    45,     0,    53,
      35,   101,   108,     0,     0,   108,   117,     0,    58,    55,
      57,   157,     0,     0,     0,    58,   158,   143,     0,     0,
     131,   132,     0,   169,    52,     0,     0,   105,   110,   130,
     113,   111,    73,   128,   118,    59,   158,   144,     0,   137,
     139,   150,     0,    58,   136,   140,   152,    42,    41,    35,
       0,   114,   108,   123,     0,   129,   123,    58,   158,   145,
       0,   146,     0,    36,    32,   112,     0,   121,   128,   119,
       0,    58,   141,   147,   128,   123,   123,   148,     0,   123,
       0,   123,   122,   120,   149,   125,   128,   124,   123,   123,
     127,   126
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,  -255,
    -255,  -255,  -255,  -255,  -255,    63,  -255,  -255,   165,   211,
    -255,  -255,  -255,    91,  -255,   195,   145,  -254,  -139,  -255,
    -255,   224,   176,  -255,   194,  -255,   -36,    99,  -255,  -255,
     -75,   -49,  -169,    89,  -126,   117,  -255,  -122,  -217,  -198,
    -192,  -133,  -255,  -147,  -255
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    40,   286,    30,    31,   160,   114,
     258,   166,   115,   214,    32,   141,   182,   232,   151,    33,
      34,   111,   157,    35,    36,    50,    74,    51,   105,    52,
      80,    75,   128,   265,   109,   226,   294,   327,   316,   202,
     152,   153,   183,   197,    37
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      76,   180,   175,   222,   199,   224,   203,   200,   248,   249,
     184,    53,   263,    38,   295,    79,   204,   142,    78,    57,
      56,   302,   205,   313,   130,   131,   133,   134,   335,   129,
      71,   207,   142,    59,   339,   348,   201,    41,   125,    42,
      73,   117,   314,   -82,   119,   120,   122,   123,   124,   322,
     280,   281,   236,   340,   136,   137,   142,   118,   244,   121,
     247,   240,   127,   330,   245,   132,    39,    58,   250,   125,
     251,   289,   143,   126,   144,   315,    73,   338,    71,   -82,
     315,   145,   146,   147,    60,   148,   315,   315,   149,   150,
     274,   311,   268,   288,    95,   142,   291,    96,   266,    65,
     275,   227,   228,   229,   126,   145,   146,   243,   277,   148,
     142,   336,   149,   150,    71,    73,    61,   341,   -82,   217,
     218,   219,   220,   307,    73,   135,    78,   -82,    62,   349,
     230,   211,   216,    67,   213,   300,   221,   303,    63,   297,
     -94,   301,    71,   325,   145,   146,   299,    71,   148,    54,
      55,   149,   150,    72,    64,   103,  -101,   317,   104,   145,
     146,  -101,   212,   148,    66,   319,   149,   150,    68,    69,
      94,     2,    73,   213,    70,     3,     4,   101,    77,   331,
       5,     6,     7,     8,     9,    10,    11,   264,    73,    81,
      12,    13,    14,    73,   329,    71,    82,   168,    15,    16,
     169,    43,    44,    45,    46,    47,   176,    83,    17,   177,
      84,    85,   287,   342,   343,    86,    87,   345,   186,   347,
      48,    88,   241,    49,   242,    89,   350,   351,   107,   187,
     188,   189,   190,   191,   192,   193,    43,    44,    45,    46,
      47,   298,    90,   242,   194,    91,   195,   196,    43,    44,
      45,    46,    47,    92,    97,    99,   108,    98,   100,   187,
     188,   189,   190,   191,   192,   193,   102,    93,   161,   162,
     163,   164,   165,   106,   272,   110,   195,   273,   187,   188,
     189,   190,   191,   192,   193,   145,   146,   246,   113,   148,
     145,   146,   149,   150,   148,   195,   198,   149,   150,   112,
     116,    78,   138,   139,   140,   154,   155,   156,   158,   159,
     167,   170,   171,   173,   172,   174,   178,   181,   179,   142,
     208,   185,   210,   215,   223,   234,   231,   225,     5,   237,
     238,   239,   242,   253,   256,   254,   257,   260,   267,   276,
     261,   262,   259,   269,   271,   278,   279,   282,   283,   284,
     296,   285,   310,   290,   293,   318,   263,   304,   320,   305,
     306,   309,   324,   321,   328,   326,   333,   337,   332,   344,
     209,   334,   323,   346,   255,   308,   233,   235,   270,   312,
     206,     0,   252,   292
};

static const yytype_int16 yycheck[] =
{
      49,   140,   128,   172,   151,   174,   153,    34,   200,   201,
     143,    67,    36,     6,   268,    51,   155,    16,    18,    30,
       3,   275,   155,    10,    99,   100,   101,   102,    10,    29,
      18,   157,    16,    67,    10,    10,    63,     6,    18,     8,
      64,    29,    29,    67,    93,    94,    95,    96,    97,   303,
     248,   249,   185,    29,   103,   104,    16,    93,   197,    95,
     199,   194,    98,   317,   197,   101,    59,    32,    67,    18,
     203,   263,    56,    53,    58,    62,    64,   331,    18,    67,
      62,    65,    66,    67,     3,    69,    62,    62,    72,    73,
     237,   289,   231,   262,    67,    16,   265,    70,   224,    38,
     239,   176,   177,   178,    53,    65,    66,    67,   241,    69,
      16,   328,    72,    73,    18,    64,     3,   334,    67,   168,
     169,   170,   171,    47,    64,    29,    18,    67,     3,   346,
     179,    16,   168,    67,    58,   274,   172,   276,     3,   272,
      32,   274,    18,   312,    65,    66,    67,    18,    69,     7,
       8,    72,    73,    29,     3,    67,    32,   296,    70,    65,
      66,    32,    47,    69,     3,   298,    72,    73,     8,    67,
      71,     0,    64,    58,    67,     4,     5,    78,    32,   318,
       9,    10,    11,    12,    13,    14,    15,   223,    64,    16,
      19,    20,    21,    64,   316,    18,     3,    67,    27,    28,
      70,    48,    49,    50,    51,    52,    67,     3,    37,    70,
      32,    67,   261,   335,   336,    67,    35,   339,    29,   341,
      67,    39,    55,    70,    57,    16,   348,   349,    31,    40,
      41,    42,    43,    44,    45,    46,    48,    49,    50,    51,
      52,    55,    67,    57,    55,     3,    57,    58,    48,    49,
      50,    51,    52,     3,    67,    67,    33,    67,    70,    40,
      41,    42,    43,    44,    45,    46,    67,    67,    22,    23,
      24,    25,    26,    67,    55,    67,    57,    58,    40,    41,
      42,    43,    44,    45,    46,    65,    66,    67,    67,    69,
      65,    66,    72,    73,    69,    57,    58,    72,    73,    69,
      36,    18,    17,     3,    16,     3,    40,    18,    30,    18,
      67,    67,    67,    54,    67,    67,    67,    18,    67,    16,
       6,    56,    17,    16,    67,     3,    18,    60,     9,    67,
      58,    16,    57,     3,     3,    67,    65,    67,    61,    16,
      67,    67,    73,    17,    17,    29,    29,    29,     3,    17,
      16,    18,    17,    67,    67,    16,    36,    67,    29,    67,
      67,    67,     3,    17,    67,    18,    17,    17,    67,    17,
     159,    67,   309,    67,   209,   284,   181,   183,   233,   290,
     156,    -1,   206,   266
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    75,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    19,    20,    21,    27,    28,    37,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      90,    91,    98,   103,   104,   107,   108,   128,     6,    59,
      88,     6,     8,    48,    49,    50,    51,    52,    67,    70,
     109,   111,   113,    67,     7,     8,     3,    30,    32,    67,
       3,     3,     3,     3,     3,    38,     3,    67,     8,    67,
      67,    18,    29,    64,   110,   115,   115,    32,    18,   110,
     114,    16,     3,     3,    32,    67,    67,    35,    39,    16,
      67,     3,     3,    67,   111,    67,    70,    67,    67,    67,
      70,   111,    67,    67,    70,   112,    67,    31,    33,   118,
      67,   105,    69,    67,    93,    96,    36,    29,   110,   115,
     115,   110,   115,   115,   115,    18,    53,   110,   116,    29,
     114,   114,   110,   114,   114,    29,   115,   115,    17,     3,
      16,    99,    16,    56,    58,    65,    66,    67,    69,    72,
      73,   102,   124,   125,     3,    40,    18,   106,    30,    18,
      92,    22,    23,    24,    25,    26,    95,    67,    67,    70,
      67,    67,    67,    54,    67,   118,    67,    70,    67,    67,
     102,    18,   100,   126,   125,    56,    29,    40,    41,    42,
      43,    44,    45,    46,    55,    57,    58,   127,    58,   127,
      34,    63,   123,   127,   102,   125,   105,   118,     6,    93,
      17,    16,    47,    58,    97,    16,   110,   115,   115,   115,
     115,   110,   116,    67,   116,    60,   119,   114,   114,   114,
     115,    18,   101,    99,     3,   108,   125,    67,    58,    16,
     125,    55,    57,    67,   102,   125,    67,   102,   124,   124,
      67,   125,   106,     3,    67,    92,     3,    65,    94,    73,
      67,    67,    67,    36,   110,   117,   118,    61,   102,    17,
     100,    17,    55,    58,   127,   102,    16,   125,    29,    29,
     123,   123,    29,     3,    17,    18,    89,   115,   116,   124,
      67,   116,   119,    67,   120,   101,    16,   125,    55,    67,
     102,   125,   101,   102,    67,    67,    67,    47,    97,    67,
      17,   123,   117,    10,    29,    62,   122,   102,    16,   125,
      29,    17,   101,    89,     3,   116,    18,   121,    67,   121,
     101,   102,    67,    17,    67,    10,   122,    17,   101,    10,
      29,   122,   121,   121,    17,   121,    67,   121,    10,   122,
     121,   121
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
     102,   102,   102,   102,   102,   103,   104,   105,   105,   106,
     106,   107,   108,   108,   109,   109,   109,   109,   109,   109,
     109,   109,   110,   110,   111,   112,   112,   112,   112,   113,
     113,   113,   113,   113,   114,   114,   114,   114,   114,   114,
     114,   115,   115,   115,   115,   115,   115,   115,   116,   116,
     116,   116,   116,   117,   117,   118,   118,   119,   119,   120,
     120,   120,   120,   121,   121,   121,   121,   121,   122,   122,
     123,   123,   123,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   125,   126,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   128
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
       3,     2,     7,     9,     2,     2,     4,     4,     6,     4,
       2,     4,     0,     1,     4,     0,     2,     2,     4,     1,
       1,     1,     1,     1,     0,     3,     5,     3,     3,     5,
       5,     0,     3,     5,     5,     7,     5,     3,     0,     3,
       5,     5,     7,     0,     3,     0,     3,     0,     3,     3,
       5,     3,     5,     0,     4,     4,     6,     6,     0,     1,
       0,     3,     3,     3,     3,     3,     5,     5,     3,     5,
       5,     7,     3,     4,     5,     6,     6,     7,     8,     9,
       5,     3,     5,     3,     3,     2,     3,     4,     0,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     2,     8
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
#line 214 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1528 "yacc_sql.tab.c"
    break;

  case 23: /* help: HELP SEMICOLON  */
#line 219 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1536 "yacc_sql.tab.c"
    break;

  case 24: /* sync: SYNC SEMICOLON  */
#line 224 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1544 "yacc_sql.tab.c"
    break;

  case 25: /* begin: TRX_BEGIN SEMICOLON  */
#line 230 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1552 "yacc_sql.tab.c"
    break;

  case 26: /* commit: TRX_COMMIT SEMICOLON  */
#line 236 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1560 "yacc_sql.tab.c"
    break;

  case 27: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 242 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1568 "yacc_sql.tab.c"
    break;

  case 28: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 248 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1577 "yacc_sql.tab.c"
    break;

  case 29: /* show_tables: SHOW TABLES SEMICOLON  */
#line 254 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1585 "yacc_sql.tab.c"
    break;

  case 30: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 260 "yacc_sql.y"
                                     {
		CONTEXT->ssql->flag = SCF_SHOW_INDEX;
		show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
	}
#line 1594 "yacc_sql.tab.c"
    break;

  case 31: /* desc_table: DESC ID SEMICOLON  */
#line 267 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1603 "yacc_sql.tab.c"
    break;

  case 32: /* create_index: CREATE unique_option INDEX ID ON ID LBRACE ID index_attr_list RBRACE SEMICOLON  */
#line 275 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), (yyvsp[-3].string), CONTEXT->unique);
		}
#line 1612 "yacc_sql.tab.c"
    break;

  case 34: /* unique_option: UNIQUE  */
#line 282 "yacc_sql.y"
                 {
		CONTEXT->unique = 1;
	}
#line 1620 "yacc_sql.tab.c"
    break;

  case 36: /* index_attr_list: COMMA ID index_attr_list  */
#line 296 "yacc_sql.y"
                                   {
		create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[-1].string));
	}
#line 1628 "yacc_sql.tab.c"
    break;

  case 37: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 302 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1637 "yacc_sql.tab.c"
    break;

  case 38: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 309 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1649 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 319 "yacc_sql.y"
                                   {    }
#line 1655 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def: ID_get type LBRACE number RBRACE NONULL  */
#line 324 "yacc_sql.y"
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
#line 1670 "yacc_sql.tab.c"
    break;

  case 42: /* attr_def: ID_get type LBRACE number RBRACE NULLABLE  */
#line 335 "yacc_sql.y"
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
#line 1685 "yacc_sql.tab.c"
    break;

  case 43: /* attr_def: ID_get type NONULL  */
#line 346 "yacc_sql.y"
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
#line 1700 "yacc_sql.tab.c"
    break;

  case 44: /* attr_def: ID_get type NULLABLE  */
#line 357 "yacc_sql.y"
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
#line 1715 "yacc_sql.tab.c"
    break;

  case 45: /* number: NUMBER  */
#line 369 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1721 "yacc_sql.tab.c"
    break;

  case 46: /* type: INT_T  */
#line 372 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1727 "yacc_sql.tab.c"
    break;

  case 47: /* type: STRING_T  */
#line 373 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1733 "yacc_sql.tab.c"
    break;

  case 48: /* type: TEXT_T  */
#line 374 "yacc_sql.y"
                    {(yyval.number)=TEXTS; }
#line 1739 "yacc_sql.tab.c"
    break;

  case 49: /* type: FLOAT_T  */
#line 375 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1745 "yacc_sql.tab.c"
    break;

  case 50: /* type: DATE_T  */
#line 376 "yacc_sql.y"
                    {(yyval.number)=DATES;}
#line 1751 "yacc_sql.tab.c"
    break;

  case 51: /* ID_get: ID  */
#line 380 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1760 "yacc_sql.tab.c"
    break;

  case 54: /* insert: INSERT INTO ID VALUES tuple tuple_list SEMICOLON  */
#line 394 "yacc_sql.y"
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
#line 1780 "yacc_sql.tab.c"
    break;

  case 55: /* tuple: LBRACE value value_list RBRACE  */
#line 411 "yacc_sql.y"
                                       {
		CONTEXT->tuple_num++;
		printf("yacc: tuple num %d\n", CONTEXT->tuple_num);
	}
#line 1789 "yacc_sql.tab.c"
    break;

  case 57: /* tuple_list: COMMA tuple tuple_list  */
#line 418 "yacc_sql.y"
                                 {
	}
#line 1796 "yacc_sql.tab.c"
    break;

  case 59: /* value_list: COMMA value value_list  */
#line 423 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1804 "yacc_sql.tab.c"
    break;

  case 60: /* value: NUMBER  */
#line 428 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
  		value_init_integer(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], (yyvsp[0].number));
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
#line 1814 "yacc_sql.tab.c"
    break;

  case 61: /* value: FLOAT  */
#line 433 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		value_init_float(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], (yyvsp[0].floats));
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
#line 1824 "yacc_sql.tab.c"
    break;

  case 62: /* value: SSS  */
#line 438 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		value_init_string(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], (yyvsp[0].string));
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
#line 1835 "yacc_sql.tab.c"
    break;

  case 63: /* value: DATE_STR  */
#line 444 "yacc_sql.y"
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
#line 1856 "yacc_sql.tab.c"
    break;

  case 64: /* value: NULLVALUE  */
#line 460 "yacc_sql.y"
                   {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
		value_init_null(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++]);
	}
#line 1865 "yacc_sql.tab.c"
    break;

  case 65: /* delete: DELETE FROM ID where SEMICOLON  */
#line 468 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
			CONTEXT->last_conditino_seqno = 0;
    }
#line 1878 "yacc_sql.tab.c"
    break;

  case 66: /* update: UPDATE ID SET assign assign_list where SEMICOLON  */
#line 479 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-5].string), CONTEXT->attribute_name, CONTEXT->values, CONTEXT->upselect_num,
					CONTEXT->conditions, CONTEXT->condition_length, CONTEXT->upselect_vec);
			CONTEXT->condition_length = 0;
			CONTEXT->last_conditino_seqno = 0;
			CONTEXT->value_length = 0;
			CONTEXT->upselect_num = 0;
		}
#line 1892 "yacc_sql.tab.c"
    break;

  case 67: /* assign: ID EQ value  */
#line 491 "yacc_sql.y"
                    {
		CONTEXT->upselect_num++;
		CONTEXT->attribute_name[CONTEXT->value_length - 1] = (yyvsp[-2].string);
	}
#line 1901 "yacc_sql.tab.c"
    break;

  case 68: /* assign: ID EQ sub_query  */
#line 495 "yacc_sql.y"
                          {
		CONTEXT->upselect_num++;
		CONTEXT->value_length++;
		CONTEXT->attribute_name[CONTEXT->value_length - 1] = (yyvsp[-2].string);
		CONTEXT->upselect_vec[CONTEXT->value_length - 1] = &CONTEXT->sub_query->sstr.selection;
	}
#line 1912 "yacc_sql.tab.c"
    break;

  case 72: /* select_query: SELECT select_attr FROM ID rel_list where order  */
#line 514 "yacc_sql.y"
                {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-3].string), NULL);

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
#line 1933 "yacc_sql.tab.c"
    break;

  case 73: /* select_query: SELECT select_attr FROM ID as_option ID rel_list where order  */
#line 531 "yacc_sql.y"
                {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-5].string), (yyvsp[-3].string));

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
#line 1954 "yacc_sql.tab.c"
    break;

  case 74: /* select_attr: STAR attr_list  */
#line 550 "yacc_sql.y"
                   {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1964 "yacc_sql.tab.c"
    break;

  case 75: /* select_attr: ID attr_list  */
#line 555 "yacc_sql.y"
                       {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1974 "yacc_sql.tab.c"
    break;

  case 76: /* select_attr: ID as_option ID attr_list  */
#line 560 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-3].string));
			attr.alias_name = (yyvsp[-1].string);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1985 "yacc_sql.tab.c"
    break;

  case 77: /* select_attr: ID DOT ID attr_list  */
#line 566 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1995 "yacc_sql.tab.c"
    break;

  case 78: /* select_attr: ID DOT ID as_option ID attr_list  */
#line 571 "yacc_sql.y"
                                           {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-5].string), (yyvsp[-3].string));
			attr.alias_name = (yyvsp[-1].string);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2006 "yacc_sql.tab.c"
    break;

  case 79: /* select_attr: ID DOT STAR attr_list  */
#line 577 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			// CONTEXT->aggregation_op = NO_AGGREGATE_OP;
			// selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_op);
			// selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, AggregationOp::NO_AGGREGATE_OP);
		}
#line 2019 "yacc_sql.tab.c"
    break;

  case 80: /* select_attr: aggregate_attr aggregate_attr_list  */
#line 585 "yacc_sql.y"
                                             {
		if (CONTEXT->last_aggregation_seqno == 0) {
			CONTEXT->last_aggregation_seqno = CONTEXT->aggregation_num;
		}		
		CONTEXT->ssql->sstr.selection.aggregation_alias[CONTEXT->last_aggregation_seqno-1] = NULL;
		CONTEXT->last_aggregation_seqno--;
	}
#line 2031 "yacc_sql.tab.c"
    break;

  case 81: /* select_attr: aggregate_attr as_option ID aggregate_attr_list  */
#line 592 "yacc_sql.y"
                                                          {
		if (CONTEXT->last_aggregation_seqno == 0) {
			CONTEXT->last_aggregation_seqno = CONTEXT->aggregation_num;
		}		
		CONTEXT->ssql->sstr.selection.aggregation_alias[CONTEXT->last_aggregation_seqno-1] = (yyvsp[-1].string);
		CONTEXT->last_aggregation_seqno--;
	}
#line 2043 "yacc_sql.tab.c"
    break;

  case 84: /* aggregate_attr: aggregate_op LBRACE aggregation_field_attr RBRACE  */
#line 615 "yacc_sql.y"
                                                          {
		// RelAttr attr;
		// relation_attr_init(&attr, NULL, $3);
		// printf("aggregation: get a attr %s\n", $3);
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		// selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		// CONTEXT->aggregation_num++;	
	}
#line 2056 "yacc_sql.tab.c"
    break;

  case 86: /* aggregation_field_attr: STAR attr_list  */
#line 626 "yacc_sql.y"
                         {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		printf("aggregation: get a attr *\n");
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
#line 2069 "yacc_sql.tab.c"
    break;

  case 87: /* aggregation_field_attr: ID attr_list  */
#line 634 "yacc_sql.y"
                       {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		printf("aggregation: get a attr %s\n", (yyvsp[-1].string));
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
#line 2082 "yacc_sql.tab.c"
    break;

  case 88: /* aggregation_field_attr: ID DOT ID attr_list  */
#line 642 "yacc_sql.y"
                              {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		printf("aggregation: get a attr %s\n", (yyvsp[-1].string));
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
#line 2095 "yacc_sql.tab.c"
    break;

  case 89: /* aggregate_op: COUNT  */
#line 652 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = COUNT_OP; }
#line 2101 "yacc_sql.tab.c"
    break;

  case 90: /* aggregate_op: AVG  */
#line 653 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = AVG_OP; }
#line 2107 "yacc_sql.tab.c"
    break;

  case 91: /* aggregate_op: MAX  */
#line 654 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = MAX_OP; }
#line 2113 "yacc_sql.tab.c"
    break;

  case 92: /* aggregate_op: MIN  */
#line 655 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = MIN_OP; }
#line 2119 "yacc_sql.tab.c"
    break;

  case 93: /* aggregate_op: SUM  */
#line 656 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = SUM_OP; }
#line 2125 "yacc_sql.tab.c"
    break;

  case 95: /* aggregate_attr_list: COMMA aggregate_attr aggregate_attr_list  */
#line 661 "yacc_sql.y"
                                                  {
		if (CONTEXT->last_aggregation_seqno == 0) {
			CONTEXT->last_aggregation_seqno = CONTEXT->aggregation_num;
		}		
		CONTEXT->ssql->sstr.selection.aggregation_alias[CONTEXT->last_aggregation_seqno-1] = NULL;
		CONTEXT->last_aggregation_seqno--;
	}
#line 2137 "yacc_sql.tab.c"
    break;

  case 96: /* aggregate_attr_list: COMMA aggregate_attr as_option ID aggregate_attr_list  */
#line 668 "yacc_sql.y"
                                                               {
		if (CONTEXT->last_aggregation_seqno == 0) {
			CONTEXT->last_aggregation_seqno = CONTEXT->aggregation_num;
		}		
		CONTEXT->ssql->sstr.selection.aggregation_alias[CONTEXT->last_aggregation_seqno-1] = (yyvsp[-1].string);
		CONTEXT->last_aggregation_seqno--;
	}
#line 2149 "yacc_sql.tab.c"
    break;

  case 97: /* aggregate_attr_list: COMMA STAR aggregate_attr_list  */
#line 676 "yacc_sql.y"
                                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2159 "yacc_sql.tab.c"
    break;

  case 98: /* aggregate_attr_list: COMMA ID aggregate_attr_list  */
#line 681 "yacc_sql.y"
                                      {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2169 "yacc_sql.tab.c"
    break;

  case 99: /* aggregate_attr_list: COMMA ID DOT ID aggregate_attr_list  */
#line 686 "yacc_sql.y"
                                               {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2179 "yacc_sql.tab.c"
    break;

  case 100: /* aggregate_attr_list: COMMA ID DOT STAR aggregate_attr_list  */
#line 691 "yacc_sql.y"
                                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2189 "yacc_sql.tab.c"
    break;

  case 102: /* attr_list: COMMA ID attr_list  */
#line 700 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 2201 "yacc_sql.tab.c"
    break;

  case 103: /* attr_list: COMMA ID as_option ID attr_list  */
#line 707 "yacc_sql.y"
                                      {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-3].string));
			attr.alias_name = (yyvsp[-1].string);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 2214 "yacc_sql.tab.c"
    break;

  case 104: /* attr_list: COMMA ID DOT ID attr_list  */
#line 715 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 2226 "yacc_sql.tab.c"
    break;

  case 105: /* attr_list: COMMA ID DOT ID as_option ID attr_list  */
#line 722 "yacc_sql.y"
                                             {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-5].string), (yyvsp[-3].string));
			attr.alias_name = (yyvsp[-1].string);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 2239 "yacc_sql.tab.c"
    break;

  case 106: /* attr_list: COMMA ID DOT STAR attr_list  */
#line 730 "yacc_sql.y"
                                      {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2249 "yacc_sql.tab.c"
    break;

  case 107: /* attr_list: COMMA aggregate_attr attr_list  */
#line 736 "yacc_sql.y"
                                         {

	}
#line 2257 "yacc_sql.tab.c"
    break;

  case 109: /* rel_list: COMMA ID rel_list  */
#line 743 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string), NULL);
		  }
#line 2265 "yacc_sql.tab.c"
    break;

  case 110: /* rel_list: COMMA ID as_option ID rel_list  */
#line 746 "yacc_sql.y"
                                     {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-3].string), (yyvsp[-1].string));
		  }
#line 2273 "yacc_sql.tab.c"
    break;

  case 111: /* rel_list: INNER JOIN ID on_list rel_list  */
#line 749 "yacc_sql.y"
                                         {
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string), NULL);
	}
#line 2281 "yacc_sql.tab.c"
    break;

  case 112: /* rel_list: INNER JOIN ID as_option ID on_list rel_list  */
#line 752 "yacc_sql.y"
                                                      {
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-4].string), (yyvsp[-2].string));
	}
#line 2289 "yacc_sql.tab.c"
    break;

  case 114: /* on_list: ON condition condition_list  */
#line 759 "yacc_sql.y"
                                      {

	}
#line 2297 "yacc_sql.tab.c"
    break;

  case 116: /* where: WHERE condition condition_list  */
#line 765 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2305 "yacc_sql.tab.c"
    break;

  case 117: /* order: %empty  */
#line 771 "yacc_sql.y"
        {
		selects_set_order(&CONTEXT->ssql->sstr.selection, 0);
	}
#line 2313 "yacc_sql.tab.c"
    break;

  case 118: /* order: ORDER BY order_attr  */
#line 774 "yacc_sql.y"
                              {
		selects_set_order(&CONTEXT->ssql->sstr.selection, 1);
	}
#line 2321 "yacc_sql.tab.c"
    break;

  case 119: /* order_attr: ID asc order_attr_list  */
#line 780 "yacc_sql.y"
                               {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
		}
#line 2331 "yacc_sql.tab.c"
    break;

  case 120: /* order_attr: ID DOT ID asc order_attr_list  */
#line 785 "yacc_sql.y"
                                        {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
		}
#line 2341 "yacc_sql.tab.c"
    break;

  case 121: /* order_attr: ID DESC order_attr_list  */
#line 790 "yacc_sql.y"
                                  {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
		}
#line 2351 "yacc_sql.tab.c"
    break;

  case 122: /* order_attr: ID DOT ID DESC order_attr_list  */
#line 795 "yacc_sql.y"
                                         {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
		}
#line 2361 "yacc_sql.tab.c"
    break;

  case 124: /* order_attr_list: COMMA ID asc order_attr_list  */
#line 804 "yacc_sql.y"
                                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
      }
#line 2371 "yacc_sql.tab.c"
    break;

  case 125: /* order_attr_list: COMMA ID DESC order_attr_list  */
#line 809 "yacc_sql.y"
                                    {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
      }
#line 2381 "yacc_sql.tab.c"
    break;

  case 126: /* order_attr_list: COMMA ID DOT ID asc order_attr_list  */
#line 814 "yacc_sql.y"
                                          {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
  	  }
#line 2391 "yacc_sql.tab.c"
    break;

  case 127: /* order_attr_list: COMMA ID DOT ID DESC order_attr_list  */
#line 819 "yacc_sql.y"
                                           {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
  	  }
#line 2401 "yacc_sql.tab.c"
    break;

  case 131: /* condition_list: AND condition condition_list  */
#line 832 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
				if (CONTEXT->last_conditino_seqno == 0) {
					CONTEXT->last_conditino_seqno = CONTEXT->condition_length;
				}
				CONTEXT->conditions[CONTEXT->last_conditino_seqno-1].is_and = 1;
				CONTEXT->last_conditino_seqno--;
				printf("get an and condition: seqno %d\n", CONTEXT->last_conditino_seqno);
			}
#line 2415 "yacc_sql.tab.c"
    break;

  case 132: /* condition_list: OR condition condition_list  */
#line 841 "yacc_sql.y"
                                  {
				if (CONTEXT->last_conditino_seqno == 0) {
					CONTEXT->last_conditino_seqno = CONTEXT->condition_length;
				}
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
				CONTEXT->conditions[CONTEXT->last_conditino_seqno-1].is_and = 0;
				CONTEXT->last_conditino_seqno--;
				printf("get an or condition: seqno %d\n", CONTEXT->last_conditino_seqno);
			}
#line 2429 "yacc_sql.tab.c"
    break;

  case 133: /* condition: ID comOp value  */
#line 853 "yacc_sql.y"
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
#line 2455 "yacc_sql.tab.c"
    break;

  case 134: /* condition: value comOp value  */
#line 875 "yacc_sql.y"
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
#line 2480 "yacc_sql.tab.c"
    break;

  case 135: /* condition: ID comOp ID  */
#line 896 "yacc_sql.y"
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
#line 2505 "yacc_sql.tab.c"
    break;

  case 136: /* condition: ID comOp ID DOT ID  */
#line 917 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

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
#line 2530 "yacc_sql.tab.c"
    break;

  case 137: /* condition: ID DOT ID comOp ID  */
#line 938 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
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
#line 2555 "yacc_sql.tab.c"
    break;

  case 138: /* condition: value comOp ID  */
#line 959 "yacc_sql.y"
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
#line 2582 "yacc_sql.tab.c"
    break;

  case 139: /* condition: ID DOT ID comOp value  */
#line 982 "yacc_sql.y"
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
#line 2608 "yacc_sql.tab.c"
    break;

  case 140: /* condition: value comOp ID DOT ID  */
#line 1004 "yacc_sql.y"
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
#line 2634 "yacc_sql.tab.c"
    break;

  case 141: /* condition: ID DOT ID comOp ID DOT ID  */
#line 1026 "yacc_sql.y"
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
#line 2658 "yacc_sql.tab.c"
    break;

  case 142: /* condition: ID IN sub_query  */
#line 1045 "yacc_sql.y"
                          {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

		Condition condition;
		condition_init(&condition, Contain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		
	}
#line 2672 "yacc_sql.tab.c"
    break;

  case 143: /* condition: ID NOT IN sub_query  */
#line 1054 "yacc_sql.y"
                              {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-3].string));

		Condition condition;
		condition_init(&condition, NotContain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 2686 "yacc_sql.tab.c"
    break;

  case 144: /* condition: ID DOT ID IN sub_query  */
#line 1063 "yacc_sql.y"
                                 {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));

		Condition condition;
		condition_init(&condition, Contain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		
	}
#line 2700 "yacc_sql.tab.c"
    break;

  case 145: /* condition: ID DOT ID NOT IN sub_query  */
#line 1072 "yacc_sql.y"
                                     {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-5].string), (yyvsp[-3].string));

		Condition condition;
		condition_init(&condition, NotContain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 2714 "yacc_sql.tab.c"
    break;

  case 146: /* condition: ID IN LBRACE value value_list RBRACE  */
#line 1081 "yacc_sql.y"
                                               {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-5].string));

		Condition condition;
		condition_init(&condition, Contain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, 
			CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length = 0;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 2730 "yacc_sql.tab.c"
    break;

  case 147: /* condition: ID NOT IN LBRACE value value_list RBRACE  */
#line 1092 "yacc_sql.y"
                                                   {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-6].string));

		Condition condition;
		condition_init(&condition, NotContain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, 
			CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length = 0;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 2746 "yacc_sql.tab.c"
    break;

  case 148: /* condition: ID DOT ID IN LBRACE value value_list RBRACE  */
#line 1103 "yacc_sql.y"
                                                      {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-7].string), (yyvsp[-5].string));

		Condition condition;
		condition_init(&condition, Contain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, 
			CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length = 0;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 2762 "yacc_sql.tab.c"
    break;

  case 149: /* condition: ID DOT ID NOT IN LBRACE value value_list RBRACE  */
#line 1114 "yacc_sql.y"
                                                          {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-8].string), (yyvsp[-6].string));

		Condition condition;
		condition_init(&condition, NotContain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, 
			CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length = 0;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 2778 "yacc_sql.tab.c"
    break;

  case 150: /* condition: ID DOT ID comOp sub_query  */
#line 1125 "yacc_sql.y"
                                    {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));

		Condition condition;
		condition_init(&condition, Comparison, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2791 "yacc_sql.tab.c"
    break;

  case 151: /* condition: ID comOp sub_query  */
#line 1133 "yacc_sql.y"
                             {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

		Condition condition;
		condition_init(&condition, Comparison, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2804 "yacc_sql.tab.c"
    break;

  case 152: /* condition: sub_query comOp ID DOT ID  */
#line 1141 "yacc_sql.y"
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
#line 2833 "yacc_sql.tab.c"
    break;

  case 153: /* condition: sub_query comOp ID  */
#line 1165 "yacc_sql.y"
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
#line 2861 "yacc_sql.tab.c"
    break;

  case 154: /* condition: sub_query comOp sub_query  */
#line 1188 "yacc_sql.y"
                                    {
		Condition condition;
		condition_init(&condition, Comparison, CONTEXT->comp, 0, 1, NULL, NULL, &CONTEXT->left_sub_query->sstr.selection, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 2872 "yacc_sql.tab.c"
    break;

  case 155: /* condition: EXISTS sub_query  */
#line 1194 "yacc_sql.y"
                           {

		Condition condition;
		condition_init(&condition, Exists, CONTEXT->comp, 0, 0, NULL, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 2884 "yacc_sql.tab.c"
    break;

  case 156: /* condition: NOT EXISTS sub_query  */
#line 1201 "yacc_sql.y"
                               {

		Condition condition;
		condition_init(&condition, NotExists, CONTEXT->comp, 0, 0, NULL, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 2896 "yacc_sql.tab.c"
    break;

  case 157: /* sub_query: LBRACE N select_query RBRACE  */
#line 1211 "yacc_sql.y"
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
#line 2914 "yacc_sql.tab.c"
    break;

  case 158: /* N: %empty  */
#line 1224 "yacc_sql.y"
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
#line 2934 "yacc_sql.tab.c"
    break;

  case 159: /* comOp: EQ  */
#line 1242 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2940 "yacc_sql.tab.c"
    break;

  case 160: /* comOp: LT  */
#line 1243 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2946 "yacc_sql.tab.c"
    break;

  case 161: /* comOp: GT  */
#line 1244 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2952 "yacc_sql.tab.c"
    break;

  case 162: /* comOp: LE  */
#line 1245 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2958 "yacc_sql.tab.c"
    break;

  case 163: /* comOp: GE  */
#line 1246 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2964 "yacc_sql.tab.c"
    break;

  case 164: /* comOp: NE  */
#line 1247 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2970 "yacc_sql.tab.c"
    break;

  case 165: /* comOp: IS  */
#line 1248 "yacc_sql.y"
             { CONTEXT->comp = LOGICAL_IS; }
#line 2976 "yacc_sql.tab.c"
    break;

  case 166: /* comOp: IS NOT  */
#line 1249 "yacc_sql.y"
                 {CONTEXT->comp = LOGICAL_IS_NOT; }
#line 2982 "yacc_sql.tab.c"
    break;

  case 167: /* comOp: LIKE  */
#line 1250 "yacc_sql.y"
               { CONTEXT->comp = LIKE_OP; }
#line 2988 "yacc_sql.tab.c"
    break;

  case 168: /* comOp: NOT LIKE  */
#line 1251 "yacc_sql.y"
                   { CONTEXT->comp = NOT_LIKE_OP; }
#line 2994 "yacc_sql.tab.c"
    break;

  case 169: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 1256 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 3003 "yacc_sql.tab.c"
    break;


#line 3007 "yacc_sql.tab.c"

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

#line 1261 "yacc_sql.y"

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
