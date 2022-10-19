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


#line 137 "yacc_sql.tab.c"

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
  YYSYMBOL_FLOAT_T = 24,                   /* FLOAT_T  */
<<<<<<< HEAD
  YYSYMBOL_HELP = 25,                      /* HELP  */
  YYSYMBOL_EXIT = 26,                      /* EXIT  */
  YYSYMBOL_DOT = 27,                       /* DOT  */
  YYSYMBOL_INTO = 28,                      /* INTO  */
  YYSYMBOL_VALUES = 29,                    /* VALUES  */
  YYSYMBOL_FROM = 30,                      /* FROM  */
  YYSYMBOL_WHERE = 31,                     /* WHERE  */
  YYSYMBOL_AND = 32,                       /* AND  */
  YYSYMBOL_SET = 33,                       /* SET  */
  YYSYMBOL_ON = 34,                        /* ON  */
  YYSYMBOL_LOAD = 35,                      /* LOAD  */
  YYSYMBOL_DATA = 36,                      /* DATA  */
  YYSYMBOL_INFILE = 37,                    /* INFILE  */
  YYSYMBOL_EQ = 38,                        /* EQ  */
  YYSYMBOL_LT = 39,                        /* LT  */
  YYSYMBOL_GT = 40,                        /* GT  */
  YYSYMBOL_LE = 41,                        /* LE  */
  YYSYMBOL_GE = 42,                        /* GE  */
  YYSYMBOL_NE = 43,                        /* NE  */
  YYSYMBOL_NUMBER = 44,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 45,                     /* FLOAT  */
  YYSYMBOL_ID = 46,                        /* ID  */
  YYSYMBOL_PATH = 47,                      /* PATH  */
  YYSYMBOL_SSS = 48,                       /* SSS  */
  YYSYMBOL_STAR = 49,                      /* STAR  */
  YYSYMBOL_STRING_V = 50,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 51,                  /* $accept  */
  YYSYMBOL_commands = 52,                  /* commands  */
  YYSYMBOL_command = 53,                   /* command  */
  YYSYMBOL_exit = 54,                      /* exit  */
  YYSYMBOL_help = 55,                      /* help  */
  YYSYMBOL_sync = 56,                      /* sync  */
  YYSYMBOL_begin = 57,                     /* begin  */
  YYSYMBOL_commit = 58,                    /* commit  */
  YYSYMBOL_rollback = 59,                  /* rollback  */
  YYSYMBOL_drop_table = 60,                /* drop_table  */
  YYSYMBOL_show_tables = 61,               /* show_tables  */
  YYSYMBOL_desc_table = 62,                /* desc_table  */
  YYSYMBOL_create_index = 63,              /* create_index  */
  YYSYMBOL_drop_index = 64,                /* drop_index  */
  YYSYMBOL_create_table = 65,              /* create_table  */
  YYSYMBOL_attr_def_list = 66,             /* attr_def_list  */
  YYSYMBOL_attr_def = 67,                  /* attr_def  */
  YYSYMBOL_number = 68,                    /* number  */
  YYSYMBOL_type = 69,                      /* type  */
  YYSYMBOL_ID_get = 70,                    /* ID_get  */
  YYSYMBOL_insert = 71,                    /* insert  */
  YYSYMBOL_tuple = 72,                     /* tuple  */
  YYSYMBOL_tuple_list = 73,                /* tuple_list  */
  YYSYMBOL_value_list = 74,                /* value_list  */
  YYSYMBOL_value = 75,                     /* value  */
  YYSYMBOL_delete = 76,                    /* delete  */
  YYSYMBOL_update = 77,                    /* update  */
  YYSYMBOL_select = 78,                    /* select  */
  YYSYMBOL_select_attr = 79,               /* select_attr  */
  YYSYMBOL_attr_list = 80,                 /* attr_list  */
  YYSYMBOL_rel_list = 81,                  /* rel_list  */
  YYSYMBOL_where = 82,                     /* where  */
  YYSYMBOL_condition_list = 83,            /* condition_list  */
  YYSYMBOL_condition = 84,                 /* condition  */
  YYSYMBOL_comOp = 85,                     /* comOp  */
  YYSYMBOL_load_data = 86                  /* load_data  */
=======
  YYSYMBOL_DATE_T = 25,                    /* DATE_T  */
  YYSYMBOL_HELP = 26,                      /* HELP  */
  YYSYMBOL_EXIT = 27,                      /* EXIT  */
  YYSYMBOL_DOT = 28,                       /* DOT  */
  YYSYMBOL_INTO = 29,                      /* INTO  */
  YYSYMBOL_VALUES = 30,                    /* VALUES  */
  YYSYMBOL_FROM = 31,                      /* FROM  */
  YYSYMBOL_WHERE = 32,                     /* WHERE  */
  YYSYMBOL_AND = 33,                       /* AND  */
  YYSYMBOL_SET = 34,                       /* SET  */
  YYSYMBOL_ON = 35,                        /* ON  */
  YYSYMBOL_LOAD = 36,                      /* LOAD  */
  YYSYMBOL_DATA = 37,                      /* DATA  */
  YYSYMBOL_INFILE = 38,                    /* INFILE  */
  YYSYMBOL_EQ = 39,                        /* EQ  */
  YYSYMBOL_LT = 40,                        /* LT  */
  YYSYMBOL_GT = 41,                        /* GT  */
  YYSYMBOL_LE = 42,                        /* LE  */
  YYSYMBOL_GE = 43,                        /* GE  */
  YYSYMBOL_NE = 44,                        /* NE  */
  YYSYMBOL_NULLABLE = 45,                  /* NULLABLE  */
  YYSYMBOL_NUMBER = 46,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 47,                     /* FLOAT  */
  YYSYMBOL_ID = 48,                        /* ID  */
  YYSYMBOL_PATH = 49,                      /* PATH  */
  YYSYMBOL_SSS = 50,                       /* SSS  */
  YYSYMBOL_STAR = 51,                      /* STAR  */
  YYSYMBOL_STRING_V = 52,                  /* STRING_V  */
  YYSYMBOL_DATE_STR = 53,                  /* DATE_STR  */
  YYSYMBOL_YYACCEPT = 54,                  /* $accept  */
  YYSYMBOL_commands = 55,                  /* commands  */
  YYSYMBOL_command = 56,                   /* command  */
  YYSYMBOL_exit = 57,                      /* exit  */
  YYSYMBOL_help = 58,                      /* help  */
  YYSYMBOL_sync = 59,                      /* sync  */
  YYSYMBOL_begin = 60,                     /* begin  */
  YYSYMBOL_commit = 61,                    /* commit  */
  YYSYMBOL_rollback = 62,                  /* rollback  */
  YYSYMBOL_drop_table = 63,                /* drop_table  */
  YYSYMBOL_show_tables = 64,               /* show_tables  */
  YYSYMBOL_desc_table = 65,                /* desc_table  */
  YYSYMBOL_create_index = 66,              /* create_index  */
  YYSYMBOL_drop_index = 67,                /* drop_index  */
  YYSYMBOL_create_table = 68,              /* create_table  */
  YYSYMBOL_attr_def_list = 69,             /* attr_def_list  */
  YYSYMBOL_attr_def = 70,                  /* attr_def  */
  YYSYMBOL_number = 71,                    /* number  */
  YYSYMBOL_type = 72,                      /* type  */
  YYSYMBOL_ID_get = 73,                    /* ID_get  */
  YYSYMBOL_insert = 74,                    /* insert  */
  YYSYMBOL_value_list = 75,                /* value_list  */
  YYSYMBOL_value = 76,                     /* value  */
  YYSYMBOL_delete = 77,                    /* delete  */
  YYSYMBOL_update = 78,                    /* update  */
  YYSYMBOL_select = 79,                    /* select  */
  YYSYMBOL_select_attr = 80,               /* select_attr  */
  YYSYMBOL_attr_list = 81,                 /* attr_list  */
  YYSYMBOL_rel_list = 82,                  /* rel_list  */
  YYSYMBOL_where = 83,                     /* where  */
  YYSYMBOL_condition_list = 84,            /* condition_list  */
  YYSYMBOL_condition = 85,                 /* condition  */
  YYSYMBOL_comOp = 86,                     /* comOp  */
  YYSYMBOL_load_data = 87                  /* load_data  */
>>>>>>> null
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
<<<<<<< HEAD
#define YYLAST   154
=======
#define YYLAST   155
>>>>>>> null

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
<<<<<<< HEAD
#define YYNRULES  82
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  171
=======
#define YYNRULES  79
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  166
>>>>>>> null

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   308


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
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
<<<<<<< HEAD
       0,   142,   142,   144,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   168,   173,   178,   184,   190,   196,   202,   208,   214,
     221,   229,   236,   245,   247,   251,   262,   275,   278,   279,
     280,   283,   293,   311,   316,   318,   321,   323,   329,   334,
     339,   348,   358,   368,   388,   393,   398,   403,   412,   414,
     421,   428,   435,   437,   441,   443,   447,   449,   454,   475,
     495,   515,   537,   558,   579,   601,   602,   603,   604,   605,
     606,   607,   611
=======
       0,   135,   135,   137,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   161,   166,   171,   177,   183,   189,   195,   201,   207,
     214,   222,   229,   238,   240,   244,   255,   266,   279,   282,
     283,   284,   285,   288,   297,   313,   315,   320,   323,   326,
     330,   342,   352,   362,   381,   386,   391,   397,   399,   406,
     415,   417,   421,   423,   427,   429,   434,   455,   475,   495,
     517,   538,   559,   581,   582,   583,   584,   585,   586,   590
>>>>>>> null
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
<<<<<<< HEAD
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "HELP",
  "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "SET", "ON",
  "LOAD", "DATA", "INFILE", "EQ", "LT", "GT", "LE", "GE", "NE", "NUMBER",
  "FLOAT", "ID", "PATH", "SSS", "STAR", "STRING_V", "$accept", "commands",
  "command", "exit", "help", "sync", "begin", "commit", "rollback",
  "drop_table", "show_tables", "desc_table", "create_index", "drop_index",
  "create_table", "attr_def_list", "attr_def", "number", "type", "ID_get",
  "insert", "tuple", "tuple_list", "value_list", "value", "delete",
  "update", "select", "select_attr", "attr_list", "rel_list", "where",
  "condition_list", "condition", "comOp", "load_data", YY_NULLPTR
=======
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "DATE_T",
  "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "SET",
  "ON", "LOAD", "DATA", "INFILE", "EQ", "LT", "GT", "LE", "GE", "NE",
  "NULLABLE", "NUMBER", "FLOAT", "ID", "PATH", "SSS", "STAR", "STRING_V",
  "DATE_STR", "$accept", "commands", "command", "exit", "help", "sync",
  "begin", "commit", "rollback", "drop_table", "show_tables", "desc_table",
  "create_index", "drop_index", "create_table", "attr_def_list",
  "attr_def", "number", "type", "ID_get", "insert", "value_list", "value",
  "delete", "update", "select", "select_attr", "attr_list", "rel_list",
  "where", "condition_list", "condition", "comOp", "load_data", YY_NULLPTR
>>>>>>> null
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

<<<<<<< HEAD
#define YYPACT_NINF (-98)
=======
#define YYPACT_NINF (-96)
>>>>>>> null

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
     -98,    43,   -98,     2,    53,    -5,   -16,    24,    34,    32,
      35,    21,    70,    79,    84,    86,    87,    55,   -98,   -98,
     -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,
     -98,   -98,   -98,   -98,   -98,   -98,    46,    47,    48,    49,
     -11,   -98,    66,    94,    95,   -98,    54,    56,    68,   -98,
     -98,   -98,   -98,   -98,    62,    88,    69,   102,   103,    61,
      37,   -98,    63,   -98,   -98,    81,    77,    65,    64,    67,
      71,   -98,   -98,    -4,    96,    96,    97,   100,   -33,   115,
      82,    91,   -98,   104,    27,   105,    39,   -98,   -98,   -98,
      78,    77,    36,   107,   -98,   -98,   -21,   -98,   -14,    98,
     -98,    36,   117,    67,   109,   -98,   -98,   -98,   111,    83,
      96,    96,    97,   125,   113,   100,   129,    89,   -98,   -98,
     -98,   -98,   -98,   -98,   -10,    26,   -33,   -98,    77,    90,
     104,   130,    93,   121,   -98,   -98,   -98,   -98,    36,   122,
     107,   -98,   -14,   -98,   -98,   114,   -98,    98,   131,   137,
     -98,   -98,   -98,   126,   139,   113,   -98,   -98,    31,    99,
     -98,   -98,   -98,   -98,   -98,   -98,   119,   -98,   -98,   101,
     -98
=======
     -96,     3,   -96,    35,    50,   -23,   -44,    13,    23,    -2,
       6,    -4,    43,    56,    58,    63,    65,     1,   -96,   -96,
     -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,
     -96,   -96,   -96,   -96,   -96,   -96,    26,    28,    29,    34,
      -9,    69,    59,    86,    99,   -96,    55,    57,    70,   -96,
     -96,   -96,   -96,   -96,    68,    91,    73,   106,   107,    64,
      66,   -96,   -96,    67,   -96,   -96,    81,    84,    71,    72,
      75,    77,   -96,   -96,    -7,    69,    95,   101,     7,   115,
      82,    97,   -96,   102,    76,   108,    79,   -96,   -96,    80,
      84,    38,   -96,   -96,     8,   -96,   -96,    53,    96,   -96,
      38,   124,    75,   114,   -96,   -96,   -96,   -96,   -10,    85,
      69,    95,   129,   116,    87,   -96,   -96,   -96,   -96,   -96,
     -96,    17,    25,     7,   -96,    84,    88,   102,   134,    92,
     -96,   122,   -96,   -96,   -96,    38,   123,    53,   -96,   -96,
     113,   -96,    96,   139,   140,   -96,   -96,   -96,   127,   142,
     116,   143,    33,   100,   -96,   -96,   -96,   -96,   -96,   -96,
     -96,   119,   -96,   -96,   103,   -96
>>>>>>> null
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    13,
       8,     5,     7,     6,     4,    18,     0,     0,     0,     0,
<<<<<<< HEAD
      58,    54,     0,     0,     0,    23,     0,     0,     0,    24,
      25,    26,    22,    21,     0,     0,     0,     0,     0,     0,
       0,    55,     0,    29,    28,     0,    64,     0,     0,     0,
       0,    27,    31,    58,    58,    58,    62,     0,     0,     0,
       0,     0,    41,    33,     0,     0,     0,    59,    56,    57,
       0,    64,     0,    44,    48,    49,    81,    50,    81,    66,
      51,     0,     0,     0,     0,    38,    39,    40,    36,     0,
      58,    58,    62,     0,    46,     0,     0,     0,    75,    76,
      77,    78,    79,    80,     0,     0,     0,    65,    64,     0,
      33,     0,     0,     0,    60,    61,    63,    53,     0,     0,
      44,    42,    81,    70,    68,    71,    69,    66,     0,     0,
      34,    32,    37,     0,     0,    46,    43,    45,     0,     0,
      67,    52,    82,    35,    30,    47,     0,    72,    73,     0,
      74
=======
      57,    57,     0,     0,     0,    23,     0,     0,     0,    24,
      25,    26,    22,    21,     0,     0,     0,     0,     0,     0,
       0,    55,    54,     0,    29,    28,     0,    62,     0,     0,
       0,     0,    27,    31,    57,    57,    60,     0,     0,     0,
       0,     0,    43,    33,     0,     0,     0,    58,    56,     0,
      62,     0,    47,    48,     0,    49,    50,     0,    64,    51,
       0,     0,     0,     0,    39,    40,    41,    42,    36,     0,
      57,    60,     0,    45,     0,    73,    74,    75,    76,    77,
      78,     0,     0,     0,    63,    62,     0,    33,     0,     0,
      37,     0,    59,    61,    53,     0,     0,     0,    68,    66,
      69,    67,    64,     0,     0,    34,    32,    38,     0,     0,
      45,     0,     0,     0,    65,    52,    79,    35,    30,    46,
      44,     0,    70,    71,     0,    72
>>>>>>> null
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
<<<<<<< HEAD
     -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,
     -98,   -98,   -98,   -98,   -98,    14,    45,   -98,   -98,   -98,
     -98,    38,     9,    -3,   -92,   -98,   -98,   -98,   -98,   -71,
      42,   -86,     3,    25,   -97,   -98
=======
     -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,   -96,
     -96,   -96,   -96,   -96,   -96,    22,    48,   -96,   -96,   -96,
     -96,     2,   -90,   -96,   -96,   -96,   -96,   -41,    42,   -85,
      12,    32,   -95,   -96
>>>>>>> null
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
<<<<<<< HEAD
      26,    27,    28,    29,    30,   104,    83,   153,   108,    84,
      31,    93,   116,   139,    98,    32,    33,    34,    42,    61,
      91,    79,   127,    99,   124,    35
=======
      26,    27,    28,    29,    30,   103,    83,   148,   108,    84,
      31,   136,    97,    32,    33,    34,    42,    61,    90,    79,
     124,    98,   121,    35
>>>>>>> null
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
<<<<<<< HEAD
     114,   125,    87,    88,    89,   113,   117,    59,    36,   128,
      37,    94,    95,    96,    59,    97,    60,   118,   119,   120,
     121,   122,   123,    86,   118,   119,   120,   121,   122,   123,
      43,    44,   144,   146,    94,    95,   143,    45,    97,   134,
     135,    40,   148,     2,    41,   158,   155,     3,     4,   105,
     106,   107,     5,     6,     7,     8,     9,    10,    11,    38,
      46,    39,    12,    13,    14,    47,   167,    48,    15,    16,
      94,    95,   145,    49,    97,    94,    95,   166,    17,    97,
      94,    95,    50,    74,    97,   110,    75,    51,   111,    52,
      53,    54,    55,    56,    57,    58,    62,    63,    64,    68,
      65,    67,    66,    70,    69,    71,    72,    73,    78,    76,
      77,    80,    81,    82,    59,    90,    92,    85,   100,   102,
     101,   109,   103,   129,   112,   115,   131,   132,   137,   133,
     126,   138,   141,   151,   161,   142,   149,   152,   154,   156,
     162,   159,   164,   163,   150,   168,   169,   170,   130,   157,
     160,   147,   165,   140,   136
=======
      62,   113,   122,     2,    43,   112,   129,     3,     4,    59,
     125,    59,     5,     6,     7,     8,     9,    10,    11,    60,
      44,    86,    12,    13,    14,    40,    45,    46,    41,    15,
      16,   139,   141,    87,    88,   130,   114,    47,    54,    17,
     143,    36,   152,    37,    48,   150,    49,   115,   116,   117,
     118,   119,   120,    92,    93,    94,    38,    95,    39,    50,
      96,    51,   162,    92,    93,   138,    52,    95,    53,   132,
      96,    92,    93,   140,    55,    95,    56,    57,    96,    92,
      93,   161,    58,    95,    92,    93,    96,    59,    95,    64,
      63,    96,   115,   116,   117,   118,   119,   120,   104,   105,
     106,   107,    65,    66,    68,    67,    69,    70,    71,    72,
      73,    77,    74,    89,    75,    76,    78,    91,    99,    80,
     102,   100,    81,    82,   109,    85,   101,   110,   111,   123,
     126,   128,   134,   131,   135,   137,   144,   146,   147,   149,
     151,   153,   155,   156,   157,   158,   160,   164,   163,   145,
     127,   165,   159,   133,   154,   142
>>>>>>> null
};

static const yytype_uint8 yycheck[] =
{
<<<<<<< HEAD
      92,    98,    73,    74,    75,    91,    27,    18,     6,   101,
       8,    44,    45,    46,    18,    48,    27,    38,    39,    40,
      41,    42,    43,    27,    38,    39,    40,    41,    42,    43,
      46,     7,   124,   125,    44,    45,    46,     3,    48,   110,
     111,    46,   128,     0,    49,   142,   138,     4,     5,    22,
      23,    24,     9,    10,    11,    12,    13,    14,    15,     6,
      28,     8,    19,    20,    21,    30,   158,    46,    25,    26,
      44,    45,    46,     3,    48,    44,    45,    46,    35,    48,
      44,    45,     3,    46,    48,    46,    49,     3,    49,     3,
       3,    36,    46,    46,    46,    46,    30,     3,     3,    37,
      46,    33,    46,    34,    16,     3,     3,    46,    31,    46,
      29,    46,    48,    46,    18,    18,    16,    46,     3,    28,
      38,    16,    18,     6,    46,    18,    17,    16,     3,    46,
      32,    18,     3,     3,     3,    46,    46,    44,    17,    17,
       3,    27,     3,    17,   130,    46,    27,    46,   103,   140,
     147,   126,   155,   115,   112
=======
      41,    91,    97,     0,    48,    90,    16,     4,     5,    18,
     100,    18,     9,    10,    11,    12,    13,    14,    15,    28,
       7,    28,    19,    20,    21,    48,     3,    29,    51,    26,
      27,   121,   122,    74,    75,    45,    28,    31,    37,    36,
     125,     6,   137,     8,    48,   135,     3,    39,    40,    41,
      42,    43,    44,    46,    47,    48,     6,    50,     8,     3,
      53,     3,   152,    46,    47,    48,     3,    50,     3,   110,
      53,    46,    47,    48,    48,    50,    48,    48,    53,    46,
      47,    48,    48,    50,    46,    47,    53,    18,    50,     3,
      31,    53,    39,    40,    41,    42,    43,    44,    22,    23,
      24,    25,     3,    48,    34,    48,    38,    16,    35,     3,
       3,    30,    48,    18,    48,    48,    32,    16,     3,    48,
      18,    39,    50,    48,    16,    48,    29,    48,    48,    33,
       6,    17,     3,    48,    18,    48,    48,     3,    46,    17,
      17,    28,     3,     3,    17,     3,     3,    28,    48,   127,
     102,    48,   150,   111,   142,   123
>>>>>>> null
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
<<<<<<< HEAD
       0,    52,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    19,    20,    21,    25,    26,    35,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    71,    76,    77,    78,    86,     6,     8,     6,     8,
      46,    49,    79,    46,     7,     3,    28,    30,    46,     3,
       3,     3,     3,     3,    36,    46,    46,    46,    46,    18,
      27,    80,    30,     3,     3,    46,    46,    33,    37,    16,
      34,     3,     3,    46,    46,    49,    46,    29,    31,    82,
      46,    48,    46,    67,    70,    46,    27,    80,    80,    80,
      18,    81,    16,    72,    44,    45,    46,    48,    75,    84,
       3,    38,    28,    18,    66,    22,    23,    24,    69,    16,
      46,    49,    46,    82,    75,    18,    73,    27,    38,    39,
      40,    41,    42,    43,    85,    85,    32,    83,    75,     6,
      67,    17,    16,    46,    80,    80,    81,     3,    18,    74,
      72,     3,    46,    46,    75,    46,    75,    84,    82,    46,
      66,     3,    44,    68,    17,    75,    17,    73,    85,    27,
      83,     3,     3,    17,     3,    74,    46,    75,    46,    27,
      46
=======
       0,    55,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    19,    20,    21,    26,    27,    36,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    74,    77,    78,    79,    87,     6,     8,     6,     8,
      48,    51,    80,    48,     7,     3,    29,    31,    48,     3,
       3,     3,     3,     3,    37,    48,    48,    48,    48,    18,
      28,    81,    81,    31,     3,     3,    48,    48,    34,    38,
      16,    35,     3,     3,    48,    48,    48,    30,    32,    83,
      48,    50,    48,    70,    73,    48,    28,    81,    81,    18,
      82,    16,    46,    47,    48,    50,    53,    76,    85,     3,
      39,    29,    18,    69,    22,    23,    24,    25,    72,    16,
      48,    48,    83,    76,    28,    39,    40,    41,    42,    43,
      44,    86,    86,    33,    84,    76,     6,    70,    17,    16,
      45,    48,    81,    82,     3,    18,    75,    48,    48,    76,
      48,    76,    85,    83,    48,    69,     3,    46,    71,    17,
      76,    17,    86,    28,    84,     3,     3,    17,     3,    75,
       3,    48,    76,    48,    28,    48
>>>>>>> null
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
<<<<<<< HEAD
       0,    51,    52,    52,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    66,    67,    67,    68,    69,    69,
      69,    70,    71,    72,    73,    73,    74,    74,    75,    75,
      75,    76,    77,    78,    79,    79,    79,    79,    80,    80,
      80,    80,    81,    81,    82,    82,    83,    83,    84,    84,
      84,    84,    84,    84,    84,    85,    85,    85,    85,    85,
      85,    85,    86
=======
       0,    54,    55,    55,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    69,    70,    70,    70,    71,    72,
      72,    72,    72,    73,    74,    75,    75,    76,    76,    76,
      76,    77,    78,    79,    80,    80,    80,    81,    81,    81,
      82,    82,    83,    83,    84,    84,    85,    85,    85,    85,
      85,    85,    85,    86,    86,    86,    86,    86,    86,    87
>>>>>>> null
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
<<<<<<< HEAD
       9,     4,     8,     0,     3,     5,     2,     1,     1,     1,
       1,     1,     7,     4,     0,     3,     0,     3,     1,     1,
       1,     5,     8,     7,     1,     2,     4,     4,     0,     3,
       5,     5,     0,     3,     0,     3,     0,     3,     3,     3,
       3,     3,     5,     5,     7,     1,     1,     1,     1,     1,
       1,     0,     8
=======
       9,     4,     8,     0,     3,     5,     2,     3,     1,     1,
       1,     1,     1,     1,     9,     0,     3,     1,     1,     1,
       1,     5,     8,     7,     2,     2,     4,     0,     3,     5,
       0,     3,     0,     3,     0,     3,     3,     3,     3,     3,
       5,     5,     7,     1,     1,     1,     1,     1,     1,     8
>>>>>>> null
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
  case 21: /* exit: EXIT SEMICOLON  */
<<<<<<< HEAD
#line 168 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1333 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 173 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1341 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 178 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1349 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 184 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1357 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 190 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1365 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 196 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1373 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 202 "yacc_sql.y"
=======
#line 161 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1319 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 166 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1327 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 171 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1335 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 177 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1343 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 183 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1351 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 189 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1359 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 195 "yacc_sql.y"
>>>>>>> null
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
<<<<<<< HEAD
#line 1382 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 208 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1390 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 214 "yacc_sql.y"
=======
#line 1368 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 201 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1376 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 207 "yacc_sql.y"
>>>>>>> null
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
<<<<<<< HEAD
#line 1399 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID RBRACE SEMICOLON  */
#line 222 "yacc_sql.y"
=======
#line 1385 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID RBRACE SEMICOLON  */
#line 215 "yacc_sql.y"
>>>>>>> null
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string));
		}
<<<<<<< HEAD
#line 1408 "yacc_sql.tab.c"
    break;

  case 31: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 230 "yacc_sql.y"
=======
#line 1394 "yacc_sql.tab.c"
    break;

  case 31: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 223 "yacc_sql.y"
>>>>>>> null
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
<<<<<<< HEAD
#line 1417 "yacc_sql.tab.c"
    break;

  case 32: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 237 "yacc_sql.y"
=======
#line 1403 "yacc_sql.tab.c"
    break;

  case 32: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 230 "yacc_sql.y"
>>>>>>> null
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
<<<<<<< HEAD
#line 1429 "yacc_sql.tab.c"
    break;

  case 34: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 247 "yacc_sql.y"
                                   {    }
#line 1435 "yacc_sql.tab.c"
    break;

  case 35: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 252 "yacc_sql.y"
=======
#line 1415 "yacc_sql.tab.c"
    break;

  case 34: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 240 "yacc_sql.y"
                                   {    }
#line 1421 "yacc_sql.tab.c"
    break;

  case 35: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 245 "yacc_sql.y"
>>>>>>> null
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
<<<<<<< HEAD
#line 1450 "yacc_sql.tab.c"
    break;

  case 36: /* attr_def: ID_get type  */
#line 263 "yacc_sql.y"
=======
#line 1436 "yacc_sql.tab.c"
    break;

  case 36: /* attr_def: ID_get type  */
#line 256 "yacc_sql.y"
>>>>>>> null
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
<<<<<<< HEAD
#line 1465 "yacc_sql.tab.c"
    break;

  case 37: /* number: NUMBER  */
#line 275 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1471 "yacc_sql.tab.c"
    break;

  case 38: /* type: INT_T  */
#line 278 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1477 "yacc_sql.tab.c"
    break;

  case 39: /* type: STRING_T  */
#line 279 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1483 "yacc_sql.tab.c"
    break;

  case 40: /* type: FLOAT_T  */
#line 280 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1489 "yacc_sql.tab.c"
    break;

  case 41: /* ID_get: ID  */
#line 284 "yacc_sql.y"
=======
#line 1451 "yacc_sql.tab.c"
    break;

  case 37: /* attr_def: ID_get type NULLABLE  */
#line 267 "yacc_sql.y"
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
#line 1466 "yacc_sql.tab.c"
    break;

  case 38: /* number: NUMBER  */
#line 279 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1472 "yacc_sql.tab.c"
    break;

  case 39: /* type: INT_T  */
#line 282 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1478 "yacc_sql.tab.c"
    break;

  case 40: /* type: STRING_T  */
#line 283 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1484 "yacc_sql.tab.c"
    break;

  case 41: /* type: FLOAT_T  */
#line 284 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1490 "yacc_sql.tab.c"
    break;

  case 42: /* type: DATE_T  */
#line 285 "yacc_sql.y"
                    {(yyval.number)=DATES;}
#line 1496 "yacc_sql.tab.c"
    break;

  case 43: /* ID_get: ID  */
#line 289 "yacc_sql.y"
>>>>>>> null
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
<<<<<<< HEAD
#line 1498 "yacc_sql.tab.c"
    break;

  case 42: /* insert: INSERT INTO ID VALUES tuple tuple_list SEMICOLON  */
#line 294 "yacc_sql.y"
=======
#line 1505 "yacc_sql.tab.c"
    break;

  case 44: /* insert: INSERT INTO ID VALUES LBRACE value value_list RBRACE SEMICOLON  */
#line 298 "yacc_sql.y"
>>>>>>> null
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
#line 1518 "yacc_sql.tab.c"
    break;

  case 43: /* tuple: LBRACE value value_list RBRACE  */
#line 311 "yacc_sql.y"
                                       {
		CONTEXT->tuple_num++;
		printf("yacc: tuple num %d\n", CONTEXT->tuple_num);
	}
#line 1527 "yacc_sql.tab.c"
    break;

  case 45: /* tuple_list: COMMA tuple tuple_list  */
#line 318 "yacc_sql.y"
                                 {
	}
#line 1534 "yacc_sql.tab.c"
    break;

  case 47: /* value_list: COMMA value value_list  */
#line 323 "yacc_sql.y"
=======
#line 1524 "yacc_sql.tab.c"
    break;

  case 46: /* value_list: COMMA value value_list  */
#line 315 "yacc_sql.y"
>>>>>>> null
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;

	  }
<<<<<<< HEAD
#line 1543 "yacc_sql.tab.c"
    break;

  case 48: /* value: NUMBER  */
#line 329 "yacc_sql.y"
=======
#line 1532 "yacc_sql.tab.c"
    break;

  case 47: /* value: NUMBER  */
#line 320 "yacc_sql.y"
>>>>>>> null
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
  		value_init_integer(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], (yyvsp[0].number));
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
<<<<<<< HEAD
#line 1553 "yacc_sql.tab.c"
    break;

  case 49: /* value: FLOAT  */
#line 334 "yacc_sql.y"
=======
#line 1540 "yacc_sql.tab.c"
    break;

  case 48: /* value: FLOAT  */
#line 323 "yacc_sql.y"
>>>>>>> null
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		value_init_float(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], (yyvsp[0].floats));
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
<<<<<<< HEAD
#line 1563 "yacc_sql.tab.c"
    break;

  case 50: /* value: SSS  */
#line 339 "yacc_sql.y"
=======
#line 1548 "yacc_sql.tab.c"
    break;

  case 49: /* value: SSS  */
#line 326 "yacc_sql.y"
>>>>>>> null
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		value_init_string(&CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]++], (yyvsp[0].string));
		printf("yacc: tuple num %d, value num %d type %d\n", CONTEXT->tuple_num, CONTEXT->value_num[CONTEXT->tuple_num], CONTEXT->tuples[CONTEXT->tuple_num][CONTEXT->value_num[CONTEXT->tuple_num]-1].type);
		}
<<<<<<< HEAD
#line 1574 "yacc_sql.tab.c"
    break;

  case 51: /* delete: DELETE FROM ID where SEMICOLON  */
#line 349 "yacc_sql.y"
=======
#line 1557 "yacc_sql.tab.c"
    break;

  case 50: /* value: DATE_STR  */
#line 330 "yacc_sql.y"
                  {
		(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		// CONTEXT->value_length += value_init_date(&CONTEXT->values[CONTEXT->value_length], $1);
		if (value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string)) == 0) {
			CONTEXT->value_length -= 1;
			CONTEXT->ssql->flag = SCF_INVALID_DATE;
			return 0;
		}
	}
#line 1571 "yacc_sql.tab.c"
    break;

  case 51: /* delete: DELETE FROM ID where SEMICOLON  */
#line 343 "yacc_sql.y"
>>>>>>> null
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
<<<<<<< HEAD
#line 1586 "yacc_sql.tab.c"
    break;

  case 52: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 359 "yacc_sql.y"
=======
#line 1583 "yacc_sql.tab.c"
    break;

  case 52: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 353 "yacc_sql.y"
>>>>>>> null
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
<<<<<<< HEAD
#line 1598 "yacc_sql.tab.c"
    break;

  case 53: /* select: SELECT select_attr FROM ID rel_list where SEMICOLON  */
#line 369 "yacc_sql.y"
=======
#line 1595 "yacc_sql.tab.c"
    break;

  case 53: /* select: SELECT select_attr FROM ID rel_list where SEMICOLON  */
#line 363 "yacc_sql.y"
>>>>>>> null
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
#line 1619 "yacc_sql.tab.c"
    break;

  case 54: /* select_attr: STAR  */
#line 388 "yacc_sql.y"
         {  
=======
#line 1615 "yacc_sql.tab.c"
    break;

  case 54: /* select_attr: STAR attr_list  */
#line 381 "yacc_sql.y"
                   {  
>>>>>>> null
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
<<<<<<< HEAD
#line 1629 "yacc_sql.tab.c"
    break;

  case 55: /* select_attr: ID attr_list  */
#line 393 "yacc_sql.y"
=======
#line 1625 "yacc_sql.tab.c"
    break;

  case 55: /* select_attr: ID attr_list  */
#line 386 "yacc_sql.y"
>>>>>>> null
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
<<<<<<< HEAD
#line 1639 "yacc_sql.tab.c"
    break;

  case 56: /* select_attr: ID DOT ID attr_list  */
#line 398 "yacc_sql.y"
=======
#line 1635 "yacc_sql.tab.c"
    break;

  case 56: /* select_attr: ID DOT ID attr_list  */
#line 391 "yacc_sql.y"
>>>>>>> null
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
<<<<<<< HEAD
#line 1649 "yacc_sql.tab.c"
    break;

  case 57: /* select_attr: ID DOT STAR attr_list  */
#line 403 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
			// CONTEXT->aggregation_op = NO_AGGREGATE_OP;
			// selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, CONTEXT->aggregation_op);
			// selects_append_aggregation_op(&CONTEXT->ssql->sstr.selection, AggregationOp::NO_AGGREGATE_OP);
		}
#line 1662 "yacc_sql.tab.c"
    break;

  case 59: /* attr_list: COMMA ID attr_list  */
#line 414 "yacc_sql.y"
=======
#line 1645 "yacc_sql.tab.c"
    break;

  case 58: /* attr_list: COMMA ID attr_list  */
#line 399 "yacc_sql.y"
>>>>>>> null
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
<<<<<<< HEAD
#line 1674 "yacc_sql.tab.c"
    break;

  case 60: /* attr_list: COMMA ID DOT ID attr_list  */
#line 421 "yacc_sql.y"
=======
#line 1657 "yacc_sql.tab.c"
    break;

  case 59: /* attr_list: COMMA ID DOT ID attr_list  */
#line 406 "yacc_sql.y"
>>>>>>> null
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
<<<<<<< HEAD
#line 1686 "yacc_sql.tab.c"
    break;

  case 61: /* attr_list: COMMA ID DOT STAR attr_list  */
#line 428 "yacc_sql.y"
                                      {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1696 "yacc_sql.tab.c"
    break;

  case 63: /* rel_list: COMMA ID rel_list  */
#line 437 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 1704 "yacc_sql.tab.c"
    break;

  case 65: /* where: WHERE condition condition_list  */
#line 443 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 1712 "yacc_sql.tab.c"
    break;

  case 67: /* condition_list: AND condition condition_list  */
#line 449 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 1720 "yacc_sql.tab.c"
    break;

  case 68: /* condition: ID comOp value  */
#line 455 "yacc_sql.y"
=======
#line 1669 "yacc_sql.tab.c"
    break;

  case 61: /* rel_list: COMMA ID rel_list  */
#line 417 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 1677 "yacc_sql.tab.c"
    break;

  case 63: /* where: WHERE condition condition_list  */
#line 423 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 1685 "yacc_sql.tab.c"
    break;

  case 65: /* condition_list: AND condition condition_list  */
#line 429 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 1693 "yacc_sql.tab.c"
    break;

  case 66: /* condition: ID comOp value  */
#line 435 "yacc_sql.y"
>>>>>>> null
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
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
#line 1745 "yacc_sql.tab.c"
    break;

  case 69: /* condition: value comOp value  */
#line 476 "yacc_sql.y"
=======
#line 1718 "yacc_sql.tab.c"
    break;

  case 67: /* condition: value comOp value  */
#line 456 "yacc_sql.y"
>>>>>>> null
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
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
#line 1769 "yacc_sql.tab.c"
    break;

  case 70: /* condition: ID comOp ID  */
#line 496 "yacc_sql.y"
=======
#line 1742 "yacc_sql.tab.c"
    break;

  case 68: /* condition: ID comOp ID  */
#line 476 "yacc_sql.y"
>>>>>>> null
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
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
#line 1793 "yacc_sql.tab.c"
    break;

  case 71: /* condition: value comOp ID  */
#line 516 "yacc_sql.y"
=======
#line 1766 "yacc_sql.tab.c"
    break;

  case 69: /* condition: value comOp ID  */
#line 496 "yacc_sql.y"
>>>>>>> null
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
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
#line 1819 "yacc_sql.tab.c"
    break;

  case 72: /* condition: ID DOT ID comOp value  */
#line 538 "yacc_sql.y"
=======
#line 1792 "yacc_sql.tab.c"
    break;

  case 70: /* condition: ID DOT ID comOp value  */
#line 518 "yacc_sql.y"
>>>>>>> null
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
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
#line 1844 "yacc_sql.tab.c"
    break;

  case 73: /* condition: value comOp ID DOT ID  */
#line 559 "yacc_sql.y"
=======
#line 1817 "yacc_sql.tab.c"
    break;

  case 71: /* condition: value comOp ID DOT ID  */
#line 539 "yacc_sql.y"
>>>>>>> null
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
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
#line 1869 "yacc_sql.tab.c"
    break;

  case 74: /* condition: ID DOT ID comOp ID DOT ID  */
#line 580 "yacc_sql.y"
=======
#line 1842 "yacc_sql.tab.c"
    break;

  case 72: /* condition: ID DOT ID comOp ID DOT ID  */
#line 560 "yacc_sql.y"
>>>>>>> null
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
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
#line 1892 "yacc_sql.tab.c"
    break;

  case 75: /* comOp: EQ  */
#line 601 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 1898 "yacc_sql.tab.c"
    break;

  case 76: /* comOp: LT  */
#line 602 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 1904 "yacc_sql.tab.c"
    break;

  case 77: /* comOp: GT  */
#line 603 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 1910 "yacc_sql.tab.c"
    break;

  case 78: /* comOp: LE  */
#line 604 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 1916 "yacc_sql.tab.c"
    break;

  case 79: /* comOp: GE  */
#line 605 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 1922 "yacc_sql.tab.c"
    break;

  case 80: /* comOp: NE  */
#line 606 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 1928 "yacc_sql.tab.c"
    break;

  case 82: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 612 "yacc_sql.y"
=======
#line 1865 "yacc_sql.tab.c"
    break;

  case 73: /* comOp: EQ  */
#line 581 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 1871 "yacc_sql.tab.c"
    break;

  case 74: /* comOp: LT  */
#line 582 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 1877 "yacc_sql.tab.c"
    break;

  case 75: /* comOp: GT  */
#line 583 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 1883 "yacc_sql.tab.c"
    break;

  case 76: /* comOp: LE  */
#line 584 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 1889 "yacc_sql.tab.c"
    break;

  case 77: /* comOp: GE  */
#line 585 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 1895 "yacc_sql.tab.c"
    break;

  case 78: /* comOp: NE  */
#line 586 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 1901 "yacc_sql.tab.c"
    break;

  case 79: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 591 "yacc_sql.y"
>>>>>>> null
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
<<<<<<< HEAD
#line 1937 "yacc_sql.tab.c"
    break;


#line 1941 "yacc_sql.tab.c"
=======
#line 1910 "yacc_sql.tab.c"
    break;


#line 1914 "yacc_sql.tab.c"
>>>>>>> null

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

<<<<<<< HEAD
#line 617 "yacc_sql.y"
=======
#line 596 "yacc_sql.y"
>>>>>>> null

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
