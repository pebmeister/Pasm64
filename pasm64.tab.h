/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
    ELSE = 300,
    UMINUS = 301,
    SHIFT_LEFT = 302,
    SHIFT_RIGHT = 303,
    OR = 304,
    AND = 305,
    GE = 306,
    LE = 307,
    EQ = 308,
    NE = 309,
    BIT_OR = 310,
    BIT_AND = 311
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{


    int iValue;                 /* integer value */
    char* strValue;      		/* string */
    char* sIndex;               /* symbol table pointer */
    parseNode *nPtr;            /* node pointer */


};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PASM64_TAB_H_INCLUDED  */
