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
#include "mem.h"




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
    MSYM = 298,
    PSYM = 299,
    SECTION = 300,
    ENDSECTION = 301,
    ELSE = 302,
    UMINUS = 303,
    SHIFT_LEFT = 304,
    SHIFT_RIGHT = 305,
    OR = 306,
    AND = 307,
    GE = 308,
    LE = 309,
    EQ = 310,
    NE = 311,
    BIT_OR = 312,
    BIT_AND = 313
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
#define YYLAST   1246

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  75
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  107
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  239

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   313

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      67,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    72,     2,     2,     2,     2,
      73,    74,    65,    63,    71,    64,     2,    66,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      59,    68,    58,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    69,    70,
       2,     2,     2,     2,    62,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    49,     2,     2,     2,
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
      45,    46,    47,    48,    50,    51,    52,    53,    54,    55,
      56,    57,    60,    61
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    68,    68,    69,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      92,    93,    97,   101,   105,   109,   113,   114,   118,   119,
     120,   121,   122,   126,   127,   128,   129,   133,   134,   135,
     136,   140,   144,   148,   149,   150,   151,   155,   159,   160,
     164,   165,   169,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   193,   194,   195,   196,   197,   199,   200,   201,
     202,   203,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   217,   218,   219,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246
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
  "HIBYTE", "DS", "INC", "LOAD", "REGX", "REGY", "VAR", "MSYM", "PSYM",
  "SECTION", "ENDSECTION", "ELSE", "UMINUS", "'~'", "SHIFT_LEFT",
  "SHIFT_RIGHT", "OR", "AND", "GE", "LE", "EQ", "NE", "'>'", "'<'",
  "BIT_OR", "BIT_AND", "'^'", "'+'", "'-'", "'*'", "'/'", "'\\n'", "'='",
  "'X'", "'Y'", "','", "'#'", "'('", "')'", "$accept", "program", "stmt",
  "stmt_list", "section", "endsection", "include_file", "load_file",
  "ifexpr", "loopexpr", "regloopexpr", "expr_list", "macrodef",
  "macrocall", "symbol_list", "var_def", "symbol_assign", "pc_assign",
  "symbol_value", "opcode", "subexpr", "expr", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   126,
     304,   305,   306,   307,   308,   309,   310,   311,    62,    60,
     312,   313,    94,    43,    45,    42,    47,    10,    61,    88,
      89,    44,    35,    40,    41
};
# endif

#define YYPACT_NINF -71

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-71)))

#define YYTABLE_NINF -59

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -71,   331,   -71,    34,   171,   269,   -65,   269,   184,   184,
     269,    -9,   931,    15,   184,    11,   184,   184,   269,    31,
      39,    48,    53,   -71,   -71,   -71,    -7,     6,    19,    21,
      27,    35,    36,    37,    38,    41,    43,    63,   958,    64,
     -71,   -71,   269,   269,   269,   269,     1,   205,   -71,   269,
     235,  1180,    24,   -71,   269,   269,   269,   269,     7,  1180,
     -71,  1072,   931,   370,     7,     7,  1180,   269,   269,   -71,
     478,   931,     7,    -4,    -5,    33,   106,     7,     7,  1180,
     -71,   -71,    69,    65,   -71,   -71,   -71,   -71,   -71,   -71,
     -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,    73,   -71,
    1180,  1180,  1180,  1180,   -29,    -8,  1180,  1180,   -70,    16,
    1022,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   148,  1180,
    1180,  1047,   248,   931,   517,   434,  1180,  1180,   269,   -71,
     556,   269,   269,   269,   269,   140,   -71,   -71,   -71,   -71,
     -71,    77,   -71,    78,   -71,    79,    29,   -30,   -30,    94,
      94,    94,    94,    94,    94,    94,    94,   -51,   -51,   -51,
       5,     5,   -71,   -71,   -71,   -71,  1180,   -71,   -71,  1180,
     595,   269,   -71,   931,  1180,   -71,   949,   987,  1004,  1180,
      82,    87,    88,    95,    98,   -71,  1180,   634,   269,   269,
     269,   269,   269,   931,   269,   -71,   -71,   -71,   -71,   -71,
    1090,  1108,  1126,  1144,  1162,   677,  1180,   931,   931,   931,
     931,   931,   147,   720,   763,   806,   849,   892,   -71,   101,
     102,   103,   105,   167,   -71,   -71,   -71,   -71,   -71
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     1,    53,    52,     0,     0,     0,    77,    79,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    23,    19,     2,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      84,    85,     0,     0,     0,     0,    67,    62,    82,     0,
       0,     0,    81,    38,     0,     0,     0,     0,    42,    37,
      81,     0,     0,     0,    78,    80,    72,     0,     0,    20,
       0,     0,    76,     0,     0,     0,     0,    74,    75,    73,
      24,    25,    43,    47,    22,    14,    15,    17,    18,     9,
      10,    11,    12,    13,    16,     7,     8,     5,     0,     4,
      90,    87,    89,    88,     0,     0,    86,    54,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    49,
      48,     0,     0,     0,     0,     0,    51,    50,     0,    21,
       0,     0,     0,     0,     0,     0,     6,    68,    69,    63,
      64,     0,    70,     0,    65,     0,    83,    93,    94,    91,
      92,    97,    98,   100,    99,    96,    95,   102,   101,   103,
     104,   105,   106,   107,    56,    57,    61,    83,    40,    39,
       0,     0,    27,     0,    29,    41,     0,     0,     0,    45,
      44,     0,     0,     0,     0,    30,    28,     0,     0,     0,
       0,     0,     0,     0,     0,    71,    66,    59,    60,    26,
       0,     0,     0,     0,     0,     0,    46,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    31,     0,
       0,     0,     0,     0,    33,    34,    35,    36,    32
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -71,   -71,    -1,   -54,   -71,   -71,   -71,   -71,   -71,   -71,
     -71,    68,   -71,   -71,   -71,   -71,   162,   -71,   -71,   144,
       0,   180
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,    69,    70,    26,    27,    28,    29,    30,    31,
      32,    58,    33,    34,    83,    35,    36,    37,    38,    39,
      59,    60
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      25,   151,    62,    51,   152,    61,    67,    63,   134,   135,
      66,    54,   124,   125,   126,   127,    73,   140,    79,    40,
      71,    41,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,    40,    80,    41,
     147,   148,   100,   101,   102,   103,    81,   106,    42,   107,
     110,    74,    75,    82,   129,   106,   130,   131,    84,    68,
      85,   149,   150,   141,    56,    43,    42,   136,   137,   139,
     126,   127,   104,    86,    44,    45,    64,    65,   132,   180,
      55,    48,    72,    43,    77,    78,    87,   153,    88,    57,
     154,   -55,    44,    45,    89,   128,   -58,    46,    47,    48,
     194,   142,    90,    91,    92,    93,    49,    50,    94,   106,
      95,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   176,   197,
      96,    99,   179,   139,   139,   143,   145,   144,   184,   139,
     146,   186,   187,   188,   189,   190,   191,   192,   193,   215,
     204,    40,   228,    41,   121,   122,   123,   124,   125,   126,
     127,   205,   206,   223,   224,   225,   226,   227,   208,   207,
     234,   235,   238,   236,    40,   237,    41,    76,    53,   139,
      42,   196,    98,    52,     0,     0,    54,    40,     0,    41,
       0,    53,     0,     0,     0,     0,   139,    43,   210,   211,
     212,   213,   214,    42,   216,     0,    44,    45,    40,     0,
      41,     0,    55,    48,   139,     0,    42,   174,   175,     0,
      43,    57,   139,   139,   139,   139,   139,     0,     0,    44,
      45,     0,     0,    43,     0,    55,    48,    42,    40,    56,
      41,     0,    44,    45,    57,     0,     0,     0,    55,    48,
       0,    40,     0,    41,    43,   178,     0,    57,     0,     0,
       0,     0,     0,    44,    45,     0,     0,    42,     0,    55,
      48,     0,    40,     0,    41,     0,   105,     0,    57,     0,
      42,     0,     0,     0,    43,     0,     0,     0,     0,     0,
       0,     0,     0,    44,    45,     0,     0,    43,   108,   109,
      48,    42,     0,     0,     0,     0,    44,    45,    57,     0,
       0,     0,    55,    48,     0,     0,     0,     0,    43,     0,
       0,    57,     0,     0,     0,     0,     0,    44,    45,     0,
       0,     2,     0,    55,    48,     3,     4,     0,     0,     5,
       0,     6,    57,     7,     8,     9,     0,    10,    11,     0,
      12,    13,     0,     0,     0,     0,     0,    14,    15,     0,
       0,     0,     0,     0,    16,    17,     0,     0,    18,    19,
      20,     0,     0,    21,     3,     4,    22,    23,     5,     0,
       6,     0,     7,     8,     9,     0,    10,    11,     0,    12,
      13,     0,     0,     0,     0,     0,    14,    15,    24,     0,
       0,     0,     0,    16,    17,     0,     0,    18,    19,    20,
       0,     0,    21,     0,     0,    22,    23,     0,     0,     0,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,    24,     3,     4,
       0,     0,     5,     0,     6,     0,     7,     8,     9,     0,
      10,    11,     0,    12,    13,     0,   182,     0,     0,     0,
      14,    15,     0,     0,     0,     0,     0,    16,    17,     0,
       0,    18,    19,    20,     0,     0,    21,     0,     0,    22,
      23,   183,     3,     4,     0,     0,     5,   138,     6,     0,
       7,     8,     9,     0,    10,    11,     0,    12,    13,     0,
       0,    24,     0,     0,    14,    15,     0,     0,     0,     0,
       0,    16,    17,     0,     0,    18,    19,    20,     0,     0,
      21,     3,     4,    22,    23,     5,     0,     6,   181,     7,
       8,     9,     0,    10,    11,     0,    12,    13,     0,     0,
       0,     0,     0,    14,    15,    24,     0,     0,     0,     0,
      16,    17,     0,     0,    18,    19,    20,     0,     0,    21,
       3,     4,    22,    23,     5,     0,     6,     0,     7,     8,
       9,     0,    10,    11,     0,    12,    13,   185,     0,     0,
       0,     0,    14,    15,    24,     0,     0,     0,     0,    16,
      17,     0,     0,    18,    19,    20,     0,     0,    21,     3,
       4,    22,    23,     5,     0,     6,     0,     7,     8,     9,
       0,    10,    11,     0,    12,    13,     0,     0,   195,     0,
       0,    14,    15,    24,     0,     0,     0,     0,    16,    17,
       0,     0,    18,    19,    20,     0,     0,    21,     3,     4,
      22,    23,     5,     0,     6,     0,     7,     8,     9,     0,
      10,    11,     0,    12,    13,     0,   209,     0,     0,     0,
      14,    15,    24,     0,     0,     0,     0,    16,    17,     0,
       0,    18,    19,    20,     0,     0,    21,     0,     0,    22,
      23,     3,     4,     0,     0,     5,     0,     6,     0,     7,
       8,     9,     0,    10,    11,     0,    12,    13,     0,     0,
       0,    24,     0,    14,    15,   222,     0,     0,     0,     0,
      16,    17,     0,     0,    18,    19,    20,     0,     0,    21,
       0,     0,    22,    23,     3,     4,     0,     0,     5,     0,
       6,     0,     7,     8,     9,     0,    10,    11,     0,    12,
      13,     0,     0,     0,    24,     0,    14,    15,   229,     0,
       0,     0,     0,    16,    17,     0,     0,    18,    19,    20,
       0,     0,    21,     0,     0,    22,    23,     3,     4,     0,
       0,     5,     0,     6,     0,     7,     8,     9,     0,    10,
      11,     0,    12,    13,     0,     0,     0,    24,     0,    14,
      15,   230,     0,     0,     0,     0,    16,    17,     0,     0,
      18,    19,    20,     0,     0,    21,     0,     0,    22,    23,
       3,     4,     0,     0,     5,     0,     6,     0,     7,     8,
       9,     0,    10,    11,     0,    12,    13,     0,     0,     0,
      24,     0,    14,    15,   231,     0,     0,     0,     0,    16,
      17,     0,     0,    18,    19,    20,     0,     0,    21,     0,
       0,    22,    23,     3,     4,     0,     0,     5,     0,     6,
       0,     7,     8,     9,     0,    10,    11,     0,    12,    13,
       0,     0,     0,    24,     0,    14,    15,   232,     0,     0,
       0,     0,    16,    17,     0,     0,    18,    19,    20,     0,
       0,    21,     0,     0,    22,    23,     3,     4,     0,     0,
       5,     0,     6,     0,     7,     8,     9,     0,    10,    11,
       0,    12,    13,     0,     0,     0,    24,     0,    14,    15,
     233,     0,     0,     0,     0,    16,    17,     0,     0,    18,
      19,    20,     0,     0,    21,     3,     4,    22,    23,     5,
       0,     6,     0,     7,     8,     9,     0,    10,    11,     0,
      12,    13,     0,     0,     0,     0,     0,    14,    15,    24,
       0,     0,     3,     0,    16,    17,     0,     0,    18,    19,
      20,     8,     9,    21,    10,     0,    22,    23,   198,   199,
       0,     0,     0,     0,    14,     0,     0,     0,     0,     0,
       0,    16,    17,     0,     0,    18,     0,     0,    24,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   200,   201,     0,     0,
       0,     0,     0,     0,     0,    97,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   202,     0,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   203,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,     0,
       0,     0,     0,   155,     0,     0,   156,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,     0,     0,     0,     0,     0,     0,
       0,   177,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   133,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   217,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   218,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   219,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   220,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   221,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127
};

static const yytype_int16 yycheck[] =
{
       1,    71,    67,     3,    74,     5,    15,     7,    62,    63,
      10,    15,    63,    64,    65,    66,     5,    71,    18,     3,
       5,     5,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,     3,     7,     5,
      69,    70,    42,    43,    44,    45,     7,    47,    32,    49,
      50,    40,    41,     5,    54,    55,    56,    57,     5,    68,
      67,    69,    70,    68,    68,    49,    32,    67,    68,    70,
      65,    66,    71,    67,    58,    59,     8,     9,    71,   133,
      64,    65,    14,    49,    16,    17,    67,    71,    67,    73,
      74,    67,    58,    59,    67,    71,    67,    63,    64,    65,
      71,    68,    67,    67,    67,    67,    72,    73,    67,   109,
      67,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   183,
      67,    67,   132,   134,   135,    29,    71,    68,   138,   140,
      67,   141,   142,   143,   144,     5,    69,    69,    69,   203,
      68,     3,     5,     5,    60,    61,    62,    63,    64,    65,
      66,    74,    74,   217,   218,   219,   220,   221,    70,    74,
      69,    69,     5,    70,     3,    70,     5,    15,     7,   180,
      32,   181,    38,     3,    -1,    -1,    15,     3,    -1,     5,
      -1,     7,    -1,    -1,    -1,    -1,   197,    49,   198,   199,
     200,   201,   202,    32,   204,    -1,    58,    59,     3,    -1,
       5,    -1,    64,    65,   215,    -1,    32,    69,    70,    -1,
      49,    73,   223,   224,   225,   226,   227,    -1,    -1,    58,
      59,    -1,    -1,    49,    -1,    64,    65,    32,     3,    68,
       5,    -1,    58,    59,    73,    -1,    -1,    -1,    64,    65,
      -1,     3,    -1,     5,    49,     7,    -1,    73,    -1,    -1,
      -1,    -1,    -1,    58,    59,    -1,    -1,    32,    -1,    64,
      65,    -1,     3,    -1,     5,    -1,    71,    -1,    73,    -1,
      32,    -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    58,    59,    -1,    -1,    49,    63,    64,
      65,    32,    -1,    -1,    -1,    -1,    58,    59,    73,    -1,
      -1,    -1,    64,    65,    -1,    -1,    -1,    -1,    49,    -1,
      -1,    73,    -1,    -1,    -1,    -1,    -1,    58,    59,    -1,
      -1,     0,    -1,    64,    65,     4,     5,    -1,    -1,     8,
      -1,    10,    73,    12,    13,    14,    -1,    16,    17,    -1,
      19,    20,    -1,    -1,    -1,    -1,    -1,    26,    27,    -1,
      -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    37,    38,
      39,    -1,    -1,    42,     4,     5,    45,    46,     8,    -1,
      10,    -1,    12,    13,    14,    -1,    16,    17,    -1,    19,
      20,    -1,    -1,    -1,    -1,    -1,    26,    27,    67,    -1,
      -1,    -1,    -1,    33,    34,    -1,    -1,    37,    38,    39,
      -1,    -1,    42,    -1,    -1,    45,    46,    -1,    -1,    -1,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,     4,     5,
      -1,    -1,     8,    -1,    10,    -1,    12,    13,    14,    -1,
      16,    17,    -1,    19,    20,    -1,    22,    -1,    -1,    -1,
      26,    27,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,
      -1,    37,    38,    39,    -1,    -1,    42,    -1,    -1,    45,
      46,    47,     4,     5,    -1,    -1,     8,     9,    10,    -1,
      12,    13,    14,    -1,    16,    17,    -1,    19,    20,    -1,
      -1,    67,    -1,    -1,    26,    27,    -1,    -1,    -1,    -1,
      -1,    33,    34,    -1,    -1,    37,    38,    39,    -1,    -1,
      42,     4,     5,    45,    46,     8,    -1,    10,    11,    12,
      13,    14,    -1,    16,    17,    -1,    19,    20,    -1,    -1,
      -1,    -1,    -1,    26,    27,    67,    -1,    -1,    -1,    -1,
      33,    34,    -1,    -1,    37,    38,    39,    -1,    -1,    42,
       4,     5,    45,    46,     8,    -1,    10,    -1,    12,    13,
      14,    -1,    16,    17,    -1,    19,    20,    21,    -1,    -1,
      -1,    -1,    26,    27,    67,    -1,    -1,    -1,    -1,    33,
      34,    -1,    -1,    37,    38,    39,    -1,    -1,    42,     4,
       5,    45,    46,     8,    -1,    10,    -1,    12,    13,    14,
      -1,    16,    17,    -1,    19,    20,    -1,    -1,    23,    -1,
      -1,    26,    27,    67,    -1,    -1,    -1,    -1,    33,    34,
      -1,    -1,    37,    38,    39,    -1,    -1,    42,     4,     5,
      45,    46,     8,    -1,    10,    -1,    12,    13,    14,    -1,
      16,    17,    -1,    19,    20,    -1,    22,    -1,    -1,    -1,
      26,    27,    67,    -1,    -1,    -1,    -1,    33,    34,    -1,
      -1,    37,    38,    39,    -1,    -1,    42,    -1,    -1,    45,
      46,     4,     5,    -1,    -1,     8,    -1,    10,    -1,    12,
      13,    14,    -1,    16,    17,    -1,    19,    20,    -1,    -1,
      -1,    67,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,
      33,    34,    -1,    -1,    37,    38,    39,    -1,    -1,    42,
      -1,    -1,    45,    46,     4,     5,    -1,    -1,     8,    -1,
      10,    -1,    12,    13,    14,    -1,    16,    17,    -1,    19,
      20,    -1,    -1,    -1,    67,    -1,    26,    27,    28,    -1,
      -1,    -1,    -1,    33,    34,    -1,    -1,    37,    38,    39,
      -1,    -1,    42,    -1,    -1,    45,    46,     4,     5,    -1,
      -1,     8,    -1,    10,    -1,    12,    13,    14,    -1,    16,
      17,    -1,    19,    20,    -1,    -1,    -1,    67,    -1,    26,
      27,    28,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,
      37,    38,    39,    -1,    -1,    42,    -1,    -1,    45,    46,
       4,     5,    -1,    -1,     8,    -1,    10,    -1,    12,    13,
      14,    -1,    16,    17,    -1,    19,    20,    -1,    -1,    -1,
      67,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,    33,
      34,    -1,    -1,    37,    38,    39,    -1,    -1,    42,    -1,
      -1,    45,    46,     4,     5,    -1,    -1,     8,    -1,    10,
      -1,    12,    13,    14,    -1,    16,    17,    -1,    19,    20,
      -1,    -1,    -1,    67,    -1,    26,    27,    28,    -1,    -1,
      -1,    -1,    33,    34,    -1,    -1,    37,    38,    39,    -1,
      -1,    42,    -1,    -1,    45,    46,     4,     5,    -1,    -1,
       8,    -1,    10,    -1,    12,    13,    14,    -1,    16,    17,
      -1,    19,    20,    -1,    -1,    -1,    67,    -1,    26,    27,
      28,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    37,
      38,    39,    -1,    -1,    42,     4,     5,    45,    46,     8,
      -1,    10,    -1,    12,    13,    14,    -1,    16,    17,    -1,
      19,    20,    -1,    -1,    -1,    -1,    -1,    26,    27,    67,
      -1,    -1,     4,    -1,    33,    34,    -1,    -1,    37,    38,
      39,    13,    14,    42,    16,    -1,    45,    46,    29,    30,
      -1,    -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    34,    -1,    -1,    37,    -1,    -1,    67,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    29,    30,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    -1,
      -1,    -1,    -1,    71,    -1,    -1,    74,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    74,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    76,     0,     4,     5,     8,    10,    12,    13,    14,
      16,    17,    19,    20,    26,    27,    33,    34,    37,    38,
      39,    42,    45,    46,    67,    77,    79,    80,    81,    82,
      83,    84,    85,    87,    88,    90,    91,    92,    93,    94,
       3,     5,    32,    49,    58,    59,    63,    64,    65,    72,
      73,    95,    96,     7,    15,    64,    68,    73,    86,    95,
      96,    95,    67,    95,    86,    86,    95,    15,    68,    77,
      78,     5,    86,     5,    40,    41,    91,    86,    86,    95,
       7,     7,     5,    89,     5,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    94,    67,
      95,    95,    95,    95,    71,    71,    95,    95,    63,    64,
      95,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    71,    95,
      95,    95,    71,    67,    78,    78,    95,    95,     9,    77,
      78,    68,    68,    29,    68,    71,    67,    69,    70,    69,
      70,    71,    74,    71,    74,    71,    74,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    69,    70,    95,    74,     7,    95,
      78,    11,    22,    47,    95,    21,    95,    95,    95,    95,
       5,    69,    69,    69,    71,    23,    95,    78,    29,    30,
      29,    30,    31,    67,    68,    74,    74,    74,    70,    22,
      95,    95,    95,    95,    95,    78,    95,    67,    67,    67,
      67,    67,    28,    78,    78,    78,    78,    78,     5,    28,
      28,    28,    28,    28,    69,    69,    70,    70,     5
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    75,    76,    76,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      78,    78,    79,    80,    81,    82,    83,    83,    84,    84,
      84,    84,    84,    85,    85,    85,    85,    86,    86,    86,
      86,    87,    88,    89,    89,    89,    89,    90,    91,    91,
      92,    92,    93,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    95,    95,    95,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96
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
       6,     4,     2,     4,     4,     4,     6,     2,     4,     4,
       4,     6,     2,     2,     2,     2,     2,     1,     2,     1,
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

    { (yyval.nPtr) = Opcode((yyvsp[-1].iValue), a, 1, Id("-"));               }

    break;

  case 63:

    { (yyval.nPtr) = Opcode((yyvsp[-3].iValue), ax, 1, Id("-"));              }

    break;

  case 64:

    { (yyval.nPtr) = Opcode((yyvsp[-3].iValue), ay, 1, Id("-"));              }

    break;

  case 65:

    { (yyval.nPtr) = Opcode((yyvsp[-3].iValue), ind, 1, Id("-"));             }

    break;

  case 66:

    { (yyval.nPtr) = Opcode((yyvsp[-5].iValue), aix, 1, Id("-"));             }

    break;

  case 67:

    { (yyval.nPtr) = Opcode((yyvsp[-1].iValue), a, 1, Id("+"));               }

    break;

  case 68:

    { (yyval.nPtr) = Opcode((yyvsp[-3].iValue), ax, 1, Id("+"));              }

    break;

  case 69:

    { (yyval.nPtr) = Opcode((yyvsp[-3].iValue), ay, 1, Id("+"));              }

    break;

  case 70:

    { (yyval.nPtr) = Opcode((yyvsp[-3].iValue), ind, 1, Id("+"));             }

    break;

  case 71:

    { (yyval.nPtr) = Opcode((yyvsp[-5].iValue), aix, 1, Id("+"));             }

    break;

  case 72:

    { (yyval.nPtr) = Opr(ORG, 1, (yyvsp[0].nPtr));                         }

    break;

  case 73:

    { (yyval.nPtr) = Opr(DS, 1, (yyvsp[0].nPtr));                          }

    break;

  case 74:

    { (yyval.nPtr) = Data(1, (yyvsp[0].nPtr));                             }

    break;

  case 75:

    { (yyval.nPtr) = Data(2, (yyvsp[0].nPtr));                             }

    break;

  case 76:

    { (yyval.nPtr) = Data(0, (yyvsp[0].nPtr));	 							}

    break;

  case 77:

    { (yyval.nPtr) = Opr(PRINT, 0);                           }

    break;

  case 78:

    { (yyval.nPtr) = Opr(PRINT, 1, (yyvsp[0].nPtr));                       }

    break;

  case 79:

    { (yyval.nPtr) = Opr(PRINTALL, 0);                        }

    break;

  case 80:

    { (yyval.nPtr) = Opr(PRINTALL, 1, (yyvsp[0].nPtr));                    }

    break;

  case 81:

    { (yyval.nPtr) = (yyvsp[0].nPtr);                                      }

    break;

  case 82:

    { (yyval.nPtr) = Con(PC, TRUE);                           }

    break;

  case 83:

    { (yyval.nPtr) = (yyvsp[-1].nPtr);                                      }

    break;

  case 84:

    { (yyval.nPtr) = Con((yyvsp[0].iValue), FALSE);                          }

    break;

  case 85:

    { (yyval.nPtr) = Id((yyvsp[0].sIndex));                                  }

    break;

  case 86:

    { (yyval.nPtr) = Opr(UMINUS, 1, (yyvsp[0].nPtr));                      }

    break;

  case 87:

    { (yyval.nPtr) = Opr('~', 1, (yyvsp[0].nPtr));                         }

    break;

  case 88:

    { (yyval.nPtr) = Opr(LOBYTE, 1, (yyvsp[0].nPtr));                      }

    break;

  case 89:

    { (yyval.nPtr) = Opr(HIBYTE, 1, (yyvsp[0].nPtr));                      }

    break;

  case 90:

    { (yyval.nPtr) = Opr(NOT, 1, (yyvsp[0].nPtr));                         }

    break;

  case 91:

    { (yyval.nPtr) = Opr(OR, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                      }

    break;

  case 92:

    { (yyval.nPtr) = Opr(AND, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                     }

    break;

  case 93:

    { (yyval.nPtr) = Opr(SHIFT_LEFT, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));              }

    break;

  case 94:

    { (yyval.nPtr) = Opr(SHIFT_RIGHT, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));             }

    break;

  case 95:

    { (yyval.nPtr) = Opr('<', 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                     }

    break;

  case 96:

    { (yyval.nPtr) = Opr('>', 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                     }

    break;

  case 97:

    { (yyval.nPtr) = Opr(GE, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                      }

    break;

  case 98:

    { (yyval.nPtr) = Opr(LE, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                      }

    break;

  case 99:

    { (yyval.nPtr) = Opr(NE, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                      }

    break;

  case 100:

    { (yyval.nPtr) = Opr(EQ, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                      }

    break;

  case 101:

    { (yyval.nPtr) = Opr(BIT_AND, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                 }

    break;

  case 102:

    { (yyval.nPtr) = Opr(BIT_OR, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                  }

    break;

  case 103:

    { (yyval.nPtr) = Opr('^', 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                     }

    break;

  case 104:

    { (yyval.nPtr) = Opr('+', 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                     }

    break;

  case 105:

    { (yyval.nPtr) = Opr('-', 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                     }

    break;

  case 106:

    { (yyval.nPtr) = Opr('*', 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr));                     }

    break;

  case 107:

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


