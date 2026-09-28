/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_MINI_Y_H_INCLUDED
# define YY_YY_MINI_Y_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INT = 258,                     /* INT  */
    EQ = 259,                      /* EQ  */
    NE = 260,                      /* NE  */
    LT = 261,                      /* LT  */
    LE = 262,                      /* LE  */
    GT = 263,                      /* GT  */
    GE = 264,                      /* GE  */
    UMINUS = 265,                  /* UMINUS  */
    IF = 266,                      /* IF  */
    ELSE = 267,                    /* ELSE  */
    WHILE = 268,                   /* WHILE  */
    INPUT = 269,                   /* INPUT  */
    OUTPUT = 270,                  /* OUTPUT  */
    RETURN = 271,                  /* RETURN  */
    INTEGER = 272,                 /* INTEGER  */
    IDENTIFIER = 273,              /* IDENTIFIER  */
    TEXT = 274,                    /* TEXT  */
    SWITCH = 275,                  /* SWITCH  */
    CASE = 276,                    /* CASE  */
    DEFAULT = 277,                 /* DEFAULT  */
    BREAK = 278,                   /* BREAK  */
    FOR = 279,                     /* FOR  */
    DO = 280,                      /* DO  */
    CONTINUE = 281,                /* CONTINUE  */
    AND = 282,                     /* AND  */
    OR = 283,                      /* OR  */
    CHAR = 284,                    /* CHAR  */
    CHARACTER = 285,               /* CHARACTER  */
    STRUCT = 286,                  /* STRUCT  */
    TYPEDEF = 287,                 /* TYPEDEF  */
    ARROW = 288,                   /* ARROW  */
    TYPEID = 289,                  /* TYPEID  */
    LOWER_THAN_POSTFIX = 290,      /* LOWER_THAN_POSTFIX  */
    LOWER_THAN_ELSE = 291          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define INT 258
#define EQ 259
#define NE 260
#define LT 261
#define LE 262
#define GT 263
#define GE 264
#define UMINUS 265
#define IF 266
#define ELSE 267
#define WHILE 268
#define INPUT 269
#define OUTPUT 270
#define RETURN 271
#define INTEGER 272
#define IDENTIFIER 273
#define TEXT 274
#define SWITCH 275
#define CASE 276
#define DEFAULT 277
#define BREAK 278
#define FOR 279
#define DO 280
#define CONTINUE 281
#define AND 282
#define OR 283
#define CHAR 284
#define CHARACTER 285
#define STRUCT 286
#define TYPEDEF 287
#define ARROW 288
#define TYPEID 289
#define LOWER_THAN_POSTFIX 290
#define LOWER_THAN_ELSE 291

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 14 "mini.y"

    char character;
    char *string;
    SYM *sym;
    TAC *tac;
    EXP	*exp;
    FIELD *field;   
    DLIST *dims;   

#line 149 "mini.y.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_MINI_Y_H_INCLUDED  */
