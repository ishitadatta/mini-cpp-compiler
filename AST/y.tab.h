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
     HASH = 258,
     INCLUDE = 259,
     IOSTREAM = 260,
     STRING_LITERAL = 261,
     HEADER_LITERAL = 262,
     PRINT = 263,
     RETURN = 264,
     INTEGER_LITERAL = 265,
     CHARACTER_LITERAL = 266,
     FLOAT_LITERAL = 267,
     IDENTIFIER = 268,
     INC_OP = 269,
     DEC_OP = 270,
     LE_OP = 271,
     GE_OP = 272,
     EQ_OP = 273,
     NE_OP = 274,
     MUL_ASSIGN = 275,
     DIV_ASSIGN = 276,
     MOD_ASSIGN = 277,
     ADD_ASSIGN = 278,
     SUB_ASSIGN = 279,
     CHAR = 280,
     INT = 281,
     FLOAT = 282,
     VOID = 283,
     FOR = 284,
     WHILE = 285,
     IF = 286
   };
#endif
/* Tokens.  */
#define HASH 258
#define INCLUDE 259
#define IOSTREAM 260
#define STRING_LITERAL 261
#define HEADER_LITERAL 262
#define PRINT 263
#define RETURN 264
#define INTEGER_LITERAL 265
#define CHARACTER_LITERAL 266
#define FLOAT_LITERAL 267
#define IDENTIFIER 268
#define INC_OP 269
#define DEC_OP 270
#define LE_OP 271
#define GE_OP 272
#define EQ_OP 273
#define NE_OP 274
#define MUL_ASSIGN 275
#define DIV_ASSIGN 276
#define MOD_ASSIGN 277
#define ADD_ASSIGN 278
#define SUB_ASSIGN 279
#define CHAR 280
#define INT 281
#define FLOAT 282
#define VOID 283
#define FOR 284
#define WHILE 285
#define IF 286




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 92 "ast.y"
{
	int ival;
	float fval;
	char cval;
	char string[128];
	struct node *ptr;
}
/* Line 1529 of yacc.c.  */
#line 119 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

