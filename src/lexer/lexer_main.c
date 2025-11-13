#include <stdio.h>
#include "../parser/parser.tab.h"

int yylex(void);
YYSTYPE yylval;
extern int yylineno;
extern char* yytext;
extern void inicializa_pilha();

/* * Este é um main "falso" que só testa o lexer.
 * Ele simplesmente pede tokens ao lexer até o fim do arquivo.
 * Se encontrar um TOKEN_DESCONHECIDO, falha (retorna 1).
 * Se chegar ao fim (EOF), passa (retorna 0).
 */
int main(void) {
    inicializa_pilha();
    yylineno = 1;
    
    int token;
    // Puxa tokens até o yylex() retornar 0 (EOF)
    while ((token = yylex())) { 
        
        // Se o lexer reportar um token desconhecido, é um erro léxico.
        if (token == TOKEN_DESCONHECIDO) {
            // A mensagem de "ERRO LÉXICO" já é impressa pelo próprio lexer.
            return 1; // Retorna código de erro
        }
    }

    return 0;
}