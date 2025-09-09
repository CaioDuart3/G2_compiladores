%{
#include <stdio.h>
%}

DIGITO      [0-9]
LETRA       [a-zA-Z_]
ID          {LETRA}({LETRA}|{DIGITO})*


%%
"if"        { printf("PALAVRA-CHAVE IF\n"); }
"else"      { printf("PALAVRA-CHAVE ELSE\n"); }
"while"     { printf("PALAVRA-CHAVE WHILE\n"); }
"for"       { printf("PALAVRA-CHAVE FOR\n"); }
"def"       { printf("PALAVRA-CHAVE DEF\n"); }
"return"    { printf("PALAVRA-CHAVE RETURN\n"); }

{ID}        { printf("IDENTIFICADOR: %s\n", yytext); }

{DIGITO}+   { printf("NUMERO-INTEIRO: %s\n", yytext); }
{DIGITO}+"."{DIGITO}+ { printf("NUMERO-FLOAT: %s\n", yytext); }

\"[^\"]*\"  { printf("STRING: %s\n", yytext); }
\'[^\']*\'  { printf("STRING: %s\n", yytext); }

"=="        { printf("OPERADOR: ==\n"); }
"!="        { printf("OPERADOR: !=\n"); }
"<="        { printf("OPERADOR: <=\n"); }
">="        { printf("OPERADOR: >=\n"); }
"<"         { printf("OPERADOR: <\n"); }
">"         { printf("OPERADOR: >\n"); }
"="         { printf("OPERADOR: =\n"); }
"\+"        { printf("OPERADOR: +\n"); }
"-"         { printf("OPERADOR: -\n"); }
"\*"        { printf("OPERADOR: *\n"); }
"/"         { printf("OPERADOR: /\n"); }

":"         { printf("DELIMITADOR: :\n"); }
","         { printf("DELIMITADOR: ,\n"); }
"\("        { printf("DELIMITADOR: (\n"); }
"\)"        { printf("DELIMITADOR: )\n"); }
"\["        { printf("DELIMITADOR: [\n"); }
"\]"        { printf("DELIMITADOR: ]\n"); }
"{"         { printf("DELIMITADOR: {\n"); }
"}"         { printf("DELIMITADOR: }\n"); }

"#".*       { /* comentário, ignora */ }

[ \t\n]+    { /* ignora espaços e quebras de linha */ }

.           { printf("CARACTERE DESCONHECIDO: %s\n", yytext); }
%%

int main(int argc, char **argv) {
    yylex();
    return 0;
}
