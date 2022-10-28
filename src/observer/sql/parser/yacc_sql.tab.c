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


#line 151 "yacc_sql.tab.c"

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
  YYSYMBOL_NUMBER = 64,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 65,                     /* FLOAT  */
  YYSYMBOL_ID = 66,                        /* ID  */
  YYSYMBOL_PATH = 67,                      /* PATH  */
  YYSYMBOL_SSS = 68,                       /* SSS  */
  YYSYMBOL_STAR = 69,                      /* STAR  */
  YYSYMBOL_STRING_V = 70,                  /* STRING_V  */
  YYSYMBOL_DATE_STR = 71,                  /* DATE_STR  */
  YYSYMBOL_NULLVALUE = 72,                 /* NULLVALUE  */
  YYSYMBOL_YYACCEPT = 73,                  /* $accept  */
  YYSYMBOL_commands = 74,                  /* commands  */
  YYSYMBOL_command = 75,                   /* command  */
  YYSYMBOL_exit = 76,                      /* exit  */
  YYSYMBOL_help = 77,                      /* help  */
  YYSYMBOL_sync = 78,                      /* sync  */
  YYSYMBOL_begin = 79,                     /* begin  */
  YYSYMBOL_commit = 80,                    /* commit  */
  YYSYMBOL_rollback = 81,                  /* rollback  */
  YYSYMBOL_drop_table = 82,                /* drop_table  */
  YYSYMBOL_show_tables = 83,               /* show_tables  */
  YYSYMBOL_show_index = 84,                /* show_index  */
  YYSYMBOL_desc_table = 85,                /* desc_table  */
  YYSYMBOL_create_index = 86,              /* create_index  */
  YYSYMBOL_unique_option = 87,             /* unique_option  */
  YYSYMBOL_index_attr_list = 88,           /* index_attr_list  */
  YYSYMBOL_drop_index = 89,                /* drop_index  */
  YYSYMBOL_create_table = 90,              /* create_table  */
  YYSYMBOL_attr_def_list = 91,             /* attr_def_list  */
  YYSYMBOL_attr_def = 92,                  /* attr_def  */
  YYSYMBOL_number = 93,                    /* number  */
  YYSYMBOL_type = 94,                      /* type  */
  YYSYMBOL_ID_get = 95,                    /* ID_get  */
  YYSYMBOL_NONULL = 96,                    /* NONULL  */
  YYSYMBOL_insert = 97,                    /* insert  */
  YYSYMBOL_tuple = 98,                     /* tuple  */
  YYSYMBOL_tuple_list = 99,                /* tuple_list  */
  YYSYMBOL_value_list = 100,               /* value_list  */
  YYSYMBOL_value = 101,                    /* value  */
  YYSYMBOL_delete = 102,                   /* delete  */
  YYSYMBOL_update = 103,                   /* update  */
  YYSYMBOL_assign = 104,                   /* assign  */
  YYSYMBOL_assign_list = 105,              /* assign_list  */
  YYSYMBOL_select = 106,                   /* select  */
  YYSYMBOL_select_query = 107,             /* select_query  */
  YYSYMBOL_select_attr = 108,              /* select_attr  */
  YYSYMBOL_aggregate_attr = 109,           /* aggregate_attr  */
  YYSYMBOL_aggregation_field_attr = 110,   /* aggregation_field_attr  */
  YYSYMBOL_aggregate_op = 111,             /* aggregate_op  */
  YYSYMBOL_aggregate_attr_list = 112,      /* aggregate_attr_list  */
  YYSYMBOL_attr_list = 113,                /* attr_list  */
  YYSYMBOL_rel_list = 114,                 /* rel_list  */
  YYSYMBOL_on_list = 115,                  /* on_list  */
  YYSYMBOL_where = 116,                    /* where  */
  YYSYMBOL_order = 117,                    /* order  */
  YYSYMBOL_order_attr = 118,               /* order_attr  */
  YYSYMBOL_order_attr_list = 119,          /* order_attr_list  */
  YYSYMBOL_asc = 120,                      /* asc  */
  YYSYMBOL_condition_list = 121,           /* condition_list  */
  YYSYMBOL_condition = 122,                /* condition  */
  YYSYMBOL_sub_query = 123,                /* sub_query  */
  YYSYMBOL_N = 124,                        /* N  */
  YYSYMBOL_comOp = 125,                    /* comOp  */
  YYSYMBOL_load_data = 126                 /* load_data  */
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
#define YYLAST   329

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  73
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  54
/* YYNRULES -- Number of rules.  */
#define YYNRULES  155
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  318

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   327


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
      65,    66,    67,    68,    69,    70,    71,    72
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   183,   183,   185,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   210,   215,   220,   226,   232,   238,   244,   250,
     256,   263,   270,   276,   278,   290,   292,   297,   304,   313,
     315,   319,   330,   341,   352,   365,   368,   369,   370,   371,
     372,   375,   382,   383,   389,   407,   412,   414,   417,   419,
     424,   429,   434,   440,   456,   463,   474,   487,   491,   500,
     502,   506,   509,   529,   534,   539,   544,   552,   567,   576,
     578,   586,   594,   604,   605,   606,   607,   608,   611,   613,
     617,   622,   627,   632,   639,   641,   648,   655,   661,   666,
     668,   671,   676,   678,   682,   684,   690,   693,   699,   704,
     709,   714,   721,   723,   728,   733,   738,   745,   746,   749,
     751,   760,   771,   793,   814,   835,   858,   880,   902,   922,
     931,   940,   949,   958,   969,   980,   991,  1002,  1010,  1018,
    1042,  1065,  1072,  1082,  1090,  1108,  1109,  1110,  1111,  1112,
    1113,  1114,  1115,  1116,  1117,  1121
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
  "ASC", "OR", "NUMBER", "FLOAT", "ID", "PATH", "SSS", "STAR", "STRING_V",
  "DATE_STR", "NULLVALUE", "$accept", "commands", "command", "exit",
  "help", "sync", "begin", "commit", "rollback", "drop_table",
  "show_tables", "show_index", "desc_table", "create_index",
  "unique_option", "index_attr_list", "drop_index", "create_table",
  "attr_def_list", "attr_def", "number", "type", "ID_get", "NONULL",
  "insert", "tuple", "tuple_list", "value_list", "value", "delete",
  "update", "assign", "assign_list", "select", "select_query",
  "select_attr", "aggregate_attr", "aggregation_field_attr",
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

#define YYPACT_NINF (-269)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -269,   139,  -269,     5,    31,    63,   -45,    39,    35,    21,
      55,    22,    98,   125,   137,   143,   154,    62,  -269,  -269,
    -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,
    -269,  -269,  -269,  -269,  -269,  -269,   161,  -269,   105,  -269,
     167,   119,   122,  -269,  -269,  -269,  -269,  -269,    13,   178,
     165,   181,   184,   199,   200,   173,  -269,   156,   158,   201,
    -269,  -269,  -269,  -269,  -269,   198,  -269,   223,   174,   240,
     241,   179,   -44,  -269,  -269,   185,   132,  -269,    51,  -269,
    -269,   186,   222,   221,   189,   188,   191,   225,  -269,  -269,
      76,   178,   178,   178,    -5,    78,   181,   181,    79,   178,
     242,   255,   244,    12,   259,   226,   245,   234,  -269,   247,
     224,   202,    57,  -269,  -269,  -269,  -269,   203,   213,   221,
      61,  -269,  -269,  -269,   204,  -269,  -269,  -269,  -269,   170,
     253,  -269,   256,   217,  -269,  -269,   149,  -269,  -269,  -269,
     175,   -22,   175,  -269,    70,   189,   221,   268,   191,   258,
    -269,  -269,  -269,  -269,  -269,    14,   260,   178,   178,    -5,
     211,   218,   181,   181,   178,   261,   244,   277,   272,  -269,
     256,   216,  -269,  -269,  -269,  -269,  -269,  -269,   227,   267,
    -269,    90,    27,   229,    97,    12,    12,  -269,   228,  -269,
    -269,   245,   281,   230,   247,   284,   231,  -269,   219,  -269,
     232,  -269,  -269,  -269,   252,   236,  -269,  -269,  -269,  -269,
     170,   273,   253,  -269,   275,  -269,   168,  -269,   170,  -269,
     283,  -269,  -269,  -269,  -269,   264,  -269,   -22,   -22,   271,
    -269,  -269,   286,  -269,  -269,  -269,   285,  -269,   287,    12,
      -5,   235,   261,  -269,  -269,  -269,   288,   115,    38,   261,
     170,  -269,   237,  -269,  -269,   243,  -269,    75,   246,   289,
     -22,  -269,    -6,  -269,  -269,   170,  -269,   291,   279,  -269,
    -269,   293,   261,  -269,  -269,  -269,  -269,   287,   308,  -269,
     295,   248,  -269,   295,   261,   170,  -269,   249,  -269,   299,
    -269,  -269,   251,  -269,     9,  -269,   301,   261,  -269,  -269,
       7,   295,   295,  -269,   302,   295,   254,   295,  -269,  -269,
    -269,  -269,    23,  -269,   295,   295,  -269,  -269
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
       0,     0,     0,    83,    84,    85,    86,    87,    94,    94,
       0,    88,     0,     0,     0,     0,    24,     0,     0,     0,
      25,    26,    27,    23,    22,     0,    71,     0,     0,     0,
       0,     0,     0,    74,    73,     0,     0,    77,    79,    31,
      29,     0,     0,   104,     0,     0,     0,     0,    28,    37,
      94,    94,    94,    94,    99,    88,    88,    88,    94,    94,
       0,     0,     0,     0,     0,     0,    69,     0,    51,    39,
       0,     0,     0,    95,    98,    75,    76,     0,     0,   104,
       0,    91,    90,    89,     0,    81,    80,    78,    30,     0,
      56,   144,     0,     0,    60,    61,     0,    62,    63,    64,
       0,   119,     0,    65,     0,     0,   104,     0,     0,     0,
      46,    47,    48,    49,    50,    52,     0,    94,    94,    99,
       0,   106,    88,    88,    94,    58,     0,     0,     0,   141,
       0,     0,   145,   146,   147,   148,   149,   150,   151,     0,
     153,     0,     0,     0,     0,     0,     0,   105,     0,    67,
      68,    69,     0,     0,    39,     0,     0,    44,     0,    43,
       0,    96,    97,   100,   102,     0,    72,    92,    93,    82,
       0,     0,    56,    54,     0,   142,     0,   152,   144,   129,
       0,   154,   124,   122,   138,   125,   123,   119,   119,   140,
      70,    66,     0,    40,    38,    45,     0,    53,    35,     0,
      99,     0,    58,    55,    57,   143,     0,     0,     0,    58,
     144,   130,     0,   120,   121,     0,   155,    52,     0,     0,
     119,   101,   117,   107,    59,   144,   131,     0,     0,   126,
     137,     0,    58,   127,   139,    42,    41,    35,     0,   103,
     112,     0,   118,   112,    58,   144,   132,     0,   133,     0,
      36,    32,     0,   110,   117,   108,     0,    58,   128,   134,
     117,   112,   112,   135,     0,   112,     0,   112,   111,   109,
     136,   114,   117,   113,   112,   112,   116,   115
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,
    -269,  -269,  -269,  -269,  -269,    44,  -269,  -269,   128,   176,
    -269,  -269,  -269,    66,  -269,   159,   114,  -222,  -129,  -269,
    -269,   182,   138,  -269,   160,  -269,   -47,  -269,  -269,   -89,
     -33,  -158,  -269,  -101,  -269,  -269,  -128,  -268,  -193,  -176,
    -130,  -269,  -137,  -269
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    40,   259,    30,    31,   149,   109,
     236,   155,   110,   199,    32,   130,   167,   211,   140,    33,
      34,   106,   146,    35,    36,    50,    51,   100,    52,    77,
      73,   119,   240,   104,   206,   263,   293,   283,   187,   141,
     142,   168,   182,    37
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     165,   203,   169,   184,   280,   188,   121,   122,   123,   227,
     228,    38,   185,   117,   190,   189,    74,   305,   161,   301,
     264,    53,    92,   281,    91,    93,   302,   271,   131,    97,
     196,    71,   307,   314,   253,   254,   306,    41,    56,    42,
     215,   186,    72,   131,   315,   192,    54,    55,   118,   219,
     289,    57,   224,   223,   131,   226,   282,   113,   114,   115,
     116,   197,   296,   260,    39,   125,   126,   279,   132,   282,
     133,   282,   198,   207,   208,   304,   134,   135,   136,   248,
     137,   242,   261,   138,   139,   282,   131,    58,    59,   249,
     251,   134,   135,   222,    71,   137,    76,    71,   138,   139,
      65,    60,   134,   135,   268,   112,   137,   120,   124,   138,
     139,    43,    44,    45,    46,    47,   266,    98,   270,   269,
      99,   272,   275,   157,   201,   202,   158,   162,    61,    48,
     163,   209,    49,   198,   134,   135,   284,   286,   137,     2,
      62,   138,   139,     3,     4,   220,    63,   221,     5,     6,
       7,     8,     9,    10,    11,   295,   297,    64,    12,    13,
      14,   134,   135,   225,    66,   137,    15,    16,   138,   139,
     267,    67,   221,   308,   309,    68,    17,   311,   171,   313,
      43,    44,    45,    46,    47,    69,   316,   317,    70,   172,
     173,   174,   175,   176,   177,   178,    71,    75,    95,    76,
      78,    96,    79,    80,   179,    81,   180,   181,   172,   173,
     174,   175,   176,   177,   178,   172,   173,   174,   175,   176,
     177,   178,    82,   246,    83,   180,   247,    43,    44,    45,
      46,    47,   180,   183,   134,   135,    84,    85,   137,    86,
      87,   138,   139,    88,    89,    90,   150,   151,   152,   153,
     154,    94,   101,   102,   103,   105,   107,   108,   128,   127,
     129,   111,   143,   145,   147,   148,   144,   160,   156,   159,
     164,   166,   131,   170,   193,   195,   200,   204,   205,   210,
     213,     5,   216,   218,   231,   217,   221,   234,   239,   256,
     243,   237,   245,   252,   229,   235,   232,   241,   238,   250,
     255,   262,   257,   273,   265,   258,   278,   285,   287,   274,
     288,   291,   277,   292,   294,   298,   299,   300,   303,   310,
     312,   290,   233,   276,   194,   212,   244,   191,   214,   230
};

static const yytype_int16 yycheck[] =
{
     129,   159,   132,   140,    10,   142,    95,    96,    97,   185,
     186,     6,    34,    18,   144,   144,    49,    10,   119,    10,
     242,    66,    66,    29,    71,    69,   294,   249,    16,    76,
      16,    18,   300,    10,   227,   228,    29,     6,     3,     8,
     170,    63,    29,    16,   312,   146,     7,     8,    53,   179,
     272,    30,   182,   182,    16,   184,    62,    90,    91,    92,
      93,    47,   284,   239,    59,    98,    99,   260,    56,    62,
      58,    62,    58,   162,   163,   297,    64,    65,    66,   216,
      68,   210,   240,    71,    72,    62,    16,    32,    66,   218,
     220,    64,    65,    66,    18,    68,    18,    18,    71,    72,
      38,     3,    64,    65,    66,    29,    68,    29,    29,    71,
      72,    48,    49,    50,    51,    52,   246,    66,   248,   248,
      69,   250,    47,    66,   157,   158,    69,    66,     3,    66,
      69,   164,    69,    58,    64,    65,   265,   267,    68,     0,
       3,    71,    72,     4,     5,    55,     3,    57,     9,    10,
      11,    12,    13,    14,    15,   283,   285,     3,    19,    20,
      21,    64,    65,    66,     3,    68,    27,    28,    71,    72,
      55,    66,    57,   301,   302,     8,    37,   305,    29,   307,
      48,    49,    50,    51,    52,    66,   314,   315,    66,    40,
      41,    42,    43,    44,    45,    46,    18,    32,    66,    18,
      16,    69,     3,     3,    55,    32,    57,    58,    40,    41,
      42,    43,    44,    45,    46,    40,    41,    42,    43,    44,
      45,    46,    66,    55,    66,    57,    58,    48,    49,    50,
      51,    52,    57,    58,    64,    65,    35,    39,    68,    16,
      66,    71,    72,     3,     3,    66,    22,    23,    24,    25,
      26,    66,    66,    31,    33,    66,    68,    66,     3,    17,
      16,    36,     3,    18,    30,    18,    40,    54,    66,    66,
      66,    18,    16,    56,     6,    17,    16,    66,    60,    18,
       3,     9,    66,    16,     3,    58,    57,     3,    36,     3,
      17,    72,    17,    29,    66,    64,    66,    61,    66,    16,
      29,    66,    17,    66,    16,    18,    17,    16,    29,    66,
      17,     3,    66,    18,    66,    66,    17,    66,    17,    17,
      66,   277,   194,   257,   148,   166,   212,   145,   168,   191
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    74,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    19,    20,    21,    27,    28,    37,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      89,    90,    97,   102,   103,   106,   107,   126,     6,    59,
      87,     6,     8,    48,    49,    50,    51,    52,    66,    69,
     108,   109,   111,    66,     7,     8,     3,    30,    32,    66,
       3,     3,     3,     3,     3,    38,     3,    66,     8,    66,
      66,    18,    29,   113,   113,    32,    18,   112,    16,     3,
       3,    32,    66,    66,    35,    39,    16,    66,     3,     3,
      66,   109,    66,    69,    66,    66,    69,   109,    66,    69,
     110,    66,    31,    33,   116,    66,   104,    68,    66,    92,
      95,    36,    29,   113,   113,   113,   113,    18,    53,   114,
      29,   112,   112,   112,    29,   113,   113,    17,     3,    16,
      98,    16,    56,    58,    64,    65,    66,    68,    71,    72,
     101,   122,   123,     3,    40,    18,   105,    30,    18,    91,
      22,    23,    24,    25,    26,    94,    66,    66,    69,    66,
      54,   116,    66,    69,    66,   101,    18,    99,   124,   123,
      56,    29,    40,    41,    42,    43,    44,    45,    46,    55,
      57,    58,   125,    58,   125,    34,    63,   121,   125,   101,
     123,   104,   116,     6,    92,    17,    16,    47,    58,    96,
      16,   113,   113,   114,    66,    60,   117,   112,   112,   113,
      18,   100,    98,     3,   107,   123,    66,    58,    16,   123,
      55,    57,    66,   101,   123,    66,   101,   122,   122,    66,
     105,     3,    66,    91,     3,    64,    93,    72,    66,    36,
     115,    61,   101,    17,    99,    17,    55,    58,   125,   101,
      16,   123,    29,   121,   121,    29,     3,    17,    18,    88,
     122,   114,    66,   118,   100,    16,   123,    55,    66,   101,
     123,   100,   101,    66,    66,    47,    96,    66,    17,   121,
      10,    29,    62,   120,   101,    16,   123,    29,    17,   100,
      88,     3,    18,   119,    66,   119,   100,   101,    66,    17,
      66,    10,   120,    17,   100,    10,    29,   120,   119,   119,
      17,   119,    66,   119,    10,   120,   119,   119
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    73,    74,    74,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    87,    88,    88,    89,    90,    91,
      91,    92,    92,    92,    92,    93,    94,    94,    94,    94,
      94,    95,    96,    96,    97,    98,    99,    99,   100,   100,
     101,   101,   101,   101,   101,   102,   103,   104,   104,   105,
     105,   106,   107,   108,   108,   108,   108,   108,   109,   110,
     110,   110,   110,   111,   111,   111,   111,   111,   112,   112,
     112,   112,   112,   112,   113,   113,   113,   113,   113,   114,
     114,   114,   115,   115,   116,   116,   117,   117,   118,   118,
     118,   118,   119,   119,   119,   119,   119,   120,   120,   121,
     121,   121,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   123,   124,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   126
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
       3,     2,     7,     2,     2,     4,     4,     2,     4,     0,
       2,     2,     4,     1,     1,     1,     1,     1,     0,     3,
       3,     3,     5,     5,     0,     3,     5,     5,     3,     0,
       3,     5,     0,     3,     0,     3,     0,     3,     3,     5,
       3,     5,     0,     4,     4,     6,     6,     0,     1,     0,
       3,     3,     3,     3,     3,     3,     5,     5,     7,     3,
       4,     5,     6,     6,     7,     8,     9,     5,     3,     5,
       3,     2,     3,     4,     0,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     2,     8
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
#line 210 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1497 "yacc_sql.tab.c"
    break;

  case 23: /* help: HELP SEMICOLON  */
#line 215 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1505 "yacc_sql.tab.c"
    break;

  case 24: /* sync: SYNC SEMICOLON  */
#line 220 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1513 "yacc_sql.tab.c"
    break;

  case 25: /* begin: TRX_BEGIN SEMICOLON  */
#line 226 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1521 "yacc_sql.tab.c"
    break;

  case 26: /* commit: TRX_COMMIT SEMICOLON  */
#line 232 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1529 "yacc_sql.tab.c"
    break;

  case 27: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 238 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1537 "yacc_sql.tab.c"
    break;

  case 28: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 244 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1546 "yacc_sql.tab.c"
    break;

  case 29: /* show_tables: SHOW TABLES SEMICOLON  */
#line 250 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1554 "yacc_sql.tab.c"
    break;

  case 30: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 256 "yacc_sql.y"
                                     {
		CONTEXT->ssql->flag = SCF_SHOW_INDEX;
		show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
	}
#line 1563 "yacc_sql.tab.c"
    break;

  case 31: /* desc_table: DESC ID SEMICOLON  */
#line 263 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1572 "yacc_sql.tab.c"
    break;

  case 32: /* create_index: CREATE unique_option INDEX ID ON ID LBRACE ID index_attr_list RBRACE SEMICOLON  */
#line 271 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), (yyvsp[-3].string), CONTEXT->unique);
		}
#line 1581 "yacc_sql.tab.c"
    break;

  case 34: /* unique_option: UNIQUE  */
#line 278 "yacc_sql.y"
                 {
		CONTEXT->unique = 1;
	}
#line 1589 "yacc_sql.tab.c"
    break;

  case 36: /* index_attr_list: COMMA ID index_attr_list  */
#line 292 "yacc_sql.y"
                                   {
		create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[-1].string));
	}
#line 1597 "yacc_sql.tab.c"
    break;

  case 37: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 298 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1606 "yacc_sql.tab.c"
    break;

  case 38: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 305 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1618 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 315 "yacc_sql.y"
                                   {    }
#line 1624 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def: ID_get type LBRACE number RBRACE NONULL  */
#line 320 "yacc_sql.y"
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
#line 1639 "yacc_sql.tab.c"
    break;

  case 42: /* attr_def: ID_get type LBRACE number RBRACE NULLABLE  */
#line 331 "yacc_sql.y"
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
#line 1654 "yacc_sql.tab.c"
    break;

  case 43: /* attr_def: ID_get type NONULL  */
#line 342 "yacc_sql.y"
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
#line 1669 "yacc_sql.tab.c"
    break;

  case 44: /* attr_def: ID_get type NULLABLE  */
#line 353 "yacc_sql.y"
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
#line 1684 "yacc_sql.tab.c"
    break;

  case 45: /* number: NUMBER  */
#line 365 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1690 "yacc_sql.tab.c"
    break;

  case 46: /* type: INT_T  */
#line 368 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1696 "yacc_sql.tab.c"
    break;

  case 47: /* type: STRING_T  */
#line 369 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1702 "yacc_sql.tab.c"
    break;

  case 48: /* type: TEXT_T  */
#line 370 "yacc_sql.y"
                    {(yyval.number)=TEXTS; }
#line 1708 "yacc_sql.tab.c"
    break;

  case 49: /* type: FLOAT_T  */
#line 371 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1714 "yacc_sql.tab.c"
    break;

  case 50: /* type: DATE_T  */
#line 372 "yacc_sql.y"
                    {(yyval.number)=DATES;}
#line 1720 "yacc_sql.tab.c"
    break;

  case 51: /* ID_get: ID  */
#line 376 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1729 "yacc_sql.tab.c"
    break;

  case 54: /* insert: INSERT INTO ID VALUES tuple tuple_list SEMICOLON  */
#line 390 "yacc_sql.y"
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
#line 1749 "yacc_sql.tab.c"
    break;

  case 55: /* tuple: LBRACE value value_list RBRACE  */
#line 407 "yacc_sql.y"
                                       {
		CONTEXT->tuple_num++;
		printf("yacc: tuple num %d\n", CONTEXT->tuple_num);
	}
#line 1758 "yacc_sql.tab.c"
    break;

  case 57: /* tuple_list: COMMA tuple tuple_list  */
#line 414 "yacc_sql.y"
                                 {
	}
#line 1765 "yacc_sql.tab.c"
    break;

  case 59: /* value_list: COMMA value value_list  */
#line 419 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1773 "yacc_sql.tab.c"
    break;

  case 60: /* value: NUMBER  */
#line 424 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
  		value_init_integer(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], (yyvsp[0].number));
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
#line 1783 "yacc_sql.tab.c"
    break;

  case 61: /* value: FLOAT  */
#line 429 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		value_init_float(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], (yyvsp[0].floats));
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
#line 1793 "yacc_sql.tab.c"
    break;

  case 62: /* value: SSS  */
#line 434 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		value_init_string(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], (yyvsp[0].string));
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
#line 1804 "yacc_sql.tab.c"
    break;

  case 63: /* value: DATE_STR  */
#line 440 "yacc_sql.y"
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
#line 1825 "yacc_sql.tab.c"
    break;

  case 64: /* value: NULLVALUE  */
#line 456 "yacc_sql.y"
                   {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
		value_init_null(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++]);
	}
#line 1834 "yacc_sql.tab.c"
    break;

  case 65: /* delete: DELETE FROM ID where SEMICOLON  */
#line 464 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
			CONTEXT->last_conditino_seqno = 0;
    }
#line 1847 "yacc_sql.tab.c"
    break;

  case 66: /* update: UPDATE ID SET assign assign_list where SEMICOLON  */
#line 475 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-5].string), CONTEXT->attribute_name, CONTEXT->values, CONTEXT->upselect_num,
					CONTEXT->conditions, CONTEXT->condition_length, CONTEXT->upselect_vec);
			CONTEXT->condition_length = 0;
			CONTEXT->last_conditino_seqno = 0;
			CONTEXT->value_length = 0;
			CONTEXT->upselect_num = 0;
		}
#line 1861 "yacc_sql.tab.c"
    break;

  case 67: /* assign: ID EQ value  */
#line 487 "yacc_sql.y"
                    {
		CONTEXT->upselect_num++;
		CONTEXT->attribute_name[CONTEXT->value_length - 1] = (yyvsp[-2].string);
	}
#line 1870 "yacc_sql.tab.c"
    break;

  case 68: /* assign: ID EQ sub_query  */
#line 491 "yacc_sql.y"
                          {
		CONTEXT->upselect_num++;
		CONTEXT->value_length++;
		CONTEXT->attribute_name[CONTEXT->value_length - 1] = (yyvsp[-2].string);
		CONTEXT->upselect_vec[CONTEXT->value_length - 1] = &CONTEXT->sub_query->sstr.selection;
	}
#line 1881 "yacc_sql.tab.c"
    break;

  case 72: /* select_query: SELECT select_attr FROM ID rel_list where order  */
#line 510 "yacc_sql.y"
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
#line 1902 "yacc_sql.tab.c"
    break;

  case 73: /* select_attr: STAR attr_list  */
#line 529 "yacc_sql.y"
                   {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1912 "yacc_sql.tab.c"
    break;

  case 74: /* select_attr: ID attr_list  */
#line 534 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1922 "yacc_sql.tab.c"
    break;

  case 75: /* select_attr: ID DOT ID attr_list  */
#line 539 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1932 "yacc_sql.tab.c"
    break;

  case 76: /* select_attr: ID DOT STAR attr_list  */
#line 544 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			// CONTEXT->aggregation_op = NO_AGGREGATE_OP;
			// selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_op);
			// selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, AggregationOp::NO_AGGREGATE_OP);
		}
#line 1945 "yacc_sql.tab.c"
    break;

  case 77: /* select_attr: aggregate_attr aggregate_attr_list  */
#line 552 "yacc_sql.y"
                                             {
			
	}
#line 1953 "yacc_sql.tab.c"
    break;

  case 78: /* aggregate_attr: aggregate_op LBRACE aggregation_field_attr RBRACE  */
#line 567 "yacc_sql.y"
                                                          {
		// RelAttr attr;
		// relation_attr_init(&attr, NULL, $3);
		// printf("aggregation: get a attr %s\n", $3);
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		// selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		// CONTEXT->aggregation_num++;	
	}
#line 1966 "yacc_sql.tab.c"
    break;

  case 80: /* aggregation_field_attr: STAR attr_list  */
#line 578 "yacc_sql.y"
                         {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		printf("aggregation: get a attr *\n");
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
#line 1979 "yacc_sql.tab.c"
    break;

  case 81: /* aggregation_field_attr: ID attr_list  */
#line 586 "yacc_sql.y"
                       {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		printf("aggregation: get a attr %s\n", (yyvsp[-1].string));
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
#line 1992 "yacc_sql.tab.c"
    break;

  case 82: /* aggregation_field_attr: ID DOT ID attr_list  */
#line 594 "yacc_sql.y"
                              {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		printf("aggregation: get a attr %s\n", (yyvsp[-1].string));
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
#line 2005 "yacc_sql.tab.c"
    break;

  case 83: /* aggregate_op: COUNT  */
#line 604 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = COUNT_OP; }
#line 2011 "yacc_sql.tab.c"
    break;

  case 84: /* aggregate_op: AVG  */
#line 605 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = AVG_OP; }
#line 2017 "yacc_sql.tab.c"
    break;

  case 85: /* aggregate_op: MAX  */
#line 606 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = MAX_OP; }
#line 2023 "yacc_sql.tab.c"
    break;

  case 86: /* aggregate_op: MIN  */
#line 607 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = MIN_OP; }
#line 2029 "yacc_sql.tab.c"
    break;

  case 87: /* aggregate_op: SUM  */
#line 608 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = SUM_OP; }
#line 2035 "yacc_sql.tab.c"
    break;

  case 89: /* aggregate_attr_list: COMMA aggregate_attr aggregate_attr_list  */
#line 613 "yacc_sql.y"
                                                  {

	}
#line 2043 "yacc_sql.tab.c"
    break;

  case 90: /* aggregate_attr_list: COMMA STAR aggregate_attr_list  */
#line 617 "yacc_sql.y"
                                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2053 "yacc_sql.tab.c"
    break;

  case 91: /* aggregate_attr_list: COMMA ID aggregate_attr_list  */
#line 622 "yacc_sql.y"
                                      {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2063 "yacc_sql.tab.c"
    break;

  case 92: /* aggregate_attr_list: COMMA ID DOT ID aggregate_attr_list  */
#line 627 "yacc_sql.y"
                                               {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2073 "yacc_sql.tab.c"
    break;

  case 93: /* aggregate_attr_list: COMMA ID DOT STAR aggregate_attr_list  */
#line 632 "yacc_sql.y"
                                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2083 "yacc_sql.tab.c"
    break;

  case 95: /* attr_list: COMMA ID attr_list  */
#line 641 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 2095 "yacc_sql.tab.c"
    break;

  case 96: /* attr_list: COMMA ID DOT ID attr_list  */
#line 648 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 2107 "yacc_sql.tab.c"
    break;

  case 97: /* attr_list: COMMA ID DOT STAR attr_list  */
#line 655 "yacc_sql.y"
                                      {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2117 "yacc_sql.tab.c"
    break;

  case 98: /* attr_list: COMMA aggregate_attr attr_list  */
#line 661 "yacc_sql.y"
                                         {

	}
#line 2125 "yacc_sql.tab.c"
    break;

  case 100: /* rel_list: COMMA ID rel_list  */
#line 668 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 2133 "yacc_sql.tab.c"
    break;

  case 101: /* rel_list: INNER JOIN ID on_list rel_list  */
#line 671 "yacc_sql.y"
                                         {
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string));
	}
#line 2141 "yacc_sql.tab.c"
    break;

  case 103: /* on_list: ON condition condition_list  */
#line 678 "yacc_sql.y"
                                      {

	}
#line 2149 "yacc_sql.tab.c"
    break;

  case 105: /* where: WHERE condition condition_list  */
#line 684 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2157 "yacc_sql.tab.c"
    break;

  case 106: /* order: %empty  */
#line 690 "yacc_sql.y"
        {
		selects_set_order(&CONTEXT->ssql->sstr.selection, 0);
	}
#line 2165 "yacc_sql.tab.c"
    break;

  case 107: /* order: ORDER BY order_attr  */
#line 693 "yacc_sql.y"
                              {
		selects_set_order(&CONTEXT->ssql->sstr.selection, 1);
	}
#line 2173 "yacc_sql.tab.c"
    break;

  case 108: /* order_attr: ID asc order_attr_list  */
#line 699 "yacc_sql.y"
                               {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
		}
#line 2183 "yacc_sql.tab.c"
    break;

  case 109: /* order_attr: ID DOT ID asc order_attr_list  */
#line 704 "yacc_sql.y"
                                        {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
		}
#line 2193 "yacc_sql.tab.c"
    break;

  case 110: /* order_attr: ID DESC order_attr_list  */
#line 709 "yacc_sql.y"
                                  {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
		}
#line 2203 "yacc_sql.tab.c"
    break;

  case 111: /* order_attr: ID DOT ID DESC order_attr_list  */
#line 714 "yacc_sql.y"
                                         {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
		}
#line 2213 "yacc_sql.tab.c"
    break;

  case 113: /* order_attr_list: COMMA ID asc order_attr_list  */
#line 723 "yacc_sql.y"
                                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
      }
#line 2223 "yacc_sql.tab.c"
    break;

  case 114: /* order_attr_list: COMMA ID DESC order_attr_list  */
#line 728 "yacc_sql.y"
                                    {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
      }
#line 2233 "yacc_sql.tab.c"
    break;

  case 115: /* order_attr_list: COMMA ID DOT ID asc order_attr_list  */
#line 733 "yacc_sql.y"
                                          {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
  	  }
#line 2243 "yacc_sql.tab.c"
    break;

  case 116: /* order_attr_list: COMMA ID DOT ID DESC order_attr_list  */
#line 738 "yacc_sql.y"
                                           {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
  	  }
#line 2253 "yacc_sql.tab.c"
    break;

  case 120: /* condition_list: AND condition condition_list  */
#line 751 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
				if (CONTEXT->last_conditino_seqno == 0) {
					CONTEXT->last_conditino_seqno = CONTEXT->condition_length;
				}
				CONTEXT->conditions[CONTEXT->last_conditino_seqno-1].is_and = 1;
				CONTEXT->last_conditino_seqno--;
				printf("get an and condition: seqno %d\n", CONTEXT->last_conditino_seqno);
			}
#line 2267 "yacc_sql.tab.c"
    break;

  case 121: /* condition_list: OR condition condition_list  */
#line 760 "yacc_sql.y"
                                  {
				if (CONTEXT->last_conditino_seqno == 0) {
					CONTEXT->last_conditino_seqno = CONTEXT->condition_length;
				}
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
				CONTEXT->conditions[CONTEXT->last_conditino_seqno-1].is_and = 0;
				CONTEXT->last_conditino_seqno--;
				printf("get an or condition: seqno %d\n", CONTEXT->last_conditino_seqno);
			}
#line 2281 "yacc_sql.tab.c"
    break;

  case 122: /* condition: ID comOp value  */
#line 772 "yacc_sql.y"
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
#line 2307 "yacc_sql.tab.c"
    break;

  case 123: /* condition: value comOp value  */
#line 794 "yacc_sql.y"
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
#line 2332 "yacc_sql.tab.c"
    break;

  case 124: /* condition: ID comOp ID  */
#line 815 "yacc_sql.y"
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
#line 2357 "yacc_sql.tab.c"
    break;

  case 125: /* condition: value comOp ID  */
#line 836 "yacc_sql.y"
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
#line 2384 "yacc_sql.tab.c"
    break;

  case 126: /* condition: ID DOT ID comOp value  */
#line 859 "yacc_sql.y"
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
#line 2410 "yacc_sql.tab.c"
    break;

  case 127: /* condition: value comOp ID DOT ID  */
#line 881 "yacc_sql.y"
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
#line 2436 "yacc_sql.tab.c"
    break;

  case 128: /* condition: ID DOT ID comOp ID DOT ID  */
#line 903 "yacc_sql.y"
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
#line 2460 "yacc_sql.tab.c"
    break;

  case 129: /* condition: ID IN sub_query  */
#line 922 "yacc_sql.y"
                          {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

		Condition condition;
		condition_init(&condition, Contain, CONTEXT->comp, 1, &left_attr, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		
	}
#line 2474 "yacc_sql.tab.c"
    break;

  case 130: /* condition: ID NOT IN sub_query  */
#line 931 "yacc_sql.y"
                              {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-3].string));

		Condition condition;
		condition_init(&condition, NotContain, CONTEXT->comp, 1, &left_attr, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 2488 "yacc_sql.tab.c"
    break;

  case 131: /* condition: ID DOT ID IN sub_query  */
#line 940 "yacc_sql.y"
                                 {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));

		Condition condition;
		condition_init(&condition, Contain, CONTEXT->comp, 1, &left_attr, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		
	}
#line 2502 "yacc_sql.tab.c"
    break;

  case 132: /* condition: ID DOT ID NOT IN sub_query  */
#line 949 "yacc_sql.y"
                                     {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-5].string), (yyvsp[-3].string));

		Condition condition;
		condition_init(&condition, NotContain, CONTEXT->comp, 1, &left_attr, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 2516 "yacc_sql.tab.c"
    break;

  case 133: /* condition: ID IN LBRACE value value_list RBRACE  */
#line 958 "yacc_sql.y"
                                               {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-5].string));

		Condition condition;
		condition_init(&condition, Contain, CONTEXT->comp, 1, &left_attr, NULL, 0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, 
			CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length = 0;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 2532 "yacc_sql.tab.c"
    break;

  case 134: /* condition: ID NOT IN LBRACE value value_list RBRACE  */
#line 969 "yacc_sql.y"
                                                   {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-6].string));

		Condition condition;
		condition_init(&condition, NotContain, CONTEXT->comp, 1, &left_attr, NULL, 0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, 
			CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length = 0;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 2548 "yacc_sql.tab.c"
    break;

  case 135: /* condition: ID DOT ID IN LBRACE value value_list RBRACE  */
#line 980 "yacc_sql.y"
                                                      {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-7].string), (yyvsp[-5].string));

		Condition condition;
		condition_init(&condition, Contain, CONTEXT->comp, 1, &left_attr, NULL, 0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, 
			CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length = 0;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 2564 "yacc_sql.tab.c"
    break;

  case 136: /* condition: ID DOT ID NOT IN LBRACE value value_list RBRACE  */
#line 991 "yacc_sql.y"
                                                          {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-8].string), (yyvsp[-6].string));

		Condition condition;
		condition_init(&condition, NotContain, CONTEXT->comp, 1, &left_attr, NULL, 0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, 
			CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length = 0;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 2580 "yacc_sql.tab.c"
    break;

  case 137: /* condition: ID DOT ID comOp sub_query  */
#line 1002 "yacc_sql.y"
                                    {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));

		Condition condition;
		condition_init(&condition, Comparison, CONTEXT->comp, 1, &left_attr, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2593 "yacc_sql.tab.c"
    break;

  case 138: /* condition: ID comOp sub_query  */
#line 1010 "yacc_sql.y"
                             {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

		Condition condition;
		condition_init(&condition, Comparison, CONTEXT->comp, 1, &left_attr, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2606 "yacc_sql.tab.c"
    break;

  case 139: /* condition: sub_query comOp ID DOT ID  */
#line 1018 "yacc_sql.y"
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
		condition_init(&condition, Comparison, CONTEXT->comp, 1, &left_attr, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2635 "yacc_sql.tab.c"
    break;

  case 140: /* condition: sub_query comOp ID  */
#line 1042 "yacc_sql.y"
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
		condition_init(&condition, Comparison, CONTEXT->comp, 1, &left_attr, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2663 "yacc_sql.tab.c"
    break;

  case 141: /* condition: EXISTS sub_query  */
#line 1065 "yacc_sql.y"
                           {

		Condition condition;
		condition_init(&condition, Exists, CONTEXT->comp, 0, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 2675 "yacc_sql.tab.c"
    break;

  case 142: /* condition: NOT EXISTS sub_query  */
#line 1072 "yacc_sql.y"
                               {

		Condition condition;
		condition_init(&condition, NotExists, CONTEXT->comp, 0, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 2687 "yacc_sql.tab.c"
    break;

  case 143: /* sub_query: LBRACE N select_query RBRACE  */
#line 1082 "yacc_sql.y"
                                     {
		// TODO support complex sub query
		ParserContext *old_context = CONTEXT->last_context;
		old_context->sub_query = CONTEXT->ssql;
		*CONTEXT = *old_context;
		printf("sub query addr %p\n", old_context->sub_query);
		printf("swap back old context\n");
	}
#line 2700 "yacc_sql.tab.c"
    break;

  case 144: /* N: %empty  */
#line 1090 "yacc_sql.y"
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
#line 2720 "yacc_sql.tab.c"
    break;

  case 145: /* comOp: EQ  */
#line 1108 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2726 "yacc_sql.tab.c"
    break;

  case 146: /* comOp: LT  */
#line 1109 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2732 "yacc_sql.tab.c"
    break;

  case 147: /* comOp: GT  */
#line 1110 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2738 "yacc_sql.tab.c"
    break;

  case 148: /* comOp: LE  */
#line 1111 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2744 "yacc_sql.tab.c"
    break;

  case 149: /* comOp: GE  */
#line 1112 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2750 "yacc_sql.tab.c"
    break;

  case 150: /* comOp: NE  */
#line 1113 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2756 "yacc_sql.tab.c"
    break;

  case 151: /* comOp: IS  */
#line 1114 "yacc_sql.y"
             { CONTEXT->comp = LOGICAL_IS; }
#line 2762 "yacc_sql.tab.c"
    break;

  case 152: /* comOp: IS NOT  */
#line 1115 "yacc_sql.y"
                 {CONTEXT->comp = LOGICAL_IS_NOT; }
#line 2768 "yacc_sql.tab.c"
    break;

  case 153: /* comOp: LIKE  */
#line 1116 "yacc_sql.y"
               { CONTEXT->comp = LIKE_OP; }
#line 2774 "yacc_sql.tab.c"
    break;

  case 154: /* comOp: NOT LIKE  */
#line 1117 "yacc_sql.y"
                   { CONTEXT->comp = NOT_LIKE_OP; }
#line 2780 "yacc_sql.tab.c"
    break;

  case 155: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 1122 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2789 "yacc_sql.tab.c"
    break;


#line 2793 "yacc_sql.tab.c"

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

#line 1127 "yacc_sql.y"

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
