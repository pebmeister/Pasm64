/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */



// ***********************************************************************
// Author           : Paul Baxter
// Created          : 02-23-2015
// ***********************************************************************

#pragma warning(disable:4065)
#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#include "pasm64.h"
#include "opcodes.h"
#include "node.h"
#include "genlist.h"
#include "pasm64.tab.h"
#include "symbol.h" 
#include "str.h" 




# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "pasm64.tab.h".  */
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

/* Copy the second part of user declarations.  */



#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1179

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  73
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  97
/* YYNRULES -- Number of states.  */
#define YYNSTATES  221

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   311

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      65,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    70,     2,     2,     2,     2,
      71,    72,    63,    61,    69,    62,     2,    64,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      51,    66,    50,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    67,    68,
       2,     2,     2,     2,    58,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    45,     2,     2,     2,
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
      46,    47,    48,    49,    52,    53,    54,    55,    56,    57,
      59,    60
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     7,    10,    13,    17,    20,    23,
      26,    29,    32,    35,    38,    41,    44,    47,    50,    53,
      55,    57,    60,    63,    65,    68,    71,    78,    83,    89,
      94,   100,   109,   120,   131,   142,   153,   164,   166,   168,
     172,   176,   181,   184,   186,   190,   194,   200,   203,   207,
     211,   215,   219,   221,   223,   227,   230,   235,   240,   245,
     252,   259,   264,   267,   270,   273,   276,   279,   281,   284,
     286,   289,   291,   293,   297,   299,   301,   304,   307,   310,
     313,   316,   320,   324,   328,   332,   336,   340,   344,   348,
     352,   356,   360,   364,   368,   372,   376,   380
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      74,     0,    -1,    74,    75,    -1,    -1,    92,    65,    -1,
      91,    65,    -1,    91,    92,    65,    -1,    89,    65,    -1,
      90,    65,    -1,    81,    65,    -1,    82,    65,    -1,    83,
      65,    -1,    85,    65,    -1,    86,    65,    -1,    77,    65,
      -1,    78,    65,    -1,    88,    65,    -1,    79,    65,    -1,
      80,    65,    -1,    65,    -1,    75,    -1,    76,    75,    -1,
      43,     5,    -1,    44,    -1,    38,     7,    -1,    39,     7,
      -1,    12,    93,    76,    47,    76,    22,    -1,    12,    93,
      76,    22,    -1,    10,    65,    76,    11,    93,    -1,    19,
      76,     9,    93,    -1,     8,    93,    65,    76,    23,    -1,
      27,    89,    29,    93,    65,    76,    28,     5,    -1,    27,
      89,    29,    93,    31,    93,    65,    76,    28,     5,    -1,
      27,    40,    66,    93,    29,    93,    65,    76,    28,    67,
      -1,    27,    40,    66,    93,    30,    93,    65,    76,    28,
      67,    -1,    27,    41,    66,    93,    29,    93,    65,    76,
      28,    68,    -1,    27,    41,    66,    93,    30,    93,    65,
      76,    28,    68,    -1,    93,    -1,     7,    -1,    84,    69,
      93,    -1,    84,    69,     7,    -1,    20,     5,    76,    21,
      -1,     5,    84,    -1,     5,    -1,    87,    69,     5,    -1,
       5,    66,    93,    -1,    87,    69,     5,    66,    93,    -1,
      42,    87,    -1,     5,    66,    93,    -1,     5,    15,    93,
      -1,    17,    66,    93,    -1,    17,    15,    93,    -1,     5,
      -1,     4,    -1,     4,    70,    93,    -1,     4,    94,    -1,
       4,    94,    69,    67,    -1,     4,    94,    69,    68,    -1,
       4,    71,    93,    72,    -1,     4,    71,    93,    69,    67,
      72,    -1,     4,    71,    93,    72,    69,    68,    -1,     4,
      94,    69,    93,    -1,    16,    93,    -1,    37,    93,    -1,
      33,    84,    -1,    34,    84,    -1,    26,    84,    -1,    13,
      -1,    13,    84,    -1,    14,    -1,    14,    84,    -1,    94,
      -1,    63,    -1,    71,    93,    72,    -1,     3,    -1,     5,
      -1,    62,    93,    -1,    45,    93,    -1,    51,    93,    -1,
      50,    93,    -1,    32,    93,    -1,    93,    57,    93,    -1,
      93,    56,    93,    -1,    93,    49,    93,    -1,    93,    48,
      93,    -1,    93,    51,    93,    -1,    93,    50,    93,    -1,
      93,    55,    93,    -1,    93,    54,    93,    -1,    93,    52,
      93,    -1,    93,    53,    93,    -1,    93,    59,    93,    -1,
      93,    60,    93,    -1,    93,    58,    93,    -1,    93,    61,
      93,    -1,    93,    62,    93,    -1,    93,    63,    93,    -1,
      93,    64,    93,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    67,    67,    68,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      91,    92,    96,   100,   104,   108,   112,   113,   117,   118,
     119,   120,   121,   125,   126,   127,   128,   132,   133,   134,
     135,   139,   143,   147,   148,   149,   150,   154,   158,   159,
     163,   164,   168,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   203,   204,   205,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "OPCODE", "SYMBOL",
  "MACROPARAM", "STRING_LITERAL", "WHILE", "ENDDO", "REPEAT", "UNTIL",
  "IF", "PRINT", "PRINTALL", "EQU", "ORG", "PCASSIGN", "END", "DO",
  "MACRO", "ENDMACRO", "ENDIF", "WEND", "STATEMENT", "EXPRLIST", "STR",
  "FOR", "NEXT", "TO", "DOWNTO", "STEP", "NOT", "BYTE", "WORD", "LOBYTE",
  "HIBYTE", "DS", "INC", "LOAD", "REGX", "REGY", "VAR", "SECTION",
  "ENDSECTION", "'~'", "UMINUS", "ELSE", "SHIFT_RIGHT", "SHIFT_LEFT",
  "'>'", "'<'", "NE", "EQ", "LE", "GE", "AND", "OR", "'^'", "BIT_AND",
  "BIT_OR", "'+'", "'-'", "'*'", "'/'", "'\\n'", "'='", "'X'", "'Y'",
  "','", "'#'", "'('", "')'", "$accept", "program", "stmt", "stmt_list",
  "section", "endsection", "include_file", "load_file", "ifexpr",
  "loopexpr", "regloopexpr", "expr_list", "macrodef", "macrocall",
  "symbol_list", "var_def", "symbol_assign", "pc_assign", "symbol_value",
  "opcode", "subexpr", "expr", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   126,   300,   301,   302,   303,
      62,    60,   304,   305,   306,   307,   308,   309,    94,   310,
     311,    43,    45,    42,    47,    10,    61,    88,    89,    44,
      35,    40,    41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    73,    74,    74,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      76,    76,    77,    78,    79,    80,    81,    81,    82,    82,
      82,    82,    82,    83,    83,    83,    83,    84,    84,    84,
      84,    85,    86,    87,    87,    87,    87,    88,    89,    89,
      90,    90,    91,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    93,    93,    93,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     2,     2,     3,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     1,
       1,     2,     2,     1,     2,     2,     6,     4,     5,     4,
       5,     8,    10,    10,    10,    10,    10,     1,     1,     3,
       3,     4,     2,     1,     3,     3,     5,     2,     3,     3,
       3,     3,     1,     1,     3,     2,     4,     4,     4,     6,
       6,     4,     2,     2,     2,     2,     2,     1,     2,     1,
       2,     1,     1,     3,     1,     1,     2,     2,     2,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     1,    53,    52,     0,     0,     0,    67,    69,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    23,    19,     2,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      74,    75,     0,     0,     0,     0,     0,    72,     0,     0,
       0,    71,    38,     0,     0,     0,    42,    37,    71,     0,
       0,     0,    68,    70,    62,     0,     0,    20,     0,     0,
      66,     0,     0,     0,     0,    64,    65,    63,    24,    25,
      43,    47,    22,    14,    15,    17,    18,     9,    10,    11,
      12,    13,    16,     7,     8,     5,     0,     4,    80,    77,
      79,    78,    76,    54,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    49,    48,     0,     0,     0,     0,     0,
      51,    50,     0,    21,     0,     0,     0,     0,     0,     0,
       6,     0,    73,    84,    83,    86,    85,    89,    90,    88,
      87,    82,    81,    93,    91,    92,    94,    95,    96,    97,
      56,    57,    61,    73,    40,    39,     0,     0,    27,     0,
      29,    41,     0,     0,     0,    45,    44,     0,     0,    30,
      28,     0,     0,     0,     0,     0,     0,     0,     0,    59,
      60,    26,     0,     0,     0,     0,     0,     0,    46,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      31,     0,     0,     0,     0,     0,    33,    34,    35,    36,
      32
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,    67,    68,    26,    27,    28,    29,    30,    31,
      32,    56,    33,    34,    81,    35,    36,    37,    38,    39,
      57,    58
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -64
static const yytype_int16 yypact[] =
{
     -64,   248,   -64,    98,     6,   192,   -61,   192,   167,   167,
     192,   -14,   843,     7,   167,    21,   167,   167,   192,    20,
      22,    25,    34,   -64,   -64,   -64,   -25,   -24,   -18,   -15,
      -2,     5,     9,    10,    11,    15,    27,    29,   879,    32,
     -64,   -64,   192,   192,   192,   192,   192,   -64,   192,   192,
    1115,   -63,   -64,   192,   192,   192,   -11,  1115,   -64,  1007,
     843,   289,   -11,   -11,  1115,   192,   192,   -64,   392,   843,
     -11,    -7,    23,    36,    35,   -11,   -11,  1115,   -64,   -64,
      38,     2,   -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,
     -64,   -64,   -64,   -64,   -64,   -64,    33,   -64,  1115,  1115,
    1115,  1115,  1115,  1115,   957,   192,   192,   192,   192,   192,
     192,   192,   192,   192,   192,   192,   192,   192,   192,   192,
     192,   192,    28,  1115,  1115,   982,   170,   843,   433,   351,
    1115,  1115,   192,   -64,   474,   192,   192,   192,   192,    88,
     -64,    57,   -37,   921,   921,    24,    24,    24,    24,    24,
      24,    24,    24,   -27,   -27,   -27,   -44,   -44,   -64,   -64,
     -64,   -64,  1115,   -64,   -64,  1115,   515,   192,   -64,   843,
    1115,   -64,   869,   905,   939,  1115,    59,    62,    61,   -64,
    1115,   556,   192,   192,   192,   192,   192,   843,   192,   -64,
     -64,   -64,  1025,  1043,  1061,  1079,  1097,   597,  1115,   843,
     843,   843,   843,   843,    95,   638,   679,   720,   761,   802,
     -64,    64,    72,    74,    76,   135,   -64,   -64,   -64,   -64,
     -64
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -64,   -64,    -1,   -46,   -64,   -64,   -64,   -64,   -64,   -64,
     -64,     8,   -64,   -64,   -64,   -64,   130,   -64,   -64,   108,
       0,   144
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -59
static const yytype_int16 yytable[] =
{
      25,    65,   -55,    50,    60,    59,   122,    61,    53,    40,
      64,    41,    69,    52,   128,   129,    62,    63,    77,   120,
     121,    53,    70,   134,    75,    76,    71,    78,   -58,    79,
      80,    40,   178,    41,   118,   119,   120,   121,    42,    82,
      83,    84,    98,    99,   100,   101,   102,    85,   103,   104,
      86,    43,    66,   123,   124,   125,    44,    45,   126,    54,
      42,    72,    73,    87,   137,   130,   131,   133,    46,    47,
      88,   139,    54,    43,    89,    90,    91,    55,    44,    45,
      92,   166,   115,   116,   117,   118,   119,   120,   121,   135,
      46,    47,    93,   176,    94,   160,   161,    97,   140,    55,
     210,    40,   136,    41,   138,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   162,   181,   177,   188,   165,   133,   133,   190,
      42,   216,   170,   133,   189,   172,   173,   174,   175,   217,
     220,   197,   218,    43,   219,    74,    96,    51,    44,    45,
       0,     0,     0,   205,   206,   207,   208,   209,     0,     0,
      46,    47,     0,     0,     0,   133,     0,   180,    48,    49,
      40,     0,    41,    40,    52,    41,     0,   164,     0,     0,
     133,     0,   192,   193,   194,   195,   196,     0,   198,     0,
       0,     0,     0,     0,     0,    40,   133,    41,     0,    42,
       0,     0,    42,     0,   133,   133,   133,   133,   133,     0,
       0,     0,    43,     0,     0,    43,     0,    44,    45,     0,
      44,    45,     0,     0,    42,     0,     0,     0,     0,    46,
      47,     0,    46,    47,     0,     0,     0,    43,    55,     0,
       0,    55,    44,    45,     0,     0,     0,     0,     2,     0,
       0,     0,     3,     4,    46,    47,     5,     0,     6,     0,
       7,     8,     9,    55,    10,    11,     0,    12,    13,     0,
       0,     0,     0,     0,    14,    15,     0,     0,     0,     0,
       0,    16,    17,     0,     0,    18,    19,    20,     0,     0,
      21,    22,    23,     3,     4,     0,     0,     5,     0,     6,
       0,     7,     8,     9,     0,    10,    11,     0,    12,    13,
       0,     0,     0,    24,     0,    14,    15,     0,     0,     0,
       0,     0,    16,    17,     0,     0,    18,    19,    20,     0,
       0,    21,    22,    23,     0,     0,     0,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,    24,     3,     4,     0,     0,     5,
       0,     6,     0,     7,     8,     9,     0,    10,    11,     0,
      12,    13,     0,   168,     0,     0,     0,    14,    15,     0,
       0,     0,     0,     0,    16,    17,     0,     0,    18,    19,
      20,     0,     0,    21,    22,    23,     3,     4,   169,     0,
       5,   132,     6,     0,     7,     8,     9,     0,    10,    11,
       0,    12,    13,     0,     0,     0,    24,     0,    14,    15,
       0,     0,     0,     0,     0,    16,    17,     0,     0,    18,
      19,    20,     0,     0,    21,    22,    23,     3,     4,     0,
       0,     5,     0,     6,   167,     7,     8,     9,     0,    10,
      11,     0,    12,    13,     0,     0,     0,    24,     0,    14,
      15,     0,     0,     0,     0,     0,    16,    17,     0,     0,
      18,    19,    20,     0,     0,    21,    22,    23,     3,     4,
       0,     0,     5,     0,     6,     0,     7,     8,     9,     0,
      10,    11,     0,    12,    13,   171,     0,     0,    24,     0,
      14,    15,     0,     0,     0,     0,     0,    16,    17,     0,
       0,    18,    19,    20,     0,     0,    21,    22,    23,     3,
       4,     0,     0,     5,     0,     6,     0,     7,     8,     9,
       0,    10,    11,     0,    12,    13,     0,     0,   179,    24,
       0,    14,    15,     0,     0,     0,     0,     0,    16,    17,
       0,     0,    18,    19,    20,     0,     0,    21,    22,    23,
       3,     4,     0,     0,     5,     0,     6,     0,     7,     8,
       9,     0,    10,    11,     0,    12,    13,     0,   191,     0,
      24,     0,    14,    15,     0,     0,     0,     0,     0,    16,
      17,     0,     0,    18,    19,    20,     0,     0,    21,    22,
      23,     3,     4,     0,     0,     5,     0,     6,     0,     7,
       8,     9,     0,    10,    11,     0,    12,    13,     0,     0,
       0,    24,     0,    14,    15,   204,     0,     0,     0,     0,
      16,    17,     0,     0,    18,    19,    20,     0,     0,    21,
      22,    23,     3,     4,     0,     0,     5,     0,     6,     0,
       7,     8,     9,     0,    10,    11,     0,    12,    13,     0,
       0,     0,    24,     0,    14,    15,   211,     0,     0,     0,
       0,    16,    17,     0,     0,    18,    19,    20,     0,     0,
      21,    22,    23,     3,     4,     0,     0,     5,     0,     6,
       0,     7,     8,     9,     0,    10,    11,     0,    12,    13,
       0,     0,     0,    24,     0,    14,    15,   212,     0,     0,
       0,     0,    16,    17,     0,     0,    18,    19,    20,     0,
       0,    21,    22,    23,     3,     4,     0,     0,     5,     0,
       6,     0,     7,     8,     9,     0,    10,    11,     0,    12,
      13,     0,     0,     0,    24,     0,    14,    15,   213,     0,
       0,     0,     0,    16,    17,     0,     0,    18,    19,    20,
       0,     0,    21,    22,    23,     3,     4,     0,     0,     5,
       0,     6,     0,     7,     8,     9,     0,    10,    11,     0,
      12,    13,     0,     0,     0,    24,     0,    14,    15,   214,
       0,     0,     0,     0,    16,    17,     0,     0,    18,    19,
      20,     0,     0,    21,    22,    23,     3,     4,     0,     0,
       5,     0,     6,     0,     7,     8,     9,     0,    10,    11,
       0,    12,    13,     0,     0,     0,    24,     0,    14,    15,
     215,     0,     0,     0,     0,    16,    17,     0,     0,    18,
      19,    20,     0,     0,    21,    22,    23,     3,     4,     0,
       0,     5,     0,     6,     0,     7,     8,     9,     0,    10,
      11,     0,    12,    13,     0,     0,     0,    24,     0,    14,
      15,     0,     0,     0,     0,     0,    16,    17,     0,     0,
      18,    19,    20,     3,     0,    21,    22,    23,     0,     0,
       0,     0,     8,     9,     0,    10,     0,     0,   182,   183,
       0,     0,     0,     0,     0,    14,     0,     0,    24,     0,
       0,     0,    16,    17,     0,     0,    18,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   184,   185,     0,     0,     0,     0,
       0,     0,     0,     0,    95,     0,     0,     0,     0,     0,
       0,     0,     0,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     186,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,     0,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   187,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,     0,     0,     0,     0,   141,     0,     0,   142,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,     0,     0,     0,
       0,     0,     0,     0,   163,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   127,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     199,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   200,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   201,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   202,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   203,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-64)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       1,    15,    65,     3,    65,     5,    69,     7,    15,     3,
      10,     5,     5,     7,    60,    61,     8,     9,    18,    63,
      64,    15,    14,    69,    16,    17,     5,     7,    65,     7,
       5,     3,    69,     5,    61,    62,    63,    64,    32,     5,
      65,    65,    42,    43,    44,    45,    46,    65,    48,    49,
      65,    45,    66,    53,    54,    55,    50,    51,    69,    66,
      32,    40,    41,    65,    29,    65,    66,    68,    62,    63,
      65,    69,    66,    45,    65,    65,    65,    71,    50,    51,
      65,   127,    58,    59,    60,    61,    62,    63,    64,    66,
      62,    63,    65,     5,    65,    67,    68,    65,    65,    71,
       5,     3,    66,     5,    66,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   169,    67,    66,   126,   128,   129,    68,
      32,    67,   132,   134,    72,   135,   136,   137,   138,    67,
       5,   187,    68,    45,    68,    15,    38,     3,    50,    51,
      -1,    -1,    -1,   199,   200,   201,   202,   203,    -1,    -1,
      62,    63,    -1,    -1,    -1,   166,    -1,   167,    70,    71,
       3,    -1,     5,     3,     7,     5,    -1,     7,    -1,    -1,
     181,    -1,   182,   183,   184,   185,   186,    -1,   188,    -1,
      -1,    -1,    -1,    -1,    -1,     3,   197,     5,    -1,    32,
      -1,    -1,    32,    -1,   205,   206,   207,   208,   209,    -1,
      -1,    -1,    45,    -1,    -1,    45,    -1,    50,    51,    -1,
      50,    51,    -1,    -1,    32,    -1,    -1,    -1,    -1,    62,
      63,    -1,    62,    63,    -1,    -1,    -1,    45,    71,    -1,
      -1,    71,    50,    51,    -1,    -1,    -1,    -1,     0,    -1,
      -1,    -1,     4,     5,    62,    63,     8,    -1,    10,    -1,
      12,    13,    14,    71,    16,    17,    -1,    19,    20,    -1,
      -1,    -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    -1,
      -1,    33,    34,    -1,    -1,    37,    38,    39,    -1,    -1,
      42,    43,    44,     4,     5,    -1,    -1,     8,    -1,    10,
      -1,    12,    13,    14,    -1,    16,    17,    -1,    19,    20,
      -1,    -1,    -1,    65,    -1,    26,    27,    -1,    -1,    -1,
      -1,    -1,    33,    34,    -1,    -1,    37,    38,    39,    -1,
      -1,    42,    43,    44,    -1,    -1,    -1,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,     4,     5,    -1,    -1,     8,
      -1,    10,    -1,    12,    13,    14,    -1,    16,    17,    -1,
      19,    20,    -1,    22,    -1,    -1,    -1,    26,    27,    -1,
      -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    37,    38,
      39,    -1,    -1,    42,    43,    44,     4,     5,    47,    -1,
       8,     9,    10,    -1,    12,    13,    14,    -1,    16,    17,
      -1,    19,    20,    -1,    -1,    -1,    65,    -1,    26,    27,
      -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    37,
      38,    39,    -1,    -1,    42,    43,    44,     4,     5,    -1,
      -1,     8,    -1,    10,    11,    12,    13,    14,    -1,    16,
      17,    -1,    19,    20,    -1,    -1,    -1,    65,    -1,    26,
      27,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,
      37,    38,    39,    -1,    -1,    42,    43,    44,     4,     5,
      -1,    -1,     8,    -1,    10,    -1,    12,    13,    14,    -1,
      16,    17,    -1,    19,    20,    21,    -1,    -1,    65,    -1,
      26,    27,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,
      -1,    37,    38,    39,    -1,    -1,    42,    43,    44,     4,
       5,    -1,    -1,     8,    -1,    10,    -1,    12,    13,    14,
      -1,    16,    17,    -1,    19,    20,    -1,    -1,    23,    65,
      -1,    26,    27,    -1,    -1,    -1,    -1,    -1,    33,    34,
      -1,    -1,    37,    38,    39,    -1,    -1,    42,    43,    44,
       4,     5,    -1,    -1,     8,    -1,    10,    -1,    12,    13,
      14,    -1,    16,    17,    -1,    19,    20,    -1,    22,    -1,
      65,    -1,    26,    27,    -1,    -1,    -1,    -1,    -1,    33,
      34,    -1,    -1,    37,    38,    39,    -1,    -1,    42,    43,
      44,     4,     5,    -1,    -1,     8,    -1,    10,    -1,    12,
      13,    14,    -1,    16,    17,    -1,    19,    20,    -1,    -1,
      -1,    65,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,
      33,    34,    -1,    -1,    37,    38,    39,    -1,    -1,    42,
      43,    44,     4,     5,    -1,    -1,     8,    -1,    10,    -1,
      12,    13,    14,    -1,    16,    17,    -1,    19,    20,    -1,
      -1,    -1,    65,    -1,    26,    27,    28,    -1,    -1,    -1,
      -1,    33,    34,    -1,    -1,    37,    38,    39,    -1,    -1,
      42,    43,    44,     4,     5,    -1,    -1,     8,    -1,    10,
      -1,    12,    13,    14,    -1,    16,    17,    -1,    19,    20,
      -1,    -1,    -1,    65,    -1,    26,    27,    28,    -1,    -1,
      -1,    -1,    33,    34,    -1,    -1,    37,    38,    39,    -1,
      -1,    42,    43,    44,     4,     5,    -1,    -1,     8,    -1,
      10,    -1,    12,    13,    14,    -1,    16,    17,    -1,    19,
      20,    -1,    -1,    -1,    65,    -1,    26,    27,    28,    -1,
      -1,    -1,    -1,    33,    34,    -1,    -1,    37,    38,    39,
      -1,    -1,    42,    43,    44,     4,     5,    -1,    -1,     8,
      -1,    10,    -1,    12,    13,    14,    -1,    16,    17,    -1,
      19,    20,    -1,    -1,    -1,    65,    -1,    26,    27,    28,
      -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    37,    38,
      39,    -1,    -1,    42,    43,    44,     4,     5,    -1,    -1,
       8,    -1,    10,    -1,    12,    13,    14,    -1,    16,    17,
      -1,    19,    20,    -1,    -1,    -1,    65,    -1,    26,    27,
      28,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    37,
      38,    39,    -1,    -1,    42,    43,    44,     4,     5,    -1,
      -1,     8,    -1,    10,    -1,    12,    13,    14,    -1,    16,
      17,    -1,    19,    20,    -1,    -1,    -1,    65,    -1,    26,
      27,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,
      37,    38,    39,     4,    -1,    42,    43,    44,    -1,    -1,
      -1,    -1,    13,    14,    -1,    16,    -1,    -1,    29,    30,
      -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,    65,    -1,
      -1,    -1,    33,    34,    -1,    -1,    37,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    29,    30,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      31,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    -1,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    -1,    -1,    -1,    -1,    69,    -1,    -1,    72,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    74,     0,     4,     5,     8,    10,    12,    13,    14,
      16,    17,    19,    20,    26,    27,    33,    34,    37,    38,
      39,    42,    43,    44,    65,    75,    77,    78,    79,    80,
      81,    82,    83,    85,    86,    88,    89,    90,    91,    92,
       3,     5,    32,    45,    50,    51,    62,    63,    70,    71,
      93,    94,     7,    15,    66,    71,    84,    93,    94,    93,
      65,    93,    84,    84,    93,    15,    66,    75,    76,     5,
      84,     5,    40,    41,    89,    84,    84,    93,     7,     7,
       5,    87,     5,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    92,    65,    93,    93,
      93,    93,    93,    93,    93,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    69,    93,    93,    93,    69,    65,    76,    76,
      93,    93,     9,    75,    76,    66,    66,    29,    66,    69,
      65,    69,    72,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      67,    68,    93,    72,     7,    93,    76,    11,    22,    47,
      93,    21,    93,    93,    93,    93,     5,    67,    69,    23,
      93,    76,    29,    30,    29,    30,    31,    65,    66,    72,
      68,    22,    93,    93,    93,    93,    93,    76,    93,    65,
      65,    65,    65,    65,    28,    76,    76,    76,    76,    76,
       5,    28,    28,    28,    28,    28,    67,    67,    68,    68,
       5
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

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
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
      yychar = YYLEX;
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

    { Ex((yyvsp[(2) - (2)].nPtr));                                       }
    break;

  case 4:

    { (yyval.nPtr) = (yyvsp[(1) - (2)].nPtr);                                      }
    break;

  case 5:

    { (yyval.nPtr) = (yyvsp[(1) - (2)].nPtr);                                      }
    break;

  case 6:

    { Ex((yyvsp[(1) - (3)].nPtr)); (yyval.nPtr) = (yyvsp[(2) - (3)].nPtr);                              }
    break;

  case 7:

    { (yyval.nPtr) = (yyvsp[(1) - (2)].nPtr);                                      }
    break;

  case 8:

    { (yyval.nPtr) = (yyvsp[(1) - (2)].nPtr);                                      }
    break;

  case 9:

    { (yyval.nPtr) = (yyvsp[(1) - (2)].nPtr);                                      }
    break;

  case 10:

    { (yyval.nPtr) = (yyvsp[(1) - (2)].nPtr);                                      }
    break;

  case 11:

    { (yyval.nPtr) = (yyvsp[(1) - (2)].nPtr);                                      }
    break;

  case 12:

    { (yyval.nPtr) = (yyvsp[(1) - (2)].nPtr);                                      }
    break;

  case 13:

    { (yyval.nPtr) = (yyvsp[(1) - (2)].nPtr);                                      }
    break;

  case 14:

    { (yyval.nPtr) = (yyvsp[(1) - (2)].nPtr);                                      }
    break;

  case 15:

    { (yyval.nPtr) = (yyvsp[(1) - (2)].nPtr);                                      }
    break;

  case 16:

    { (yyval.nPtr) = (yyvsp[(1) - (2)].nPtr);                                      }
    break;

  case 17:

    { (yyval.nPtr) = (yyvsp[(1) - (2)].nPtr);                                      }
    break;

  case 18:

    { (yyval.nPtr) = (yyvsp[(1) - (2)].nPtr);                                      }
    break;

  case 19:

    { (yyval.nPtr) = Opr(STATEMENT, 0);                       }
    break;

  case 20:

    { (yyval.nPtr) = (yyvsp[(1) - (1)].nPtr);                                      }
    break;

  case 21:

    { (yyval.nPtr) = Opr(STATEMENT, 2, (yyvsp[(1) - (2)].nPtr), (yyvsp[(2) - (2)].nPtr));               }
    break;

  case 22:

    { (yyval.nPtr) = Opr(SECTION, 1, Id((yyvsp[(2) - (2)].sIndex)));                 }
    break;

  case 23:

    { (yyval.nPtr) = Opr(ENDSECTION, 0);                      }
    break;

  case 24:

    { (yyval.nPtr) = Opr(INC, 1, Str((yyvsp[(2) - (2)].strValue)));                    }
    break;

  case 25:

    { (yyval.nPtr) = Opr(LOAD, 1, Str((yyvsp[(2) - (2)].strValue)));                   }
    break;

  case 26:

    { (yyval.nPtr) = Opr(IF, 3, (yyvsp[(2) - (6)].nPtr), (yyvsp[(3) - (6)].nPtr), (yyvsp[(5) - (6)].nPtr));                  }
    break;

  case 27:

    { (yyval.nPtr) = Opr(IF, 2, (yyvsp[(2) - (4)].nPtr), (yyvsp[(3) - (4)].nPtr));                      }
    break;

  case 28:

    { (yyval.nPtr) = Opr(REPEAT, 2, (yyvsp[(3) - (5)].nPtr), (yyvsp[(5) - (5)].nPtr));                  }
    break;

  case 29:

    { (yyval.nPtr) = Opr(DO, 2, (yyvsp[(2) - (4)].nPtr), (yyvsp[(4) - (4)].nPtr));                      }
    break;

  case 30:

    { (yyval.nPtr) = Opr(WHILE, 2, (yyvsp[(2) - (5)].nPtr), (yyvsp[(4) - (5)].nPtr));                   }
    break;

  case 31:

    { (yyval.nPtr) = Opr(FOR, 4, (yyvsp[(2) - (8)].nPtr), (yyvsp[(4) - (8)].nPtr), (yyvsp[(6) - (8)].nPtr), Id((yyvsp[(8) - (8)].sIndex)));         }
    break;

  case 32:

    { (yyval.nPtr) = Opr(FOR, 5, (yyvsp[(2) - (10)].nPtr), (yyvsp[(4) - (10)].nPtr), (yyvsp[(8) - (10)].nPtr), Id((yyvsp[(10) - (10)].sIndex)), (yyvsp[(6) - (10)].nPtr));    }
    break;

  case 33:

    { (yyval.nPtr) = Opr(REGX, 4, (yyvsp[(4) - (10)].nPtr), (yyvsp[(6) - (10)].nPtr), (yyvsp[(8) - (10)].nPtr), Con(1, 0));     }
    break;

  case 34:

    { (yyval.nPtr) = Opr(REGX, 4, (yyvsp[(4) - (10)].nPtr), (yyvsp[(6) - (10)].nPtr), (yyvsp[(8) - (10)].nPtr), Con(-1,0));     }
    break;

  case 35:

    { (yyval.nPtr) = Opr(REGY, 4, (yyvsp[(4) - (10)].nPtr), (yyvsp[(6) - (10)].nPtr), (yyvsp[(8) - (10)].nPtr), Con(1,0));      }
    break;

  case 36:

    { (yyval.nPtr) = Opr(REGY, 4, (yyvsp[(4) - (10)].nPtr), (yyvsp[(6) - (10)].nPtr), (yyvsp[(8) - (10)].nPtr), Con(-1,0));     }
    break;

  case 37:

    { (yyval.nPtr) = Opr(EXPRLIST, 1, (yyvsp[(1) - (1)].nPtr));                    }
    break;

  case 38:

    { (yyval.nPtr) = Opr(EXPRLIST, 1, Str((yyvsp[(1) - (1)].strValue)));               }
    break;

  case 39:

    { (yyval.nPtr) = Opr(EXPRLIST, 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr));                }
    break;

  case 40:

    { (yyval.nPtr) = Opr(EXPRLIST, 2, (yyvsp[(1) - (3)].nPtr), Str((yyvsp[(3) - (3)].strValue)));           }
    break;

  case 41:

    { (yyval.nPtr) = Opr(MACRO, 2, MacroId((yyvsp[(2) - (4)].sIndex)), (yyvsp[(3) - (4)].nPtr));          }
    break;

  case 42:

    { (yyval.nPtr) = MacroEx((yyvsp[(1) - (2)].sIndex), (yyvsp[(2) - (2)].nPtr));                         }
    break;

  case 43:

    { (yyval.nPtr) = Opr(EXPRLIST, 1, Id((yyvsp[(1) - (1)].sIndex)));                }
    break;

  case 44:

    { (yyval.nPtr) = Opr(EXPRLIST, 2, (yyvsp[(1) - (3)].nPtr), Id((yyvsp[(3) - (3)].sIndex)));            }
    break;

  case 45:

    { (yyval.nPtr) = Opr(EXPRLIST, 3, Id((yyvsp[(1) - (3)].sIndex)), (yyvsp[(3) - (3)].nPtr));            }
    break;

  case 46:

    { (yyval.nPtr) = Opr(EXPRLIST, 3, (yyvsp[(1) - (5)].nPtr), Id((yyvsp[(3) - (5)].sIndex)), (yyvsp[(5) - (5)].nPtr));        }
    break;

  case 47:

    { (yyval.nPtr) = Opr(VAR, 1, (yyvsp[(2) - (2)].nPtr));                         }
    break;

  case 48:

    { (yyval.nPtr) = Opr('=', 2, Id((yyvsp[(1) - (3)].sIndex)), (yyvsp[(3) - (3)].nPtr));                 }
    break;

  case 49:

    { (yyval.nPtr) = Opr(EQU, 2, Id((yyvsp[(1) - (3)].sIndex)), (yyvsp[(3) - (3)].nPtr));                 }
    break;

  case 50:

    { (yyval.nPtr) = Opr(PCASSIGN, 1, (yyvsp[(3) - (3)].nPtr));                    }
    break;

  case 51:

    { (yyval.nPtr) = Opr(PCASSIGN, 2, (yyvsp[(3) - (3)].nPtr));                    }
    break;

  case 52:

    {                                                
                                            SymbolTablePtr sym = LookUpSymbol((yyvsp[(1) - (1)].sIndex));
                                            if (sym && sym->ismacroname)
                                            {
                                                (yyval.nPtr) = MacroEx((yyvsp[(1) - (1)].sIndex), NULL);
                                            }
                                            else
                                            {
                                                (yyval.nPtr) = Opr('=', 2, Id((yyvsp[(1) - (1)].sIndex)), Con(PC, TRUE));
                                            }
                                        }
    break;

  case 53:

    { (yyval.nPtr) = Opcode((yyvsp[(1) - (1)].iValue), i, 0);                        }
    break;

  case 54:

    { (yyval.nPtr) = Opcode((yyvsp[(1) - (3)].iValue), I, 1, (yyvsp[(3) - (3)].nPtr));                    }
    break;

  case 55:

    { (yyval.nPtr) = Opcode((yyvsp[(1) - (2)].iValue), a, 1, (yyvsp[(2) - (2)].nPtr));                    }
    break;

  case 56:

    { (yyval.nPtr) = Opcode((yyvsp[(1) - (4)].iValue), ax, 1, (yyvsp[(2) - (4)].nPtr));                   }
    break;

  case 57:

    { (yyval.nPtr) = Opcode((yyvsp[(1) - (4)].iValue), ay, 1, (yyvsp[(2) - (4)].nPtr));                   }
    break;

  case 58:

    { (yyval.nPtr) = Opcode((yyvsp[(1) - (4)].iValue), ind, 1, (yyvsp[(3) - (4)].nPtr));                  }
    break;

  case 59:

    { (yyval.nPtr) = Opcode((yyvsp[(1) - (6)].iValue), aix, 1, (yyvsp[(3) - (6)].nPtr));                  }
    break;

  case 60:

    { (yyval.nPtr) = Opcode((yyvsp[(1) - (6)].iValue), zpiy, 1, (yyvsp[(3) - (6)].nPtr));                 }
    break;

  case 61:

    { (yyval.nPtr) = Opcode((yyvsp[(1) - (4)].iValue), zr, 2, (yyvsp[(2) - (4)].nPtr), (yyvsp[(4) - (4)].nPtr));               }
    break;

  case 62:

    { (yyval.nPtr) = Opr(ORG, 1, (yyvsp[(2) - (2)].nPtr));                         }
    break;

  case 63:

    { (yyval.nPtr) = Opr(DS, 1, (yyvsp[(2) - (2)].nPtr));                          }
    break;

  case 64:

    { (yyval.nPtr) = Data(1, (yyvsp[(2) - (2)].nPtr));                             }
    break;

  case 65:

    { (yyval.nPtr) = Data(2, (yyvsp[(2) - (2)].nPtr));                             }
    break;

  case 66:

    { (yyval.nPtr) = Data(0, (yyvsp[(2) - (2)].nPtr));	 							}
    break;

  case 67:

    { (yyval.nPtr) = Opr(PRINT, 0);                           }
    break;

  case 68:

    { (yyval.nPtr) = Opr(PRINT, 1, (yyvsp[(2) - (2)].nPtr));                       }
    break;

  case 69:

    { (yyval.nPtr) = Opr(PRINTALL, 0);                        }
    break;

  case 70:

    { (yyval.nPtr) = Opr(PRINTALL, 1, (yyvsp[(2) - (2)].nPtr));                    }
    break;

  case 71:

    { (yyval.nPtr) = (yyvsp[(1) - (1)].nPtr);                                      }
    break;

  case 72:

    { (yyval.nPtr) = Con(PC, TRUE);                           }
    break;

  case 73:

    { (yyval.nPtr) = (yyvsp[(2) - (3)].nPtr);                                      }
    break;

  case 74:

    { (yyval.nPtr) = Con((yyvsp[(1) - (1)].iValue), FALSE);                          }
    break;

  case 75:

    { (yyval.nPtr) = Id((yyvsp[(1) - (1)].sIndex));                                  }
    break;

  case 76:

    { (yyval.nPtr) = Opr(UMINUS, 1, (yyvsp[(2) - (2)].nPtr));                      }
    break;

  case 77:

    { (yyval.nPtr) = Opr('~', 1, (yyvsp[(2) - (2)].nPtr));                         }
    break;

  case 78:

    { (yyval.nPtr) = Opr(LOBYTE, 1, (yyvsp[(2) - (2)].nPtr));                      }
    break;

  case 79:

    { (yyval.nPtr) = Opr(HIBYTE, 1, (yyvsp[(2) - (2)].nPtr));                      }
    break;

  case 80:

    { (yyval.nPtr) = Opr(NOT, 1, (yyvsp[(2) - (2)].nPtr));                         }
    break;

  case 81:

    { (yyval.nPtr) = Opr(OR, 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr));                      }
    break;

  case 82:

    { (yyval.nPtr) = Opr(AND, 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr));                     }
    break;

  case 83:

    { (yyval.nPtr) = Opr(SHIFT_LEFT, 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr));              }
    break;

  case 84:

    { (yyval.nPtr) = Opr(SHIFT_RIGHT, 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr));             }
    break;

  case 85:

    { (yyval.nPtr) = Opr('<', 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr));                     }
    break;

  case 86:

    { (yyval.nPtr) = Opr('>', 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr));                     }
    break;

  case 87:

    { (yyval.nPtr) = Opr(GE, 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr));                      }
    break;

  case 88:

    { (yyval.nPtr) = Opr(LE, 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr));                      }
    break;

  case 89:

    { (yyval.nPtr) = Opr(NE, 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr));                      }
    break;

  case 90:

    { (yyval.nPtr) = Opr(EQ, 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr));                      }
    break;

  case 91:

    { (yyval.nPtr) = Opr(BIT_AND, 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr));                 }
    break;

  case 92:

    { (yyval.nPtr) = Opr(BIT_OR, 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr));                  }
    break;

  case 93:

    { (yyval.nPtr) = Opr('^', 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr));                     }
    break;

  case 94:

    { (yyval.nPtr) = Opr('+', 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr));                     }
    break;

  case 95:

    { (yyval.nPtr) = Opr('-', 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr));                     }
    break;

  case 96:

    { (yyval.nPtr) = Opr('*', 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr));                     }
    break;

  case 97:

    { (yyval.nPtr) = Opr('/', 2, (yyvsp[(1) - (3)].nPtr), (yyvsp[(3) - (3)].nPtr));                     }
    break;



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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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
        yyerror (yymsgp);
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
		      yytoken, &yylval);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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
		  yystos[yystate], yyvsp);
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
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}




