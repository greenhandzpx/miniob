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
    ORDER = 315,
    BY = 316,
    ASC = 317,
    GROUP = 318,
    HAVING = 319,
    OR = 320,
    AS = 321,
    LENGTH = 322,
    ROUND = 323,
    DATE_FORMAT = 324,
    NUMBER = 325,
    FLOAT = 326,
    ID = 327,
    PATH = 328,
    SSS = 329,
    STAR = 330,
    STRING_V = 331,
    DATE_STR = 332,
    NULLVALUE = 333
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 165 "yacc_sql.y"

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
  char *position;
  struct FuncAttrCon *FuncAttrCon1;
  struct RelAttr *relAttr;

#line 295 "yacc_sql.tab.c"

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
#define YYLAST   615

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  79
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  67
/* YYNRULES -- Number of rules.  */
#define YYNRULES  237
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  554

#define YYUNDEFTOK  2
#define YYMAXUTOK   333


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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   198,   198,   200,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   225,   230,   235,   241,   247,   253,   259,   265,
     271,   278,   285,   291,   293,   305,   307,   312,   319,   328,
     330,   334,   345,   356,   367,   380,   383,   384,   385,   386,
     387,   390,   397,   398,   404,   422,   427,   429,   432,   434,
     439,   444,   449,   455,   471,   478,   489,   502,   506,   515,
     517,   521,   524,   541,   558,   575,   580,   586,   591,   599,
     606,   612,   618,   626,   633,   643,   645,   648,   663,   684,
     704,   719,   738,   760,   770,   778,   800,   809,   811,   820,
     829,   838,   849,   850,   857,   864,   871,   881,   882,   883,
     884,   885,   887,   889,   896,   903,   908,   913,   918,   924,
     926,   933,   943,   948,   955,   963,   968,   975,   977,   980,
     983,   986,   991,   993,   997,   999,  1004,  1006,  1015,  1027,
    1040,  1052,  1066,  1069,  1075,  1083,  1105,  1127,  1140,  1154,
    1168,  1182,  1195,  1208,  1220,  1231,  1242,  1253,  1265,  1279,
    1300,  1321,  1344,  1365,  1386,  1406,  1415,  1424,  1433,  1442,
    1453,  1464,  1475,  1486,  1494,  1502,  1526,  1549,  1555,  1562,
    1573,  1576,  1582,  1587,  1588,  1595,  1600,  1608,  1611,  1617,
    1618,  1627,  1628,  1635,  1642,  1649,  1656,  1663,  1670,  1677,
    1684,  1691,  1698,  1705,  1712,  1719,  1726,  1733,  1740,  1747,
    1754,  1761,  1771,  1774,  1780,  1785,  1790,  1795,  1802,  1804,
    1809,  1814,  1819,  1826,  1827,  1832,  1845,  1863,  1864,  1865,
    1866,  1867,  1868,  1869,  1870,  1871,  1872,  1876
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "CREATE", "DROP", "TABLE",
  "TABLES", "INDEX", "SELECT", "DESC", "SHOW", "SYNC", "INSERT", "DELETE",
  "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN", "TRX_COMMIT",
  "TRX_ROLLBACK", "INT_T", "STRING_T", "TEXT_T", "FLOAT_T", "DATE_T",
  "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "SET",
  "ON", "LOAD", "DATA", "INFILE", "EQ", "LT", "GT", "LE", "GE", "NE", "IS",
  "NULLABLE", "COUNT", "AVG", "MAX", "MIN", "SUM", "INNER", "JOIN", "IN",
  "EXISTS", "LIKE", "NOT", "UNIQUE", "ORDER", "BY", "ASC", "GROUP",
  "HAVING", "OR", "AS", "LENGTH", "ROUND", "DATE_FORMAT", "NUMBER",
  "FLOAT", "ID", "PATH", "SSS", "STAR", "STRING_V", "DATE_STR",
  "NULLVALUE", "$accept", "commands", "command", "exit", "help", "sync",
  "begin", "commit", "rollback", "drop_table", "show_tables", "show_index",
  "desc_table", "create_index", "unique_option", "index_attr_list",
  "drop_index", "create_table", "attr_def_list", "attr_def", "number",
  "type", "ID_get", "NONULL", "insert", "tuple", "tuple_list",
  "value_list", "value", "delete", "update", "assign", "assign_list",
  "select", "select_query", "select_attr", "as_option", "func_attr",
  "function_field_attr", "aggregate_attr", "aggregation_field_attr",
  "aggrattr_list", "aggregate_op", "aggregate_attr_list", "attr_list",
  "rel_list", "on_list", "where", "condition_list", "funcCp",
  "funcCp_field_attr", "condition", "group", "group_attrs",
  "group_attr_list", "group_attr", "having", "having_condition_list",
  "having_condition", "order", "order_attr", "order_attr_list", "asc",
  "sub_query", "N", "comOp", "load_data", YY_NULLPTR
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
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333
};
# endif

#define YYPACT_NINF (-426)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-86)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -426,   309,  -426,    18,   145,   310,   -24,   205,    61,    44,
      47,    20,   120,   124,   137,   155,   172,   114,  -426,  -426,
    -426,  -426,  -426,  -426,  -426,  -426,  -426,  -426,  -426,  -426,
    -426,  -426,  -426,  -426,  -426,  -426,   227,  -426,   123,  -426,
     200,   146,   163,  -426,  -426,  -426,  -426,  -426,   233,   252,
     271,    23,    36,   243,   293,   154,   311,   322,   323,   300,
    -426,   261,   277,   315,  -426,  -426,  -426,  -426,  -426,   314,
    -426,   338,   285,   361,   362,   397,   397,   397,   319,    69,
    -426,   291,  -426,   294,  -426,   308,  -426,   202,   312,  -426,
      98,  -426,  -426,   317,   359,   348,   327,   334,   339,   347,
    -426,  -426,  -426,  -426,   384,  -426,  -426,  -426,  -426,   404,
     396,   407,    28,   293,   408,    36,   293,   293,   293,   149,
      15,   293,   154,   408,    29,   412,   405,   426,   423,   110,
     437,   413,   436,   425,  -426,   438,   350,   398,   400,    53,
     411,   411,   111,   401,  -426,  -426,  -426,   414,  -426,  -426,
    -426,  -426,   415,   441,   424,   348,   135,  -426,  -426,   427,
    -426,  -426,   142,   147,  -426,  -426,  -426,  -426,   411,   461,
    -426,   481,   444,   482,   485,   486,   215,   360,   352,    -9,
     360,  -426,   127,   327,   348,   497,   339,   487,  -426,  -426,
    -426,  -426,  -426,    90,   489,  -426,   434,   490,   491,    36,
     293,   293,   293,   149,   439,     2,   446,   293,   293,   408,
     106,   412,   412,   412,   492,   423,   509,   504,  -426,   481,
     406,   406,   406,   443,  -426,  -426,  -426,  -426,  -426,  -426,
     456,   500,  -426,   119,   122,   460,   212,   502,   174,   374,
     110,   110,  -426,   -12,  -426,  -426,   436,   516,   448,   438,
     518,   452,  -426,   445,  -426,   453,  -426,    53,    53,   454,
    -426,  -426,  -426,  -426,   455,  -426,   -13,   348,   463,   468,
    -426,  -426,  -426,   153,  -426,  -426,  -426,  -426,   411,   512,
     461,  -426,   513,  -426,   503,  -426,   514,   515,   517,   392,
    -426,   411,  -426,   520,  -426,   505,  -426,  -426,  -426,   508,
    -426,  -426,   411,  -426,   522,   510,  -426,  -426,    -9,    -9,
     511,  -426,  -426,  -426,   538,  -426,  -426,  -426,   525,  -426,
     526,   471,   473,   293,     2,   110,   474,     2,   468,   475,
     488,  -426,   412,   412,   492,  -426,  -426,  -426,   476,  -426,
     411,   411,   534,   236,   169,   492,   411,  -426,   479,   480,
     492,   411,  -426,   483,  -426,  -426,   484,  -426,    92,   493,
     536,  -426,  -426,  -426,  -426,    -9,   521,  -426,  -426,   529,
     495,   542,   494,  -426,  -426,  -426,  -426,   537,   544,   411,
    -426,   546,   535,  -426,  -426,  -426,   550,   492,  -426,  -426,
     551,   492,  -426,  -426,  -426,  -426,   526,   560,  -426,     2,
     498,   442,  -426,   475,  -426,    74,  -426,  -426,  -426,   492,
     411,  -426,   499,  -426,   552,  -426,   555,  -426,  -426,  -426,
    -426,   557,   558,   559,   561,   562,   563,   542,   564,   507,
    -426,   564,   566,   492,  -426,  -426,  -426,   170,   192,   213,
     220,   226,   442,  -426,  -426,   519,  -426,     7,  -426,  -426,
     567,    13,   568,    14,   569,    34,   570,   101,   571,   103,
     572,   563,    87,   564,   564,  -426,   360,   235,   360,   360,
     240,   360,   360,   259,   360,   360,   266,   360,   360,   270,
     360,  -426,   564,   523,   564,  -426,  -426,   411,   573,   575,
     411,   411,   576,   577,   411,   411,   579,   580,   411,   411,
     581,   582,   411,   411,   583,   584,   411,  -426,    80,  -426,
    -426,   360,   360,  -426,  -426,   360,   360,  -426,  -426,   360,
     360,  -426,  -426,   360,   360,  -426,  -426,   360,   360,  -426,
     564,   564,   411,   411,   411,   411,   411,   411,   411,   411,
     411,   411,  -426,  -426,  -426,  -426,  -426,  -426,  -426,  -426,
    -426,  -426,  -426,  -426
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
       0,     0,     0,   107,   108,   109,   110,   111,     0,     0,
       0,   119,   119,    74,   119,   112,     0,     0,     0,     0,
      24,     0,     0,     0,    25,    26,    27,    23,    22,     0,
      71,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      86,     0,    77,     0,    75,     0,    80,     0,     0,    83,
      97,    31,    29,     0,     0,   134,     0,     0,     0,     0,
      28,    37,    60,    61,    94,    62,    63,    64,    93,     0,
       0,     0,   119,   119,   112,   119,   119,   119,   119,   127,
     119,   119,   112,   112,   102,   102,     0,     0,     0,     0,
       0,     0,    69,     0,    51,    39,     0,     0,     0,    87,
       0,     0,     0,     0,   120,   122,   126,     0,    79,    82,
      78,    76,     0,     0,     0,   134,     0,   116,   115,     0,
     113,    84,     0,     0,    99,    98,    96,    30,     0,    56,
     226,     0,     0,     0,     0,     0,     0,     0,     0,   136,
       0,    65,     0,     0,   134,     0,     0,     0,    46,    47,
      48,    49,    50,    52,     0,    95,     0,     0,     0,   119,
     119,   119,   119,   127,     0,   127,   180,   119,   119,   112,
     102,   102,   102,   102,    58,     0,     0,     0,   178,     0,
       0,     0,     0,     0,   227,   228,   229,   230,   231,   232,
     233,     0,   235,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   135,     0,    67,    68,    69,     0,     0,    39,
       0,     0,    44,     0,    43,     0,    90,    88,    89,     0,
     123,   125,   121,    81,     0,   128,   132,   134,     0,   212,
     117,   118,   114,     0,   104,   103,   100,   101,     0,     0,
      56,    54,     0,   179,   143,   142,     0,     0,     0,     0,
     234,   226,   165,     0,   236,   147,   145,   148,   174,   161,
     146,   150,   226,   155,     0,   151,   153,   154,   136,   136,
     176,   177,    70,    66,     0,    40,    38,    45,     0,    53,
      35,     0,     0,   119,   127,     0,     0,   127,   212,     0,
       0,    72,   102,   102,    58,    55,    57,   225,     0,   139,
       0,     0,     0,     0,     0,    58,   226,   166,     0,     0,
      58,   226,   156,     0,   137,   138,     0,   237,    52,     0,
       0,    91,    92,   124,   129,   136,   132,   130,    73,   185,
     187,   183,     0,   105,   106,    59,   144,     0,     0,   226,
     167,     0,   160,   162,   149,   173,     0,    58,   159,   163,
       0,    58,   152,   175,    42,    41,    35,     0,   133,   127,
       0,   191,   181,     0,   182,   223,   213,   140,   141,    58,
     226,   168,     0,   169,     0,   157,     0,    36,    32,   131,
     186,     0,     0,     0,     0,     0,   189,   183,   218,     0,
     224,   218,     0,    58,   164,   170,   158,     0,     0,     0,
       0,     0,   191,   188,   184,     0,   216,   223,   214,   171,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   189,   223,   218,   218,   172,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   190,   218,     0,   218,   217,   215,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   220,   223,   219,
     192,     0,     0,   193,   196,     0,     0,   197,   200,     0,
       0,   201,   204,     0,     0,   205,   208,     0,     0,   209,
     218,   218,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   222,   221,   194,   195,   198,   199,   202,   203,
     206,   207,   210,   211
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -426,  -426,  -426,  -426,  -426,  -426,  -426,  -426,  -426,  -426,
    -426,  -426,  -426,  -426,  -426,   180,  -426,  -426,   331,   416,
    -426,  -426,  -426,   245,  -426,   389,   325,  -300,   -75,  -426,
    -426,   428,   363,  -426,   390,  -426,   -34,   528,   186,   -59,
    -426,   -99,  -426,   -87,   -45,  -193,   242,  -152,  -269,  -223,
      95,  -226,  -426,  -426,   183,   209,  -426,   152,   173,   286,
    -426,  -402,  -425,  -133,  -426,  -172,  -426
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    40,   360,    30,    31,   187,   135,
     318,   193,   136,   254,    32,   169,   216,   279,   177,    33,
      34,   132,   184,    35,    36,    53,    81,    54,   109,    55,
     126,   164,    56,    89,    82,   155,   327,   130,   242,   178,
     286,   179,   269,   370,   404,   371,   402,   443,   426,   331,
     406,   446,   431,   180,   217,   234,    37
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     108,   108,   108,   206,   170,   236,   239,    84,   243,    86,
     265,   297,   267,   301,   308,   309,   307,   463,    83,   114,
     152,    88,   464,   325,    38,   240,   165,   146,   122,   448,
     466,   469,   247,    78,   375,   160,   161,   484,   218,   354,
     355,    78,   467,   470,   156,   386,    78,   162,    57,   245,
     390,   472,    79,    80,    78,   153,   241,   142,   163,   -85,
     310,   485,   486,   473,    60,   197,   198,   144,   145,   430,
     148,   149,   150,   151,    61,   157,   158,    39,   143,    62,
     507,   147,   509,   531,   428,   154,   283,   414,   159,    80,
     530,   416,    63,   214,    80,   -85,   398,   482,   292,   365,
     -85,   298,    80,   429,   303,   196,   251,   244,   -85,   432,
     311,   274,   275,   276,   277,   328,   483,   344,   475,    80,
     478,   384,   272,    64,   162,   -85,   170,    65,   542,   543,
     476,   364,   479,   450,   367,   273,   430,   252,   170,   394,
      66,   115,   430,   170,   116,   285,   285,   285,   253,   430,
     253,    41,    69,    42,   260,   261,   262,   263,    67,   296,
     347,   300,   270,   271,   306,   259,   171,   152,   172,   264,
     124,   352,    87,   125,   293,    68,   294,   173,   174,   175,
     102,   103,   176,   199,   105,   170,   200,   106,   107,   173,
     174,   175,   102,   103,   295,    71,   105,   102,   103,   106,
     107,   105,   153,   334,   106,   107,   419,   207,    72,   380,
     208,   385,    58,    59,   210,    80,   345,   211,    73,   212,
      80,   -85,   213,   321,   322,   332,   -85,   350,   333,   304,
      70,   294,   326,   373,   374,    74,   173,   174,   175,   102,
     103,   382,   451,   105,   223,   452,   106,   107,   411,    75,
      43,    44,    45,    46,    47,   224,   225,   226,   227,   228,
     229,   230,   110,   111,   453,   377,   378,   454,    76,   383,
     231,   387,   232,   233,   120,    85,   391,   121,   363,   173,
     174,   175,   102,   103,   299,   455,   105,    77,   456,   106,
     107,   381,   457,   294,   487,   458,   490,   491,   459,   494,
     495,   460,   498,   499,   409,   502,   503,   488,   506,     2,
     489,    78,   492,     3,     4,   493,   287,   288,     5,     6,
       7,     8,     9,    10,    11,    91,    92,    90,    12,    13,
      14,   496,    93,    94,   497,   433,    15,    16,   500,   532,
     533,   501,   504,   534,   535,   505,    17,   536,   537,    95,
      96,   538,   539,    97,    98,   540,   541,    99,    43,    44,
      45,    46,    47,   117,   100,   101,   118,    43,    44,    45,
      46,    47,   188,   189,   190,   191,   192,    48,    49,    50,
     119,   129,    51,   137,   123,    52,    48,    49,    50,   127,
     128,   112,   224,   225,   226,   227,   228,   229,   230,   131,
     224,   225,   226,   227,   228,   229,   230,   237,   133,   232,
     238,   134,   510,   138,   140,   513,   514,   232,   235,   517,
     518,   139,   166,   521,   522,   141,    87,   525,   526,   167,
     162,   529,   224,   225,   226,   227,   228,   229,   230,   168,
     181,   173,   174,   175,   102,   103,   305,   342,   105,   232,
     343,   106,   107,   182,   183,   185,   186,   544,   545,   546,
     547,   548,   549,   550,   551,   552,   553,   102,   103,   104,
     194,   105,   195,   201,   106,   107,   102,   103,   284,   215,
     105,   102,   103,   106,   107,   105,   202,   203,   106,   107,
     421,   422,   423,   424,   425,   204,   205,   170,   220,   209,
     219,   221,   222,   248,   250,   255,   256,   257,   258,   268,
     278,   266,   281,     5,   290,   289,   291,   294,   302,   313,
     314,   316,   317,   319,   329,   320,   323,   324,   330,   335,
     337,   339,   338,   340,   348,   341,   346,   349,   351,   353,
     356,   357,   358,   361,   359,   362,   366,   369,   376,   372,
     379,   388,   389,   397,   407,   392,   393,   325,   400,   401,
     403,   408,   410,   418,   412,   396,   405,   413,   415,   435,
     420,   434,   436,   437,   438,   439,   417,   440,   441,   447,
     315,   442,   445,   449,   465,   468,   471,   474,   477,   480,
     511,   462,   512,   515,   516,   508,   519,   520,   523,   524,
     527,   528,   249,   395,   280,   336,   113,   282,   399,   312,
     444,   246,   427,   481,   368,   461
};

static const yytype_int16 yycheck[] =
{
      75,    76,    77,   155,    16,   177,   178,    52,   180,    54,
     203,   234,   205,   236,   240,   241,   239,    10,    52,    78,
      18,    55,   447,    36,     6,    34,   125,   114,    87,   431,
      17,    17,   184,    18,   334,   122,   123,   462,   171,   308,
     309,    18,    29,    29,    29,   345,    18,    18,    72,   182,
     350,    17,    29,    66,    18,    53,    65,    29,    29,    72,
      72,   463,   464,    29,     3,   140,   141,   112,   113,    62,
     115,   116,   117,   118,    30,   120,   121,    59,   112,    32,
     482,   115,   484,   508,    10,   119,   219,   387,   122,    66,
      10,   391,    72,   168,    66,    72,   365,    10,   231,   325,
      72,   234,    66,    29,   237,   139,    16,   182,    72,   409,
     243,   210,   211,   212,   213,   267,    29,   289,    17,    66,
      17,   344,   209,     3,    18,    72,    16,     3,   530,   531,
      29,   324,    29,   433,   327,    29,    62,    47,    16,    47,
       3,    72,    62,    16,    75,   220,   221,   222,    58,    62,
      58,     6,    38,     8,   199,   200,   201,   202,     3,   234,
     293,   236,   207,   208,   239,   199,    56,    18,    58,   203,
      72,   304,    18,    75,    55,     3,    57,    67,    68,    69,
      70,    71,    72,    72,    74,    16,    75,    77,    78,    67,
      68,    69,    70,    71,    72,    72,    74,    70,    71,    77,
      78,    74,    53,   278,    77,    78,   399,    72,     8,   342,
      75,   344,     7,     8,    72,    66,   291,    75,    72,    72,
      66,    72,    75,   257,   258,    72,    72,   302,    75,    55,
       3,    57,   266,   332,   333,    72,    67,    68,    69,    70,
      71,    72,    72,    74,    29,    75,    77,    78,   381,    16,
      48,    49,    50,    51,    52,    40,    41,    42,    43,    44,
      45,    46,    76,    77,    72,   340,   341,    75,    16,   344,
      55,   346,    57,    58,    72,    32,   351,    75,   323,    67,
      68,    69,    70,    71,    72,    72,    74,    16,    75,    77,
      78,    55,    72,    57,   466,    75,   468,   469,    72,   471,
     472,    75,   474,   475,   379,   477,   478,    72,   480,     0,
      75,    18,    72,     4,     5,    75,   221,   222,     9,    10,
      11,    12,    13,    14,    15,     3,     3,    16,    19,    20,
      21,    72,    32,    72,    75,   410,    27,    28,    72,   511,
     512,    75,    72,   515,   516,    75,    37,   519,   520,    72,
      35,   523,   524,    39,    16,   527,   528,    72,    48,    49,
      50,    51,    52,    72,     3,     3,    72,    48,    49,    50,
      51,    52,    22,    23,    24,    25,    26,    67,    68,    69,
      72,    33,    72,    36,    72,    75,    67,    68,    69,    72,
      31,    72,    40,    41,    42,    43,    44,    45,    46,    72,
      40,    41,    42,    43,    44,    45,    46,    55,    74,    57,
      58,    72,   487,    29,    18,   490,   491,    57,    58,   494,
     495,    17,    17,   498,   499,    18,    18,   502,   503,     3,
      18,   506,    40,    41,    42,    43,    44,    45,    46,    16,
       3,    67,    68,    69,    70,    71,    72,    55,    74,    57,
      58,    77,    78,    40,    18,    30,    18,   532,   533,   534,
     535,   536,   537,   538,   539,   540,   541,    70,    71,    72,
      72,    74,    72,    72,    77,    78,    70,    71,    72,    18,
      74,    70,    71,    77,    78,    74,    72,    72,    77,    78,
      48,    49,    50,    51,    52,    54,    72,    16,    16,    72,
      56,    16,    16,     6,    17,    16,    72,    17,    17,    63,
      18,    72,     3,     9,    58,    72,    16,    57,    16,     3,
      72,     3,    70,    78,    61,    72,    72,    72,    60,    17,
      17,    17,    29,    18,    29,    18,    16,    29,    16,    29,
      29,     3,    17,    72,    18,    72,    72,    72,    72,    61,
      16,    72,    72,    17,    17,    72,    72,    36,    29,    64,
      18,    17,    16,     3,    29,    72,    72,    17,    17,    17,
      72,    72,    17,    16,    16,    16,   396,    16,    16,    72,
     249,    18,    18,    17,    17,    17,    17,    17,    17,    17,
      17,    72,    17,    17,    17,    72,    17,    17,    17,    17,
      17,    17,   186,   358,   215,   280,    78,   217,   366,   246,
     427,   183,   403,   461,   328,   442
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    80,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    19,    20,    21,    27,    28,    37,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      95,    96,   103,   108,   109,   112,   113,   145,     6,    59,
      93,     6,     8,    48,    49,    50,    51,    52,    67,    68,
      69,    72,    75,   114,   116,   118,   121,    72,     7,     8,
       3,    30,    32,    72,     3,     3,     3,     3,     3,    38,
       3,    72,     8,    72,    72,    16,    16,    16,    18,    29,
      66,   115,   123,   115,   123,    32,   123,    18,   115,   122,
      16,     3,     3,    32,    72,    72,    35,    39,    16,    72,
       3,     3,    70,    71,    72,    74,    77,    78,   107,   117,
     117,   117,    72,   116,   118,    72,    75,    72,    72,    72,
      72,    75,   118,    72,    72,    75,   119,    72,    31,    33,
     126,    72,   110,    74,    72,    98,   101,    36,    29,    17,
      18,    18,    29,   115,   123,   123,   122,   115,   123,   123,
     123,   123,    18,    53,   115,   124,    29,   123,   123,   115,
     122,   122,    18,    29,   120,   120,    17,     3,    16,   104,
      16,    56,    58,    67,    68,    69,    72,   107,   128,   130,
     142,     3,    40,    18,   111,    30,    18,    97,    22,    23,
      24,    25,    26,   100,    72,    72,   115,   107,   107,    72,
      75,    72,    72,    72,    54,    72,   126,    72,    75,    72,
      72,    75,    72,    75,   107,    18,   105,   143,   142,    56,
      16,    16,    16,    29,    40,    41,    42,    43,    44,    45,
      46,    55,    57,    58,   144,    58,   144,    55,    58,   144,
      34,    65,   127,   144,   107,   142,   110,   126,     6,    98,
      17,    16,    47,    58,   102,    16,    72,    17,    17,   115,
     123,   123,   123,   123,   115,   124,    72,   124,    63,   131,
     123,   123,   122,    29,   120,   120,   120,   120,    18,   106,
     104,     3,   113,   142,    72,   107,   129,   129,   129,    72,
      58,    16,   142,    55,    57,    72,   107,   128,   142,    72,
     107,   128,    16,   142,    55,    72,   107,   128,   130,   130,
      72,   142,   111,     3,    72,    97,     3,    70,    99,    78,
      72,   115,   115,    72,    72,    36,   115,   125,   126,    61,
      60,   138,    72,    75,   107,    17,   105,    17,    29,    17,
      18,    18,    55,    58,   144,   107,    16,   142,    29,    29,
     107,    16,   142,    29,   127,   127,    29,     3,    17,    18,
      94,    72,    72,   123,   124,   130,    72,   124,   138,    72,
     132,   134,    61,   120,   120,   106,    72,   107,   107,    16,
     142,    55,    72,   107,   128,   142,   106,   107,    72,    72,
     106,   107,    72,    72,    47,   102,    72,    17,   127,   125,
      29,    64,   135,    18,   133,    72,   139,    17,    17,   107,
      16,   142,    29,    17,   106,    17,   106,    94,     3,   124,
      72,    48,    49,    50,    51,    52,   137,   134,    10,    29,
      62,   141,   106,   107,    72,    17,    17,    16,    16,    16,
      16,    16,    18,   136,   133,    18,   140,    72,   140,    17,
     106,    72,    75,    72,    75,    72,    75,    72,    75,    72,
      75,   137,    72,    10,   141,    17,    17,    29,    17,    17,
      29,    17,    17,    29,    17,    17,    29,    17,    17,    29,
      17,   136,    10,    29,   141,   140,   140,   144,    72,    75,
     144,   144,    72,    75,   144,   144,    72,    75,   144,   144,
      72,    75,   144,   144,    72,    75,   144,   140,    72,   140,
     107,    17,    17,   107,   107,    17,    17,   107,   107,    17,
      17,   107,   107,    17,    17,   107,   107,    17,    17,   107,
      10,   141,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   140,   140,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    79,    80,    80,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    93,    94,    94,    95,    96,    97,
      97,    98,    98,    98,    98,    99,   100,   100,   100,   100,
     100,   101,   102,   102,   103,   104,   105,   105,   106,   106,
     107,   107,   107,   107,   107,   108,   109,   110,   110,   111,
     111,   112,   113,   113,   113,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   115,   115,   116,   116,   116,
     116,   116,   116,   117,   117,   117,   118,   119,   119,   119,
     119,   119,   120,   120,   120,   120,   120,   121,   121,   121,
     121,   121,   122,   122,   122,   122,   122,   122,   122,   123,
     123,   123,   123,   123,   123,   123,   123,   124,   124,   124,
     124,   124,   125,   125,   126,   126,   127,   127,   127,   128,
     128,   128,   129,   129,   129,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     131,   131,   132,   133,   133,   134,   134,   135,   135,   136,
     136,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   138,   138,   139,   139,   139,   139,   140,   140,
     140,   140,   140,   141,   141,   142,   143,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   145
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
       1,     1,     1,     1,     1,     5,     7,     3,     3,     0,
       3,     2,     8,     9,     2,     2,     4,     2,     4,     4,
       2,     6,     4,     2,     4,     0,     1,     4,     6,     6,
       6,     8,     8,     1,     1,     3,     4,     0,     2,     2,
       4,     4,     0,     3,     3,     5,     5,     1,     1,     1,
       1,     1,     0,     3,     5,     3,     3,     5,     5,     0,
       3,     5,     3,     5,     7,     5,     3,     0,     3,     5,
       5,     7,     0,     3,     0,     3,     0,     3,     3,     4,
       6,     6,     1,     1,     3,     3,     3,     3,     3,     5,
       3,     3,     5,     3,     3,     3,     4,     6,     7,     5,
       5,     3,     5,     5,     7,     3,     4,     5,     6,     6,
       7,     8,     9,     5,     3,     5,     3,     3,     2,     3,
       0,     4,     2,     0,     3,     1,     3,     0,     3,     0,
       3,     0,     6,     6,     8,     8,     6,     6,     8,     8,
       6,     6,     8,     8,     6,     6,     8,     8,     6,     6,
       8,     8,     0,     3,     3,     5,     3,     5,     0,     4,
       4,     6,     6,     0,     1,     4,     0,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     2,     8
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
  case 22:
#line 225 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1869 "yacc_sql.tab.c"
    break;

  case 23:
#line 230 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1877 "yacc_sql.tab.c"
    break;

  case 24:
#line 235 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1885 "yacc_sql.tab.c"
    break;

  case 25:
#line 241 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1893 "yacc_sql.tab.c"
    break;

  case 26:
#line 247 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1901 "yacc_sql.tab.c"
    break;

  case 27:
#line 253 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1909 "yacc_sql.tab.c"
    break;

  case 28:
#line 259 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1918 "yacc_sql.tab.c"
    break;

  case 29:
#line 265 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1926 "yacc_sql.tab.c"
    break;

  case 30:
#line 271 "yacc_sql.y"
                                     {
		CONTEXT->ssql->flag = SCF_SHOW_INDEX;
		show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
	}
#line 1935 "yacc_sql.tab.c"
    break;

  case 31:
#line 278 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1944 "yacc_sql.tab.c"
    break;

  case 32:
#line 286 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), (yyvsp[-3].string), CONTEXT->unique);
		}
#line 1953 "yacc_sql.tab.c"
    break;

  case 34:
#line 293 "yacc_sql.y"
                 {
		CONTEXT->unique = 1;
	}
#line 1961 "yacc_sql.tab.c"
    break;

  case 36:
#line 307 "yacc_sql.y"
                                   {
		create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[-1].string));
	}
#line 1969 "yacc_sql.tab.c"
    break;

  case 37:
#line 313 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1978 "yacc_sql.tab.c"
    break;

  case 38:
#line 320 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1990 "yacc_sql.tab.c"
    break;

  case 40:
#line 330 "yacc_sql.y"
                                   {    }
#line 1996 "yacc_sql.tab.c"
    break;

  case 41:
#line 335 "yacc_sql.y"
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
#line 2011 "yacc_sql.tab.c"
    break;

  case 42:
#line 346 "yacc_sql.y"
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
#line 2026 "yacc_sql.tab.c"
    break;

  case 43:
#line 357 "yacc_sql.y"
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
#line 2041 "yacc_sql.tab.c"
    break;

  case 44:
#line 368 "yacc_sql.y"
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
#line 2056 "yacc_sql.tab.c"
    break;

  case 45:
#line 380 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 2062 "yacc_sql.tab.c"
    break;

  case 46:
#line 383 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 2068 "yacc_sql.tab.c"
    break;

  case 47:
#line 384 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 2074 "yacc_sql.tab.c"
    break;

  case 48:
#line 385 "yacc_sql.y"
                    {(yyval.number)=TEXTS; }
#line 2080 "yacc_sql.tab.c"
    break;

  case 49:
#line 386 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 2086 "yacc_sql.tab.c"
    break;

  case 50:
#line 387 "yacc_sql.y"
                    {(yyval.number)=DATES;}
#line 2092 "yacc_sql.tab.c"
    break;

  case 51:
#line 391 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 2101 "yacc_sql.tab.c"
    break;

  case 54:
#line 405 "yacc_sql.y"
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
#line 2121 "yacc_sql.tab.c"
    break;

  case 55:
#line 422 "yacc_sql.y"
                                       {
		CONTEXT->tuple_num++;
		printf("yacc: tuple num %d\n", CONTEXT->tuple_num);
	}
#line 2130 "yacc_sql.tab.c"
    break;

  case 57:
#line 429 "yacc_sql.y"
                                 {
	}
#line 2137 "yacc_sql.tab.c"
    break;

  case 59:
#line 434 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 2145 "yacc_sql.tab.c"
    break;

  case 60:
#line 439 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
  		value_init_integer(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], (yyvsp[0].number));
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
#line 2155 "yacc_sql.tab.c"
    break;

  case 61:
#line 444 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		value_init_float(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], (yyvsp[0].floats));
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
#line 2165 "yacc_sql.tab.c"
    break;

  case 62:
#line 449 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		value_init_string(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], (yyvsp[0].string));
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
#line 2176 "yacc_sql.tab.c"
    break;

  case 63:
#line 455 "yacc_sql.y"
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
#line 2197 "yacc_sql.tab.c"
    break;

  case 64:
#line 471 "yacc_sql.y"
                   {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
		value_init_null(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++]);
	}
#line 2206 "yacc_sql.tab.c"
    break;

  case 65:
#line 479 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
			CONTEXT->last_conditino_seqno = 0;
    }
#line 2219 "yacc_sql.tab.c"
    break;

  case 66:
#line 490 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-5].string), CONTEXT->attribute_name, CONTEXT->values, CONTEXT->upselect_num,
					CONTEXT->conditions, CONTEXT->condition_length, CONTEXT->upselect_vec);
			CONTEXT->condition_length = 0;
			CONTEXT->last_conditino_seqno = 0;
			CONTEXT->value_length = 0;
			CONTEXT->upselect_num = 0;
		}
#line 2233 "yacc_sql.tab.c"
    break;

  case 67:
#line 502 "yacc_sql.y"
                    {
		CONTEXT->upselect_num++;
		CONTEXT->attribute_name[CONTEXT->value_length - 1] = (yyvsp[-2].string);
	}
#line 2242 "yacc_sql.tab.c"
    break;

  case 68:
#line 506 "yacc_sql.y"
                          {
		CONTEXT->upselect_num++;
		CONTEXT->value_length++;
		CONTEXT->attribute_name[CONTEXT->value_length - 1] = (yyvsp[-2].string);
		CONTEXT->upselect_vec[CONTEXT->value_length - 1] = &CONTEXT->sub_query->sstr.selection;
	}
#line 2253 "yacc_sql.tab.c"
    break;

  case 72:
#line 525 "yacc_sql.y"
                {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-4].string), NULL);

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
#line 2274 "yacc_sql.tab.c"
    break;

  case 73:
#line 542 "yacc_sql.y"
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
#line 2295 "yacc_sql.tab.c"
    break;

  case 74:
#line 559 "yacc_sql.y"
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
#line 2312 "yacc_sql.tab.c"
    break;

  case 75:
#line 575 "yacc_sql.y"
                   {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2322 "yacc_sql.tab.c"
    break;

  case 76:
#line 580 "yacc_sql.y"
                                  {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			attr.alias_name = (yyvsp[-1].string);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2333 "yacc_sql.tab.c"
    break;

  case 77:
#line 586 "yacc_sql.y"
                       {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2343 "yacc_sql.tab.c"
    break;

  case 78:
#line 591 "yacc_sql.y"
                                {
		printf("                     %s\n", (yyvsp[-1].string));
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-3].string));
			attr.alias_name = (yyvsp[-1].string);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2355 "yacc_sql.tab.c"
    break;

  case 79:
#line 599 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2365 "yacc_sql.tab.c"
    break;

  case 80:
#line 606 "yacc_sql.y"
                              {
		}
#line 2372 "yacc_sql.tab.c"
    break;

  case 81:
#line 612 "yacc_sql.y"
                                           {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-5].string), (yyvsp[-3].string));
			attr.alias_name = (yyvsp[-1].string);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2383 "yacc_sql.tab.c"
    break;

  case 82:
#line 618 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			// CONTEXT->aggregation_op = NO_AGGREGATE_OP;
			// selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_op);
			// selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, AggregationOp::NO_AGGREGATE_OP);
		}
#line 2396 "yacc_sql.tab.c"
    break;

  case 83:
#line 626 "yacc_sql.y"
                                             {
		if (CONTEXT->last_aggregation_seqno == 0) {
			CONTEXT->last_aggregation_seqno = CONTEXT->aggregation_num;
		}		
		CONTEXT->ssql->sstr.selection.aggregation_alias[CONTEXT->last_aggregation_seqno-1] = NULL;
		CONTEXT->last_aggregation_seqno--;
	}
#line 2408 "yacc_sql.tab.c"
    break;

  case 84:
#line 633 "yacc_sql.y"
                                                          {
		if (CONTEXT->last_aggregation_seqno == 0) {
			CONTEXT->last_aggregation_seqno = CONTEXT->aggregation_num;
		}		
		CONTEXT->ssql->sstr.selection.aggregation_alias[CONTEXT->last_aggregation_seqno-1] = (yyvsp[-1].string);
		CONTEXT->last_aggregation_seqno--;
	}
#line 2420 "yacc_sql.tab.c"
    break;

  case 87:
#line 648 "yacc_sql.y"
                                                 {
		selects_append_funcop(&CONTEXT->ssql->sstr.selection, LENGTH_OP);
		selects_append_funcvalue2(&CONTEXT->ssql->sstr.selection, 0);
		char* attr_name = (char*)malloc(strlen("length(") + strlen((yyvsp[-1].string)) + strlen(")") + 1);
		memset(attr_name, strlen("length(") + strlen((yyvsp[-1].string)) + strlen(")") + 1, 0);

		//strcat(attr_name, "length(");
		strcpy(attr_name, "length(");
		strcat(attr_name, (yyvsp[-1].string));
		strcat(attr_name, ")");
		strcat(attr_name, "\0");

		selects_modify_alias_name(&CONTEXT->ssql->sstr.selection, attr_name);
		printf("func name %s\n", attr_name);
	}
#line 2440 "yacc_sql.tab.c"
    break;

  case 88:
#line 663 "yacc_sql.y"
                                                              {
		selects_append_funcop(&CONTEXT->ssql->sstr.selection, ROUND_OP);
		selects_append_funcvalue2(&CONTEXT->ssql->sstr.selection, &CONTEXT->values[CONTEXT->value_length - 1]);
		
		char * value_string = value2string(&CONTEXT->values[CONTEXT->value_length - 1]);

		char* attr_name = (char*)malloc(strlen("round(") + strlen((yyvsp[-3].string)) + strlen(",") + strlen(value_string) + strlen(")") + 1);
		memset(attr_name, strlen("round(") + strlen((yyvsp[-3].string)) + strlen(",") + strlen(value_string) + strlen(")") + 1, 0);

		//strcat(attr_name, "round(");
		strcpy(attr_name, "round(");
		strcat(attr_name, (yyvsp[-3].string));
		strcat(attr_name, ",");
		strcat(attr_name, "\0");
		
		strcat(attr_name, value_string);
		strcat(attr_name, ")");

		selects_modify_alias_name(&CONTEXT->ssql->sstr.selection, attr_name);
		printf("func name %s\n", attr_name);
	}
#line 2466 "yacc_sql.tab.c"
    break;

  case 89:
#line 684 "yacc_sql.y"
                                                                    {
		selects_append_funcop(&CONTEXT->ssql->sstr.selection, DATE_FORMAT_OP);
		selects_append_funcvalue2(&CONTEXT->ssql->sstr.selection, &CONTEXT->values[CONTEXT->value_length - 1]);

		char * value_string = value2string(&CONTEXT->values[CONTEXT->value_length - 1]);
		char* attr_name = (char*)malloc(strlen("date_format(") + strlen((yyvsp[-3].string)) + strlen(",") + strlen(value_string) + strlen(")") + 1);
		memset(attr_name, strlen("date_format(") + strlen((yyvsp[-3].string)) + strlen(",") + strlen(value_string) + strlen(")") + 1, 0);
		
		//strcat(attr_name, "date_format(");
		strcpy(attr_name, "date_format(");
		strcat(attr_name, (yyvsp[-3].string));
		strcat(attr_name, ",");
		strcat(attr_name, value_string);
		strcat(attr_name, ")");
		strcat(attr_name, "\0");

		selects_modify_alias_name(&CONTEXT->ssql->sstr.selection, attr_name);
		printf("func name %s\n", attr_name);
	}
#line 2490 "yacc_sql.tab.c"
    break;

  case 90:
#line 704 "yacc_sql.y"
                                                                {
		selects_append_funcop(&CONTEXT->ssql->sstr.selection, LENGTH_OP);
		selects_append_funcvalue2(&CONTEXT->ssql->sstr.selection, 0);

		//char* attr_name = (char*)malloc(strlen("length(") + strlen($3) + strlen(")") + 1);
		//memset(attr_name, strlen("length(") + strlen($3) + strlen(")") + 1, 0);

		//strcat(attr_name, "length(");
		//strcat(attr_name, $3);
		//strcat(attr_name, ")");
		//strcat(attr_name, "\0");

		selects_modify_alias_name(&CONTEXT->ssql->sstr.selection, (yyvsp[0].string));
		//printf("func name %s\n", attr_name);
	}
#line 2510 "yacc_sql.tab.c"
    break;

  case 91:
#line 719 "yacc_sql.y"
                                                                           {
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

		selects_modify_alias_name(&CONTEXT->ssql->sstr.selection, (yyvsp[0].string));
		//printf("func name %s\n", attr_name);
	}
#line 2534 "yacc_sql.tab.c"
    break;

  case 92:
#line 738 "yacc_sql.y"
                                                                                 {
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

		selects_modify_alias_name(&CONTEXT->ssql->sstr.selection, (yyvsp[0].string));
		//printf("func name %s\n", attr_name);
	}
#line 2557 "yacc_sql.tab.c"
    break;

  case 93:
#line 760 "yacc_sql.y"
              {
		RelAttr attr;
		attr.relation_name = NULL;
		attr.attribute_name = NULL;
		attr.alias_name = NULL;    
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_funcvalue1(&CONTEXT->ssql->sstr.selection, &CONTEXT->values[CONTEXT->value_length - 1]);

		(yyval.string) = value2string(&CONTEXT->values[CONTEXT->value_length - 1]);
	}
#line 2572 "yacc_sql.tab.c"
    break;

  case 94:
#line 770 "yacc_sql.y"
             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[0].string));
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_funcvalue1(&CONTEXT->ssql->sstr.selection, 0);
		(yyval.string) = (yyvsp[0].string);
		
	}
#line 2585 "yacc_sql.tab.c"
    break;

  case 95:
#line 778 "yacc_sql.y"
                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_funcvalue1(&CONTEXT->ssql->sstr.selection, NULL);

		(yyval.string) = (char*)malloc(strlen((yyvsp[-2].string)) + 1 + strlen((yyvsp[0].string)));
		strcat((yyval.string), (yyvsp[-2].string));
		strcat((yyval.string), ".");
		strcat((yyval.string), (yyvsp[0].string));
	}
#line 2601 "yacc_sql.tab.c"
    break;

  case 96:
#line 800 "yacc_sql.y"
                                                          {
		// RelAttr attr;
		// relation_attr_init(&attr, NULL, $3);
		// printf("aggregation: get a attr %s\n", $3);
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		// selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		// CONTEXT->aggregation_num++;	
	}
#line 2614 "yacc_sql.tab.c"
    break;

  case 98:
#line 811 "yacc_sql.y"
                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		printf("aggregation: get a attr *\n");
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
#line 2628 "yacc_sql.tab.c"
    break;

  case 99:
#line 820 "yacc_sql.y"
                           {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		printf("aggregation: get a attr %s\n", (yyvsp[-1].string));
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
#line 2642 "yacc_sql.tab.c"
    break;

  case 100:
#line 829 "yacc_sql.y"
                                  {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		printf("aggregation: get a attr %s\n", (yyvsp[-3].string));
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
#line 2656 "yacc_sql.tab.c"
    break;

  case 101:
#line 838 "yacc_sql.y"
                                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), "*");
		printf("aggregation: get a attr %s\n", (yyvsp[-3].string));
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
#line 2670 "yacc_sql.tab.c"
    break;

  case 103:
#line 850 "yacc_sql.y"
                                   {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		printf("aggregation: get a attr *\n");
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2682 "yacc_sql.tab.c"
    break;

  case 104:
#line 857 "yacc_sql.y"
                                 {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		printf("aggregation: get a attr %s\n", (yyvsp[-1].string));
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2694 "yacc_sql.tab.c"
    break;

  case 105:
#line 864 "yacc_sql.y"
                                        {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		printf("aggregation: get a attr %s\n", (yyvsp[-3].string));
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2706 "yacc_sql.tab.c"
    break;

  case 106:
#line 871 "yacc_sql.y"
                                          {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), "*");
		printf("aggregation: get a attr %s\n", (yyvsp[-3].string));
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2718 "yacc_sql.tab.c"
    break;

  case 107:
#line 881 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = COUNT_OP; }
#line 2724 "yacc_sql.tab.c"
    break;

  case 108:
#line 882 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = AVG_OP; }
#line 2730 "yacc_sql.tab.c"
    break;

  case 109:
#line 883 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = MAX_OP; }
#line 2736 "yacc_sql.tab.c"
    break;

  case 110:
#line 884 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = MIN_OP; }
#line 2742 "yacc_sql.tab.c"
    break;

  case 111:
#line 885 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = SUM_OP; }
#line 2748 "yacc_sql.tab.c"
    break;

  case 113:
#line 889 "yacc_sql.y"
                                                  {
		if (CONTEXT->last_aggregation_seqno == 0) {
			CONTEXT->last_aggregation_seqno = CONTEXT->aggregation_num;
		}		
		CONTEXT->ssql->sstr.selection.aggregation_alias[CONTEXT->last_aggregation_seqno-1] = NULL;
		CONTEXT->last_aggregation_seqno--;
	}
#line 2760 "yacc_sql.tab.c"
    break;

  case 114:
#line 896 "yacc_sql.y"
                                                               {
		if (CONTEXT->last_aggregation_seqno == 0) {
			CONTEXT->last_aggregation_seqno = CONTEXT->aggregation_num;
		}		
		CONTEXT->ssql->sstr.selection.aggregation_alias[CONTEXT->last_aggregation_seqno-1] = (yyvsp[-1].string);
		CONTEXT->last_aggregation_seqno--;
	}
#line 2772 "yacc_sql.tab.c"
    break;

  case 115:
#line 903 "yacc_sql.y"
                               {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2782 "yacc_sql.tab.c"
    break;

  case 116:
#line 908 "yacc_sql.y"
                            {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2792 "yacc_sql.tab.c"
    break;

  case 117:
#line 913 "yacc_sql.y"
                                    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2802 "yacc_sql.tab.c"
    break;

  case 118:
#line 918 "yacc_sql.y"
                                      {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2812 "yacc_sql.tab.c"
    break;

  case 120:
#line 926 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 2824 "yacc_sql.tab.c"
    break;

  case 121:
#line 933 "yacc_sql.y"
                                      {
		printf("                     %s\n", (yyvsp[-1].string));
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-3].string));
			attr.alias_name = (yyvsp[-1].string);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 2838 "yacc_sql.tab.c"
    break;

  case 122:
#line 943 "yacc_sql.y"
                                    {
		
		}
#line 2846 "yacc_sql.tab.c"
    break;

  case 123:
#line 948 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 2858 "yacc_sql.tab.c"
    break;

  case 124:
#line 955 "yacc_sql.y"
                                             {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-5].string), (yyvsp[-3].string));
			attr.alias_name = (yyvsp[-1].string);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 2871 "yacc_sql.tab.c"
    break;

  case 125:
#line 963 "yacc_sql.y"
                                      {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2881 "yacc_sql.tab.c"
    break;

  case 126:
#line 968 "yacc_sql.y"
                                                   {

	}
#line 2889 "yacc_sql.tab.c"
    break;

  case 128:
#line 977 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string), NULL);
		  }
#line 2897 "yacc_sql.tab.c"
    break;

  case 129:
#line 980 "yacc_sql.y"
                                     {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-3].string), (yyvsp[-1].string));
		  }
#line 2905 "yacc_sql.tab.c"
    break;

  case 130:
#line 983 "yacc_sql.y"
                                         {
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string), NULL);
	}
#line 2913 "yacc_sql.tab.c"
    break;

  case 131:
#line 986 "yacc_sql.y"
                                                      {
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-4].string), (yyvsp[-2].string));
	}
#line 2921 "yacc_sql.tab.c"
    break;

  case 133:
#line 993 "yacc_sql.y"
                                      {

	}
#line 2929 "yacc_sql.tab.c"
    break;

  case 135:
#line 999 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2937 "yacc_sql.tab.c"
    break;

  case 137:
#line 1006 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
				if (CONTEXT->last_conditino_seqno == 0) {
					CONTEXT->last_conditino_seqno = CONTEXT->condition_length;
				}
				CONTEXT->conditions[CONTEXT->last_conditino_seqno-1].is_and = 1;
				CONTEXT->last_conditino_seqno--;
				printf("get an and condition: seqno %d\n", CONTEXT->last_conditino_seqno);
			}
#line 2951 "yacc_sql.tab.c"
    break;

  case 138:
#line 1015 "yacc_sql.y"
                                  {
				if (CONTEXT->last_conditino_seqno == 0) {
					CONTEXT->last_conditino_seqno = CONTEXT->condition_length;
				}
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
				CONTEXT->conditions[CONTEXT->last_conditino_seqno-1].is_and = 0;
				CONTEXT->last_conditino_seqno--;
				printf("get an or condition: seqno %d\n", CONTEXT->last_conditino_seqno);
			}
#line 2965 "yacc_sql.tab.c"
    break;

  case 139:
#line 1027 "yacc_sql.y"
                                               {
		FuncAttrCon* ff = (FuncAttrCon*)malloc(sizeof(FuncAttrCon));
		ff->funcop = LENGTH_OP;
		ff->args_value.type = 0;
		ff->attr = (yyvsp[-1].relAttr);
		if ((yyvsp[-1].relAttr) == NULL) {
			ff->value = CONTEXT->values[CONTEXT->value_length - 1];
		} else {
			ff->value.type = UNDEFINED;
		}
		(yyval.FuncAttrCon1) = ff;
		
	}
#line 2983 "yacc_sql.tab.c"
    break;

  case 140:
#line 1040 "yacc_sql.y"
                                                            {
		FuncAttrCon* ff = (FuncAttrCon*)malloc(sizeof(FuncAttrCon));
		ff->funcop = ROUND_OP;
		ff->args_value = CONTEXT->values[CONTEXT->value_length - 1];
		ff->attr = (yyvsp[-3].relAttr);
		if ((yyvsp[-3].relAttr) == NULL) {
			ff->value = CONTEXT->values[CONTEXT->value_length - 2];
		} else {
			ff->value.type = UNDEFINED;
		}
		(yyval.FuncAttrCon1) = ff;
	}
#line 3000 "yacc_sql.tab.c"
    break;

  case 141:
#line 1052 "yacc_sql.y"
                                                                  {
		FuncAttrCon* ff = (FuncAttrCon*)malloc(sizeof(FuncAttrCon));
		ff->funcop = DATE_FORMAT_OP;
		ff->args_value = CONTEXT->values[CONTEXT->value_length - 1];
		ff->attr = (yyvsp[-3].relAttr);
		if ((yyvsp[-3].relAttr) == NULL) {
			ff->value = CONTEXT->values[CONTEXT->value_length - 2];
		} else {
			ff->value.type = UNDEFINED;
		}
		(yyval.FuncAttrCon1) = ff;
	}
#line 3017 "yacc_sql.tab.c"
    break;

  case 142:
#line 1066 "yacc_sql.y"
              {
		(yyval.relAttr) = NULL;
	}
#line 3025 "yacc_sql.tab.c"
    break;

  case 143:
#line 1069 "yacc_sql.y"
             {
		RelAttr* attr = (RelAttr*)malloc(sizeof(RelAttr));
		relation_attr_init(attr, NULL, (yyvsp[0].string));
		(yyval.relAttr) = attr;
		
	}
#line 3036 "yacc_sql.tab.c"
    break;

  case 144:
#line 1075 "yacc_sql.y"
                    {
		RelAttr* attr = (RelAttr*)malloc(sizeof(RelAttr));
		relation_attr_init(attr, (yyvsp[-2].string), (yyvsp[0].string));
		(yyval.relAttr) = attr;
	}
#line 3046 "yacc_sql.tab.c"
    break;

  case 145:
#line 1084 "yacc_sql.y"
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
#line 3072 "yacc_sql.tab.c"
    break;

  case 146:
#line 1106 "yacc_sql.y"
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
#line 3097 "yacc_sql.tab.c"
    break;

  case 147:
#line 1128 "yacc_sql.y"
        {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, Comparison, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 1, 0, 0, &right_attr, NULL, NULL, NULL, 0);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 3113 "yacc_sql.tab.c"
    break;

  case 148:
#line 1141 "yacc_sql.y"
        {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
		FuncAttrCon* right_func_attr = (yyvsp[0].FuncAttrCon1);
		Condition condition;
		condition_init_func(&condition, Comparison, CONTEXT->comp, 
							1, 0, &left_attr, NULL, NULL,   
		                    0, 0, 0, NULL, NULL, NULL, NULL, 0,  
						    NULL, right_func_attr);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		printf("a\n");
	}
#line 3130 "yacc_sql.tab.c"
    break;

  case 149:
#line 1155 "yacc_sql.y"
        {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-2].string), (yyvsp[-4].string));
		FuncAttrCon* right_func_attr = (yyvsp[-2].string);
		Condition condition;
		condition_init_func(&condition, Comparison, CONTEXT->comp, 
							1, 0, &left_attr, NULL, NULL,  
							0, 0, 0, NULL, NULL, NULL, NULL, 0,  
							NULL, right_func_attr);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		printf("b\n");
	}
#line 3147 "yacc_sql.tab.c"
    break;

  case 150:
#line 1169 "yacc_sql.y"
        {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
		FuncAttrCon* right_func_attr = (yyvsp[0].FuncAttrCon1);

		Condition condition;
		condition_init_func(&condition, Comparison, CONTEXT->comp, 
							0, 0, NULL, left_value, NULL, 
							1, 0, 0, NULL, NULL, NULL, NULL, 0,  
							NULL, right_func_attr);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		printf("c\n");
	}
#line 3164 "yacc_sql.tab.c"
    break;

  case 151:
#line 1183 "yacc_sql.y"
        {
		FuncAttrCon* left_func_attr = (yyvsp[-2].FuncAttrCon1);
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, (yyvsp[0].string));
		Condition condition;
		condition_init_func(&condition, Comparison, CONTEXT->comp, 1, 0, NULL, NULL, NULL, 
							1, 0, 0, &right_attr, NULL, NULL, NULL, 0,  
							left_func_attr, NULL);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		printf("d\n");
	}
#line 3180 "yacc_sql.tab.c"
    break;

  case 152:
#line 1196 "yacc_sql.y"
        {	
		FuncAttrCon* left_func_attr = (yyvsp[-4].FuncAttrCon1);
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, (yyvsp[-2].string));
		Condition condition;
		condition_init_func(&condition, Comparison, CONTEXT->comp, 1, 0, NULL, NULL, NULL, 
							1, 0, 0, &right_attr, NULL, NULL, NULL, 0,  
							left_func_attr, NULL);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		printf("e\n");
	}
#line 3196 "yacc_sql.tab.c"
    break;

  case 153:
#line 1209 "yacc_sql.y"
        {
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
		FuncAttrCon* left_func_attr = (yyvsp[-2].FuncAttrCon1);

		Condition condition;
		condition_init_func(&condition, Comparison, CONTEXT->comp, 1, 0, NULL, NULL, NULL, 
							0, 0, 0, NULL, right_value, NULL, NULL, 0,
							left_func_attr, NULL);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		printf("f\n");
	}
#line 3212 "yacc_sql.tab.c"
    break;

  case 154:
#line 1221 "yacc_sql.y"
        {
		FuncAttrCon* left_func_attr = (yyvsp[-2].FuncAttrCon1);
		FuncAttrCon* right_func_attr = (yyvsp[0].FuncAttrCon1);
		Condition condition;
		condition_init_func(&condition, Comparison, CONTEXT->comp, 1, 0, NULL, NULL, NULL, 
							1, 0, 0, NULL, NULL, NULL, NULL, 0,   
							left_func_attr, right_func_attr);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		printf("g\n");
	}
#line 3227 "yacc_sql.tab.c"
    break;

  case 155:
#line 1232 "yacc_sql.y"
        {
		FuncAttrCon* left_func_attr = (yyvsp[-2].FuncAttrCon1);
		Condition condition;
		condition_init_func(&condition, Contain, CONTEXT->comp, 
							1, 0, NULL, NULL, NULL, 
							0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0,
							left_func_attr, NULL);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		printf("h\n");
	}
#line 3242 "yacc_sql.tab.c"
    break;

  case 156:
#line 1243 "yacc_sql.y"
        {
		FuncAttrCon* left_func_attr = (yyvsp[-3].FuncAttrCon1);
		Condition condition;
		condition_init_func(&condition, NotContain, CONTEXT->comp, 
							1, 0, NULL, NULL, NULL, 
							0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0,
							left_func_attr, NULL);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		printf("i\n");
	}
#line 3257 "yacc_sql.tab.c"
    break;

  case 157:
#line 1254 "yacc_sql.y"
        {
		FuncAttrCon* left_func_attr = (yyvsp[-5].FuncAttrCon1);
		Condition condition;
		condition_init_func(&condition, Contain, CONTEXT->comp, 
							1, 0, NULL, NULL, NULL, 
							0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, CONTEXT->values, CONTEXT->value_length,
							left_func_attr, NULL);
		CONTEXT->value_length = 0;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		printf("j\n");
	}
#line 3273 "yacc_sql.tab.c"
    break;

  case 158:
#line 1266 "yacc_sql.y"
        {
		FuncAttrCon* left_func_attr = (yyvsp[-6].FuncAttrCon1);
		Condition condition;
		condition_init_func(&condition, NotContain, CONTEXT->comp, 
							1, 0, NULL, NULL, NULL, 
							0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, CONTEXT->values, CONTEXT->value_length,
							left_func_attr, NULL);
		CONTEXT->value_length = 0;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		printf("k\n");
	}
#line 3289 "yacc_sql.tab.c"
    break;

  case 159:
#line 1280 "yacc_sql.y"
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
#line 3314 "yacc_sql.tab.c"
    break;

  case 160:
#line 1301 "yacc_sql.y"
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
#line 3339 "yacc_sql.tab.c"
    break;

  case 161:
#line 1322 "yacc_sql.y"
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
#line 3366 "yacc_sql.tab.c"
    break;

  case 162:
#line 1345 "yacc_sql.y"
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
#line 3391 "yacc_sql.tab.c"
    break;

  case 163:
#line 1366 "yacc_sql.y"
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
#line 3416 "yacc_sql.tab.c"
    break;

  case 164:
#line 1387 "yacc_sql.y"
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
#line 3440 "yacc_sql.tab.c"
    break;

  case 165:
#line 1406 "yacc_sql.y"
                          {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

		Condition condition;
		condition_init(&condition, Contain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		
	}
#line 3454 "yacc_sql.tab.c"
    break;

  case 166:
#line 1415 "yacc_sql.y"
                              {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-3].string));

		Condition condition;
		condition_init(&condition, NotContain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 3468 "yacc_sql.tab.c"
    break;

  case 167:
#line 1424 "yacc_sql.y"
                                 {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));

		Condition condition;
		condition_init(&condition, Contain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		
	}
#line 3482 "yacc_sql.tab.c"
    break;

  case 168:
#line 1433 "yacc_sql.y"
                                     {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-5].string), (yyvsp[-3].string));

		Condition condition;
		condition_init(&condition, NotContain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 3496 "yacc_sql.tab.c"
    break;

  case 169:
#line 1442 "yacc_sql.y"
                                               {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-5].string));

		Condition condition;
		condition_init(&condition, Contain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, 
			CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length = 0;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 3512 "yacc_sql.tab.c"
    break;

  case 170:
#line 1453 "yacc_sql.y"
                                                   {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-6].string));

		Condition condition;
		condition_init(&condition, NotContain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, 
			CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length = 0;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 3528 "yacc_sql.tab.c"
    break;

  case 171:
#line 1464 "yacc_sql.y"
                                                      {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-7].string), (yyvsp[-5].string));

		Condition condition;
		condition_init(&condition, Contain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, 
			CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length = 0;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 3544 "yacc_sql.tab.c"
    break;

  case 172:
#line 1475 "yacc_sql.y"
                                                          {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-8].string), (yyvsp[-6].string));

		Condition condition;
		condition_init(&condition, NotContain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, 
			CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length = 0;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 3560 "yacc_sql.tab.c"
    break;

  case 173:
#line 1486 "yacc_sql.y"
                                    {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));

		Condition condition;
		condition_init(&condition, Comparison, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 3573 "yacc_sql.tab.c"
    break;

  case 174:
#line 1494 "yacc_sql.y"
                             {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

		Condition condition;
		condition_init(&condition, Comparison, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 3586 "yacc_sql.tab.c"
    break;

  case 175:
#line 1502 "yacc_sql.y"
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
#line 3615 "yacc_sql.tab.c"
    break;

  case 176:
#line 1526 "yacc_sql.y"
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
#line 3643 "yacc_sql.tab.c"
    break;

  case 177:
#line 1549 "yacc_sql.y"
                                    {
		Condition condition;
		condition_init(&condition, Comparison, CONTEXT->comp, 0, 1, NULL, NULL, &CONTEXT->left_sub_query->sstr.selection, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 3654 "yacc_sql.tab.c"
    break;

  case 178:
#line 1555 "yacc_sql.y"
                           {

		Condition condition;
		condition_init(&condition, Exists, CONTEXT->comp, 0, 0, NULL, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 3666 "yacc_sql.tab.c"
    break;

  case 179:
#line 1562 "yacc_sql.y"
                               {

		Condition condition;
		condition_init(&condition, NotExists, CONTEXT->comp, 0, 0, NULL, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 3678 "yacc_sql.tab.c"
    break;

  case 180:
#line 1573 "yacc_sql.y"
        {
		selects_set_group(&CONTEXT->ssql->sstr.selection, 0);
	}
#line 3686 "yacc_sql.tab.c"
    break;

  case 181:
#line 1576 "yacc_sql.y"
                                      {
		selects_set_group(&CONTEXT->ssql->sstr.selection, 1);
	}
#line 3694 "yacc_sql.tab.c"
    break;

  case 182:
#line 1582 "yacc_sql.y"
                                   {
		// 递归。最新秒杀升级版。
	}
#line 3702 "yacc_sql.tab.c"
    break;

  case 184:
#line 1588 "yacc_sql.y"
                                           {
		// 递归。最新秒杀升级版。
	}
#line 3710 "yacc_sql.tab.c"
    break;

  case 185:
#line 1595 "yacc_sql.y"
           {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[0].string));
		selects_append_groupattr(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 3720 "yacc_sql.tab.c"
    break;

  case 186:
#line 1600 "yacc_sql.y"
                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
		selects_append_groupattr(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 3730 "yacc_sql.tab.c"
    break;

  case 187:
#line 1608 "yacc_sql.y"
        {
		selects_set_having(&CONTEXT->ssql->sstr.selection, 0);
	}
#line 3738 "yacc_sql.tab.c"
    break;

  case 188:
#line 1611 "yacc_sql.y"
                                                        {
		// 递归
		selects_set_having(&CONTEXT->ssql->sstr.selection, 1);
	}
#line 3747 "yacc_sql.tab.c"
    break;

  case 190:
#line 1618 "yacc_sql.y"
                                                      {
		// 递归
	}
#line 3755 "yacc_sql.tab.c"
    break;

  case 192:
#line 1628 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, COUNT_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3767 "yacc_sql.tab.c"
    break;

  case 193:
#line 1635 "yacc_sql.y"
                                               {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		Having_Condition condition;
		having_condition_init(&condition, COUNT_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3779 "yacc_sql.tab.c"
    break;

  case 194:
#line 1642 "yacc_sql.y"
                                                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, COUNT_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3791 "yacc_sql.tab.c"
    break;

  case 195:
#line 1649 "yacc_sql.y"
                                                      {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), "*");
		Having_Condition condition;
		having_condition_init(&condition, COUNT_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3803 "yacc_sql.tab.c"
    break;

  case 196:
#line 1656 "yacc_sql.y"
                                           {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, AVG_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3815 "yacc_sql.tab.c"
    break;

  case 197:
#line 1663 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		Having_Condition condition;
		having_condition_init(&condition, AVG_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3827 "yacc_sql.tab.c"
    break;

  case 198:
#line 1670 "yacc_sql.y"
                                                  {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, AVG_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3839 "yacc_sql.tab.c"
    break;

  case 199:
#line 1677 "yacc_sql.y"
                                                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), "*");
		Having_Condition condition;
		having_condition_init(&condition, AVG_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3851 "yacc_sql.tab.c"
    break;

  case 200:
#line 1684 "yacc_sql.y"
                                           {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, MAX_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3863 "yacc_sql.tab.c"
    break;

  case 201:
#line 1691 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		Having_Condition condition;
		having_condition_init(&condition, MAX_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3875 "yacc_sql.tab.c"
    break;

  case 202:
#line 1698 "yacc_sql.y"
                                                  {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, MAX_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3887 "yacc_sql.tab.c"
    break;

  case 203:
#line 1705 "yacc_sql.y"
                                                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), "*");
		Having_Condition condition;
		having_condition_init(&condition, MAX_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3899 "yacc_sql.tab.c"
    break;

  case 204:
#line 1712 "yacc_sql.y"
                                           {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, MIN_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3911 "yacc_sql.tab.c"
    break;

  case 205:
#line 1719 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		Having_Condition condition;
		having_condition_init(&condition, MIN_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3923 "yacc_sql.tab.c"
    break;

  case 206:
#line 1726 "yacc_sql.y"
                                                  {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, MIN_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3935 "yacc_sql.tab.c"
    break;

  case 207:
#line 1733 "yacc_sql.y"
                                                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), "*");
		Having_Condition condition;
		having_condition_init(&condition, MIN_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3947 "yacc_sql.tab.c"
    break;

  case 208:
#line 1740 "yacc_sql.y"
                                           {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, SUM_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3959 "yacc_sql.tab.c"
    break;

  case 209:
#line 1747 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "$3");
		Having_Condition condition;
		having_condition_init(&condition, SUM_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3971 "yacc_sql.tab.c"
    break;

  case 210:
#line 1754 "yacc_sql.y"
                                                  {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, SUM_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3983 "yacc_sql.tab.c"
    break;

  case 211:
#line 1761 "yacc_sql.y"
                                                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), "*");
		Having_Condition condition;
		having_condition_init(&condition, SUM_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3995 "yacc_sql.tab.c"
    break;

  case 212:
#line 1771 "yacc_sql.y"
        {
		selects_set_order(&CONTEXT->ssql->sstr.selection, 0);
	}
#line 4003 "yacc_sql.tab.c"
    break;

  case 213:
#line 1774 "yacc_sql.y"
                              {
		selects_set_order(&CONTEXT->ssql->sstr.selection, 1);
	}
#line 4011 "yacc_sql.tab.c"
    break;

  case 214:
#line 1780 "yacc_sql.y"
                               {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
		}
#line 4021 "yacc_sql.tab.c"
    break;

  case 215:
#line 1785 "yacc_sql.y"
                                        {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
		}
#line 4031 "yacc_sql.tab.c"
    break;

  case 216:
#line 1790 "yacc_sql.y"
                                  {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
		}
#line 4041 "yacc_sql.tab.c"
    break;

  case 217:
#line 1795 "yacc_sql.y"
                                         {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
		}
#line 4051 "yacc_sql.tab.c"
    break;

  case 219:
#line 1804 "yacc_sql.y"
                                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
      }
#line 4061 "yacc_sql.tab.c"
    break;

  case 220:
#line 1809 "yacc_sql.y"
                                    {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
      }
#line 4071 "yacc_sql.tab.c"
    break;

  case 221:
#line 1814 "yacc_sql.y"
                                          {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
  	  }
#line 4081 "yacc_sql.tab.c"
    break;

  case 222:
#line 1819 "yacc_sql.y"
                                           {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
  	  }
#line 4091 "yacc_sql.tab.c"
    break;

  case 225:
#line 1832 "yacc_sql.y"
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
#line 4109 "yacc_sql.tab.c"
    break;

  case 226:
#line 1845 "yacc_sql.y"
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
#line 4129 "yacc_sql.tab.c"
    break;

  case 227:
#line 1863 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 4135 "yacc_sql.tab.c"
    break;

  case 228:
#line 1864 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 4141 "yacc_sql.tab.c"
    break;

  case 229:
#line 1865 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 4147 "yacc_sql.tab.c"
    break;

  case 230:
#line 1866 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 4153 "yacc_sql.tab.c"
    break;

  case 231:
#line 1867 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 4159 "yacc_sql.tab.c"
    break;

  case 232:
#line 1868 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 4165 "yacc_sql.tab.c"
    break;

  case 233:
#line 1869 "yacc_sql.y"
             { CONTEXT->comp = LOGICAL_IS; }
#line 4171 "yacc_sql.tab.c"
    break;

  case 234:
#line 1870 "yacc_sql.y"
                 {CONTEXT->comp = LOGICAL_IS_NOT; }
#line 4177 "yacc_sql.tab.c"
    break;

  case 235:
#line 1871 "yacc_sql.y"
               { CONTEXT->comp = LIKE_OP; }
#line 4183 "yacc_sql.tab.c"
    break;

  case 236:
#line 1872 "yacc_sql.y"
                   { CONTEXT->comp = NOT_LIKE_OP; }
#line 4189 "yacc_sql.tab.c"
    break;

  case 237:
#line 1877 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 4198 "yacc_sql.tab.c"
    break;


#line 4202 "yacc_sql.tab.c"

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
#line 1882 "yacc_sql.y"

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
