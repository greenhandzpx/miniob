/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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
<<<<<<< HEAD
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    CREATE = 259,                  /* CREATE  */
    DROP = 260,                    /* DROP  */
    TABLE = 261,                   /* TABLE  */
    TABLES = 262,                  /* TABLES  */
    INDEX = 263,                   /* INDEX  */
    SELECT = 264,                  /* SELECT  */
    DESC = 265,                    /* DESC  */
    SHOW = 266,                    /* SHOW  */
    SYNC = 267,                    /* SYNC  */
    INSERT = 268,                  /* INSERT  */
    DELETE = 269,                  /* DELETE  */
    UPDATE = 270,                  /* UPDATE  */
    LBRACE = 271,                  /* LBRACE  */
    RBRACE = 272,                  /* RBRACE  */
    COMMA = 273,                   /* COMMA  */
    TRX_BEGIN = 274,               /* TRX_BEGIN  */
    TRX_COMMIT = 275,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 276,            /* TRX_ROLLBACK  */
    INT_T = 277,                   /* INT_T  */
    STRING_T = 278,                /* STRING_T  */
    TEXT_T = 279,                  /* TEXT_T  */
    FLOAT_T = 280,                 /* FLOAT_T  */
    DATE_T = 281,                  /* DATE_T  */
    HELP = 282,                    /* HELP  */
    EXIT = 283,                    /* EXIT  */
    DOT = 284,                     /* DOT  */
    INTO = 285,                    /* INTO  */
    VALUES = 286,                  /* VALUES  */
    FROM = 287,                    /* FROM  */
    WHERE = 288,                   /* WHERE  */
    AND = 289,                     /* AND  */
    SET = 290,                     /* SET  */
    ON = 291,                      /* ON  */
    LOAD = 292,                    /* LOAD  */
    DATA = 293,                    /* DATA  */
    INFILE = 294,                  /* INFILE  */
    EQ = 295,                      /* EQ  */
    LT = 296,                      /* LT  */
    GT = 297,                      /* GT  */
    LE = 298,                      /* LE  */
    GE = 299,                      /* GE  */
    NE = 300,                      /* NE  */
    IS = 301,                      /* IS  */
    NULLABLE = 302,                /* NULLABLE  */
    COUNT = 303,                   /* COUNT  */
    AVG = 304,                     /* AVG  */
    MAX = 305,                     /* MAX  */
    MIN = 306,                     /* MIN  */
    SUM = 307,                     /* SUM  */
    INNER = 308,                   /* INNER  */
    JOIN = 309,                    /* JOIN  */
    IN = 310,                      /* IN  */
    EXISTS = 311,                  /* EXISTS  */
    LIKE = 312,                    /* LIKE  */
    NOT = 313,                     /* NOT  */
    UNIQUE = 314,                  /* UNIQUE  */
    ORDER = 315,                   /* ORDER  */
    BY = 316,                      /* BY  */
    ASC = 317,                     /* ASC  */
    NUMBER = 318,                  /* NUMBER  */
    FLOAT = 319,                   /* FLOAT  */
    ID = 320,                      /* ID  */
    PATH = 321,                    /* PATH  */
    SSS = 322,                     /* SSS  */
    STAR = 323,                    /* STAR  */
    STRING_V = 324,                /* STRING_V  */
    DATE_STR = 325,                /* DATE_STR  */
    NULLVALUE = 326                /* NULLVALUE  */
=======
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
>>>>>>> updatesel
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 147 "yacc_sql.y"

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
	char *position;

<<<<<<< HEAD
#line 145 "yacc_sql.tab.h"
=======
#line 136 "yacc_sql.tab.h"
>>>>>>> updatesel

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void *scanner);

#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */
