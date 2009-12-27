
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "gram.y"

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    #include "postgres.h"
    #include "parsing.h"

    #define YYDEBUG 1
    #define QUERY_LENGTH 5
    #define YYPARSE_PARAM result  /* need this to pass a pointer (void *) to yyparse */

    int real_length=0;
    char *field;
    char *fuzzy_query[QUERY_LENGTH];
	#define DDL_FP_CLAUSE 0
		
	//To know if it is an AND or an OR in the query
	#define LEAST 1
	#define GREATEST 2
	int fop;

	enum sql_type {SELECT_CLAUSE,FROM_CLAUSE,WHERE_CLAUSE,ORDER_BY_CLAUSE,CALIBRATION_CLAUSE};

	char *sub_sqlf_filters[1024];
	char *args_membdg[1024];
	
	int count_membdg=0;
	int filter_times=0;
	char *select_items;

    typedef struct Membdg_values {
        char *min;
        char *first_core;
        char *second_core;
        char *max;
    } Membdg_values;

    Membdg_values membdg_values;

	int *is_fuzzy;

	int ScanKeyword(const char *keyword);



/* Line 189 of yacc.c  */
#line 120 "gram.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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
     INNER = 268,
     JOIN = 269,
     LEFT = 270,
     RIGHT = 271,
     DROP = 272,
     EQUAL = 273,
     SELECT = 274,
     WHERE = 275,
     FROM = 276,
     AND = 277,
     OR = 278,
     ORDER = 279,
     BY = 280,
     ASC = 281,
     DESC = 282,
     WITH = 283,
     CALIBRATION = 284,
     PARAMETER = 285
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 47 "gram.y"

    int	integer;
    char *text;



/* Line 214 of yacc.c  */
#line 193 "gram.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 205 "gram.c"

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
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
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

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

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

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   98

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  11
/* YYNRULES -- Number of rules.  */
#define YYNRULES  41
/* YYNRULES -- Number of states.  */
#define YYNSTATES  101

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      31,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     7,     9,    11,    13,    15,    18,
      37,    56,    75,    80,    85,    89,    94,    99,   101,   103,
     107,   111,   114,   116,   120,   124,   127,   132,   137,   142,
     148,   150,   153,   157,   161,   166,   170,   175,   178,   180,
     184,   187
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      33,     0,    -1,    -1,    33,    34,    -1,    31,    -1,    35,
      -1,    36,    -1,    37,    -1,     1,    31,    -1,     3,     4,
       5,    38,     6,    38,     9,    38,     7,    10,    38,     8,
      38,     8,    38,     8,    38,    11,    -1,     3,     4,     5,
      38,     6,    38,     9,    38,     7,    10,    12,     8,    12,
       8,    38,     8,    38,    11,    -1,     3,     4,     5,    38,
       6,    38,     9,    38,     7,    10,    38,     8,    38,     8,
      12,     8,    12,    11,    -1,    17,     4,     5,    38,    -1,
      19,    39,    21,    40,    -1,    37,    20,    41,    -1,    37,
      24,    25,    42,    -1,    37,    28,    29,    38,    -1,    30,
      -1,    38,    -1,    39,     8,    38,    -1,    39,     7,    38,
      -1,    39,    38,    -1,    38,    -1,    40,     8,    38,    -1,
      40,     7,    38,    -1,    40,    38,    -1,    40,    13,    14,
      38,    -1,    40,    15,    14,    38,    -1,    40,    16,    14,
      38,    -1,    40,     6,    38,    18,    38,    -1,    38,    -1,
      10,    38,    -1,    41,    18,    38,    -1,    41,    22,    38,
      -1,    41,    11,    22,    38,    -1,    41,    23,    38,    -1,
      41,    11,    23,    38,    -1,    41,    11,    -1,    38,    -1,
      42,     8,    38,    -1,    42,    26,    -1,    42,    27,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    59,    59,    60,   174,   175,   176,   177,   178,   182,
     187,   192,   199,   242,   259,   276,   285,   295,   298,   299,
     303,   307,   314,   315,   319,   323,   327,   331,   335,   339,
     349,   354,   362,   403,   417,   425,   439,   447,   456,   457,
     461,   465
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CREATE", "FUZZY", "PREDICATE", "ON",
  "AS", "COMMA", "DOTDOT", "LEFTP", "RIGHTP", "INFINIT", "INNER", "JOIN",
  "LEFT", "RIGHT", "DROP", "EQUAL", "SELECT", "WHERE", "FROM", "AND", "OR",
  "ORDER", "BY", "ASC", "DESC", "WITH", "CALIBRATION", "PARAMETER",
  "'\\n'", "$accept", "query", "command", "CreateFuzzyPredStmt",
  "DropFuzzyPredStmt", "SelectStmt", "Param", "Param_select", "Param_from",
  "List_where", "List_order", 0
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
     285,    10
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    32,    33,    33,    34,    34,    34,    34,    34,    35,
      35,    35,    36,    37,    37,    37,    37,    38,    39,    39,
      39,    39,    40,    40,    40,    40,    40,    40,    40,    40,
      41,    41,    41,    41,    41,    41,    41,    41,    42,    42,
      42,    42
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     2,    18,
      18,    18,     4,     4,     3,     4,     4,     1,     1,     3,
       3,     2,     1,     3,     3,     2,     4,     4,     4,     5,
       1,     2,     3,     3,     4,     3,     4,     2,     1,     3,
       2,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     4,     3,     5,
       6,     7,     8,     0,     0,    17,    18,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    21,     0,    30,    14,
       0,     0,     0,    12,    20,    19,    22,    13,    31,    37,
       0,     0,     0,    38,    15,    16,     0,     0,     0,     0,
       0,     0,     0,    25,     0,     0,    32,    33,    35,     0,
      40,    41,     0,     0,    24,    23,     0,     0,     0,    34,
      36,    39,     0,     0,    26,    27,    28,     0,    29,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    10,    11,
       9
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     8,     9,    10,    11,    16,    17,    37,    29,
      44
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -18
static const yytype_int8 yypact[] =
{
     -18,    16,   -18,   -16,    22,    35,    10,   -18,   -18,   -18,
     -18,    40,   -18,    43,    53,   -18,   -18,    36,    -8,    44,
      45,    10,    10,    10,    10,    10,   -18,    10,   -18,    23,
      10,    10,    59,   -18,   -18,   -18,   -18,    46,   -18,   -11,
      10,    10,    10,   -18,     1,   -18,    10,    10,    10,    10,
      58,    64,    65,   -18,    10,    10,   -18,   -18,   -18,    10,
     -18,   -18,    71,    55,   -18,   -18,    10,    10,    10,   -18,
     -18,   -18,    10,    10,   -18,   -18,   -18,    74,   -18,    72,
      -9,    75,    76,    73,    10,    78,    79,    10,     6,    80,
      81,    82,    10,    83,    10,    85,    86,    87,   -18,   -18,
     -18
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -18,   -18,   -18,   -18,   -18,   -18,   -17,   -18,   -18,   -18,
     -18
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      26,    28,    27,    81,    32,    33,    34,    35,    36,    59,
      38,    54,    55,    43,    45,    12,     2,     3,    90,     4,
      53,    15,    15,    56,    57,    58,    13,    60,    61,    62,
      63,    64,    65,     5,    39,     6,    15,    69,    70,    14,
      15,    40,    71,    23,    24,    41,    42,     7,    21,    74,
      75,    76,    47,    48,    49,    77,    78,    25,    22,    50,
      18,    51,    52,    82,    19,    46,    15,    86,    20,    30,
      89,    91,    66,    73,    31,    95,    15,    97,    67,    68,
      72,    79,    80,    83,    84,    85,    87,    88,    92,    93,
      94,     0,     0,     0,     0,    96,    98,    99,   100
};

static const yytype_int8 yycheck[] =
{
      17,    18,    10,    12,    21,    22,    23,    24,    25,     8,
      27,    22,    23,    30,    31,    31,     0,     1,    12,     3,
      37,    30,    30,    40,    41,    42,     4,    26,    27,    46,
      47,    48,    49,    17,    11,    19,    30,    54,    55,     4,
      30,    18,    59,     7,     8,    22,    23,    31,     5,    66,
      67,    68,     6,     7,     8,    72,    73,    21,     5,    13,
      20,    15,    16,    80,    24,     6,    30,    84,    28,    25,
      87,    88,    14,    18,    29,    92,    30,    94,    14,    14,
       9,     7,    10,     8,     8,    12,     8,     8,     8,     8,
       8,    -1,    -1,    -1,    -1,    12,    11,    11,    11
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    33,     0,     1,     3,    17,    19,    31,    34,    35,
      36,    37,    31,     4,     4,    30,    38,    39,    20,    24,
      28,     5,     5,     7,     8,    21,    38,    10,    38,    41,
      25,    29,    38,    38,    38,    38,    38,    40,    38,    11,
      18,    22,    23,    38,    42,    38,     6,     6,     7,     8,
      13,    15,    16,    38,    22,    23,    38,    38,    38,     8,
      26,    27,    38,    38,    38,    38,    14,    14,    14,    38,
      38,    38,     9,    18,    38,    38,    38,    38,    38,     7,
      10,    12,    38,     8,     8,    12,    38,     8,     8,    38,
      12,    38,     8,     8,     8,    38,    12,    38,    11,    11,
      11
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
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

/* Prevent warnings from -Wmissing-prototypes.  */
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
  if (yyn == YYPACT_NINF)
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;

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
        case 3:

/* Line 1455 of yacc.c  */
#line 61 "gram.y"
    {
			int   i=0;
			int   j=0;
			char  *sql;
			int   len;
 			//This variable is used to add the membership degree function
			//in the where clause 
			char	*calib_where;

			len=0;
			for (i=0;i<real_length;i++)
				len+=strlen(fuzzy_query[i]);
			len+=20;
			if(filter_times==1 || real_length==1){
			
		        sql=(char *)palloc(sizeof(char *)*len);
		        strcpy(sql,"");

				for (i=0;i<real_length;i++){
					if (i==FROM_CLAUSE){
						strcat(sql,args_membdg[0]);
						strcat(sql," as membdg");
					}

					strcat(sql,fuzzy_query[i]);

					if (i==WHERE_CLAUSE)
						strcat(sql," ORDER BY membdg");
				}
			}else{

				for(i=0;i<filter_times;i++){
					len+=strlen(sub_sqlf_filters[i]);
					len+=150;
				}

				for(i=0;i<count_membdg;i++)
					len+=strlen(args_membdg[i]);
				
				len+=strlen(fuzzy_query[SELECT_CLAUSE])+strlen(select_items);

		        sql=(char *)palloc(sizeof(char *)*len);
		        strcpy(sql,"");

				len=0;
				for (i=0;i<real_length;i++){
					if (i==FROM_CLAUSE){

						for (j=0;j<count_membdg;j++)
							len+=strlen(args_membdg[j]);

						calib_where=(char *)palloc(sizeof(char *)*len);
						strcpy(calib_where,"");
						
						if (fop==LEAST)
							strcpy(calib_where,"LEAST(");
						else if (fop==GREATEST)
							strcpy(calib_where,"GREATEST(");

						for (j=0;j<count_membdg;j++)
							strcat(calib_where,args_membdg[j]);

						if (calib_where[strlen(calib_where)-1]!=')')
							strcat(calib_where,") ");
						
						strcat(sql,calib_where);
						strcat(sql," as membdg ");

					}

					//This is to prevent adding the WITH CALIBRATION at the end of the query
					if (i!=CALIBRATION_CLAUSE)
	            	strcat(sql,fuzzy_query[i]);

					if (i==WHERE_CLAUSE){
						if (real_length==5){
							strcat(sql," AND ");
							strcat(sql,calib_where);
							strcat(sql,"=");
							strcat(sql,fuzzy_query[CALIBRATION_CLAUSE]);
						}
						strcat(sql," ORDER BY membdg");
					}

				}
				pfree(calib_where);

			}

			*((void **)result) = sql;

			//Cleaning
			pfree(sql);
			if (real_length>1)
				pfree(select_items);
			for (i=0;i<real_length;i++){
				strcpy(fuzzy_query[i],"");            
				pfree(fuzzy_query[i]);
			}
			for (i=0;i<count_membdg;i++){
				strcpy(args_membdg[i],"");
				pfree(args_membdg[i]);
			}
			for (i=0;i<filter_times;i++){
				strcpy(sub_sqlf_filters[i],"");						
				pfree(sub_sqlf_filters[i]);
			}
			count_membdg=0;
			filter_times=0;
			real_length=0;
        ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 175 "gram.y"
    { real_length=1; ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 176 "gram.y"
    { real_length=1; ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 178 "gram.y"
    { yyerrok;;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 183 "gram.y"
    {
            fuzzy_query[DDL_FP_CLAUSE]=create_fuzzy_pred((yyvsp[(4) - (18)].text),(yyvsp[(6) - (18)].text),(yyvsp[(8) - (18)].text),(yyvsp[(11) - (18)].text),(yyvsp[(13) - (18)].text),(yyvsp[(15) - (18)].text),(yyvsp[(17) - (18)].text));
        ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 188 "gram.y"
    {
			fuzzy_query[DDL_FP_CLAUSE]=create_fuzzy_pred((yyvsp[(4) - (18)].text),(yyvsp[(6) - (18)].text),(yyvsp[(8) - (18)].text),"INFINIT","INFINIT",(yyvsp[(15) - (18)].text),(yyvsp[(17) - (18)].text));
		;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 193 "gram.y"
    {
			fuzzy_query[DDL_FP_CLAUSE]=create_fuzzy_pred((yyvsp[(4) - (18)].text),(yyvsp[(6) - (18)].text),(yyvsp[(8) - (18)].text),(yyvsp[(11) - (18)].text),(yyvsp[(13) - (18)].text),"INFINIT","INFINIT");
		;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 200 "gram.y"
    {
			fuzzy_query[DDL_FP_CLAUSE]=drop_fuzzy_pred((yyvsp[(4) - (4)].text));
		;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 243 "gram.y"
    {
                int len;
                len=strlen((yyvsp[(2) - (4)].text))+10;
                fuzzy_query[SELECT_CLAUSE]=(char *)palloc(sizeof(char *)*len);
				select_items=(char *)palloc(sizeof(char *)*len);
				snprintf(select_items,len,"%s",(yyvsp[(2) - (4)].text));

                len=strlen((yyvsp[(4) - (4)].text))+10;
                fuzzy_query[FROM_CLAUSE]=(char *)palloc(sizeof(char *)*len);
							
                snprintf(fuzzy_query[SELECT_CLAUSE],(strlen((yyvsp[(2) - (4)].text))+40)," SELECT %s,",(yyvsp[(2) - (4)].text));
                snprintf(fuzzy_query[FROM_CLAUSE],(strlen((yyvsp[(4) - (4)].text))+60)," FROM %s ",(yyvsp[(4) - (4)].text));

                real_length=2;
            ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 260 "gram.y"
    {
				int i,len=0;
				
				for(i=0;i<filter_times;i++)
					len+=strlen(sub_sqlf_filters[i]);

				len+=10;
                fuzzy_query[WHERE_CLAUSE]=(char *)palloc(sizeof(char *)+len);
                strcpy(fuzzy_query[WHERE_CLAUSE],"WHERE ");

				for(i=0;i<filter_times;i++)
					strcat(fuzzy_query[WHERE_CLAUSE],sub_sqlf_filters[i]);
							
                real_length=3;
            ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 277 "gram.y"
    {
                int len;
                len=strlen((yyvsp[(4) - (4)].text))+2;
                fuzzy_query[ORDER_BY_CLAUSE]=(char *)palloc(sizeof(char *)*len);
                snprintf(fuzzy_query[ORDER_BY_CLAUSE],(strlen((yyvsp[(4) - (4)].text))+20),", %s",(yyvsp[(4) - (4)].text));
                real_length=4;
            ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 286 "gram.y"
    {
                int len;
                len=strlen((yyvsp[(4) - (4)].text))+2;
                fuzzy_query[CALIBRATION_CLAUSE]=(char *)palloc(sizeof(char *)*len);
                snprintf(fuzzy_query[CALIBRATION_CLAUSE],len,"%s",(yyvsp[(4) - (4)].text));
                real_length=5;
            ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 295 "gram.y"
    { (yyval.text) = (yyvsp[(1) - (1)].text); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 298 "gram.y"
    { (yyval.text) = (yyvsp[(1) - (1)].text); ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 299 "gram.y"
    {
                strcat((yyval.text),", ");
                strcat((yyval.text),(yyvsp[(3) - (3)].text));
            ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 303 "gram.y"
    {
                strcat((yyval.text)," AS ");
                strcat((yyval.text),(yyvsp[(3) - (3)].text));
            ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 307 "gram.y"
    {
                strcat((yyval.text)," ");
                strcat((yyval.text),(yyvsp[(2) - (2)].text));
            ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 314 "gram.y"
    { (yyval.text) = (yyvsp[(1) - (1)].text);;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 315 "gram.y"
    {
			strcat((yyval.text),", ");
			strcat((yyval.text),(yyvsp[(3) - (3)].text));
		;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 319 "gram.y"
    {
			strcat((yyval.text)," AS ");
			strcat((yyval.text),(yyvsp[(3) - (3)].text));
		;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 323 "gram.y"
    {
			strcat((yyval.text)," ");
			strcat((yyval.text),(yyvsp[(2) - (2)].text));
		;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 327 "gram.y"
    {
			strcat((yyval.text)," INNER JOIN ");
			strcat((yyval.text),(yyvsp[(4) - (4)].text));
		;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 331 "gram.y"
    {
			strcat((yyval.text)," LEFT JOIN ");
			strcat((yyval.text),(yyvsp[(4) - (4)].text));
		;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 335 "gram.y"
    {
			strcat((yyval.text)," RIGHT JOIN ");
			strcat((yyval.text),(yyvsp[(4) - (4)].text));
		;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 339 "gram.y"
    {
			strcat((yyval.text)," ON ");
			strcat((yyval.text),(yyvsp[(3) - (5)].text));
			strcat((yyval.text)," = ");
			strcat((yyval.text),(yyvsp[(5) - (5)].text));
		;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 349 "gram.y"
    {
			(yyval.text)=(yyvsp[(1) - (1)].text);
			field=(char *)palloc(sizeof(char *)*strlen((yyvsp[(1) - (1)].text)));
			strcpy(field,(yyvsp[(1) - (1)].text));
		;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 354 "gram.y"
    {
			field=(char *)palloc(sizeof(char *)*strlen((yyvsp[(2) - (2)].text)));
			strcpy(field,(yyvsp[(2) - (2)].text));
							
			sub_sqlf_filters[filter_times]=(char *)palloc(sizeof(char *)+2);
			snprintf(sub_sqlf_filters[filter_times],2,"(");
			filter_times++;
		;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 362 "gram.y"
    {
			int len;
			char *str_filter;
			char *str_result;
			
			//I use str_filter to save the translated filter from sqlf to sql
			len=strlen(field)+strlen((yyvsp[(3) - (3)].text))+15; //15 is the length of "%s > %f AND %s < %f"
			str_result=(char *)palloc(sizeof(char *)*(len));

			is_fuzzy=0;
			str_filter=(char *)palloc(sizeof(char *)*(len));
			str_filter=translate_fuzzy_preds(str_result,field,(yyvsp[(3) - (3)].text),&membdg_values.min,&membdg_values.first_core,
			&membdg_values.second_core,&membdg_values.max,&is_fuzzy);

			if (is_fuzzy==1){
				
				//if there's more than one field and ignoring the parenthesis
				if (filter_times>0 && strcmp(sub_sqlf_filters[filter_times-1],"(")!=0 ){
					args_membdg[count_membdg]=(char *)palloc(sizeof(char *)+2);
					snprintf(args_membdg[count_membdg],2,",");
					count_membdg++;
				}
				
				//This is used to get the membership degree
				len=strlen(field)+100;
				args_membdg[count_membdg]=(char *)palloc(sizeof(char *)*len);
				snprintf(args_membdg[count_membdg],len,
						"fuzzy.membdg(%s,'%s'::text,'%s'::text,'%s'::text,'%s'::text)",field,
						membdg_values.min,membdg_values.first_core,membdg_values.second_core,membdg_values.max);
			
				count_membdg++;
			}
			len=strlen(str_filter);

			sub_sqlf_filters[filter_times]=(char *)palloc(sizeof(char *)*len*2);

			snprintf(sub_sqlf_filters[filter_times],(len*2),"%s",str_filter);

			filter_times++;
			pfree(str_result);
		;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 403 "gram.y"
    {

			//I add a comma to args_membdg to separate the memberships degrees
			fop=LEAST;

			//This I add an AND to the sub_sqlf_filters array
			sub_sqlf_filters[filter_times]=(char *)palloc(sizeof(char *)+10);
			snprintf(sub_sqlf_filters[filter_times],10," AND ");
			filter_times++;
			
			//Add a field name to field variable
			field=(char *)palloc(sizeof(char *)*strlen((yyvsp[(3) - (3)].text)));
			strcpy(field,(yyvsp[(3) - (3)].text));
		;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 417 "gram.y"
    {
			field=(char *)palloc(sizeof(char *)*strlen((yyvsp[(4) - (4)].text)));
			strcpy(field,(yyvsp[(4) - (4)].text));

			sub_sqlf_filters[filter_times]=(char *)palloc(sizeof(char *)+6);
			snprintf(sub_sqlf_filters[filter_times],6,") AND ");
			filter_times++;
		;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 425 "gram.y"
    {

			fop=GREATEST;
			args_membdg[count_membdg]=(char *)palloc(sizeof(char *)+2);
			snprintf(args_membdg[count_membdg],2,",");
			count_membdg++;

			sub_sqlf_filters[filter_times]=(char *)palloc(sizeof(char *)+10);
			snprintf(sub_sqlf_filters[filter_times],10," OR ");
			filter_times++;

			field=(char *)palloc(sizeof(char *)*strlen((yyvsp[(3) - (3)].text)));
			strcpy(field,(yyvsp[(3) - (3)].text));
		;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 439 "gram.y"
    {
			field=(char *)palloc(sizeof(char *)*strlen((yyvsp[(4) - (4)].text)));
			strcpy(field,(yyvsp[(4) - (4)].text));

			sub_sqlf_filters[filter_times]=(char *)palloc(sizeof(char *)+6);
			snprintf(sub_sqlf_filters[filter_times],6,") OR ");
			filter_times++;
		;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 447 "gram.y"
    {
			sub_sqlf_filters[filter_times]=(char *)palloc(sizeof(char *)+2);
			snprintf(sub_sqlf_filters[filter_times],2,")");
			filter_times++;
		;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 456 "gram.y"
    { (yyval.text)=(yyvsp[(1) - (1)].text); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 457 "gram.y"
    {
                strcat((yyval.text),", ");
                strcat((yyval.text),(yyvsp[(3) - (3)].text));
            ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 461 "gram.y"
    { 
                strcat((yyval.text)," ASC");
                strcat((yyval.text),(yyvsp[(1) - (2)].text));
            ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 465 "gram.y"
    { 
                strcat((yyval.text)," DESC");
                strcat((yyval.text),(yyvsp[(1) - (2)].text));
            ;}
    break;



/* Line 1455 of yacc.c  */
#line 2030 "gram.c"
      default: break;
    }
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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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
      if (yyn != YYPACT_NINF)
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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
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



/* Line 1675 of yacc.c  */
#line 471 "gram.y"

void yyerror (char *s) {elog (ERROR, "%s\n", s);}

int ScanKeyword(const char *word){
        int i,len;

    Keyword keyfuzzywords[] = {
			{"AND",AND},
			{"AS",AS},
			{"CREATE",CREATE},
			{"DROP",DROP},
			{"FROM",FROM},
			{"FUZZY",FUZZY},
			{"INFINIT",INFINIT},
			{"ON",ON},
			{"OR",OR},
			{"PREDICATE",PREDICATE},
			{"SELECT",SELECT},
			{"WHERE",WHERE},
			{"ORDER",ORDER},
			{"BY",BY},
			{"ASC",ASC},
			{"DESC",DESC},
			{"WITH",WITH},
			{"CALIBRATION",CALIBRATION},
			{"INNER",INNER},
			{"JOIN",JOIN},
			{"LEFT",LEFT},
			{"RIGHT",RIGHT}
    };

    len=sizeof(keyfuzzywords)/sizeof(Keyword);

    for(i=0;i<len;i++){
            if (strcmp(keyfuzzywords[i].name,word)==0)
                    return keyfuzzywords[i].value;
    }

    return 0;
}

#include "scan.c"

