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
  YYSYMBOL_NULLABLE = 46,                  /* NULLABLE  */
  YYSYMBOL_COUNT = 47,                     /* COUNT  */
  YYSYMBOL_AVG = 48,                       /* AVG  */
  YYSYMBOL_MAX = 49,                       /* MAX  */
  YYSYMBOL_MIN = 50,                       /* MIN  */
  YYSYMBOL_SUM = 51,                       /* SUM  */
  YYSYMBOL_INNER = 52,                     /* INNER  */
  YYSYMBOL_JOIN = 53,                      /* JOIN  */
  YYSYMBOL_IN = 54,                        /* IN  */
  YYSYMBOL_EXISTS = 55,                    /* EXISTS  */
  YYSYMBOL_LIKE = 56,                      /* LIKE  */
  YYSYMBOL_NOT = 57,                       /* NOT  */
  YYSYMBOL_UNIQUE = 58,                    /* UNIQUE  */
  YYSYMBOL_NUMBER = 59,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 60,                     /* FLOAT  */
  YYSYMBOL_ID = 61,                        /* ID  */
  YYSYMBOL_PATH = 62,                      /* PATH  */
  YYSYMBOL_SSS = 63,                       /* SSS  */
  YYSYMBOL_STAR = 64,                      /* STAR  */
  YYSYMBOL_STRING_V = 65,                  /* STRING_V  */
  YYSYMBOL_DATE_STR = 66,                  /* DATE_STR  */
  YYSYMBOL_YYACCEPT = 67,                  /* $accept  */
  YYSYMBOL_commands = 68,                  /* commands  */
  YYSYMBOL_command = 69,                   /* command  */
  YYSYMBOL_exit = 70,                      /* exit  */
  YYSYMBOL_help = 71,                      /* help  */
  YYSYMBOL_sync = 72,                      /* sync  */
  YYSYMBOL_begin = 73,                     /* begin  */
  YYSYMBOL_commit = 74,                    /* commit  */
  YYSYMBOL_rollback = 75,                  /* rollback  */
  YYSYMBOL_drop_table = 76,                /* drop_table  */
  YYSYMBOL_show_tables = 77,               /* show_tables  */
  YYSYMBOL_show_index = 78,                /* show_index  */
  YYSYMBOL_desc_table = 79,                /* desc_table  */
  YYSYMBOL_create_index = 80,              /* create_index  */
  YYSYMBOL_unique_option = 81,             /* unique_option  */
  YYSYMBOL_index_attr_list = 82,           /* index_attr_list  */
  YYSYMBOL_drop_index = 83,                /* drop_index  */
  YYSYMBOL_create_table = 84,              /* create_table  */
  YYSYMBOL_attr_def_list = 85,             /* attr_def_list  */
  YYSYMBOL_attr_def = 86,                  /* attr_def  */
  YYSYMBOL_number = 87,                    /* number  */
  YYSYMBOL_type = 88,                      /* type  */
  YYSYMBOL_ID_get = 89,                    /* ID_get  */
  YYSYMBOL_insert = 90,                    /* insert  */
  YYSYMBOL_tuple = 91,                     /* tuple  */
  YYSYMBOL_tuple_list = 92,                /* tuple_list  */
  YYSYMBOL_value_list = 93,                /* value_list  */
  YYSYMBOL_value = 94,                     /* value  */
  YYSYMBOL_delete = 95,                    /* delete  */
  YYSYMBOL_update = 96,                    /* update  */
  YYSYMBOL_select = 97,                    /* select  */
  YYSYMBOL_select_query = 98,              /* select_query  */
  YYSYMBOL_select_attr = 99,               /* select_attr  */
  YYSYMBOL_aggregate_attr = 100,           /* aggregate_attr  */
  YYSYMBOL_aggregation_field_attr = 101,   /* aggregation_field_attr  */
  YYSYMBOL_aggregate_op = 102,             /* aggregate_op  */
  YYSYMBOL_aggregate_attr_list = 103,      /* aggregate_attr_list  */
  YYSYMBOL_attr_list = 104,                /* attr_list  */
  YYSYMBOL_rel_list = 105,                 /* rel_list  */
  YYSYMBOL_on_list = 106,                  /* on_list  */
  YYSYMBOL_where = 107,                    /* where  */
  YYSYMBOL_condition_list = 108,           /* condition_list  */
  YYSYMBOL_condition = 109,                /* condition  */
  YYSYMBOL_sub_query = 110,                /* sub_query  */
  YYSYMBOL_N = 111,                        /* N  */
  YYSYMBOL_comOp = 112,                    /* comOp  */
  YYSYMBOL_load_data = 113                 /* load_data  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYLAST   236

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  67
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  122
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  244

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   321


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
      65,    66
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   169,   169,   171,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   196,   201,   206,   212,   218,   224,   230,   236,
     242,   249,   256,   262,   264,   276,   278,   283,   290,   299,
     301,   305,   316,   327,   338,   351,   354,   355,   356,   357,
     358,   361,   371,   389,   394,   396,   399,   401,   407,   412,
     417,   423,   442,   452,   463,   466,   486,   491,   496,   501,
     509,   524,   533,   535,   543,   553,   554,   555,   556,   557,
     560,   562,   566,   571,   576,   581,   588,   590,   597,   604,
     610,   615,   617,   620,   625,   627,   631,   633,   637,   639,
     644,   666,   687,   708,   731,   753,   775,   795,   804,   813,
     821,   828,   838,   846,   864,   865,   866,   867,   868,   869,
     870,   871,   875
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
  "GE", "NE", "NULLABLE", "COUNT", "AVG", "MAX", "MIN", "SUM", "INNER",
  "JOIN", "IN", "EXISTS", "LIKE", "NOT", "UNIQUE", "NUMBER", "FLOAT", "ID",
  "PATH", "SSS", "STAR", "STRING_V", "DATE_STR", "$accept", "commands",
  "command", "exit", "help", "sync", "begin", "commit", "rollback",
  "drop_table", "show_tables", "show_index", "desc_table", "create_index",
  "unique_option", "index_attr_list", "drop_index", "create_table",
  "attr_def_list", "attr_def", "number", "type", "ID_get", "insert",
  "tuple", "tuple_list", "value_list", "value", "delete", "update",
  "select", "select_query", "select_attr", "aggregate_attr",
  "aggregation_field_attr", "aggregate_op", "aggregate_attr_list",
  "attr_list", "rel_list", "on_list", "where", "condition_list",
  "condition", "sub_query", "N", "comOp", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-194)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -194,    79,  -194,    -2,    97,    81,   -45,    40,    51,    25,
      38,    10,    73,    83,    84,    92,    93,    66,  -194,  -194,
    -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,
    -194,  -194,  -194,  -194,  -194,  -194,   115,  -194,    47,  -194,
     125,    74,    77,  -194,  -194,  -194,  -194,  -194,    -5,   121,
     108,   123,   127,   141,   149,   122,  -194,   100,   106,   137,
    -194,  -194,  -194,  -194,  -194,   119,  -194,   158,   114,   174,
     175,   -29,   -25,  -194,  -194,   118,    99,  -194,     4,  -194,
    -194,   120,   151,   147,   124,   126,   129,   148,  -194,  -194,
      -4,   121,   121,   121,    -7,     8,   123,   123,   121,   121,
     166,   183,   171,    96,   185,   152,   161,  -194,   176,    35,
     132,    17,  -194,  -194,  -194,  -194,   134,   143,   147,    21,
    -194,  -194,  -194,  -194,  -194,  -194,  -194,   110,   179,   182,
     144,  -194,  -194,    80,  -194,  -194,    70,   167,  -194,   110,
     194,   129,   186,  -194,  -194,  -194,  -194,  -194,    -6,   188,
     121,   121,    -7,   145,  -194,   123,   123,   184,   171,   202,
    -194,  -194,   182,   146,  -194,  -194,  -194,  -194,  -194,  -194,
     182,  -194,    63,   -32,   153,   105,    96,  -194,   147,   150,
     176,   205,   154,  -194,   155,  -194,  -194,  -194,   178,  -194,
    -194,   110,   193,   179,  -194,   203,  -194,    70,  -194,   182,
    -194,  -194,  -194,   189,  -194,   167,   212,   214,  -194,  -194,
    -194,   204,   201,    96,    -7,   184,  -194,  -194,   206,    14,
    -194,   159,  -194,  -194,  -194,   180,   163,   208,   167,  -194,
    -194,  -194,   198,  -194,  -194,  -194,  -194,   201,   219,  -194,
     168,  -194,  -194,  -194
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,    33,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    21,
      20,    15,    16,    17,    18,     9,    10,    11,    12,    13,
      14,     8,     5,     7,     6,     4,     0,    19,     0,    34,
       0,     0,     0,    75,    76,    77,    78,    79,    86,    86,
       0,    80,     0,     0,     0,     0,    24,     0,     0,     0,
      25,    26,    27,    23,    22,     0,    64,     0,     0,     0,
       0,     0,     0,    67,    66,     0,     0,    70,    72,    31,
      29,     0,     0,    96,     0,     0,     0,     0,    28,    37,
      86,    86,    86,    86,    91,    80,    80,    80,    86,    86,
       0,     0,     0,     0,     0,     0,     0,    51,    39,     0,
       0,     0,    87,    90,    68,    69,     0,     0,    96,     0,
      83,    82,    81,    74,    73,    71,    30,     0,    54,     0,
       0,    58,    59,     0,    60,    61,     0,    98,    62,     0,
       0,     0,     0,    46,    47,    48,    49,    50,    43,     0,
      86,    86,    91,     0,    65,    80,    80,    56,     0,     0,
     113,   110,     0,     0,   114,   115,   116,   117,   118,   119,
       0,   120,     0,     0,     0,     0,     0,    97,    96,     0,
      39,     0,     0,    44,     0,    88,    89,    92,    94,    84,
      85,     0,     0,    54,    52,     0,   111,     0,   107,     0,
     121,   102,   100,   103,   101,    98,     0,     0,    40,    38,
      45,     0,    35,     0,    91,    56,    53,    55,     0,     0,
     108,     0,    99,    63,   122,    41,     0,     0,    98,    93,
      57,   112,     0,   104,   109,   105,    42,    35,     0,    95,
       0,    36,    32,   106
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,  -194,
    -194,  -194,  -194,  -194,  -194,    -9,  -194,  -194,    50,    90,
    -194,  -194,  -194,  -194,    75,    39,    19,  -122,  -194,  -194,
    -194,    41,  -194,   -38,  -194,  -194,   -89,   -49,  -151,  -194,
    -116,  -193,  -167,  -147,  -194,  -133,  -194
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    40,   227,    30,    31,   142,   108,
     211,   148,   109,    32,   128,   159,   192,   136,    33,    34,
      35,    36,    50,    51,   100,    52,    77,    73,   118,   214,
     104,   177,   137,   161,   195,   173,    37
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      74,   187,   154,   175,    38,   157,   120,   121,   122,   205,
     182,   116,   222,    71,    71,   196,    53,   178,    43,    44,
      45,    46,    47,   198,    72,   111,    76,   131,   132,   201,
     160,   134,    90,    91,   135,   239,    92,   119,    97,    93,
     183,   112,   113,   114,   115,   117,   228,    54,    55,   123,
     124,   202,   220,   204,    56,    57,    39,   143,   144,   145,
     146,   147,   206,   229,   219,    98,   189,   190,    99,   215,
      58,    59,   234,   131,   132,   232,    60,   134,   150,     2,
     135,   151,   155,     3,     4,   156,    61,    62,     5,     6,
       7,     8,     9,    10,    11,    63,    64,   233,    12,    13,
      14,   185,   186,    41,    65,    42,    15,    16,    67,   163,
     164,   165,   166,   167,   168,   169,    17,   199,    66,   200,
     164,   165,   166,   167,   168,   169,   171,   174,    43,    44,
      45,    46,    47,    68,   170,    69,   171,   172,    70,    71,
      75,    76,    48,    78,    79,    49,    43,    44,    45,    46,
      47,   129,    80,   130,    81,   131,   132,   133,    85,   134,
      95,    82,   135,    96,   131,   132,   203,    83,   134,   131,
     132,   135,    84,   134,    86,    87,   135,    88,    89,    94,
     103,   101,   102,   125,   110,   105,   126,   127,   138,   106,
     107,   140,   139,   149,   141,   152,   153,   158,   160,   162,
     179,   176,   191,   181,   184,   194,   188,   197,   209,   200,
     216,   207,     5,   210,   213,   223,   212,   224,   221,   226,
     235,   225,   242,   231,   237,   238,   236,   240,   241,   243,
     208,   180,   217,   193,   230,     0,   218
};

static const yytype_int16 yycheck[] =
{
      49,   152,   118,   136,     6,   127,    95,    96,    97,   176,
      16,    18,   205,    18,    18,   162,    61,   139,    47,    48,
      49,    50,    51,   170,    29,    29,    18,    59,    60,    61,
      16,    63,    61,    71,    66,   228,    61,    29,    76,    64,
      46,    90,    91,    92,    93,    52,   213,     7,     8,    98,
      99,   173,   199,   175,     3,    30,    58,    22,    23,    24,
      25,    26,   178,   214,   197,    61,   155,   156,    64,   191,
      32,    61,   219,    59,    60,    61,     3,    63,    61,     0,
      66,    64,    61,     4,     5,    64,     3,     3,     9,    10,
      11,    12,    13,    14,    15,     3,     3,   219,    19,    20,
      21,   150,   151,     6,    38,     8,    27,    28,    61,    29,
      40,    41,    42,    43,    44,    45,    37,    54,     3,    56,
      40,    41,    42,    43,    44,    45,    56,    57,    47,    48,
      49,    50,    51,     8,    54,    61,    56,    57,    61,    18,
      32,    18,    61,    16,     3,    64,    47,    48,    49,    50,
      51,    55,     3,    57,    32,    59,    60,    61,    39,    63,
      61,    61,    66,    64,    59,    60,    61,    61,    63,    59,
      60,    66,    35,    63,    16,    61,    66,     3,     3,    61,
      33,    61,    31,    17,    36,    61,     3,    16,     3,    63,
      61,    30,    40,    61,    18,    61,    53,    18,    16,    55,
       6,    34,    18,    17,    16,     3,    61,    61,     3,    56,
      17,    61,     9,    59,    36,     3,    61,     3,    29,    18,
      61,    17,     3,    17,    61,    17,    46,    29,   237,    61,
     180,   141,   193,   158,   215,    -1,   195
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    68,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    19,    20,    21,    27,    28,    37,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      83,    84,    90,    95,    96,    97,    98,   113,     6,    58,
      81,     6,     8,    47,    48,    49,    50,    51,    61,    64,
      99,   100,   102,    61,     7,     8,     3,    30,    32,    61,
       3,     3,     3,     3,     3,    38,     3,    61,     8,    61,
      61,    18,    29,   104,   104,    32,    18,   103,    16,     3,
       3,    32,    61,    61,    35,    39,    16,    61,     3,     3,
      61,   100,    61,    64,    61,    61,    64,   100,    61,    64,
     101,    61,    31,    33,   107,    61,    63,    61,    86,    89,
      36,    29,   104,   104,   104,   104,    18,    52,   105,    29,
     103,   103,   103,   104,   104,    17,     3,    16,    91,    55,
      57,    59,    60,    61,    63,    66,    94,   109,     3,    40,
      30,    18,    85,    22,    23,    24,    25,    26,    88,    61,
      61,    64,    61,    53,   107,    61,    64,    94,    18,    92,
      16,   110,    55,    29,    40,    41,    42,    43,    44,    45,
      54,    56,    57,   112,    57,   112,    34,   108,    94,     6,
      86,    17,    16,    46,    16,   104,   104,   105,    61,   103,
     103,    18,    93,    91,     3,   111,   110,    61,   110,    54,
      56,    61,    94,    61,    94,   109,   107,    61,    85,     3,
      59,    87,    61,    36,   106,    94,    17,    92,    98,   112,
     110,    29,   108,     3,     3,    17,    18,    82,   109,   105,
      93,    17,    61,    94,   110,    61,    46,    61,    17,   108,
      29,    82,     3,    61
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    67,    68,    68,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    81,    82,    82,    83,    84,    85,
      85,    86,    86,    86,    86,    87,    88,    88,    88,    88,
      88,    89,    90,    91,    92,    92,    93,    93,    94,    94,
      94,    94,    95,    96,    97,    98,    99,    99,    99,    99,
      99,   100,   101,   101,   101,   102,   102,   102,   102,   102,
     103,   103,   103,   103,   103,   103,   104,   104,   104,   104,
     104,   105,   105,   105,   106,   106,   107,   107,   108,   108,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   110,   111,   112,   112,   112,   112,   112,   112,
     112,   112,   113
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     4,     3,
       5,     3,    11,     0,     1,     0,     3,     4,     8,     0,
       3,     5,     6,     2,     3,     1,     1,     1,     1,     1,
       1,     1,     7,     4,     0,     3,     0,     3,     1,     1,
       1,     1,     5,     8,     2,     6,     2,     2,     4,     4,
       2,     4,     0,     2,     2,     1,     1,     1,     1,     1,
       0,     3,     3,     3,     5,     5,     0,     3,     5,     5,
       3,     0,     3,     5,     0,     3,     0,     3,     0,     3,
       3,     3,     3,     3,     5,     5,     7,     3,     4,     5,
       2,     3,     4,     0,     1,     1,     1,     1,     1,     1,
       1,     2,     8
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
#line 196 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1426 "yacc_sql.tab.c"
    break;

  case 23: /* help: HELP SEMICOLON  */
#line 201 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1434 "yacc_sql.tab.c"
    break;

  case 24: /* sync: SYNC SEMICOLON  */
#line 206 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1442 "yacc_sql.tab.c"
    break;

  case 25: /* begin: TRX_BEGIN SEMICOLON  */
#line 212 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1450 "yacc_sql.tab.c"
    break;

  case 26: /* commit: TRX_COMMIT SEMICOLON  */
#line 218 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1458 "yacc_sql.tab.c"
    break;

  case 27: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 224 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1466 "yacc_sql.tab.c"
    break;

  case 28: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 230 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1475 "yacc_sql.tab.c"
    break;

  case 29: /* show_tables: SHOW TABLES SEMICOLON  */
#line 236 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1483 "yacc_sql.tab.c"
    break;

  case 30: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 242 "yacc_sql.y"
                                     {
		CONTEXT->ssql->flag = SCF_SHOW_INDEX;
		show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
	}
#line 1492 "yacc_sql.tab.c"
    break;

  case 31: /* desc_table: DESC ID SEMICOLON  */
#line 249 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1501 "yacc_sql.tab.c"
    break;

  case 32: /* create_index: CREATE unique_option INDEX ID ON ID LBRACE ID index_attr_list RBRACE SEMICOLON  */
#line 257 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), (yyvsp[-3].string), CONTEXT->unique);
		}
#line 1510 "yacc_sql.tab.c"
    break;

  case 34: /* unique_option: UNIQUE  */
#line 264 "yacc_sql.y"
                 {
		CONTEXT->unique = 1;
	}
#line 1518 "yacc_sql.tab.c"
    break;

  case 36: /* index_attr_list: COMMA ID index_attr_list  */
#line 278 "yacc_sql.y"
                                   {
		create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[-1].string));
	}
#line 1526 "yacc_sql.tab.c"
    break;

  case 37: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 284 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1535 "yacc_sql.tab.c"
    break;

  case 38: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 291 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1547 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 301 "yacc_sql.y"
                                   {    }
#line 1553 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 306 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-3].number), (yyvsp[-1].number), 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
#line 1568 "yacc_sql.tab.c"
    break;

  case 42: /* attr_def: ID_get type LBRACE number RBRACE NULLABLE  */
#line 317 "yacc_sql.y"
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
#line 1583 "yacc_sql.tab.c"
    break;

  case 43: /* attr_def: ID_get type  */
#line 328 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[0].number), 4, 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
#line 1598 "yacc_sql.tab.c"
    break;

  case 44: /* attr_def: ID_get type NULLABLE  */
#line 339 "yacc_sql.y"
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
#line 1613 "yacc_sql.tab.c"
    break;

  case 45: /* number: NUMBER  */
#line 351 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1619 "yacc_sql.tab.c"
    break;

  case 46: /* type: INT_T  */
#line 354 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1625 "yacc_sql.tab.c"
    break;

  case 47: /* type: STRING_T  */
#line 355 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1631 "yacc_sql.tab.c"
    break;

  case 48: /* type: TEXT_T  */
#line 356 "yacc_sql.y"
                    {(yyval.number)=TEXTS; }
#line 1637 "yacc_sql.tab.c"
    break;

  case 49: /* type: FLOAT_T  */
#line 357 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1643 "yacc_sql.tab.c"
    break;

  case 50: /* type: DATE_T  */
#line 358 "yacc_sql.y"
                    {(yyval.number)=DATES;}
#line 1649 "yacc_sql.tab.c"
    break;

  case 51: /* ID_get: ID  */
#line 362 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1658 "yacc_sql.tab.c"
    break;

  case 52: /* insert: INSERT INTO ID VALUES tuple tuple_list SEMICOLON  */
#line 372 "yacc_sql.y"
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
#line 1678 "yacc_sql.tab.c"
    break;

  case 53: /* tuple: LBRACE value value_list RBRACE  */
#line 389 "yacc_sql.y"
                                       {
		CONTEXT->tuple_num++;
		printf("yacc: tuple num %d\n", CONTEXT->tuple_num);
	}
#line 1687 "yacc_sql.tab.c"
    break;

  case 55: /* tuple_list: COMMA tuple tuple_list  */
#line 396 "yacc_sql.y"
                                 {
	}
#line 1694 "yacc_sql.tab.c"
    break;

  case 57: /* value_list: COMMA value value_list  */
#line 401 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;

	  }
#line 1703 "yacc_sql.tab.c"
    break;

  case 58: /* value: NUMBER  */
#line 407 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
  		value_init_integer(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], (yyvsp[0].number));
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
#line 1713 "yacc_sql.tab.c"
    break;

  case 59: /* value: FLOAT  */
#line 412 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		value_init_float(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], (yyvsp[0].floats));
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
#line 1723 "yacc_sql.tab.c"
    break;

  case 60: /* value: SSS  */
#line 417 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		value_init_string(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], (yyvsp[0].string));
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
#line 1734 "yacc_sql.tab.c"
    break;

  case 61: /* value: DATE_STR  */
#line 423 "yacc_sql.y"
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
#line 1755 "yacc_sql.tab.c"
    break;

  case 62: /* delete: DELETE FROM ID where SEMICOLON  */
#line 443 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1767 "yacc_sql.tab.c"
    break;

  case 63: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 453 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1779 "yacc_sql.tab.c"
    break;

  case 65: /* select_query: SELECT select_attr FROM ID rel_list where  */
#line 467 "yacc_sql.y"
                {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string));

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
#line 1800 "yacc_sql.tab.c"
    break;

  case 66: /* select_attr: STAR attr_list  */
#line 486 "yacc_sql.y"
                   {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1810 "yacc_sql.tab.c"
    break;

  case 67: /* select_attr: ID attr_list  */
#line 491 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1820 "yacc_sql.tab.c"
    break;

  case 68: /* select_attr: ID DOT ID attr_list  */
#line 496 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1830 "yacc_sql.tab.c"
    break;

  case 69: /* select_attr: ID DOT STAR attr_list  */
#line 501 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			// CONTEXT->aggregation_op = NO_AGGREGATE_OP;
			// selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_op);
			// selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, AggregationOp::NO_AGGREGATE_OP);
		}
#line 1843 "yacc_sql.tab.c"
    break;

  case 70: /* select_attr: aggregate_attr aggregate_attr_list  */
#line 509 "yacc_sql.y"
                                             {
			
	}
#line 1851 "yacc_sql.tab.c"
    break;

  case 71: /* aggregate_attr: aggregate_op LBRACE aggregation_field_attr RBRACE  */
#line 524 "yacc_sql.y"
                                                          {
		// RelAttr attr;
		// relation_attr_init(&attr, NULL, $3);
		// printf("aggregation: get a attr %s\n", $3);
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		// selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		// CONTEXT->aggregation_num++;	
	}
#line 1864 "yacc_sql.tab.c"
    break;

  case 73: /* aggregation_field_attr: STAR attr_list  */
#line 535 "yacc_sql.y"
                         {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		printf("aggregation: get a attr *\n");
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
#line 1877 "yacc_sql.tab.c"
    break;

  case 74: /* aggregation_field_attr: ID attr_list  */
#line 543 "yacc_sql.y"
                       {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		printf("aggregation: get a attr %s\n", (yyvsp[-1].string));
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
#line 1890 "yacc_sql.tab.c"
    break;

  case 75: /* aggregate_op: COUNT  */
#line 553 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = COUNT_OP; }
#line 1896 "yacc_sql.tab.c"
    break;

  case 76: /* aggregate_op: AVG  */
#line 554 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = AVG_OP; }
#line 1902 "yacc_sql.tab.c"
    break;

  case 77: /* aggregate_op: MAX  */
#line 555 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = MAX_OP; }
#line 1908 "yacc_sql.tab.c"
    break;

  case 78: /* aggregate_op: MIN  */
#line 556 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = MIN_OP; }
#line 1914 "yacc_sql.tab.c"
    break;

  case 79: /* aggregate_op: SUM  */
#line 557 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = SUM_OP; }
#line 1920 "yacc_sql.tab.c"
    break;

  case 81: /* aggregate_attr_list: COMMA aggregate_attr aggregate_attr_list  */
#line 562 "yacc_sql.y"
                                                  {

	}
#line 1928 "yacc_sql.tab.c"
    break;

  case 82: /* aggregate_attr_list: COMMA STAR aggregate_attr_list  */
#line 566 "yacc_sql.y"
                                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1938 "yacc_sql.tab.c"
    break;

  case 83: /* aggregate_attr_list: COMMA ID aggregate_attr_list  */
#line 571 "yacc_sql.y"
                                      {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1948 "yacc_sql.tab.c"
    break;

  case 84: /* aggregate_attr_list: COMMA ID DOT ID aggregate_attr_list  */
#line 576 "yacc_sql.y"
                                               {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1958 "yacc_sql.tab.c"
    break;

  case 85: /* aggregate_attr_list: COMMA ID DOT STAR aggregate_attr_list  */
#line 581 "yacc_sql.y"
                                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1968 "yacc_sql.tab.c"
    break;

  case 87: /* attr_list: COMMA ID attr_list  */
#line 590 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 1980 "yacc_sql.tab.c"
    break;

  case 88: /* attr_list: COMMA ID DOT ID attr_list  */
#line 597 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 1992 "yacc_sql.tab.c"
    break;

  case 89: /* attr_list: COMMA ID DOT STAR attr_list  */
#line 604 "yacc_sql.y"
                                      {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2002 "yacc_sql.tab.c"
    break;

  case 90: /* attr_list: COMMA aggregate_attr attr_list  */
#line 610 "yacc_sql.y"
                                         {

	}
#line 2010 "yacc_sql.tab.c"
    break;

  case 92: /* rel_list: COMMA ID rel_list  */
#line 617 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 2018 "yacc_sql.tab.c"
    break;

  case 93: /* rel_list: INNER JOIN ID on_list rel_list  */
#line 620 "yacc_sql.y"
                                         {
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string));
	}
#line 2026 "yacc_sql.tab.c"
    break;

  case 95: /* on_list: ON condition condition_list  */
#line 627 "yacc_sql.y"
                                      {

	}
#line 2034 "yacc_sql.tab.c"
    break;

  case 97: /* where: WHERE condition condition_list  */
#line 633 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2042 "yacc_sql.tab.c"
    break;

  case 99: /* condition_list: AND condition condition_list  */
#line 639 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2050 "yacc_sql.tab.c"
    break;

  case 100: /* condition: ID comOp value  */
#line 645 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			// condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			condition_init(&condition, Comparison, CONTEXT->comp, 1, &left_attr, NULL, 0, 0, NULL, right_value, NULL);
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
#line 2076 "yacc_sql.tab.c"
    break;

  case 101: /* condition: value comOp value  */
#line 667 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			// condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
			condition_init(&condition, Comparison, CONTEXT->comp, 0, NULL, left_value, 0, 0, NULL, right_value, NULL);
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
#line 2101 "yacc_sql.tab.c"
    break;

  case 102: /* condition: ID comOp ID  */
#line 688 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			// condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			condition_init(&condition, Comparison, CONTEXT->comp, 1, &left_attr, NULL, 1, 0, &right_attr, NULL, NULL);
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
#line 2126 "yacc_sql.tab.c"
    break;

  case 103: /* condition: value comOp ID  */
#line 709 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			// condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			condition_init(&condition, Comparison, CONTEXT->comp, 0, NULL, left_value, 1, 0, &right_attr, NULL, NULL);
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
#line 2153 "yacc_sql.tab.c"
    break;

  case 104: /* condition: ID DOT ID comOp value  */
#line 732 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			// condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			condition_init(&condition, Comparison, CONTEXT->comp, 1, &left_attr, NULL, 0, 0, NULL, right_value, NULL);
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
#line 2179 "yacc_sql.tab.c"
    break;

  case 105: /* condition: value comOp ID DOT ID  */
#line 754 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			// condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			condition_init(&condition, Comparison, CONTEXT->comp, 0, NULL, left_value, 1, 0, &right_attr, NULL, NULL);
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
#line 2205 "yacc_sql.tab.c"
    break;

  case 106: /* condition: ID DOT ID comOp ID DOT ID  */
#line 776 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			// condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			condition_init(&condition, Comparison, CONTEXT->comp, 1, &left_attr, NULL, 1, 0, &right_attr, NULL, NULL);
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
#line 2229 "yacc_sql.tab.c"
    break;

  case 107: /* condition: ID IN sub_query  */
#line 795 "yacc_sql.y"
                          {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

		Condition condition;
		condition_init(&condition, Contain, CONTEXT->comp, 1, &left_attr, NULL, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		
	}
#line 2243 "yacc_sql.tab.c"
    break;

  case 108: /* condition: ID NOT IN sub_query  */
#line 804 "yacc_sql.y"
                              {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-3].string));

		Condition condition;
		condition_init(&condition, NotContain, CONTEXT->comp, 1, &left_attr, NULL, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 2257 "yacc_sql.tab.c"
    break;

  case 109: /* condition: ID DOT ID comOp sub_query  */
#line 813 "yacc_sql.y"
                                    {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));

		Condition condition;
		condition_init(&condition, Comparison, CONTEXT->comp, 1, &left_attr, NULL, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2270 "yacc_sql.tab.c"
    break;

  case 110: /* condition: EXISTS sub_query  */
#line 821 "yacc_sql.y"
                           {

		Condition condition;
		condition_init(&condition, Exists, CONTEXT->comp, 0, NULL, NULL, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 2282 "yacc_sql.tab.c"
    break;

  case 111: /* condition: NOT EXISTS sub_query  */
#line 828 "yacc_sql.y"
                               {

		Condition condition;
		condition_init(&condition, NotExists, CONTEXT->comp, 0, NULL, NULL, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 2294 "yacc_sql.tab.c"
    break;

  case 112: /* sub_query: LBRACE N select_query RBRACE  */
#line 838 "yacc_sql.y"
                                     {
		// TODO support complex sub query
		ParserContext *old_context = CONTEXT->last_context;
		old_context->sub_query = CONTEXT->ssql;
		*CONTEXT = *old_context;
		printf("sub query addr %p\n", old_context->sub_query);
		printf("swap back old context\n");
	}
#line 2307 "yacc_sql.tab.c"
    break;

  case 113: /* N: %empty  */
#line 846 "yacc_sql.y"
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
#line 2327 "yacc_sql.tab.c"
    break;

  case 114: /* comOp: EQ  */
#line 864 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2333 "yacc_sql.tab.c"
    break;

  case 115: /* comOp: LT  */
#line 865 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2339 "yacc_sql.tab.c"
    break;

  case 116: /* comOp: GT  */
#line 866 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2345 "yacc_sql.tab.c"
    break;

  case 117: /* comOp: LE  */
#line 867 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2351 "yacc_sql.tab.c"
    break;

  case 118: /* comOp: GE  */
#line 868 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2357 "yacc_sql.tab.c"
    break;

  case 119: /* comOp: NE  */
#line 869 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2363 "yacc_sql.tab.c"
    break;

  case 120: /* comOp: LIKE  */
#line 870 "yacc_sql.y"
               { CONTEXT->comp = LIKE_OP; }
#line 2369 "yacc_sql.tab.c"
    break;

  case 121: /* comOp: NOT LIKE  */
#line 871 "yacc_sql.y"
                   { CONTEXT->comp = NOT_LIKE_OP; }
#line 2375 "yacc_sql.tab.c"
    break;

  case 122: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 876 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2384 "yacc_sql.tab.c"
    break;


#line 2388 "yacc_sql.tab.c"

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

#line 881 "yacc_sql.y"

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
