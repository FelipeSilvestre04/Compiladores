/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
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


#line 134 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUM = 3,                        /* NUM  */
  YYSYMBOL_ID = 4,                         /* ID  */
  YYSYMBOL_IF = 5,                         /* IF  */
  YYSYMBOL_ELSE = 6,                       /* ELSE  */
  YYSYMBOL_INT = 7,                        /* INT  */
  YYSYMBOL_RET = 8,                        /* RET  */
  YYSYMBOL_VOI = 9,                        /* VOI  */
  YYSYMBOL_WHI = 10,                       /* WHI  */
  YYSYMBOL_SOM = 11,                       /* SOM  */
  YYSYMBOL_SUB = 12,                       /* SUB  */
  YYSYMBOL_MUL = 13,                       /* MUL  */
  YYSYMBOL_DIV = 14,                       /* DIV  */
  YYSYMBOL_MENOR = 15,                     /* MENOR  */
  YYSYMBOL_LEQUAL = 16,                    /* LEQUAL  */
  YYSYMBOL_HIGHER = 17,                    /* HIGHER  */
  YYSYMBOL_HEQUAL = 18,                    /* HEQUAL  */
  YYSYMBOL_IGL = 19,                       /* IGL  */
  YYSYMBOL_DIF = 20,                       /* DIF  */
  YYSYMBOL_REC = 21,                       /* REC  */
  YYSYMBOL_PEV = 22,                       /* PEV  */
  YYSYMBOL_VIR = 23,                       /* VIR  */
  YYSYMBOL_APR = 24,                       /* APR  */
  YYSYMBOL_FPR = 25,                       /* FPR  */
  YYSYMBOL_ACO = 26,                       /* ACO  */
  YYSYMBOL_FCO = 27,                       /* FCO  */
  YYSYMBOL_ACH = 28,                       /* ACH  */
  YYSYMBOL_FCH = 29,                       /* FCH  */
  YYSYMBOL_LOWER_THAN_ELSE = 30,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 31,                  /* $accept  */
  YYSYMBOL_programa = 32,                  /* programa  */
  YYSYMBOL_declaracao_lista = 33,          /* declaracao_lista  */
  YYSYMBOL_declaracao = 34,                /* declaracao  */
  YYSYMBOL_var_declaracao = 35,            /* var_declaracao  */
  YYSYMBOL_tipo_especificador = 36,        /* tipo_especificador  */
  YYSYMBOL_fun_declaracao = 37,            /* fun_declaracao  */
  YYSYMBOL_params = 38,                    /* params  */
  YYSYMBOL_param_lista = 39,               /* param_lista  */
  YYSYMBOL_param = 40,                     /* param  */
  YYSYMBOL_composto_decl = 41,             /* composto_decl  */
  YYSYMBOL_local_declaracoes = 42,         /* local_declaracoes  */
  YYSYMBOL_statement_lista = 43,           /* statement_lista  */
  YYSYMBOL_statement = 44,                 /* statement  */
  YYSYMBOL_expressao_decl = 45,            /* expressao_decl  */
  YYSYMBOL_selecao_decl = 46,              /* selecao_decl  */
  YYSYMBOL_iteracao_decl = 47,             /* iteracao_decl  */
  YYSYMBOL_retorno_decl = 48,              /* retorno_decl  */
  YYSYMBOL_expressao = 49,                 /* expressao  */
  YYSYMBOL_var = 50,                       /* var  */
  YYSYMBOL_simples_expressao = 51,         /* simples_expressao  */
  YYSYMBOL_relacional = 52,                /* relacional  */
  YYSYMBOL_soma_expressao = 53,            /* soma_expressao  */
  YYSYMBOL_soma = 54,                      /* soma  */
  YYSYMBOL_termo = 55,                     /* termo  */
  YYSYMBOL_mult = 56,                      /* mult  */
  YYSYMBOL_fator = 57,                     /* fator  */
  YYSYMBOL_ativacao = 58,                  /* ativacao  */
  YYSYMBOL_args = 59,                      /* args  */
  YYSYMBOL_arg_lista = 60                  /* arg_lista  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   97

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  63
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  102

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   285


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   100,   100,   107,   117,   121,   122,   126,   129,   135,
     136,   140,   148,   149,   153,   159,   163,   166,   172,   178,
     188,   192,   202,   206,   207,   208,   209,   210,   214,   215,
     219,   222,   228,   234,   237,   243,   246,   250,   251,   257,
     260,   264,   265,   266,   267,   268,   269,   273,   276,   280,
     281,   285,   288,   292,   293,   297,   298,   299,   300,   304,
     310,   311,   315,   321
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NUM", "ID", "IF",
  "ELSE", "INT", "RET", "VOI", "WHI", "SOM", "SUB", "MUL", "DIV", "MENOR",
  "LEQUAL", "HIGHER", "HEQUAL", "IGL", "DIF", "REC", "PEV", "VIR", "APR",
  "FPR", "ACO", "FCO", "ACH", "FCH", "LOWER_THAN_ELSE", "$accept",
  "programa", "declaracao_lista", "declaracao", "var_declaracao",
  "tipo_especificador", "fun_declaracao", "params", "param_lista", "param",
  "composto_decl", "local_declaracoes", "statement_lista", "statement",
  "expressao_decl", "selecao_decl", "iteracao_decl", "retorno_decl",
  "expressao", "var", "simples_expressao", "relacional", "soma_expressao",
  "soma", "termo", "mult", "fator", "ativacao", "args", "arg_lista", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-92)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-14)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      50,   -92,   -92,    24,    50,   -92,   -92,    35,   -92,   -92,
     -92,   -12,   -92,    53,    45,    31,    64,    44,    47,   -92,
      46,    48,    43,    50,    54,    52,   -92,   -92,   -92,   -92,
     -92,    50,   -92,    68,     3,    -5,   -92,    37,    56,    12,
      57,   -92,    -2,   -92,   -92,   -92,   -92,   -92,   -92,   -92,
      60,    62,   -92,    26,    51,   -92,   -92,    -2,    -2,    -2,
     -92,    63,    -2,    59,   -92,    -2,   -92,   -92,   -92,   -92,
     -92,   -92,   -92,   -92,    -2,    -2,   -92,   -92,    -2,   -92,
      61,    65,    66,    67,   -92,    69,   -92,   -92,   -92,    55,
      51,   -92,   -92,    -2,   -92,    25,    25,   -92,    71,   -92,
      25,   -92
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     9,    10,     0,     2,     4,     5,     0,     6,     1,
       3,     0,     7,     0,     0,    10,     0,     0,    12,    15,
       0,    16,     0,     0,     0,     0,    20,    11,    14,     8,
      17,    22,    19,     0,     0,     0,    58,    37,     0,     0,
       0,    29,     0,    18,    24,    21,    23,    25,    26,    27,
       0,    56,    36,    40,    48,    52,    57,    61,     0,     0,
      33,     0,     0,     0,    28,     0,    49,    50,    42,    41,
      43,    44,    45,    46,     0,     0,    53,    54,     0,    63,
       0,    60,     0,     0,    34,     0,    55,    35,    56,    39,
      47,    51,    59,     0,    38,     0,     0,    62,    30,    32,
       0,    31
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -92,   -92,   -92,    74,    58,    27,   -92,   -92,   -92,    72,
      75,   -92,   -92,   -91,   -92,   -92,   -92,   -92,   -39,   -23,
     -92,   -92,     1,   -92,    15,   -92,     9,   -92,   -92,   -92
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     5,     6,     7,     8,    17,    18,    19,
      44,    31,    34,    45,    46,    47,    48,    49,    50,    51,
      52,    74,    53,    75,    54,    78,    55,    56,    80,    81
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      61,    36,    37,    63,    98,    99,    36,    37,    38,   101,
      12,    39,    13,    40,    14,    36,    37,    12,    79,    82,
      83,    14,    42,    85,     9,    41,    87,    42,    36,    37,
      38,    26,    43,    39,    60,    40,    42,    66,    67,    11,
      16,    68,    69,    70,    71,    72,    73,    41,    20,    42,
      16,    88,    88,    26,    97,    88,   -13,     1,    33,     2,
       1,    57,    15,    58,    76,    77,    66,    67,    21,    22,
      23,    26,    35,    24,    25,    89,    29,   100,    10,    30,
      59,    62,    64,    65,    86,    84,    92,    91,    93,    32,
      90,     0,    95,    94,    96,    28,     0,    27
};

static const yytype_int8 yycheck[] =
{
      39,     3,     4,    42,    95,    96,     3,     4,     5,   100,
      22,     8,    24,    10,    26,     3,     4,    22,    57,    58,
      59,    26,    24,    62,     0,    22,    65,    24,     3,     4,
       5,    28,    29,     8,    22,    10,    24,    11,    12,     4,
      13,    15,    16,    17,    18,    19,    20,    22,     3,    24,
      23,    74,    75,    28,    93,    78,    25,     7,    31,     9,
       7,    24,     9,    26,    13,    14,    11,    12,     4,    25,
      23,    28,     4,    27,    26,    74,    22,     6,     4,    27,
      24,    24,    22,    21,    25,    22,    25,    78,    23,    31,
      75,    -1,    25,    27,    25,    23,    -1,    22
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,     9,    32,    33,    34,    35,    36,    37,     0,
      34,     4,    22,    24,    26,     9,    36,    38,    39,    40,
       3,     4,    25,    23,    27,    26,    28,    41,    40,    22,
      27,    42,    35,    36,    43,     4,     3,     4,     5,     8,
      10,    22,    24,    29,    41,    44,    45,    46,    47,    48,
      49,    50,    51,    53,    55,    57,    58,    24,    26,    24,
      22,    49,    24,    49,    22,    21,    11,    12,    15,    16,
      17,    18,    19,    20,    52,    54,    13,    14,    56,    49,
      59,    60,    49,    49,    22,    49,    25,    49,    50,    53,
      55,    57,    25,    23,    27,    25,    25,    49,    44,    44,
       6,    44
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    35,    35,    36,
      36,    37,    38,    38,    39,    39,    40,    40,    41,    42,
      42,    43,    43,    44,    44,    44,    44,    44,    45,    45,
      46,    46,    47,    48,    48,    49,    49,    50,    50,    51,
      51,    52,    52,    52,    52,    52,    52,    53,    53,    54,
      54,    55,    55,    56,    56,    57,    57,    57,    57,    58,
      59,    59,    60,    60
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     6,     1,
       1,     6,     1,     1,     3,     1,     2,     4,     4,     2,
       0,     2,     0,     1,     1,     1,     1,     1,     2,     1,
       5,     7,     5,     2,     3,     3,     1,     1,     4,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     1,     1,     3,     1,     1,     1,     4,
       1,     0,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 2: /* programa: declaracao_lista  */
#line 100 "parser.y"
                     { 
        (yyval.nptr) = create_node(NODE_PROGRAMA, (yyvsp[0].nptr), NULL, NULL); 
        ast_root = (yyval.nptr);
    }
#line 1251 "parser.tab.c"
    break;

  case 3: /* declaracao_lista: declaracao_lista declaracao  */
#line 107 "parser.y"
                                {
        Node* head = (yyvsp[-1].nptr);
        if (head) {
            while (head->sibling) head = head->sibling;
            head->sibling = (yyvsp[0].nptr);
            (yyval.nptr) = (yyvsp[-1].nptr);
        } else {
            (yyval.nptr) = (yyvsp[0].nptr);
        }
    }
#line 1266 "parser.tab.c"
    break;

  case 4: /* declaracao_lista: declaracao  */
#line 117 "parser.y"
                 { (yyval.nptr) = (yyvsp[0].nptr); }
#line 1272 "parser.tab.c"
    break;

  case 5: /* declaracao: var_declaracao  */
#line 121 "parser.y"
                   { (yyval.nptr) = (yyvsp[0].nptr); }
#line 1278 "parser.tab.c"
    break;

  case 6: /* declaracao: fun_declaracao  */
#line 122 "parser.y"
                     { (yyval.nptr) = (yyvsp[0].nptr); }
#line 1284 "parser.tab.c"
    break;

  case 7: /* var_declaracao: tipo_especificador ID PEV  */
#line 126 "parser.y"
                              { 
        (yyval.nptr) = create_node(NODE_VAR_DECLARACAO, (yyvsp[-2].nptr), create_leaf_id(NODE_ID, (yyvsp[-1].sval)), NULL); 
    }
#line 1292 "parser.tab.c"
    break;

  case 8: /* var_declaracao: tipo_especificador ID ACO NUM FCO PEV  */
#line 129 "parser.y"
                                            { 
        (yyval.nptr) = create_node(NODE_VAR_DECLARACAO_ARRAY, (yyvsp[-5].nptr), create_leaf_id(NODE_ID, (yyvsp[-4].sval)), create_leaf_val(NODE_NUM, (yyvsp[-2].ival))); 
    }
#line 1300 "parser.tab.c"
    break;

  case 9: /* tipo_especificador: INT  */
#line 135 "parser.y"
        { (yyval.nptr) = create_node(NODE_TIPO_INT, NULL, NULL, NULL); }
#line 1306 "parser.tab.c"
    break;

  case 10: /* tipo_especificador: VOI  */
#line 136 "parser.y"
          { (yyval.nptr) = create_node(NODE_TIPO_VOID, NULL, NULL, NULL); }
#line 1312 "parser.tab.c"
    break;

  case 11: /* fun_declaracao: tipo_especificador ID APR params FPR composto_decl  */
#line 140 "parser.y"
                                                       {
        Node* id_node = create_leaf_id(NODE_ID, (yyvsp[-4].sval));
        id_node->child1 = (yyvsp[-2].nptr);
        (yyval.nptr) = create_node(NODE_FUN_DECLARACAO, (yyvsp[-5].nptr), id_node, (yyvsp[0].nptr));
    }
#line 1322 "parser.tab.c"
    break;

  case 12: /* params: param_lista  */
#line 148 "parser.y"
                { (yyval.nptr) = (yyvsp[0].nptr); }
#line 1328 "parser.tab.c"
    break;

  case 13: /* params: VOI  */
#line 149 "parser.y"
          { (yyval.nptr) = create_node(NODE_TIPO_VOID, NULL, NULL, NULL); }
#line 1334 "parser.tab.c"
    break;

  case 14: /* param_lista: param_lista VIR param  */
#line 153 "parser.y"
                          {
        Node* head = (yyvsp[-2].nptr);
        while (head->sibling) head = head->sibling;
        head->sibling = (yyvsp[0].nptr);
        (yyval.nptr) = (yyvsp[-2].nptr);
    }
#line 1345 "parser.tab.c"
    break;

  case 15: /* param_lista: param  */
#line 159 "parser.y"
            { (yyval.nptr) = (yyvsp[0].nptr); }
#line 1351 "parser.tab.c"
    break;

  case 16: /* param: tipo_especificador ID  */
#line 163 "parser.y"
                          { 
        (yyval.nptr) = create_node(NODE_PARAM, (yyvsp[-1].nptr), create_leaf_id(NODE_ID, (yyvsp[0].sval)), NULL); 
    }
#line 1359 "parser.tab.c"
    break;

  case 17: /* param: tipo_especificador ID ACO FCO  */
#line 166 "parser.y"
                                    { 
        (yyval.nptr) = create_node(NODE_PARAM_ARRAY, (yyvsp[-3].nptr), create_leaf_id(NODE_ID, (yyvsp[-2].sval)), NULL); 
    }
#line 1367 "parser.tab.c"
    break;

  case 18: /* composto_decl: ACH local_declaracoes statement_lista FCH  */
#line 172 "parser.y"
                                              { 
        (yyval.nptr) = create_node(NODE_COMPOSTO_DECL, (yyvsp[-2].nptr), (yyvsp[-1].nptr), NULL); 
    }
#line 1375 "parser.tab.c"
    break;

  case 19: /* local_declaracoes: local_declaracoes var_declaracao  */
#line 178 "parser.y"
                                     {
        Node* head = (yyvsp[-1].nptr);
        if (head) {
            while (head->sibling) head = head->sibling;
            head->sibling = (yyvsp[0].nptr);
            (yyval.nptr) = (yyvsp[-1].nptr);
        } else {
            (yyval.nptr) = (yyvsp[0].nptr);
        }
    }
#line 1390 "parser.tab.c"
    break;

  case 20: /* local_declaracoes: %empty  */
#line 188 "parser.y"
      { (yyval.nptr) = NULL; }
#line 1396 "parser.tab.c"
    break;

  case 21: /* statement_lista: statement_lista statement  */
#line 192 "parser.y"
                              {
        Node* head = (yyvsp[-1].nptr);
        if (head) {
            while (head->sibling) head = head->sibling;
            head->sibling = (yyvsp[0].nptr);
            (yyval.nptr) = (yyvsp[-1].nptr);
        } else {
            (yyval.nptr) = (yyvsp[0].nptr);
        }
    }
#line 1411 "parser.tab.c"
    break;

  case 22: /* statement_lista: %empty  */
#line 202 "parser.y"
      { (yyval.nptr) = NULL; }
#line 1417 "parser.tab.c"
    break;

  case 23: /* statement: expressao_decl  */
#line 206 "parser.y"
                   { (yyval.nptr) = (yyvsp[0].nptr); }
#line 1423 "parser.tab.c"
    break;

  case 24: /* statement: composto_decl  */
#line 207 "parser.y"
                    { (yyval.nptr) = (yyvsp[0].nptr); }
#line 1429 "parser.tab.c"
    break;

  case 25: /* statement: selecao_decl  */
#line 208 "parser.y"
                   { (yyval.nptr) = (yyvsp[0].nptr); }
#line 1435 "parser.tab.c"
    break;

  case 26: /* statement: iteracao_decl  */
#line 209 "parser.y"
                    { (yyval.nptr) = (yyvsp[0].nptr); }
#line 1441 "parser.tab.c"
    break;

  case 27: /* statement: retorno_decl  */
#line 210 "parser.y"
                   { (yyval.nptr) = (yyvsp[0].nptr); }
#line 1447 "parser.tab.c"
    break;

  case 28: /* expressao_decl: expressao PEV  */
#line 214 "parser.y"
                  { (yyval.nptr) = (yyvsp[-1].nptr); }
#line 1453 "parser.tab.c"
    break;

  case 29: /* expressao_decl: PEV  */
#line 215 "parser.y"
          { (yyval.nptr) = NULL; }
#line 1459 "parser.tab.c"
    break;

  case 30: /* selecao_decl: IF APR expressao FPR statement  */
#line 219 "parser.y"
                                                         { 
        (yyval.nptr) = create_node(NODE_SELECAO_DECL, (yyvsp[-2].nptr), (yyvsp[0].nptr), NULL); 
    }
#line 1467 "parser.tab.c"
    break;

  case 31: /* selecao_decl: IF APR expressao FPR statement ELSE statement  */
#line 222 "parser.y"
                                                    { 
        (yyval.nptr) = create_node(NODE_SELECAO_DECL, (yyvsp[-4].nptr), (yyvsp[-2].nptr), (yyvsp[0].nptr)); 
    }
#line 1475 "parser.tab.c"
    break;

  case 32: /* iteracao_decl: WHI APR expressao FPR statement  */
#line 228 "parser.y"
                                    { 
        (yyval.nptr) = create_node(NODE_ITERACAO_DECL, (yyvsp[-2].nptr), (yyvsp[0].nptr), NULL); 
    }
#line 1483 "parser.tab.c"
    break;

  case 33: /* retorno_decl: RET PEV  */
#line 234 "parser.y"
            { 
        (yyval.nptr) = create_node(NODE_RETORNO_DECL, NULL, NULL, NULL); 
    }
#line 1491 "parser.tab.c"
    break;

  case 34: /* retorno_decl: RET expressao PEV  */
#line 237 "parser.y"
                        { 
        (yyval.nptr) = create_node(NODE_RETORNO_DECL, (yyvsp[-1].nptr), NULL, NULL); 
    }
#line 1499 "parser.tab.c"
    break;

  case 35: /* expressao: var REC expressao  */
#line 243 "parser.y"
                      { 
        (yyval.nptr) = create_node(NODE_EXPRESSAO_REC, (yyvsp[-2].nptr), (yyvsp[0].nptr), NULL); 
    }
#line 1507 "parser.tab.c"
    break;

  case 36: /* expressao: simples_expressao  */
#line 246 "parser.y"
                        { (yyval.nptr) = (yyvsp[0].nptr); }
#line 1513 "parser.tab.c"
    break;

  case 37: /* var: ID  */
#line 250 "parser.y"
       { (yyval.nptr) = create_leaf_id(NODE_ID, (yyvsp[0].sval)); }
#line 1519 "parser.tab.c"
    break;

  case 38: /* var: ID ACO expressao FCO  */
#line 251 "parser.y"
                           { 
        (yyval.nptr) = create_node(NODE_VAR_ARRAY, create_leaf_id(NODE_ID, (yyvsp[-3].sval)), (yyvsp[-1].nptr), NULL); 
    }
#line 1527 "parser.tab.c"
    break;

  case 39: /* simples_expressao: soma_expressao relacional soma_expressao  */
#line 257 "parser.y"
                                             { 
        (yyval.nptr) = create_node(NODE_RELACIONAL, (yyvsp[-2].nptr), (yyvsp[0].nptr), (yyvsp[-1].nptr)); 
    }
#line 1535 "parser.tab.c"
    break;

  case 40: /* simples_expressao: soma_expressao  */
#line 260 "parser.y"
                     { (yyval.nptr) = (yyvsp[0].nptr); }
#line 1541 "parser.tab.c"
    break;

  case 41: /* relacional: LEQUAL  */
#line 264 "parser.y"
           { (yyval.nptr) = create_node(NODE_REL_LEQUAL, NULL, NULL, NULL); }
#line 1547 "parser.tab.c"
    break;

  case 42: /* relacional: MENOR  */
#line 265 "parser.y"
            { (yyval.nptr) = create_node(NODE_REL_MENOR, NULL, NULL, NULL); }
#line 1553 "parser.tab.c"
    break;

  case 43: /* relacional: HIGHER  */
#line 266 "parser.y"
             { (yyval.nptr) = create_node(NODE_REL_HIGHER, NULL, NULL, NULL); }
#line 1559 "parser.tab.c"
    break;

  case 44: /* relacional: HEQUAL  */
#line 267 "parser.y"
             { (yyval.nptr) = create_node(NODE_REL_HEQUAL, NULL, NULL, NULL); }
#line 1565 "parser.tab.c"
    break;

  case 45: /* relacional: IGL  */
#line 268 "parser.y"
          { (yyval.nptr) = create_node(NODE_REL_IGL, NULL, NULL, NULL); }
#line 1571 "parser.tab.c"
    break;

  case 46: /* relacional: DIF  */
#line 269 "parser.y"
          { (yyval.nptr) = create_node(NODE_REL_DIF, NULL, NULL, NULL); }
#line 1577 "parser.tab.c"
    break;

  case 47: /* soma_expressao: soma_expressao soma termo  */
#line 273 "parser.y"
                              { 
        (yyval.nptr) = create_node((yyvsp[-1].nptr)->type, (yyvsp[-2].nptr), (yyvsp[0].nptr), NULL); 
    }
#line 1585 "parser.tab.c"
    break;

  case 48: /* soma_expressao: termo  */
#line 276 "parser.y"
            { (yyval.nptr) = (yyvsp[0].nptr); }
#line 1591 "parser.tab.c"
    break;

  case 49: /* soma: SOM  */
#line 280 "parser.y"
        { (yyval.nptr) = create_node(NODE_SOMA, NULL, NULL, NULL); }
#line 1597 "parser.tab.c"
    break;

  case 50: /* soma: SUB  */
#line 281 "parser.y"
          { (yyval.nptr) = create_node(NODE_SUB, NULL, NULL, NULL); }
#line 1603 "parser.tab.c"
    break;

  case 51: /* termo: termo mult fator  */
#line 285 "parser.y"
                     { 
        (yyval.nptr) = create_node((yyvsp[-1].nptr)->type, (yyvsp[-2].nptr), (yyvsp[0].nptr), NULL); 
    }
#line 1611 "parser.tab.c"
    break;

  case 52: /* termo: fator  */
#line 288 "parser.y"
            { (yyval.nptr) = (yyvsp[0].nptr); }
#line 1617 "parser.tab.c"
    break;

  case 53: /* mult: MUL  */
#line 292 "parser.y"
        { (yyval.nptr) = create_node(NODE_MULT, NULL, NULL, NULL); }
#line 1623 "parser.tab.c"
    break;

  case 54: /* mult: DIV  */
#line 293 "parser.y"
          { (yyval.nptr) = create_node(NODE_DIV, NULL, NULL, NULL); }
#line 1629 "parser.tab.c"
    break;

  case 55: /* fator: APR expressao FPR  */
#line 297 "parser.y"
                      { (yyval.nptr) = (yyvsp[-1].nptr); }
#line 1635 "parser.tab.c"
    break;

  case 56: /* fator: var  */
#line 298 "parser.y"
          { (yyval.nptr) = (yyvsp[0].nptr); }
#line 1641 "parser.tab.c"
    break;

  case 57: /* fator: ativacao  */
#line 299 "parser.y"
               { (yyval.nptr) = (yyvsp[0].nptr); }
#line 1647 "parser.tab.c"
    break;

  case 58: /* fator: NUM  */
#line 300 "parser.y"
          { (yyval.nptr) = create_leaf_val(NODE_NUM, (yyvsp[0].ival)); }
#line 1653 "parser.tab.c"
    break;

  case 59: /* ativacao: ID APR args FPR  */
#line 304 "parser.y"
                    { 
        (yyval.nptr) = create_node(NODE_ATIVACAO, create_leaf_id(NODE_ID, (yyvsp[-3].sval)), (yyvsp[-1].nptr), NULL); 
    }
#line 1661 "parser.tab.c"
    break;

  case 60: /* args: arg_lista  */
#line 310 "parser.y"
              { (yyval.nptr) = (yyvsp[0].nptr); }
#line 1667 "parser.tab.c"
    break;

  case 61: /* args: %empty  */
#line 311 "parser.y"
      { (yyval.nptr) = NULL; }
#line 1673 "parser.tab.c"
    break;

  case 62: /* arg_lista: arg_lista VIR expressao  */
#line 315 "parser.y"
                            {
        Node* head = (yyvsp[-2].nptr);
        while (head->sibling) head = head->sibling;
        head->sibling = (yyvsp[0].nptr);
        (yyval.nptr) = (yyvsp[-2].nptr);
    }
#line 1684 "parser.tab.c"
    break;

  case 63: /* arg_lista: expressao  */
#line 321 "parser.y"
                { (yyval.nptr) = (yyvsp[0].nptr); }
#line 1690 "parser.tab.c"
    break;


#line 1694 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 323 "parser.y"


Node* create_node(NodeType type, Node* c1, Node* c2, Node* c3) {
    Node* n = (Node*) malloc(sizeof(Node));
    if (n == NULL) {
        yyerror("Erro: Sem memória para criar nó da árvore");
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
        default: printf("ERRO: Nó desconhecido (%d)\n", node->type);
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
    if (yyparse() == 0) { 
        printf("Analise Sintatica concluida com SUCESSO!\n");
        printf("\nImprimindo Arvore Sintatica Abstrata:\n");
        print_tree(ast_root, 0);
        
        printf("\nIniciando Analise Semantica...\n");
        semantic_analysis(ast_root);
    } else {
        printf("Analise Sintatica falhou.\n");
    }

    fclose(f_in);
    return 0;
}

void yyerror(const char *s) {
    printf("ERRO SINTÁTICO: %s LINHA: %d\n", yytext, yylineno);
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

Symbol* symbol_table = NULL;

void semantic_error(char* msg, char* id, int lineno) {
    if (id)
        printf("ERRO SEMÂNTICO: %s %s LINHA: %d\n", msg, id, lineno);
    else
        printf("ERRO SEMÂNTICO: %s LINHA: %d\n", msg, lineno);
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
                semantic_error("declaração inválida de variável", name, node->lineno);
            } 
            else if (is_declared_in_scope(name, current_scope)) {
                semantic_error("declaração inválida de variável", name, node->lineno); 
            } 
            else if (lookup_function(name)) {
                 semantic_error("declaração inválida", name, node->lineno); 
            } else {
                insert_symbol(name, type, current_scope, (node->type == NODE_VAR_DECLARACAO_ARRAY) ? "array" : "var", node->lineno);
            }
            break;
        }
        
        case NODE_FUN_DECLARACAO: {
            char* type = get_type_from_node(node->child1);
            char* name = node->child2->sval;
            
            if (lookup_function(name)) {
                semantic_error("declaração inválida", name, node->lineno);
            } else {
                insert_symbol(name, type, "global", "fun", node->lineno);
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
                                semantic_error("declaração inválida de variável", p_name, p->lineno);
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
                    semantic_error("chamada inválida", "número de parâmetros inválido", node->lineno);
                } else {
                    arg = args;
                    p = fun_sym->params;
                    while (arg && p) {
                        char* arg_type = get_expression_type(arg, current_scope);
                        if (strcmp(arg_type, p->type) != 0) {
                             if (strcmp(arg_type, "unknown") != 0 && strcmp(p->type, "unknown") != 0) {
                                semantic_error("chamada inválida", "tipo de parâmetro inválido", node->lineno);
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
                semantic_error("variável não declarada", name, node->lineno);
            }
            break;
        }
        
        case NODE_VAR_ARRAY: {
            char* name = node->child1->sval;
            Symbol* sym = lookup_symbol(name, current_scope);
            if (!sym) {
                semantic_error("variável não declarada", name, node->lineno);
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
            if (var_node->type == NODE_ID) {
                Symbol* sym = lookup_symbol(var_node->sval, current_scope);
                if (sym) var_type = sym->type;
            } else if (var_node->type == NODE_VAR_ARRAY) {
                 Symbol* sym = lookup_symbol(var_node->child1->sval, current_scope);
                 if (sym) var_type = sym->type;
            }
            
            char* expr_type = get_expression_type(expr_node, current_scope);
            
            if (strcmp(var_type, "int") == 0 && strcmp(expr_type, "void") == 0) {
                 semantic_error("atribuição inválida", NULL, node->lineno);
            }
            break;
        }

        case NODE_RETORNO_DECL: {
            if (strcmp(current_scope, "global") != 0) {
                Symbol* fun_sym = lookup_function(current_scope);
                if (fun_sym) {
                    if (node->child1) { 
                        if (strcmp(fun_sym->type, "void") == 0) {
                            semantic_error("chamada inválida", "parâmetro de retorno da função não previsto", node->lineno);
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
    
    if (lookup_function("main") == NULL) {
        semantic_error("função main() não declarada", NULL, 0); 
    }
    
    print_symbol_table();
}
