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
     TLOWERTHANELSE = 258,
     TELSE = 259,
     TIDENT = 260,
     TNUMBER = 261,
     TCONST = 262,
     TIF = 263,
     TINT = 264,
     TRETURN = 265,
     TVOID = 266,
     TWHILE = 267,
     TADDASSIGN = 268,
     TSUBASSIGN = 269,
     TMULASSIGN = 270,
     TDIVASSIGN = 271,
     TMODASSIGN = 272,
     TOR = 273,
     TAND = 274,
     TEQUAL = 275,
     TNOTEQU = 276,
     TGREATE = 277,
     TLESSE = 278,
     TINC = 279,
     TDEC = 280,
     TPLUS = 281,
     TMINUS = 282,
     TSTAR = 283,
     TSLASH = 284,
     TMOD = 285,
     TASSIGN = 286,
     TNOT = 287,
     TLESS = 288,
     TGREAT = 289,
     TLSBRACKET = 290,
     TRSBRACKET = 291,
     TCOMMA = 292,
     TLMBRACKET = 293,
     TRMBRACKET = 294,
     TLLBRACKET = 295,
     TRLBRACKET = 296,
     TSEMICOLON = 297,
     TCOMMENT = 298,
     TSEPERATOR = 299,
     TLINE = 300,
     TILLID = 301
   };
#endif
/* Tokens.  */
#define TLOWERTHANELSE 258
#define TELSE 259
#define TIDENT 260
#define TNUMBER 261
#define TCONST 262
#define TIF 263
#define TINT 264
#define TRETURN 265
#define TVOID 266
#define TWHILE 267
#define TADDASSIGN 268
#define TSUBASSIGN 269
#define TMULASSIGN 270
#define TDIVASSIGN 271
#define TMODASSIGN 272
#define TOR 273
#define TAND 274
#define TEQUAL 275
#define TNOTEQU 276
#define TGREATE 277
#define TLESSE 278
#define TINC 279
#define TDEC 280
#define TPLUS 281
#define TMINUS 282
#define TSTAR 283
#define TSLASH 284
#define TMOD 285
#define TASSIGN 286
#define TNOT 287
#define TLESS 288
#define TGREAT 289
#define TLSBRACKET 290
#define TRSBRACKET 291
#define TCOMMA 292
#define TLMBRACKET 293
#define TRMBRACKET 294
#define TLLBRACKET 295
#define TRLBRACKET 296
#define TSEMICOLON 297
#define TCOMMENT 298
#define TSEPERATOR 299
#define TLINE 300
#define TILLID 301




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 26 "parser.y"
{
        char *str;
}
/* Line 1529 of yacc.c.  */
#line 145 "parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

