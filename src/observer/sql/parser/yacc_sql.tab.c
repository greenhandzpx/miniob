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


#line 144 "yacc_sql.tab.c"

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
  YYSYMBOL_NOT = 55,                       /* NOT  */
  YYSYMBOL_EXISTS = 56,                    /* EXISTS  */
  YYSYMBOL_NUMBER = 57,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 58,                     /* FLOAT  */
  YYSYMBOL_ID = 59,                        /* ID  */
  YYSYMBOL_PATH = 60,                      /* PATH  */
  YYSYMBOL_SSS = 61,                       /* SSS  */
  YYSYMBOL_STAR = 62,                      /* STAR  */
  YYSYMBOL_STRING_V = 63,                  /* STRING_V  */
  YYSYMBOL_DATE_STR = 64,                  /* DATE_STR  */
  YYSYMBOL_YYACCEPT = 65,                  /* $accept  */
  YYSYMBOL_commands = 66,                  /* commands  */
  YYSYMBOL_command = 67,                   /* command  */
  YYSYMBOL_exit = 68,                      /* exit  */
  YYSYMBOL_help = 69,                      /* help  */
  YYSYMBOL_sync = 70,                      /* sync  */
  YYSYMBOL_begin = 71,                     /* begin  */
  YYSYMBOL_commit = 72,                    /* commit  */
  YYSYMBOL_rollback = 73,                  /* rollback  */
  YYSYMBOL_drop_table = 74,                /* drop_table  */
  YYSYMBOL_show_tables = 75,               /* show_tables  */
  YYSYMBOL_show_index = 76,                /* show_index  */
  YYSYMBOL_desc_table = 77,                /* desc_table  */
  YYSYMBOL_create_index = 78,              /* create_index  */
  YYSYMBOL_index_attr_list = 79,           /* index_attr_list  */
  YYSYMBOL_drop_index = 80,                /* drop_index  */
  YYSYMBOL_create_table = 81,              /* create_table  */
  YYSYMBOL_attr_def_list = 82,             /* attr_def_list  */
  YYSYMBOL_attr_def = 83,                  /* attr_def  */
  YYSYMBOL_number = 84,                    /* number  */
  YYSYMBOL_type = 85,                      /* type  */
  YYSYMBOL_ID_get = 86,                    /* ID_get  */
  YYSYMBOL_insert = 87,                    /* insert  */
  YYSYMBOL_tuple = 88,                     /* tuple  */
  YYSYMBOL_tuple_list = 89,                /* tuple_list  */
  YYSYMBOL_value_list = 90,                /* value_list  */
  YYSYMBOL_value = 91,                     /* value  */
  YYSYMBOL_delete = 92,                    /* delete  */
  YYSYMBOL_update = 93,                    /* update  */
  YYSYMBOL_select = 94,                    /* select  */
  YYSYMBOL_select_query = 95,              /* select_query  */
  YYSYMBOL_select_attr = 96,               /* select_attr  */
  YYSYMBOL_aggregate_attr = 97,            /* aggregate_attr  */
  YYSYMBOL_aggregation_field_attr = 98,    /* aggregation_field_attr  */
  YYSYMBOL_aggregate_op = 99,              /* aggregate_op  */
  YYSYMBOL_aggregate_attr_list = 100,      /* aggregate_attr_list  */
  YYSYMBOL_attr_list = 101,                /* attr_list  */
  YYSYMBOL_rel_list = 102,                 /* rel_list  */
  YYSYMBOL_on_list = 103,                  /* on_list  */
  YYSYMBOL_where = 104,                    /* where  */
  YYSYMBOL_condition_list = 105,           /* condition_list  */
  YYSYMBOL_condition = 106,                /* condition  */
  YYSYMBOL_sub_query = 107,                /* sub_query  */
  YYSYMBOL_N = 108,                        /* N  */
  YYSYMBOL_comOp = 109,                    /* comOp  */
  YYSYMBOL_load_data = 110                 /* load_data  */
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
#define YYLAST   229

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  65
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  46
/* YYNRULES -- Number of rules.  */
#define YYNRULES  119
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  239

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   319


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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   165,   165,   167,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   192,   197,   202,   208,   214,   220,   226,   232,
     238,   245,   252,   258,   260,   265,   272,   281,   283,   287,
     298,   309,   320,   333,   336,   337,   338,   339,   340,   343,
     353,   371,   376,   378,   381,   383,   389,   394,   399,   405,
     424,   434,   445,   448,   468,   473,   478,   483,   491,   506,
     515,   517,   525,   535,   536,   537,   538,   539,   542,   544,
     548,   553,   558,   563,   570,   572,   579,   586,   592,   597,
     599,   602,   607,   609,   613,   615,   619,   621,   626,   648,
     669,   690,   713,   735,   757,   777,   786,   795,   803,   810,
     820,   828,   846,   847,   848,   849,   850,   851,   852,   856
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
  "JOIN", "IN", "NOT", "EXISTS", "NUMBER", "FLOAT", "ID", "PATH", "SSS",
  "STAR", "STRING_V", "DATE_STR", "$accept", "commands", "command", "exit",
  "help", "sync", "begin", "commit", "rollback", "drop_table",
  "show_tables", "show_index", "desc_table", "create_index",
  "index_attr_list", "drop_index", "create_table", "attr_def_list",
  "attr_def", "number", "type", "ID_get", "insert", "tuple", "tuple_list",
  "value_list", "value", "delete", "update", "select", "select_query",
  "select_attr", "aggregate_attr", "aggregation_field_attr",
  "aggregate_op", "aggregate_attr_list", "attr_list", "rel_list",
  "on_list", "where", "condition_list", "condition", "sub_query", "N",
  "comOp", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-186)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -186,    67,  -186,    77,    84,    49,   -44,    62,    31,    43,
      42,    16,    81,    86,    90,   100,   102,    68,  -186,  -186,
    -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,
    -186,  -186,  -186,  -186,  -186,  -186,   104,  -186,    50,    51,
      63,    64,  -186,  -186,  -186,  -186,  -186,     0,   107,    94,
     110,   119,   134,   135,   111,  -186,    87,    92,   123,  -186,
    -186,  -186,  -186,  -186,   106,  -186,   140,   136,   156,   170,
      70,   -45,  -186,  -186,   115,    65,  -186,   -27,  -186,  -186,
     116,   146,   143,   120,   117,   122,   124,  -186,  -186,     1,
     107,   107,   107,     2,     4,   110,   110,   107,   107,   163,
     179,   168,    75,   182,   147,   158,  -186,   171,   145,   174,
      -3,  -186,  -186,  -186,  -186,   127,   138,   143,    -2,  -186,
    -186,  -186,  -186,  -186,  -186,  -186,    96,   175,   139,   176,
    -186,  -186,   -17,  -186,  -186,   121,   160,  -186,    96,   190,
     122,   180,  -186,  -186,  -186,  -186,  -186,    -7,   141,   107,
     107,     2,   142,  -186,   110,   110,   181,   168,   195,   176,
    -186,  -186,   144,  -186,  -186,  -186,  -186,  -186,  -186,   176,
     148,    83,    91,    75,  -186,   143,   149,   171,   201,   150,
    -186,   187,  -186,  -186,  -186,   173,  -186,  -186,    96,   189,
     175,  -186,  -186,   202,   121,  -186,   176,  -186,  -186,   183,
    -186,   160,   207,   210,  -186,  -186,  -186,   197,   157,   198,
      75,     2,   181,  -186,  -186,   200,    -6,  -186,   159,  -186,
    -186,  -186,   177,   187,   216,   160,  -186,  -186,  -186,   191,
    -186,  -186,  -186,  -186,  -186,  -186,  -186,   162,  -186
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    21,
      20,    15,    16,    17,    18,     9,    10,    11,    12,    13,
      14,     8,     5,     7,     6,     4,     0,    19,     0,     0,
       0,     0,    73,    74,    75,    76,    77,    84,    84,     0,
      78,     0,     0,     0,     0,    24,     0,     0,     0,    25,
      26,    27,    23,    22,     0,    62,     0,     0,     0,     0,
       0,     0,    65,    64,     0,     0,    68,    70,    31,    29,
       0,     0,    94,     0,     0,     0,     0,    28,    35,    84,
      84,    84,    84,    89,    78,    78,    78,    84,    84,     0,
       0,     0,     0,     0,     0,     0,    49,    37,     0,     0,
       0,    85,    88,    66,    67,     0,     0,    94,     0,    81,
      80,    79,    72,    71,    69,    30,     0,    52,     0,     0,
      56,    57,   118,    58,    59,   118,    96,    60,     0,     0,
       0,     0,    44,    45,    46,    47,    48,    41,     0,    84,
      84,    89,     0,    63,    78,    78,    54,     0,     0,     0,
     111,   108,     0,   112,   113,   114,   115,   116,   117,     0,
       0,     0,     0,     0,    95,    94,     0,    37,     0,     0,
      42,    33,    86,    87,    90,    92,    82,    83,     0,     0,
      52,    50,   109,     0,   118,   105,     0,   100,    98,   101,
      99,    96,     0,     0,    38,    36,    43,     0,     0,     0,
       0,    89,    54,    51,    53,     0,     0,   106,     0,    97,
      61,   119,    39,    33,     0,    96,    91,    55,   110,     0,
     102,   107,   103,    40,    34,    32,    93,     0,   104
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,
    -186,  -186,  -186,  -186,    -1,  -186,  -186,    47,    85,  -186,
    -186,  -186,  -186,    69,    37,    17,  -125,  -186,  -186,  -186,
      35,  -186,   -39,  -186,  -186,   -90,   -48,  -149,  -186,  -114,
    -185,  -165,  -148,  -186,  -128,  -186
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,   209,    30,    31,   141,   107,   207,
     147,   108,    32,   127,   158,   189,   135,    33,    34,    35,
      36,    49,    50,    99,    51,    76,    72,   117,   211,   103,
     174,   136,   161,   193,   171,    37
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      73,   156,   184,   153,   119,   120,   121,   172,   201,   179,
     160,   192,   162,   175,    91,    52,   219,    92,    70,    70,
     115,   195,    75,   163,   164,   165,   166,   167,   168,    71,
     110,    90,    97,   118,    55,    98,    96,   169,   170,   180,
     236,   111,   112,   113,   114,   225,   198,   200,   217,   122,
     123,   130,   131,   229,   116,   133,   149,   154,   134,   150,
     155,   202,   226,   212,   186,   187,   216,     2,   231,    53,
      54,     3,     4,    56,    57,    58,     5,     6,     7,     8,
       9,    10,    11,    38,    59,    39,    12,    13,    14,    60,
      40,   230,    41,    61,    15,    16,    42,    43,    44,    45,
      46,   182,   183,    62,    17,    63,    64,    65,    47,    66,
      67,    48,    42,    43,    44,    45,    46,    42,    43,    44,
      45,    46,    68,    69,    94,    70,    74,    95,    75,    89,
     128,   129,   130,   131,   132,    77,   133,    78,    79,   134,
     130,   131,   197,    80,   133,    84,    81,   134,   130,   131,
     199,    82,   133,   130,   131,   134,    85,   133,    83,    87,
     134,   163,   164,   165,   166,   167,   168,   142,   143,   144,
     145,   146,    86,    88,    93,   100,   102,   101,   105,   104,
     124,   106,   125,   109,   126,   137,   151,   138,   139,   140,
     148,   152,   160,   157,   173,   159,   176,   178,   191,   188,
     181,   185,   196,   194,   205,   208,   213,   206,   203,   210,
     220,     5,   218,   221,   222,   224,   223,   228,   232,   235,
     237,   238,   234,   233,   204,   177,   190,   214,   215,   227
};

static const yytype_uint8 yycheck[] =
{
      48,   126,   151,   117,    94,    95,    96,   135,   173,    16,
      16,   159,    29,   138,    59,    59,   201,    62,    18,    18,
      18,   169,    18,    40,    41,    42,    43,    44,    45,    29,
      29,    70,    59,    29,     3,    62,    75,    54,    55,    46,
     225,    89,    90,    91,    92,   210,   171,   172,   196,    97,
      98,    57,    58,    59,    52,    61,    59,    59,    64,    62,
      62,   175,   211,   188,   154,   155,   194,     0,   216,     7,
       8,     4,     5,    30,    32,    59,     9,    10,    11,    12,
      13,    14,    15,     6,     3,     8,    19,    20,    21,     3,
       6,   216,     8,     3,    27,    28,    47,    48,    49,    50,
      51,   149,   150,     3,    37,     3,    38,     3,    59,    59,
      59,    62,    47,    48,    49,    50,    51,    47,    48,    49,
      50,    51,    59,    59,    59,    18,    32,    62,    18,    59,
      55,    56,    57,    58,    59,    16,    61,     3,     3,    64,
      57,    58,    59,    32,    61,    39,    59,    64,    57,    58,
      59,    59,    61,    57,    58,    64,    16,    61,    35,     3,
      64,    40,    41,    42,    43,    44,    45,    22,    23,    24,
      25,    26,    36,     3,    59,    59,    33,    31,    61,    59,
      17,    59,     3,    59,    16,     3,    59,    40,    30,    18,
      16,    53,    16,    18,    34,    56,     6,    17,     3,    18,
      59,    59,    54,    59,     3,    18,    17,    57,    59,    36,
       3,     9,    29,     3,    17,    17,    59,    17,    59,     3,
      29,    59,   223,    46,   177,   140,   157,   190,   193,   212
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    66,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    19,    20,    21,    27,    28,    37,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      80,    81,    87,    92,    93,    94,    95,   110,     6,     8,
       6,     8,    47,    48,    49,    50,    51,    59,    62,    96,
      97,    99,    59,     7,     8,     3,    30,    32,    59,     3,
       3,     3,     3,     3,    38,     3,    59,    59,    59,    59,
      18,    29,   101,   101,    32,    18,   100,    16,     3,     3,
      32,    59,    59,    35,    39,    16,    36,     3,     3,    59,
      97,    59,    62,    59,    59,    62,    97,    59,    62,    98,
      59,    31,    33,   104,    59,    61,    59,    83,    86,    59,
      29,   101,   101,   101,   101,    18,    52,   102,    29,   100,
     100,   100,   101,   101,    17,     3,    16,    88,    55,    56,
      57,    58,    59,    61,    64,    91,   106,     3,    40,    30,
      18,    82,    22,    23,    24,    25,    26,    85,    16,    59,
      62,    59,    53,   104,    59,    62,    91,    18,    89,    56,
      16,   107,    29,    40,    41,    42,    43,    44,    45,    54,
      55,   109,   109,    34,   105,    91,     6,    83,    17,    16,
      46,    59,   101,   101,   102,    59,   100,   100,    18,    90,
      88,     3,   107,   108,    59,   107,    54,    59,    91,    59,
      91,   106,   104,    59,    82,     3,    57,    84,    18,    79,
      36,   103,    91,    17,    89,    95,   109,   107,    29,   105,
       3,     3,    17,    59,    17,   106,   102,    90,    17,    59,
      91,   107,    59,    46,    79,     3,   105,    29,    59
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    65,    66,    66,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    79,    80,    81,    82,    82,    83,
      83,    83,    83,    84,    85,    85,    85,    85,    85,    86,
      87,    88,    89,    89,    90,    90,    91,    91,    91,    91,
      92,    93,    94,    95,    96,    96,    96,    96,    96,    97,
      98,    98,    98,    99,    99,    99,    99,    99,   100,   100,
     100,   100,   100,   100,   101,   101,   101,   101,   101,   102,
     102,   102,   103,   103,   104,   104,   105,   105,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     107,   108,   109,   109,   109,   109,   109,   109,   109,   110
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     4,     3,
       5,     3,    10,     0,     3,     4,     8,     0,     3,     5,
       6,     2,     3,     1,     1,     1,     1,     1,     1,     1,
       7,     4,     0,     3,     0,     3,     1,     1,     1,     1,
       5,     8,     2,     6,     2,     2,     4,     4,     2,     4,
       0,     2,     2,     1,     1,     1,     1,     1,     0,     3,
       3,     3,     5,     5,     0,     3,     5,     5,     3,     0,
       3,     5,     0,     3,     0,     3,     0,     3,     3,     3,
       3,     3,     5,     5,     7,     3,     4,     5,     2,     3,
       4,     0,     1,     1,     1,     1,     1,     1,     0,     8
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
#line 192 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1413 "yacc_sql.tab.c"
    break;

  case 23: /* help: HELP SEMICOLON  */
#line 197 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1421 "yacc_sql.tab.c"
    break;

  case 24: /* sync: SYNC SEMICOLON  */
#line 202 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1429 "yacc_sql.tab.c"
    break;

  case 25: /* begin: TRX_BEGIN SEMICOLON  */
#line 208 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1437 "yacc_sql.tab.c"
    break;

  case 26: /* commit: TRX_COMMIT SEMICOLON  */
#line 214 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1445 "yacc_sql.tab.c"
    break;

  case 27: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 220 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1453 "yacc_sql.tab.c"
    break;

  case 28: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 226 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1462 "yacc_sql.tab.c"
    break;

  case 29: /* show_tables: SHOW TABLES SEMICOLON  */
#line 232 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1470 "yacc_sql.tab.c"
    break;

  case 30: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 238 "yacc_sql.y"
                                     {
		CONTEXT->ssql->flag = SCF_SHOW_INDEX;
		show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
	}
#line 1479 "yacc_sql.tab.c"
    break;

  case 31: /* desc_table: DESC ID SEMICOLON  */
#line 245 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1488 "yacc_sql.tab.c"
    break;

  case 32: /* create_index: CREATE INDEX ID ON ID LBRACE ID index_attr_list RBRACE SEMICOLON  */
#line 253 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), (yyvsp[-3].string));
		}
#line 1497 "yacc_sql.tab.c"
    break;

  case 34: /* index_attr_list: COMMA ID index_attr_list  */
#line 260 "yacc_sql.y"
                                   {
		create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[-1].string));
	}
#line 1505 "yacc_sql.tab.c"
    break;

  case 35: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 266 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1514 "yacc_sql.tab.c"
    break;

  case 36: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 273 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1526 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 283 "yacc_sql.y"
                                   {    }
#line 1532 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 288 "yacc_sql.y"
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
#line 1547 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def: ID_get type LBRACE number RBRACE NULLABLE  */
#line 299 "yacc_sql.y"
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
#line 1562 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def: ID_get type  */
#line 310 "yacc_sql.y"
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
#line 1577 "yacc_sql.tab.c"
    break;

  case 42: /* attr_def: ID_get type NULLABLE  */
#line 321 "yacc_sql.y"
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
#line 1592 "yacc_sql.tab.c"
    break;

  case 43: /* number: NUMBER  */
#line 333 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1598 "yacc_sql.tab.c"
    break;

  case 44: /* type: INT_T  */
#line 336 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1604 "yacc_sql.tab.c"
    break;

  case 45: /* type: STRING_T  */
#line 337 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1610 "yacc_sql.tab.c"
    break;

  case 46: /* type: TEXT_T  */
#line 338 "yacc_sql.y"
                    {(yyval.number)=TEXTS; }
#line 1616 "yacc_sql.tab.c"
    break;

  case 47: /* type: FLOAT_T  */
#line 339 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1622 "yacc_sql.tab.c"
    break;

  case 48: /* type: DATE_T  */
#line 340 "yacc_sql.y"
                    {(yyval.number)=DATES;}
#line 1628 "yacc_sql.tab.c"
    break;

  case 49: /* ID_get: ID  */
#line 344 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1637 "yacc_sql.tab.c"
    break;

  case 50: /* insert: INSERT INTO ID VALUES tuple tuple_list SEMICOLON  */
#line 354 "yacc_sql.y"
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
#line 1657 "yacc_sql.tab.c"
    break;

  case 51: /* tuple: LBRACE value value_list RBRACE  */
#line 371 "yacc_sql.y"
                                       {
		CONTEXT->tuple_num++;
		printf("yacc: tuple num %d\n", CONTEXT->tuple_num);
	}
#line 1666 "yacc_sql.tab.c"
    break;

  case 53: /* tuple_list: COMMA tuple tuple_list  */
#line 378 "yacc_sql.y"
                                 {
	}
#line 1673 "yacc_sql.tab.c"
    break;

  case 55: /* value_list: COMMA value value_list  */
#line 383 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;

	  }
#line 1682 "yacc_sql.tab.c"
    break;

  case 56: /* value: NUMBER  */
#line 389 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
  		value_init_integer(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], (yyvsp[0].number));
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
#line 1692 "yacc_sql.tab.c"
    break;

  case 57: /* value: FLOAT  */
#line 394 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		value_init_float(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], (yyvsp[0].floats));
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
#line 1702 "yacc_sql.tab.c"
    break;

  case 58: /* value: SSS  */
#line 399 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		value_init_string(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], (yyvsp[0].string));
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
#line 1713 "yacc_sql.tab.c"
    break;

  case 59: /* value: DATE_STR  */
#line 405 "yacc_sql.y"
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
#line 1734 "yacc_sql.tab.c"
    break;

  case 60: /* delete: DELETE FROM ID where SEMICOLON  */
#line 425 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1746 "yacc_sql.tab.c"
    break;

  case 61: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 435 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1758 "yacc_sql.tab.c"
    break;

  case 63: /* select_query: SELECT select_attr FROM ID rel_list where  */
#line 449 "yacc_sql.y"
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
#line 1779 "yacc_sql.tab.c"
    break;

  case 64: /* select_attr: STAR attr_list  */
#line 468 "yacc_sql.y"
                   {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1789 "yacc_sql.tab.c"
    break;

  case 65: /* select_attr: ID attr_list  */
#line 473 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1799 "yacc_sql.tab.c"
    break;

  case 66: /* select_attr: ID DOT ID attr_list  */
#line 478 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1809 "yacc_sql.tab.c"
    break;

  case 67: /* select_attr: ID DOT STAR attr_list  */
#line 483 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			// CONTEXT->aggregation_op = NO_AGGREGATE_OP;
			// selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_op);
			// selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, AggregationOp::NO_AGGREGATE_OP);
		}
#line 1822 "yacc_sql.tab.c"
    break;

  case 68: /* select_attr: aggregate_attr aggregate_attr_list  */
#line 491 "yacc_sql.y"
                                             {
			
	}
#line 1830 "yacc_sql.tab.c"
    break;

  case 69: /* aggregate_attr: aggregate_op LBRACE aggregation_field_attr RBRACE  */
#line 506 "yacc_sql.y"
                                                          {
		// RelAttr attr;
		// relation_attr_init(&attr, NULL, $3);
		// printf("aggregation: get a attr %s\n", $3);
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		// selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		// CONTEXT->aggregation_num++;	
	}
#line 1843 "yacc_sql.tab.c"
    break;

  case 71: /* aggregation_field_attr: STAR attr_list  */
#line 517 "yacc_sql.y"
                         {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		printf("aggregation: get a attr *\n");
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
#line 1856 "yacc_sql.tab.c"
    break;

  case 72: /* aggregation_field_attr: ID attr_list  */
#line 525 "yacc_sql.y"
                       {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		printf("aggregation: get a attr %s\n", (yyvsp[-1].string));
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
#line 1869 "yacc_sql.tab.c"
    break;

  case 73: /* aggregate_op: COUNT  */
#line 535 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = COUNT_OP; }
#line 1875 "yacc_sql.tab.c"
    break;

  case 74: /* aggregate_op: AVG  */
#line 536 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = AVG_OP; }
#line 1881 "yacc_sql.tab.c"
    break;

  case 75: /* aggregate_op: MAX  */
#line 537 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = MAX_OP; }
#line 1887 "yacc_sql.tab.c"
    break;

  case 76: /* aggregate_op: MIN  */
#line 538 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = MIN_OP; }
#line 1893 "yacc_sql.tab.c"
    break;

  case 77: /* aggregate_op: SUM  */
#line 539 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = SUM_OP; }
#line 1899 "yacc_sql.tab.c"
    break;

  case 79: /* aggregate_attr_list: COMMA aggregate_attr aggregate_attr_list  */
#line 544 "yacc_sql.y"
                                                  {

	}
#line 1907 "yacc_sql.tab.c"
    break;

  case 80: /* aggregate_attr_list: COMMA STAR aggregate_attr_list  */
#line 548 "yacc_sql.y"
                                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1917 "yacc_sql.tab.c"
    break;

  case 81: /* aggregate_attr_list: COMMA ID aggregate_attr_list  */
#line 553 "yacc_sql.y"
                                      {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1927 "yacc_sql.tab.c"
    break;

  case 82: /* aggregate_attr_list: COMMA ID DOT ID aggregate_attr_list  */
#line 558 "yacc_sql.y"
                                               {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1937 "yacc_sql.tab.c"
    break;

  case 83: /* aggregate_attr_list: COMMA ID DOT STAR aggregate_attr_list  */
#line 563 "yacc_sql.y"
                                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1947 "yacc_sql.tab.c"
    break;

  case 85: /* attr_list: COMMA ID attr_list  */
#line 572 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 1959 "yacc_sql.tab.c"
    break;

  case 86: /* attr_list: COMMA ID DOT ID attr_list  */
#line 579 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 1971 "yacc_sql.tab.c"
    break;

  case 87: /* attr_list: COMMA ID DOT STAR attr_list  */
#line 586 "yacc_sql.y"
                                      {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1981 "yacc_sql.tab.c"
    break;

  case 88: /* attr_list: COMMA aggregate_attr attr_list  */
#line 592 "yacc_sql.y"
                                         {

	}
#line 1989 "yacc_sql.tab.c"
    break;

  case 90: /* rel_list: COMMA ID rel_list  */
#line 599 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 1997 "yacc_sql.tab.c"
    break;

  case 91: /* rel_list: INNER JOIN ID on_list rel_list  */
#line 602 "yacc_sql.y"
                                         {
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string));
	}
#line 2005 "yacc_sql.tab.c"
    break;

  case 93: /* on_list: ON condition condition_list  */
#line 609 "yacc_sql.y"
                                      {

	}
#line 2013 "yacc_sql.tab.c"
    break;

  case 95: /* where: WHERE condition condition_list  */
#line 615 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2021 "yacc_sql.tab.c"
    break;

  case 97: /* condition_list: AND condition condition_list  */
#line 621 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2029 "yacc_sql.tab.c"
    break;

  case 98: /* condition: ID comOp value  */
#line 627 "yacc_sql.y"
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
#line 2055 "yacc_sql.tab.c"
    break;

  case 99: /* condition: value comOp value  */
#line 649 "yacc_sql.y"
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
#line 2080 "yacc_sql.tab.c"
    break;

  case 100: /* condition: ID comOp ID  */
#line 670 "yacc_sql.y"
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
#line 2105 "yacc_sql.tab.c"
    break;

  case 101: /* condition: value comOp ID  */
#line 691 "yacc_sql.y"
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
#line 2132 "yacc_sql.tab.c"
    break;

  case 102: /* condition: ID DOT ID comOp value  */
#line 714 "yacc_sql.y"
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
#line 2158 "yacc_sql.tab.c"
    break;

  case 103: /* condition: value comOp ID DOT ID  */
#line 736 "yacc_sql.y"
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
#line 2184 "yacc_sql.tab.c"
    break;

  case 104: /* condition: ID DOT ID comOp ID DOT ID  */
#line 758 "yacc_sql.y"
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
#line 2208 "yacc_sql.tab.c"
    break;

  case 105: /* condition: ID IN sub_query  */
#line 777 "yacc_sql.y"
                          {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

		Condition condition;
		condition_init(&condition, Contain, CONTEXT->comp, 1, &left_attr, NULL, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		
	}
#line 2222 "yacc_sql.tab.c"
    break;

  case 106: /* condition: ID NOT IN sub_query  */
#line 786 "yacc_sql.y"
                              {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-3].string));

		Condition condition;
		condition_init(&condition, NotContain, CONTEXT->comp, 1, &left_attr, NULL, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 2236 "yacc_sql.tab.c"
    break;

  case 107: /* condition: ID DOT ID comOp sub_query  */
#line 795 "yacc_sql.y"
                                    {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));

		Condition condition;
		condition_init(&condition, Comparison, CONTEXT->comp, 1, &left_attr, NULL, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2249 "yacc_sql.tab.c"
    break;

  case 108: /* condition: EXISTS sub_query  */
#line 803 "yacc_sql.y"
                           {

		Condition condition;
		condition_init(&condition, Exists, CONTEXT->comp, 0, NULL, NULL, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 2261 "yacc_sql.tab.c"
    break;

  case 109: /* condition: NOT EXISTS sub_query  */
#line 810 "yacc_sql.y"
                               {

		Condition condition;
		condition_init(&condition, NotExists, CONTEXT->comp, 0, NULL, NULL, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 2273 "yacc_sql.tab.c"
    break;

  case 110: /* sub_query: LBRACE N select_query RBRACE  */
#line 820 "yacc_sql.y"
                                     {
		// TODO support complex sub query
		ParserContext *old_context = CONTEXT->last_context;
		old_context->sub_query = CONTEXT->ssql;
		*CONTEXT = *old_context;
		printf("sub query addr %p\n", old_context->sub_query);
		printf("swap back old context\n");
	}
#line 2286 "yacc_sql.tab.c"
    break;

  case 111: /* N: %empty  */
#line 828 "yacc_sql.y"
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
#line 2306 "yacc_sql.tab.c"
    break;

  case 112: /* comOp: EQ  */
#line 846 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2312 "yacc_sql.tab.c"
    break;

  case 113: /* comOp: LT  */
#line 847 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2318 "yacc_sql.tab.c"
    break;

  case 114: /* comOp: GT  */
#line 848 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2324 "yacc_sql.tab.c"
    break;

  case 115: /* comOp: LE  */
#line 849 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2330 "yacc_sql.tab.c"
    break;

  case 116: /* comOp: GE  */
#line 850 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2336 "yacc_sql.tab.c"
    break;

  case 117: /* comOp: NE  */
#line 851 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2342 "yacc_sql.tab.c"
    break;

  case 119: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 857 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2351 "yacc_sql.tab.c"
    break;


#line 2355 "yacc_sql.tab.c"

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

#line 862 "yacc_sql.y"

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
