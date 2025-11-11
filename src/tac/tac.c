/*
 * tac.c - Implementação do Gerador de Código de Três Endereços (TAC)
 *
 * "Visita" a AST e gera uma lista ligada de instruções TAC.
 */

#include "tac.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Variáveis Estáticas Globais (privadas para este arquivo) ---

// A lista de código que estamos construindo.
static TacCodigo* tac_global = NULL;

// Contadores para gerar nomes únicos para temporários e labels.
static int contador_temp = 0;
static int contador_label = 0;

// --- Funções Auxiliares Internas ---

/**
 * @brief Aloca e inicializa a estrutura principal do código TAC.
 * Reinicia os contadores globais.
 */
static void inicializar_gerador() {
    tac_global = (TacCodigo*) malloc(sizeof(TacCodigo));
    if (!tac_global) {
        fprintf(stderr, "Erro fatal: falha ao alocar TacCodigo.\n");
        exit(EXIT_FAILURE);
    }
    tac_global->inicio = NULL;
    tac_global->fim = NULL;
    contador_temp = 0;
    contador_label = 0;
}

/**
 * @brief Gera um novo nome de variável temporária (ex: "t0", "t1").
 * @return Uma nova string (alocada) com o nome do temporário.
 */
static char* novo_temp() {
    char buffer[20];
    sprintf(buffer, "t%d", contador_temp++);
    return strdup(buffer); // strdup aloca e copia a string
}

/**
 * @brief Gera um novo nome de label (ex: "L0", "L1").
 * @return Uma nova string (alocada) com o nome do label.
 */
static char* novo_label() {
    char buffer[20];
    sprintf(buffer, "L%d", contador_label++);
    return strdup(buffer);
}

/**
 * @brief Converte um valor inteiro para uma string alocada.
 * @param valor O inteiro a ser convertido.
 * @return Uma nova string (alocada) com o número.
 */
static char* int_para_string(int valor) {
    char buffer[20];
    sprintf(buffer, "%d", valor);
    return strdup(buffer);
}

/**
 * @brief Formata uma string literal (adiciona aspas).
 * @param str A string do nó (ex: "acabou").
 * @return Uma nova string (alocada) com o formato (ex: "\"acabou\"").
 */
static char* formatar_string_literal(const char* str) {
    // Aloca espaço para aspas + string + terminador nulo
    char* buffer = (char*) malloc(strlen(str) + 3);
    if (!buffer) {
        fprintf(stderr, "Erro fatal: falha ao alocar string literal.\n");
        exit(EXIT_FAILURE);
    }
    sprintf(buffer, "\"%s\"", str);
    return buffer;
}

/**
 * @brief Cria e "emite" (adiciona) uma nova instrução TAC ao fim da lista global.
 * @param op O opcode da instrução (ex: TAC_SOMA).
 * @param res O endereço de resultado (pode ser NULL).
 * @param arg1 O endereço do argumento 1 (pode ser NULL).
 * @param arg2 O endereço do argumento 2 (pode ser NULL).
 */
static void emitir(TacOpcode op, char* res, char* arg1, char* arg2) {
    TacInstrucao* nova = (TacInstrucao*) malloc(sizeof(TacInstrucao));
    if (!nova) {
        fprintf(stderr, "Erro fatal: falha ao alocar TacInstrucao.\n");
        exit(EXIT_FAILURE);
    }
    
    nova->op = op;
    nova->res = res;   // Esta função assume a "posse" das strings.
    nova->arg1 = arg1; // Elas devem ter sido alocadas (strdup, novo_temp, etc).
    nova->arg2 = arg2;
    nova->proxima = NULL;
    
    if (tac_global->inicio == NULL) {
        // Lista está vazia
        tac_global->inicio = nova;
        tac_global->fim = nova;
    } else {
        // Adiciona no fim da lista
        tac_global->fim->proxima = nova;
        tac_global->fim = nova;
    }
}

// --- O Visitor Recursivo (O Cérebro) ---

/**
 * @brief Processa recursivamente um nó da AST e gera o TAC correspondente.
 * @param no O nó da AST a ser processado.
 * @return Para nós de EXPRESSÃO, retorna o nome (char* alocado) do
 * temporário/variável/constante que contém o resultado.
 * Para nós de COMANDO (statements), retorna NULL.
 */
static char* processar_no(NoAST* no) {
    if (!no) return NULL;

    // Variáveis auxiliares para os resultados dos filhos
    char *res = NULL, *esq = NULL, *dir = NULL, *aux1 = NULL, *aux2 = NULL, *arg1 = NULL;
    NoAST *no_lista = NULL; // Para percorrer listas (params, args)

    switch (no->tipo) {
        
        // --- Casos Base (Folhas) ---
        // Retornam uma string alocada representando seu valor.
        case NO_NUM:
            return int_para_string(no->valor_int);
        case NO_BOOL:
            return int_para_string(no->valor_int); // 1 (True) ou 0 (False)
        case NO_ID:
            return strdup(no->valor_string); // Nome da variável
        case NO_STRING:
            return formatar_string_literal(no->valor_string);

        // --- Expressões ---
        // Geram TAC e retornam o nome do temporário (res) que guarda o resultado.
        case NO_OP_BINARIA:
            esq = processar_no(no->filho1);
            dir = processar_no(no->filho2);
            res = novo_temp();
            
            TacOpcode op;
            // Mapeia os operadores do seu ast.c (avaliarExpressao)
            switch (no->operador) {
                case '+': op = TAC_SOMA; break;
                case '-': op = TAC_SUB; break;
                case '*': op = TAC_MUL; break;
                case '/': op = TAC_DIV; break;
                case '<': op = TAC_MENOR; break;
                case '>': op = TAC_MAIOR; break;
                case 'l': op = TAC_MENOR_IGUAL; break; // (de "<=")
                case 'g': op = TAC_MAIOR_IGUAL; break; // (de ">=")
                case '=': op = TAC_IGUAL; break;       // (de "==")
                case '!': op = TAC_DIFERENTE; break;   // (de "!=")
                default:  op = TAC_INDEFINIDO; break;
            }
            
            emitir(op, res, esq, dir);
            free(esq); // Já usamos os resultados dos filhos
            free(dir);
            return res; // Retorna o temporário (ex: "t0")

        // Implementação de 'AND' e 'OR' com curto-circuito
        case NO_OP_LOGICA_AND:
            res = novo_temp();
            aux1 = novo_label(); // label_falso
            aux2 = novo_label(); // label_fim
            
            esq = processar_no(no->filho1);
            emitir(TAC_IFZ, aux1, esq, NULL); // if_false esq goto L_FALSO
            
            dir = processar_no(no->filho2);
            emitir(TAC_ATRIBUICAO, res, dir, NULL); // res = dir (resultado de B)
            emitir(TAC_GOTO, aux2, NULL, NULL);     // goto L_FIM
            
            emitir(TAC_LABEL, aux1, NULL, NULL);   // L_FALSO:
            emitir(TAC_ATRIBUICAO, res, strdup("0"), NULL); // res = 0 (False)
            
            emitir(TAC_LABEL, aux2, NULL, NULL);   // L_FIM:
            
            free(esq); free(dir); free(aux1); free(aux2);
            return res;
            
        case NO_OP_LOGICA_OR:
            res = novo_temp();
            aux1 = novo_label(); // label_verdadeiro
            aux2 = novo_label(); // label_fim
            
            esq = processar_no(no->filho1);
            // "if_true": não temos, então testamos o *oposto* de IFZ
            // (Isso é mais complexo. Vamos simplificar por agora)
            // Versão simples (sem curto-circuito)
            // dir = processar_no(no->filho2);
            // emitir(TAC_OR, res, esq, dir);
            // free(esq); free(dir);
            
            // Versão com curto-circuito (correta)
            emitir(TAC_IFZ, aux1, esq, NULL); // if_false esq goto L_TESTA_B
            emitir(TAC_ATRIBUICAO, res, strdup("1"), NULL); // res = 1 (True)
            emitir(TAC_GOTO, aux2, NULL, NULL);     // goto L_FIM

            emitir(TAC_LABEL, aux1, NULL, NULL);   // L_TESTA_B:
            dir = processar_no(no->filho2);
            emitir(TAC_ATRIBUICAO, res, dir, NULL); // res = dir (resultado de B)
            
            emitir(TAC_LABEL, aux2, NULL, NULL);   // L_FIM:
            
            free(esq); free(dir); free(aux1); free(aux2);
            return res;

        // --- Comandos (Statements) ---
        // Geram TAC mas retornam NULL.
        
        case NO_LISTA_COMANDOS:
            processar_no(no->filho1);  // Processa o comando atual
            processar_no(no->proximo); // Processa o resto da lista
            return NULL;

        case NO_ATRIBUICAO:
            // O filho1 (ID) não é processado, pegamos o nome diretamente
            res = strdup(no->filho1->valor_string);
            // Processamos a expressão (lado direito)
            arg1 = processar_no(no->filho2);
            
            emitir(TAC_ATRIBUICAO, res, arg1, NULL); // res = arg1 (ex: x = t0)
            
            // free(res); // NÃO! 'res' é o nome da variável, não foi alocado por nós.
            // Correção:
            // free(arg1); // SIM! 'arg1' é o temp/constante do lado direito.
            // Vamos refazer
            
            // REFAZENDO NO_ATRIBUICAO (correto):
            arg1 = processar_no(no->filho2); // Valor (ex: "t0")
            emitir(TAC_ATRIBUICAO, strdup(no->filho1->valor_string), arg1, NULL);
            free(arg1); // Libera o temp/constante do lado direito
            return NULL;
            
        case NO_IF:
            aux1 = novo_label(); // label_else
            aux2 = novo_label(); // label_fim_if
            
            // 1. Processa a condição
            res = processar_no(no->filho1);
            
            // 2. Emite o salto condicional
            //    (Se a condição 'res' for falsa (zero), pula para 'aux1' [label_else])
            emitir(TAC_IFZ, aux1, res, NULL);
            free(res); // Já usamos o resultado da condição
            
            // 3. Processa o bloco THEN
            processar_no(no->filho2);
            
            // 4. Se houver um 'else', precisamos pular sobre ele
            if (no->filho3) {
                emitir(TAC_GOTO, aux2, NULL, NULL);
            }
            
            // 5. Emite o label ELSE (ou fim, se não houver 'else')
            emitir(TAC_LABEL, aux1, NULL, NULL);
            
            // 6. Processa o bloco ELSE (se existir)
            if (no->filho3) {
                processar_no(no->filho3);
                // 7. Emite o label FIM
                emitir(TAC_LABEL, aux2, NULL, NULL);
                free(aux2);
            }
            
            free(aux1);
            return NULL;

        case NO_WHILE:
            aux1 = novo_label(); // label_inicio_loop
            aux2 = novo_label(); // label_fim_loop
            
            // 1. Emite o label de INÍCIO
            emitir(TAC_LABEL, aux1, NULL, NULL);
            
            // 2. Processa a condição
            res = processar_no(no->filho1);
            
            // 3. Emite o salto condicional (se for falso, pula para o fim 'aux2')
            emitir(TAC_IFZ, aux2, res, NULL);
            free(res);
            
            // 4. Processa o CORPO do loop
            processar_no(no->filho2);
            
            // 5. Emite o salto incondicional de volta para o INÍCIO
            emitir(TAC_GOTO, aux1, NULL, NULL);
            
            // 6. Emite o label de FIM
            emitir(TAC_LABEL, aux2, NULL, NULL);
            
            free(aux1);
            free(aux2);
            return NULL;
            
        case NO_FUNCAO:
            emitir(TAC_INICIO_FUNCAO, strdup(no->valor_string), NULL, NULL);
            // Processa a lista de parâmetros (filho1)
            no_lista = no->filho1;
            while (no_lista) {
                emitir(TAC_PARAM, strdup(no_lista->valor_string), NULL, NULL);
                no_lista = no_lista->proximo;
            }
            // Processa o corpo (filho2)
            processar_no(no->filho2);
            emitir(TAC_FIM_FUNCAO, strdup(no->valor_string), NULL, NULL);
            return NULL;
            
        case NO_RETORNO:
            if (no->filho1) {
                res = processar_no(no->filho1);
                emitir(TAC_RETORNO_VAL, NULL, res, NULL);
                free(res);
            } else {
                emitir(TAC_RETORNO_VAZIO, NULL, NULL, NULL);
            }
            return NULL;

        case NO_CHAMADA_FUNCAO:
            // 1. Processa todos os argumentos (filho2) e os emite
            no_lista = no->filho2;
            while (no_lista) {
                res = processar_no(no_lista);
                emitir(TAC_ARG, NULL, res, NULL);
                free(res);
                no_lista = no_lista->proximo;
            }
            
            // 2. Cria um temporário para o valor de retorno
            res = novo_temp();
            
            // 3. Emite a chamada
            // (filho1 é o NO_ID da função)
            emitir(TAC_CHAMADA, res, strdup(no->filho1->valor_string), NULL);
            
            // 4. Retorna o temporário que contém o resultado
            return res;

        // --- Nós ainda não implementados ---
        case NO_FOR:
        case NO_INDEX:
        case NO_LISTA:
        case NO_ATRIBUICAO_MULTIPLA:
            fprintf(stderr, "Aviso: Geração TAC para o nó %d ainda não implementada.\n", no->tipo);
            return NULL;

        case NO_VAZIO:
            return NULL; // Não gera código

        default:
            // Para nós "container" ou desconhecidos
            fprintf(stderr, "Aviso: Nó AST desconhecido (%d) encontrado pelo gerador TAC.\n", no->tipo);
            return NULL;
    }
}


// --- Funções Públicas (Definidas em tac.h) ---

TacCodigo* gerar_tac(NoAST* raiz) {
    inicializar_gerador();
    if (raiz) {
        processar_no(raiz);
    }
    return tac_global;
}

// Mapeia o enum para uma string para impressão
static const char* opcode_para_string(TacOpcode op) {
    switch(op) {
        case TAC_SOMA:          return "+";
        case TAC_SUB:           return "-";
        case TAC_MUL:           return "*";
        case TAC_DIV:           return "/";
        case TAC_AND:           return "&&"; // (TAC usa &&)
        case TAC_OR:            return "||"; // (TAC usa ||)
        case TAC_MENOR:         return "<";
        case TAC_MAIOR:         return ">";
        case TAC_MENOR_IGUAL:   return "<=";
        case TAC_MAIOR_IGUAL:   return ">=";
        case TAC_IGUAL:         return "==";
        case TAC_DIFERENTE:     return "!=";
        default:                return "?OP?";
    }
}

void imprimir_tac(TacCodigo* codigo) {
    if (!codigo) {
        printf("  (Código TAC vazio)\n");
        return;
    }
    
    for (TacInstrucao* inst = codigo->inicio; inst; inst = inst->proxima) {
        
        switch(inst->op) {
            case TAC_LABEL:
                printf("%s:\n", inst->res);
                break;
            case TAC_GOTO:
                printf("  goto %s\n", inst->res);
                break;
            case TAC_IFZ:
                printf("  if_false %s goto %s\n", inst->arg1, inst->res);
                break;
            case TAC_ATRIBUICAO:
                printf("  %s = %s\n", inst->res, inst->arg1);
                break;
            case TAC_INICIO_FUNCAO:
                printf("\n--- Início Função: %s ---\n", inst->res);
                break;
            case TAC_FIM_FUNCAO:
                printf("--- Fim Função: %s ---\n", inst->res);
                break;
            case TAC_PARAM:
                printf("  param %s\n", inst->res);
                break;
            case TAC_ARG:
                printf("  arg %s\n", inst->arg1);
                break;
            case TAC_CHAMADA:
                printf("  %s = call %s\n", inst->res, inst->arg1);
                break;
            case TAC_RETORNO_VAL:
                printf("  return %s\n", inst->arg1);
                break;
            case TAC_RETORNO_VAZIO:
                printf("  return\n");
                break;
            case TAC_INDEFINIDO:
                printf("  (instrução indefinida)\n");
                break;
            default:
                // Formato padrão: res = arg1 op arg2
                printf("  %s = %s %s %s\n", inst->res, inst->arg1, 
                       opcode_para_string(inst->op), inst->arg2);
                break;
        }
    }
}

void liberar_tac(TacCodigo* codigo) {
    if (!codigo) return;
    
    TacInstrucao* inst = codigo->inicio;
    while (inst) {
        // Libera as strings alocadas dentro da instrução
        if(inst->res) free(inst->res);
        if(inst->arg1) free(inst->arg1);
        if(inst->arg2) free(inst->arg2);
        
        // Guarda o ponteiro para a próxima
        TacInstrucao* proxima = inst->proxima;
        
        // Libera a instrução atual
        free(inst);
        
        // Avança
        inst = proxima;
    }
    
    // Libera a estrutura container
    free(codigo);
}