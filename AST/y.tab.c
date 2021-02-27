/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 1 "ast.y"

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <limits.h>
	// #define COUNT 10	

	void yyerror(const char*);
	int yylex();
	extern FILE * yyin, *yyout;

	int x=0;	

	extern int line;
	
	int scope = 0;

	int unaryop = -1;		//unary operator type
	int assignop = -1;		//assignment operator == += -=
	int datatype = -1;		//type specifier
	int assigntype = -1;	//RHS type 
	int idcheck = -1;		//check if ID 
	int check_un = 0;		//check for undeclared variables


	char tempStr[100];		//sprintf

	struct node{
		char token[20];
		char name[20];
		int dtype;
		int scope;
		int lineno;
		int valid;
		union value{
			float f;
			int i;
			char c;
		}val;
		
		struct node *link;

	}*first = NULL, *tmp, *crt, *lhs;

	typedef struct Node{
		struct Node *left;
		struct Node *right;
		char token[100];
		struct Node *val;
		int level;
	}Node;

	typedef struct tree_stack{
		Node *node;
		struct tree_stack *next;
	}tree_stack;

	tree_stack *tree_top = NULL;
	char preBuf[1000000];

	struct node * checksym(char *);
	void addsymbol(struct node *,char *);	
	void addInt(struct node *, int, int);
	void addFloat(struct node *, int, float);
	void addChar(struct node *, int, char);
	void addfunc(struct node *t, int, char *);
	void printsymtable();

	struct node * addtosymbol(struct node * n);
	void cleansymbol();


	//AST 
	void create_node(char *token, int leaf);
	void push_tree(Node *newnode);
	Node *pop_tree();
	void preorder(Node* root);
	void printtree(Node* root);
	int getmaxlevel(Node *root);
	void printGivenLevel(Node* root, int level, int h);
	void get_levels(Node *root, int level);




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
/* Line 193 of yacc.c.  */
#line 251 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 264 "y.tab.c"

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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
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
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   253

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  98
/* YYNRULES -- Number of states.  */
#define YYNSTATES  168

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   288

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    48,     2,     2,     2,    14,     2,     2,
      43,    44,    13,    10,    45,    11,     2,    12,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    47,    42,
      38,    15,    39,    46,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    40,     2,    41,    49,     2,     2,     2,
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
       5,     6,     7,     8,     9,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    50,    51
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,    12,    17,    19,    21,    24,    26,
      28,    30,    33,    37,    39,    42,    44,    46,    49,    52,
      55,    60,    67,    71,    73,    75,    77,    79,    85,    93,
      99,   101,   103,   105,   107,   109,   113,   114,   119,   121,
     123,   124,   129,   131,   133,   135,   137,   139,   141,   143,
     149,   151,   154,   156,   160,   162,   164,   166,   168,   172,
     174,   177,   180,   182,   185,   187,   189,   191,   193,   195,
     197,   199,   203,   207,   209,   213,   217,   221,   225,   227,
     231,   235,   237,   241,   245,   249,   253,   256,   261,   265,
     267,   272,   277,   281,   283,   287,   290,   292,   294
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      53,     0,    -1,    54,    -1,     3,     4,    38,    57,    39,
      54,    -1,     3,     4,     7,    54,    -1,    55,    -1,    56,
      -1,    55,    56,    -1,    62,    -1,    84,    -1,     5,    -1,
      40,    41,    -1,    40,    59,    41,    -1,    60,    -1,    59,
      60,    -1,    62,    -1,    63,    -1,    85,    42,    -1,     9,
      74,    -1,    61,    42,    -1,     8,    43,     6,    44,    -1,
       8,    43,     6,    45,    75,    44,    -1,    66,    67,    42,
      -1,    58,    -1,    74,    -1,    65,    -1,    64,    -1,    37,
      43,    81,    44,    63,    -1,    35,    43,    74,    74,    75,
      44,    63,    -1,    36,    43,    81,    44,    63,    -1,    34,
      -1,    31,    -1,    32,    -1,    33,    -1,    68,    -1,    67,
      45,    68,    -1,    -1,    19,    69,    15,    70,    -1,    19,
      -1,    73,    -1,    -1,    78,    71,    72,    70,    -1,    15,
      -1,    29,    -1,    30,    -1,    26,    -1,    27,    -1,    28,
      -1,    80,    -1,    80,    46,    75,    47,    73,    -1,    42,
      -1,    75,    42,    -1,    70,    -1,    75,    45,    70,    -1,
      19,    -1,    16,    -1,    18,    -1,    17,    -1,    43,    75,
      44,    -1,    76,    -1,    77,    20,    -1,    77,    21,    -1,
      77,    -1,    79,    78,    -1,    10,    -1,    11,    -1,    48,
      -1,    49,    -1,    50,    -1,    51,    -1,    81,    -1,    80,
      24,    81,    -1,    80,    25,    81,    -1,    82,    -1,    81,
      38,    82,    -1,    81,    39,    82,    -1,    81,    22,    82,
      -1,    81,    23,    82,    -1,    83,    -1,    82,    10,    83,
      -1,    82,    11,    83,    -1,    78,    -1,    83,    13,    78,
      -1,    83,    12,    78,    -1,    83,    14,    78,    -1,    66,
      86,    58,    -1,    86,    58,    -1,    86,    43,    89,    44,
      -1,    86,    43,    44,    -1,    19,    -1,    86,    43,    87,
      44,    -1,    86,    43,    89,    44,    -1,    86,    43,    44,
      -1,    88,    -1,    87,    45,    88,    -1,    66,    19,    -1,
      66,    -1,    19,    -1,    89,    45,    19,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   128,   128,   136,   137,   138,   143,   144,   149,   150,
     155,   160,   161,   166,   167,   175,   176,   177,   178,   182,
     187,   188,   193,   198,   210,   211,   212,   216,   222,   226,
     234,   235,   236,   237,   242,   243,   248,   248,   356,   423,
     424,   424,   673,   674,   675,   676,   677,   678,   683,   684,
     699,   700,   705,   706,   711,   745,   754,   772,   790,   797,
     798,   799,   804,   805,   833,   834,   835,   836,   837,   838,
     843,   844,   853,   865,   866,   875,   884,   893,   906,   907,
     912,   921,   922,   927,   941,   960,   978,  1005,  1006,  1011,
    1018,  1019,  1020,  1025,  1026,  1031,  1032,  1037,  1038
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "HASH", "INCLUDE", "IOSTREAM",
  "STRING_LITERAL", "HEADER_LITERAL", "PRINT", "RETURN", "'+'", "'-'",
  "'/'", "'*'", "'%'", "'='", "INTEGER_LITERAL", "CHARACTER_LITERAL",
  "FLOAT_LITERAL", "IDENTIFIER", "INC_OP", "DEC_OP", "LE_OP", "GE_OP",
  "EQ_OP", "NE_OP", "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "ADD_ASSIGN",
  "SUB_ASSIGN", "CHAR", "INT", "FLOAT", "VOID", "FOR", "WHILE", "IF",
  "'<'", "'>'", "'{'", "'}'", "';'", "'('", "')'", "','", "'?'", "':'",
  "'!'", "'~'", "\"INC_OP\"", "\"DEC_OP\"", "$accept", "S", "program",
  "translation_unit", "ext_dec", "libraries", "compound_statement",
  "block_item_list", "block_item", "printstat", "declaration", "statement",
  "condition_statement", "iteration_statement", "type_specifier",
  "init_declarator_list", "init_declarator", "@1", "assignment_expression",
  "@2", "assignment_operator", "conditional_expression",
  "expression_statement", "expression", "primary_expression",
  "postfix_expression", "unary_expression", "unary_operator",
  "equality_expression", "relational_expression", "additive_expression",
  "multiplicative_expression", "function_definition", "function_call",
  "declarator", "parameter_list", "parameter_declaration",
  "identifier_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
      43,    45,    47,    42,    37,    61,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   276,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,    60,    62,
     123,   125,    59,    40,    41,    44,    63,    58,    33,   126,
     287,   288
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    52,    53,    54,    54,    54,    55,    55,    56,    56,
      57,    58,    58,    59,    59,    60,    60,    60,    60,    60,
      61,    61,    62,    63,    63,    63,    63,    64,    65,    65,
      66,    66,    66,    66,    67,    67,    69,    68,    68,    70,
      71,    70,    72,    72,    72,    72,    72,    72,    73,    73,
      74,    74,    75,    75,    76,    76,    76,    76,    76,    77,
      77,    77,    78,    78,    79,    79,    79,    79,    79,    79,
      80,    80,    80,    81,    81,    81,    81,    81,    82,    82,
      82,    83,    83,    83,    83,    84,    84,    85,    85,    86,
      86,    86,    86,    87,    87,    88,    88,    89,    89
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     6,     4,     1,     1,     2,     1,     1,
       1,     2,     3,     1,     2,     1,     1,     2,     2,     2,
       4,     6,     3,     1,     1,     1,     1,     5,     7,     5,
       1,     1,     1,     1,     1,     3,     0,     4,     1,     1,
       0,     4,     1,     1,     1,     1,     1,     1,     1,     5,
       1,     2,     1,     3,     1,     1,     1,     1,     3,     1,
       2,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     2,     4,     3,     1,
       4,     4,     3,     1,     3,     2,     1,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    89,    31,    32,    33,    30,     0,     2,     5,
       6,     8,     0,     9,     0,     0,     1,     7,    38,     0,
      34,     0,     0,     0,    86,     0,     0,     0,    22,     0,
      85,     0,     0,    64,    65,    55,    57,    56,    54,     0,
       0,     0,    11,    50,     0,    66,    67,    68,    69,    23,
       0,    13,     0,    15,    16,    26,    25,     0,    52,    39,
      24,     0,    59,    62,    81,     0,    48,    70,    73,    78,
       0,     0,    97,    92,    96,     0,    93,     0,     4,    10,
       0,     0,    38,    35,     0,    54,    18,     0,     0,     0,
       0,    12,    14,    19,    51,     0,    60,    61,     0,    63,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    17,     0,    95,    90,     0,    91,     0,     0,
      37,     0,     0,    81,     0,     0,    58,    53,    42,    45,
      46,    47,    43,    44,     0,    71,    72,     0,    76,    77,
      74,    75,    79,    80,    83,    82,    84,    88,     0,    94,
      98,     3,    20,     0,     0,     0,     0,    41,     0,    87,
       0,     0,    29,    27,    49,    21,     0,    28
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     7,     8,     9,    10,    80,    49,    50,    51,    52,
      11,    54,    55,    56,    12,    19,    20,    27,    58,    98,
     134,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    13,    70,    14,    75,    76,    77
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -139
static const yytype_int16 yypact[] =
{
     160,     6,  -139,  -139,  -139,  -139,  -139,    15,  -139,    -8,
    -139,  -139,     8,  -139,    26,    -2,  -139,  -139,    20,    51,
    -139,    26,    71,   168,  -139,   160,    57,    63,  -139,    72,
    -139,    86,    22,  -139,  -139,  -139,  -139,  -139,    94,   116,
     121,   126,  -139,  -139,   117,  -139,  -139,  -139,  -139,  -139,
     107,  -139,   134,  -139,  -139,  -139,  -139,    72,  -139,  -139,
    -139,    56,  -139,    -1,   189,   117,   -12,    45,    75,   118,
     146,   137,  -139,  -139,    80,   177,  -139,   188,  -139,  -139,
     157,   117,   208,  -139,   224,  -139,  -139,    22,   117,   117,
     190,  -139,  -139,  -139,  -139,   117,  -139,  -139,   198,  -139,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,  -139,   176,  -139,  -139,    23,  -139,   195,   160,
    -139,   192,    22,  -139,   159,   167,  -139,  -139,  -139,  -139,
    -139,  -139,  -139,  -139,   117,    45,    45,   184,    75,    75,
      75,    75,   118,   118,  -139,  -139,  -139,   204,   194,  -139,
    -139,  -139,  -139,   117,   117,   135,   135,  -139,   117,   205,
     196,   199,  -139,  -139,  -139,  -139,   135,  -139
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -139,  -139,   -22,  -139,   233,  -139,     0,  -139,   200,  -139,
     -13,  -138,  -139,  -139,   -21,  -139,   220,  -139,   -73,  -139,
    -139,    93,   -28,   -44,  -139,  -139,   -58,  -139,  -139,    73,
     -29,   138,  -139,  -139,    -6,  -139,   136,   140
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -93
static const yytype_int16 yytable[] =
{
      90,    57,    74,    78,    86,    25,    21,    99,   120,    53,
      15,     2,   100,   101,    24,    16,    71,   162,   163,    96,
      97,    30,   127,     3,     4,     5,     6,    18,   167,    57,
     123,   123,    33,    34,   102,   -36,    26,    53,    35,    36,
      37,    85,   123,   123,    71,   123,   123,   123,   123,   123,
     123,   144,   145,   146,     3,     4,     5,     6,   137,   122,
     -89,   157,    79,   -89,    43,    44,    22,   103,   104,    23,
      45,    46,    47,    48,   138,   139,   140,   141,    81,    31,
      32,    33,    34,   105,   106,   107,   108,    35,    36,    37,
      38,    82,    74,    28,   154,    74,    29,   151,    94,   114,
     123,    95,     3,     4,     5,     6,    39,    40,    41,   160,
     161,    22,    42,    43,    44,    31,    32,    33,    34,    45,
      46,    47,    48,    35,    36,    37,    38,    33,    34,    84,
     109,   110,   111,    35,    36,    37,    85,   -89,     3,     4,
       5,     6,    39,    40,    41,    33,    34,    22,    91,    43,
      44,    35,    36,    37,    85,    45,    46,    47,    48,    87,
      44,   124,   125,     1,    88,    45,    46,    47,    48,    89,
      39,    40,    41,   135,   136,    22,    93,    43,    44,     2,
     113,   103,   104,    45,    46,    47,    48,    72,   112,   103,
     104,     3,     4,     5,     6,    72,   119,   105,   106,     3,
       4,     5,     6,   155,   -40,   105,   106,     3,     4,     5,
       6,   156,    73,   128,   150,   -40,   -40,   -40,   -40,   -40,
     147,   115,   116,   -36,   129,   130,   131,   132,   133,    95,
     121,   158,   117,   118,   126,    95,   152,   153,   159,   118,
     165,    95,    17,   166,    95,   142,   143,   -92,   -91,    83,
      92,   164,   149,   148
};

static const yytype_uint8 yycheck[] =
{
      44,    22,    23,    25,    32,     7,    12,    65,    81,    22,
       4,    19,    24,    25,    14,     0,    22,   155,   156,    20,
      21,    21,    95,    31,    32,    33,    34,    19,   166,    50,
      88,    89,    10,    11,    46,    15,    38,    50,    16,    17,
      18,    19,   100,   101,    50,   103,   104,   105,   106,   107,
     108,   109,   110,   111,    31,    32,    33,    34,   102,    87,
      40,   134,     5,    43,    42,    43,    40,    22,    23,    43,
      48,    49,    50,    51,   103,   104,   105,   106,    15,     8,
       9,    10,    11,    38,    39,    10,    11,    16,    17,    18,
      19,    19,   113,    42,   122,   116,    45,   119,    42,    19,
     158,    45,    31,    32,    33,    34,    35,    36,    37,   153,
     154,    40,    41,    42,    43,     8,     9,    10,    11,    48,
      49,    50,    51,    16,    17,    18,    19,    10,    11,    43,
      12,    13,    14,    16,    17,    18,    19,    43,    31,    32,
      33,    34,    35,    36,    37,    10,    11,    40,    41,    42,
      43,    16,    17,    18,    19,    48,    49,    50,    51,    43,
      43,    88,    89,     3,    43,    48,    49,    50,    51,    43,
      35,    36,    37,   100,   101,    40,    42,    42,    43,    19,
      43,    22,    23,    48,    49,    50,    51,    19,    42,    22,
      23,    31,    32,    33,    34,    19,    39,    38,    39,    31,
      32,    33,    34,    44,    15,    38,    39,    31,    32,    33,
      34,    44,    44,    15,    19,    26,    27,    28,    29,    30,
      44,    44,    45,    15,    26,    27,    28,    29,    30,    45,
       6,    47,    44,    45,    44,    45,    44,    45,    44,    45,
      44,    45,     9,    44,    45,   107,   108,    43,    43,    29,
      50,   158,   116,   113
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    19,    31,    32,    33,    34,    53,    54,    55,
      56,    62,    66,    84,    86,     4,     0,    56,    19,    67,
      68,    86,    40,    43,    58,     7,    38,    69,    42,    45,
      58,     8,     9,    10,    11,    16,    17,    18,    19,    35,
      36,    37,    41,    42,    43,    48,    49,    50,    51,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    70,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      85,    86,    19,    44,    66,    87,    88,    89,    54,     5,
      57,    15,    19,    68,    43,    19,    74,    43,    43,    43,
      75,    41,    60,    42,    42,    45,    20,    21,    71,    78,
      24,    25,    46,    22,    23,    38,    39,    10,    11,    12,
      13,    14,    42,    43,    19,    44,    45,    44,    45,    39,
      70,     6,    74,    78,    81,    81,    44,    70,    15,    26,
      27,    28,    29,    30,    72,    81,    81,    75,    82,    82,
      82,    82,    83,    83,    78,    78,    78,    44,    89,    88,
      19,    54,    44,    45,    74,    44,    44,    70,    47,    44,
      75,    75,    63,    63,    73,    44,    44,    63
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
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
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
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
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
        case 2:
#line 128 "ast.y"
    {
				cleansymbol();	
                printsymtable();
                return 0;
            }
    break;

  case 14:
#line 168 "ast.y"
    {
				create_node("stmt", 0);
			}
    break;

  case 18:
#line 179 "ast.y"
    {
				create_node("return", 1);
			}
    break;

  case 23:
#line 198 "ast.y"
    {
						struct node *ftp;
						ftp = first;
						while(ftp!=NULL){
							if(ftp->scope == scope && ftp->valid == 1){
								ftp->valid = 0;
							}
							ftp=ftp->link;
						}
						scope--;

					}
    break;

  case 27:
#line 216 "ast.y"
    {create_node("if", 0);}
    break;

  case 28:
#line 223 "ast.y"
    { 
				create_node("for", 0); 
			}
    break;

  case 29:
#line 227 "ast.y"
    {
		create_node("while", 0); 
	}
    break;

  case 30:
#line 234 "ast.y"
    {	datatype = (yyvsp[(1) - (1)].ival); }
    break;

  case 31:
#line 235 "ast.y"
    {	datatype = (yyvsp[(1) - (1)].ival); }
    break;

  case 32:
#line 236 "ast.y"
    {	datatype = (yyvsp[(1) - (1)].ival); }
    break;

  case 33:
#line 237 "ast.y"
    {	datatype = (yyvsp[(1) - (1)].ival); }
    break;

  case 36:
#line 248 "ast.y"
    { create_node((yyvsp[(1) - (1)].ptr)->name, 1); }
    break;

  case 37:
#line 249 "ast.y"
    {	
						if((yyvsp[(1) - (4)].ptr)->dtype !=- 1 && (yyvsp[(1) - (4)].ptr)->scope < scope && (yyvsp[(1) - (4)].ptr)->valid == 1){
																		
							struct node *ftp, *nnode;
							nnode = (struct node *)malloc(sizeof(struct node));
							ftp = first;
							while(ftp->link!=NULL){
								ftp = ftp->link;
							}
							addsymbol(nnode,(yyvsp[(1) - (4)].ptr)->name);	
							ftp->link = nnode;
							nnode->link = NULL;
							(yyvsp[(1) - (4)].ptr) = nnode;

							if (datatype == 0){	
								
								addInt((yyvsp[(1) - (4)].ptr), 0, (yyvsp[(4) - (4)].fval));
								if(assigntype == 1){
									printf("Line:%d: ", line);
									printf("\033[1;35m"); 
									printf("warning: ");
									printf("\033[0m");
									printf("implicit conversion from \'float\' to \'int\' \n\n");
								}
							}
							else if(datatype == 1){
								
								addFloat((yyvsp[(1) - (4)].ptr), 1, (yyvsp[(4) - (4)].fval));
								if(assigntype == 2){
									printf("Line:%d: ", line);
									printf("\033[1;35m"); 
									printf("warning: ");
									printf("\033[0m");
									printf("implicit conversion from \'char\' to \'float\' \n\n");
								}
							}
							else if(datatype == 2){
								float tempf = (float)(yyvsp[(4) - (4)].fval);
								addChar((yyvsp[(1) - (4)].ptr), 2, (int)tempf);

								if(assigntype == 1){
									printf("Line:%d: ", line);
									printf("\033[1;35m"); 
									printf("warning: ");
									printf("\033[0m");
									printf("implicit conversion from \'float\' to \'char\' \n\n");
								}
							}
							x = datatype;
							
							create_node("=", 0);

						}

						
						else if((yyvsp[(1) - (4)].ptr)->dtype !=- 1){

								printf("Line:%d: ", line);
								printf("\033[1;31m");
								printf("error: ");
								printf("\033[0m");
								printf("redefinition of \'%s\' \n",  (yyvsp[(1) - (4)].ptr)->name);
						}
						else{
							
							
							create_node("=", 0);

							if (datatype == 0){	
								
								addInt((yyvsp[(1) - (4)].ptr), 0, (yyvsp[(4) - (4)].fval));
								if(assigntype == 1){
									printf("Line:%d: ", line);
									printf("\033[1;35m"); 
									printf("warning: ");
									printf("\033[0m");
									printf("implicit conversion from \'float\' to \'int\' \n\n");
								}
							}
							else if(datatype == 1){
								
								addFloat((yyvsp[(1) - (4)].ptr), 1, (yyvsp[(4) - (4)].fval));
								if(assigntype == 2){
									printf("Line:%d: ", line);
									printf("\033[1;35m"); 
									printf("warning: ");
									printf("\033[0m");
									printf("implicit conversion from \'char\' to \'float\' \n\n");
								}
							}
							else if(datatype == 2){
								float tempf = (float)(yyvsp[(4) - (4)].fval);
								addChar((yyvsp[(1) - (4)].ptr), 2, (int)tempf);

								if(assigntype == 1){
									printf("Line:%d: ", line);
									printf("\033[1;35m"); 
									printf("warning: ");
									printf("\033[0m");
									printf("implicit conversion from \'float\' to \'char\' \n\n");
								}
							}
							x = datatype;
							
						}
					}
    break;

  case 38:
#line 356 "ast.y"
    {	//previous. a , dtype = 1(int)
						// printf("type = %d\nscope = %d\nvalid = %d", $1->dtype, $1->scope, $1->valid);
						if((yyvsp[(1) - (1)].ptr)->dtype !=- 1 && (yyvsp[(1) - (1)].ptr)->scope < scope && (yyvsp[(1) - (1)].ptr)->valid == 1){
							// printf("case 1 \n" );
																		
							struct node *ftp, *nnode;
							nnode = (struct node *)malloc(sizeof(struct node));
							ftp = first;
							while(ftp->link!=NULL){
								ftp = ftp->link;
							}
							addsymbol(nnode,(yyvsp[(1) - (1)].ptr)->name);	
							ftp->link = nnode;
							nnode->link = NULL;							
							(yyvsp[(1) - (1)].ptr) = nnode;
							
							if (datatype == 0){	
								addInt((yyvsp[(1) - (1)].ptr), 0, INT_MIN);
							}
							else if(datatype == 1){
								addFloat((yyvsp[(1) - (1)].ptr), 1, INT_MIN);
							}
							else if(datatype == 2){
								addChar((yyvsp[(1) - (1)].ptr), 2, '-');
		
							}
							x = datatype;

							char buff[20];
							strcpy(buff, "Dc ");
							strcat(buff, (yyvsp[(1) - (1)].ptr)->name);
							create_node(buff, 1);

						}
						else if((yyvsp[(1) - (1)].ptr)->dtype !=- 1 ){
							printf("Line:%d: ", line);
							printf("\033[1;31m");
							printf("error: ");
							printf("\033[0m");
							printf("redefinition of \'%s\' \n", (yyvsp[(1) - (1)].ptr)->name);
						
						}else{
							

							if (datatype == 0){	
								addInt((yyvsp[(1) - (1)].ptr), 0, INT_MIN);
							}
							else if(datatype == 1){
								addFloat((yyvsp[(1) - (1)].ptr), 1, INT_MIN);
							}
							else if(datatype == 2){
								addChar((yyvsp[(1) - (1)].ptr), 2, '-');
		
							}
							x = datatype;

							char buff[20];
							strcpy(buff, "Dc ");
							strcat(buff, (yyvsp[(1) - (1)].ptr)->name);
							create_node(buff, 1);
						
						}
					}
    break;

  case 39:
#line 423 "ast.y"
    {	(yyval.fval) = (yyvsp[(1) - (1)].fval); }
    break;

  case 40:
#line 424 "ast.y"
    { crt = lhs; }
    break;

  case 41:
#line 425 "ast.y"
    {							
				switch(assignop){
					case 0: if(idcheck == 1){
								create_node("=", 0);
								if(crt->dtype == 0){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'float\' to \'int\' \n\n");
									}
									crt->val.i = (int)(yyvsp[(4) - (4)].fval);
									
								}
								else if(crt->dtype == 1){
									if(assigntype == 2){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'char\' to \'float\' \n\n");
									}
									crt->val.f = (yyvsp[(4) - (4)].fval);
								}
								else if(crt->dtype == 2){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'float\' to \'char\' \n\n");
									}
									crt->val.c = (char)((int)(yyvsp[(4) - (4)].fval));
								}
							}
							else{
								printf("We'll see later\n");
							}
							crt = NULL;
							break;

					case 1: if(idcheck == 1){
								create_node("+=", 0);
								if(crt->dtype == 0){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'float\' to \'int\' \n\n");
									}
									crt->val.i = (int)(yyvsp[(1) - (4)].fval) + (int)(yyvsp[(4) - (4)].fval);
								}
								else if(crt->dtype == 1){
									if(assigntype == 2){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'char\' to \'float\' \n\n");
									}
									crt->val.f = (yyvsp[(1) - (4)].fval)+ (yyvsp[(4) - (4)].fval);
								}
								else if(crt->dtype == 2){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'float\' to \'char\' \n\n");
									}
									crt->val.c = (char)((int)(yyvsp[(1) - (4)].fval) + (int)(yyvsp[(4) - (4)].fval));
								}
							}
							else{
								printf("We'll see later\n");
							}
							crt = NULL;
							break;

					case 2:	if(idcheck == 1){
							create_node("-=", 0);
								if(crt->dtype == 0){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'float\' to \'int\' \n\n");
									}
									crt->val.i = (int)(yyvsp[(1) - (4)].fval) - (int)(yyvsp[(4) - (4)].fval);
								}
								else if(crt->dtype == 1){
									if(assigntype == 2){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'char\' to \'float\' \n\n");
									}
									crt->val.f = (yyvsp[(1) - (4)].fval) - (yyvsp[(4) - (4)].fval);
								}
								else if(crt->dtype == 2){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'float\' to \'char\' \n\n");
									}
									crt->val.c = (char)((int)(yyvsp[(1) - (4)].fval) - (int)(yyvsp[(4) - (4)].fval));
								}
							}
							else{
								printf("We'll see later\n");
							}
							crt = NULL;
							break;

					case 3:	if(idcheck == 1){
								create_node("*=", 0);
								if(crt->dtype == 0){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'float\' to \'int\' \n\n");
									}
									crt->val.i = (int)(yyvsp[(1) - (4)].fval) * (int)(yyvsp[(4) - (4)].fval);
								}
								else if(crt->dtype == 1){
									if(assigntype == 2){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'char\' to \'float\' \n\n");
									}
									crt->val.f = (yyvsp[(1) - (4)].fval) * (yyvsp[(4) - (4)].fval);
								}
								else if(crt->dtype == 2){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'float\' to \'char\' \n\n");
									}
									crt->val.c = (char)((int)(yyvsp[(1) - (4)].fval) * (int)(yyvsp[(4) - (4)].fval));
								}
							}
							else{
								printf("We'll see later\n");
							}
							crt = NULL;
							break;

					case 4:	if(idcheck == 1){
								create_node("/=", 0);
								if(crt->dtype == 0){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'float\' to \'int\' \n\n");
									}
									crt->val.i = (int)(yyvsp[(1) - (4)].fval) / (int)(yyvsp[(4) - (4)].fval);
								}
								else if(crt->dtype == 1){
									if(assigntype == 2){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'char\' to \'float\' \n\n");
									}
									crt->val.f = (yyvsp[(1) - (4)].fval) / (yyvsp[(4) - (4)].fval);
								}
								else if(crt->dtype == 2){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'float\' to \'char\' \n\n");
									}
									crt->val.c = (char)((int)(yyvsp[(1) - (4)].fval) / (int)(yyvsp[(4) - (4)].fval));
								}
							}
							else{
								printf("We'll see later\n");
							}
							crt = NULL;
							break;

					case 5:	if(idcheck == 1){
								create_node("%=", 0);
								if(crt->dtype == 0){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'float\' to \'int\' \n\n");
									}
									crt->val.i = (int)(yyvsp[(1) - (4)].fval) % (int)(yyvsp[(4) - (4)].fval);
								}
								else if(crt->dtype == 1){
									if(assigntype == 2){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'char\' to \'float\' \n\n");
									}
									crt->val.f = (int)(yyvsp[(1) - (4)].fval) % (int)(yyvsp[(4) - (4)].fval);
								}
								else if(crt->dtype == 2){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										printf("\033[1;35m"); 
										printf("warning: ");
										printf("\033[0m");
										printf("implicit conversion from \'float\' to \'char\' \n\n");
									}
									crt->val.c = (char)((int)(yyvsp[(1) - (4)].fval) % (int)(yyvsp[(4) - (4)].fval));
								}
							}
							else{
								printf("We'll see later\n");
							}
							crt = NULL;
							break;


				}
				assignop = -1;
				assigntype = -1;
			}
    break;

  case 42:
#line 673 "ast.y"
    {	assignop = 0;	}
    break;

  case 43:
#line 674 "ast.y"
    {	assignop = 1;	}
    break;

  case 44:
#line 675 "ast.y"
    {	assignop = 2;	}
    break;

  case 45:
#line 676 "ast.y"
    {	assignop = 3;	}
    break;

  case 46:
#line 677 "ast.y"
    {	assignop = 4;	}
    break;

  case 47:
#line 678 "ast.y"
    {	assignop = 5;	}
    break;

  case 48:
#line 683 "ast.y"
    {	(yyval.fval) = (yyvsp[(1) - (1)].fval);	}
    break;

  case 49:
#line 685 "ast.y"
    {
				create_node("else", 0);
				create_node("if", 0);
				if((yyvsp[(1) - (5)].fval) == 1){
					(yyval.fval) = (yyvsp[(3) - (5)].fval);

				}else{
					(yyval.fval) = (yyvsp[(5) - (5)].fval);
				}
			}
    break;

  case 50:
#line 699 "ast.y"
    {				}
    break;

  case 51:
#line 700 "ast.y"
    {				}
    break;

  case 52:
#line 705 "ast.y"
    {		}
    break;

  case 53:
#line 706 "ast.y"
    {		}
    break;

  case 54:
#line 712 "ast.y"
    {					
					idcheck = 1;
					lhs = (yyvsp[(1) - (1)].ptr);

					if((yyvsp[(1) - (1)].ptr)->dtype == -1 && check_un == 0){

						printf("Line:%d: ", line);
						printf("\033[1;31m");
						printf("error: ");
						printf("\033[0m");
						printf("use of undeclared identifier \'%s\' \n\n", (yyvsp[(1) - (1)].ptr)->name);

						check_un = 0;		// set check_un = -1

					}
					else if((yyvsp[(1) - (1)].ptr)->dtype == 0){
						(yyval.fval) = (yyvsp[(1) - (1)].ptr)->val.i;
						assigntype = 0;
						create_node((yyvsp[(1) - (1)].ptr)->name, 1);
					}
					else if((yyvsp[(1) - (1)].ptr)->dtype == 1){
						(yyval.fval) = (yyvsp[(1) - (1)].ptr)->val.f;
						assigntype = 1;
						create_node((yyvsp[(1) - (1)].ptr)->name, 1);
					}
					else if((yyvsp[(1) - (1)].ptr)->dtype == 2){
						(yyval.fval) = (yyvsp[(1) - (1)].ptr)->val.c;
						assigntype = 2;
						create_node((yyvsp[(1) - (1)].ptr)->name, 1);
					}
						
									
				}
    break;

  case 55:
#line 746 "ast.y"
    {
					(yyval.fval) = (yyvsp[(1) - (1)].ival);
					assigntype = 0;
				
					sprintf(tempStr, "%d", (int)(yyvsp[(1) - (1)].ival));
					create_node(tempStr, 1);
				}
    break;

  case 56:
#line 755 "ast.y"
    {	
					assigntype = 1;
					if(datatype == 1){
						(yyval.fval) = (yyvsp[(1) - (1)].fval);
					}
					else if(datatype == 0){
						
						(yyval.fval) = (int)(yyvsp[(1) - (1)].fval);
					}
					else if(datatype == 2){

						(yyval.fval) = (int)(yyvsp[(1) - (1)].fval);
					}

					sprintf(tempStr, "%f", (yyvsp[(1) - (1)].fval));
					create_node(tempStr, 1);
				}
    break;

  case 57:
#line 773 "ast.y"
    {	
					assigntype = 2;
					if(datatype == 2){
						int tempc = (int)(yyvsp[(1) - (1)].cval);
						(yyval.fval) =  (float)tempc;
					}
					else if(datatype == 0){
						(yyval.fval) = (int)(yyvsp[(1) - (1)].cval);
					}
					else if(datatype == 1){
						
						(yyval.fval) = (int)(yyvsp[(1) - (1)].cval);
					}

					sprintf(tempStr, "%c", (yyvsp[(1) - (1)].cval));
					create_node(tempStr, 1);
				}
    break;

  case 58:
#line 791 "ast.y"
    {
					(yyval.fval) = (yyvsp[(2) - (3)].fval);
				}
    break;

  case 59:
#line 797 "ast.y"
    {	(yyval.fval) = (yyvsp[(1) - (1)].fval);	}
    break;

  case 60:
#line 798 "ast.y"
    {	(yyvsp[(1) - (2)].fval)++; (yyval.fval) = (yyvsp[(1) - (2)].fval);	create_node("++", 0); }
    break;

  case 61:
#line 799 "ast.y"
    {	(yyvsp[(1) - (2)].fval)--; (yyval.fval) = (yyvsp[(1) - (2)].fval);	create_node("--", 0); }
    break;

  case 62:
#line 804 "ast.y"
    {	(yyval.fval) = (yyvsp[(1) - (1)].fval);	}
    break;

  case 63:
#line 806 "ast.y"
    {
					switch(unaryop){
						case 1:	(yyval.fval) = (yyvsp[(2) - (2)].fval);
								create_node("'+'", 0);
								break;
						case 2:	(yyval.fval) = -(yyvsp[(2) - (2)].fval);
								create_node("'+'", 0);
								break;
						case 3:	(yyval.fval) = !(yyvsp[(2) - (2)].fval);
								create_node("!", 0);
								break;
						case 4:	(yyval.fval) = ~((int)(yyvsp[(2) - (2)].fval));
								create_node("~", 0);
								break;	
						case 5:	(yyval.fval) = ++(yyvsp[(2) - (2)].fval);
								create_node("++", 0);							
								break;
						case 6:	(yyval.fval) = --(yyvsp[(2) - (2)].fval);
								create_node("--", 0);
								break;		
					}
					unaryop = -1;
				}
    break;

  case 64:
#line 833 "ast.y"
    {	unaryop = 1;	}
    break;

  case 65:
#line 834 "ast.y"
    {	unaryop = 2;	}
    break;

  case 66:
#line 835 "ast.y"
    {	unaryop = 3;	}
    break;

  case 67:
#line 836 "ast.y"
    {	unaryop = 4;	}
    break;

  case 68:
#line 837 "ast.y"
    {	unaryop = 5;	}
    break;

  case 69:
#line 838 "ast.y"
    {	unaryop = 6;	}
    break;

  case 70:
#line 843 "ast.y"
    {	(yyval.fval) = (yyvsp[(1) - (1)].fval);	}
    break;

  case 71:
#line 845 "ast.y"
    { 
					create_node("==", 0);
					if((yyvsp[(1) - (3)].fval) == (yyvsp[(3) - (3)].fval))
						(yyval.fval) = 1;
					else
						(yyval.fval) = 0;

				}
    break;

  case 72:
#line 854 "ast.y"
    { 
					create_node("!=", 0);
					if((yyvsp[(1) - (3)].fval) != (yyvsp[(3) - (3)].fval))
						(yyval.fval) = 1;
					else
						(yyval.fval) = 0;
				}
    break;

  case 73:
#line 865 "ast.y"
    {	(yyval.fval) = (yyvsp[(1) - (1)].fval);	}
    break;

  case 74:
#line 867 "ast.y"
    { 
					create_node("<", 0);
					if((yyvsp[(1) - (3)].fval) < (yyvsp[(3) - (3)].fval))
						(yyval.fval) = 1;
					else
						(yyval.fval) = 0;

				}
    break;

  case 75:
#line 876 "ast.y"
    { 
					create_node(">", 0);
					if((yyvsp[(1) - (3)].fval) > (yyvsp[(3) - (3)].fval))
						(yyval.fval) = 1;
					else
						(yyval.fval) = 0;

				}
    break;

  case 76:
#line 885 "ast.y"
    { 
					create_node("<=", 0);
					if((yyvsp[(1) - (3)].fval) <= (yyvsp[(3) - (3)].fval))
						(yyval.fval) = 1;
					else
						(yyval.fval) = 0;

				}
    break;

  case 77:
#line 894 "ast.y"
    { 
					create_node(">=", 0);
					if((yyvsp[(1) - (3)].fval) >= (yyvsp[(3) - (3)].fval))
						(yyval.fval) = 1;
					else
						(yyval.fval) = 0;

				}
    break;

  case 78:
#line 906 "ast.y"
    {	(yyval.fval) = (yyvsp[(1) - (1)].fval);	}
    break;

  case 79:
#line 908 "ast.y"
    {	
				create_node("+", 0);
				(yyval.fval) = (yyvsp[(1) - (3)].fval) + (yyvsp[(3) - (3)].fval);	
			}
    break;

  case 80:
#line 913 "ast.y"
    {	
				create_node("-", 0);
				(yyval.fval) = (yyvsp[(1) - (3)].fval) - (yyvsp[(3) - (3)].fval);	
			}
    break;

  case 81:
#line 921 "ast.y"
    {	(yyval.fval) = (yyvsp[(1) - (1)].fval);	}
    break;

  case 82:
#line 923 "ast.y"
    {	
						create_node("*", 0);	
						(yyval.fval) = (yyvsp[(1) - (3)].fval) * (yyvsp[(3) - (3)].fval);	
					}
    break;

  case 83:
#line 928 "ast.y"
    {	
						if((yyvsp[(3) - (3)].fval) == 0){
							printf("Line:%d: ", line);
							printf("\033[1;35m"); 
							printf("warning: ");
							printf("\033[0m");
							printf("division by zero is undefined\n\n");
							(yyval.fval) = INT_MAX;		//junk value in real
						}else{
							(yyval.fval) = (yyvsp[(1) - (3)].fval) / (yyvsp[(3) - (3)].fval);	
							create_node("/", 0);
						}
					}
    break;

  case 84:
#line 942 "ast.y"
    {	
						if(assigntype == 1){
							printf("Line:%d: ", line);
							printf("\033[1;31m");
							printf("error: ");
							printf("\033[0m");
							printf("invalid operands to binary expression (\'float\' and \'float\') \n\n");
							}else{								
								(yyval.fval) = (int)(yyvsp[(1) - (3)].fval) % (int)(yyvsp[(3) - (3)].fval);	
								create_node("%", 0);
							}
						}
    break;

  case 85:
#line 961 "ast.y"
    {
					create_node((yyvsp[(2) - (3)].string), 3);
					struct node *ftp;
					ftp = first;
					while(ftp!=NULL){
						if(ftp->scope == scope && ftp->valid == 1){
							ftp->valid = 0;
						}
						else if(strcmp(ftp->token, "param") == 0 && ftp->valid == 1){
							ftp->valid = 0;
						}

						ftp=ftp->link;
					}
					scope--;

				}
    break;

  case 86:
#line 979 "ast.y"
    {	
					create_node((yyvsp[(1) - (2)].string), 3);
					printf("Line:%d: ", line);
					printf("\033[1;35m"); 
					printf("warning: ");
					printf("\033[0m");
					printf("type specifier missing, defaults to \'int\' \n");

					struct node *ftp;
					ftp = first;
					while(ftp!=NULL){
						if(ftp->scope == scope && ftp->valid == 1){
							ftp->valid = 0;
						}
						else if(strcmp(ftp->token, "param") == 0 && ftp->valid == 1){
							ftp->valid = 0;
						}

						ftp=ftp->link;
					}
					scope--;
				}
    break;

  case 89:
#line 1012 "ast.y"
    {	
					// printf("OKAY : %s\n", $1->name);
					// create_node($1->name, 1);
					addfunc((yyvsp[(1) - (1)].ptr), datatype, "function");	
					strcpy((yyval.string), (yyvsp[(1) - (1)].ptr)->name); 								
				}
    break;

  case 90:
#line 1018 "ast.y"
    { }
    break;

  case 91:
#line 1019 "ast.y"
    { }
    break;

  case 92:
#line 1020 "ast.y"
    { }
    break;

  case 93:
#line 1025 "ast.y"
    {}
    break;

  case 94:
#line 1026 "ast.y"
    {}
    break;

  case 95:
#line 1031 "ast.y"
    {	addfunc((yyvsp[(2) - (2)].ptr), datatype, "param");	}
    break;

  case 96:
#line 1032 "ast.y"
    {}
    break;

  case 97:
#line 1037 "ast.y"
    {		}
    break;

  case 98:
#line 1038 "ast.y"
    {		}
    break;


/* Line 1267 of yacc.c.  */
#line 2646 "y.tab.c"
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
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  if (yyn == YYFINAL)
    YYACCEPT;

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
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


#line 1042 "ast.y"



void yyerror(const char *str){
	fflush(stdout);
	printf("Line:%d: ", line);
	printf("\033[1;31m");
	printf("error: ");
	printf("\033[0m");
	printf("%s\n", str);
}


int main(){
	yyout = fopen("output.c", "w");


	tree_top = (tree_stack*)malloc(sizeof(tree_stack));
	tree_top->node = NULL;
	tree_top->next = NULL;
	struct Node *root;

	printf("\n");
	yyparse();

	root = pop_tree();
	get_levels(root, 1);

	printtree(root);
	

	preorder(root);
	printf("\n\nPreorder Traversal\n\n");
	printf("%s\n", preBuf);

	fclose(yyout);
	return 0;
}


void addfunc(struct node *t,int type, char *s){
	if(t->dtype == -1) {
        t->dtype = type;
        t->val.i = 0;
        strcpy(t->token, s);
    }
}


void addInt(struct node *t,int type,int val) {
    if(t->dtype == -1) {
        t->dtype = type;
        t->val.i = val;
        strcpy(t->token, "identifier");
    }
}


void addFloat(struct node *t,int type,float val) {
    if(t->dtype == -1) {
        t->dtype = type;
        t->val.f = (float)val;
        strcpy(t->token, "identifier");
    }
}


void addChar(struct node *t,int type, char val) {
   	if(t->dtype == -1) {
   	    t->dtype = type;
   	    t->val.c = (char)val;
   	    strcpy(t->token, "identifier");
   	}
}


struct node * addtosymbol(struct node * n){
	if(first == NULL){
		first = n;
	}
	else{
		struct  node * ftp = first;
		while(ftp->link !=NULL) {
			ftp = ftp->link;
		}
		ftp->link = n;
	}
	return n;
}


struct node * checksym(char *vname) {
	struct node *ftp;
	struct node *rp;
	struct node *nnode;
	struct node *same;
	
	if(first == NULL) {
		nnode = (struct node *)malloc(sizeof(struct node));
		addsymbol(nnode,vname);
	    first = nnode;
	}
	else {
	    ftp = first;
	    while(ftp!=NULL) {

	        if(strcmp(vname,ftp->name) == 0){
	            if(ftp->scope > scope && ftp->valid == 1) {	          	
					same = ftp; 
	            	return same;
	            }	
	            else if(ftp->scope == scope && ftp->valid == 1){
	            	same = ftp;
	            	return same;
	            }          	
	            else if(ftp->scope < scope && ftp->valid == 1){
	         		check_un = 1;	//no error 

	         		same = ftp;
	            	return same;
	         			            		         				         		       	         
	            } 
	          	else if(ftp->scope > scope && ftp->valid == 0){
	          		check_un = 0;	//undeclared
	          	}

	        }            
	        rp = ftp;
	        ftp = ftp->link;
	    }
	    nnode = (struct node *)malloc(sizeof(struct node));
		addsymbol(nnode,vname);

	    rp->link = nnode;
	}
	return nnode;
}


void addsymbol(struct node *tp, char *vname) {
    strcpy(tp->name,vname);
    tp->dtype = -1;
    tp->link = NULL;
    tp->scope = scope;
    tp->valid = 1;
    tp->lineno = line;
}


void cleansymbol(){
	struct node** pp = &first; 
    while (*pp) { 
  
        struct node* entry = *pp; 
 
        if (entry->dtype == -1  ) { 
            *pp = entry->link; 
            free(entry); 
        }
        else if(strcmp(entry->name,"main")== 0 && strcmp(entry->token, "function")==0){	//remove main entry from symbol table
        	*pp = entry->link; 
            free(entry); 
        }
        // Else move to next 
        else
            pp = &(entry->link); 
    } 
}


void printsymtable(){
	struct node *ftp;
    ftp=first;
    //blue
    printf("\n\nSymbol Table\n\n");
    //white

	printf("   Symbol\t\tName\t  Type\t      Scope\t   Line Number\t       Value \n");
   
    while(ftp!=NULL) {
        char data_type[10];
        if(ftp->dtype==0)
        	strcpy(data_type,"int");
        if(ftp->dtype==1)
        	strcpy(data_type,"float");
        if(ftp->dtype==2)
        	strcpy(data_type,"char");
        if(ftp->dtype==3)
        	strcpy(data_type,"void");

        printf("%11s\t%12s\t%6s\t\t%d\t\t%d\t\t",ftp->token, ftp->name, data_type, ftp->scope, ftp->lineno);

        if(ftp->dtype == 0){
        	if(ftp->val.i == INT_MIN)
        		printf("-\n");
        	else
           		printf("%d\n",ftp->val.i);
        }
        else if(ftp->dtype == 1){
        	if(ftp->val.f == INT_MIN)
        		printf("-\n");
        	else
           		printf("%f\n",ftp->val.f);
       	}
        else if(ftp->dtype == 2){
            printf("%c\n",ftp->val.c);
        }
        else if(strcmp(ftp->token, "function")==0){
        	printf("-\n");
        }
        else{
	        printf("-	Delete it\n");
	    }
        ftp=ftp->link;
    }
    printf("\n\n\n");
}


void create_node(char *token, int leaf) {
	Node *l;
	Node *r;
	if(leaf==0) {

		r = pop_tree();
		l = pop_tree();
	}
	else if(leaf ==1) {
		l = NULL;
		r = NULL;
	}
	else {
		l = pop_tree();
		r = NULL;
	}

	Node *newnode = (Node*)malloc(sizeof(Node));
	strcpy(newnode->token, token);
	newnode->left = l;
	newnode->right = r;
	push_tree(newnode);
}


void push_tree(Node *newnode){
	tree_stack *temp= (tree_stack*)malloc(sizeof(tree_stack));
	temp->node = newnode;
	temp->next = tree_top;
	tree_top = temp;
}


Node* pop_tree(){
	tree_stack *temp = tree_top;
	tree_top = tree_top->next;
	Node *retnode = temp->node;
	if(temp != NULL)
		free(temp);
	return retnode;
}


void printtree(Node* root){
/*
    int h = getmaxlevel(root)-1;
    int i;
	
	printf("\n\nAbstract Syntax Tree\n\n");

	
    for (i=1; i<=h; i++){
		printf("\t");
		for(int j=0;j<=h+1-i;j++){
			printf("      ");
		}
        printGivenLevel(root, i,h);

        printf("\n\n\n");
    }
*/
}


int getmaxlevel(Node *root){
	int count=0;
	Node *temp= root;
	while(temp->left!=NULL){
		count++;
		temp=temp->left;
	}
	return count*2;
}


void printGivenLevel(Node* root, int level, int h){
    if (root == NULL)
        return;
    if (level == 1){
		for(int j=0; j<=h-1-level; j++){
			printf(" ");
		}
	    printf("%s ", root->token);
	}
    else if (level > 1){
        printGivenLevel(root->left, level-1,h);
		for(int j=0; j<=h-1-level; j++){
			printf(" ");
		}
        printGivenLevel(root->right, level-1,h);
    }
}


void preorder(Node * node){
	if (node == NULL)
		return;

	if(node->left!=NULL && node->right!=NULL)
		strcat(preBuf, "   ( ");
	strcat(preBuf, node->token);
	strcat(preBuf, "   ");

	preorder(node-> left);

	
	if(node->right){
		preorder(node-> right);
	}
	
	if(node->left!=NULL && node->right!=NULL)
		strcat(preBuf, ")   ");
	// printf("\n");
	
}

void get_levels(Node *root, int level){
	root->level = level;
	if(root->left == NULL && root->right == NULL){
		return;
	}
	if(root->left == NULL){
		get_levels(root->right, level+1);
	}
	else if(root->right == NULL){
		get_levels(root->left, level+1);
	}
	else{
		get_levels(root->left, level+1);
		get_levels(root->right, level+1);
	}
}

