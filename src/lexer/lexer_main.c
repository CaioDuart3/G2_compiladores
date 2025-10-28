#include <stdio.h>
#include "../parser/parser.tab.h" // Para ter a definição dos tokens

// Declarações de funções e variáveis do Flex
int yylex(void);
YYSTYPE yylval; // <<< MUDANÇA: Define a variável que o linker estava procurando
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
    // <<< MUDANÇA: Parênteses extras para remover o warning
    while ((token = yylex())) { 
        
        // Se o lexer reportar um token desconhecido, é um erro léxico.
        if (token == TOKEN_DESCONHECIDO) {
            // A mensagem de "ERRO LÉXICO" já é impressa pelo próprio lexer.
            return 1; // Retorna código de erro
        }
    }
    
    // Chegou ao fim do arquivo sem erros léxicos
    return 0; // Sucesso
}