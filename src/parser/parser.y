%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *saida;

int yylex(void);
void yyerror(const char *s);
%}

%union {
    char* str;
    int inteiro;
    float flutuante;
}

%token <str> TOKEN_IDENTIFICADOR TOKEN_STRING
%token <inteiro> TOKEN_INTEIRO
%token <flutuante> TOKEN_FLOAT


%token TOKEN_PALAVRA_CHAVE_IF TOKEN_PALAVRA_CHAVE_ELSE TOKEN_PALAVRA_CHAVE_ELIF
%token TOKEN_PALAVRA_CHAVE_WHILE TOKEN_PALAVRA_CHAVE_FOR
%token TOKEN_PALAVRA_CHAVE_DEF TOKEN_PALAVRA_CHAVE_RETURN TOKEN_PALAVRA_CHAVE_IN

%token TOKEN_OPERADOR_IGUAL TOKEN_OPERADOR_DIFERENTE
%token TOKEN_OPERADOR_MENOR_IGUAL TOKEN_OPERADOR_MAIOR_IGUAL
%token TOKEN_OPERADOR_MENOR TOKEN_OPERADOR_MAIOR
%token TOKEN_OPERADOR_ATRIBUICAO
%token TOKEN_OPERADOR_MAIS TOKEN_OPERADOR_MENOS TOKEN_OPERADOR_MULTIPLICACAO TOKEN_OPERADOR_DIVISAO

%token TOKEN_DELIMITADOR_DOIS_PONTOS TOKEN_DELIMITADOR_VIRGULA
%token TOKEN_DELIMITADOR_ABRE_PARENTESES TOKEN_DELIMITADOR_FECHA_PARENTESES
%token TOKEN_DELIMITADOR_ABRE_COLCHETES TOKEN_DELIMITADOR_FECHA_COLCHETES
%token TOKEN_DELIMITADOR_ABRE_CHAVES TOKEN_DELIMITADOR_FECHA_CHAVES

%left TOKEN_OPERADOR_MAIS TOKEN_OPERADOR_MENOS
%left TOKEN_OPERADOR_MULTIPLICACAO TOKEN_OPERADOR_DIVISAO
%right TOKEN_OPERADOR_ATRIBUICAO

%type <str> expr

%%

program:
    { fprintf(saida, "#include <stdio.h>\n\nint main() {\n"); }
    stmt_list
    { fprintf(saida, "return 0;\n}\n"); }
;

stmt_list:
    stmt_list stmt
    | stmt
;

stmt:
    simple_stmt
    | compound_stmt
;

simple_stmt:
    expr_stmt
    | return_stmt
;

expr_stmt:
    TOKEN_IDENTIFICADOR TOKEN_OPERADOR_ATRIBUICAO expr {
        fprintf(saida, "%s = %s;\n", $1, $3);
    }
;

return_stmt:
    TOKEN_PALAVRA_CHAVE_RETURN expr {
        fprintf(saida, "return %s;\n", $2);
    }
;

compound_stmt:
    if_stmt
    | while_stmt
    | func_def
;

if_stmt:
    TOKEN_PALAVRA_CHAVE_IF expr TOKEN_DELIMITADOR_DOIS_PONTOS stmt_list {
        fprintf(saida, "if (%s) {\n", $2);
    }
    TOKEN_PALAVRA_CHAVE_ELSE TOKEN_DELIMITADOR_DOIS_PONTOS stmt_list {
        fprintf(saida, "} else {\n");
    }
    { fprintf(saida, "}\n"); }
;

while_stmt:
    TOKEN_PALAVRA_CHAVE_WHILE expr TOKEN_DELIMITADOR_DOIS_PONTOS stmt_list {
        fprintf(saida, "while (%s) {\n", $2);
        fprintf(saida, "}\n");
    }
;

func_def:
    TOKEN_PALAVRA_CHAVE_DEF TOKEN_IDENTIFICADOR TOKEN_DELIMITADOR_ABRE_PARENTESES opt_params TOKEN_DELIMITADOR_FECHA_PARENTESES TOKEN_DELIMITADOR_DOIS_PONTOS stmt_list {
        fprintf(saida, "int %s(", $2);
        fprintf(saida, ") {\n");
        fprintf(saida, "}\n");
    }
;

opt_params:
    /* vazio */
    | param_list
;

param_list:
    TOKEN_IDENTIFICADOR {
        fprintf(saida, "int %s", $1);
    }
    | param_list TOKEN_DELIMITADOR_VIRGULA TOKEN_IDENTIFICADOR {
        fprintf(saida, ", int %s", $3);
    }
;

expr:
    expr TOKEN_OPERADOR_MAIS expr {
        char *buf = malloc(strlen($1) + strlen($3) + 6);
        sprintf(buf, "(%s + %s)", $1, $3);
        $$ = buf;
    }
    | expr TOKEN_OPERADOR_MENOS expr {
        char *buf = malloc(strlen($1) + strlen($3) + 6);
        sprintf(buf, "(%s - %s)", $1, $3);
        $$ = buf;
    }
    | expr TOKEN_OPERADOR_MULTIPLICACAO expr {
        char *buf = malloc(strlen($1) + strlen($3) + 6);
        sprintf(buf, "(%s * %s)", $1, $3);
        $$ = buf;
    }
    | expr TOKEN_OPERADOR_DIVISAO expr {
        char *buf = malloc(strlen($1) + strlen($3) + 6);
        sprintf(buf, "(%s / %s)", $1, $3);
        $$ = buf;
    }
    | TOKEN_DELIMITADOR_ABRE_PARENTESES expr TOKEN_DELIMITADOR_FECHA_PARENTESES {
        char *buf = malloc(strlen($2) + 3);
        sprintf(buf, "(%s)", $2);
        $$ = buf;
    }
    | TOKEN_INTEIRO {
        char *buf = malloc(32);
        sprintf(buf, "%d", $1);
        $$ = buf;
    }
    | TOKEN_FLOAT {
        char *buf = malloc(32);
        sprintf(buf, "%f", $1);
        $$ = buf;
    }
    | TOKEN_STRING {
        $$ = $1;
    }
    | TOKEN_IDENTIFICADOR {
        $$ = $1;
    }
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro sintático: %s\n", s);
}

int main(void) {
    saida = fopen("output.c", "w");
    if (!saida) {
        perror("Erro ao abrir output.c");
        return 1;
    }
    yyparse();
    fclose(saida);
    return 0;
}
