/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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

#ifndef YY_YY_PASM64_TAB_H_INCLUDED
# define YY_YY_PASM64_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INTEGER = 258,
     OPCODE = 259,
     SYMBOL = 260,
     MACROPARAM = 261,
     STRING_LITERAL = 262,
     WHILE = 263,
     ENDDO = 264,
     REPEAT = 265,
     UNTIL = 266,
     IF = 267,
     PRINT = 268,
     PRINTALL = 269,
     EQU = 270,
     ORG = 271,
     PCASSIGN = 272,
     END = 273,
     DO = 274,
     MACRO = 275,
     ENDMACRO = 276,
     ENDIF = 277,
     WEND = 278,
     STATEMENT = 279,
     EXPRLIST = 280,
     STR = 281,
     FOR = 282,
     NEXT = 283,
     TO = 284,
     DOWNTO = 285,
     STEP = 286,
     NOT = 287,
     BYTE = 288,
     WORD = 289,
     LOBYTE = 290,
     HIBYTE = 291,
     DS = 292,
     INC = 293,
     LOAD = 294,
     REGX = 295,
     REGY = 296,
     VAR = 297,
     SECTION = 298,
     ENDSECTION = 299,
     UMINUS = 300,
     ELSE = 301,
     SHIFT_RIGHT = 302,
     SHIFT_LEFT = 303,
     NE = 304,
     EQ = 305,
     LE = 306,
     GE = 307,
     AND = 308,
     OR = 309,
     BIT_AND = 310,
     BIT_OR = 311
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{


    int iValue;                 /* integer value */
    char* strValue;      		/* string */
    char* sIndex;               /* symbol table pointer */
    parseNode *nPtr;            /* node pointer */



} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_PASM64_TAB_H_INCLUDED  */
