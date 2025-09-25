%{
#include <stdio.h>
#include <string.h>
#include "parser.tab.h"

/* Enumeração para os tipos de tokens */


/* Variável global para armazenar o valor do token, se necessário */
/* Para este exemplo, vamos armazenar o yytext. Em um analisador real, você pode ter uma 'union' */
char *yytoken_value;

%}


DIGITO      [0-9]
LETRA       [a-zA-Z_]
ID          {LETRA}({LETRA}|{DIGITO})*


%%


"if"        { return TOKEN_PALAVRA_CHAVE_IF; }
"else"      { return TOKEN_PALAVRA_CHAVE_ELSE; }
"elif"      { return TOKEN_PALAVRA_CHAVE_ELIF; }
"while"     { return TOKEN_PALAVRA_CHAVE_WHILE; }
"for"       { return TOKEN_PALAVRA_CHAVE_FOR; }
"def"       { return TOKEN_PALAVRA_CHAVE_DEF; }
"return"    { return TOKEN_PALAVRA_CHAVE_RETURN; }
"in"        { return TOKEN_PALAVRA_CHAVE_IN; }

{ID}        { yytoken_value = strdup(yytext); printf("LEXER: Token identificador (%s)\n", yytext); return TOKEN_IDENTIFICADOR; }

{DIGITO}+   { yytoken_value = strdup(yytext); printf("LEXER: Token INTEIRO (%s)\n", yytext); return TOKEN_INTEIRO; }
{DIGITO}+("."{DIGITO}+)?   { yytoken_value = strdup(yytext); printf("LEXER: Token FLOAT (%s)\n", yytext); return TOKEN_FLOAT; }

\"[^\"]*\"  { yytoken_value = strdup(yytext); return TOKEN_STRING; }
\'[^\']*\'  { yytoken_value = strdup(yytext); return TOKEN_STRING; }

"=="        { return TOKEN_OPERADOR_IGUAL; }
"!="        { return TOKEN_OPERADOR_DIFERENTE; }
"<="        { return TOKEN_OPERADOR_MENOR_IGUAL; }
">="        { return TOKEN_OPERADOR_MAIOR_IGUAL; }
"<"         { return TOKEN_OPERADOR_MENOR; }
">"         { return TOKEN_OPERADOR_MAIOR; }
"="         { printf("LEXER: Token IGUAL (%s)\n", yytext); return TOKEN_OPERADOR_ATRIBUICAO; }
"+"         { return TOKEN_OPERADOR_MAIS; }
"-"         { return TOKEN_OPERADOR_MENOS; }
"*"         { return TOKEN_OPERADOR_MULTIPLICACAO; }
"/"         { return TOKEN_OPERADOR_DIVISAO; }

":"         { return TOKEN_DELIMITADOR_DOIS_PONTOS; }
","         { return TOKEN_DELIMITADOR_VIRGULA; }
"("         { return TOKEN_DELIMITADOR_ABRE_PARENTESES; }
")"         { return TOKEN_DELIMITADOR_FECHA_PARENTESES; }
"["         { return TOKEN_DELIMITADOR_ABRE_COLCHETES; }
"]"         { return TOKEN_DELIMITADOR_FECHA_COLCHETES; }
"{"         { return TOKEN_DELIMITADOR_ABRE_CHAVES; }
"}"         { return TOKEN_DELIMITADOR_FECHA_CHAVES; }
\n          { printf("LEXER: Token QUEBRA LINHA (%s)\n", yytext); return TOKEN_NEWLINE; }


[ \t]+      { /* ignora espaços e tabs */ }
"#".*       { /* ignora comentário */ }


.           { printf("ERROR: Caractere invalido '%s'\n", yytext); return TOKEN_DESCONHECIDO; }
%%

const char *token_to_string(int token) {
    switch(token) {
        case TOKEN_PALAVRA_CHAVE_IF: return "PALAVRA-CHAVE IF";
        case TOKEN_PALAVRA_CHAVE_ELSE: return "PALAVRA-CHAVE ELSE";
        case TOKEN_PALAVRA_CHAVE_ELIF: return "PALAVRA-CHAVE ELIF";
        case TOKEN_PALAVRA_CHAVE_WHILE: return "PALAVRA-CHAVE WHILE";
        case TOKEN_PALAVRA_CHAVE_FOR: return "PALAVRA-CHAVE FOR";
        case TOKEN_PALAVRA_CHAVE_DEF: return "PALAVRA-CHAVE DEF";
        case TOKEN_PALAVRA_CHAVE_RETURN: return "PALAVRA-CHAVE RETURN";
        case TOKEN_PALAVRA_CHAVE_IN: return "PALAVRA-CHAVE IN";
        case TOKEN_IDENTIFICADOR: return "IDENTIFICADOR";
        case TOKEN_INTEIRO: return "NUMERO-INTEIRO";
        case TOKEN_FLOAT: return "NUMERO-FLOAT";
        case TOKEN_STRING: return "STRING";
        case TOKEN_OPERADOR_IGUAL: return "OPERADOR: ==";
        case TOKEN_OPERADOR_DIFERENTE: return "OPERADOR: !=";
        case TOKEN_OPERADOR_MENOR_IGUAL: return "OPERADOR: <=";
        case TOKEN_OPERADOR_MAIOR_IGUAL: return "OPERADOR: >=";
        case TOKEN_OPERADOR_MENOR: return "OPERADOR: <";
        case TOKEN_OPERADOR_MAIOR: return "OPERADOR: >";
        case TOKEN_OPERADOR_ATRIBUICAO: return "OPERADOR: =";
        case TOKEN_OPERADOR_MAIS: return "OPERADOR: +";
        case TOKEN_OPERADOR_MENOS: return "OPERADOR: -";
        case TOKEN_OPERADOR_MULTIPLICACAO: return "OPERADOR: *";
        case TOKEN_OPERADOR_DIVISAO: return "OPERADOR: /";
        case TOKEN_DELIMITADOR_DOIS_PONTOS: return "DELIMITADOR: :";
        case TOKEN_DELIMITADOR_VIRGULA: return "DELIMITADOR: ,";
        case TOKEN_DELIMITADOR_ABRE_PARENTESES: return "DELIMITADOR: (";
        case TOKEN_DELIMITADOR_FECHA_PARENTESES: return "DELIMITADOR: )";
        case TOKEN_DELIMITADOR_ABRE_COLCHETES: return "DELIMITADOR: [";
        case TOKEN_DELIMITADOR_FECHA_COLCHETES: return "DELIMITADOR: ]";
        case TOKEN_DELIMITADOR_ABRE_CHAVES: return "DELIMITADOR: {";
        case TOKEN_DELIMITADOR_FECHA_CHAVES: return "DELIMITADOR: }";
        case TOKEN_NEWLINE: return "DELIMITADOR: \n";
        case TOKEN_DESCONHECIDO: return "CARACTERE DESCONHECIDO";
        default: return "EOF";
    }
}