%option noyywrap
%option yylineno

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./parser.tab.h"

#define MAX_INDENT 100

int indent_stack[MAX_INDENT];
int indent_top = 0;
char *yytoken_value;

void push_indent(int n) { indent_stack[++indent_top] = n; }
void pop_indent() { if (indent_top > 0) indent_top--; }
int top_indent() { return indent_stack[indent_top]; }

int convert_to_int(char *text) { return atoi(text); }

void inicializa_pilha() {
    indent_stack[0] = 0;
    indent_top = 0;
}
%}


%option noyywrap nomain
%x IDENT

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

{ID}        { yytoken_value = strdup(yytext); return TOKEN_IDENTIFICADOR; }

{DIGITO}+   { yytoken_value = strdup(yytext); return TOKEN_INTEIRO; }
{DIGITO}+("."{DIGITO}+)? { yytoken_value = strdup(yytext); return TOKEN_FLOAT; }

\"([^\"\n\\]|\\.)*\"  { yytoken_value = strdup(yytext); return TOKEN_STRING; }
\'([^\'\n\\]|\\.)*\'  { yytoken_value = strdup(yytext); return TOKEN_STRING; }

"=="        { return TOKEN_OPERADOR_IGUAL; }
"!="        { return TOKEN_OPERADOR_DIFERENTE; }
"<="        { return TOKEN_OPERADOR_MENOR_IGUAL; }
">="        { return TOKEN_OPERADOR_MAIOR_IGUAL; }
"<"         { return TOKEN_OPERADOR_MENOR; }
">"         { return TOKEN_OPERADOR_MAIOR; }
"="         { return TOKEN_OPERADOR_ATRIBUICAO; }
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

"#".*       { /* Ignorar */ }

\n  { return TOKEN_NEWLINE; }



<IDENT>^[ \t]+ {
    int espacos = 0;
    for (int i = 0; i < yyleng; i++) {
        if (yytext[i] == ' ') espacos++;
        else if (yytext[i] == '\t') espacos += 4; 
    }

    if (espacos > top_indent()) {
        push_indent(espacos);
        BEGIN(INITIAL);
        return TOKEN_INDENT;
    } else if (espacos < top_indent()) {
        while (indent_top > 0 && espacos < top_indent()) {
            pop_indent();
        
            BEGIN(INITIAL);
            return TOKEN_DEDENT;
        }
    }
    BEGIN(INITIAL);
}


<IDENT>^[^ \t\n] {
    unput(yytext[0]); 
    while (indent_top > 0) {
        pop_indent();
        return TOKEN_DEDENT;
    }
    BEGIN(INITIAL);
}

[ \t]+    { /* ignorar */ }

. { fprintf(stderr, "ERRO LÉXICO linha %d: '%s'\n", yylineno, yytext); return TOKEN_DESCONHECIDO; }


<<EOF>> {
    while (indent_top > 0) {
        pop_indent();
        return TOKEN_DEDENT;
    }
    yyterminate();
}

%%

const char *token_to_string(int token) {
    switch(token) {
        case TOKEN_PALAVRA_CHAVE_IF: return "IF";
        case TOKEN_PALAVRA_CHAVE_ELSE: return "ELSE";
        case TOKEN_PALAVRA_CHAVE_ELIF: return "ELIF";
        case TOKEN_PALAVRA_CHAVE_WHILE: return "WHILE";
        case TOKEN_PALAVRA_CHAVE_FOR: return "FOR";
        case TOKEN_PALAVRA_CHAVE_DEF: return "DEF";
        case TOKEN_PALAVRA_CHAVE_RETURN: return "RETURN";
        case TOKEN_PALAVRA_CHAVE_IN: return "IN";
        case TOKEN_IDENTIFICADOR: return "IDENTIFICADOR";
        case TOKEN_INTEIRO: return "NUMERO-INTEIRO";
        case TOKEN_FLOAT: return "NUMERO-FLOAT";
        case TOKEN_STRING: return "STRING";
        case TOKEN_OPERADOR_IGUAL: return "==";
        case TOKEN_OPERADOR_DIFERENTE: return "!=";
        case TOKEN_OPERADOR_MENOR_IGUAL: return "<=";
        case TOKEN_OPERADOR_MAIOR_IGUAL: return ">=";
        case TOKEN_OPERADOR_MENOR: return "<";
        case TOKEN_OPERADOR_MAIOR: return ">";
        case TOKEN_OPERADOR_ATRIBUICAO: return "=";
        case TOKEN_OPERADOR_MAIS: return "+";
        case TOKEN_OPERADOR_MENOS: return "-";
        case TOKEN_OPERADOR_MULTIPLICACAO: return "*";
        case TOKEN_OPERADOR_DIVISAO: return "/";
        case TOKEN_DELIMITADOR_DOIS_PONTOS: return ":";
        case TOKEN_DELIMITADOR_VIRGULA: return ",";
        case TOKEN_DELIMITADOR_ABRE_PARENTESES: return "(";
        case TOKEN_DELIMITADOR_FECHA_PARENTESES: return ")";
        case TOKEN_DELIMITADOR_ABRE_COLCHETES: return "[";
        case TOKEN_DELIMITADOR_FECHA_COLCHETES: return "]";
        case TOKEN_DELIMITADOR_ABRE_CHAVES: return "{";
        case TOKEN_DELIMITADOR_FECHA_CHAVES: return "}";
        case TOKEN_NEWLINE: return "NEWLINE";
        case TOKEN_INDENT: return "INDENT";
        case TOKEN_DEDENT: return "DEDENT";
        case TOKEN_DESCONHECIDO: return "DESCONHECIDO";
        default: return "EOF";
    }
}
