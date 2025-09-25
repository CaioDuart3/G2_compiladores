%{
    #include <stdio.h>
    #include <stdlib.h>

    #define YYERROR_VERBOSE 1

    /* Definindo yylex e yyerror */
    int yylex(void);
    void yyerror(const char *s);

    extern char *yytext;
%}

%define parse.trace


/* Tokens vindos do lexer */
%token TOKEN_IDENTIFICADOR TOKEN_INTEIRO TOKEN_FLOAT TOKEN_STRING
%token TOKEN_PALAVRA_CHAVE_IF TOKEN_PALAVRA_CHAVE_ELSE TOKEN_PALAVRA_CHAVE_ELIF
%token TOKEN_PALAVRA_CHAVE_WHILE TOKEN_PALAVRA_CHAVE_FOR TOKEN_PALAVRA_CHAVE_DEF TOKEN_PALAVRA_CHAVE_RETURN TOKEN_PALAVRA_CHAVE_IN
%token TOKEN_OPERADOR_IGUAL TOKEN_OPERADOR_DIFERENTE TOKEN_OPERADOR_MENOR_IGUAL TOKEN_OPERADOR_MAIOR_IGUAL
%token TOKEN_OPERADOR_MENOR TOKEN_OPERADOR_MAIOR
%token TOKEN_OPERADOR_ATRIBUICAO
%token TOKEN_OPERADOR_MAIS TOKEN_OPERADOR_MENOS TOKEN_OPERADOR_MULTIPLICACAO TOKEN_OPERADOR_DIVISAO
%token TOKEN_DELIMITADOR_DOIS_PONTOS TOKEN_DELIMITADOR_VIRGULA
%token TOKEN_DELIMITADOR_ABRE_PARENTESES TOKEN_DELIMITADOR_FECHA_PARENTESES
%token TOKEN_DELIMITADOR_ABRE_CHAVES TOKEN_DELIMITADOR_FECHA_CHAVES
%token TOKEN_DELIMITADOR_ABRE_COLCHETES TOKEN_DELIMITADOR_FECHA_COLCHETES
%token TOKEN_DESCONHECIDO
%token TOKEN_NEWLINE

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
    | expressao
    | TOKEN_NEWLINE 
    ;


atribuicao:
    lista_identificadores TOKEN_OPERADOR_ATRIBUICAO lista_expressoes
  | lista_identificadores TOKEN_OPERADOR_ATRIBUICAO atribuicao
  ;

lista_identificadores:
    TOKEN_IDENTIFICADOR
  | lista_identificadores TOKEN_DELIMITADOR_VIRGULA TOKEN_IDENTIFICADOR
  ;

lista_expressoes:
    expressao
  | lista_expressoes TOKEN_DELIMITADOR_VIRGULA expressao
  ;

expressao:
      TOKEN_INTEIRO
    | TOKEN_FLOAT
    | TOKEN_STRING
    | TOKEN_IDENTIFICADOR
    | expressao TOKEN_OPERADOR_MAIS expressao
    | expressao TOKEN_OPERADOR_MENOS expressao
    | expressao TOKEN_OPERADOR_MULTIPLICACAO expressao
    | expressao TOKEN_OPERADOR_DIVISAO expressao
    | TOKEN_DELIMITADOR_ABRE_PARENTESES expressao TOKEN_DELIMITADOR_FECHA_PARENTESES
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro de sintaxe: %s próximo de '%s'\n", s, yytext);
}

int main(void) {
    printf("Iniciando parser...\n");
    yyparse();
    printf("Parsing concluído com sucesso!\n");
    return 0;
}
