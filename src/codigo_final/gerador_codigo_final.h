#ifndef GERADOR_CODIGO_FINAL_H
#define GERADOR_CODIGO_FINAL_H

#include "tac.h"

// Função principal que gera código C a partir do TAC
// 'saida' pode ser um arquivo aberto para escrita (ex: stdout ou fopen)
void gerar_codigo_final(TacCodigo* tac, FILE* saida);

#endif
