%{
#include <stdio.h>
#include <string.h>
#include "./parser.tab.h"

#define MAX_INDENT 100

int indent_stack[MAX_INDENT];
int indent_top = 0;
char *yytoken_value;

void push_indent(int n) { indent_stack[++indent_top] = n; }
void pop_indent() { if (indent_top > 0) indent_top--; }
int top_indent() { return indent_stack[indent_top]; }

%}

%option noyywrap
%option yylineno

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
"+"         { printf("LEXER: Token MAIS (%s)\n", yytext); return TOKEN_OPERADOR_MAIS; }
"-"         { printf("LEXER: Token MENOS (%s)\n", yytext); return TOKEN_OPERADOR_MENOS; }
"*"         { printf("LEXER: Token VEZES (%s)\n", yytext); return TOKEN_OPERADOR_MULTIPLICACAO; }
"/"         { printf("LEXER: Token DIVISÃO (%s)\n", yytext); return TOKEN_OPERADOR_DIVISAO; }

":"         { return TOKEN_DELIMITADOR_DOIS_PONTOS; }
","         { printf("LEXER: Token VIRGULA (%s)\n", yytext); return TOKEN_DELIMITADOR_VIRGULA; }
"("         { printf("LEXER: Token ABRE PARENTESES (%s)\n", yytext); return TOKEN_DELIMITADOR_ABRE_PARENTESES; }
")"         { printf("LEXER: Token FECHA PARENTESES (%s)\n", yytext); return TOKEN_DELIMITADOR_FECHA_PARENTESES; }
"["         { return TOKEN_DELIMITADOR_ABRE_COLCHETES; }
"]"         { return TOKEN_DELIMITADOR_FECHA_COLCHETES; }
"{"         { return TOKEN_DELIMITADOR_ABRE_CHAVES; }
"}"         { return TOKEN_DELIMITADOR_FECHA_CHAVES; }
\n          { printf("LEXER: Token QUEBRA LINHA (/n)\n"); return TOKEN_NEWLINE; }


^[ \t]*    { // tratamento de identação
    int n = yyleng;  // número de espaços/tabs
    if (n > top_indent()) {
        push_indent(n);
        printf("LEXER: Token INDENT\n");
        return TOKEN_INDENT;
    } else if (n < top_indent()) {
        while (n < top_indent()) {
            pop_indent();
            printf("LEXER: Token DEDENT\n");
            return TOKEN_DEDENT;
        }
    }
}

[ \t]+      { /* ignora espaços dentro da linha */ }


"#".*       { /* ignora comentário */ }


.           { printf("ERRO: Caractere invalido '%s'\n", yytext); return TOKEN_DESCONHECIDO; }
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