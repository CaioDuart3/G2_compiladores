%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Inclui a definição dos tokens E da union 'yylval' vinda do parser */
#include "../parser/parser.tab.h" 

int line_num = 1;
int pilha_indentacao[100];
int topo_pilha = 0;

void inicializa_pilha() {
    pilha_indentacao[0] = 0;
    topo_pilha = 0;
}
%}

%option noyywrap noinput nomain
%x IDENT

DIGITO    [0-9]
LETRA     [a-zA-Z_]
ID        {LETRA}({LETRA}|{DIGITO})*

%%

    /* Palavras-chave */
"if"      { printf("LEXER: Token PALAVRA_CHAVE_IF (%s)\n", yytext); return TOKEN_PALAVRA_CHAVE_IF; }
"else"    { printf("LEXER: Token PALAVRA_CHAVE_ELSE (%s)\n", yytext); return TOKEN_PALAVRA_CHAVE_ELSE; }
"elif"    { printf("LEXER: Token PALAVRA_CHAVE_ELIF (%s)\n", yytext); return TOKEN_PALAVRA_CHAVE_ELIF; }
"while"   { printf("LEXER: Token PALAVRA_CHAVE_WHILE (%s)\n", yytext); return TOKEN_PALAVRA_CHAVE_WHILE; }
"for"     { printf("LEXER: Token PALAVRA_CHAVE_FOR (%s)\n", yytext); return TOKEN_PALAVRA_CHAVE_FOR; }
"def"     { printf("LEXER: Token PALAVRA_CHAVE_DEF (%s)\n", yytext); return TOKEN_PALAVRA_CHAVE_DEF; }
"return"  { printf("LEXER: Token PALAVRA_CHAVE_RETURN (%s)\n", yytext); return TOKEN_PALAVRA_CHAVE_RETURN; }
"in"      { printf("LEXER: Token PALAVRA_CHAVE_IN (%s)\n", yytext); return TOKEN_PALAVRA_CHAVE_IN; }

    /* Literais Booleanos (colocam 1 ou 0 na yylval) */
"True"    { yylval.ival = 1; printf("LEXER: Token PALAVRA_CHAVE_TRUE (%s)\n", yytext); return TOKEN_PALAVRA_CHAVE_TRUE; }
"False"   { yylval.ival = 0; printf("LEXER: Token PALAVRA_CHAVE_FALSE (%s)\n", yytext); return TOKEN_PALAVRA_CHAVE_FALSE; }

    /* Operadores */
"=="      { printf("LEXER: Token OPERADOR_IGUAL (%s)\n", yytext); return TOKEN_OPERADOR_IGUAL; }
"!="      { printf("LEXER: Token OPERADOR_DIFERENTE (%s)\n", yytext); return TOKEN_OPERADOR_DIFERENTE; }
"<="      { printf("LEXER: Token OPERADOR_MENOR_IGUAL (%s)\n", yytext); return TOKEN_OPERADOR_MENOR_IGUAL; }
">="      { printf("LEXER: Token OPERADOR_MAIOR_IGUAL (%s)\n", yytext); return TOKEN_OPERADOR_MAIOR_IGUAL; }
"<"       { printf("LEXER: Token OPERADOR_MENOR (%s)\n", yytext); return TOKEN_OPERADOR_MENOR; }
">"       { printf("LEXER: Token OPERADOR_MAIOR (%s)\n", yytext); return TOKEN_OPERADOR_MAIOR; }
"="       { printf("LEXER: Token OPERADOR_ATRIBUICAO (%s)\n", yytext); return TOKEN_OPERADOR_ATRIBUICAO; }
"+"       { printf("LEXER: Token OPERADOR_MAIS (%s)\n", yytext); return TOKEN_OPERADOR_MAIS; }
"-"       { printf("LEXER: Token OPERADOR_MENOS (%s)\n", yytext); return TOKEN_OPERADOR_MENOS; }
"*"       { printf("LEXER: Token OPERADOR_MULTIPLICACAO (%s)\n", yytext); return TOKEN_OPERADOR_MULTIPLICACAO; }
"/"       { printf("LEXER: Token OPERADOR_DIVISAO (%s)\n", yytext); return TOKEN_OPERADOR_DIVISAO; }

    /* Delimitadores */
":"       { printf("LEXER: Token DELIMITADOR_DOIS_PONTOS (%s)\n", yytext); return TOKEN_DELIMITADOR_DOIS_PONTOS; }
","       { printf("LEXER: Token DELIMITADOR_VIRGULA (%s)\n", yytext); return TOKEN_DELIMITADOR_VIRGULA; }
"("       { printf("LEXER: Token DELIMITADOR_ABRE_PARENTESES (%s)\n", yytext); return TOKEN_DELIMITADOR_ABRE_PARENTESES; }
")"       { printf("LEXER: Token DELIMITADOR_FECHA_PARENTESES (%s)\n", yytext); return TOKEN_DELIMITADOR_FECHA_PARENTESES; }
"["       { printf("LEXER: Token DELIMITADOR_ABRE_COLCHETES (%s)\n", yytext); return TOKEN_DELIMITADOR_ABRE_COLCHETES; }
"]"       { printf("LEXER: Token DELIMITADOR_FECHA_COLCHETES (%s)\n", yytext); return TOKEN_DELIMITADOR_FECHA_COLCHETES; }
"{"       { printf("LEXER: Token DELIMITADOR_ABRE_CHAVES (%s)\n", yytext); return TOKEN_DELIMITADOR_ABRE_CHAVES; }
"}"       { printf("LEXER: Token DELIMITADOR_FECHA_CHAVES (%s)\n", yytext); return TOKEN_DELIMITADOR_FECHA_CHAVES; }


    /* --- Tokens com Valor --- */

{DIGITO}+("."{DIGITO}+)?  { 
    if (strchr(yytext,'.')) {
        /* yylval.fval = atof(yytext); // Descomente se adicionar float na union */
        printf("LEXER: Token FLOAT (%s)\n", yytext);
        return TOKEN_FLOAT;
    } else {
        yylval.ival = atoi(yytext); /* Coloca o inteiro na union */
        printf("LEXER: Token INTEIRO (%s)\n", yytext);
        return TOKEN_INTEIRO;
    }
}

    /* Strings (ambas ' e ") */
\"[^\"]*\"  { yylval.sval = strdup(yytext); printf("LEXER: Token STRING (%s)\n", yytext); return TOKEN_STRING; }
\'[^\']*\'  { yylval.sval = strdup(yytext); printf("LEXER: Token STRING (%s)\n", yytext); return TOKEN_STRING; }

    /* Identificador */
{ID}      { 
    yylval.sval = strdup(yytext); /* Coloca a string na union */
    printf("LEXER: Token IDENTIFICADOR (%s)\n", yytext);
    return TOKEN_IDENTIFICADOR; 
}


    /* --- Lógica de Indentação --- */

\n        { 
    line_num++;
    yylineno++;
    BEGIN(IDENT);
    printf("LEXER: Token QUEBRA-DE-LINHA (\\n)\n\n");
    return TOKEN_NEWLINE;
}

[ \t]+    { /* Ignora espaço em branco no meio da linha */ }

<IDENT>^[ \t]+ {
    int espacos = 0;
    for (int i = 0; i < yyleng; i++) {
        if (yytext[i]==' ') espacos++;
        else if (yytext[i]=='\t') espacos+=4;
    }

    if (espacos > pilha_indentacao[topo_pilha]) {
        pilha_indentacao[++topo_pilha] = espacos;
        BEGIN(INITIAL);
        printf("LEXER: INDENT (nível %d)\n", topo_pilha);
        return TOKEN_INDENT;
    } else if (espacos < pilha_indentacao[topo_pilha]) {
        while(topo_pilha>0 && espacos < pilha_indentacao[topo_pilha]) {
            topo_pilha--;
            BEGIN(INITIAL);
            printf("LEXER: DEDENT (nível %d)\n", topo_pilha);
            return TOKEN_DEDENT;
        }
    }
    BEGIN(INITIAL); /* Mesma indentação, não faz nada */
}

<IDENT>^[^ \t\n] {
    unput(yytext[0]);
    while(topo_pilha>0) {
        topo_pilha--;
        BEGIN(INITIAL);
        printf("LEXER: DEDENT (nível %d)\n", topo_pilha);
        return TOKEN_DEDENT;
    }
    BEGIN(INITIAL);
}

. { 
    fprintf(stderr,"ERRO LÉXICO linha %d: '%s'\n", line_num, yytext);
    return TOKEN_DESCONHECIDO;
}

<<EOF>> {
    while(topo_pilha>0) {
        topo_pilha--;
        printf("LEXER: DEDENT (nível %d)\n", topo_pilha);
        return TOKEN_DEDENT;
    }
    yyterminate();
}

%%