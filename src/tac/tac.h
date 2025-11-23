#ifndef TAC_H
#define TAC_H

#include "../ast/ast.h" 

// --- Opcodes do TAC ---
typedef enum {
    TAC_INDEFINIDO, // Para debug
    TAC_ATRIBUICAO, // res = arg1 (ex: x = t1)
    
    // Operações Aritméticas (Inteiros)
    TAC_SOMA, // res = arg1 + arg2
    TAC_SUB, // res = arg1 - arg2
    TAC_MUL, // res = arg1 * arg2
    TAC_DIV, // res = arg1 / arg2
    
    // Operações Lógicas
    TAC_AND, // res = arg1 and arg2
    TAC_OR, // res = arg1 or arg2
    TAC_NOT, // res = not arg1 (Adicionei caso precise)
    
    // Operações Relacionais (Inteiros)
    TAC_MENOR, // res = arg1 < arg2
    TAC_MAIOR, // res = arg1 > arg2
    TAC_MENOR_IGUAL, // res = arg1 <= arg2
    TAC_MAIOR_IGUAL, // res = arg1 >= arg2
    TAC_IGUAL, // res = arg1 == arg2
    TAC_DIFERENTE,  // res = arg1 != arg2

    /* --- NOVOS: Operações de Float (ADICIONADOS AQUI) --- */
    TAC_SOMA_F,      // res = arg1 + arg2 (float)
    TAC_SUB_F,       // res = arg1 - arg2 (float)
    TAC_MUL_F,       // res = arg1 * arg2 (float)
    TAC_DIV_F,       // res = arg1 / arg2 (float)
    
    TAC_MENOR_F,       // < (float)
    TAC_MAIOR_F,       // > (float)
    TAC_MENOR_IGUAL_F, // <= (float)
    TAC_MAIOR_IGUAL_F, // >= (float)
    TAC_IGUAL_F,       // == (float)
    TAC_DIFERENTE_F,   // != (float)
    
    // Controle de Fluxo
    TAC_LABEL, // res:
    TAC_GOTO, // goto res
    TAC_IFZ, // if_false arg1 goto res (If Zero / Se Falso)
    
    // Funções
    TAC_INICIO_FUNCAO, // Início de uma função (marcação)
    TAC_FIM_FUNCAO, // Fim de uma função (marcação)
    TAC_PARAM, // Define um parâmetro (ex: t1 é um param)
    TAC_ARG, // Passa um argumento para uma chamada
    TAC_CHAMADA, // res = call arg1 (arg1=nome da func)
    TAC_RETORNO_VAL, // return arg1
    TAC_RETORNO_VAZIO, // return (void)
    
    // Vetores
    TAC_VET_ALLOC,  // res = alloc tamanho
    TAC_VET_SET,    // res[arg1] = arg2
    TAC_VET_GET     // res = arg1[arg2]
    
} TacOpcode;

// --- Estrutura da Instrução ---
typedef struct TacInstrucao {
    TacOpcode op;
    
    // Os "Três Endereços": strings que representam
    // variáveis, temporários, constantes ou labels.
    char* res;
    char* arg1;
    char* arg2;
    
    struct TacInstrucao* proxima; // Ponteiro para a próxima instrução
} TacInstrucao;

// --- Estrutura do Código ---
typedef struct {
    TacInstrucao* inicio;
    TacInstrucao* fim;
} TacCodigo;

// --- Funções Públicas ---
/**
 * @brief Função principal que gera o código TAC a partir da raiz da AST.
 * @param raiz O ponteiro para o nó raiz da AST (seu 'ast_root').
 * @return Um ponteiro para a estrutura TacCodigo contendo a lista de instruções.
 */
TacCodigo* gerar_tac(NoAST* raiz);

/**
 * @brief Imprime o código TAC gerado de forma legível no console.
 * @param codigo O ponteiro para a estrutura TacCodigo.
 */
void imprimir_tac(TacCodigo* codigo);

/**
 * @brief Libera toda a memória alocada para o código TAC.
 * @param codigo O ponteiro para a estrutura TacCodigo.
 */
void liberar_tac(TacCodigo* codigo);

#endif