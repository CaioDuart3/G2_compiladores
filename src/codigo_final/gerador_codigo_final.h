#ifndef GERADOR_CODIGO_FINAL_H
#define GERADOR_CODIGO_FINAL_H

#include <stdio.h>
#include "../tac/tac.h"

/**
 * @brief Gera código C padrão a partir da lista de instruções TAC.
 * * @param tac Ponteiro para a estrutura contendo o código de três endereços.
 * @param saida Ponteiro para o arquivo onde o código C será escrito.
 */
void gerar_codigo_final(TacCodigo* tac, FILE* saida);

#endif