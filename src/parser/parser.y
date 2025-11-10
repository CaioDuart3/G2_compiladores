%{
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

  NoAST *raizAST = NULL;
%}

%define parse.trace
%locations

%union {
    int ival;
    char *sval;
    struct NoAST *no;
}

%token <ival> TOKEN_INTEIRO
%token <sval> TOKEN_IDENTIFICADOR TOKEN_STRING
%token <ival> TOKEN_PALAVRA_CHAVE_TRUE TOKEN_PALAVRA_CHAVE_FALSE
%token TOKEN_FLOAT
%token TOKEN_PALAVRA_CHAVE_IF TOKEN_PALAVRA_CHAVE_ELSE TOKEN_PALAVRA_CHAVE_ELIF
%token TOKEN_PALAVRA_CHAVE_WHILE TOKEN_PALAVRA_CHAVE_FOR TOKEN_PALAVRA_CHAVE_DEF TOKEN_PALAVRA_CHAVE_RETURN TOKEN_PALAVRA_CHAVE_IN
%token TOKEN_OPERADOR_IGUAL TOKEN_OPERADOR_DIFERENTE TOKEN_OPERADOR_MENOR_IGUAL TOKEN_OPERADOR_MAIOR_IGUAL
%token TOKEN_OPERADOR_MENOR TOKEN_OPERADOR_MAIOR
%token TOKEN_OPERADOR_ATRIBUICAO
%token TOKEN_OPERADOR_MAIS TOKEN_OPERADOR_MENOS TOKEN_OPERADOR_MULTIPLICAACAO TOKEN_OPERADOR_DIVISAO
%token TOKEN_DELIMITADOR_DOIS_PONTOS TOKEN_DELIMITADOR_VIRGULA
%token TOKEN_DELIMITADOR_ABRE_PARENTESES TOKEN_DELIMITADOR_FECHA_PARENTESES
%token TOKEN_DELIMITADOR_ABRE_CHAVES TOKEN_DELIMITADOR_FECHA_CHAVES
%token TOKEN_DELIMITADOR_ABRE_COLCHETES TOKEN_DELIMITADOR_FECHA_COLCHETES
%token TOKEN_DESCONHECIDO
%token TOKEN_NEWLINE TOKEN_INDENT TOKEN_DEDENT

%type <no> programa lista_comandos_opt lista_comandos comando atribuicao expressao atomo bloco if_stmt for_stmt

%left TOKEN_OPERADOR_MAIS TOKEN_OPERADOR_MENOS
%left TOKEN_OPERADOR_MULTIPLICAACAO TOKEN_OPERADOR_DIVISAO
%right TOKEN_OPERADOR_ATRIBUICAO
%nonassoc TOKEN_PALAVRA_CHAVE_ELSE

%%

programa:
    lista_comandos_opt 
    { 
        raizAST = $1;
        $$ = $1;
    }
  ;

lista_comandos_opt:
    /* vazio */         { $$ = NULL; }
  | lista_comandos      { $$ = $1; }
  ;

lista_comandos:
    comando              { $$ = $1; }
  | lista_comandos comando 
    {
        if ($2 != NULL) {
            if ($1 == NULL) {
                $$ = $2;
            } else {
                NoAST *tmp = $1;
                while (tmp->proximo) tmp = tmp->proximo;
                tmp->proximo = $2;
                $$ = $1;
            }
        } else $$ = $1;
    }
  ;

comando:
    atribuicao           { $$ = $1; }
  | expressao            { $$ = $1; }
  | if_stmt              { $$ = $1; }
  | for_stmt             { $$ = $1; }
  | bloco                { $$ = $1; }
  | TOKEN_NEWLINE        { $$ = NULL; }
  ;

atribuicao:
    TOKEN_IDENTIFICADOR TOKEN_OPERADOR_ATRIBUICAO expressao 
    { 
        Simbolo *s = searchST($1);
        if (!s) insertST($1, NONE);

        $$ = criarNoAtribuicao(criarNoId($1), $3);
        free($1);
    }
;

expressao:
    expressao TOKEN_OPERADOR_MAIS expressao
        { $$ = criarNoOp('+', $1, $3); }
  | expressao TOKEN_OPERADOR_MENOS expressao
        { $$ = criarNoOp('-', $1, $3); }
  | expressao TOKEN_OPERADOR_MULTIPLICAACAO expressao
        { $$ = criarNoOp('*', $1, $3); }
  | expressao TOKEN_OPERADOR_DIVISAO expressao
        { $$ = criarNoOp('/', $1, $3); }
  | atomo
        { $$ = $1; }
  ;

atomo:
    TOKEN_DELIMITADOR_ABRE_PARENTESES expressao TOKEN_DELIMITADOR_FECHA_PARENTESES
        { $$ = $2; }
  | TOKEN_INTEIRO
        { $$ = criarNoNum($1); }
  | TOKEN_IDENTIFICADOR
        {
            Simbolo *s = searchST($1);
            if (!s) insertST($1, NONE);
            $$ = criarNoId($1);
            free($1);
        }
  | TOKEN_STRING
        { $$ = criarNoString($1); free($1); }
  | TOKEN_PALAVRA_CHAVE_TRUE
        { $$ = criarNoBool(1); }
  | TOKEN_PALAVRA_CHAVE_FALSE
        { $$ = criarNoBool(0); }
  ;



bloco:
    TOKEN_NEWLINE TOKEN_INDENT lista_comandos TOKEN_DEDENT
    { $$ = $3; }
  ;

if_stmt:
    TOKEN_PALAVRA_CHAVE_IF expressao TOKEN_DELIMITADOR_DOIS_PONTOS bloco
        { $$ = criarNoIf($2, $4, NULL); }
  | TOKEN_PALAVRA_CHAVE_IF expressao TOKEN_DELIMITADOR_DOIS_PONTOS bloco TOKEN_PALAVRA_CHAVE_ELSE TOKEN_DELIMITADOR_DOIS_PONTOS bloco
        { $$ = criarNoIf($2, $4, $7); }
  ;


for_stmt:
    TOKEN_PALAVRA_CHAVE_FOR TOKEN_IDENTIFICADOR TOKEN_PALAVRA_CHAVE_IN expressao TOKEN_DELIMITADOR_DOIS_PONTOS bloco
    {
        Simbolo *s = searchST($2);
        if (!s) insertST($2, NONE);

        $$ = criarNoFor(criarNoId($2), $4, $6);
        free($2);
    }
  ;

%%

void yyerror(const char *s) {
  fprintf(stderr, "ERRO SINTÁTICO (linha %d): %s\n", yylineno, s);
}

int main(void) {
  extern int yydebug;
  yydebug = 1;

  inicializa_pilha();
  initST();
  yylineno = 1;

  int result = yyparse();

  if (result == 0) {
      printf("\nParsing concluído com sucesso!\n");
      printf("\n--- ÁRVORE SINTÁTICA ABSTRATA (AST) ---\n");
      if (raizAST) imprimirAST(raizAST, 0);
      else printf("(AST vazia)\n");

      printf("\n--- TABELA DE SÍMBOLOS ---\n");
      showST();

      liberarAST(raizAST);
      freeST();
  } else {
      printf("Parsing interrompido por erro.\n");
  }

  return result;
}
