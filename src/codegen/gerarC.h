#ifndef GERAR_C_H
#define GERAR_C_H

#include <stdio.h>
#include "ast.h"

// --- Funções principais ---
void gerarCabecalhoC(FILE *saida);
void gerarDeclaracoesVariaveis(FILE *saida);
void gerarC(NoAST *no, FILE *saida, int indent);

// --- Função auxiliar para imprimir indentação ---
void printIndent(FILE *saida, int indent);

#endif // GERAR_C_H
