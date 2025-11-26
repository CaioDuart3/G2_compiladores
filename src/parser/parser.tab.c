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
#line 1 "parser/parser.y"

  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "../st/st.h"
  #include "../tac/tac.h"
  #include "../ast/ast.h"
  #include "../codigo_final/gerador_codigo_final.h"



  #define YYERROR_VERBOSE 1

  int yylex(void);
  void yyerror(const char *s);

  extern int yylineno;
  extern void inicializa_pilha();

  /* Variável global que guardará a raiz da árvore */
  NoAST *raizAST = NULL;

  /* Auxiliares para passar dados do header do 'for' até depois do 'bloco' */
//   static char *last_for_var = NULL;
//   static NoAST *last_for_expr = NULL;

//   static void set_last_for_var(char *s) { last_for_var = s; }
//   static char *get_last_for_var(void) { return last_for_var; }
//   static void set_last_for_expr(NoAST *n) { last_for_expr = n; }
//   static NoAST *get_last_for_expr(void) { return last_for_expr; }

#line 103 "parser/parser.tab.c"

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
  YYSYMBOL_TOKEN_IDENTIFICADOR = 3,        /* TOKEN_IDENTIFICADOR  */
  YYSYMBOL_TOKEN_STRING = 4,               /* TOKEN_STRING  */
  YYSYMBOL_TOKEN_INTEIRO = 5,              /* TOKEN_INTEIRO  */
  YYSYMBOL_TOKEN_PALAVRA_CHAVE_TRUE = 6,   /* TOKEN_PALAVRA_CHAVE_TRUE  */
  YYSYMBOL_TOKEN_PALAVRA_CHAVE_FALSE = 7,  /* TOKEN_PALAVRA_CHAVE_FALSE  */
  YYSYMBOL_TOKEN_FLOAT = 8,                /* TOKEN_FLOAT  */
  YYSYMBOL_TOKEN_PALAVRA_CHAVE_IF = 9,     /* TOKEN_PALAVRA_CHAVE_IF  */
  YYSYMBOL_TOKEN_PALAVRA_CHAVE_ELSE = 10,  /* TOKEN_PALAVRA_CHAVE_ELSE  */
  YYSYMBOL_TOKEN_PALAVRA_CHAVE_ELIF = 11,  /* TOKEN_PALAVRA_CHAVE_ELIF  */
  YYSYMBOL_TOKEN_PALAVRA_CHAVE_WHILE = 12, /* TOKEN_PALAVRA_CHAVE_WHILE  */
  YYSYMBOL_TOKEN_PALAVRA_CHAVE_FOR = 13,   /* TOKEN_PALAVRA_CHAVE_FOR  */
  YYSYMBOL_TOKEN_PALAVRA_CHAVE_RETURN = 14, /* TOKEN_PALAVRA_CHAVE_RETURN  */
  YYSYMBOL_TOKEN_PALAVRA_CHAVE_IN = 15,    /* TOKEN_PALAVRA_CHAVE_IN  */
  YYSYMBOL_TOKEN_OPERADOR_IGUAL = 16,      /* TOKEN_OPERADOR_IGUAL  */
  YYSYMBOL_TOKEN_OPERADOR_DIFERENTE = 17,  /* TOKEN_OPERADOR_DIFERENTE  */
  YYSYMBOL_TOKEN_OPERADOR_MENOR_IGUAL = 18, /* TOKEN_OPERADOR_MENOR_IGUAL  */
  YYSYMBOL_TOKEN_OPERADOR_MAIOR_IGUAL = 19, /* TOKEN_OPERADOR_MAIOR_IGUAL  */
  YYSYMBOL_TOKEN_OPERADOR_MENOR = 20,      /* TOKEN_OPERADOR_MENOR  */
  YYSYMBOL_TOKEN_OPERADOR_MAIOR = 21,      /* TOKEN_OPERADOR_MAIOR  */
  YYSYMBOL_TOKEN_OPERADOR_ATRIBUICAO = 22, /* TOKEN_OPERADOR_ATRIBUICAO  */
  YYSYMBOL_TOKEN_OPERADOR_MAIS = 23,       /* TOKEN_OPERADOR_MAIS  */
  YYSYMBOL_TOKEN_OPERADOR_MENOS = 24,      /* TOKEN_OPERADOR_MENOS  */
  YYSYMBOL_TOKEN_OPERADOR_MULTIPLICACAO = 25, /* TOKEN_OPERADOR_MULTIPLICACAO  */
  YYSYMBOL_TOKEN_OPERADOR_DIVISAO = 26,    /* TOKEN_OPERADOR_DIVISAO  */
  YYSYMBOL_TOKEN_DELIMITADOR_DOIS_PONTOS = 27, /* TOKEN_DELIMITADOR_DOIS_PONTOS  */
  YYSYMBOL_TOKEN_DELIMITADOR_VIRGULA = 28, /* TOKEN_DELIMITADOR_VIRGULA  */
  YYSYMBOL_TOKEN_DELIMITADOR_ABRE_PARENTESES = 29, /* TOKEN_DELIMITADOR_ABRE_PARENTESES  */
  YYSYMBOL_TOKEN_DELIMITADOR_FECHA_PARENTESES = 30, /* TOKEN_DELIMITADOR_FECHA_PARENTESES  */
  YYSYMBOL_TOKEN_DELIMITADOR_ABRE_CHAVES = 31, /* TOKEN_DELIMITADOR_ABRE_CHAVES  */
  YYSYMBOL_TOKEN_DELIMITADOR_FECHA_CHAVES = 32, /* TOKEN_DELIMITADOR_FECHA_CHAVES  */
  YYSYMBOL_TOKEN_DELIMITADOR_ABRE_COLCHETES = 33, /* TOKEN_DELIMITADOR_ABRE_COLCHETES  */
  YYSYMBOL_TOKEN_DELIMITADOR_FECHA_COLCHETES = 34, /* TOKEN_DELIMITADOR_FECHA_COLCHETES  */
  YYSYMBOL_TOKEN_DESCONHECIDO = 35,        /* TOKEN_DESCONHECIDO  */
  YYSYMBOL_TOKEN_NEWLINE = 36,             /* TOKEN_NEWLINE  */
  YYSYMBOL_TOKEN_INDENT = 37,              /* TOKEN_INDENT  */
  YYSYMBOL_TOKEN_DEDENT = 38,              /* TOKEN_DEDENT  */
  YYSYMBOL_TOKEN_PALAVRA_CHAVE_DEF = 39,   /* TOKEN_PALAVRA_CHAVE_DEF  */
  YYSYMBOL_TOKEN_OPERADOR_LOGICO_AND = 40, /* TOKEN_OPERADOR_LOGICO_AND  */
  YYSYMBOL_TOKEN_OPERADOR_LOGICO_OR = 41,  /* TOKEN_OPERADOR_LOGICO_OR  */
  YYSYMBOL_TOKEN_OPERADOR_LOGICO_NOT = 42, /* TOKEN_OPERADOR_LOGICO_NOT  */
  YYSYMBOL_LOWER_THAN_ELSE = 43,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 44,                  /* $accept  */
  YYSYMBOL_programa = 45,                  /* programa  */
  YYSYMBOL_newlines_opt = 46,              /* newlines_opt  */
  YYSYMBOL_lista_comandos_opt = 47,        /* lista_comandos_opt  */
  YYSYMBOL_lista_comandos = 48,            /* lista_comandos  */
  YYSYMBOL_comando = 49,                   /* comando  */
  YYSYMBOL_declaracao_funcao = 50,         /* declaracao_funcao  */
  YYSYMBOL_51_1 = 51,                      /* $@1  */
  YYSYMBOL_retorno = 52,                   /* retorno  */
  YYSYMBOL_atribuicao = 53,                /* atribuicao  */
  YYSYMBOL_atribuicao_indexacao = 54,      /* atribuicao_indexacao  */
  YYSYMBOL_atribuicao_simples = 55,        /* atribuicao_simples  */
  YYSYMBOL_atribuicao_multipla = 56,       /* atribuicao_multipla  */
  YYSYMBOL_atribuicao_encadeada = 57,      /* atribuicao_encadeada  */
  YYSYMBOL_lista_identificadores = 58,     /* lista_identificadores  */
  YYSYMBOL_lista_expressoes = 59,          /* lista_expressoes  */
  YYSYMBOL_lista_argumentos = 60,          /* lista_argumentos  */
  YYSYMBOL_chamada_funcao = 61,            /* chamada_funcao  */
  YYSYMBOL_expressao = 62,                 /* expressao  */
  YYSYMBOL_atomo = 63,                     /* atomo  */
  YYSYMBOL_lista_valores = 64,             /* lista_valores  */
  YYSYMBOL_chamada_index = 65,             /* chamada_index  */
  YYSYMBOL_bloco = 66,                     /* bloco  */
  YYSYMBOL_if_stmt = 67,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 68,                /* while_stmt  */
  YYSYMBOL_69_2 = 69,                      /* $@2  */
  YYSYMBOL_for_stmt = 70,                  /* for_stmt  */
  YYSYMBOL_71_3 = 71                       /* $@3  */
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
typedef yytype_uint8 yy_state_t;

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

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  51
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   337

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  72
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  131

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   298


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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   105,   105,   112,   114,   118,   119,   126,   128,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   152,   151,
     167,   174,   175,   176,   177,   181,   192,   256,   263,   301,
     305,   312,   316,   325,   326,   328,   333,   343,   345,   347,
     349,   351,   353,   355,   357,   359,   361,   363,   365,   367,
     369,   376,   378,   380,   382,   394,   396,   398,   400,   404,
     406,   412,   413,   418,   426,   436,   442,   450,   459,   469,
     468,   489,   488
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TOKEN_IDENTIFICADOR",
  "TOKEN_STRING", "TOKEN_INTEIRO", "TOKEN_PALAVRA_CHAVE_TRUE",
  "TOKEN_PALAVRA_CHAVE_FALSE", "TOKEN_FLOAT", "TOKEN_PALAVRA_CHAVE_IF",
  "TOKEN_PALAVRA_CHAVE_ELSE", "TOKEN_PALAVRA_CHAVE_ELIF",
  "TOKEN_PALAVRA_CHAVE_WHILE", "TOKEN_PALAVRA_CHAVE_FOR",
  "TOKEN_PALAVRA_CHAVE_RETURN", "TOKEN_PALAVRA_CHAVE_IN",
  "TOKEN_OPERADOR_IGUAL", "TOKEN_OPERADOR_DIFERENTE",
  "TOKEN_OPERADOR_MENOR_IGUAL", "TOKEN_OPERADOR_MAIOR_IGUAL",
  "TOKEN_OPERADOR_MENOR", "TOKEN_OPERADOR_MAIOR",
  "TOKEN_OPERADOR_ATRIBUICAO", "TOKEN_OPERADOR_MAIS",
  "TOKEN_OPERADOR_MENOS", "TOKEN_OPERADOR_MULTIPLICACAO",
  "TOKEN_OPERADOR_DIVISAO", "TOKEN_DELIMITADOR_DOIS_PONTOS",
  "TOKEN_DELIMITADOR_VIRGULA", "TOKEN_DELIMITADOR_ABRE_PARENTESES",
  "TOKEN_DELIMITADOR_FECHA_PARENTESES", "TOKEN_DELIMITADOR_ABRE_CHAVES",
  "TOKEN_DELIMITADOR_FECHA_CHAVES", "TOKEN_DELIMITADOR_ABRE_COLCHETES",
  "TOKEN_DELIMITADOR_FECHA_COLCHETES", "TOKEN_DESCONHECIDO",
  "TOKEN_NEWLINE", "TOKEN_INDENT", "TOKEN_DEDENT",
  "TOKEN_PALAVRA_CHAVE_DEF", "TOKEN_OPERADOR_LOGICO_AND",
  "TOKEN_OPERADOR_LOGICO_OR", "TOKEN_OPERADOR_LOGICO_NOT",
  "LOWER_THAN_ELSE", "$accept", "programa", "newlines_opt",
  "lista_comandos_opt", "lista_comandos", "comando", "declaracao_funcao",
  "$@1", "retorno", "atribuicao", "atribuicao_indexacao",
  "atribuicao_simples", "atribuicao_multipla", "atribuicao_encadeada",
  "lista_identificadores", "lista_expressoes", "lista_argumentos",
  "chamada_funcao", "expressao", "atomo", "lista_valores", "chamada_index",
  "bloco", "if_stmt", "while_stmt", "$@2", "for_stmt", "$@3", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-56)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-30)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     112,     6,   -56,   -56,   -56,   -56,   -56,   124,   124,     3,
     124,   124,   124,   -26,    22,   124,    27,   -56,   112,   -56,
     -56,   -56,   -56,   -56,   -56,   -56,   -56,     4,   -56,   271,
       0,   -56,   -56,   -56,   -56,   -56,   130,   124,   124,     7,
      -3,   157,    29,   271,   169,    17,   271,    12,   112,    33,
     300,   -56,    30,   -56,   124,    64,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   -56,
     271,   -21,   271,   195,    36,   -56,   124,   -56,   124,   -56,
      72,    70,   -56,    17,   -56,   311,   311,    69,   181,    69,
     181,    15,    15,   -56,   -56,   300,   282,   207,   124,   -56,
      60,   -26,    32,    36,   233,   271,   -56,   -56,   -18,   -56,
     271,   124,    56,   124,   -56,   -56,    71,   271,    36,   245,
      36,   -56,   -56,    36,   -56,    36,    86,   -56,    73,    36,
     -56
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,    54,    55,    52,    56,    57,    53,     0,     0,     0,
       0,     0,    61,    14,     0,     0,     0,     3,     6,     7,
      16,    17,     9,    24,    21,    22,    23,     0,    60,    10,
      50,    59,    15,    11,    12,    13,     0,    33,     0,    54,
       0,     0,     0,    20,     0,    62,    31,     0,     0,     0,
      49,     1,     2,     8,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    28,
      26,     0,    34,     0,     0,    69,     0,    51,     0,    58,
       0,     0,     4,    27,    30,    41,    42,    44,    46,    43,
      45,    37,    38,    39,    40,    47,    48,     0,     0,    36,
       0,     0,    65,     0,     0,    32,    64,    29,     0,    63,
      35,     0,     0,     0,    70,    71,     0,    25,     0,     0,
       0,    18,    68,     0,    72,     0,    66,    19,     0,     0,
      67
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -56,   -56,   -56,   -56,    49,   -16,   -56,   -56,   -56,    63,
     -56,   -56,   -56,   -56,    21,    53,   -56,   -56,    -7,   -56,
     -56,   -56,   -55,   -56,   -56,   -56,   -56,   -56
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    16,    52,    17,    18,    19,    20,   125,    21,    22,
      23,    24,    25,    26,    27,    45,    71,    28,    29,    30,
      47,    31,    32,    33,    34,   103,    35,   120
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      40,    41,    53,    43,    44,    46,    42,    98,    50,    99,
      55,    48,   116,    56,    57,    58,    59,    60,    61,   102,
      62,    63,    64,    65,    74,    49,    54,    51,    36,    70,
      72,    73,    55,    68,   -29,    37,    37,    66,    67,    38,
      64,    65,   112,   113,    76,    78,    79,    46,   114,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    81,   122,    53,   124,    82,    84,   126,   104,
     127,   105,   101,   107,   130,     1,     2,     3,     4,     5,
       6,     7,   111,   118,     8,     9,    10,   -30,    59,   -30,
      61,   110,    62,    63,    64,    65,   128,    80,   121,    69,
     129,    11,   108,     0,   117,    12,   119,    83,    13,     0,
     106,    14,     0,     0,    15,     1,     2,     3,     4,     5,
       6,     7,     0,     0,     8,     9,    10,    39,     2,     3,
       4,     5,     6,     1,     2,     3,     4,     5,     6,     0,
       0,    11,     0,     0,     0,    12,     0,     0,    13,     0,
       0,    14,     0,    11,    15,     0,     0,    12,     0,    11,
       0,     0,     0,    12,     0,     0,    15,     0,     0,     0,
       0,     0,    15,    56,    57,    58,    59,    60,    61,     0,
      62,    63,    64,    65,    75,    56,    57,    58,    59,    60,
      61,     0,    62,    63,    64,    65,     0,    66,    67,    77,
     -30,     0,   -30,     0,    62,    63,    64,    65,     0,    66,
      67,    56,    57,    58,    59,    60,    61,     0,    62,    63,
      64,    65,     0,    56,    57,    58,    59,    60,    61,   100,
      62,    63,    64,    65,     0,    66,    67,     0,     0,     0,
       0,   109,     0,     0,     0,     0,     0,    66,    67,    56,
      57,    58,    59,    60,    61,     0,    62,    63,    64,    65,
     115,    56,    57,    58,    59,    60,    61,     0,    62,    63,
      64,    65,   123,    66,    67,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    66,    67,    56,    57,    58,
      59,    60,    61,     0,    62,    63,    64,    65,    56,    57,
      58,    59,    60,    61,     0,    62,    63,    64,    65,     0,
       0,    66,    67,     0,     0,     0,    56,    57,    58,    59,
      60,    61,    66,    62,    63,    64,    65,   -30,   -30,    58,
      59,    60,    61,     0,    62,    63,    64,    65
};

static const yytype_int16 yycheck[] =
{
       7,     8,    18,    10,    11,    12,     3,    28,    15,    30,
      28,    37,    30,    16,    17,    18,    19,    20,    21,    74,
      23,    24,    25,    26,    27,     3,    22,     0,    22,    36,
      37,    38,    28,    33,    28,    29,    29,    40,    41,    33,
      25,    26,    10,    11,    15,    28,    34,    54,   103,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    29,   118,    80,   120,    36,     3,   123,    76,
     125,    78,    36,     3,   129,     3,     4,     5,     6,     7,
       8,     9,    22,    27,    12,    13,    14,    18,    19,    20,
      21,    98,    23,    24,    25,    26,    10,    48,    27,    36,
      27,    29,    81,    -1,   111,    33,   113,    54,    36,    -1,
      38,    39,    -1,    -1,    42,     3,     4,     5,     6,     7,
       8,     9,    -1,    -1,    12,    13,    14,     3,     4,     5,
       6,     7,     8,     3,     4,     5,     6,     7,     8,    -1,
      -1,    29,    -1,    -1,    -1,    33,    -1,    -1,    36,    -1,
      -1,    39,    -1,    29,    42,    -1,    -1,    33,    -1,    29,
      -1,    -1,    -1,    33,    -1,    -1,    42,    -1,    -1,    -1,
      -1,    -1,    42,    16,    17,    18,    19,    20,    21,    -1,
      23,    24,    25,    26,    27,    16,    17,    18,    19,    20,
      21,    -1,    23,    24,    25,    26,    -1,    40,    41,    30,
      19,    -1,    21,    -1,    23,    24,    25,    26,    -1,    40,
      41,    16,    17,    18,    19,    20,    21,    -1,    23,    24,
      25,    26,    -1,    16,    17,    18,    19,    20,    21,    34,
      23,    24,    25,    26,    -1,    40,    41,    -1,    -1,    -1,
      -1,    34,    -1,    -1,    -1,    -1,    -1,    40,    41,    16,
      17,    18,    19,    20,    21,    -1,    23,    24,    25,    26,
      27,    16,    17,    18,    19,    20,    21,    -1,    23,    24,
      25,    26,    27,    40,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    40,    41,    16,    17,    18,
      19,    20,    21,    -1,    23,    24,    25,    26,    16,    17,
      18,    19,    20,    21,    -1,    23,    24,    25,    26,    -1,
      -1,    40,    41,    -1,    -1,    -1,    16,    17,    18,    19,
      20,    21,    40,    23,    24,    25,    26,    16,    17,    18,
      19,    20,    21,    -1,    23,    24,    25,    26
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    12,    13,
      14,    29,    33,    36,    39,    42,    45,    47,    48,    49,
      50,    52,    53,    54,    55,    56,    57,    58,    61,    62,
      63,    65,    66,    67,    68,    70,    22,    29,    33,     3,
      62,    62,     3,    62,    62,    59,    62,    64,    37,     3,
      62,     0,    46,    49,    22,    28,    16,    17,    18,    19,
      20,    21,    23,    24,    25,    26,    40,    41,    33,    53,
      62,    60,    62,    62,    27,    27,    15,    30,    28,    34,
      48,    29,    36,    59,     3,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    28,    30,
      34,    36,    66,    69,    62,    62,    38,     3,    58,    34,
      62,    22,    10,    11,    66,    27,    30,    62,    27,    62,
      71,    27,    66,    27,    66,    51,    66,    66,    10,    27,
      66
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    44,    45,    46,    46,    47,    47,    48,    48,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    51,    50,
      52,    53,    53,    53,    53,    54,    55,    56,    57,    58,
      58,    59,    59,    60,    60,    60,    61,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    64,    64,    65,    66,    67,    67,    67,    67,    69,
      68,    71,    70
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     0,     2,     0,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     8,
       2,     1,     1,     1,     1,     6,     3,     3,     3,     1,
       3,     1,     3,     0,     1,     3,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     0,     1,     4,     4,     4,     8,    11,     7,     0,
       5,     0,     7
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

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* programa: lista_comandos_opt newlines_opt  */
#line 106 "parser/parser.y"
    { 
        raizAST = (yyvsp[-1].no); /* Salva a raiz global */
        (yyval.no) = (yyvsp[-1].no);
    }
#line 1695 "parser/parser.tab.c"
    break;

  case 5: /* lista_comandos_opt: %empty  */
#line 118 "parser/parser.y"
                        { (yyval.no) = NULL; }
#line 1701 "parser/parser.tab.c"
    break;

  case 6: /* lista_comandos_opt: lista_comandos  */
#line 119 "parser/parser.y"
                      { (yyval.no) = (yyvsp[0].no); }
#line 1707 "parser/parser.tab.c"
    break;

  case 7: /* lista_comandos: comando  */
#line 127 "parser/parser.y"
        { (yyval.no) = criarNoLista((yyvsp[0].no), NULL); }
#line 1713 "parser/parser.tab.c"
    break;

  case 8: /* lista_comandos: lista_comandos comando  */
#line 129 "parser/parser.y"
        {
            if ((yyvsp[0].no) != NULL)
                (yyval.no) = criarNoLista((yyvsp[-1].no), (yyvsp[0].no));
            else
                (yyval.no) = (yyvsp[-1].no);
        }
#line 1724 "parser/parser.tab.c"
    break;

  case 9: /* comando: atribuicao  */
#line 138 "parser/parser.y"
                         { (yyval.no) = (yyvsp[0].no); }
#line 1730 "parser/parser.tab.c"
    break;

  case 10: /* comando: expressao  */
#line 139 "parser/parser.y"
                         { (yyval.no) = (yyvsp[0].no); }
#line 1736 "parser/parser.tab.c"
    break;

  case 11: /* comando: if_stmt  */
#line 140 "parser/parser.y"
                         { (yyval.no) = (yyvsp[0].no); }
#line 1742 "parser/parser.tab.c"
    break;

  case 12: /* comando: while_stmt  */
#line 141 "parser/parser.y"
                         { (yyval.no) = (yyvsp[0].no); }
#line 1748 "parser/parser.tab.c"
    break;

  case 13: /* comando: for_stmt  */
#line 142 "parser/parser.y"
                         { (yyval.no) = (yyvsp[0].no); }
#line 1754 "parser/parser.tab.c"
    break;

  case 14: /* comando: TOKEN_NEWLINE  */
#line 143 "parser/parser.y"
                         { (yyval.no) = NULL; }
#line 1760 "parser/parser.tab.c"
    break;

  case 15: /* comando: bloco  */
#line 144 "parser/parser.y"
                         { (yyval.no) = (yyvsp[0].no); }
#line 1766 "parser/parser.tab.c"
    break;

  case 16: /* comando: declaracao_funcao  */
#line 145 "parser/parser.y"
                         { (yyval.no) = (yyvsp[0].no); }
#line 1772 "parser/parser.tab.c"
    break;

  case 17: /* comando: retorno  */
#line 146 "parser/parser.y"
                         { (yyval.no) = (yyvsp[0].no); }
#line 1778 "parser/parser.tab.c"
    break;

  case 18: /* $@1: %empty  */
#line 152 "parser/parser.y"
    {
        openScope();

        registrarParametros((yyvsp[-2].no)); 
    }
#line 1788 "parser/parser.tab.c"
    break;

  case 19: /* declaracao_funcao: TOKEN_PALAVRA_CHAVE_DEF TOKEN_IDENTIFICADOR TOKEN_DELIMITADOR_ABRE_PARENTESES lista_identificadores TOKEN_DELIMITADOR_FECHA_PARENTESES TOKEN_DELIMITADOR_DOIS_PONTOS $@1 bloco  */
#line 158 "parser/parser.y"
    {
        closeScope();
        
        (yyval.no) = criarNoFuncao((yyvsp[-6].sval), (yyvsp[-4].no), (yyvsp[0].no));
        insertST((yyvsp[-6].sval), FUNCAO);
    }
#line 1799 "parser/parser.tab.c"
    break;

  case 20: /* retorno: TOKEN_PALAVRA_CHAVE_RETURN expressao  */
#line 168 "parser/parser.y"
    {
        (yyval.no) = criarNoReturn((yyvsp[0].no));
    }
#line 1807 "parser/parser.tab.c"
    break;

  case 25: /* atribuicao_indexacao: TOKEN_IDENTIFICADOR TOKEN_DELIMITADOR_ABRE_COLCHETES expressao TOKEN_DELIMITADOR_FECHA_COLCHETES TOKEN_OPERADOR_ATRIBUICAO expressao  */
#line 182 "parser/parser.y"
    {

        NoAST *no_index = criarNoIndex(criarNoId((yyvsp[-5].sval)), (yyvsp[-3].no));
        (yyval.no) = criarNoAtribuicao(no_index, (yyvsp[0].no));

        free((yyvsp[-5].sval));
    }
#line 1819 "parser/parser.tab.c"
    break;

  case 26: /* atribuicao_simples: TOKEN_IDENTIFICADOR TOKEN_OPERADOR_ATRIBUICAO expressao  */
#line 193 "parser/parser.y"
{
    (yyval.no) = criarNoAtribuicao(criarNoId((yyvsp[-2].sval)), (yyvsp[0].no));
    Simbolo *s = searchST((yyvsp[-2].sval));
    
    // Se não existe, cria. Se for lista, cria como VETOR, senão inferir.
    if (!s) {
        Tipo t = ((yyvsp[0].no)->tipo == NO_LISTA) ? VETOR : inferirTipo((yyvsp[0].no));
        insertST((yyvsp[-2].sval), t);
        s = searchST((yyvsp[-2].sval));
    }

    s->inicializado = true;

    if ((yyvsp[0].no)->tipo == NO_LISTA) {
        s->tipo = VETOR;
        int tamanho = 0;
        
        // O nó NO_LISTA tem a cadeia de expressões no filho1
        NoAST *elem = (yyvsp[0].no)->filho1; 
        
        // 1. Calcular tamanho
        while(elem) { 
            tamanho++; 
            elem = elem->proximo; 
        }
        
        // 2. Realocar memória
        if (s->vetor) free(s->vetor);
        s->vetor = malloc(sizeof(int) * tamanho);
        s->tamanho = tamanho;
        
        // 3. Preencher valores (AVALIANDO a expressão)
        elem = (yyvsp[0].no)->filho1; // Reinicia ponteiro
        for(int i=0; i < tamanho; i++) {
            // O elemento da lista pode ser uma expressão (ex: 1+1), precisa avaliar
            s->vetor[i] = avaliarExpressao(elem);
            elem = elem->proximo;
        }
    } else {
        // Lógica padrão para escalares
        switch(s->tipo) {
            case INT:
            case BOOL:
                // Assume que avaliarExpressao retorna INT/BOOL
                s->valor.valor_int = avaliarExpressao((yyvsp[0].no)); 
                break;
            case FLOAT:
                // NOVO: Usa a nova função de avaliação para floats
                // (Assumimos que você criará avaliarExpressaoFloat no seu ast.c)
                s->valor.valor_float = avaliarExpressaoFloat((yyvsp[0].no)); 
                break;
            case STRING:
                if ((yyvsp[0].no)->valor_string) s->valor.valor_string = strdup((yyvsp[0].no)->valor_string);
                break;
            default:
                break;
        }
    }
    free((yyvsp[-2].sval));
}
#line 1884 "parser/parser.tab.c"
    break;

  case 27: /* atribuicao_multipla: lista_identificadores TOKEN_OPERADOR_ATRIBUICAO lista_expressoes  */
#line 257 "parser/parser.y"
      {
          (yyval.no) = criarNoAtribuicaoMultipla((yyvsp[-2].no), (yyvsp[0].no));
      }
#line 1892 "parser/parser.tab.c"
    break;

  case 28: /* atribuicao_encadeada: TOKEN_IDENTIFICADOR TOKEN_OPERADOR_ATRIBUICAO atribuicao  */
#line 264 "parser/parser.y"
{
    (yyval.no) = criarNoAtribuicao(criarNoId((yyvsp[-2].sval)), (yyvsp[0].no));

    NoAST *rhs = (yyvsp[0].no);

    while (rhs->tipo == NO_ATRIBUICAO) {
        rhs = rhs->filho2;
    }

    Tipo t = inferirTipo(rhs);

    Simbolo *s = searchST((yyvsp[-2].sval));
    if (!s) insertST((yyvsp[-2].sval), t);
    else s->tipo = t;

switch (t) {
    case INT:
        s->valor.valor_int = (yyvsp[0].no)->valor_int;
        break;
    case BOOL:
        s->valor.valor_bool = (yyvsp[0].no)->valor_int;
        break;
    case STRING:
        if ((yyvsp[0].no)->valor_string)
            s->valor.valor_string = strdup((yyvsp[0].no)->valor_string);
        break;
    case FLOAT:
        fprintf(stderr, "[WARN] FLOAT não implementado ainda.\n");
        break;
    default:
        break;
}
    free((yyvsp[-2].sval));
}
#line 1931 "parser/parser.tab.c"
    break;

  case 29: /* lista_identificadores: TOKEN_IDENTIFICADOR  */
#line 302 "parser/parser.y"
      {
          (yyval.no) = criarListaIds((yyvsp[0].sval));
      }
#line 1939 "parser/parser.tab.c"
    break;

  case 30: /* lista_identificadores: lista_identificadores TOKEN_DELIMITADOR_VIRGULA TOKEN_IDENTIFICADOR  */
#line 306 "parser/parser.y"
      {
          (yyval.no) = adicionaIdNaLista((yyvsp[-2].no), (yyvsp[0].sval));
      }
#line 1947 "parser/parser.tab.c"
    break;

  case 31: /* lista_expressoes: expressao  */
#line 313 "parser/parser.y"
      {
          (yyval.no) = criarListaExp((yyvsp[0].no));
      }
#line 1955 "parser/parser.tab.c"
    break;

  case 32: /* lista_expressoes: lista_expressoes TOKEN_DELIMITADOR_VIRGULA expressao  */
#line 317 "parser/parser.y"
      {
          (yyval.no) = adicionaExpNaLista((yyvsp[-2].no), (yyvsp[0].no));
      }
#line 1963 "parser/parser.tab.c"
    break;

  case 33: /* lista_argumentos: %empty  */
#line 325 "parser/parser.y"
        { (yyval.no) = NULL; }
#line 1969 "parser/parser.tab.c"
    break;

  case 34: /* lista_argumentos: expressao  */
#line 327 "parser/parser.y"
        { (yyval.no) = criarListaExp((yyvsp[0].no)); }
#line 1975 "parser/parser.tab.c"
    break;

  case 35: /* lista_argumentos: lista_argumentos TOKEN_DELIMITADOR_VIRGULA expressao  */
#line 329 "parser/parser.y"
        { (yyval.no) = adicionaExpNaLista((yyvsp[-2].no), (yyvsp[0].no)); }
#line 1981 "parser/parser.tab.c"
    break;

  case 36: /* chamada_funcao: TOKEN_IDENTIFICADOR TOKEN_DELIMITADOR_ABRE_PARENTESES lista_argumentos TOKEN_DELIMITADOR_FECHA_PARENTESES  */
#line 334 "parser/parser.y"
        {
            NoAST *id = criarNoId((yyvsp[-3].sval));
            (yyval.no) = criarNoChamadaFuncao(id, (yyvsp[-1].no));
            free((yyvsp[-3].sval));
        }
#line 1991 "parser/parser.tab.c"
    break;

  case 37: /* expressao: expressao TOKEN_OPERADOR_MAIS expressao  */
#line 344 "parser/parser.y"
        { (yyval.no) = criarNoOp('+', (yyvsp[-2].no), (yyvsp[0].no)); }
#line 1997 "parser/parser.tab.c"
    break;

  case 38: /* expressao: expressao TOKEN_OPERADOR_MENOS expressao  */
#line 346 "parser/parser.y"
        { (yyval.no) = criarNoOp('-', (yyvsp[-2].no), (yyvsp[0].no)); }
#line 2003 "parser/parser.tab.c"
    break;

  case 39: /* expressao: expressao TOKEN_OPERADOR_MULTIPLICACAO expressao  */
#line 348 "parser/parser.y"
        { (yyval.no) = criarNoOp('*', (yyvsp[-2].no), (yyvsp[0].no)); }
#line 2009 "parser/parser.tab.c"
    break;

  case 40: /* expressao: expressao TOKEN_OPERADOR_DIVISAO expressao  */
#line 350 "parser/parser.y"
        { (yyval.no) = criarNoOp('/', (yyvsp[-2].no), (yyvsp[0].no)); }
#line 2015 "parser/parser.tab.c"
    break;

  case 41: /* expressao: expressao TOKEN_OPERADOR_IGUAL expressao  */
#line 352 "parser/parser.y"
        { (yyval.no) = criarNoOp('=', (yyvsp[-2].no), (yyvsp[0].no)); }
#line 2021 "parser/parser.tab.c"
    break;

  case 42: /* expressao: expressao TOKEN_OPERADOR_DIFERENTE expressao  */
#line 354 "parser/parser.y"
        { (yyval.no) = criarNoOp('!', (yyvsp[-2].no), (yyvsp[0].no)); }
#line 2027 "parser/parser.tab.c"
    break;

  case 43: /* expressao: expressao TOKEN_OPERADOR_MENOR expressao  */
#line 356 "parser/parser.y"
        { (yyval.no) = criarNoOp('<', (yyvsp[-2].no), (yyvsp[0].no)); }
#line 2033 "parser/parser.tab.c"
    break;

  case 44: /* expressao: expressao TOKEN_OPERADOR_MENOR_IGUAL expressao  */
#line 358 "parser/parser.y"
        { (yyval.no) = criarNoOp('l', (yyvsp[-2].no), (yyvsp[0].no)); }
#line 2039 "parser/parser.tab.c"
    break;

  case 45: /* expressao: expressao TOKEN_OPERADOR_MAIOR expressao  */
#line 360 "parser/parser.y"
        { (yyval.no) = criarNoOp('>', (yyvsp[-2].no), (yyvsp[0].no)); }
#line 2045 "parser/parser.tab.c"
    break;

  case 46: /* expressao: expressao TOKEN_OPERADOR_MAIOR_IGUAL expressao  */
#line 362 "parser/parser.y"
        { (yyval.no) = criarNoOp('g', (yyvsp[-2].no), (yyvsp[0].no)); }
#line 2051 "parser/parser.tab.c"
    break;

  case 47: /* expressao: expressao TOKEN_OPERADOR_LOGICO_AND expressao  */
#line 364 "parser/parser.y"
        { (yyval.no) = criarNoOpLogicaAnd((yyvsp[-2].no), (yyvsp[0].no)); }
#line 2057 "parser/parser.tab.c"
    break;

  case 48: /* expressao: expressao TOKEN_OPERADOR_LOGICO_OR expressao  */
#line 366 "parser/parser.y"
        { (yyval.no) = criarNoOpLogicaOr((yyvsp[-2].no), (yyvsp[0].no)); }
#line 2063 "parser/parser.tab.c"
    break;

  case 49: /* expressao: TOKEN_OPERADOR_LOGICO_NOT expressao  */
#line 368 "parser/parser.y"
        { (yyval.no) = criarNoOp('N', (yyvsp[0].no), NULL); }
#line 2069 "parser/parser.tab.c"
    break;

  case 50: /* expressao: atomo  */
#line 370 "parser/parser.y"
        { (yyval.no) = (yyvsp[0].no); }
#line 2075 "parser/parser.tab.c"
    break;

  case 51: /* atomo: TOKEN_DELIMITADOR_ABRE_PARENTESES expressao TOKEN_DELIMITADOR_FECHA_PARENTESES  */
#line 377 "parser/parser.y"
        { (yyval.no) = (yyvsp[-1].no); }
#line 2081 "parser/parser.tab.c"
    break;

  case 52: /* atomo: TOKEN_INTEIRO  */
#line 379 "parser/parser.y"
        { (yyval.no) = criarNoNum((yyvsp[0].ival)); }
#line 2087 "parser/parser.tab.c"
    break;

  case 53: /* atomo: TOKEN_FLOAT  */
#line 381 "parser/parser.y"
        { (yyval.no) = criarNoFloat((yyvsp[0].dval)); }
#line 2093 "parser/parser.tab.c"
    break;

  case 54: /* atomo: TOKEN_IDENTIFICADOR  */
#line 383 "parser/parser.y"
        {
            (yyval.no) = criarNoId((yyvsp[0].sval));

            Simbolo *s = searchST((yyvsp[0].sval));
            if (!s) {
                fprintf(stderr, "[ERRO] Variável '%s' usada antes de ser declarada (linha %d)\n", (yyvsp[0].sval), yylineno);
                insertST((yyvsp[0].sval), NONE);
            }

            free((yyvsp[0].sval));
        }
#line 2109 "parser/parser.tab.c"
    break;

  case 55: /* atomo: TOKEN_STRING  */
#line 395 "parser/parser.y"
        { (yyval.no) = criarNoString((yyvsp[0].sval)); free((yyvsp[0].sval)); }
#line 2115 "parser/parser.tab.c"
    break;

  case 56: /* atomo: TOKEN_PALAVRA_CHAVE_TRUE  */
#line 397 "parser/parser.y"
        { (yyval.no) = criarNoBool((yyvsp[0].ival)); }
#line 2121 "parser/parser.tab.c"
    break;

  case 57: /* atomo: TOKEN_PALAVRA_CHAVE_FALSE  */
#line 399 "parser/parser.y"
        { (yyval.no) = criarNoBool((yyvsp[0].ival)); }
#line 2127 "parser/parser.tab.c"
    break;

  case 58: /* atomo: TOKEN_DELIMITADOR_ABRE_COLCHETES lista_valores TOKEN_DELIMITADOR_FECHA_COLCHETES  */
#line 401 "parser/parser.y"
        {
            (yyval.no) = criarNoLista((yyvsp[-1].no), NULL);
        }
#line 2135 "parser/parser.tab.c"
    break;

  case 59: /* atomo: chamada_index  */
#line 405 "parser/parser.y"
        { (yyval.no) = (yyvsp[0].no); }
#line 2141 "parser/parser.tab.c"
    break;

  case 60: /* atomo: chamada_funcao  */
#line 407 "parser/parser.y"
        { (yyval.no) = (yyvsp[0].no); }
#line 2147 "parser/parser.tab.c"
    break;

  case 61: /* lista_valores: %empty  */
#line 412 "parser/parser.y"
                           { (yyval.no) = NULL; }
#line 2153 "parser/parser.tab.c"
    break;

  case 62: /* lista_valores: lista_expressoes  */
#line 413 "parser/parser.y"
                           { (yyval.no) = (yyvsp[0].no); }
#line 2159 "parser/parser.tab.c"
    break;

  case 63: /* chamada_index: atomo TOKEN_DELIMITADOR_ABRE_COLCHETES expressao TOKEN_DELIMITADOR_FECHA_COLCHETES  */
#line 419 "parser/parser.y"
        {
            (yyval.no) = criarNoIndex((yyvsp[-3].no), (yyvsp[-1].no)); /* cria nó AST de indexação: $1[$3] */
        }
#line 2167 "parser/parser.tab.c"
    break;

  case 64: /* bloco: TOKEN_NEWLINE TOKEN_INDENT lista_comandos TOKEN_DEDENT  */
#line 427 "parser/parser.y"
    {
        (yyval.no) = (yyvsp[-1].no); // Apenas retorna a lista de comandos
    }
#line 2175 "parser/parser.tab.c"
    break;

  case 65: /* if_stmt: TOKEN_PALAVRA_CHAVE_IF expressao TOKEN_DELIMITADOR_DOIS_PONTOS bloco  */
#line 437 "parser/parser.y"
    {
        (yyval.no) = criarNoIf((yyvsp[-2].no), (yyvsp[0].no), NULL);
    }
#line 2183 "parser/parser.tab.c"
    break;

  case 66: /* if_stmt: TOKEN_PALAVRA_CHAVE_IF expressao TOKEN_DELIMITADOR_DOIS_PONTOS bloco TOKEN_PALAVRA_CHAVE_ELIF expressao TOKEN_DELIMITADOR_DOIS_PONTOS bloco  */
#line 444 "parser/parser.y"
    {
        NoAST *elif_if = criarNoIf((yyvsp[-2].no), (yyvsp[0].no), NULL);
        (yyval.no) = criarNoIf((yyvsp[-6].no), (yyvsp[-4].no), elif_if);
    }
#line 2192 "parser/parser.tab.c"
    break;

  case 67: /* if_stmt: TOKEN_PALAVRA_CHAVE_IF expressao TOKEN_DELIMITADOR_DOIS_PONTOS bloco TOKEN_PALAVRA_CHAVE_ELIF expressao TOKEN_DELIMITADOR_DOIS_PONTOS bloco TOKEN_PALAVRA_CHAVE_ELSE TOKEN_DELIMITADOR_DOIS_PONTOS bloco  */
#line 453 "parser/parser.y"
    {
        NoAST *elif_if = criarNoIf((yyvsp[-5].no), (yyvsp[-3].no), (yyvsp[0].no));
        (yyval.no) = criarNoIf((yyvsp[-9].no), (yyvsp[-7].no), elif_if);
    }
#line 2201 "parser/parser.tab.c"
    break;

  case 68: /* if_stmt: TOKEN_PALAVRA_CHAVE_IF expressao TOKEN_DELIMITADOR_DOIS_PONTOS bloco TOKEN_PALAVRA_CHAVE_ELSE TOKEN_DELIMITADOR_DOIS_PONTOS bloco  */
#line 461 "parser/parser.y"
    {
        (yyval.no) = criarNoIf((yyvsp[-5].no), (yyvsp[-3].no), (yyvsp[0].no));
    }
#line 2209 "parser/parser.tab.c"
    break;

  case 69: /* $@2: %empty  */
#line 469 "parser/parser.y"
    {
        openScope();
    }
#line 2217 "parser/parser.tab.c"
    break;

  case 70: /* while_stmt: TOKEN_PALAVRA_CHAVE_WHILE expressao TOKEN_DELIMITADOR_DOIS_PONTOS $@2 bloco  */
#line 473 "parser/parser.y"
    {
        closeScope();
        (yyval.no) = criarNoWhile((yyvsp[-3].no), (yyvsp[0].no));
    }
#line 2226 "parser/parser.tab.c"
    break;

  case 71: /* $@3: %empty  */
#line 489 "parser/parser.y"
    {
        openScope();
        
        if (!searchST((yyvsp[-3].sval))) {
            insertST((yyvsp[-3].sval), INT);
        }
    }
#line 2238 "parser/parser.tab.c"
    break;

  case 72: /* for_stmt: TOKEN_PALAVRA_CHAVE_FOR TOKEN_IDENTIFICADOR TOKEN_PALAVRA_CHAVE_IN expressao TOKEN_DELIMITADOR_DOIS_PONTOS $@3 bloco  */
#line 497 "parser/parser.y"
    {
        closeScope();
        (yyval.no) = criarNoFor(criarNoId((yyvsp[-5].sval)), (yyvsp[-3].no), (yyvsp[0].no));
        free((yyvsp[-5].sval));
    }
#line 2248 "parser/parser.tab.c"
    break;


#line 2252 "parser/parser.tab.c"

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
  *++yylsp = yyloc;

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 503 "parser/parser.y"



void yyerror(const char *s) {
  fprintf(stderr, "ERRO SINTÁTICO (linha %d): %s\n", yylineno, s);
}

int main(void) {
    initST();
    inicializa_pilha();
    yylineno = 1;

    int result = yyparse();
    if (result == 0) {
        printf("Parsing concluído com sucesso!\n");

        /* --- AST --- */
        printf("\n--- ÁRVORE SINTÁTICA ABSTRATA (AST) ---\n");
        if (raizAST) {
            imprimirAST(raizAST, 0);
        } else {
            printf("(AST está vazia)\n");
        }
        printf("---------------------------------------\n");

        /* --- Execução da AST --- */
        printf("\n--- EXECUÇÃO DA AST ---\n");
        if (raizAST) {
            executarAST(raizAST);
        }

        /* --- Tabela de Símbolos --- */
        printf("\n--- TABELA DE SÍMBOLOS ---\n");
        showST();

        /* --- TAC --- */
        if (raizAST) {
            printf("\n--- CÓDIGO INTERMEDIÁRIO (TAC) ---\n");
            TacCodigo* codigo = gerar_tac(raizAST);
            if (codigo) {
                imprimir_tac(codigo);

                /* --- Código Final em C --- */
                printf("\n--- GERAÇÃO DE CÓDIGO FINAL ---\n");
                FILE* out = fopen("programa_gerado.c", "w");
                if (out) {
                    gerar_codigo_final(codigo, out);
                    fclose(out);
                    printf("[INFO] Código C gerado em 'programa_gerado.c'.\n");
                } else {
                    fprintf(stderr, "[ERRO] Não foi possível criar 'programa_gerado.c'.\n");
                }
                printf("-----------------------------------\n");

                liberar_tac(codigo);
            } else {
                printf("(Código TAC vazio)\n");
            }
        }

        /* --- Limpeza --- */
        freeST();
        if (raizAST) {
            liberarAST(raizAST);
        }

    } else {
        printf("Parsing interrompido por erro.\n");
    }

    return result;
}
