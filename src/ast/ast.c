#include "ast.h"
#include "../st/st.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função auxiliar interna para alocar e inicializar um nó
static NoAST *alocarNo(TipoNo tipo) {
    NoAST *novo = malloc(sizeof(NoAST));
    if (!novo) {
        fprintf(stderr, "Erro: falha ao alocar memória para nó.\n");
        exit(EXIT_FAILURE);
    }
    
    novo->tipo = tipo;
    novo->valor_int = 0;
    novo->valor_string = NULL;
    novo->operador = '\0';
    novo->filho1 = NULL;
    novo->filho2 = NULL;
    novo->filho3 = NULL;
    novo->proximo = NULL;
    
    return novo;
}

// --- Funções de Criação de Nós ("Fábricas") ---

NoAST *criarNoNum(int valor) {
    NoAST *novo = alocarNo(NO_NUM);
    novo->valor_int = valor;
    return novo;
}

NoAST *criarNoId(char *nome) {
    NoAST *novo = alocarNo(NO_ID);
    novo->valor_string = strdup(nome); // Copia a string
    return novo;
}

NoAST *criarNoString(char *texto) {
    NoAST *novo = alocarNo(NO_STRING);
    // Remove as aspas (simples ou duplas)
    int len = strlen(texto);
    if (len >= 2) {
        novo->valor_string = strndup(texto + 1, len - 2);
    } else {
        novo->valor_string = strdup(""); // String vazia se algo der errado
    }
    return novo;
}

NoAST *criarNoBool(int valor) {
    NoAST *novo = alocarNo(NO_BOOL);
    novo->valor_int = (valor != 0); // Garante 0 ou 1
    return novo;
}

NoAST *criarNoVazio() {
    return alocarNo(NO_VAZIO);
}

NoAST *criarNoOp(char operador, NoAST *esq, NoAST *dir) {
    NoAST *no = malloc(sizeof(NoAST));
    no->tipo = NO_OP_BINARIA;
    no->operador = operador;
    no->filho1 = esq;
    no->filho2 = dir;
    no->filho3 = NULL;
    no->proximo = NULL;
    return no;
}


NoAST *criarNoAtribuicao(NoAST *id, NoAST *expr) {
    NoAST *novo = alocarNo(NO_ATRIBUICAO);
    novo->filho1 = id;
    novo->filho2 = expr;
    return novo;
}

NoAST *criarNoIf(NoAST *cond, NoAST *blocoThen, NoAST *blocoElse) {
    NoAST *novo = alocarNo(NO_IF);
    novo->filho1 = cond;
    novo->filho2 = blocoThen;
    novo->filho3 = blocoElse; // Pode ser NULL
    return novo;
}

NoAST *criarNoLista(NoAST *comando, NoAST *proximaLista) {
    NoAST *novo = alocarNo(NO_LISTA_COMANDOS);
    novo->filho1 = comando;
    novo->proximo = proximaLista;
    return novo;
}

// Nós de atribuição múltipla
NoAST* criarListaIds(char* nome) {
    NoAST* no = criarNoId(nome);
    no->proximo = NULL;
    return no;
}

NoAST* adicionaIdNaLista(NoAST* lista, char* nome) {
    NoAST* novo = criarNoId(nome);
    novo->proximo = NULL;

    NoAST* temp = lista;
    while (temp->proximo != NULL)
        temp = temp->proximo;

    temp->proximo = novo;
    return lista;
}

NoAST* criarListaExp(NoAST* exp) {
    exp->proximo = NULL;
    return exp;
}

NoAST* adicionaExpNaLista(NoAST* lista, NoAST* exp) {
    NoAST* temp = lista;
    while (temp->proximo != NULL)
        temp = temp->proximo;

    temp->proximo = exp;
    return lista;
}

NoAST* criarNoAtribuicaoMultipla(NoAST* ids, NoAST* exps) {
    NoAST* no = malloc(sizeof(NoAST));
    no->tipo = NO_ATRIBUICAO_MULTIPLA;
    no->listaIds = ids;
    no->listaExps = exps;
    no->proximo = NULL;
    return no;
}

NoAST *criarNoChamadaFuncao(NoAST *id, NoAST *args) {
    NoAST *novo = alocarNo(NO_CHAMADA_FUNCAO);
    novo->filho1 = id;
    novo->filho2 = args;
    return novo;
}

// --- Funções de Gerenciamento ---

// Função auxiliar para imprimir indentação
static void printIndent(int indent) {
    for (int i = 0; i < indent; i++) {
        printf("  ");
    }
}

void imprimirAST(const NoAST *raiz, int indent) {
    if (!raiz) return;

    // Nós que são parte de uma lista de comandos
    if (raiz->tipo == NO_LISTA_COMANDOS) {
        imprimirAST(raiz->filho1, indent); // Imprime o comando atual
        imprimirAST(raiz->proximo, indent); // Imprime o resto da lista
        return;
    }

    // Para todos os outros nós, imprime a indentação
    printIndent(indent);

    switch (raiz->tipo) {
        case NO_NUM:
            printf("NUM: %d\n", raiz->valor_int);
            break;
        case NO_ID:
            printf("ID: %s\n", raiz->valor_string);
            break;
        case NO_STRING:
            printf("STRING: \"%s\"\n", raiz->valor_string);
            break;
        case NO_BOOL:
            printf("BOOL: %s\n", raiz->valor_int ? "True" : "False");
            break;
        case NO_VAZIO:
            printf("(Comando Vazio)\n");
            break;

        case NO_OP_BINARIA:
            printf("OP: %c\n", raiz->operador);
            imprimirAST(raiz->filho1, indent + 1);
            imprimirAST(raiz->filho2, indent + 1);
            break;
            
        case NO_ATRIBUICAO:
            printf("ATTR:\n");
            imprimirAST(raiz->filho1, indent + 1); // ID
            imprimirAST(raiz->filho2, indent + 1); // Expressão
            break;

        case NO_IF:
            printf("IF:\n");
            printIndent(indent + 1); printf("COND:\n");
            imprimirAST(raiz->filho1, indent + 2); // Condição
            
            printIndent(indent + 1); printf("THEN:\n");
            imprimirAST(raiz->filho2, indent + 2); // Bloco Then
            
            if (raiz->filho3) {
                printIndent(indent + 1); printf("ELSE:\n");
                imprimirAST(raiz->filho3, indent + 2); // Bloco Else
            }
            break;

        case NO_CHAMADA_FUNCAO:
            printf("CALL:\n");
            printIndent(indent + 1);
            printf("FUNC:\n");
            imprimirAST(raiz->filho1, indent + 2);
            if (raiz->filho2) {
                printIndent(indent + 1);
                printf("ARGS:\n");
                NoAST *arg = raiz->filho2;
                while (arg) {
                    imprimirAST(arg, indent + 2);
                    arg = arg->proximo; // percorre a lista de argumentos
                }
            }
            break;

            
        default:
            fprintf(stderr, "Erro: tipo de nó desconhecido para impressão.\n");
    }
}

void liberarAST(NoAST *raiz) {
    if (!raiz) return;
    
    // Libera filhos
    liberarAST(raiz->filho1);
    liberarAST(raiz->filho2);
    liberarAST(raiz->filho3);
    
    // Libera o próximo da lista
    liberarAST(raiz->proximo);
    
    // Libera strings alocadas
    if (raiz->tipo == NO_ID || raiz->tipo == NO_STRING) {
        free(raiz->valor_string);
    }
    
    // Libera o próprio nó
    free(raiz);
}

Tipo inferirTipo(NoAST *no) {
    switch (no->tipo) {
        case NO_NUM: return INT;
        case NO_STRING: return STRING;
        case NO_BOOL: return BOOL;
        case NO_OP_BINARIA:
            // Simplificação: se ambos INT -> INT, etc.
            return INT;
        default: return NONE;
    }
}
