%{
  #include <stdio.h>
  #include <stdlib.h>

  #define YYERROR_VERBOSE 1

  /* Definindo yylex e yyerror */
  int yylex(void);
  void yyerror(const char *s);

  extern char *yytext;
  extern int yylineno;
  extern void inicializa_pilha(); //colocamos extern para evitar warning: implicit declaration
%}

%define parse.trace
%locations


/* Tokens vindos do lexer */
%token TOKEN_IDENTIFICADOR TOKEN_INTEIRO TOKEN_FLOAT TOKEN_STRING
%token TOKEN_PALAVRA_CHAVE_IF TOKEN_PALAVRA_CHAVE_ELSE TOKEN_PALAVRA_CHAVE_ELIF
%token TOKEN_PALAVRA_CHAVE_WHILE TOKEN_PALAVRA_CHAVE_FOR TOKEN_PALAVRA_CHAVE_DEF TOKEN_PALAVRA_CHAVE_RETURN TOKEN_PALAVRA_CHAVE_IN
%token TOKEN_OPERADOR_IGUAL TOKEN_OPERADOR_DIFERENTE TOKEN_OPERADOR_MENOR_IGUAL TOKEN_OPERADOR_MAIOR_IGUAL
%token TOKEN_OPERADOR_MENOR TOKEN_OPERADOR_MAIOR
%token TOKEN_PALAVRA_CHAVE_TRUE TOKEN_PALAVRA_CHAVE_FALSE
%token TOKEN_OPERADOR_ATRIBUICAO
%token TOKEN_OPERADOR_MAIS TOKEN_OPERADOR_MENOS TOKEN_OPERADOR_MULTIPLICACAO TOKEN_OPERADOR_DIVISAO
%token TOKEN_DELIMITADOR_DOIS_PONTOS TOKEN_DELIMITADOR_VIRGULA
%token TOKEN_DELIMITADOR_ABRE_PARENTESES TOKEN_DELIMITADOR_FECHA_PARENTESES
%token TOKEN_DELIMITADOR_ABRE_CHAVES TOKEN_DELIMITADOR_FECHA_CHAVES
%token TOKEN_DELIMITADOR_ABRE_COLCHETES TOKEN_DELIMITADOR_FECHA_COLCHETES
%token TOKEN_DESCONHECIDO
%token TOKEN_NEWLINE TOKEN_INDENT TOKEN_DEDENT


/* Precedência dos operadores */
%left TOKEN_OPERADOR_MAIS TOKEN_OPERADOR_MENOS
%left TOKEN_OPERADOR_MULTIPLICACAO TOKEN_OPERADOR_DIVISAO

%right TOKEN_OPERADOR_ATRIBUICAO

%nonassoc TOKEN_PALAVRA_CHAVE_ELSE TOKEN_PALAVRA_CHAVE_ELIF

%%
programa:
    /* vazio */
  | programa comando
  ;

comando:
    atribuicao
  | chamada_funcao
  | expressao
  | TOKEN_NEWLINE
  | bloco
  ;

lista_comandos:
    comando
  | lista_comandos comando
  ;

atribuicao:
    lista_identificadores TOKEN_OPERADOR_ATRIBUICAO lista_expressoes
  | lista_identificadores TOKEN_OPERADOR_ATRIBUICAO atribuicao
  ;


lista_identificadores:
    TOKEN_IDENTIFICADOR
  | TOKEN_IDENTIFICADOR TOKEN_DELIMITADOR_VIRGULA lista_identificadores
  ;

lista_expressoes:
    expressao
  | expressao TOKEN_DELIMITADOR_VIRGULA lista_expressoes
  ;

lista_argumentos:
    /* vazio */
  | expressao
  | lista_argumentos TOKEN_DELIMITADOR_VIRGULA expressao
  ;

chamada_funcao:
    TOKEN_IDENTIFICADOR TOKEN_DELIMITADOR_ABRE_PARENTESES lista_argumentos TOKEN_DELIMITADOR_FECHA_PARENTESES
  | TOKEN_IDENTIFICADOR TOKEN_DELIMITADOR_ABRE_PARENTESES lista_identificadores TOKEN_DELIMITADOR_FECHA_PARENTESES
  ;

expressao:
    expressao TOKEN_OPERADOR_MAIS expressao
  | expressao TOKEN_OPERADOR_MENOS expressao
  | expressao TOKEN_OPERADOR_MULTIPLICACAO expressao
  | expressao TOKEN_OPERADOR_DIVISAO expressao
  | TOKEN_DELIMITADOR_ABRE_PARENTESES expressao TOKEN_DELIMITADOR_FECHA_PARENTESES
  | TOKEN_INTEIRO
  | TOKEN_PALAVRA_CHAVE_TRUE
  | TOKEN_PALAVRA_CHAVE_FALSE   
  | TOKEN_STRING
  ;



bloco:
    TOKEN_NEWLINE TOKEN_INDENT lista_comandos TOKEN_DEDENT
  ;

%%

void yyerror(const char *s) {
  fprintf(stderr, "ERRO (linha %d): %s próximo de '%s'\n", yylineno, s, yytext);
}

int main(void) {
  inicializa_pilha();
  yylineno = 1;
  int result = yyparse();
  if (result == 0) {
      printf("Parsing concluído com sucesso!\n");
  } else {
      printf("Parsing interrompido por erro.\n");
  }
  return result;
}