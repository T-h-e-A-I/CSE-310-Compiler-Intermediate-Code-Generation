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
     IF = 258,
     ELSE = 259,
     FOR = 260,
     WHILE = 261,
     ID = 262,
     LPAREN = 263,
     RPAREN = 264,
     SEMICOLON = 265,
     LCURL = 266,
     RCURL = 267,
     LTHIRD = 268,
     RTHIRD = 269,
     COMMA = 270,
     ASSIGNOP = 271,
     RELOP = 272,
     LOGICOP = 273,
     ADDOP = 274,
     MULOP = 275,
     NOT = 276,
     INCOP = 277,
     DECOP = 278,
     PRINTLN = 279,
     RETURN = 280,
     INT = 281,
     FLOAT = 282,
     VOID = 283,
     CONST_INT = 284,
     CONST_FLOAT = 285,
     LOWER_THAN_ELSE = 286
   };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define FOR 260
#define WHILE 261
#define ID 262
#define LPAREN 263
#define RPAREN 264
#define SEMICOLON 265
#define LCURL 266
#define RCURL 267
#define LTHIRD 268
#define RTHIRD 269
#define COMMA 270
#define ASSIGNOP 271
#define RELOP 272
#define LOGICOP 273
#define ADDOP 274
#define MULOP 275
#define NOT 276
#define INCOP 277
#define DECOP 278
#define PRINTLN 279
#define RETURN 280
#define INT 281
#define FLOAT 282
#define VOID 283
#define CONST_INT 284
#define CONST_FLOAT 285
#define LOWER_THAN_ELSE 286




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 657 "2005054.y"
{
    SymbolInfo* symbol_info;
}
/* Line 1529 of yacc.c.  */
#line 115 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

