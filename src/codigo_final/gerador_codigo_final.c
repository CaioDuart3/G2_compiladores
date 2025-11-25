#include "gerador_codigo_final.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Converte uma instrução TAC para código C equivalente
 */
static void traduzir_instrucao_c(TacInstrucao* inst, FILE* saida) {
    if (!inst) return;

    switch (inst->op) {
        // Atribuições
        case TAC_ATRIBUICAO:
            fprintf(saida, "    %s = %s;\n", inst->res, inst->arg1);
            break;

        // Operações aritméticas
        case TAC_SOMA: case TAC_SUB: case TAC_MUL: case TAC_DIV:
        case TAC_SOMA_F: case TAC_SUB_F: case TAC_MUL_F: case TAC_DIV_F:
        {
            const char* op = "?";
            switch (inst->op) {
                case TAC_SOMA: case TAC_SOMA_F: op = "+"; break;
                case TAC_SUB: case TAC_SUB_F: op = "-"; break;
                case TAC_MUL: case TAC_MUL_F: op = "*"; break;
                case TAC_DIV: case TAC_DIV_F: op = "/"; break;
                default: break;
            }
            fprintf(saida, "    %s = %s %s %s;\n", inst->res, inst->arg1, op, inst->arg2);
            break;
        }

        // Controle de fluxo
        case TAC_LABEL:
            fprintf(saida, "%s:\n", inst->res);
            break;

        case TAC_GOTO:
            fprintf(saida, "    goto %s;\n", inst->res);
            break;

        case TAC_IFZ:
            fprintf(saida, "    if (!%s) goto %s;\n", inst->arg1, inst->res);
            break;

        // Funções
        case TAC_INICIO_FUNCAO:
            fprintf(saida, "\nvoid %s() {\n", inst->res);
            break;

        case TAC_FIM_FUNCAO:
            fprintf(saida, "}\n");
            break;

        case TAC_PARAM:
            // Pode ser ignorado no C, pois parâmetro já vem na função
            break;

        case TAC_ARG:
            // Para funções simples sem pilha, podemos ignorar
            break;

        case TAC_CHAMADA:
            fprintf(saida, "    %s = %s();\n", inst->res, inst->arg1);
            break;

        case TAC_RETORNO_VAL:
            fprintf(saida, "    return %s;\n", inst->arg1);
            break;

        case TAC_RETORNO_VAZIO:
            fprintf(saida, "    return;\n");
            break;

        // Vetores
        case TAC_VET_ALLOC:
            fprintf(saida, "    int %s[%s];\n", inst->res, inst->arg1); // Assume int
            break;

        case TAC_VET_SET:
            fprintf(saida, "    %s[%s] = %s;\n", inst->res, inst->arg1, inst->arg2);
            break;

        case TAC_VET_GET:
            fprintf(saida, "    %s = %s[%s];\n", inst->res, inst->arg1, inst->arg2);
            break;

        default:
            fprintf(saida, "    /* Instrução indefinida */\n");
            break;
    }
}

/**
 * @brief Gera o código C completo a partir do TAC
 */
void gerar_codigo_final(TacCodigo* tac, FILE* saida) {
    if (!tac || !saida) return;

    fprintf(saida, "#include <stdio.h>\n#include <stdlib.h>\n\nint main() {\n");

    for (TacInstrucao* inst = tac->inicio; inst; inst = inst->proxima) {
        traduzir_instrucao_c(inst, saida);
    }

    fprintf(saida, "    return 0;\n}\n");
}
