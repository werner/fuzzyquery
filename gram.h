/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CREATE = 258,
     FUZZY = 259,
     PREDICATE = 260,
     ON = 261,
     AS = 262,
     COMMA = 263,
     DOTDOT = 264,
     LEFTP = 265,
     RIGHTP = 266,
     INFINIT = 267,
     DROP = 268,
     EQUAL = 269,
     SELECT = 270,
     WHERE = 271,
     FROM = 272,
     AND = 273,
     OR = 274,
     ORDER = 275,
     BY = 276,
     ASC = 277,
     DESC = 278,
     WITH = 279,
     CALIBRATION = 280,
     PARAMETER = 281
   };
#endif
/* Tokens.  */
#define CREATE 258
#define FUZZY 259
#define PREDICATE 260
#define ON 261
#define AS 262
#define COMMA 263
#define DOTDOT 264
#define LEFTP 265
#define RIGHTP 266
#define INFINIT 267
#define DROP 268
#define EQUAL 269
#define SELECT 270
#define WHERE 271
#define FROM 272
#define AND 273
#define OR 274
#define ORDER 275
#define BY 276
#define ASC 277
#define DESC 278
#define WITH 279
#define CALIBRATION 280
#define PARAMETER 281




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 19 "gram.y"
{
    int	integer;
    char *text;
}
/* Line 1489 of yacc.c.  */
#line 106 "gram.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

