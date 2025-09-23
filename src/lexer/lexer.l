%{
#include <stdio.h>
#include <string.h>

/* Enumeração para os tipos de tokens */
typedef enum {
    TOKEN_EOF = 0,
    TOKEN_IDENTIFICADOR,
    TOKEN_INTEIRO,
    TOKEN_FLOAT,
    TOKEN_STRING,
    TOKEN_PALAVRA_CHAVE_IF,
    TOKEN_PALAVRA_CHAVE_ELSE,
    TOKEN_PALAVRA_CHAVE_ELIF,
    TOKEN_PALAVRA_CHAVE_WHILE,
    TOKEN_PALAVRA_CHAVE_FOR,
    TOKEN_PALAVRA_CHAVE_DEF,
    TOKEN_PALAVRA_CHAVE_RETURN,
    TOKEN_PALAVRA_CHAVE_IN,
    TOKEN_OPERADOR_IGUAL,
    TOKEN_OPERADOR_DIFERENTE,
    TOKEN_OPERADOR_MENOR_IGUAL,
    TOKEN_OPERADOR_MAIOR_IGUAL,
    TOKEN_OPERADOR_MENOR,
    TOKEN_OPERADOR_MAIOR,
    TOKEN_OPERADOR_ATRIBUICAO,
    TOKEN_OPERADOR_MAIS,
    TOKEN_OPERADOR_MENOS,
    TOKEN_OPERADOR_MULTIPLICACAO,
    TOKEN_OPERADOR_DIVISAO,
    TOKEN_DELIMITADOR_DOIS_PONTOS,
    TOKEN_DELIMITADOR_VIRGULA,
    TOKEN_DELIMITADOR_ABRE_PARENTESES,
    TOKEN_DELIMITADOR_FECHA_PARENTESES,
    TOKEN_DELIMITADOR_ABRE_COLCHETES,
    TOKEN_DELIMITADOR_FECHA_COLCHETES,
    TOKEN_DELIMITADOR_ABRE_CHAVES,
    TOKEN_DELIMITADOR_FECHA_CHAVES,
    TOKEN_DESCONHECIDO
} TokenType;

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

{ID}        { yytoken_value = strdup(yytext); return TOKEN_IDENTIFICADOR; }

{DIGITO}+   { yytoken_value = strdup(yytext); return TOKEN_INTEIRO; }
{DIGITO}+"."{DIGITO}+ { yytoken_value = strdup(yytext); return TOKEN_FLOAT; }

\"[^\"]*\"  { yytoken_value = strdup(yytext); return TOKEN_STRING; }
\'[^\']*\'  { yytoken_value = strdup(yytext); return TOKEN_STRING; }

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

"#".* { /* comentário, ignora */ }

[ \t\n]+    { /* ignora espaços e quebras de linha */ }

.           { printf("ERROR: Caractere invalido '%s'\n", yytext); return TOKEN_DESCONHECIDO; }
%%

const char *token_to_string(TokenType token) {
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
        case TOKEN_DESCONHECIDO: return "CARACTERE DESCONHECIDO";
        default: return "EOF";
    }
}

int main(int argc, char **argv) {
    TokenType token;
    while ((token = yylex()) != TOKEN_EOF) {
        printf("TOKEN: %s", token_to_string(token));
        if (token == TOKEN_IDENTIFICADOR || token == TOKEN_INTEIRO || token == TOKEN_FLOAT || token == TOKEN_STRING) {
            printf(": %s", yytoken_value);
            free(yytoken_value); /* Libera a memória alocada */
        }
        printf("\n");
    }
    return 0;
}