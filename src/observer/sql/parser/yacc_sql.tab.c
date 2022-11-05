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
#define YYLAST   620

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  79
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  67
/* YYNRULES -- Number of rules.  */
#define YYNRULES  240
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  558

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
     699,   719,   734,   753,   760,   782,   792,   800,   822,   831,
     833,   842,   851,   860,   871,   872,   879,   886,   893,   903,
     904,   905,   906,   907,   909,   911,   918,   925,   930,   935,
     940,   946,   948,   955,   965,   970,   977,   985,   990,   997,
     999,  1002,  1005,  1008,  1013,  1015,  1019,  1021,  1026,  1028,
    1037,  1049,  1062,  1075,  1087,  1101,  1104,  1110,  1118,  1140,
    1162,  1175,  1190,  1205,  1220,  1234,  1248,  1261,  1273,  1285,
    1297,  1310,  1325,  1346,  1367,  1390,  1411,  1432,  1452,  1461,
    1470,  1479,  1488,  1499,  1510,  1521,  1532,  1540,  1548,  1572,
    1595,  1601,  1608,  1619,  1622,  1628,  1633,  1634,  1641,  1646,
    1654,  1657,  1663,  1664,  1673,  1674,  1681,  1688,  1695,  1702,
    1709,  1716,  1723,  1730,  1737,  1744,  1751,  1758,  1765,  1772,
    1779,  1786,  1793,  1800,  1807,  1817,  1820,  1826,  1831,  1836,
    1841,  1848,  1850,  1855,  1860,  1865,  1872,  1873,  1878,  1891,
    1909,  1910,  1911,  1912,  1913,  1914,  1915,  1916,  1917,  1918,
    1922
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

#define YYPACT_NINF (-424)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-86)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -424,   310,  -424,    40,   151,   215,   -60,   224,    56,    25,
      42,    49,   137,   162,   170,   195,   201,   171,  -424,  -424,
    -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,
    -424,  -424,  -424,  -424,  -424,  -424,   212,  -424,   149,  -424,
     217,   169,   174,  -424,  -424,  -424,  -424,  -424,   243,   283,
     286,    24,    80,   240,   287,   112,   296,   314,   325,   319,
    -424,   274,   288,   323,  -424,  -424,  -424,  -424,  -424,   334,
    -424,   343,   302,   372,   374,   146,   146,   146,   332,   -18,
    -424,   322,  -424,   324,  -424,   326,  -424,   320,   333,  -424,
     114,  -424,  -424,   341,   362,   364,   349,   348,   353,   370,
    -424,  -424,  -424,  -424,   386,  -424,  -424,  -424,  -424,   409,
      17,   411,   135,   287,   412,    80,   287,   287,   287,    84,
      19,   287,   112,   412,    98,   415,   417,   440,   428,   125,
     454,   418,   441,   430,  -424,   474,   456,   421,   422,    72,
      72,    65,    65,   115,   423,  -424,  -424,  -424,   424,  -424,
    -424,  -424,  -424,   425,   444,   427,   364,   136,  -424,  -424,
     429,  -424,  -424,   154,   167,  -424,  -424,  -424,  -424,    65,
     482,  -424,   486,   447,   488,   489,   490,   321,   345,   396,
      -5,   345,  -424,    48,   349,   364,   501,   353,   491,  -424,
    -424,  -424,  -424,  -424,   104,   493,  -424,   438,   439,   495,
     496,    80,   287,   287,   287,    84,   442,     8,   452,   287,
     287,   412,   116,   415,   415,   415,   498,   428,   514,   509,
    -424,   486,   413,   413,   413,   448,  -424,  -424,  -424,  -424,
    -424,  -424,   461,   505,  -424,   117,   166,   465,   340,   507,
     256,   378,   125,   125,  -424,     5,  -424,  -424,   441,   521,
     453,   474,   523,   457,  -424,   450,  -424,   458,  -424,  -424,
      72,    72,   459,  -424,  -424,  -424,  -424,   460,  -424,   119,
     364,   468,   473,  -424,  -424,  -424,   173,  -424,  -424,  -424,
    -424,    65,   517,   482,  -424,   518,  -424,   508,  -424,   519,
     309,   520,   431,  -424,    65,  -424,   524,  -424,   510,  -424,
    -424,  -424,   512,  -424,  -424,    65,  -424,   526,   515,  -424,
    -424,    -5,    -5,   516,  -424,  -424,  -424,   540,  -424,  -424,
    -424,   529,  -424,   530,   475,   477,   287,     8,   125,   478,
       8,   473,   479,   492,  -424,   415,   415,   498,  -424,  -424,
    -424,   480,  -424,  -424,    65,    65,   538,   261,   184,   498,
      65,  -424,   483,   484,   498,    65,  -424,   485,  -424,  -424,
     487,  -424,   130,   494,   541,  -424,  -424,  -424,  -424,    -5,
     525,  -424,  -424,   531,   499,   544,   497,  -424,  -424,  -424,
    -424,   547,   548,    65,  -424,   551,   539,  -424,  -424,  -424,
     553,   498,  -424,  -424,   554,   498,  -424,  -424,  -424,  -424,
     530,   569,  -424,     8,   502,   284,  -424,   479,  -424,     9,
    -424,  -424,  -424,   498,    65,  -424,   503,  -424,   556,  -424,
     559,  -424,  -424,  -424,  -424,   561,   562,   563,   564,   565,
     566,   544,   567,   511,  -424,   567,   570,   498,  -424,  -424,
    -424,   175,   185,   196,   202,   204,   284,  -424,  -424,   522,
    -424,    39,  -424,  -424,   571,    16,   572,    23,   573,    27,
     574,    34,   575,    41,   576,   566,    66,   567,   567,  -424,
     345,   206,   345,   345,   213,   345,   345,   214,   345,   345,
     219,   345,   345,   221,   345,  -424,   567,   527,   567,  -424,
    -424,    65,   578,   579,    65,    65,   580,   581,    65,    65,
     583,   584,    65,    65,   585,   586,    65,    65,   587,   588,
      65,  -424,    52,  -424,  -424,   345,   345,  -424,  -424,   345,
     345,  -424,  -424,   345,   345,  -424,  -424,   345,   345,  -424,
    -424,   345,   345,  -424,   567,   567,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,  -424,  -424,  -424,  -424,
    -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424
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
       0,     0,     0,   109,   110,   111,   112,   113,     0,     0,
       0,   121,   121,    74,   121,   114,     0,     0,     0,     0,
      24,     0,     0,     0,    25,    26,    27,    23,    22,     0,
      71,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      86,     0,    77,     0,    75,     0,    80,     0,     0,    83,
      99,    31,    29,     0,     0,   136,     0,     0,     0,     0,
      28,    37,    60,    61,    96,    62,    63,    64,    95,     0,
       0,     0,   121,   121,   114,   121,   121,   121,   121,   129,
     121,   121,   114,   114,   104,   104,     0,     0,     0,     0,
       0,     0,    69,     0,    51,    39,     0,     0,     0,    87,
      89,     0,     0,     0,     0,   122,   124,   128,     0,    79,
      82,    78,    76,     0,     0,     0,   136,     0,   118,   117,
       0,   115,    84,     0,     0,   101,   100,    98,    30,     0,
      56,   229,     0,     0,     0,     0,     0,     0,     0,     0,
     138,     0,    65,     0,     0,   136,     0,     0,     0,    46,
      47,    48,    49,    50,    52,     0,    97,     0,     0,     0,
       0,   121,   121,   121,   121,   129,     0,   129,   183,   121,
     121,   114,   104,   104,   104,   104,    58,     0,     0,     0,
     181,     0,     0,     0,     0,     0,   230,   231,   232,   233,
     234,   235,   236,     0,   238,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   137,     0,    67,    68,    69,     0,
       0,    39,     0,     0,    44,     0,    43,     0,    91,    93,
      88,    90,     0,   125,   127,   123,    81,     0,   130,   134,
     136,     0,   215,   119,   120,   116,     0,   106,   105,   102,
     103,     0,     0,    56,    54,     0,   182,   146,   145,     0,
       0,     0,     0,   237,   229,   168,     0,   239,   150,   148,
     151,   177,   164,   149,   153,   229,   158,     0,   154,   156,
     157,   138,   138,   179,   180,    70,    66,     0,    40,    38,
      45,     0,    53,    35,     0,     0,   121,   129,     0,     0,
     129,   215,     0,     0,    72,   104,   104,    58,    55,    57,
     228,     0,   141,   142,     0,     0,     0,     0,     0,    58,
     229,   169,     0,     0,    58,   229,   159,     0,   139,   140,
       0,   240,    52,     0,     0,    92,    94,   126,   131,   138,
     134,   132,    73,   188,   190,   186,     0,   107,   108,    59,
     147,     0,     0,   229,   170,     0,   163,   165,   152,   176,
       0,    58,   162,   166,     0,    58,   155,   178,    42,    41,
      35,     0,   135,   129,     0,   194,   184,     0,   185,   226,
     216,   143,   144,    58,   229,   171,     0,   172,     0,   160,
       0,    36,    32,   133,   189,     0,     0,     0,     0,     0,
     192,   186,   221,     0,   227,   221,     0,    58,   167,   173,
     161,     0,     0,     0,     0,     0,   194,   191,   187,     0,
     219,   226,   217,   174,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   192,   226,   221,   221,   175,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   193,   221,     0,   221,   220,
     218,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   223,   226,   222,   195,     0,     0,   196,   199,     0,
       0,   200,   203,     0,     0,   204,   207,     0,     0,   208,
     211,     0,     0,   212,   221,   221,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   225,   224,   197,   198,
     201,   202,   205,   206,   209,   210,   213,   214
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,  -424,
    -424,  -424,  -424,  -424,  -424,   182,  -424,  -424,   335,   419,
    -424,  -424,  -424,   245,  -424,   391,   327,  -322,   -75,  -424,
    -424,   432,   361,  -424,   392,  -424,   -47,   534,   266,   -37,
    -424,  -108,  -424,  -100,   -34,  -198,   244,  -146,  -281,  -225,
     131,  -218,  -424,  -424,   186,   208,  -424,   148,   172,   289,
    -424,  -355,  -423,  -136,  -424,  -175,  -424
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    40,   364,    30,    31,   188,   135,
     321,   194,   136,   256,    32,   170,   218,   282,   178,    33,
      34,   132,   185,    35,    36,    53,    81,    54,   109,    55,
     126,   165,    56,    89,    82,   156,   330,   130,   244,   179,
     289,   180,   272,   374,   408,   375,   406,   447,   430,   334,
     410,   450,   435,   181,   219,   236,    37
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     108,   108,   108,   238,   241,    83,   245,   268,    88,   270,
     208,   300,    57,   304,   147,   379,   310,   166,    84,   432,
      86,   171,   161,   162,   311,   312,   153,   390,   468,   242,
     358,   359,   394,   470,   140,   141,   220,    78,   433,   249,
     473,   114,    78,   488,   476,   471,    38,   247,   157,   467,
     122,   479,   474,    79,   115,    61,   477,   116,   482,    60,
     243,   154,   534,   480,   171,   144,   199,   200,   148,   418,
     483,   434,   155,   420,    62,   160,   486,   313,   145,   146,
     452,   149,   150,   151,   152,   286,   158,   159,   402,   535,
      80,   436,   197,   198,   216,   487,   -85,   295,    78,    39,
     301,   434,   153,   306,   277,   278,   279,   280,   246,   314,
     369,   275,   489,   490,   434,   454,   163,   348,   102,   103,
     253,    63,   105,   388,   331,   106,   107,   164,   434,   368,
      87,   511,   371,   513,   163,   102,   103,   154,    80,   105,
      64,   171,   106,   107,   -85,   276,    80,   288,   288,   288,
      80,   254,   -85,    78,   262,   328,   -85,    41,   267,    42,
     351,   299,   255,   303,   143,    65,   309,   263,   264,   265,
     266,   356,   296,    66,   297,   273,   274,   398,    80,   546,
     547,   172,   171,   173,   -85,    80,   124,   201,   255,   125,
     202,   -85,   174,   175,   176,   102,   103,   177,    67,   105,
     171,    80,   106,   107,    68,   423,   337,   -85,   209,    69,
     384,   210,   389,   324,   325,    70,   102,   103,   104,   349,
     105,    71,   329,   106,   107,    72,   212,   377,   378,   213,
     354,    58,    59,   174,   175,   176,   102,   103,   298,   214,
     105,    73,   215,   106,   107,   335,    74,   455,   336,   415,
     456,   174,   175,   176,   102,   103,   386,   457,   105,    75,
     458,   106,   107,    43,    44,    45,    46,    47,   459,   381,
     382,   460,    85,   387,   461,   391,   463,   462,   492,   464,
     395,   493,    48,    49,    50,   496,   500,    51,   497,   501,
      52,   504,   367,   508,   505,   491,   509,   494,   495,    76,
     498,   499,    77,   502,   503,    78,   506,   507,   413,   510,
       2,   307,    90,   297,     3,     4,   385,    91,   297,     5,
       6,     7,     8,     9,    10,    11,   343,   344,    92,    12,
      13,    14,   425,   426,   427,   428,   429,    15,    16,   437,
     536,   537,   110,   111,   538,   539,    94,    17,   540,   541,
     225,    93,   542,   543,   290,   291,   544,   545,    96,    98,
      95,   226,   227,   228,   229,   230,   231,   232,    43,    44,
      45,    46,    47,    97,    99,   100,   233,   101,   234,   235,
      43,    44,    45,    46,    47,   226,   227,   228,   229,   230,
     231,   232,   120,   128,   117,   121,   118,   129,   119,    48,
      49,    50,   234,   237,   112,   123,   137,   174,   175,   176,
     102,   103,   302,   127,   105,   138,   514,   106,   107,   517,
     518,   131,   133,   521,   522,   134,   139,   525,   526,   142,
      87,   529,   530,   163,   167,   533,   226,   227,   228,   229,
     230,   231,   232,   168,   169,   174,   175,   176,   102,   103,
     308,   239,   105,   234,   240,   106,   107,   182,   183,   184,
     186,   548,   549,   550,   551,   552,   553,   554,   555,   556,
     557,   226,   227,   228,   229,   230,   231,   232,   189,   190,
     191,   192,   193,   102,   103,   287,   346,   105,   234,   347,
     106,   107,   187,   195,   196,   203,   204,   205,   206,   207,
     217,   211,   171,   221,   222,   223,   224,   250,   252,   257,
     258,   259,   260,   261,   269,   271,   281,   284,     5,   293,
     292,   294,   297,   305,   316,   317,   319,   320,   322,   332,
     323,   326,   327,   333,   338,   340,   342,   341,   345,   352,
     350,   353,   355,   361,   357,   360,   362,   365,   363,   366,
     370,   373,   380,   376,   383,   392,   393,   396,   401,   397,
     404,   328,   407,   405,   411,   412,   400,   414,   416,   409,
     417,   419,   422,   439,   424,   438,   440,   441,   442,   443,
     444,   445,   421,   451,   446,   449,   318,   453,   469,   472,
     475,   478,   481,   484,   466,   515,   516,   519,   520,   512,
     523,   524,   527,   528,   531,   532,   251,   399,   283,   315,
     339,   285,   113,   485,   403,   431,   248,   448,   465,     0,
     372
};

static const yytype_int16 yycheck[] =
{
      75,    76,    77,   178,   179,    52,   181,   205,    55,   207,
     156,   236,    72,   238,   114,   337,   241,   125,    52,    10,
      54,    16,   122,   123,   242,   243,    18,   349,   451,    34,
     311,   312,   354,    17,    17,    18,   172,    18,    29,   185,
      17,    78,    18,   466,    17,    29,     6,   183,    29,    10,
      87,    17,    29,    29,    72,    30,    29,    75,    17,     3,
      65,    53,    10,    29,    16,   112,   141,   142,   115,   391,
      29,    62,   119,   395,    32,   122,    10,    72,   112,   113,
     435,   115,   116,   117,   118,   221,   120,   121,   369,   512,
      66,   413,   139,   140,   169,    29,    72,   233,    18,    59,
     236,    62,    18,   239,   212,   213,   214,   215,   183,   245,
     328,   211,   467,   468,    62,   437,    18,   292,    70,    71,
      16,    72,    74,   348,   270,    77,    78,    29,    62,   327,
      18,   486,   330,   488,    18,    70,    71,    53,    66,    74,
       3,    16,    77,    78,    72,    29,    66,   222,   223,   224,
      66,    47,    72,    18,   201,    36,    72,     6,   205,     8,
     296,   236,    58,   238,    29,     3,   241,   201,   202,   203,
     204,   307,    55,     3,    57,   209,   210,    47,    66,   534,
     535,    56,    16,    58,    72,    66,    72,    72,    58,    75,
      75,    72,    67,    68,    69,    70,    71,    72,     3,    74,
      16,    66,    77,    78,     3,   403,   281,    72,    72,    38,
     346,    75,   348,   260,   261,     3,    70,    71,    72,   294,
      74,    72,   269,    77,    78,     8,    72,   335,   336,    75,
     305,     7,     8,    67,    68,    69,    70,    71,    72,    72,
      74,    72,    75,    77,    78,    72,    72,    72,    75,   385,
      75,    67,    68,    69,    70,    71,    72,    72,    74,    16,
      75,    77,    78,    48,    49,    50,    51,    52,    72,   344,
     345,    75,    32,   348,    72,   350,    72,    75,    72,    75,
     355,    75,    67,    68,    69,    72,    72,    72,    75,    75,
      75,    72,   326,    72,    75,   470,    75,   472,   473,    16,
     475,   476,    16,   478,   479,    18,   481,   482,   383,   484,
       0,    55,    16,    57,     4,     5,    55,     3,    57,     9,
      10,    11,    12,    13,    14,    15,    17,    18,     3,    19,
      20,    21,    48,    49,    50,    51,    52,    27,    28,   414,
     515,   516,    76,    77,   519,   520,    72,    37,   523,   524,
      29,    32,   527,   528,   223,   224,   531,   532,    35,    16,
      72,    40,    41,    42,    43,    44,    45,    46,    48,    49,
      50,    51,    52,    39,    72,     3,    55,     3,    57,    58,
      48,    49,    50,    51,    52,    40,    41,    42,    43,    44,
      45,    46,    72,    31,    72,    75,    72,    33,    72,    67,
      68,    69,    57,    58,    72,    72,    36,    67,    68,    69,
      70,    71,    72,    72,    74,    29,   491,    77,    78,   494,
     495,    72,    74,   498,   499,    72,    17,   502,   503,    18,
      18,   506,   507,    18,    17,   510,    40,    41,    42,    43,
      44,    45,    46,     3,    16,    67,    68,    69,    70,    71,
      72,    55,    74,    57,    58,    77,    78,     3,    40,    18,
      30,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,    40,    41,    42,    43,    44,    45,    46,    22,    23,
      24,    25,    26,    70,    71,    72,    55,    74,    57,    58,
      77,    78,    18,    72,    72,    72,    72,    72,    54,    72,
      18,    72,    16,    56,    16,    16,    16,     6,    17,    16,
      72,    72,    17,    17,    72,    63,    18,     3,     9,    58,
      72,    16,    57,    16,     3,    72,     3,    70,    78,    61,
      72,    72,    72,    60,    17,    17,    17,    29,    18,    29,
      16,    29,    16,     3,    29,    29,    17,    72,    18,    72,
      72,    72,    72,    61,    16,    72,    72,    72,    17,    72,
      29,    36,    18,    64,    17,    17,    72,    16,    29,    72,
      17,    17,     3,    17,    72,    72,    17,    16,    16,    16,
      16,    16,   400,    72,    18,    18,   251,    17,    17,    17,
      17,    17,    17,    17,    72,    17,    17,    17,    17,    72,
      17,    17,    17,    17,    17,    17,   187,   362,   217,   248,
     283,   219,    78,   465,   370,   407,   184,   431,   446,    -1,
     331
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
      17,    18,    18,    29,   115,   123,   123,   122,   115,   123,
     123,   123,   123,    18,    53,   115,   124,    29,   123,   123,
     115,   122,   122,    18,    29,   120,   120,    17,     3,    16,
     104,    16,    56,    58,    67,    68,    69,    72,   107,   128,
     130,   142,     3,    40,    18,   111,    30,    18,    97,    22,
      23,    24,    25,    26,   100,    72,    72,   115,   115,   107,
     107,    72,    75,    72,    72,    72,    54,    72,   126,    72,
      75,    72,    72,    75,    72,    75,   107,    18,   105,   143,
     142,    56,    16,    16,    16,    29,    40,    41,    42,    43,
      44,    45,    46,    55,    57,    58,   144,    58,   144,    55,
      58,   144,    34,    65,   127,   144,   107,   142,   110,   126,
       6,    98,    17,    16,    47,    58,   102,    16,    72,    72,
      17,    17,   115,   123,   123,   123,   123,   115,   124,    72,
     124,    63,   131,   123,   123,   122,    29,   120,   120,   120,
     120,    18,   106,   104,     3,   113,   142,    72,   107,   129,
     129,   129,    72,    58,    16,   142,    55,    57,    72,   107,
     128,   142,    72,   107,   128,    16,   142,    55,    72,   107,
     128,   130,   130,    72,   142,   111,     3,    72,    97,     3,
      70,    99,    78,    72,   115,   115,    72,    72,    36,   115,
     125,   126,    61,    60,   138,    72,    75,   107,    17,   105,
      17,    29,    17,    17,    18,    18,    55,    58,   144,   107,
      16,   142,    29,    29,   107,    16,   142,    29,   127,   127,
      29,     3,    17,    18,    94,    72,    72,   123,   124,   130,
      72,   124,   138,    72,   132,   134,    61,   120,   120,   106,
      72,   107,   107,    16,   142,    55,    72,   107,   128,   142,
     106,   107,    72,    72,   106,   107,    72,    72,    47,   102,
      72,    17,   127,   125,    29,    64,   135,    18,   133,    72,
     139,    17,    17,   107,    16,   142,    29,    17,   106,    17,
     106,    94,     3,   124,    72,    48,    49,    50,    51,    52,
     137,   134,    10,    29,    62,   141,   106,   107,    72,    17,
      17,    16,    16,    16,    16,    16,    18,   136,   133,    18,
     140,    72,   140,    17,   106,    72,    75,    72,    75,    72,
      75,    72,    75,    72,    75,   137,    72,    10,   141,    17,
      17,    29,    17,    17,    29,    17,    17,    29,    17,    17,
      29,    17,    17,    29,    17,   136,    10,    29,   141,   140,
     140,   144,    72,    75,   144,   144,    72,    75,   144,   144,
      72,    75,   144,   144,    72,    75,   144,   144,    72,    75,
     144,   140,    72,   140,   107,    17,    17,   107,   107,    17,
      17,   107,   107,    17,    17,   107,   107,    17,    17,   107,
     107,    17,    17,   107,    10,   141,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   140,   140,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107
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
     116,   116,   116,   116,   116,   117,   117,   117,   118,   119,
     119,   119,   119,   119,   120,   120,   120,   120,   120,   121,
     121,   121,   121,   121,   122,   122,   122,   122,   122,   122,
     122,   123,   123,   123,   123,   123,   123,   123,   123,   124,
     124,   124,   124,   124,   125,   125,   126,   126,   127,   127,
     127,   128,   128,   128,   128,   129,   129,   129,   130,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   130,   131,   131,   132,   133,   133,   134,   134,
     135,   135,   136,   136,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   138,   138,   139,   139,   139,
     139,   140,   140,   140,   140,   140,   141,   141,   142,   143,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     145
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
       2,     6,     4,     2,     4,     0,     1,     4,     6,     4,
       6,     6,     8,     6,     8,     1,     1,     3,     4,     0,
       2,     2,     4,     4,     0,     3,     3,     5,     5,     1,
       1,     1,     1,     1,     0,     3,     5,     3,     3,     5,
       5,     0,     3,     5,     3,     5,     7,     5,     3,     0,
       3,     5,     5,     7,     0,     3,     0,     3,     0,     3,
       3,     4,     4,     6,     6,     1,     1,     3,     3,     3,
       3,     3,     5,     3,     3,     5,     3,     3,     3,     4,
       6,     7,     5,     5,     3,     5,     5,     7,     3,     4,
       5,     6,     6,     7,     8,     9,     5,     3,     5,     3,
       3,     2,     3,     0,     4,     2,     0,     3,     1,     3,
       0,     3,     0,     3,     0,     6,     6,     8,     8,     6,
       6,     8,     8,     6,     6,     8,     8,     6,     6,     8,
       8,     6,     6,     8,     8,     0,     3,     3,     5,     3,
       5,     0,     4,     4,     6,     6,     0,     1,     4,     0,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     2,
       8
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
#line 1874 "yacc_sql.tab.c"
    break;

  case 23:
#line 230 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1882 "yacc_sql.tab.c"
    break;

  case 24:
#line 235 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1890 "yacc_sql.tab.c"
    break;

  case 25:
#line 241 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1898 "yacc_sql.tab.c"
    break;

  case 26:
#line 247 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1906 "yacc_sql.tab.c"
    break;

  case 27:
#line 253 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1914 "yacc_sql.tab.c"
    break;

  case 28:
#line 259 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1923 "yacc_sql.tab.c"
    break;

  case 29:
#line 265 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1931 "yacc_sql.tab.c"
    break;

  case 30:
#line 271 "yacc_sql.y"
                                     {
		CONTEXT->ssql->flag = SCF_SHOW_INDEX;
		show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
	}
#line 1940 "yacc_sql.tab.c"
    break;

  case 31:
#line 278 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1949 "yacc_sql.tab.c"
    break;

  case 32:
#line 286 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), (yyvsp[-3].string), CONTEXT->unique);
		}
#line 1958 "yacc_sql.tab.c"
    break;

  case 34:
#line 293 "yacc_sql.y"
                 {
		CONTEXT->unique = 1;
	}
#line 1966 "yacc_sql.tab.c"
    break;

  case 36:
#line 307 "yacc_sql.y"
                                   {
		create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[-1].string));
	}
#line 1974 "yacc_sql.tab.c"
    break;

  case 37:
#line 313 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1983 "yacc_sql.tab.c"
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
#line 1995 "yacc_sql.tab.c"
    break;

  case 40:
#line 330 "yacc_sql.y"
                                   {    }
#line 2001 "yacc_sql.tab.c"
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
#line 2016 "yacc_sql.tab.c"
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
#line 2031 "yacc_sql.tab.c"
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
#line 2046 "yacc_sql.tab.c"
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
#line 2061 "yacc_sql.tab.c"
    break;

  case 45:
#line 380 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 2067 "yacc_sql.tab.c"
    break;

  case 46:
#line 383 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 2073 "yacc_sql.tab.c"
    break;

  case 47:
#line 384 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 2079 "yacc_sql.tab.c"
    break;

  case 48:
#line 385 "yacc_sql.y"
                    {(yyval.number)=TEXTS; }
#line 2085 "yacc_sql.tab.c"
    break;

  case 49:
#line 386 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 2091 "yacc_sql.tab.c"
    break;

  case 50:
#line 387 "yacc_sql.y"
                    {(yyval.number)=DATES;}
#line 2097 "yacc_sql.tab.c"
    break;

  case 51:
#line 391 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 2106 "yacc_sql.tab.c"
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
#line 2126 "yacc_sql.tab.c"
    break;

  case 55:
#line 422 "yacc_sql.y"
                                       {
		CONTEXT->tuple_num++;
		printf("yacc: tuple num %d\n", CONTEXT->tuple_num);
	}
#line 2135 "yacc_sql.tab.c"
    break;

  case 57:
#line 429 "yacc_sql.y"
                                 {
	}
#line 2142 "yacc_sql.tab.c"
    break;

  case 59:
#line 434 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 2150 "yacc_sql.tab.c"
    break;

  case 60:
#line 439 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
  		value_init_integer(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], (yyvsp[0].number));
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
#line 2160 "yacc_sql.tab.c"
    break;

  case 61:
#line 444 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		value_init_float(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], (yyvsp[0].floats));
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
#line 2170 "yacc_sql.tab.c"
    break;

  case 62:
#line 449 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		value_init_string(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], (yyvsp[0].string));
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
#line 2181 "yacc_sql.tab.c"
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
#line 2202 "yacc_sql.tab.c"
    break;

  case 64:
#line 471 "yacc_sql.y"
                   {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
		value_init_null(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++]);
	}
#line 2211 "yacc_sql.tab.c"
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
#line 2224 "yacc_sql.tab.c"
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
#line 2238 "yacc_sql.tab.c"
    break;

  case 67:
#line 502 "yacc_sql.y"
                    {
		CONTEXT->upselect_num++;
		CONTEXT->attribute_name[CONTEXT->value_length - 1] = (yyvsp[-2].string);
	}
#line 2247 "yacc_sql.tab.c"
    break;

  case 68:
#line 506 "yacc_sql.y"
                          {
		CONTEXT->upselect_num++;
		CONTEXT->value_length++;
		CONTEXT->attribute_name[CONTEXT->value_length - 1] = (yyvsp[-2].string);
		CONTEXT->upselect_vec[CONTEXT->value_length - 1] = &CONTEXT->sub_query->sstr.selection;
	}
#line 2258 "yacc_sql.tab.c"
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
#line 2279 "yacc_sql.tab.c"
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
#line 2300 "yacc_sql.tab.c"
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
#line 2317 "yacc_sql.tab.c"
    break;

  case 75:
#line 575 "yacc_sql.y"
                   {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2327 "yacc_sql.tab.c"
    break;

  case 76:
#line 580 "yacc_sql.y"
                                  {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			attr.alias_name = (yyvsp[-1].string);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2338 "yacc_sql.tab.c"
    break;

  case 77:
#line 586 "yacc_sql.y"
                       {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2348 "yacc_sql.tab.c"
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
#line 2360 "yacc_sql.tab.c"
    break;

  case 79:
#line 599 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2370 "yacc_sql.tab.c"
    break;

  case 80:
#line 606 "yacc_sql.y"
                              {
		}
#line 2377 "yacc_sql.tab.c"
    break;

  case 81:
#line 612 "yacc_sql.y"
                                           {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-5].string), (yyvsp[-3].string));
			attr.alias_name = (yyvsp[-1].string);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2388 "yacc_sql.tab.c"
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
#line 2401 "yacc_sql.tab.c"
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
#line 2413 "yacc_sql.tab.c"
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
#line 2425 "yacc_sql.tab.c"
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
#line 2445 "yacc_sql.tab.c"
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
#line 2471 "yacc_sql.tab.c"
    break;

  case 89:
#line 684 "yacc_sql.y"
                                                  {
		selects_append_funcop(&CONTEXT->ssql->sstr.selection, ROUND_OP);
		selects_append_funcvalue2(&CONTEXT->ssql->sstr.selection, 0);
		char* attr_name = (char*)malloc(strlen("round(") + strlen((yyvsp[-1].string)) + strlen(")") + 1);
		memset(attr_name, strlen("round(") + strlen((yyvsp[-1].string)) + strlen(")") + 1, 0);

		//strcat(attr_name, "round(");
		strcpy(attr_name, "round(");
		strcat(attr_name, (yyvsp[-1].string));
		strcat(attr_name, ")");
		strcat(attr_name, "\0");

		selects_modify_alias_name(&CONTEXT->ssql->sstr.selection, attr_name);
		printf("func name %s\n", attr_name);
	}
#line 2491 "yacc_sql.tab.c"
    break;

  case 90:
#line 699 "yacc_sql.y"
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
#line 2515 "yacc_sql.tab.c"
    break;

  case 91:
#line 719 "yacc_sql.y"
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
#line 2535 "yacc_sql.tab.c"
    break;

  case 92:
#line 734 "yacc_sql.y"
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
#line 2559 "yacc_sql.tab.c"
    break;

  case 93:
#line 753 "yacc_sql.y"
                                                               {
		selects_append_funcop(&CONTEXT->ssql->sstr.selection, ROUND_OP);
		selects_append_funcvalue2(&CONTEXT->ssql->sstr.selection, 0);

		selects_modify_alias_name(&CONTEXT->ssql->sstr.selection, (yyvsp[0].string));
		//printf("func name %s\n", attr_name);
	}
#line 2571 "yacc_sql.tab.c"
    break;

  case 94:
#line 760 "yacc_sql.y"
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
#line 2594 "yacc_sql.tab.c"
    break;

  case 95:
#line 782 "yacc_sql.y"
              {
		RelAttr attr;
		attr.relation_name = NULL;
		attr.attribute_name = NULL;
		attr.alias_name = NULL;    
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_funcvalue1(&CONTEXT->ssql->sstr.selection, &CONTEXT->values[CONTEXT->value_length - 1]);

		(yyval.string) = value2string(&CONTEXT->values[CONTEXT->value_length - 1]);
	}
#line 2609 "yacc_sql.tab.c"
    break;

  case 96:
#line 792 "yacc_sql.y"
             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[0].string));
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_funcvalue1(&CONTEXT->ssql->sstr.selection, 0);
		(yyval.string) = (yyvsp[0].string);
		
	}
#line 2622 "yacc_sql.tab.c"
    break;

  case 97:
#line 800 "yacc_sql.y"
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
#line 2638 "yacc_sql.tab.c"
    break;

  case 98:
#line 822 "yacc_sql.y"
                                                          {
		// RelAttr attr;
		// relation_attr_init(&attr, NULL, $3);
		// printf("aggregation: get a attr %s\n", $3);
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		// selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		// CONTEXT->aggregation_num++;	
	}
#line 2651 "yacc_sql.tab.c"
    break;

  case 100:
#line 833 "yacc_sql.y"
                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		printf("aggregation: get a attr *\n");
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
#line 2665 "yacc_sql.tab.c"
    break;

  case 101:
#line 842 "yacc_sql.y"
                           {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		printf("aggregation: get a attr %s\n", (yyvsp[-1].string));
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
#line 2679 "yacc_sql.tab.c"
    break;

  case 102:
#line 851 "yacc_sql.y"
                                  {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		printf("aggregation: get a attr %s\n", (yyvsp[-3].string));
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
#line 2693 "yacc_sql.tab.c"
    break;

  case 103:
#line 860 "yacc_sql.y"
                                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), "*");
		printf("aggregation: get a attr %s\n", (yyvsp[-3].string));
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_ops[CONTEXT->aggregation_num]);
		CONTEXT->aggregation_num++;	
	}
#line 2707 "yacc_sql.tab.c"
    break;

  case 105:
#line 872 "yacc_sql.y"
                                   {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		printf("aggregation: get a attr *\n");
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2719 "yacc_sql.tab.c"
    break;

  case 106:
#line 879 "yacc_sql.y"
                                 {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		printf("aggregation: get a attr %s\n", (yyvsp[-1].string));
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2731 "yacc_sql.tab.c"
    break;

  case 107:
#line 886 "yacc_sql.y"
                                        {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		printf("aggregation: get a attr %s\n", (yyvsp[-3].string));
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2743 "yacc_sql.tab.c"
    break;

  case 108:
#line 893 "yacc_sql.y"
                                          {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), "*");
		printf("aggregation: get a attr %s\n", (yyvsp[-3].string));
		// selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		selects_append_aggrattr(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2755 "yacc_sql.tab.c"
    break;

  case 109:
#line 903 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = COUNT_OP; }
#line 2761 "yacc_sql.tab.c"
    break;

  case 110:
#line 904 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = AVG_OP; }
#line 2767 "yacc_sql.tab.c"
    break;

  case 111:
#line 905 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = MAX_OP; }
#line 2773 "yacc_sql.tab.c"
    break;

  case 112:
#line 906 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = MIN_OP; }
#line 2779 "yacc_sql.tab.c"
    break;

  case 113:
#line 907 "yacc_sql.y"
                { CONTEXT->aggregation_ops[CONTEXT->aggregation_num] = SUM_OP; }
#line 2785 "yacc_sql.tab.c"
    break;

  case 115:
#line 911 "yacc_sql.y"
                                                  {
		if (CONTEXT->last_aggregation_seqno == 0) {
			CONTEXT->last_aggregation_seqno = CONTEXT->aggregation_num;
		}		
		CONTEXT->ssql->sstr.selection.aggregation_alias[CONTEXT->last_aggregation_seqno-1] = NULL;
		CONTEXT->last_aggregation_seqno--;
	}
#line 2797 "yacc_sql.tab.c"
    break;

  case 116:
#line 918 "yacc_sql.y"
                                                               {
		if (CONTEXT->last_aggregation_seqno == 0) {
			CONTEXT->last_aggregation_seqno = CONTEXT->aggregation_num;
		}		
		CONTEXT->ssql->sstr.selection.aggregation_alias[CONTEXT->last_aggregation_seqno-1] = (yyvsp[-1].string);
		CONTEXT->last_aggregation_seqno--;
	}
#line 2809 "yacc_sql.tab.c"
    break;

  case 117:
#line 925 "yacc_sql.y"
                               {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2819 "yacc_sql.tab.c"
    break;

  case 118:
#line 930 "yacc_sql.y"
                            {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2829 "yacc_sql.tab.c"
    break;

  case 119:
#line 935 "yacc_sql.y"
                                    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2839 "yacc_sql.tab.c"
    break;

  case 120:
#line 940 "yacc_sql.y"
                                      {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2849 "yacc_sql.tab.c"
    break;

  case 122:
#line 948 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 2861 "yacc_sql.tab.c"
    break;

  case 123:
#line 955 "yacc_sql.y"
                                      {
		printf("                     %s\n", (yyvsp[-1].string));
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-3].string));
			attr.alias_name = (yyvsp[-1].string);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 2875 "yacc_sql.tab.c"
    break;

  case 124:
#line 965 "yacc_sql.y"
                                    {
		
		}
#line 2883 "yacc_sql.tab.c"
    break;

  case 125:
#line 970 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 2895 "yacc_sql.tab.c"
    break;

  case 126:
#line 977 "yacc_sql.y"
                                             {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-5].string), (yyvsp[-3].string));
			attr.alias_name = (yyvsp[-1].string);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 2908 "yacc_sql.tab.c"
    break;

  case 127:
#line 985 "yacc_sql.y"
                                      {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2918 "yacc_sql.tab.c"
    break;

  case 128:
#line 990 "yacc_sql.y"
                                                   {

	}
#line 2926 "yacc_sql.tab.c"
    break;

  case 130:
#line 999 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string), NULL);
		  }
#line 2934 "yacc_sql.tab.c"
    break;

  case 131:
#line 1002 "yacc_sql.y"
                                     {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-3].string), (yyvsp[-1].string));
		  }
#line 2942 "yacc_sql.tab.c"
    break;

  case 132:
#line 1005 "yacc_sql.y"
                                         {
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string), NULL);
	}
#line 2950 "yacc_sql.tab.c"
    break;

  case 133:
#line 1008 "yacc_sql.y"
                                                      {
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-4].string), (yyvsp[-2].string));
	}
#line 2958 "yacc_sql.tab.c"
    break;

  case 135:
#line 1015 "yacc_sql.y"
                                      {

	}
#line 2966 "yacc_sql.tab.c"
    break;

  case 137:
#line 1021 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2974 "yacc_sql.tab.c"
    break;

  case 139:
#line 1028 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
				if (CONTEXT->last_conditino_seqno == 0) {
					CONTEXT->last_conditino_seqno = CONTEXT->condition_length;
				}
				CONTEXT->conditions[CONTEXT->last_conditino_seqno-1].is_and = 1;
				CONTEXT->last_conditino_seqno--;
				printf("get an and condition: seqno %d\n", CONTEXT->last_conditino_seqno);
			}
#line 2988 "yacc_sql.tab.c"
    break;

  case 140:
#line 1037 "yacc_sql.y"
                                  {
				if (CONTEXT->last_conditino_seqno == 0) {
					CONTEXT->last_conditino_seqno = CONTEXT->condition_length;
				}
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
				CONTEXT->conditions[CONTEXT->last_conditino_seqno-1].is_and = 0;
				CONTEXT->last_conditino_seqno--;
				printf("get an or condition: seqno %d\n", CONTEXT->last_conditino_seqno);
			}
#line 3002 "yacc_sql.tab.c"
    break;

  case 141:
#line 1049 "yacc_sql.y"
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
#line 3020 "yacc_sql.tab.c"
    break;

  case 142:
#line 1062 "yacc_sql.y"
                                                {
		FuncAttrCon* ff = (FuncAttrCon*)malloc(sizeof(FuncAttrCon));
		ff->funcop = ROUND_OP;
		ff->args_value.type = 0;
		ff->attr = (yyvsp[-1].relAttr);
		if ((yyvsp[-1].relAttr) == NULL) {
			ff->value = CONTEXT->values[CONTEXT->value_length - 1];
		} else {
			ff->value.type = UNDEFINED;
		}
		(yyval.FuncAttrCon1) = ff;
		
	}
#line 3038 "yacc_sql.tab.c"
    break;

  case 143:
#line 1075 "yacc_sql.y"
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
#line 3055 "yacc_sql.tab.c"
    break;

  case 144:
#line 1087 "yacc_sql.y"
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
#line 3072 "yacc_sql.tab.c"
    break;

  case 145:
#line 1101 "yacc_sql.y"
              {
		(yyval.relAttr) = NULL;
	}
#line 3080 "yacc_sql.tab.c"
    break;

  case 146:
#line 1104 "yacc_sql.y"
             {
		RelAttr* attr = (RelAttr*)malloc(sizeof(RelAttr));
		relation_attr_init(attr, NULL, (yyvsp[0].string));
		(yyval.relAttr) = attr;
		
	}
#line 3091 "yacc_sql.tab.c"
    break;

  case 147:
#line 1110 "yacc_sql.y"
                    {
		RelAttr* attr = (RelAttr*)malloc(sizeof(RelAttr));
		relation_attr_init(attr, (yyvsp[-2].string), (yyvsp[0].string));
		(yyval.relAttr) = attr;
	}
#line 3101 "yacc_sql.tab.c"
    break;

  case 148:
#line 1119 "yacc_sql.y"
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
#line 3127 "yacc_sql.tab.c"
    break;

  case 149:
#line 1141 "yacc_sql.y"
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
#line 3152 "yacc_sql.tab.c"
    break;

  case 150:
#line 1163 "yacc_sql.y"
        {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, Comparison, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 1, 0, 0, &right_attr, NULL, NULL, NULL, 0);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 3168 "yacc_sql.tab.c"
    break;

  case 151:
#line 1176 "yacc_sql.y"
        {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
		FuncAttrCon* right_func_attr = (yyvsp[0].FuncAttrCon1);
		Condition condition;
		condition_init_func(&condition, Comparison, CONTEXT->comp, 
							1, 0, &left_attr, NULL, NULL,   
		                    0, 0, 0, NULL, NULL, NULL, NULL, 0,  
						    NULL, right_func_attr);
		condition.isfunc = 1;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		printf("a\n");
	}
#line 3186 "yacc_sql.tab.c"
    break;

  case 152:
#line 1191 "yacc_sql.y"
        {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-2].string), (yyvsp[-4].string));
		FuncAttrCon* right_func_attr = (yyvsp[-2].string);
		Condition condition;
		condition_init_func(&condition, Comparison, CONTEXT->comp, 
							1, 0, &left_attr, NULL, NULL,  
							0, 0, 0, NULL, NULL, NULL, NULL, 0,  
							NULL, right_func_attr);
		condition.isfunc = 1;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		printf("b\n");
	}
#line 3204 "yacc_sql.tab.c"
    break;

  case 153:
#line 1206 "yacc_sql.y"
        {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
		FuncAttrCon* right_func_attr = (yyvsp[0].FuncAttrCon1);

		Condition condition;
		condition_init_func(&condition, Comparison, CONTEXT->comp, 
							0, 0, NULL, left_value, NULL, 
							1, 0, 0, NULL, NULL, NULL, NULL, 0,  
							NULL, right_func_attr);
		condition.isfunc = 1;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		printf("c\n");
	}
#line 3222 "yacc_sql.tab.c"
    break;

  case 154:
#line 1221 "yacc_sql.y"
        {
		FuncAttrCon* left_func_attr = (yyvsp[-2].FuncAttrCon1);
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, (yyvsp[0].string));
		Condition condition;
		condition_init_func(&condition, Comparison, CONTEXT->comp, 1, 0, NULL, NULL, NULL, 
							1, 0, 0, &right_attr, NULL, NULL, NULL, 0,  
							left_func_attr, NULL);
		condition.isfunc = 1;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		printf("d\n");
	}
#line 3239 "yacc_sql.tab.c"
    break;

  case 155:
#line 1235 "yacc_sql.y"
        {	
		FuncAttrCon* left_func_attr = (yyvsp[-4].FuncAttrCon1);
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, (yyvsp[-2].string));
		Condition condition;
		condition_init_func(&condition, Comparison, CONTEXT->comp, 1, 0, NULL, NULL, NULL, 
							1, 0, 0, &right_attr, NULL, NULL, NULL, 0,  
							left_func_attr, NULL);
		condition.isfunc = 1;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		printf("e\n");
	}
#line 3256 "yacc_sql.tab.c"
    break;

  case 156:
#line 1249 "yacc_sql.y"
        {
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];
		FuncAttrCon* left_func_attr = (yyvsp[-2].FuncAttrCon1);

		Condition condition;
		condition_init_func(&condition, Comparison, CONTEXT->comp, 1, 0, NULL, NULL, NULL, 
							0, 0, 0, NULL, right_value, NULL, NULL, 0,
							left_func_attr, NULL);
		condition.isfunc = 1;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		printf("f\n");
	}
#line 3273 "yacc_sql.tab.c"
    break;

  case 157:
#line 1262 "yacc_sql.y"
        {
		FuncAttrCon* left_func_attr = (yyvsp[-2].FuncAttrCon1);
		FuncAttrCon* right_func_attr = (yyvsp[0].FuncAttrCon1);
		Condition condition;
		condition_init_func(&condition, Comparison, CONTEXT->comp, 1, 0, NULL, NULL, NULL, 
							1, 0, 0, NULL, NULL, NULL, NULL, 0,   
							left_func_attr, right_func_attr);
		condition.isfunc = 1;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		printf("g\n");
	}
#line 3289 "yacc_sql.tab.c"
    break;

  case 158:
#line 1274 "yacc_sql.y"
        {
		FuncAttrCon* left_func_attr = (yyvsp[-2].FuncAttrCon1);
		Condition condition;
		condition_init_func(&condition, Contain, CONTEXT->comp, 
							1, 0, NULL, NULL, NULL, 
							0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0,
							left_func_attr, NULL);
		condition.isfunc = 1;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		printf("h\n");
	}
#line 3305 "yacc_sql.tab.c"
    break;

  case 159:
#line 1286 "yacc_sql.y"
        {
		FuncAttrCon* left_func_attr = (yyvsp[-3].FuncAttrCon1);
		Condition condition;
		condition_init_func(&condition, NotContain, CONTEXT->comp, 
							1, 0, NULL, NULL, NULL, 
							0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0,
							left_func_attr, NULL);
		condition.isfunc = 1;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		printf("i\n");
	}
#line 3321 "yacc_sql.tab.c"
    break;

  case 160:
#line 1298 "yacc_sql.y"
        {
		FuncAttrCon* left_func_attr = (yyvsp[-5].FuncAttrCon1);
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
#line 3338 "yacc_sql.tab.c"
    break;

  case 161:
#line 1311 "yacc_sql.y"
        {
		FuncAttrCon* left_func_attr = (yyvsp[-6].FuncAttrCon1);
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
#line 3355 "yacc_sql.tab.c"
    break;

  case 162:
#line 1326 "yacc_sql.y"
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
#line 3380 "yacc_sql.tab.c"
    break;

  case 163:
#line 1347 "yacc_sql.y"
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
#line 3405 "yacc_sql.tab.c"
    break;

  case 164:
#line 1368 "yacc_sql.y"
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
#line 3432 "yacc_sql.tab.c"
    break;

  case 165:
#line 1391 "yacc_sql.y"
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
#line 3457 "yacc_sql.tab.c"
    break;

  case 166:
#line 1412 "yacc_sql.y"
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
#line 3482 "yacc_sql.tab.c"
    break;

  case 167:
#line 1433 "yacc_sql.y"
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
#line 3506 "yacc_sql.tab.c"
    break;

  case 168:
#line 1452 "yacc_sql.y"
                          {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

		Condition condition;
		condition_init(&condition, Contain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		
	}
#line 3520 "yacc_sql.tab.c"
    break;

  case 169:
#line 1461 "yacc_sql.y"
                              {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-3].string));

		Condition condition;
		condition_init(&condition, NotContain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 3534 "yacc_sql.tab.c"
    break;

  case 170:
#line 1470 "yacc_sql.y"
                                 {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));

		Condition condition;
		condition_init(&condition, Contain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
		
	}
#line 3548 "yacc_sql.tab.c"
    break;

  case 171:
#line 1479 "yacc_sql.y"
                                     {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-5].string), (yyvsp[-3].string));

		Condition condition;
		condition_init(&condition, NotContain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 3562 "yacc_sql.tab.c"
    break;

  case 172:
#line 1488 "yacc_sql.y"
                                               {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-5].string));

		Condition condition;
		condition_init(&condition, Contain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, 
			CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length = 0;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 3578 "yacc_sql.tab.c"
    break;

  case 173:
#line 1499 "yacc_sql.y"
                                                   {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-6].string));

		Condition condition;
		condition_init(&condition, NotContain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, 
			CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length = 0;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 3594 "yacc_sql.tab.c"
    break;

  case 174:
#line 1510 "yacc_sql.y"
                                                      {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-7].string), (yyvsp[-5].string));

		Condition condition;
		condition_init(&condition, Contain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, 
			CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length = 0;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 3610 "yacc_sql.tab.c"
    break;

  case 175:
#line 1521 "yacc_sql.y"
                                                          {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-8].string), (yyvsp[-6].string));

		Condition condition;
		condition_init(&condition, NotContain, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 0, 1, NULL, NULL, &CONTEXT->sub_query->sstr.selection, 
			CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length = 0;
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 3626 "yacc_sql.tab.c"
    break;

  case 176:
#line 1532 "yacc_sql.y"
                                    {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));

		Condition condition;
		condition_init(&condition, Comparison, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 3639 "yacc_sql.tab.c"
    break;

  case 177:
#line 1540 "yacc_sql.y"
                             {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

		Condition condition;
		condition_init(&condition, Comparison, CONTEXT->comp, 1, 0, &left_attr, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 3652 "yacc_sql.tab.c"
    break;

  case 178:
#line 1548 "yacc_sql.y"
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
#line 3681 "yacc_sql.tab.c"
    break;

  case 179:
#line 1572 "yacc_sql.y"
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
#line 3709 "yacc_sql.tab.c"
    break;

  case 180:
#line 1595 "yacc_sql.y"
                                    {
		Condition condition;
		condition_init(&condition, Comparison, CONTEXT->comp, 0, 1, NULL, NULL, &CONTEXT->left_sub_query->sstr.selection, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 3720 "yacc_sql.tab.c"
    break;

  case 181:
#line 1601 "yacc_sql.y"
                           {

		Condition condition;
		condition_init(&condition, Exists, CONTEXT->comp, 0, 0, NULL, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 3732 "yacc_sql.tab.c"
    break;

  case 182:
#line 1608 "yacc_sql.y"
                               {

		Condition condition;
		condition_init(&condition, NotExists, CONTEXT->comp, 0, 0, NULL, NULL, NULL, 0, 1, 0, NULL, NULL, &CONTEXT->sub_query->sstr.selection, NULL, 0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
#line 3744 "yacc_sql.tab.c"
    break;

  case 183:
#line 1619 "yacc_sql.y"
        {
		selects_set_group(&CONTEXT->ssql->sstr.selection, 0);
	}
#line 3752 "yacc_sql.tab.c"
    break;

  case 184:
#line 1622 "yacc_sql.y"
                                      {
		selects_set_group(&CONTEXT->ssql->sstr.selection, 1);
	}
#line 3760 "yacc_sql.tab.c"
    break;

  case 185:
#line 1628 "yacc_sql.y"
                                   {
		// 递归。最新秒杀升级版。
	}
#line 3768 "yacc_sql.tab.c"
    break;

  case 187:
#line 1634 "yacc_sql.y"
                                           {
		// 递归。最新秒杀升级版。
	}
#line 3776 "yacc_sql.tab.c"
    break;

  case 188:
#line 1641 "yacc_sql.y"
           {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[0].string));
		selects_append_groupattr(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 3786 "yacc_sql.tab.c"
    break;

  case 189:
#line 1646 "yacc_sql.y"
                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
		selects_append_groupattr(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 3796 "yacc_sql.tab.c"
    break;

  case 190:
#line 1654 "yacc_sql.y"
        {
		selects_set_having(&CONTEXT->ssql->sstr.selection, 0);
	}
#line 3804 "yacc_sql.tab.c"
    break;

  case 191:
#line 1657 "yacc_sql.y"
                                                        {
		// 递归
		selects_set_having(&CONTEXT->ssql->sstr.selection, 1);
	}
#line 3813 "yacc_sql.tab.c"
    break;

  case 193:
#line 1664 "yacc_sql.y"
                                                      {
		// 递归
	}
#line 3821 "yacc_sql.tab.c"
    break;

  case 195:
#line 1674 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, COUNT_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3833 "yacc_sql.tab.c"
    break;

  case 196:
#line 1681 "yacc_sql.y"
                                               {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		Having_Condition condition;
		having_condition_init(&condition, COUNT_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3845 "yacc_sql.tab.c"
    break;

  case 197:
#line 1688 "yacc_sql.y"
                                                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, COUNT_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3857 "yacc_sql.tab.c"
    break;

  case 198:
#line 1695 "yacc_sql.y"
                                                      {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), "*");
		Having_Condition condition;
		having_condition_init(&condition, COUNT_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3869 "yacc_sql.tab.c"
    break;

  case 199:
#line 1702 "yacc_sql.y"
                                           {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, AVG_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3881 "yacc_sql.tab.c"
    break;

  case 200:
#line 1709 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		Having_Condition condition;
		having_condition_init(&condition, AVG_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3893 "yacc_sql.tab.c"
    break;

  case 201:
#line 1716 "yacc_sql.y"
                                                  {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, AVG_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3905 "yacc_sql.tab.c"
    break;

  case 202:
#line 1723 "yacc_sql.y"
                                                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), "*");
		Having_Condition condition;
		having_condition_init(&condition, AVG_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3917 "yacc_sql.tab.c"
    break;

  case 203:
#line 1730 "yacc_sql.y"
                                           {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, MAX_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3929 "yacc_sql.tab.c"
    break;

  case 204:
#line 1737 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		Having_Condition condition;
		having_condition_init(&condition, MAX_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3941 "yacc_sql.tab.c"
    break;

  case 205:
#line 1744 "yacc_sql.y"
                                                  {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, MAX_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3953 "yacc_sql.tab.c"
    break;

  case 206:
#line 1751 "yacc_sql.y"
                                                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), "*");
		Having_Condition condition;
		having_condition_init(&condition, MAX_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3965 "yacc_sql.tab.c"
    break;

  case 207:
#line 1758 "yacc_sql.y"
                                           {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, MIN_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3977 "yacc_sql.tab.c"
    break;

  case 208:
#line 1765 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		Having_Condition condition;
		having_condition_init(&condition, MIN_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 3989 "yacc_sql.tab.c"
    break;

  case 209:
#line 1772 "yacc_sql.y"
                                                  {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, MIN_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 4001 "yacc_sql.tab.c"
    break;

  case 210:
#line 1779 "yacc_sql.y"
                                                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), "*");
		Having_Condition condition;
		having_condition_init(&condition, MIN_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 4013 "yacc_sql.tab.c"
    break;

  case 211:
#line 1786 "yacc_sql.y"
                                           {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, SUM_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 4025 "yacc_sql.tab.c"
    break;

  case 212:
#line 1793 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "$3");
		Having_Condition condition;
		having_condition_init(&condition, SUM_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 4037 "yacc_sql.tab.c"
    break;

  case 213:
#line 1800 "yacc_sql.y"
                                                  {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), (yyvsp[-3].string));
		Having_Condition condition;
		having_condition_init(&condition, SUM_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 4049 "yacc_sql.tab.c"
    break;

  case 214:
#line 1807 "yacc_sql.y"
                                                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-5].string), "*");
		Having_Condition condition;
		having_condition_init(&condition, SUM_OP, CONTEXT->comp, &CONTEXT->values[CONTEXT->value_length - 1], &attr);
		selects_append_havingcondition(&CONTEXT->ssql->sstr.selection, &condition);
	}
#line 4061 "yacc_sql.tab.c"
    break;

  case 215:
#line 1817 "yacc_sql.y"
        {
		selects_set_order(&CONTEXT->ssql->sstr.selection, 0);
	}
#line 4069 "yacc_sql.tab.c"
    break;

  case 216:
#line 1820 "yacc_sql.y"
                              {
		selects_set_order(&CONTEXT->ssql->sstr.selection, 1);
	}
#line 4077 "yacc_sql.tab.c"
    break;

  case 217:
#line 1826 "yacc_sql.y"
                               {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
		}
#line 4087 "yacc_sql.tab.c"
    break;

  case 218:
#line 1831 "yacc_sql.y"
                                        {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
		}
#line 4097 "yacc_sql.tab.c"
    break;

  case 219:
#line 1836 "yacc_sql.y"
                                  {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
		}
#line 4107 "yacc_sql.tab.c"
    break;

  case 220:
#line 1841 "yacc_sql.y"
                                         {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
		}
#line 4117 "yacc_sql.tab.c"
    break;

  case 222:
#line 1850 "yacc_sql.y"
                                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
      }
#line 4127 "yacc_sql.tab.c"
    break;

  case 223:
#line 1855 "yacc_sql.y"
                                    {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
      }
#line 4137 "yacc_sql.tab.c"
    break;

  case 224:
#line 1860 "yacc_sql.y"
                                          {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 1);
  	  }
#line 4147 "yacc_sql.tab.c"
    break;

  case 225:
#line 1865 "yacc_sql.y"
                                           {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_orderattr(&CONTEXT->ssql->sstr.selection, &attr, 0);
  	  }
#line 4157 "yacc_sql.tab.c"
    break;

  case 228:
#line 1878 "yacc_sql.y"
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
#line 4175 "yacc_sql.tab.c"
    break;

  case 229:
#line 1891 "yacc_sql.y"
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
#line 4195 "yacc_sql.tab.c"
    break;

  case 230:
#line 1909 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 4201 "yacc_sql.tab.c"
    break;

  case 231:
#line 1910 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 4207 "yacc_sql.tab.c"
    break;

  case 232:
#line 1911 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 4213 "yacc_sql.tab.c"
    break;

  case 233:
#line 1912 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 4219 "yacc_sql.tab.c"
    break;

  case 234:
#line 1913 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 4225 "yacc_sql.tab.c"
    break;

  case 235:
#line 1914 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 4231 "yacc_sql.tab.c"
    break;

  case 236:
#line 1915 "yacc_sql.y"
             { CONTEXT->comp = LOGICAL_IS; }
#line 4237 "yacc_sql.tab.c"
    break;

  case 237:
#line 1916 "yacc_sql.y"
                 {CONTEXT->comp = LOGICAL_IS_NOT; }
#line 4243 "yacc_sql.tab.c"
    break;

  case 238:
#line 1917 "yacc_sql.y"
               { CONTEXT->comp = LIKE_OP; }
#line 4249 "yacc_sql.tab.c"
    break;

  case 239:
#line 1918 "yacc_sql.y"
                   { CONTEXT->comp = NOT_LIKE_OP; }
#line 4255 "yacc_sql.tab.c"
    break;

  case 240:
#line 1923 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 4264 "yacc_sql.tab.c"
    break;


#line 4268 "yacc_sql.tab.c"

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
#line 1928 "yacc_sql.y"

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
