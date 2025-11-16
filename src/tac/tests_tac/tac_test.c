#include <stdio.h>
#include "../ast/ast.h"
#include "../tac/tac.h"
#include "../st/st.h"

int main() {
    // Inicializa tabela de símbolos
    initST();

    /* ===== Exemplo 1: if (x < 10) x = 5 else x = 20 ===== */
    NoAST* id_x = criarNoId("x");
    NoAST* num10 = criarNoNum(10);
    NoAST* cond = criarNoOp('<', id_x, num10);

    NoAST* then_assign = criarNoAtribuicao(criarNoId("x"), criarNoNum(5));
    NoAST* else_assign = criarNoAtribuicao(criarNoId("x"), criarNoNum(20));

    NoAST* if_stmt = criarNoIf(cond, then_assign, else_assign);

    printf("\n--- TESTE TAC: IF ---\n");
    TacCodigo* codigo_if = gerar_tac(if_stmt);
    imprimir_tac(codigo_if);
    liberar_tac(codigo_if);
    liberarAST(if_stmt);

    /* ===== Exemplo 2: while (x < 5) x = x + 1 ===== */
    NoAST* cond_while = criarNoOp('<', criarNoId("x"), criarNoNum(5));
    NoAST* soma = criarNoOp('+', criarNoId("x"), criarNoNum(1));
    NoAST* atrib = criarNoAtribuicao(criarNoId("x"), soma);

    NoAST* while_stmt = criarNoWhile(cond_while, atrib);

    printf("\n--- TESTE TAC: WHILE ---\n");
    TacCodigo* codigo_while = gerar_tac(while_stmt);
    imprimir_tac(codigo_while);
    liberar_tac(codigo_while);
    liberarAST(while_stmt);

    // Finaliza tabela de símbolos
    freeST();

    return 0;
}
