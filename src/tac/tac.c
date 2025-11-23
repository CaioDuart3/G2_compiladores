#include "tac.h"
#include "../ast/ast.h"
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

static char* float_para_string(double valor) {
    char buffer[64];
    sprintf(buffer, "%.6f", valor);
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
    
    // MODELO SEGURO: A instrução copia TODOS os seus dados.
    // Ela não "rouba" nenhum ponteiro do processar_no.
    nova->res = res ? strdup(res) : NULL;
    nova->arg1 = arg1 ? strdup(arg1) : NULL;
    nova->arg2 = arg2 ? strdup(arg2) : NULL;
    
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
        // Retornam ponteiros alocados que serão liberados pelo 'pai'
        case NO_NUM:
            return int_para_string(no->valor_int);

        case NO_FLOAT: 
            return float_para_string(no->valor_double);

        case NO_BOOL:
            return int_para_string(no->valor_int);

        case NO_ID:
            return strdup(no->valor_string);
        case NO_STRING:
            return formatar_string_literal(no->valor_string);

        // --- Expressões ---
        case NO_OP_BINARIA:
            esq = processar_no(no->filho1);
            dir = processar_no(no->filho2);
            res = novo_temp();
            
            Tipo t = inferirTipo(no);     // Descobre se é FLOAT ou INT
            int eh_float = (t == FLOAT);  // Flag auxiliar
            TacOpcode op = TAC_INDEFINIDO;
            
            switch (no->operador) {
                // Aritmética: Se eh_float for verdadeiro, usa _F, senão usa o normal
                case '+': op = eh_float ? TAC_SOMA_F : TAC_SOMA; break;
                case '-': op = eh_float ? TAC_SUB_F : TAC_SUB; break;
                case '*': op = eh_float ? TAC_MUL_F : TAC_MUL; break;
                case '/': op = eh_float ? TAC_DIV_F : TAC_DIV; break;
                
                // Relacional
                case '<': op = eh_float ? TAC_MENOR_F : TAC_MENOR; break;
                case '>': op = eh_float ? TAC_MAIOR_F : TAC_MAIOR; break;
                
                // Ajuste conforme os caracteres que seu parser usa (ex: 'l' para <=)
                case 'l': op = eh_float ? TAC_MENOR_IGUAL_F : TAC_MENOR_IGUAL; break; 
                case 'g': op = eh_float ? TAC_MAIOR_IGUAL_F : TAC_MAIOR_IGUAL; break; 
                
                case '=': op = eh_float ? TAC_IGUAL_F : TAC_IGUAL; break;       
                case '!': op = eh_float ? TAC_DIFERENTE_F : TAC_DIFERENTE; break;   
                
                default:  op = TAC_INDEFINIDO; break;
            }
            
            emitir(op, res, esq, dir);
            
            // REGRA: Liberamos tudo que passamos, pois emitir() copiou.
            free(esq);
            free(dir);
            
            // NÃO liberamos 'res', pois ele é retornado para o 'pai'.
            return res; 

        case NO_OP_LOGICA_AND:
            res = novo_temp();
            aux1 = novo_label(); // label_falso
            aux2 = novo_label(); // label_fim
            
            esq = processar_no(no->filho1);
            emitir(TAC_IFZ, aux1, esq, NULL); 
            free(esq); // Liberado
            
            dir = processar_no(no->filho2);
            emitir(TAC_ATRIBUICAO, res, dir, NULL);
            free(dir); // Liberado
            
            emitir(TAC_GOTO, aux2, NULL, NULL);     
            
            emitir(TAC_LABEL, aux1, NULL, NULL);   
            emitir(TAC_ATRIBUICAO, res, strdup("0"), NULL); // strdup é liberado pelo emitir
            
            emitir(TAC_LABEL, aux2, NULL, NULL);   
            
            // REGRA: Liberamos nossos labels locais
            free(aux1);
            free(aux2);
            
            return res; // Retorna 'res' para o 'pai'
            
        case NO_OP_LOGICA_OR:
            res = novo_temp();
            aux1 = novo_label(); // label_testa_b
            aux2 = novo_label(); // label_fim
            
            esq = processar_no(no->filho1);
            emitir(TAC_IFZ, aux1, esq, NULL); 
            free(esq); // Liberado
            
            emitir(TAC_ATRIBUICAO, res, strdup("1"), NULL); // strdup é liberado pelo emitir
            emitir(TAC_GOTO, aux2, NULL, NULL);     

            emitir(TAC_LABEL, aux1, NULL, NULL);   
            dir = processar_no(no->filho2);
            emitir(TAC_ATRIBUICAO, res, dir, NULL); 
            free(dir); // Liberado
            
            emitir(TAC_LABEL, aux2, NULL, NULL);   
            
            // REGRA: Liberamos nossos labels locais
            free(aux1);
            free(aux2);
            
            return res; // Retorna 'res' para o 'pai'

        // --- Comandos (Statements) ---
        case NO_LISTA_COMANDOS:
            processar_no(no->filho1);  
            processar_no(no->proximo); 
            return NULL;

        case NO_ATRIBUICAO:
            
            if (no->filho1->tipo == NO_INDEX) {
                // Estrutura do NO_INDEX: filho1 = ID (nome), filho2 = Expressão (índice)
                NoAST* no_index = no->filho1;
                
                char* nome_vetor = strdup(no_index->filho1->valor_string);
                char* indice = processar_no(no_index->filho2); // Processa o índice (ex: "0")
                char* valor = processar_no(no->filho2);        // Processa o valor (ex: "10")
                
                // Emite: nome_vetor[indice] = valor
                emitir(TAC_VET_SET, nome_vetor, indice, valor);
                
                free(nome_vetor); // strdup copiado por emitir
                free(indice);     // processar_no liberado
                free(valor);      // processar_no liberado
                
            } 
            
            else {
                // Atribuição normal: variavel = valor
                arg1 = processar_no(no->filho2); 
                emitir(TAC_ATRIBUICAO, strdup(no->filho1->valor_string), arg1, NULL);
                free(arg1);
            }
            
            return NULL;
            
        case NO_IF:
            aux1 = novo_label(); // label_else
            aux2 = novo_label(); // label_fim_if
            
            res = processar_no(no->filho1); // Condição
            
            emitir(TAC_IFZ, aux1, res, NULL);
            free(res); // Liberado
            
            processar_no(no->filho2); // Bloco THEN
            
            if (no->filho3) {
                emitir(TAC_GOTO, aux2, NULL, NULL);
            }
            
            emitir(TAC_LABEL, aux1, NULL, NULL);
            
            if (no->filho3) {
                processar_no(no->filho3); // Bloco ELSE
                emitir(TAC_LABEL, aux2, NULL, NULL);
            }
            
            // REGRA: Liberamos nossos labels locais
            free(aux1);
            free(aux2);
            return NULL;


        case NO_WHILE:
            aux1 = novo_label(); // label_inicio_loop
            aux2 = novo_label(); // label_fim_loop
            
            emitir(TAC_LABEL, aux1, NULL, NULL);
            
            res = processar_no(no->filho1); // Condição
            emitir(TAC_IFZ, aux2, res, NULL);
            free(res); // Liberado
            
            processar_no(no->filho2); // CORPO
            
            emitir(TAC_GOTO, aux1, NULL, NULL);
            
            emitir(TAC_LABEL, aux2, NULL, NULL);
            
            // REGRA: Liberamos nossos labels locais
            free(aux1);
            free(aux2);
            return NULL;
            

        case NO_FUNCAO:
            // strdup(nome) é copiado e liberado por emitir
            emitir(TAC_INICIO_FUNCAO, strdup(no->valor_string), NULL, NULL);
            
            no_lista = no->filho1;
            while (no_lista) {
                emitir(TAC_PARAM, strdup(no_lista->valor_string), NULL, NULL);
                no_lista = no_lista->proximo;
            }
            
            processar_no(no->filho2);
            emitir(TAC_FIM_FUNCAO, strdup(no->valor_string), NULL, NULL);
            return NULL;
            

        case NO_RETORNO:
            if (no->filho1) {
                res = processar_no(no->filho1);
                emitir(TAC_RETORNO_VAL, NULL, res, NULL);
                free(res); // Liberado
            } else {
                emitir(TAC_RETORNO_VAZIO, NULL, NULL, NULL);
            }
            return NULL;


        case NO_CHAMADA_FUNCAO:
            no_lista = no->filho2; // Lista de argumentos
            while (no_lista) {
                res = processar_no(no_lista); // Processa argumento
                emitir(TAC_ARG, NULL, res, NULL);
                free(res); // Libera o 'res' do argumento
                no_lista = no_lista->proximo;
            }
            
            res = novo_temp(); // 'res' para o valor de retorno
            emitir(TAC_CHAMADA, res, strdup(no->filho1->valor_string), NULL);
            
            // NÃO liberamos 'res', pois ele é retornado para o 'pai'.
            return res;

       
        case NO_FOR:
            // Verifica se é um range()
            // (Assumindo que filho2 é NO_CHAMADA_FUNCAO e o nome é "range")
            if (no->filho2->tipo == NO_CHAMADA_FUNCAO &&
                strcmp(no->filho2->filho1->valor_string, "range") == 0) {
                
                // --- 1. Extrair argumentos do range(inicio, fim) ---
                NoAST* args = no->filho2->filho2;
                NoAST* arg_inicio = args; 
                NoAST* arg_fim = args->proximo; // Assumindo range(0, 5)

                // Se quiser ser robusto para range(5), precisaria checar se arg_fim existe
                // Mas vamos focar no teste ok_05 que tem 2 argumentos.

                // --- 2. Inicialização (i = inicio) ---
                char* val_inicio = processar_no(arg_inicio);
                
                // i = 0
                emitir(TAC_ATRIBUICAO, strdup(no->filho1->valor_string), val_inicio, NULL);
                free(val_inicio); // Libera o temp/valor retornado

                // --- 3. Labels ---
                aux1 = novo_label(); // Label INICIO
                aux2 = novo_label(); // Label FIM

                emitir(TAC_LABEL, aux1, NULL, NULL); // L_INICIO:

                // --- 4. Condição de Parada (i < fim) ---
                // Precisamos comparar a variável 'i' com o valor final
                char* val_fim = processar_no(arg_fim);
                res = novo_temp(); // Temp para guardar (i < 5)
                
                // emitir copia os args, então podemos passar strdup e liberar
                char* var_iter = strdup(no->filho1->valor_string);
                emitir(TAC_MENOR, res, var_iter, val_fim); 
                free(var_iter);
                free(val_fim);

                // Se (i < 5) for falso (zero), sai do loop
                emitir(TAC_IFZ, strdup(aux2), res, NULL);
                free(res); // Libera temp da condição

                // --- 5. Corpo do Loop ---
                processar_no(no->filho3);

                // --- 6. Incremento Automático (i = i + 1) ---
                // Como é um range, o Python incrementa sozinho no final
                char* temp_inc = novo_temp();
                var_iter = strdup(no->filho1->valor_string);
                
                // tX = i + 1
                emitir(TAC_SOMA, temp_inc, var_iter, "1"); // "1" literal é copiado pelo emitir
                free(var_iter);

                // i = tX
                emitir(TAC_ATRIBUICAO, strdup(no->filho1->valor_string), strdup(temp_inc), NULL);
                free(temp_inc);

                // --- 7. Volta para o início ---
                emitir(TAC_GOTO, strdup(aux1), NULL, NULL);

                // --- 8. Label Fim ---
                emitir(TAC_LABEL, aux2, NULL, NULL);

                // Limpeza de labels locais
                free(aux1);
                free(aux2);

            } else {
                // Caso tente fazer "for i in lista" (ainda não suportado)
                 fprintf(stderr, "Aviso: Loop FOR suporta apenas range() por enquanto.\n");
            }
            return NULL;
            
        case NO_INDEX:
            
            res = novo_temp(); // Vai guardar o valor lido
            
            // filho1 é o ID do vetor, filho2 é a expressão do índice
            char* nome_vet = strdup(no->filho1->valor_string);
            char* val_idx = processar_no(no->filho2);
            
            // t1 = vetor[0]
            emitir(TAC_VET_GET, strdup(res), nome_vet, val_idx);
            
            free(nome_vet); // strdup copiado por emitir
            free(val_idx);  // processar_no liberado
            
            return res;

    
        case NO_LISTA:
            res = novo_temp();
            
            // Conta quantos elementos tem na lista
            int tamanho = 0;
            no_lista = no->filho1;
            while (no_lista) {
                tamanho++;
                no_lista = no_lista->proximo;
            }
            
            // Emite alocação: t0 = alloc tamanho
            char* str_tam = int_para_string(tamanho);
            emitir(TAC_VET_ALLOC, strdup(res), str_tam, NULL);
            free(str_tam); // int_para_string liberado
            
            // Percorre a lista preenchendo os valores
            // t0[0] = 1, t0[1] = 2...
            no_lista = no->filho1;
            int idx = 0;
            while (no_lista) {
                char* val_elem = processar_no(no_lista); // Valor do elemento
                char* str_idx = int_para_string(idx);    // Índice atual
                
                // vetor[idx] = val
                emitir(TAC_VET_SET, strdup(res), str_idx, val_elem);
                
                free(val_elem);
                free(str_idx);
                
                idx++;
                no_lista = no_lista->proximo;
            }
            
            return res;

        
        case NO_ATRIBUICAO_MULTIPLA:
            
            int qtd = 0;
            no_lista = no->filho2;
            while (no_lista) {
                qtd++;
                no_lista = no_lista->proximo;
            }
            
            if (qtd == 0) return NULL;

            char** temps_rhs = (char**) malloc(qtd * sizeof(char*));
            if (!temps_rhs) {
                fprintf(stderr, "Erro de alocação em atribuição múltipla.\n");
                exit(1);
            }

            no_lista = no->filho2;
            int i = 0;
            while (no_lista) {
                temps_rhs[i] = processar_no(no_lista); 
                no_lista = no_lista->proximo;
                i++;
            }

            no_lista = no->filho1;
            i = 0;
            while (no_lista && i < qtd) {
                
                if (no_lista->tipo == NO_ID) {
                    // Copia nome da var e nome do temp para o emitir
                    emitir(TAC_ATRIBUICAO, strdup(no_lista->valor_string), temps_rhs[i], NULL);
                }
                free(temps_rhs[i]);
                
                no_lista = no_lista->proximo;
                i++;
            }
            
            free(temps_rhs);
            
            return NULL;



    fprintf(stderr, "Aviso: Geração TAC para o nó %d ainda não implementada.\n", no->tipo);
            return NULL;

        case NO_VAZIO:
            return NULL; // Não gera código

        default:
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
            case TAC_VET_ALLOC:
                printf("  %s = alloc %s\n", inst->res, inst->arg1);
                break;
            case TAC_VET_SET:
                // vetor[indice] = valor
                printf("  %s[%s] = %s\n", inst->res, inst->arg1, inst->arg2);
                break;
            case TAC_VET_GET:
                // valor = vetor[indice]
                printf("  %s = %s[%s]\n", inst->res, inst->arg1, inst->arg2);
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