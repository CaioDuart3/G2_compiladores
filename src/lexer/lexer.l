%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "../parser/parser.tab.h"

int line_num = 1;


int pilha_indentacao[100];
int topo_pilha = 0;

void inicializa_pilha() {
    pilha_indentacao[0] = 0;
    topo_pilha = 0;
}


int yylex(void);
%}


%option noyywrap noinput nomain


%x INDENT

DIGITO    [0-9]
LETRA     [a-zA-Z_]
ID        {LETRA}({LETRA}|{DIGITO})*

%%

"if"      { printf("LEXER: Token PALAVRA_CHAVE_IF (%s)\n", yytext); return TOKEN_PALAVRA_CHAVE_IF; }
"else"    { printf("LEXER: Token PALAVRA_CHAVE_ELSE (%s)\n", yytext); return TOKEN_PALAVRA_CHAVE_ELSE; }
"elif"    { printf("LEXER: Token PALAVRA_CHAVE_ELIF (%s)\n", yytext); return TOKEN_PALAVRA_CHAVE_ELIF; }
"while"   { printf("LEXER: Token PALAVRA_CHAVE_WHILE (%s)\n", yytext); return TOKEN_PALAVRA_CHAVE_WHILE; }
"for"     { printf("LEXER: Token PALAVRA_CHAVE_FOR (%s)\n", yytext); return TOKEN_PALAVRA_CHAVE_FOR; }
"def"     { printf("LEXER: Token PALAVRA_CHAVE_DEF (%s)\n", yytext); return TOKEN_PALAVRA_CHAVE_DEF; }
"return"  { printf("LEXER: Token PALAVRA_CHAVE_RETURN (%s)\n", yytext); return TOKEN_PALAVRA_CHAVE_RETURN; }
"in"      { printf("LEXER: Token PALAVRA_CHAVE_IN (%s)\n", yytext); return TOKEN_PALAVRA_CHAVE_IN; }


"True"    { yylval.ival = 1; printf("LEXER: Token PALAVRA_CHAVE_TRUE (%s)\n", yytext); return TOKEN_PALAVRA_CHAVE_TRUE; }
"False"   { yylval.ival = 0; printf("LEXER: Token PALAVRA_CHAVE_FALSE (%s)\n", yytext); return TOKEN_PALAVRA_CHAVE_FALSE; }


"=="      { printf("LEXER: Token OPERADOR_IGUAL (%s)\n", yytext); return TOKEN_OPERADOR_IGUAL; }
"!="      { printf("LEXER: Token OPERADOR_DIFERENTE (%s)\n", yytext); return TOKEN_OPERADOR_DIFERENTE; }
"<="      { printf("LEXER: Token OPERADOR_MENOR_IGUAL (%s)\n", yytext); return TOKEN_OPERADOR_MENOR_IGUAL; }
">="      { printf("LEXER: Token OPERADOR_MAIOR_IGUAL (%s)\n", yytext); return TOKEN_OPERADOR_MAIOR_IGUAL; }
"<"       { printf("LEXER: Token OPERADOR_MENOR (%s)\n", yytext); return TOKEN_OPERADOR_MENOR; }
">"       { printf("LEXER: Token OPERADOR_MAIOR (%s)\n", yytext); return TOKEN_OPERADOR_MAIOR; }
"="       { printf("LEXER: Token OPERADOR_ATRIBUICAO (%s)\n", yytext); return TOKEN_OPERADOR_ATRIBUICAO; }
"++"      { }
"+"       { printf("LEXER: Token OPERADOR_MAIS (%s)\n", yytext); return TOKEN_OPERADOR_MAIS; }
"-"       { printf("LEXER: Token OPERADOR_MENOS (%s)\n", yytext); return TOKEN_OPERADOR_MENOS; }
"*"       { printf("LEXER: Token OPERADOR_MULTIPLICAACAO (%s)\n", yytext); return TOKEN_OPERADOR_MULTIPLICAACAO; }
"/"       { printf("LEXER: Token OPERADOR_DIVISAO (%s)\n", yytext); return TOKEN_OPERADOR_DIVISAO; }

":"       { printf("LEXER: Token DELIMITADOR_DOIS_PONTOS (%s)\n", yytext); return TOKEN_DELIMITADOR_DOIS_PONTOS; }
","       { printf("LEXER: Token DELIMITADOR_VIRGULA (%s)\n", yytext); return TOKEN_DELIMITADOR_VIRGULA; }
"("       { printf("LEXER: Token DELIMITADOR_ABRE_PARENTESES (%s)\n", yytext); return TOKEN_DELIMITADOR_ABRE_PARENTESES; }
")"       { printf("LEXER: Token DELIMITADOR_FECHA_PARENTESES (%s)\n", yytext); return TOKEN_DELIMITADOR_FECHA_PARENTESES; }
"["       { printf("LEXER: Token DELIMITADOR_ABRE_COLCHETES (%s)\n", yytext); return TOKEN_DELIMITADOR_ABRE_COLCHETES; }
"]"       { printf("LEXER: Token DELIMITADOR_FECHA_COLCHETES (%s)\n", yytext); return TOKEN_DELIMITADOR_FECHA_COLCHETES; }
"{"       { printf("LEXER: Token DELIMITADOR_ABRE_CHAVES (%s)\n", yytext); return TOKEN_DELIMITADOR_ABRE_CHAVES; }
"}"       { printf("LEXER: Token DELIMITADOR_FECHA_CHAVES (%s)\n", yytext); return TOKEN_DELIMITADOR_FECHA_CHAVES; }


{DIGITO}+("."{DIGITO}+)?  {
    if (strchr(yytext,'.')) {

        printf("LEXER: Token FLOAT (%s)\n", yytext);
        return TOKEN_FLOAT;
    } else {
        yylval.ival = atoi(yytext);
        printf("LEXER: Token INTEIRO (%s)\n", yytext);
        return TOKEN_INTEIRO;
    }
}


\"([^\\\"]|\\.)*\"  { yylval.sval = strdup(yytext); printf("LEXER: Token STRING (%s)\n", yytext); return TOKEN_STRING; }
\'([^\\\']|\\.)*\'  { yylval.sval = strdup(yytext); printf("LEXER: Token STRING (%s)\n", yytext); return TOKEN_STRING; }


{ID} {
    yylval.sval = strdup(yytext);
    printf("LEXER: Token IDENTIFICADOR (%s)\n", yytext);
    return TOKEN_IDENTIFICADOR;
}


"#".*   { }


\n      {
    yylineno++;
    line_num++;
    BEGIN(INDENT);
    printf("LEXER: Token QUEBRA-DE-LINHA (\\n)\\n\\n");
    return TOKEN_NEWLINE;
}

[ \t]+  { }

.       {
    fprintf(stderr,"ERRO LÉXICO linha %d: '%s'\n", line_num, yytext);
    return TOKEN_DESCONHECIDO;
}


<INDENT>[ \t]+ {
    int espacos = 0;
    for (int i = 0; i < yyleng; ++i) {
        if (yytext[i] == ' ') espacos += 1;
        else if (yytext[i] == '\t') espacos += 4; 
    }


    if (espacos > pilha_indentacao[topo_pilha]) {
        pilha_indentacao[++topo_pilha] = espacos;
        BEGIN(INITIAL);
        printf("LEXER: INDENT (nível %d, cols=%d)\n", topo_pilha, espacos);
        return TOKEN_INDENT;
    }


    if (espacos == pilha_indentacao[topo_pilha]) {
        BEGIN(INITIAL);

        return yylex();
    }


    if (espacos < pilha_indentacao[topo_pilha]) {

        topo_pilha--;
        BEGIN(INITIAL);
        printf("LEXER: DEDENT (novo nível %d, target cols=%d)\n", topo_pilha, espacos);
        return TOKEN_DEDENT;
    }

    BEGIN(INITIAL);
    return yylex();
}

<INDENT>[^ \t\n] {
    unput(yytext[0]);
    BEGIN(INITIAL);

    return yylex();
}


<<EOF>> {
    if (topo_pilha > 0) {
        topo_pilha--;
        printf("LEXER: EOF -> DEDENT (nível %d)\n", topo_pilha);
        return TOKEN_DEDENT;
    }
    return 0;
}

%%
