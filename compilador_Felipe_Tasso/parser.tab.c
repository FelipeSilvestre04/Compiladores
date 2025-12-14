/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2006, 2009-2010 Free Software
   Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.2"

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
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex();
void yyerror(const char *s);
extern int yylineno;
extern char* yytext;
extern FILE *yyin;

typedef enum {
    NODE_PROGRAMA,
    NODE_VAR_DECLARACAO,
    NODE_VAR_DECLARACAO_ARRAY,
    NODE_TIPO_INT,
    NODE_TIPO_VOID,
    NODE_FUN_DECLARACAO,
    NODE_PARAM,
    NODE_PARAM_ARRAY,
    NODE_COMPOSTO_DECL,
    NODE_SELECAO_DECL,
    NODE_ITERACAO_DECL,
    NODE_RETORNO_DECL,
    NODE_EXPRESSAO_REC,
    NODE_VAR_ARRAY,
    NODE_RELACIONAL,
    NODE_REL_LEQUAL,
    NODE_REL_MENOR,
    NODE_REL_HIGHER,
    NODE_REL_HEQUAL,
    NODE_REL_IGL,
    NODE_REL_DIF,
    NODE_SOMA,
    NODE_SUB,
    NODE_MULT,
    NODE_DIV,
    NODE_ATIVACAO,
    NODE_ID,
    NODE_NUM
} NodeType;

typedef struct Node {
    NodeType type;
    int ival;
    char* sval;
    struct Node* child1;
    struct Node* child2;
    struct Node* child3;
    struct Node* sibling;
    int lineno;
} Node;

Node* create_node(NodeType type, Node* c1, Node* c2, Node* c3);
Node* create_leaf_val(NodeType type, int ival);
Node* create_leaf_id(NodeType type, char* sval);
void print_tree(Node* node, int indent);
void semantic_analysis(Node* root);

Node* ast_root = NULL;
int syntax_error_count = 0;  // Contador de erros sintaticos



/* Line 189 of yacc.c  */
#line 137 "parser.tab.c"

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
     NUM = 258,
     ID = 259,
     IF = 260,
     ELSE = 261,
     INT = 262,
     RET = 263,
     VOI = 264,
     WHI = 265,
     SOM = 266,
     SUB = 267,
     MUL = 268,
     DIV = 269,
     MENOR = 270,
     LEQUAL = 271,
     HIGHER = 272,
     HEQUAL = 273,
     IGL = 274,
     DIF = 275,
     REC = 276,
     PEV = 277,
     VIR = 278,
     APR = 279,
     FPR = 280,
     ACO = 281,
     FCO = 282,
     ACH = 283,
     FCH = 284,
     LOWER_THAN_ELSE = 285
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 65 "parser.y"

    int ival;
    char* sval; 
    struct Node* nptr;



/* Line 214 of yacc.c  */
#line 211 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 223 "parser.tab.c"

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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   112

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  65
/* YYNRULES -- Number of states.  */
#define YYNSTATES  106

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       0,     0,     3,     5,     8,    10,    12,    14,    17,    21,
      28,    30,    32,    39,    41,    43,    47,    49,    52,    57,
      62,    65,    66,    69,    70,    72,    74,    76,    78,    80,
      83,    86,    88,    94,   102,   108,   111,   115,   119,   121,
     123,   128,   132,   134,   136,   138,   140,   142,   144,   146,
     150,   152,   154,   156,   160,   162,   164,   166,   170,   172,
     174,   176,   181,   183,   184,   188
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      32,     0,    -1,    33,    -1,    33,    34,    -1,    34,    -1,
      35,    -1,    37,    -1,     1,    22,    -1,    36,     4,    22,
      -1,    36,     4,    26,     3,    27,    22,    -1,     7,    -1,
       9,    -1,    36,     4,    24,    38,    25,    41,    -1,    39,
      -1,     9,    -1,    39,    23,    40,    -1,    40,    -1,    36,
       4,    -1,    36,     4,    26,    27,    -1,    28,    42,    43,
      29,    -1,    42,    35,    -1,    -1,    43,    44,    -1,    -1,
      45,    -1,    41,    -1,    46,    -1,    47,    -1,    48,    -1,
       1,    22,    -1,    49,    22,    -1,    22,    -1,     5,    24,
      49,    25,    44,    -1,     5,    24,    49,    25,    44,     6,
      44,    -1,    10,    24,    49,    25,    44,    -1,     8,    22,
      -1,     8,    49,    22,    -1,    50,    21,    49,    -1,    51,
      -1,     4,    -1,     4,    26,    49,    27,    -1,    53,    52,
      53,    -1,    53,    -1,    16,    -1,    15,    -1,    17,    -1,
      18,    -1,    19,    -1,    20,    -1,    53,    54,    55,    -1,
      55,    -1,    11,    -1,    12,    -1,    55,    56,    57,    -1,
      57,    -1,    13,    -1,    14,    -1,    24,    49,    25,    -1,
      50,    -1,    58,    -1,     3,    -1,     4,    24,    59,    25,
      -1,    60,    -1,    -1,    60,    23,    49,    -1,    49,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   101,   101,   108,   118,   122,   123,   124,   128,   131,
     137,   138,   142,   150,   151,   155,   161,   165,   168,   174,
     180,   190,   194,   204,   208,   209,   210,   211,   212,   213,
     217,   218,   222,   225,   231,   237,   240,   246,   249,   253,
     254,   260,   263,   267,   268,   269,   270,   271,   272,   276,
     279,   283,   284,   288,   291,   295,   296,   300,   301,   302,
     303,   307,   313,   314,   318,   324
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUM", "ID", "IF", "ELSE", "INT", "RET",
  "VOI", "WHI", "SOM", "SUB", "MUL", "DIV", "MENOR", "LEQUAL", "HIGHER",
  "HEQUAL", "IGL", "DIF", "REC", "PEV", "VIR", "APR", "FPR", "ACO", "FCO",
  "ACH", "FCH", "LOWER_THAN_ELSE", "$accept", "programa",
  "declaracao_lista", "declaracao", "var_declaracao", "tipo_especificador",
  "fun_declaracao", "params", "param_lista", "param", "composto_decl",
  "local_declaracoes", "statement_lista", "statement", "expressao_decl",
  "selecao_decl", "iteracao_decl", "retorno_decl", "expressao", "var",
  "simples_expressao", "relacional", "soma_expressao", "soma", "termo",
  "mult", "fator", "ativacao", "args", "arg_lista", 0
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
     285
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    34,    35,    35,
      36,    36,    37,    38,    38,    39,    39,    40,    40,    41,
      42,    42,    43,    43,    44,    44,    44,    44,    44,    44,
      45,    45,    46,    46,    47,    48,    48,    49,    49,    50,
      50,    51,    51,    52,    52,    52,    52,    52,    52,    53,
      53,    54,    54,    55,    55,    56,    56,    57,    57,    57,
      57,    58,    59,    59,    60,    60
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     2,     3,     6,
       1,     1,     6,     1,     1,     3,     1,     2,     4,     4,
       2,     0,     2,     0,     1,     1,     1,     1,     1,     2,
       2,     1,     5,     7,     5,     2,     3,     3,     1,     1,
       4,     3,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     3,     1,     1,     1,     3,     1,     1,
       1,     4,     1,     0,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    10,    11,     0,     0,     4,     5,     0,     6,
       7,     1,     3,     0,     8,     0,     0,    11,     0,     0,
      13,    16,     0,    17,     0,     0,     0,     0,    21,    12,
      15,     9,    18,    23,    20,     0,     0,     0,     0,    60,
      39,     0,     0,     0,    31,     0,    19,    25,    22,    24,
      26,    27,    28,     0,    58,    38,    42,    50,    54,    59,
      29,    63,     0,     0,    35,     0,     0,     0,    30,     0,
      51,    52,    44,    43,    45,    46,    47,    48,     0,     0,
      55,    56,     0,    65,     0,    62,     0,     0,    36,     0,
      57,    37,    58,    41,    49,    53,    61,     0,    40,     0,
       0,    64,    32,    34,     0,    33
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,     9,    19,    20,    21,
      47,    33,    36,    48,    49,    50,    51,    52,    53,    54,
      55,    78,    56,    79,    57,    82,    58,    59,    84,    85
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -88
static const yytype_int8 yypact[] =
{
      40,   -21,   -88,   -88,    18,    44,   -88,   -88,    55,   -88,
     -88,   -88,   -88,    46,   -88,    39,    19,    41,    76,    56,
      20,   -88,    57,    59,    43,    60,    61,    63,   -88,   -88,
     -88,   -88,   -88,    60,   -88,    78,     1,   -12,    64,   -88,
      13,    65,     4,    68,   -88,    12,   -88,   -88,   -88,   -88,
     -88,   -88,   -88,    66,    70,   -88,    45,    62,   -88,   -88,
     -88,    12,    12,    12,   -88,    71,    12,    69,   -88,    12,
     -88,   -88,   -88,   -88,   -88,   -88,   -88,   -88,    12,    12,
     -88,   -88,    12,   -88,    72,    73,    74,    75,   -88,    77,
     -88,   -88,   -88,    67,    62,   -88,   -88,    12,   -88,    30,
      30,   -88,    81,   -88,    30,   -88
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -88,   -88,   -88,    90,    79,    17,   -88,   -88,   -88,    80,
      82,   -88,   -88,   -87,   -88,   -88,   -88,   -88,   -42,    -5,
     -88,   -88,    21,   -88,    24,   -88,    16,   -88,   -88,   -88
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -15
static const yytype_int8 yytable[] =
{
      65,    10,    38,    67,    39,    40,    41,    39,    40,    42,
      14,    43,   102,   103,    16,    39,    40,   105,    11,    83,
      86,    87,    22,    44,    89,    45,    64,    91,    45,    28,
      46,    38,    18,    39,    40,    41,    45,    61,    42,    62,
      43,     1,    18,    25,    -2,     1,     2,     2,    17,     3,
      35,     2,    44,     3,    45,   101,    70,    71,    28,    13,
      72,    73,    74,    75,    76,    77,   -14,     2,    14,     3,
      15,    28,    16,    92,    92,    80,    81,    92,    70,    71,
      23,    24,    37,    31,    26,    27,    60,   104,    68,    63,
      32,    69,    66,    88,    90,    12,    97,    96,    95,    93,
      99,    98,   100,    94,     0,    30,    29,     0,     0,     0,
       0,     0,    34
};

static const yytype_int8 yycheck[] =
{
      42,    22,     1,    45,     3,     4,     5,     3,     4,     8,
      22,    10,    99,   100,    26,     3,     4,   104,     0,    61,
      62,    63,     3,    22,    66,    24,    22,    69,    24,    28,
      29,     1,    15,     3,     4,     5,    24,    24,     8,    26,
      10,     1,    25,    23,     0,     1,     7,     7,     9,     9,
      33,     7,    22,     9,    24,    97,    11,    12,    28,     4,
      15,    16,    17,    18,    19,    20,    25,     7,    22,     9,
      24,    28,    26,    78,    79,    13,    14,    82,    11,    12,
       4,    25,     4,    22,    27,    26,    22,     6,    22,    24,
      27,    21,    24,    22,    25,     5,    23,    25,    82,    78,
      25,    27,    25,    79,    -1,    25,    24,    -1,    -1,    -1,
      -1,    -1,    33
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     7,     9,    32,    33,    34,    35,    36,    37,
      22,     0,    34,     4,    22,    24,    26,     9,    36,    38,
      39,    40,     3,     4,    25,    23,    27,    26,    28,    41,
      40,    22,    27,    42,    35,    36,    43,     4,     1,     3,
       4,     5,     8,    10,    22,    24,    29,    41,    44,    45,
      46,    47,    48,    49,    50,    51,    53,    55,    57,    58,
      22,    24,    26,    24,    22,    49,    24,    49,    22,    21,
      11,    12,    15,    16,    17,    18,    19,    20,    52,    54,
      13,    14,    56,    49,    59,    60,    49,    49,    22,    49,
      25,    49,    50,    53,    55,    57,    25,    23,    27,    25,
      25,    49,    44,    44,     6,    44
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
        case 2:

/* Line 1464 of yacc.c  */
#line 101 "parser.y"
    { 
        (yyval.nptr) = create_node(NODE_PROGRAMA, (yyvsp[(1) - (1)].nptr), NULL, NULL); 
        ast_root = (yyval.nptr);
    ;}
    break;

  case 3:

/* Line 1464 of yacc.c  */
#line 108 "parser.y"
    {
        Node* head = (yyvsp[(1) - (2)].nptr);
        if (head) {
            while (head->sibling) head = head->sibling;
            head->sibling = (yyvsp[(2) - (2)].nptr);
            (yyval.nptr) = (yyvsp[(1) - (2)].nptr);
        } else {
            (yyval.nptr) = (yyvsp[(2) - (2)].nptr);
        }
    ;}
    break;

  case 4:

/* Line 1464 of yacc.c  */
#line 118 "parser.y"
    { (yyval.nptr) = (yyvsp[(1) - (1)].nptr); ;}
    break;

  case 5:

/* Line 1464 of yacc.c  */
#line 122 "parser.y"
    { (yyval.nptr) = (yyvsp[(1) - (1)].nptr); ;}
    break;

  case 6:

/* Line 1464 of yacc.c  */
#line 123 "parser.y"
    { (yyval.nptr) = (yyvsp[(1) - (1)].nptr); ;}
    break;

  case 7:

/* Line 1464 of yacc.c  */
#line 124 "parser.y"
    { yyerrok; (yyval.nptr) = NULL; ;}
    break;

  case 8:

/* Line 1464 of yacc.c  */
#line 128 "parser.y"
    { 
        (yyval.nptr) = create_node(NODE_VAR_DECLARACAO, (yyvsp[(1) - (3)].nptr), create_leaf_id(NODE_ID, (yyvsp[(2) - (3)].sval)), NULL); 
    ;}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 131 "parser.y"
    { 
        (yyval.nptr) = create_node(NODE_VAR_DECLARACAO_ARRAY, (yyvsp[(1) - (6)].nptr), create_leaf_id(NODE_ID, (yyvsp[(2) - (6)].sval)), create_leaf_val(NODE_NUM, (yyvsp[(4) - (6)].ival))); 
    ;}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 137 "parser.y"
    { (yyval.nptr) = create_node(NODE_TIPO_INT, NULL, NULL, NULL); ;}
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 138 "parser.y"
    { (yyval.nptr) = create_node(NODE_TIPO_VOID, NULL, NULL, NULL); ;}
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 142 "parser.y"
    {
        Node* id_node = create_leaf_id(NODE_ID, (yyvsp[(2) - (6)].sval));
        id_node->child1 = (yyvsp[(4) - (6)].nptr);
        (yyval.nptr) = create_node(NODE_FUN_DECLARACAO, (yyvsp[(1) - (6)].nptr), id_node, (yyvsp[(6) - (6)].nptr));
    ;}
    break;

  case 13:

/* Line 1464 of yacc.c  */
#line 150 "parser.y"
    { (yyval.nptr) = (yyvsp[(1) - (1)].nptr); ;}
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 151 "parser.y"
    { (yyval.nptr) = create_node(NODE_TIPO_VOID, NULL, NULL, NULL); ;}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 155 "parser.y"
    {
        Node* head = (yyvsp[(1) - (3)].nptr);
        while (head->sibling) head = head->sibling;
        head->sibling = (yyvsp[(3) - (3)].nptr);
        (yyval.nptr) = (yyvsp[(1) - (3)].nptr);
    ;}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 161 "parser.y"
    { (yyval.nptr) = (yyvsp[(1) - (1)].nptr); ;}
    break;

  case 17:

/* Line 1464 of yacc.c  */
#line 165 "parser.y"
    { 
        (yyval.nptr) = create_node(NODE_PARAM, (yyvsp[(1) - (2)].nptr), create_leaf_id(NODE_ID, (yyvsp[(2) - (2)].sval)), NULL); 
    ;}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 168 "parser.y"
    { 
        (yyval.nptr) = create_node(NODE_PARAM_ARRAY, (yyvsp[(1) - (4)].nptr), create_leaf_id(NODE_ID, (yyvsp[(2) - (4)].sval)), NULL); 
    ;}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 174 "parser.y"
    { 
        (yyval.nptr) = create_node(NODE_COMPOSTO_DECL, (yyvsp[(2) - (4)].nptr), (yyvsp[(3) - (4)].nptr), NULL); 
    ;}
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 180 "parser.y"
    {
        Node* head = (yyvsp[(1) - (2)].nptr);
        if (head) {
            while (head->sibling) head = head->sibling;
            head->sibling = (yyvsp[(2) - (2)].nptr);
            (yyval.nptr) = (yyvsp[(1) - (2)].nptr);
        } else {
            (yyval.nptr) = (yyvsp[(2) - (2)].nptr);
        }
    ;}
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 190 "parser.y"
    { (yyval.nptr) = NULL; ;}
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 194 "parser.y"
    {
        Node* head = (yyvsp[(1) - (2)].nptr);
        if (head) {
            while (head->sibling) head = head->sibling;
            head->sibling = (yyvsp[(2) - (2)].nptr);
            (yyval.nptr) = (yyvsp[(1) - (2)].nptr);
        } else {
            (yyval.nptr) = (yyvsp[(2) - (2)].nptr);
        }
    ;}
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 204 "parser.y"
    { (yyval.nptr) = NULL; ;}
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 208 "parser.y"
    { (yyval.nptr) = (yyvsp[(1) - (1)].nptr); ;}
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 209 "parser.y"
    { (yyval.nptr) = (yyvsp[(1) - (1)].nptr); ;}
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 210 "parser.y"
    { (yyval.nptr) = (yyvsp[(1) - (1)].nptr); ;}
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 211 "parser.y"
    { (yyval.nptr) = (yyvsp[(1) - (1)].nptr); ;}
    break;

  case 28:

/* Line 1464 of yacc.c  */
#line 212 "parser.y"
    { (yyval.nptr) = (yyvsp[(1) - (1)].nptr); ;}
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 213 "parser.y"
    { yyerrok; (yyval.nptr) = NULL; ;}
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 217 "parser.y"
    { (yyval.nptr) = (yyvsp[(1) - (2)].nptr); ;}
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 218 "parser.y"
    { (yyval.nptr) = NULL; ;}
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 222 "parser.y"
    { 
        (yyval.nptr) = create_node(NODE_SELECAO_DECL, (yyvsp[(3) - (5)].nptr), (yyvsp[(5) - (5)].nptr), NULL); 
    ;}
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 225 "parser.y"
    { 
        (yyval.nptr) = create_node(NODE_SELECAO_DECL, (yyvsp[(3) - (7)].nptr), (yyvsp[(5) - (7)].nptr), (yyvsp[(7) - (7)].nptr)); 
    ;}
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 231 "parser.y"
    { 
        (yyval.nptr) = create_node(NODE_ITERACAO_DECL, (yyvsp[(3) - (5)].nptr), (yyvsp[(5) - (5)].nptr), NULL); 
    ;}
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 237 "parser.y"
    { 
        (yyval.nptr) = create_node(NODE_RETORNO_DECL, NULL, NULL, NULL); 
    ;}
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 240 "parser.y"
    { 
        (yyval.nptr) = create_node(NODE_RETORNO_DECL, (yyvsp[(2) - (3)].nptr), NULL, NULL); 
    ;}
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 246 "parser.y"
    { 
        (yyval.nptr) = create_node(NODE_EXPRESSAO_REC, (yyvsp[(1) - (3)].nptr), (yyvsp[(3) - (3)].nptr), NULL); 
    ;}
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 249 "parser.y"
    { (yyval.nptr) = (yyvsp[(1) - (1)].nptr); ;}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 253 "parser.y"
    { (yyval.nptr) = create_leaf_id(NODE_ID, (yyvsp[(1) - (1)].sval)); ;}
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 254 "parser.y"
    { 
        (yyval.nptr) = create_node(NODE_VAR_ARRAY, create_leaf_id(NODE_ID, (yyvsp[(1) - (4)].sval)), (yyvsp[(3) - (4)].nptr), NULL); 
    ;}
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 260 "parser.y"
    { 
        (yyval.nptr) = create_node(NODE_RELACIONAL, (yyvsp[(1) - (3)].nptr), (yyvsp[(3) - (3)].nptr), (yyvsp[(2) - (3)].nptr)); 
    ;}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 263 "parser.y"
    { (yyval.nptr) = (yyvsp[(1) - (1)].nptr); ;}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 267 "parser.y"
    { (yyval.nptr) = create_node(NODE_REL_LEQUAL, NULL, NULL, NULL); ;}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 268 "parser.y"
    { (yyval.nptr) = create_node(NODE_REL_MENOR, NULL, NULL, NULL); ;}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 269 "parser.y"
    { (yyval.nptr) = create_node(NODE_REL_HIGHER, NULL, NULL, NULL); ;}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 270 "parser.y"
    { (yyval.nptr) = create_node(NODE_REL_HEQUAL, NULL, NULL, NULL); ;}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 271 "parser.y"
    { (yyval.nptr) = create_node(NODE_REL_IGL, NULL, NULL, NULL); ;}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 272 "parser.y"
    { (yyval.nptr) = create_node(NODE_REL_DIF, NULL, NULL, NULL); ;}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 276 "parser.y"
    { 
        (yyval.nptr) = create_node((yyvsp[(2) - (3)].nptr)->type, (yyvsp[(1) - (3)].nptr), (yyvsp[(3) - (3)].nptr), NULL); 
    ;}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 279 "parser.y"
    { (yyval.nptr) = (yyvsp[(1) - (1)].nptr); ;}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 283 "parser.y"
    { (yyval.nptr) = create_node(NODE_SOMA, NULL, NULL, NULL); ;}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 284 "parser.y"
    { (yyval.nptr) = create_node(NODE_SUB, NULL, NULL, NULL); ;}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 288 "parser.y"
    { 
        (yyval.nptr) = create_node((yyvsp[(2) - (3)].nptr)->type, (yyvsp[(1) - (3)].nptr), (yyvsp[(3) - (3)].nptr), NULL); 
    ;}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 291 "parser.y"
    { (yyval.nptr) = (yyvsp[(1) - (1)].nptr); ;}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 295 "parser.y"
    { (yyval.nptr) = create_node(NODE_MULT, NULL, NULL, NULL); ;}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 296 "parser.y"
    { (yyval.nptr) = create_node(NODE_DIV, NULL, NULL, NULL); ;}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 300 "parser.y"
    { (yyval.nptr) = (yyvsp[(2) - (3)].nptr); ;}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 301 "parser.y"
    { (yyval.nptr) = (yyvsp[(1) - (1)].nptr); ;}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 302 "parser.y"
    { (yyval.nptr) = (yyvsp[(1) - (1)].nptr); ;}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 303 "parser.y"
    { (yyval.nptr) = create_leaf_val(NODE_NUM, (yyvsp[(1) - (1)].ival)); ;}
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 307 "parser.y"
    { 
        (yyval.nptr) = create_node(NODE_ATIVACAO, create_leaf_id(NODE_ID, (yyvsp[(1) - (4)].sval)), (yyvsp[(3) - (4)].nptr), NULL); 
    ;}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 313 "parser.y"
    { (yyval.nptr) = (yyvsp[(1) - (1)].nptr); ;}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 314 "parser.y"
    { (yyval.nptr) = NULL; ;}
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 318 "parser.y"
    {
        Node* head = (yyvsp[(1) - (3)].nptr);
        while (head->sibling) head = head->sibling;
        head->sibling = (yyvsp[(3) - (3)].nptr);
        (yyval.nptr) = (yyvsp[(1) - (3)].nptr);
    ;}
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 324 "parser.y"
    { (yyval.nptr) = (yyvsp[(1) - (1)].nptr); ;}
    break;



/* Line 1464 of yacc.c  */
#line 2045 "parser.tab.c"
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



/* Line 1684 of yacc.c  */
#line 326 "parser.y"


Node* create_node(NodeType type, Node* c1, Node* c2, Node* c3) {
    Node* n = (Node*) malloc(sizeof(Node));
    if (n == NULL) {
        yyerror("Erro: Sem memoria para criar no da arvore");
        exit(1);
    }
    n->type = type;
    n->ival = 0;
    n->sval = NULL;
    n->child1 = c1;
    n->child2 = c2;
    n->child3 = c3;
    n->sibling = NULL;
    n->lineno = yylineno;
    return n;
}

Node* create_leaf_val(NodeType type, int ival) {
    Node* n = create_node(type, NULL, NULL, NULL);
    n->ival = ival;
    return n;
}

Node* create_leaf_id(NodeType type, char* sval) {
    Node* n = create_node(type, NULL, NULL, NULL);
    n->sval = strdup(sval); 
    return n;
}

void print_tree(Node* node, int indent) {
    if (node == NULL) {
        return;
    }

    for(int i = 0; i < indent; i++) {
        printf("  ");
    }

    switch(node->type) {
        case NODE_PROGRAMA: printf("PROGRAMA\n"); break;
        case NODE_VAR_DECLARACAO: printf("VAR_DECLARACAO\n"); break;
        case NODE_VAR_DECLARACAO_ARRAY: printf("VAR_DECLARACAO_ARRAY\n"); break;
        case NODE_TIPO_INT: printf("TIPO: INT\n"); break;
        case NODE_TIPO_VOID: printf("TIPO: VOID\n"); break;
        case NODE_FUN_DECLARACAO: printf("FUN_DECLARACAO\n"); break;
        case NODE_PARAM: printf("PARAM\n"); break;
        case NODE_PARAM_ARRAY: printf("PARAM_ARRAY\n"); break;
        case NODE_COMPOSTO_DECL: printf("COMPOSTO_DECL\n"); break;
        case NODE_SELECAO_DECL: printf("SELECAO_DECL (IF)\n"); break;
        case NODE_ITERACAO_DECL: printf("ITERACAO_DECL (WHILE)\n"); break;
        case NODE_RETORNO_DECL: printf("RETORNO_DECL\n"); break;
        case NODE_EXPRESSAO_REC: printf("ATRIBUICAO (=)\n"); break;
        case NODE_VAR_ARRAY: printf("VAR_ARRAY (acesso)\n"); break;
        case NODE_RELACIONAL: printf("RELACIONAL\n"); break;
        case NODE_REL_LEQUAL: printf("RELACIONAL (<=)\n"); break;
        case NODE_REL_MENOR: printf("RELACIONAL (<)\n"); break;
        case NODE_REL_HIGHER: printf("RELACIONAL (>)\n"); break;
        case NODE_REL_HEQUAL: printf("RELACIONAL (>=)\n"); break;
        case NODE_REL_IGL: printf("RELACIONAL (==)\n"); break;
        case NODE_REL_DIF: printf("RELACIONAL (!=)\n"); break;
        case NODE_SOMA: printf("OPERADOR (+)\n"); break;
        case NODE_SUB: printf("OPERADOR (-)\n"); break;
        case NODE_MULT: printf("OPERADOR (*)\n"); break;
        case NODE_DIV: printf("OPERADOR (/)\n"); break;
        case NODE_ATIVACAO: printf("ATIVACAO (call)\n"); break;
        case NODE_ID: printf("ID (%s)\n", node->sval); break;
        case NODE_NUM: printf("NUM (%d)\n", node->ival); break;
        default: printf("ERRO: No desconhecido (%d)\n", node->type);
    }

    print_tree(node->child1, indent + 1);
    print_tree(node->child2, indent + 1);
    print_tree(node->child3, indent + 1);
    print_tree(node->sibling, indent);
}

int main(int argc, char *argv[]) {
    FILE *f_in;
    if (argc == 2) {
        if ( !(f_in = fopen(argv[1], "r")) ) {
            perror(argv[1]);
            return 1;
        }
        yyin = f_in;
    } else {
        printf("Uso: ./meu_parser <arquivo_de_entrada>\n");
        return 1;
    }

    printf("Iniciando analise sintatica de: %s\n", argv[1]);
    int parse_result = yyparse();
    
    if (parse_result == 0 && syntax_error_count == 0) { 
        printf("Analise Sintatica concluida com SUCESSO!\n");
        printf("\nImprimindo Arvore Sintatica Abstrata:\n");
        print_tree(ast_root, 0);
        
        printf("\nIniciando Analise Semantica...\n");
        semantic_analysis(ast_root);
    } else {
        printf("Analise Sintatica concluida com %d erro(s) sintatico(s).\n", syntax_error_count);
    }

    fclose(f_in);
    return 0;
}

void yyerror(const char *s) {
    syntax_error_count++;  // Incrementa contador
    printf("ERRO SINTATICO: %s LINHA: %d\n", yytext, yylineno);
}

typedef struct Symbol {
    char* name;
    char* type; 
    char* scope; 
    char* kind; 
    int lineno;
    struct Symbol* next;
    struct Symbol* params; 
} Symbol;

int function_has_return(Node* node) {
    if (node == NULL) return 0;
    
    if (node->type == NODE_RETORNO_DECL && node->child1 != NULL) {
        return 1;
    }
    
    if (function_has_return(node->child1)) return 1;
    if (function_has_return(node->child2)) return 1;
    if (function_has_return(node->child3)) return 1;
    if (function_has_return(node->sibling)) return 1;
    
    return 0;
}

Symbol* symbol_table = NULL;
int semantic_error_count = 0;  

void semantic_error(char* msg, char* id, int lineno) {
    semantic_error_count++;  
    if (id)
        printf("ERRO SEMANTICO: %s %s LINHA: %d\n", msg, id, lineno);
    else
        printf("ERRO SEMANTICO: %s LINHA: %d\n", msg, lineno);
}

Symbol* create_symbol(char* name, char* type, char* scope, char* kind, int lineno) {
    Symbol* s = (Symbol*) malloc(sizeof(Symbol));
    s->name = strdup(name);
    s->type = strdup(type);
    s->scope = strdup(scope);
    s->kind = strdup(kind);
    s->lineno = lineno;
    s->next = NULL;
    s->params = NULL;
    return s;
}

void insert_symbol(char* name, char* type, char* scope, char* kind, int lineno) {
    Symbol* s = create_symbol(name, type, scope, kind, lineno);
    s->next = symbol_table;
    symbol_table = s;
}

Symbol* lookup_symbol(char* name, char* scope) {
    Symbol* s = symbol_table;
    while (s != NULL) {
        if (strcmp(s->name, name) == 0) {
            
            if (strcmp(s->scope, scope) == 0) {
                return s;
            }
        }
        s = s->next;
    }
    
    s = symbol_table;
    while (s != NULL) {
        if (strcmp(s->name, name) == 0) {
            if (strcmp(s->scope, "global") == 0) {
                return s;
            }
        }
        s = s->next;
    }
    return NULL;
}

Symbol* lookup_function(char* name) {
    Symbol* s = symbol_table;
    while (s != NULL) {
        if (strcmp(s->name, name) == 0 && strcmp(s->kind, "fun") == 0) {
            return s;
        }
        s = s->next;
    }
    return NULL;
}

int is_declared_in_scope(char* name, char* scope) {
    Symbol* s = symbol_table;
    while (s != NULL) {
        if (strcmp(s->name, name) == 0 && strcmp(s->scope, scope) == 0) {
            return 1;
        }
        s = s->next;
    }
    return 0;
}

void print_symbol_table() {
    printf("\nTABELA DE SIMBOLOS:\n");
    printf("%-20s %-10s %-10s %-10s %-10s\n", "Nome", "Tipo", "Escopo", "Categoria", "Linha");
    Symbol* s = symbol_table;
    while (s != NULL) {
        printf("%-20s %-10s %-10s %-10s %d\n", s->name, s->type, s->scope, s->kind, s->lineno);
        s = s->next;
    }
}

char* get_type_from_node(Node* node) {
    if (node->type == NODE_TIPO_INT) return "int";
    if (node->type == NODE_TIPO_VOID) return "void";
    return "unknown";
}

char* get_expression_type(Node* node, char* scope) {
    if (!node) return "void";
    
    switch(node->type) {
        case NODE_NUM: return "int";
        case NODE_ID: {
            Symbol* s = lookup_symbol(node->sval, scope);
            return s ? s->type : "unknown";
        }
        case NODE_VAR_ARRAY: {
             Symbol* s = lookup_symbol(node->child1->sval, scope);
             return s ? s->type : "unknown";
        }
        case NODE_ATIVACAO: {
            Symbol* s = lookup_function(node->child1->sval);
            return s ? s->type : "unknown";
        }
        case NODE_SOMA:
        case NODE_SUB:
        case NODE_MULT:
        case NODE_DIV:
            return "int";
        default:
            return "int"; 
    }
}

void analyze_node(Node* node, char* current_scope) {
    if (node == NULL) return;

    switch(node->type) {
        case NODE_PROGRAMA:
            analyze_node(node->child1, current_scope); 
            break;
            
        case NODE_VAR_DECLARACAO:
        case NODE_VAR_DECLARACAO_ARRAY: {
            char* type = get_type_from_node(node->child1);
            char* name = node->child2->sval;
            
            if (strcmp(type, "void") == 0) {
                semantic_error("declaração invalida de variavel", name, node->lineno);
            } 
            else if (is_declared_in_scope(name, current_scope)) {
                semantic_error("declaração invalida de variavel", name, node->lineno); 
            } 
            else if (lookup_function(name)) {
                 semantic_error("declaração invalida", name, node->lineno); 
            } else {
                insert_symbol(name, type, current_scope, (node->type == NODE_VAR_DECLARACAO_ARRAY) ? "array" : "var", node->lineno);
            }
            break;
        }
        
        case NODE_FUN_DECLARACAO: {
            char* type = get_type_from_node(node->child1);
            char* name = node->child2->sval;
            int fun_lineno = node->child1->lineno; 
            
            if (lookup_function(name)) {
                semantic_error("declaração invalida", name, fun_lineno);
            } else {
                insert_symbol(name, type, "global", "fun", fun_lineno);
                Symbol* fun_sym = symbol_table; 
                
                Node* params = node->child2->child1; 
                Node* param_list = params;
                
                if (param_list && param_list->type != NODE_TIPO_VOID) {
                    Node* p = param_list;
                    while (p) {
                        if (p->type == NODE_PARAM || p->type == NODE_PARAM_ARRAY) {
                            char* p_type = get_type_from_node(p->child1);
                            char* p_name = p->child2->sval;
                            
                            if (strcmp(p_type, "void") == 0) {
                                semantic_error("declaração invalida de variavel", p_name, p->lineno);
                            } else {
                                insert_symbol(p_name, p_type, name, "param", p->lineno);
                                
                                Symbol* param_sym = create_symbol(p_name, p_type, name, "param", p->lineno);
                                
                                if (fun_sym->params == NULL) {
                                    fun_sym->params = param_sym;
                                } else {
                                    Symbol* last = fun_sym->params;
                                    while (last->next) last = last->next;
                                    last->next = param_sym;
                                }
                            }
                        }
                        p = p->sibling;
                    }
                }
            }
            
            analyze_node(node->child3, name);
            
            if (strcmp(type, "int") == 0) {
                if (!function_has_return(node->child3)) {
                    semantic_error("função int sem retorno", name, node->lineno);
                }
            }
            break;
        }
        
        case NODE_COMPOSTO_DECL:
            analyze_node(node->child1, current_scope); 
            analyze_node(node->child2, current_scope); 
            break;
            
        case NODE_ATIVACAO: {
            char* func_name = node->child1->sval;
            Symbol* fun_sym = lookup_function(func_name);
            
            if (!fun_sym) {
                semantic_error("chamada de função não declarada", func_name, node->lineno);
            } else {
                Node* args = node->child2; 
                
                int arg_count = 0;
                Node* arg = args;
                while (arg) {
                    arg_count++;
                    arg = arg->sibling;
                }
                
                int param_count = 0;
                Symbol* p = fun_sym->params;
                while (p) {
                    param_count++;
                    p = p->next;
                }
                
                if (arg_count != param_count) {
                    semantic_error("chamada invalida", "número de parâmetros invalido", node->lineno);
                } else {
                    arg = args;
                    p = fun_sym->params;
                    while (arg && p) {
                        char* arg_type = get_expression_type(arg, current_scope);
                        if (strcmp(arg_type, p->type) != 0) {
                             if (strcmp(arg_type, "unknown") != 0 && strcmp(p->type, "unknown") != 0) {
                                semantic_error("chamada invalida", "tipo de parâmetro invalido", node->lineno);
                             }
                        }
                        arg = arg->sibling;
                        p = p->next;
                    }
                }
            }
            break;
        }
        
        case NODE_ID: {
            char* name = node->sval;
            Symbol* sym = lookup_symbol(name, current_scope);
            if (!sym) {
                semantic_error("variavel não declarada", name, node->lineno);
            }
            break;
        }
        
        case NODE_VAR_ARRAY: {
            char* name = node->child1->sval;
            Symbol* sym = lookup_symbol(name, current_scope);
            if (!sym) {
                semantic_error("variavel não declarada", name, node->lineno);
            }
            analyze_node(node->child2, current_scope); 
            break;
        }
        
        case NODE_EXPRESSAO_REC: {
            Node* var_node = node->child1;
            Node* expr_node = node->child2;
            
            analyze_node(var_node, current_scope);
            analyze_node(expr_node, current_scope);
            
            char* var_type = "unknown";
            char* var_kind = "var";
            
            if (var_node->type == NODE_ID) {
                Symbol* sym = lookup_symbol(var_node->sval, current_scope);
                if (sym) {
                    var_type = sym->type;
                    var_kind = sym->kind;
                }
                
                if (sym && strcmp(sym->kind, "array") == 0) {
                    semantic_error("atribuição invalida a array", var_node->sval, node->lineno);
                }
            } else if (var_node->type == NODE_VAR_ARRAY) {
                 Symbol* sym = lookup_symbol(var_node->child1->sval, current_scope);
                 if (sym) var_type = sym->type;
            }
            
            char* expr_type = get_expression_type(expr_node, current_scope);
            
            if (strcmp(var_type, "int") == 0 && strcmp(expr_type, "void") == 0) {
                 semantic_error("atribuição invalida", NULL, node->lineno);
            }
            break;
        }

        case NODE_RETORNO_DECL: {
            if (strcmp(current_scope, "global") != 0) {
                Symbol* fun_sym = lookup_function(current_scope);
                if (fun_sym) {
                    if (node->child1) { 
                        if (strcmp(fun_sym->type, "void") == 0) {
                            semantic_error("chamada invalida", "parâmetro de retorno da função não previsto", node->lineno);
                        } else {
                        }
                    } else {
                        if (strcmp(fun_sym->type, "int") == 0) {
                        }
                    }
                }
            }
            break;
        }
        
        default:
            analyze_node(node->child1, current_scope);
            analyze_node(node->child2, current_scope);
            analyze_node(node->child3, current_scope);
            break;
    }
    analyze_node(node->sibling, current_scope);
}

void semantic_analysis(Node* root) {
    insert_symbol("input", "int", "global", "fun", 0);
    
    insert_symbol("output", "void", "global", "fun", 0);
    Symbol* out_sym = lookup_function("output");
    Symbol* param = create_symbol("x", "int", "output", "param", 0);
    out_sym->params = param;
    
    analyze_node(root, "global");
    
    Symbol* main_sym = lookup_function("main");
    if (main_sym == NULL) {
        semantic_error("função main() não declarada", NULL, 0); 
    } else {
        if (strcmp(main_sym->type, "void") != 0) {
            semantic_error("função main deve ser do tipo void", "main", main_sym->lineno);
        }
        if (main_sym->params != NULL) {
            semantic_error("função main não deve ter parâmetros", "main", main_sym->lineno);
        }
    }
    
    print_symbol_table();
    
    if (semantic_error_count == 0) {
        printf("\nAnalise Semantica concluida com SUCESSO! Nenhum erro detectado.\n");
    } else {
        printf("\nAnalise Semantica concluida com %d erro(s).\n", semantic_error_count);
    }
}

