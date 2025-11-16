/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_HOME_LARYSSA_DOCUMENTS_UNB_COMPILADORES_1_G2_COMPILADORES_SRC_PARSER_PARSER_TAB_H_INCLUDED
# define YY_YY_HOME_LARYSSA_DOCUMENTS_UNB_COMPILADORES_1_G2_COMPILADORES_SRC_PARSER_PARSER_TAB_H_INCLUDED
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
    TOKEN_OPERADOR_LOGICO_AND = 295, /* TOKEN_OPERADOR_LOGICO_AND  */
    TOKEN_OPERADOR_LOGICO_OR = 296, /* TOKEN_OPERADOR_LOGICO_OR  */
    TOKEN_OPERADOR_LOGICO_NOT = 297, /* TOKEN_OPERADOR_LOGICO_NOT  */
    LOWER_THAN_ELSE = 298          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 38 "/home/laryssa/Documents/unb/compiladores_1/G2_compiladores/src/parser/parser.y"

    int ival;            /* Para inteiros (TOKEN_INTEIRO) e Bools (0 ou 1) */
    char *sval;          /* Para strings (TOKEN_IDENTIFICADOR, TOKEN_STRING) */
    struct NoAST *no;    /* um ponteiro para um nó da AST */

#line 113 "/home/laryssa/Documents/unb/compiladores_1/G2_compiladores/src/parser/parser.tab.h"

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


#endif /* !YY_YY_HOME_LARYSSA_DOCUMENTS_UNB_COMPILADORES_1_G2_COMPILADORES_SRC_PARSER_PARSER_TAB_H_INCLUDED  */
