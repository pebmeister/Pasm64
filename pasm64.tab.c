/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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
#define YYBISON_VERSION "3.0.4"

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




# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

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
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1192

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  73
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  97
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  221

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   311

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      65,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    70,     2,     2,     2,     2,
      71,    72,    63,    61,    69,    62,     2,    64,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      57,    66,    56,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    67,    68,
       2,     2,     2,     2,    60,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    47,     2,     2,     2,
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
      45,    46,    48,    49,    50,    51,    52,    53,    54,    55,
      58,    59
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
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
  "ENDSECTION", "ELSE", "UMINUS", "'~'", "SHIFT_LEFT", "SHIFT_RIGHT", "OR",
  "AND", "GE", "LE", "EQ", "NE", "'>'", "'<'", "BIT_OR", "BIT_AND", "'^'",
  "'+'", "'-'", "'*'", "'/'", "'\\n'", "'='", "'X'", "'Y'", "','", "'#'",
  "'('", "')'", "$accept", "program", "stmt", "stmt_list", "section",
  "endsection", "include_file", "load_file", "ifexpr", "loopexpr",
  "regloopexpr", "expr_list", "macrodef", "macrocall", "symbol_list",
  "var_def", "symbol_assign", "pc_assign", "symbol_value", "opcode",
  "subexpr", "expr", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   126,   302,   303,
     304,   305,   306,   307,   308,   309,    62,    60,   310,   311,
      94,    43,    45,    42,    47,    10,    61,    88,    89,    44,
      35,    40,    41
};
# endif

#define YYPACT_NINF -62

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-62)))

#define YYTABLE_NINF -59

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -62,   302,   -62,   168,    26,   242,   -49,   242,   187,   187,
     242,   -14,   898,    23,   187,    -3,   187,   187,   242,    25,
      27,    30,    31,   -62,   -62,   -62,   -35,   -26,   -25,   -18,
     -15,    -6,    -5,    -4,    -2,     4,     5,     6,   238,     7,
     -62,   -62,   242,   242,   242,   242,   242,   -62,   242,   242,
     918,   -61,   -62,   242,   242,   242,   -13,   918,   -62,  1037,
     898,   343,   -13,   -13,   918,   242,   242,   -62,   447,   898,
     -13,    -9,     2,    18,    22,   -13,   -13,   918,   -62,   -62,
      19,    -7,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,
     -62,   -62,   -62,   -62,   -62,   -62,    21,   -62,   918,   918,
     918,   918,   918,   918,   987,   242,   242,   242,   242,   242,
     242,   242,   242,   242,   242,   242,   242,   242,   242,   242,
     242,   242,   155,   918,   918,  1012,   230,   898,   488,   405,
     918,   918,   242,   -62,   529,   242,   242,   242,   242,    59,
     -62,    20,   -56,   951,   951,    16,    16,    16,    16,    16,
      16,    16,    16,   -37,   -37,   -37,   -42,   -42,   -62,   -62,
     -62,   -62,   918,   -62,   -62,   918,   570,   242,   -62,   898,
     918,   -62,   897,   935,   969,   918,    24,    28,    33,   -62,
     918,   611,   242,   242,   242,   242,   242,   898,   242,   -62,
     -62,   -62,  1055,  1073,  1091,  1109,  1127,   652,   918,   898,
     898,   898,   898,   898,    86,   693,   734,   775,   816,   857,
     -62,    29,    32,    34,    35,    88,   -62,   -62,   -62,   -62,
     -62
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
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
       6,     0,    73,    83,    84,    81,    82,    87,    88,    90,
      89,    86,    85,    92,    91,    93,    94,    95,    96,    97,
      56,    57,    61,    73,    40,    39,     0,     0,    27,     0,
      29,    41,     0,     0,     0,    45,    44,     0,     0,    30,
      28,     0,     0,     0,     0,     0,     0,     0,     0,    59,
      60,    26,     0,     0,     0,     0,     0,     0,    46,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      31,     0,     0,     0,     0,     0,    33,    34,    35,    36,
      32
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -62,   -62,    -1,   -46,   -62,   -62,   -62,   -62,   -62,   -62,
     -62,     3,   -62,   -62,   -62,   -62,    79,   -62,   -62,    57,
       0,    95
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,    67,    68,    26,    27,    28,    29,    30,    31,
      32,    56,    33,    34,    81,    35,    36,    37,    38,    39,
      57,    58
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      25,    65,    71,    50,   -55,    59,    53,    61,   122,   -58,
      64,    62,    63,   178,   128,   129,    60,    70,    77,    75,
      76,   120,   121,   134,   118,   119,   120,   121,    69,    40,
      83,    41,    78,    52,    79,    80,    82,    72,    73,    84,
      85,    53,    98,    99,   100,   101,   102,    86,   103,   104,
      87,   137,    66,   123,   124,   125,   126,    54,    42,    88,
      89,    90,   139,    91,   176,   130,   131,   133,   135,    92,
      93,    94,    97,    43,   115,   116,   117,   118,   119,   120,
     121,   166,    44,    45,   136,   138,   140,   177,    46,    47,
     188,   210,    54,   220,    74,    96,   216,    55,    51,   217,
     189,   190,   218,   219,     0,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   162,   181,     0,     0,   165,   133,   133,     0,
       0,     0,   170,   133,     0,   172,   173,   174,   175,     0,
       0,   197,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   205,   206,   207,   208,   209,    40,     0,
      41,     0,     0,     0,     0,   133,     0,   180,     0,     0,
       0,    40,     0,    41,     0,     0,     0,     0,     0,     0,
     133,     0,   192,   193,   194,   195,   196,    42,   198,     0,
      40,     0,    41,     0,    52,     0,   133,     0,     0,     0,
      42,     0,    43,     0,   133,   133,   133,   133,   133,     0,
       0,    44,    45,     0,     0,    43,     0,    46,    47,    42,
       0,     0,   160,   161,    44,    45,    55,     0,     0,     0,
      46,    47,     0,    40,    43,    41,     0,   164,    48,    49,
       0,     0,     3,    44,    45,    40,     0,    41,     0,    46,
      47,     8,     9,     0,    10,     0,     0,     0,    55,     0,
       0,     0,    42,     0,    14,     0,     0,     0,     0,     0,
       0,    16,    17,     0,    42,    18,     0,    43,     0,     0,
       0,     0,     0,     0,     0,     0,    44,    45,     0,    43,
       0,     0,    46,    47,     0,     0,     0,     0,    44,    45,
       0,    55,     2,    95,    46,    47,     3,     4,     0,     0,
       5,     0,     6,    55,     7,     8,     9,     0,    10,    11,
       0,    12,    13,     0,     0,     0,     0,     0,    14,    15,
       0,     0,     0,     0,     0,    16,    17,     0,     0,    18,
      19,    20,     0,     0,    21,    22,    23,     3,     4,     0,
       0,     5,     0,     6,     0,     7,     8,     9,     0,    10,
      11,     0,    12,    13,     0,     0,     0,    24,     0,    14,
      15,     0,     0,     0,     0,     0,    16,    17,     0,     0,
      18,    19,    20,     0,     0,    21,    22,    23,     0,     0,
       0,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,    24,     3,
       4,     0,     0,     5,     0,     6,     0,     7,     8,     9,
       0,    10,    11,     0,    12,    13,     0,   168,     0,     0,
       0,    14,    15,     0,     0,     0,     0,     0,    16,    17,
       0,     0,    18,    19,    20,     0,     0,    21,    22,    23,
     169,     3,     4,     0,     0,     5,   132,     6,     0,     7,
       8,     9,     0,    10,    11,     0,    12,    13,     0,     0,
      24,     0,     0,    14,    15,     0,     0,     0,     0,     0,
      16,    17,     0,     0,    18,    19,    20,     0,     0,    21,
      22,    23,     3,     4,     0,     0,     5,     0,     6,   167,
       7,     8,     9,     0,    10,    11,     0,    12,    13,     0,
       0,     0,    24,     0,    14,    15,     0,     0,     0,     0,
       0,    16,    17,     0,     0,    18,    19,    20,     0,     0,
      21,    22,    23,     3,     4,     0,     0,     5,     0,     6,
       0,     7,     8,     9,     0,    10,    11,     0,    12,    13,
     171,     0,     0,    24,     0,    14,    15,     0,     0,     0,
       0,     0,    16,    17,     0,     0,    18,    19,    20,     0,
       0,    21,    22,    23,     3,     4,     0,     0,     5,     0,
       6,     0,     7,     8,     9,     0,    10,    11,     0,    12,
      13,     0,     0,   179,    24,     0,    14,    15,     0,     0,
       0,     0,     0,    16,    17,     0,     0,    18,    19,    20,
       0,     0,    21,    22,    23,     3,     4,     0,     0,     5,
       0,     6,     0,     7,     8,     9,     0,    10,    11,     0,
      12,    13,     0,   191,     0,    24,     0,    14,    15,     0,
       0,     0,     0,     0,    16,    17,     0,     0,    18,    19,
      20,     0,     0,    21,    22,    23,     3,     4,     0,     0,
       5,     0,     6,     0,     7,     8,     9,     0,    10,    11,
       0,    12,    13,     0,     0,     0,    24,     0,    14,    15,
     204,     0,     0,     0,     0,    16,    17,     0,     0,    18,
      19,    20,     0,     0,    21,    22,    23,     3,     4,     0,
       0,     5,     0,     6,     0,     7,     8,     9,     0,    10,
      11,     0,    12,    13,     0,     0,     0,    24,     0,    14,
      15,   211,     0,     0,     0,     0,    16,    17,     0,     0,
      18,    19,    20,     0,     0,    21,    22,    23,     3,     4,
       0,     0,     5,     0,     6,     0,     7,     8,     9,     0,
      10,    11,     0,    12,    13,     0,     0,     0,    24,     0,
      14,    15,   212,     0,     0,     0,     0,    16,    17,     0,
       0,    18,    19,    20,     0,     0,    21,    22,    23,     3,
       4,     0,     0,     5,     0,     6,     0,     7,     8,     9,
       0,    10,    11,     0,    12,    13,     0,     0,     0,    24,
       0,    14,    15,   213,     0,     0,     0,     0,    16,    17,
       0,     0,    18,    19,    20,     0,     0,    21,    22,    23,
       3,     4,     0,     0,     5,     0,     6,     0,     7,     8,
       9,     0,    10,    11,     0,    12,    13,     0,     0,     0,
      24,     0,    14,    15,   214,     0,     0,     0,     0,    16,
      17,     0,     0,    18,    19,    20,     0,     0,    21,    22,
      23,     3,     4,     0,     0,     5,     0,     6,     0,     7,
       8,     9,     0,    10,    11,     0,    12,    13,     0,     0,
       0,    24,     0,    14,    15,   215,     0,     0,     0,     0,
      16,    17,     0,     0,    18,    19,    20,     0,     0,    21,
      22,    23,     3,     4,     0,     0,     5,     0,     6,     0,
       7,     8,     9,     0,    10,    11,     0,    12,    13,     0,
       0,     0,    24,     0,    14,    15,   182,   183,     0,     0,
       0,    16,    17,     0,     0,    18,    19,    20,     0,     0,
      21,    22,    23,     0,     0,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,     0,    24,   184,   185,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   105,   106,   107,   108,   109,   110,   111,
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
     120,   121,   203
};

static const yytype_int16 yycheck[] =
{
       1,    15,     5,     3,    65,     5,    15,     7,    69,    65,
      10,     8,     9,    69,    60,    61,    65,    14,    18,    16,
      17,    63,    64,    69,    61,    62,    63,    64,     5,     3,
      65,     5,     7,     7,     7,     5,     5,    40,    41,    65,
      65,    15,    42,    43,    44,    45,    46,    65,    48,    49,
      65,    29,    66,    53,    54,    55,    69,    66,    32,    65,
      65,    65,    69,    65,     5,    65,    66,    68,    66,    65,
      65,    65,    65,    47,    58,    59,    60,    61,    62,    63,
      64,   127,    56,    57,    66,    66,    65,    67,    62,    63,
      66,     5,    66,     5,    15,    38,    67,    71,     3,    67,
      72,    68,    68,    68,    -1,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   169,    -1,    -1,   126,   128,   129,    -1,
      -1,    -1,   132,   134,    -1,   135,   136,   137,   138,    -1,
      -1,   187,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   199,   200,   201,   202,   203,     3,    -1,
       5,    -1,    -1,    -1,    -1,   166,    -1,   167,    -1,    -1,
      -1,     3,    -1,     5,    -1,    -1,    -1,    -1,    -1,    -1,
     181,    -1,   182,   183,   184,   185,   186,    32,   188,    -1,
       3,    -1,     5,    -1,     7,    -1,   197,    -1,    -1,    -1,
      32,    -1,    47,    -1,   205,   206,   207,   208,   209,    -1,
      -1,    56,    57,    -1,    -1,    47,    -1,    62,    63,    32,
      -1,    -1,    67,    68,    56,    57,    71,    -1,    -1,    -1,
      62,    63,    -1,     3,    47,     5,    -1,     7,    70,    71,
      -1,    -1,     4,    56,    57,     3,    -1,     5,    -1,    62,
      63,    13,    14,    -1,    16,    -1,    -1,    -1,    71,    -1,
      -1,    -1,    32,    -1,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    34,    -1,    32,    37,    -1,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    -1,    47,
      -1,    -1,    62,    63,    -1,    -1,    -1,    -1,    56,    57,
      -1,    71,     0,    65,    62,    63,     4,     5,    -1,    -1,
       8,    -1,    10,    71,    12,    13,    14,    -1,    16,    17,
      -1,    19,    20,    -1,    -1,    -1,    -1,    -1,    26,    27,
      -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    37,
      38,    39,    -1,    -1,    42,    43,    44,     4,     5,    -1,
      -1,     8,    -1,    10,    -1,    12,    13,    14,    -1,    16,
      17,    -1,    19,    20,    -1,    -1,    -1,    65,    -1,    26,
      27,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,
      37,    38,    39,    -1,    -1,    42,    43,    44,    -1,    -1,
      -1,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,     4,
       5,    -1,    -1,     8,    -1,    10,    -1,    12,    13,    14,
      -1,    16,    17,    -1,    19,    20,    -1,    22,    -1,    -1,
      -1,    26,    27,    -1,    -1,    -1,    -1,    -1,    33,    34,
      -1,    -1,    37,    38,    39,    -1,    -1,    42,    43,    44,
      45,     4,     5,    -1,    -1,     8,     9,    10,    -1,    12,
      13,    14,    -1,    16,    17,    -1,    19,    20,    -1,    -1,
      65,    -1,    -1,    26,    27,    -1,    -1,    -1,    -1,    -1,
      33,    34,    -1,    -1,    37,    38,    39,    -1,    -1,    42,
      43,    44,     4,     5,    -1,    -1,     8,    -1,    10,    11,
      12,    13,    14,    -1,    16,    17,    -1,    19,    20,    -1,
      -1,    -1,    65,    -1,    26,    27,    -1,    -1,    -1,    -1,
      -1,    33,    34,    -1,    -1,    37,    38,    39,    -1,    -1,
      42,    43,    44,     4,     5,    -1,    -1,     8,    -1,    10,
      -1,    12,    13,    14,    -1,    16,    17,    -1,    19,    20,
      21,    -1,    -1,    65,    -1,    26,    27,    -1,    -1,    -1,
      -1,    -1,    33,    34,    -1,    -1,    37,    38,    39,    -1,
      -1,    42,    43,    44,     4,     5,    -1,    -1,     8,    -1,
      10,    -1,    12,    13,    14,    -1,    16,    17,    -1,    19,
      20,    -1,    -1,    23,    65,    -1,    26,    27,    -1,    -1,
      -1,    -1,    -1,    33,    34,    -1,    -1,    37,    38,    39,
      -1,    -1,    42,    43,    44,     4,     5,    -1,    -1,     8,
      -1,    10,    -1,    12,    13,    14,    -1,    16,    17,    -1,
      19,    20,    -1,    22,    -1,    65,    -1,    26,    27,    -1,
      -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    37,    38,
      39,    -1,    -1,    42,    43,    44,     4,     5,    -1,    -1,
       8,    -1,    10,    -1,    12,    13,    14,    -1,    16,    17,
      -1,    19,    20,    -1,    -1,    -1,    65,    -1,    26,    27,
      28,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    37,
      38,    39,    -1,    -1,    42,    43,    44,     4,     5,    -1,
      -1,     8,    -1,    10,    -1,    12,    13,    14,    -1,    16,
      17,    -1,    19,    20,    -1,    -1,    -1,    65,    -1,    26,
      27,    28,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,
      37,    38,    39,    -1,    -1,    42,    43,    44,     4,     5,
      -1,    -1,     8,    -1,    10,    -1,    12,    13,    14,    -1,
      16,    17,    -1,    19,    20,    -1,    -1,    -1,    65,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,    33,    34,    -1,
      -1,    37,    38,    39,    -1,    -1,    42,    43,    44,     4,
       5,    -1,    -1,     8,    -1,    10,    -1,    12,    13,    14,
      -1,    16,    17,    -1,    19,    20,    -1,    -1,    -1,    65,
      -1,    26,    27,    28,    -1,    -1,    -1,    -1,    33,    34,
      -1,    -1,    37,    38,    39,    -1,    -1,    42,    43,    44,
       4,     5,    -1,    -1,     8,    -1,    10,    -1,    12,    13,
      14,    -1,    16,    17,    -1,    19,    20,    -1,    -1,    -1,
      65,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,    33,
      34,    -1,    -1,    37,    38,    39,    -1,    -1,    42,    43,
      44,     4,     5,    -1,    -1,     8,    -1,    10,    -1,    12,
      13,    14,    -1,    16,    17,    -1,    19,    20,    -1,    -1,
      -1,    65,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,
      33,    34,    -1,    -1,    37,    38,    39,    -1,    -1,    42,
      43,    44,     4,     5,    -1,    -1,     8,    -1,    10,    -1,
      12,    13,    14,    -1,    16,    17,    -1,    19,    20,    -1,
      -1,    -1,    65,    -1,    26,    27,    29,    30,    -1,    -1,
      -1,    33,    34,    -1,    -1,    37,    38,    39,    -1,    -1,
      42,    43,    44,    -1,    -1,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    -1,    65,    29,    30,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    48,    49,    50,    51,    52,    53,    54,
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
      63,    64,    65
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    74,     0,     4,     5,     8,    10,    12,    13,    14,
      16,    17,    19,    20,    26,    27,    33,    34,    37,    38,
      39,    42,    43,    44,    65,    75,    77,    78,    79,    80,
      81,    82,    83,    85,    86,    88,    89,    90,    91,    92,
       3,     5,    32,    47,    56,    57,    62,    63,    70,    71,
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
      67,    68,    93,    72,     7,    93,    76,    11,    22,    45,
      93,    21,    93,    93,    93,    93,     5,    67,    69,    23,
      93,    76,    29,    30,    29,    30,    31,    65,    66,    72,
      68,    22,    93,    93,    93,    93,    93,    76,    93,    65,
      65,    65,    65,    65,    28,    76,    76,    76,    76,    76,
       5,    28,    28,    28,    28,    28,    67,    67,    68,    68,
       5
};

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

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
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


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

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
      yychar = yylex ();
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
        case 2:

    { Ex((yyvsp[0].nPtr));                                       }

    break;

  case 4:

    { (yyval.nPtr) = (yyvsp[-1].nPtr);                                      }

    break;

  case 5:

    { (yyval.nPtr) = (yyvsp[-1].nPtr);                                      }

    break;

  case 6:

    { Ex((yyvsp[-2].nPtr)); (yyval.nPtr) = (yyvsp[-1].nPtr);                              }

    break;

  case 7:

    { (yyval.nPtr) = (yyvsp[-1].nPtr);                                      }

    break;

  case 8:

    { (yyval.nPtr) = (yyvsp[-1].nPtr);                                      }

    break;

  case 9:

    { (yyval.nPtr) = (yyvsp[-1].nPtr);                                      }

    break;

  case 10:

    { (yyval.nPtr) = (yyvsp[-1].nPtr);                                      }

    break;

  case 11:

    { (yyval.nPtr) = (yyvsp[-1].nPtr);                                      }

    break;

  case 12:

    { (yyval.nPtr) = (yyvsp[-1].nPtr);                                      }

    break;

  case 13:

    { (yyval.nPtr) = (yyvsp[-1].nPtr);                                      }

    break;

  case 14:

    { (yyval.nPtr) = (yyvsp[-1].nPtr);                                      }

    break;

  case 15:

    { (yyval.nPtr) = (yyvsp[-1].nPtr);                                      }

    break;

  case 16:

    { (yyval.nPtr) = (yyvsp[-1].nPtr);                                      }

    break;

  case 17:

    { (yyval.nPtr) = (yyvsp[-1].nPtr);                                      }

    break;

  case 18:

    { (yyval.nPtr) = (yyvsp[-1].nPtr);                                      }

    break;

  case 19:

    { (yyval.nPtr) = Opr(STATEMENT, 0);                       }

    break;

  case 20:

    { (yyval.nPtr) = (yyvsp[0].nPtr);                                      }

    break;

  case 21:

    { (yyval.nPtr) = Opr(STATEMENT, 2, (yyvsp[-1].nPtr), (yyvsp[0].nPtr));               }

    break;

  case 22:

    { (yyval.nPtr) = Opr(SECTION, 1, Id((yyvsp[0].sIndex)));                 }

    break;

  case 23:

    { (yyval.nPtr) = Opr(ENDSECTION, 0);                      }

    break;

  case 24:

    { (yyval.nPtr) = Opr(INC, 1, Str((yyvsp[0].strValue)));                    }

    break;

  case 25:

    { (yyval.nPtr) = Opr(LOAD, 1, Str((yyvsp[0].strValue)));                   }

    break;

  case 26:

    { (yyval.nPtr) = Opr(IF, 3, (yyvsp[-4].nPtr), (yyvsp[-3].nPtr), (yyvsp[-1].nPtr));                  }

    break;

  case 27:

    { (yyval.nPtr) = Opr(IF, 2, (yyvsp[-2].nPtr), (yyvsp[-1].nPtr));                      }

    break;

  case 28:

    { (yyval.nPtr) = Opr(REPEAT, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                  }

    break;

  case 29:

    { (yyval.nPtr) = Opr(DO, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                      }

    break;

  case 30:

    { (yyval.nPtr) = Opr(WHILE, 2, (yyvsp[-3].nPtr), (yyvsp[-1].nPtr));                   }

    break;

  case 31:

    { (yyval.nPtr) = Opr(FOR, 4, (yyvsp[-6].nPtr), (yyvsp[-4].nPtr), (yyvsp[-2].nPtr), Id((yyvsp[0].sIndex)));         }

    break;

  case 32:

    { (yyval.nPtr) = Opr(FOR, 5, (yyvsp[-8].nPtr), (yyvsp[-6].nPtr), (yyvsp[-2].nPtr), Id((yyvsp[0].sIndex)), (yyvsp[-4].nPtr));    }

    break;

  case 33:

    { (yyval.nPtr) = Opr(REGX, 4, (yyvsp[-6].nPtr), (yyvsp[-4].nPtr), (yyvsp[-2].nPtr), Con(1, 0));     }

    break;

  case 34:

    { (yyval.nPtr) = Opr(REGX, 4, (yyvsp[-6].nPtr), (yyvsp[-4].nPtr), (yyvsp[-2].nPtr), Con(-1,0));     }

    break;

  case 35:

    { (yyval.nPtr) = Opr(REGY, 4, (yyvsp[-6].nPtr), (yyvsp[-4].nPtr), (yyvsp[-2].nPtr), Con(1,0));      }

    break;

  case 36:

    { (yyval.nPtr) = Opr(REGY, 4, (yyvsp[-6].nPtr), (yyvsp[-4].nPtr), (yyvsp[-2].nPtr), Con(-1,0));     }

    break;

  case 37:

    { (yyval.nPtr) = Opr(EXPRLIST, 1, (yyvsp[0].nPtr));                    }

    break;

  case 38:

    { (yyval.nPtr) = Opr(EXPRLIST, 1, Str((yyvsp[0].strValue)));               }

    break;

  case 39:

    { (yyval.nPtr) = Opr(EXPRLIST, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                }

    break;

  case 40:

    { (yyval.nPtr) = Opr(EXPRLIST, 2, (yyvsp[-2].nPtr), Str((yyvsp[0].strValue)));           }

    break;

  case 41:

    { (yyval.nPtr) = Opr(MACRO, 2, MacroId((yyvsp[-2].sIndex)), (yyvsp[-1].nPtr));          }

    break;

  case 42:

    { (yyval.nPtr) = MacroEx((yyvsp[-1].sIndex), (yyvsp[0].nPtr));                         }

    break;

  case 43:

    { (yyval.nPtr) = Opr(EXPRLIST, 1, Id((yyvsp[0].sIndex)));                }

    break;

  case 44:

    { (yyval.nPtr) = Opr(EXPRLIST, 2, (yyvsp[-2].nPtr), Id((yyvsp[0].sIndex)));            }

    break;

  case 45:

    { (yyval.nPtr) = Opr(EXPRLIST, 3, Id((yyvsp[-2].sIndex)), (yyvsp[0].nPtr));            }

    break;

  case 46:

    { (yyval.nPtr) = Opr(EXPRLIST, 3, (yyvsp[-4].nPtr), Id((yyvsp[-2].sIndex)), (yyvsp[0].nPtr));        }

    break;

  case 47:

    { (yyval.nPtr) = Opr(VAR, 1, (yyvsp[0].nPtr));                         }

    break;

  case 48:

    { (yyval.nPtr) = Opr('=', 2, Id((yyvsp[-2].sIndex)), (yyvsp[0].nPtr));                 }

    break;

  case 49:

    { (yyval.nPtr) = Opr(EQU, 2, Id((yyvsp[-2].sIndex)), (yyvsp[0].nPtr));                 }

    break;

  case 50:

    { (yyval.nPtr) = Opr(PCASSIGN, 1, (yyvsp[0].nPtr));                    }

    break;

  case 51:

    { (yyval.nPtr) = Opr(PCASSIGN, 2, (yyvsp[0].nPtr));                    }

    break;

  case 52:

    {                                                
                                            SymbolTablePtr sym = LookUpSymbol((yyvsp[0].sIndex));
                                            if (sym && sym->ismacroname)
                                            {
                                                (yyval.nPtr) = MacroEx((yyvsp[0].sIndex), NULL);
                                            }
                                            else
                                            {
                                                (yyval.nPtr) = Opr('=', 2, Id((yyvsp[0].sIndex)), Con(PC, TRUE));
                                            }
                                        }

    break;

  case 53:

    { (yyval.nPtr) = Opcode((yyvsp[0].iValue), i, 0);                        }

    break;

  case 54:

    { (yyval.nPtr) = Opcode((yyvsp[-2].iValue), I, 1, (yyvsp[0].nPtr));                    }

    break;

  case 55:

    { (yyval.nPtr) = Opcode((yyvsp[-1].iValue), a, 1, (yyvsp[0].nPtr));                    }

    break;

  case 56:

    { (yyval.nPtr) = Opcode((yyvsp[-3].iValue), ax, 1, (yyvsp[-2].nPtr));                   }

    break;

  case 57:

    { (yyval.nPtr) = Opcode((yyvsp[-3].iValue), ay, 1, (yyvsp[-2].nPtr));                   }

    break;

  case 58:

    { (yyval.nPtr) = Opcode((yyvsp[-3].iValue), ind, 1, (yyvsp[-1].nPtr));                  }

    break;

  case 59:

    { (yyval.nPtr) = Opcode((yyvsp[-5].iValue), aix, 1, (yyvsp[-3].nPtr));                  }

    break;

  case 60:

    { (yyval.nPtr) = Opcode((yyvsp[-5].iValue), zpiy, 1, (yyvsp[-3].nPtr));                 }

    break;

  case 61:

    { (yyval.nPtr) = Opcode((yyvsp[-3].iValue), zr, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));               }

    break;

  case 62:

    { (yyval.nPtr) = Opr(ORG, 1, (yyvsp[0].nPtr));                         }

    break;

  case 63:

    { (yyval.nPtr) = Opr(DS, 1, (yyvsp[0].nPtr));                          }

    break;

  case 64:

    { (yyval.nPtr) = Data(1, (yyvsp[0].nPtr));                             }

    break;

  case 65:

    { (yyval.nPtr) = Data(2, (yyvsp[0].nPtr));                             }

    break;

  case 66:

    { (yyval.nPtr) = Data(0, (yyvsp[0].nPtr));	 							}

    break;

  case 67:

    { (yyval.nPtr) = Opr(PRINT, 0);                           }

    break;

  case 68:

    { (yyval.nPtr) = Opr(PRINT, 1, (yyvsp[0].nPtr));                       }

    break;

  case 69:

    { (yyval.nPtr) = Opr(PRINTALL, 0);                        }

    break;

  case 70:

    { (yyval.nPtr) = Opr(PRINTALL, 1, (yyvsp[0].nPtr));                    }

    break;

  case 71:

    { (yyval.nPtr) = (yyvsp[0].nPtr);                                      }

    break;

  case 72:

    { (yyval.nPtr) = Con(PC, TRUE);                           }

    break;

  case 73:

    { (yyval.nPtr) = (yyvsp[-1].nPtr);                                      }

    break;

  case 74:

    { (yyval.nPtr) = Con((yyvsp[0].iValue), FALSE);                          }

    break;

  case 75:

    { (yyval.nPtr) = Id((yyvsp[0].sIndex));                                  }

    break;

  case 76:

    { (yyval.nPtr) = Opr(UMINUS, 1, (yyvsp[0].nPtr));                      }

    break;

  case 77:

    { (yyval.nPtr) = Opr('~', 1, (yyvsp[0].nPtr));                         }

    break;

  case 78:

    { (yyval.nPtr) = Opr(LOBYTE, 1, (yyvsp[0].nPtr));                      }

    break;

  case 79:

    { (yyval.nPtr) = Opr(HIBYTE, 1, (yyvsp[0].nPtr));                      }

    break;

  case 80:

    { (yyval.nPtr) = Opr(NOT, 1, (yyvsp[0].nPtr));                         }

    break;

  case 81:

    { (yyval.nPtr) = Opr(OR, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                      }

    break;

  case 82:

    { (yyval.nPtr) = Opr(AND, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                     }

    break;

  case 83:

    { (yyval.nPtr) = Opr(SHIFT_LEFT, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));              }

    break;

  case 84:

    { (yyval.nPtr) = Opr(SHIFT_RIGHT, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));             }

    break;

  case 85:

    { (yyval.nPtr) = Opr('<', 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                     }

    break;

  case 86:

    { (yyval.nPtr) = Opr('>', 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                     }

    break;

  case 87:

    { (yyval.nPtr) = Opr(GE, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                      }

    break;

  case 88:

    { (yyval.nPtr) = Opr(LE, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                      }

    break;

  case 89:

    { (yyval.nPtr) = Opr(NE, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                      }

    break;

  case 90:

    { (yyval.nPtr) = Opr(EQ, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                      }

    break;

  case 91:

    { (yyval.nPtr) = Opr(BIT_AND, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                 }

    break;

  case 92:

    { (yyval.nPtr) = Opr(BIT_OR, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                  }

    break;

  case 93:

    { (yyval.nPtr) = Opr('^', 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                     }

    break;

  case 94:

    { (yyval.nPtr) = Opr('+', 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                     }

    break;

  case 95:

    { (yyval.nPtr) = Opr('-', 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                     }

    break;

  case 96:

    { (yyval.nPtr) = Opr('*', 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                     }

    break;

  case 97:

    { (yyval.nPtr) = Opr('/', 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                     }

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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}


