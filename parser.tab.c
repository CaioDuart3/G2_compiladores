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
#line 1 "src/parser/parser.y"

  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "../st/st.h"

  #include "../ast/ast.h"


  #define YYERROR_VERBOSE 1

  int yylex(void);
  void yyerror(const char *s);

  extern int yylineno;
  extern void inicializa_pilha();

  /* Variável global que guardará a raiz da nossa árvore */
  NoAST *raizAST = NULL;

#line 92 "parser.tab.c"

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


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOKEN_IDENTIFICADOR = 258,     /* TOKEN_IDENTIFICADOR  */
    TOKEN_STRING = 259,            /* TOKEN_STRING  */
    TOKEN_INTEIRO = 260,           /* TOKEN_INTEIRO  */
    TOKEN_PALAVRA_CHAVE_TRUE = 261, /* TOKEN_PALAVRA_CHAVE_TRUE  */
    TOKEN_PALAVRA_CHAVE_FALSE = 262, /* TOKEN_PALAVRA_CHAVE_FALSE  */
    TOKEN_FLOAT = 263,             /* TOKEN_FLOAT  */
    TOKEN_PALAVRA_CHAVE_IF = 264,  /* TOKEN_PALAVRA_CHAVE_IF  */
    TOKEN_PALAVRA_CHAVE_ELSE = 265, /* TOKEN_PALAVRA_CHAVE_ELSE  */
    TOKEN_PALAVRA_CHAVE_ELIF = 266, /* TOKEN_PALAVRA_CHAVE_ELIF  */
    TOKEN_PALAVRA_CHAVE_WHILE = 267, /* TOKEN_PALAVRA_CHAVE_WHILE  */
    TOKEN_PALAVRA_CHAVE_FOR = 268, /* TOKEN_PALAVRA_CHAVE_FOR  */
    TOKEN_PALAVRA_CHAVE_RETURN = 269, /* TOKEN_PALAVRA_CHAVE_RETURN  */
    TOKEN_PALAVRA_CHAVE_IN = 270,  /* TOKEN_PALAVRA_CHAVE_IN  */
    TOKEN_OPERADOR_IGUAL = 271,    /* TOKEN_OPERADOR_IGUAL  */
    TOKEN_OPERADOR_DIFERENTE = 272, /* TOKEN_OPERADOR_DIFERENTE  */
    TOKEN_OPERADOR_MENOR_IGUAL = 273, /* TOKEN_OPERADOR_MENOR_IGUAL  */
    TOKEN_OPERADOR_MAIOR_IGUAL = 274, /* TOKEN_OPERADOR_MAIOR_IGUAL  */
    TOKEN_OPERADOR_MENOR = 275,    /* TOKEN_OPERADOR_MENOR  */
    TOKEN_OPERADOR_MAIOR = 276,    /* TOKEN_OPERADOR_MAIOR  */
    TOKEN_OPERADOR_ATRIBUICAO = 277, /* TOKEN_OPERADOR_ATRIBUICAO  */
    TOKEN_OPERADOR_MAIS = 278,     /* TOKEN_OPERADOR_MAIS  */
    TOKEN_OPERADOR_MENOS = 279,    /* TOKEN_OPERADOR_MENOS  */
    TOKEN_OPERADOR_MULTIPLICACAO = 280, /* TOKEN_OPERADOR_MULTIPLICACAO  */
    TOKEN_OPERADOR_DIVISAO = 281,  /* TOKEN_OPERADOR_DIVISAO  */
    TOKEN_DELIMITADOR_DOIS_PONTOS = 282, /* TOKEN_DELIMITADOR_DOIS_PONTOS  */
    TOKEN_DELIMITADOR_VIRGULA = 283, /* TOKEN_DELIMITADOR_VIRGULA  */
    TOKEN_DELIMITADOR_ABRE_PARENTESES = 284, /* TOKEN_DELIMITADOR_ABRE_PARENTESES  */
    TOKEN_DELIMITADOR_FECHA_PARENTESES = 285, /* TOKEN_DELIMITADOR_FECHA_PARENTESES  */
    TOKEN_DELIMITADOR_ABRE_CHAVES = 286, /* TOKEN_DELIMITADOR_ABRE_CHAVES  */
    TOKEN_DELIMITADOR_FECHA_CHAVES = 287, /* TOKEN_DELIMITADOR_FECHA_CHAVES  */
    TOKEN_DELIMITADOR_ABRE_COLCHETES = 288, /* TOKEN_DELIMITADOR_ABRE_COLCHETES  */
    TOKEN_DELIMITADOR_FECHA_COLCHETES = 289, /* TOKEN_DELIMITADOR_FECHA_COLCHETES  */
    TOKEN_DESCONHECIDO = 290,      /* TOKEN_DESCONHECIDO  */
    TOKEN_NEWLINE = 291,           /* TOKEN_NEWLINE  */
    TOKEN_INDENT = 292,            /* TOKEN_INDENT  */
    TOKEN_DEDENT = 293,            /* TOKEN_DEDENT  */
    TOKEN_PALAVRA_CHAVE_DEF = 294, /* TOKEN_PALAVRA_CHAVE_DEF  */
    LOWER_THAN_ELSE = 295          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 29 "src/parser/parser.y"

    int ival;            /* Para inteiros (TOKEN_INTEIRO) e Bools (0 ou 1) */
    char *sval;          /* Para strings (TOKEN_IDENTIFICADOR, TOKEN_STRING) */
    struct NoAST *no;    /* O tipo mais importante: um ponteiro para um nó da AST */

#line 185 "parser.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (void);



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
  YYSYMBOL_LOWER_THAN_ELSE = 40,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 41,                  /* $accept  */
  YYSYMBOL_programa = 42,                  /* programa  */
  YYSYMBOL_newlines_opt = 43,              /* newlines_opt  */
  YYSYMBOL_lista_comandos_opt = 44,        /* lista_comandos_opt  */
  YYSYMBOL_lista_comandos = 45,            /* lista_comandos  */
  YYSYMBOL_comando = 46,                   /* comando  */
  YYSYMBOL_declaracao_funcao = 47,         /* declaracao_funcao  */
  YYSYMBOL_48_1 = 48,                      /* $@1  */
  YYSYMBOL_retorno = 49,                   /* retorno  */
  YYSYMBOL_atribuicao = 50,                /* atribuicao  */
  YYSYMBOL_atribuicao_indexacao = 51,      /* atribuicao_indexacao  */
  YYSYMBOL_atribuicao_simples = 52,        /* atribuicao_simples  */
  YYSYMBOL_atribuicao_multipla = 53,       /* atribuicao_multipla  */
  YYSYMBOL_atribuicao_encadeada = 54,      /* atribuicao_encadeada  */
  YYSYMBOL_lista_identificadores = 55,     /* lista_identificadores  */
  YYSYMBOL_lista_expressoes = 56,          /* lista_expressoes  */
  YYSYMBOL_lista_argumentos = 57,          /* lista_argumentos  */
  YYSYMBOL_chamada_funcao = 58,            /* chamada_funcao  */
  YYSYMBOL_expressao = 59,                 /* expressao  */
  YYSYMBOL_atomo = 60,                     /* atomo  */
  YYSYMBOL_lista_valores = 61,             /* lista_valores  */
  YYSYMBOL_chamada_index = 62,             /* chamada_index  */
  YYSYMBOL_bloco = 63,                     /* bloco  */
  YYSYMBOL_if_stmt = 64,                   /* if_stmt  */
  YYSYMBOL_65_2 = 65,                      /* $@2  */
  YYSYMBOL_66_3 = 66,                      /* $@3  */
  YYSYMBOL_67_4 = 67,                      /* $@4  */
  YYSYMBOL_68_5 = 68,                      /* $@5  */
  YYSYMBOL_while_stmt = 69,                /* while_stmt  */
  YYSYMBOL_70_6 = 70,                      /* $@6  */
  YYSYMBOL_for_stmt = 71,                  /* for_stmt  */
  YYSYMBOL_72_7 = 72                       /* $@7  */
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
#define YYFINAL  48
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   227

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  122

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   295


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
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    95,    95,   102,   104,   108,   109,   116,   118,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   142,   141,
     161,   170,   171,   172,   173,   177,   191,   233,   240,   285,
     289,   296,   300,   310,   311,   313,   318,   328,   330,   332,
     334,   336,   338,   340,   342,   344,   346,   348,   357,   359,
     361,   373,   375,   377,   379,   383,   385,   391,   392,   397,
     407,   415,   414,   427,   431,   435,   426,   448,   447,   460,
     459
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
  "TOKEN_PALAVRA_CHAVE_DEF", "LOWER_THAN_ELSE", "$accept", "programa",
  "newlines_opt", "lista_comandos_opt", "lista_comandos", "comando",
  "declaracao_funcao", "$@1", "retorno", "atribuicao",
  "atribuicao_indexacao", "atribuicao_simples", "atribuicao_multipla",
  "atribuicao_encadeada", "lista_identificadores", "lista_expressoes",
  "lista_argumentos", "chamada_funcao", "expressao", "atomo",
  "lista_valores", "chamada_index", "bloco", "if_stmt", "$@2", "$@3",
  "$@4", "$@5", "while_stmt", "$@6", "for_stmt", "$@7", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-37)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-30)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      66,    -9,   -37,   -37,   -37,   -37,    83,    83,     8,    83,
      83,    83,   -23,    15,    22,   -37,    66,   -37,   -37,   -37,
     -37,   -37,   -37,   -37,   -37,    -1,   -37,   184,    -7,   -37,
     -37,   -37,   -37,   -37,   103,    83,    83,     2,   148,   160,
      19,   184,   133,    16,   184,     6,    66,    14,   -37,    10,
     -37,    83,    59,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,   -37,   184,    -5,   184,   101,   -37,
     -37,    83,   -37,    83,   -37,     3,    60,   -37,    16,   -37,
     193,   193,   201,    68,   201,    68,    12,    12,   -37,   -37,
     121,    83,   -37,    42,    30,    30,    30,   172,   184,   -37,
     -37,     5,   -37,   184,    83,   -23,   -37,   -37,   -37,   -37,
      41,   184,    64,    30,   -37,    49,   -37,    30,   -37,   -37,
      30,   -37
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,    50,    51,    49,    52,    53,     0,     0,     0,     0,
       0,    57,    14,     0,     0,     3,     6,     7,    16,    17,
       9,    24,    21,    22,    23,     0,    56,    10,    47,    55,
      15,    11,    12,    13,     0,    33,     0,    50,     0,     0,
       0,    20,     0,    58,    31,     0,     0,     0,     1,     2,
       8,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    28,    26,     0,    34,     0,    61,
      67,     0,    48,     0,    54,     0,     0,     4,    27,    30,
      41,    42,    44,    46,    43,    45,    37,    38,    39,    40,
       0,     0,    36,     0,     0,     0,     0,     0,    32,    60,
      29,     0,    59,    35,     0,     0,    62,    64,    68,    69,
       0,    25,     0,     0,    18,     0,    70,     0,    65,    19,
       0,    66
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -37,   -37,   -37,   -37,    36,   -14,   -37,   -37,   -37,    62,
     -37,   -37,   -37,   -37,     7,    46,   -37,   -37,    -6,   -37,
     -37,   -37,   -36,   -37,   -37,   -37,   -37,   -37,   -37,   -37,
     -37,   -37
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    14,    49,    15,    16,    17,    18,   117,    19,    20,
      21,    22,    23,    24,    25,    43,    66,    26,    27,    28,
      45,    29,    30,    31,    94,    95,   112,   120,    32,    96,
      33,   113
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      38,    39,    50,    41,    42,    44,     1,     2,     3,     4,
       5,    40,     6,    34,    46,     7,     8,     9,    47,   -29,
      35,    51,    48,    91,    36,    92,    63,    52,    65,    67,
      68,    35,    10,    52,    71,   110,    11,    61,    62,    12,
      74,    99,    13,    76,    73,    44,    77,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,   106,   107,
     108,    50,    79,   100,   104,    97,   105,    98,   114,     1,
       2,     3,     4,     5,   115,     6,   118,   116,     7,     8,
       9,   119,    75,   101,   121,   103,    37,     2,     3,     4,
       5,    59,    60,    61,    62,    10,    64,    78,   111,    11,
       0,     0,    12,     0,     0,    13,     1,     2,     3,     4,
       5,     0,    10,     0,     0,     0,    11,    53,    54,    55,
      56,    57,    58,     0,    59,    60,    61,    62,     0,     0,
       0,     0,    10,     0,     0,    93,    11,    53,    54,    55,
      56,    57,    58,     0,    59,    60,    61,    62,     0,    53,
      54,    55,    56,    57,    58,   102,    59,    60,    61,    62,
       0,     0,     0,    72,    53,    54,    55,    56,    57,    58,
       0,    59,    60,    61,    62,    69,    53,    54,    55,    56,
      57,    58,     0,    59,    60,    61,    62,    70,    53,    54,
      55,    56,    57,    58,     0,    59,    60,    61,    62,   109,
      53,    54,    55,    56,    57,    58,     0,    59,    60,    61,
      62,    55,    56,    57,    58,     0,    59,    60,    61,    62,
      56,     0,    58,     0,    59,    60,    61,    62
};

static const yytype_int8 yycheck[] =
{
       6,     7,    16,     9,    10,    11,     3,     4,     5,     6,
       7,     3,     9,    22,    37,    12,    13,    14,     3,    28,
      29,    22,     0,    28,    33,    30,    33,    28,    34,    35,
      36,    29,    29,    28,    15,    30,    33,    25,    26,    36,
      34,    38,    39,    29,    28,    51,    36,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    94,    95,
      96,    75,     3,     3,    22,    71,    36,    73,    27,     3,
       4,     5,     6,     7,    10,     9,    27,   113,    12,    13,
      14,   117,    46,    76,   120,    91,     3,     4,     5,     6,
       7,    23,    24,    25,    26,    29,    34,    51,   104,    33,
      -1,    -1,    36,    -1,    -1,    39,     3,     4,     5,     6,
       7,    -1,    29,    -1,    -1,    -1,    33,    16,    17,    18,
      19,    20,    21,    -1,    23,    24,    25,    26,    -1,    -1,
      -1,    -1,    29,    -1,    -1,    34,    33,    16,    17,    18,
      19,    20,    21,    -1,    23,    24,    25,    26,    -1,    16,
      17,    18,    19,    20,    21,    34,    23,    24,    25,    26,
      -1,    -1,    -1,    30,    16,    17,    18,    19,    20,    21,
      -1,    23,    24,    25,    26,    27,    16,    17,    18,    19,
      20,    21,    -1,    23,    24,    25,    26,    27,    16,    17,
      18,    19,    20,    21,    -1,    23,    24,    25,    26,    27,
      16,    17,    18,    19,    20,    21,    -1,    23,    24,    25,
      26,    18,    19,    20,    21,    -1,    23,    24,    25,    26,
      19,    -1,    21,    -1,    23,    24,    25,    26
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     9,    12,    13,    14,
      29,    33,    36,    39,    42,    44,    45,    46,    47,    49,
      50,    51,    52,    53,    54,    55,    58,    59,    60,    62,
      63,    64,    69,    71,    22,    29,    33,     3,    59,    59,
       3,    59,    59,    56,    59,    61,    37,     3,     0,    43,
      46,    22,    28,    16,    17,    18,    19,    20,    21,    23,
      24,    25,    26,    33,    50,    59,    57,    59,    59,    27,
      27,    15,    30,    28,    34,    45,    29,    36,    56,     3,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    28,    30,    34,    65,    66,    70,    59,    59,    38,
       3,    55,    34,    59,    22,    36,    63,    63,    63,    27,
      30,    59,    67,    72,    27,    10,    63,    48,    27,    63,
      68,    63
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    42,    43,    43,    44,    44,    45,    45,    46,
      46,    46,    46,    46,    46,    46,    46,    46,    48,    47,
      49,    50,    50,    50,    50,    51,    52,    53,    54,    55,
      55,    56,    56,    57,    57,    57,    58,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    61,    61,    62,
      63,    65,    64,    66,    67,    68,    64,    70,    69,    72,
      71
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     0,     2,     0,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     8,
       2,     1,     1,     1,     1,     6,     3,     3,     3,     1,
       3,     1,     3,     0,     1,     3,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     3,     1,
       1,     1,     1,     1,     3,     1,     1,     0,     1,     4,
       4,     0,     5,     0,     0,     0,    10,     0,     5,     0,
       7
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
#line 96 "src/parser/parser.y"
    { 
        raizAST = (yyvsp[-1].no); /* Salva a raiz global */
        (yyval.no) = (yyvsp[-1].no);
    }
#line 1760 "parser.tab.c"
    break;

  case 5: /* lista_comandos_opt: %empty  */
#line 108 "src/parser/parser.y"
                        { (yyval.no) = NULL; }
#line 1766 "parser.tab.c"
    break;

  case 6: /* lista_comandos_opt: lista_comandos  */
#line 109 "src/parser/parser.y"
                      { (yyval.no) = (yyvsp[0].no); }
#line 1772 "parser.tab.c"
    break;

  case 7: /* lista_comandos: comando  */
#line 117 "src/parser/parser.y"
        { (yyval.no) = criarNoLista((yyvsp[0].no), NULL); }
#line 1778 "parser.tab.c"
    break;

  case 8: /* lista_comandos: lista_comandos comando  */
#line 119 "src/parser/parser.y"
        {
            if ((yyvsp[0].no) != NULL)
                (yyval.no) = criarNoLista((yyvsp[-1].no), (yyvsp[0].no));
            else
                (yyval.no) = (yyvsp[-1].no);
        }
#line 1789 "parser.tab.c"
    break;

  case 9: /* comando: atribuicao  */
#line 128 "src/parser/parser.y"
                         { (yyval.no) = (yyvsp[0].no); }
#line 1795 "parser.tab.c"
    break;

  case 10: /* comando: expressao  */
#line 129 "src/parser/parser.y"
                         { (yyval.no) = (yyvsp[0].no); }
#line 1801 "parser.tab.c"
    break;

  case 11: /* comando: if_stmt  */
#line 130 "src/parser/parser.y"
                         { (yyval.no) = (yyvsp[0].no); }
#line 1807 "parser.tab.c"
    break;

  case 12: /* comando: while_stmt  */
#line 131 "src/parser/parser.y"
                         { (yyval.no) = (yyvsp[0].no); }
#line 1813 "parser.tab.c"
    break;

  case 13: /* comando: for_stmt  */
#line 132 "src/parser/parser.y"
                         { (yyval.no) = (yyvsp[0].no); }
#line 1819 "parser.tab.c"
    break;

  case 14: /* comando: TOKEN_NEWLINE  */
#line 133 "src/parser/parser.y"
                         { (yyval.no) = NULL; }
#line 1825 "parser.tab.c"
    break;

  case 15: /* comando: bloco  */
#line 134 "src/parser/parser.y"
                         { (yyval.no) = (yyvsp[0].no); }
#line 1831 "parser.tab.c"
    break;

  case 16: /* comando: declaracao_funcao  */
#line 135 "src/parser/parser.y"
                         { (yyval.no) = (yyvsp[0].no); }
#line 1837 "parser.tab.c"
    break;

  case 17: /* comando: retorno  */
#line 136 "src/parser/parser.y"
                         { (yyval.no) = (yyvsp[0].no); }
#line 1843 "parser.tab.c"
    break;

  case 18: /* $@1: %empty  */
#line 142 "src/parser/parser.y"
    {
        
        openScope();

        
        registrarParametros((yyvsp[-2].no)); 
    }
#line 1855 "parser.tab.c"
    break;

  case 19: /* declaracao_funcao: TOKEN_PALAVRA_CHAVE_DEF TOKEN_IDENTIFICADOR TOKEN_DELIMITADOR_ABRE_PARENTESES lista_identificadores TOKEN_DELIMITADOR_FECHA_PARENTESES TOKEN_DELIMITADOR_DOIS_PONTOS $@1 bloco  */
#line 150 "src/parser/parser.y"
    {
        // Ação 3: Executa DEPOIS do 'bloco' ser analisado
        closeScope();
        
        // Ação 4: Agora sim, cria o nó da função
        (yyval.no) = criarNoFuncao((yyvsp[-6].sval), (yyvsp[-4].no), (yyvsp[0].no)); // $8 é o 'bloco'
        insertST((yyvsp[-6].sval), FUNCAO); // Insere o nome da função no escopo *anterior*
    }
#line 1868 "parser.tab.c"
    break;

  case 20: /* retorno: TOKEN_PALAVRA_CHAVE_RETURN expressao  */
#line 162 "src/parser/parser.y"
    {
        (yyval.no) = criarNoReturn((yyvsp[0].no));
    }
#line 1876 "parser.tab.c"
    break;

  case 25: /* atribuicao_indexacao: TOKEN_IDENTIFICADOR TOKEN_DELIMITADOR_ABRE_COLCHETES expressao TOKEN_DELIMITADOR_FECHA_COLCHETES TOKEN_OPERADOR_ATRIBUICAO expressao  */
#line 178 "src/parser/parser.y"
    {
        // $1 = char* (nome do vetor)
        // $3 = NoAST* (índice)
        // $6 = NoAST* (valor a atribuir)

        NoAST *no_index = criarNoIndex(criarNoId((yyvsp[-5].sval)), (yyvsp[-3].no)); // cria vetor_int[0]
        (yyval.no) = criarNoAtribuicao(no_index, (yyvsp[0].no));              // cria vetor_int[0] = 0

        free((yyvsp[-5].sval)); // libera string
    }
#line 1891 "parser.tab.c"
    break;

  case 26: /* atribuicao_simples: TOKEN_IDENTIFICADOR TOKEN_OPERADOR_ATRIBUICAO expressao  */
#line 192 "src/parser/parser.y"
{
    (yyval.no) = criarNoAtribuicao(criarNoId((yyvsp[-2].sval)), (yyvsp[0].no));

    Simbolo *s = searchST((yyvsp[-2].sval));
    if (!s) {
        insertST((yyvsp[-2].sval), inferirTipo((yyvsp[0].no)));
        s = searchST((yyvsp[-2].sval));
    }

    s->inicializado = true;

    // Se for lista, cria vetor
    if ((yyvsp[0].no)->tipo == NO_LISTA) {
        int tamanho = 0;
        NoAST *elem = (yyvsp[0].no);
        while(elem) { tamanho++; elem = elem->proximo; }
        s->vetor = malloc(sizeof(int) * tamanho);
        s->tamanho = tamanho;
        elem = (yyvsp[0].no);
        for(int i=0; i<tamanho; i++, elem=elem->proximo)
            s->vetor[i] = elem->valor_int;
    }

    // Avalia expressões
    switch(s->tipo) {
        case INT:
        case BOOL:
            s->valor.valor_int = avaliarExpressao((yyvsp[0].no));
            break;
        case STRING:
            if ((yyvsp[0].no)->valor_string) s->valor.valor_string = strdup((yyvsp[0].no)->valor_string);
            break;
        default:
            break;
    }

    free((yyvsp[-2].sval));
}
#line 1934 "parser.tab.c"
    break;

  case 27: /* atribuicao_multipla: lista_identificadores TOKEN_OPERADOR_ATRIBUICAO lista_expressoes  */
#line 234 "src/parser/parser.y"
      {
          (yyval.no) = criarNoAtribuicaoMultipla((yyvsp[-2].no), (yyvsp[0].no));
      }
#line 1942 "parser.tab.c"
    break;

  case 28: /* atribuicao_encadeada: TOKEN_IDENTIFICADOR TOKEN_OPERADOR_ATRIBUICAO atribuicao  */
#line 241 "src/parser/parser.y"
{
    (yyval.no) = criarNoAtribuicao(criarNoId((yyvsp[-2].sval)), (yyvsp[0].no));

    // Todos os nós da cadeia de atribuição
    NoAST *rhs = (yyvsp[0].no);

    while (rhs->tipo == NO_ATRIBUICAO) {
        rhs = rhs->filho2; // vai para o próximo RHS
    }

    // Inferir tipo do RHS final
    Tipo t = inferirTipo(rhs);

    // Atualizar ST para o LHS
    Simbolo *s = searchST((yyvsp[-2].sval));
    if (!s) insertST((yyvsp[-2].sval), t);
    else s->tipo = t;

    // Atualizar valor do LHS com nomes corretos do union
switch (t) {
    case INT:
        s->valor.valor_int = (yyvsp[0].no)->valor_int; // $3 é NoAST*, NO_NUM
        break;
    case BOOL:
        s->valor.valor_bool = (yyvsp[0].no)->valor_int; // NO_BOOL armazena booleano em valor_int
        break;
    case STRING:
        if ((yyvsp[0].no)->valor_string)
            s->valor.valor_string = strdup((yyvsp[0].no)->valor_string); // NO_STRING ou NO_ID
        break;
    case FLOAT:
        fprintf(stderr, "[WARN] FLOAT não implementado ainda.\n");
        break;
    default:
        break;
}


    free((yyvsp[-2].sval));
}
#line 1987 "parser.tab.c"
    break;

  case 29: /* lista_identificadores: TOKEN_IDENTIFICADOR  */
#line 286 "src/parser/parser.y"
      {
          (yyval.no) = criarListaIds((yyvsp[0].sval));
      }
#line 1995 "parser.tab.c"
    break;

  case 30: /* lista_identificadores: lista_identificadores TOKEN_DELIMITADOR_VIRGULA TOKEN_IDENTIFICADOR  */
#line 290 "src/parser/parser.y"
      {
          (yyval.no) = adicionaIdNaLista((yyvsp[-2].no), (yyvsp[0].sval));
      }
#line 2003 "parser.tab.c"
    break;

  case 31: /* lista_expressoes: expressao  */
#line 297 "src/parser/parser.y"
      {
          (yyval.no) = criarListaExp((yyvsp[0].no));
      }
#line 2011 "parser.tab.c"
    break;

  case 32: /* lista_expressoes: lista_expressoes TOKEN_DELIMITADOR_VIRGULA expressao  */
#line 301 "src/parser/parser.y"
      {
          (yyval.no) = adicionaExpNaLista((yyvsp[-2].no), (yyvsp[0].no));
      }
#line 2019 "parser.tab.c"
    break;

  case 33: /* lista_argumentos: %empty  */
#line 310 "src/parser/parser.y"
        { (yyval.no) = NULL; }
#line 2025 "parser.tab.c"
    break;

  case 34: /* lista_argumentos: expressao  */
#line 312 "src/parser/parser.y"
        { (yyval.no) = criarListaExp((yyvsp[0].no)); }
#line 2031 "parser.tab.c"
    break;

  case 35: /* lista_argumentos: lista_argumentos TOKEN_DELIMITADOR_VIRGULA expressao  */
#line 314 "src/parser/parser.y"
        { (yyval.no) = adicionaExpNaLista((yyvsp[-2].no), (yyvsp[0].no)); }
#line 2037 "parser.tab.c"
    break;

  case 36: /* chamada_funcao: TOKEN_IDENTIFICADOR TOKEN_DELIMITADOR_ABRE_PARENTESES lista_argumentos TOKEN_DELIMITADOR_FECHA_PARENTESES  */
#line 319 "src/parser/parser.y"
        {
            NoAST *id = criarNoId((yyvsp[-3].sval));
            (yyval.no) = criarNoChamadaFuncao(id, (yyvsp[-1].no));
            free((yyvsp[-3].sval));
        }
#line 2047 "parser.tab.c"
    break;

  case 37: /* expressao: expressao TOKEN_OPERADOR_MAIS expressao  */
#line 329 "src/parser/parser.y"
        { (yyval.no) = criarNoOp('+', (yyvsp[-2].no), (yyvsp[0].no)); }
#line 2053 "parser.tab.c"
    break;

  case 38: /* expressao: expressao TOKEN_OPERADOR_MENOS expressao  */
#line 331 "src/parser/parser.y"
        { (yyval.no) = criarNoOp('-', (yyvsp[-2].no), (yyvsp[0].no)); }
#line 2059 "parser.tab.c"
    break;

  case 39: /* expressao: expressao TOKEN_OPERADOR_MULTIPLICACAO expressao  */
#line 333 "src/parser/parser.y"
        { (yyval.no) = criarNoOp('*', (yyvsp[-2].no), (yyvsp[0].no)); }
#line 2065 "parser.tab.c"
    break;

  case 40: /* expressao: expressao TOKEN_OPERADOR_DIVISAO expressao  */
#line 335 "src/parser/parser.y"
        { (yyval.no) = criarNoOp('/', (yyvsp[-2].no), (yyvsp[0].no)); }
#line 2071 "parser.tab.c"
    break;

  case 41: /* expressao: expressao TOKEN_OPERADOR_IGUAL expressao  */
#line 337 "src/parser/parser.y"
        { (yyval.no) = criarNoOp('=', (yyvsp[-2].no), (yyvsp[0].no)); }
#line 2077 "parser.tab.c"
    break;

  case 42: /* expressao: expressao TOKEN_OPERADOR_DIFERENTE expressao  */
#line 339 "src/parser/parser.y"
        { (yyval.no) = criarNoOp('!', (yyvsp[-2].no), (yyvsp[0].no)); }
#line 2083 "parser.tab.c"
    break;

  case 43: /* expressao: expressao TOKEN_OPERADOR_MENOR expressao  */
#line 341 "src/parser/parser.y"
        { (yyval.no) = criarNoOp('<', (yyvsp[-2].no), (yyvsp[0].no)); }
#line 2089 "parser.tab.c"
    break;

  case 44: /* expressao: expressao TOKEN_OPERADOR_MENOR_IGUAL expressao  */
#line 343 "src/parser/parser.y"
        { (yyval.no) = criarNoOp('l', (yyvsp[-2].no), (yyvsp[0].no)); }
#line 2095 "parser.tab.c"
    break;

  case 45: /* expressao: expressao TOKEN_OPERADOR_MAIOR expressao  */
#line 345 "src/parser/parser.y"
        { (yyval.no) = criarNoOp('>', (yyvsp[-2].no), (yyvsp[0].no)); }
#line 2101 "parser.tab.c"
    break;

  case 46: /* expressao: expressao TOKEN_OPERADOR_MAIOR_IGUAL expressao  */
#line 347 "src/parser/parser.y"
        { (yyval.no) = criarNoOp('g', (yyvsp[-2].no), (yyvsp[0].no)); }
#line 2107 "parser.tab.c"
    break;

  case 47: /* expressao: atomo  */
#line 349 "src/parser/parser.y"
        { (yyval.no) = (yyvsp[0].no); }
#line 2113 "parser.tab.c"
    break;

  case 48: /* atomo: TOKEN_DELIMITADOR_ABRE_PARENTESES expressao TOKEN_DELIMITADOR_FECHA_PARENTESES  */
#line 358 "src/parser/parser.y"
        { (yyval.no) = (yyvsp[-1].no); }
#line 2119 "parser.tab.c"
    break;

  case 49: /* atomo: TOKEN_INTEIRO  */
#line 360 "src/parser/parser.y"
        { (yyval.no) = criarNoNum((yyvsp[0].ival)); }
#line 2125 "parser.tab.c"
    break;

  case 50: /* atomo: TOKEN_IDENTIFICADOR  */
#line 362 "src/parser/parser.y"
        {
            (yyval.no) = criarNoId((yyvsp[0].sval));

            Simbolo *s = searchST((yyvsp[0].sval));
            if (!s) {
                fprintf(stderr, "[ERRO] Variável '%s' usada antes de ser declarada (linha %d)\n", (yyvsp[0].sval), yylineno);
                insertST((yyvsp[0].sval), NONE); // opcional para continuar parsing
            }

            free((yyvsp[0].sval));
        }
#line 2141 "parser.tab.c"
    break;

  case 51: /* atomo: TOKEN_STRING  */
#line 374 "src/parser/parser.y"
        { (yyval.no) = criarNoString((yyvsp[0].sval)); free((yyvsp[0].sval)); }
#line 2147 "parser.tab.c"
    break;

  case 52: /* atomo: TOKEN_PALAVRA_CHAVE_TRUE  */
#line 376 "src/parser/parser.y"
        { (yyval.no) = criarNoBool((yyvsp[0].ival)); }
#line 2153 "parser.tab.c"
    break;

  case 53: /* atomo: TOKEN_PALAVRA_CHAVE_FALSE  */
#line 378 "src/parser/parser.y"
        { (yyval.no) = criarNoBool((yyvsp[0].ival)); }
#line 2159 "parser.tab.c"
    break;

  case 54: /* atomo: TOKEN_DELIMITADOR_ABRE_COLCHETES lista_valores TOKEN_DELIMITADOR_FECHA_COLCHETES  */
#line 380 "src/parser/parser.y"
        {
            (yyval.no) = criarNoLista((yyvsp[-1].no), NULL); /* Lista literal */
        }
#line 2167 "parser.tab.c"
    break;

  case 55: /* atomo: chamada_index  */
#line 384 "src/parser/parser.y"
        { (yyval.no) = (yyvsp[0].no); }
#line 2173 "parser.tab.c"
    break;

  case 56: /* atomo: chamada_funcao  */
#line 386 "src/parser/parser.y"
        { (yyval.no) = (yyvsp[0].no); }
#line 2179 "parser.tab.c"
    break;

  case 57: /* lista_valores: %empty  */
#line 391 "src/parser/parser.y"
                           { (yyval.no) = NULL; }
#line 2185 "parser.tab.c"
    break;

  case 58: /* lista_valores: lista_expressoes  */
#line 392 "src/parser/parser.y"
                           { (yyval.no) = (yyvsp[0].no); }
#line 2191 "parser.tab.c"
    break;

  case 59: /* chamada_index: atomo TOKEN_DELIMITADOR_ABRE_COLCHETES expressao TOKEN_DELIMITADOR_FECHA_COLCHETES  */
#line 398 "src/parser/parser.y"
        {
            (yyval.no) = criarNoIndex((yyvsp[-3].no), (yyvsp[-1].no)); /* cria nó AST de indexação: $1[$3] */
        }
#line 2199 "parser.tab.c"
    break;

  case 60: /* bloco: TOKEN_NEWLINE TOKEN_INDENT lista_comandos TOKEN_DEDENT  */
#line 408 "src/parser/parser.y"
    {
        (yyval.no) = (yyvsp[-1].no);        // Apenas retorna a lista de comandos
    }
#line 2207 "parser.tab.c"
    break;

  case 61: /* $@2: %empty  */
#line 415 "src/parser/parser.y"
    {
        openScope();
    }
#line 2215 "parser.tab.c"
    break;

  case 62: /* if_stmt: TOKEN_PALAVRA_CHAVE_IF expressao TOKEN_DELIMITADOR_DOIS_PONTOS $@2 bloco  */
#line 419 "src/parser/parser.y"
    {
        closeScope();
        (yyval.no) = criarNoIf((yyvsp[-3].no), (yyvsp[0].no), NULL);
    }
#line 2224 "parser.tab.c"
    break;

  case 63: /* $@3: %empty  */
#line 427 "src/parser/parser.y"
    {
        openScope();
    }
#line 2232 "parser.tab.c"
    break;

  case 64: /* $@4: %empty  */
#line 431 "src/parser/parser.y"
    {
        closeScope();
    }
#line 2240 "parser.tab.c"
    break;

  case 65: /* $@5: %empty  */
#line 435 "src/parser/parser.y"
    {
        openScope();
    }
#line 2248 "parser.tab.c"
    break;

  case 66: /* if_stmt: TOKEN_PALAVRA_CHAVE_IF expressao TOKEN_DELIMITADOR_DOIS_PONTOS $@3 bloco $@4 TOKEN_PALAVRA_CHAVE_ELSE TOKEN_DELIMITADOR_DOIS_PONTOS $@5 bloco  */
#line 439 "src/parser/parser.y"
    {
        closeScope();
        (yyval.no) = criarNoIf((yyvsp[-8].no), (yyvsp[-5].no), (yyvsp[0].no));
    }
#line 2257 "parser.tab.c"
    break;

  case 67: /* $@6: %empty  */
#line 448 "src/parser/parser.y"
    {
        openScope(); // Abre o escopo ANTES do bloco
    }
#line 2265 "parser.tab.c"
    break;

  case 68: /* while_stmt: TOKEN_PALAVRA_CHAVE_WHILE expressao TOKEN_DELIMITADOR_DOIS_PONTOS $@6 bloco  */
#line 452 "src/parser/parser.y"
    {
        closeScope(); // Fecha o escopo DEPOIS do bloco
        (yyval.no) = criarNoWhile((yyvsp[-3].no), (yyvsp[0].no));
    }
#line 2274 "parser.tab.c"
    break;

  case 69: /* $@7: %empty  */
#line 460 "src/parser/parser.y"
    {
        openScope(); // Abre o escopo ANTES do bloco
        
        // Adiciona a variável de iteração ($2) ao *novo* escopo
        if (!searchST((yyvsp[-3].sval))) {
            insertST((yyvsp[-3].sval), INT); // Ou o tipo que você inferir da expressão $4
        }
        // Você pode querer marcar como inicializada aqui também
    }
#line 2288 "parser.tab.c"
    break;

  case 70: /* for_stmt: TOKEN_PALAVRA_CHAVE_FOR TOKEN_IDENTIFICADOR TOKEN_PALAVRA_CHAVE_IN expressao TOKEN_DELIMITADOR_DOIS_PONTOS $@7 bloco  */
#line 470 "src/parser/parser.y"
    {
        closeScope(); // Fecha o escopo DEPOIS do bloco
        (yyval.no) = criarNoFor(criarNoId((yyvsp[-5].sval)), (yyvsp[-3].no), (yyvsp[0].no));
        free((yyvsp[-5].sval));
    }
#line 2298 "parser.tab.c"
    break;


#line 2302 "parser.tab.c"

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

#line 477 "src/parser/parser.y"



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

        printf("\n--- ÁRVORE SINTÁTICA ABSTRATA (AST) ---\n");
        if (raizAST) {
            imprimirAST(raizAST, 0); // Imprime a árvore
        } else {
            printf("(AST está vazia)\n");
        }
        printf("---------------------------------------\n");

        printf("\n--- EXECUÇÃO DA AST ---\n");
        if (raizAST) {
            NoAST *cmd = raizAST;
            while (cmd) {
                // Executa comandos de atribuição
                if (cmd->tipo == NO_ATRIBUICAO || cmd->tipo == NO_ATRIBUICAO_MULTIPLA) {
                    executarAtribuicao(cmd);
                }
                // Para expressões isoladas, você pode avaliar e imprimir
                else if (cmd->tipo == NO_OP_BINARIA) {
                    int val = avaliarExpressao(cmd);
                    printf("Resultado da expressão: %d\n", val);
                }
                cmd = cmd->proximo;
            }
        }

        printf("\n--- TABELA DE SÍMBOLOS ---\n");
        showST();   // Mostra as variáveis e valores
        freeST();   // Libera a tabela de símbolos

        if (raizAST) {
            liberarAST(raizAST); // Libera a memória da AST após a execução
        }
    } else {
        printf("Parsing interrompido por erro.\n");
    }

    return result;
}
