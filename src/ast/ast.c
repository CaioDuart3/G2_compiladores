#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Cria um nó numérico
NoAST *criarNoNum(int valor) {
    NoAST *novo = malloc(sizeof(NoAST));
    if (!novo) {
        fprintf(stderr, "Erro: falha ao alocar memória para nó numérico.\n");
        exit(EXIT_FAILURE);
    }

    novo->tipo = NO_NUM;
    novo->valor = valor;
    novo->nome[0] = '\0';
    novo->operador = '\0';
    novo->esquerda = novo->direita = NULL;
    return novo;
}

// Cria um nó identificador (variável)
NoAST *criarNoId(const char *nome) {
    NoAST *novo = malloc(sizeof(NoAST));
    if (!novo) {
        fprintf(stderr, "Erro: falha ao alocar memória para nó identificador.\n");
        exit(EXIT_FAILURE);
    }

    novo->tipo = NO_ID;
    strncpy(novo->nome, nome, sizeof(novo->nome) - 1);
    novo->nome[sizeof(novo->nome) - 1] = '\0';
    novo->operador = '\0';
    novo->esquerda = novo->direita = NULL;
    return novo;
}

// Cria um nó operador (+, -, *, /, etc.)
NoAST *criarNoOp(char operador, NoAST *esq, NoAST *dir) {
    NoAST *novo = malloc(sizeof(NoAST));
    if (!novo) {
        fprintf(stderr, "Erro: falha ao alocar memória para nó operador.\n");
        exit(EXIT_FAILURE);
    }

    novo->tipo = NO_OP;
    novo->operador = operador;
    novo->nome[0] = '\0';
    novo->valor = 0;
    novo->esquerda = esq;
    novo->direita = dir;
    return novo;
}

// Imprime a árvore em notação infixa
void imprimirAST(const NoAST *raiz) {
    if (!raiz) return;

    switch (raiz->tipo) {
        case NO_NUM:
            printf("%d", raiz->valor);
            break;
        case NO_ID:
            printf("%s", raiz->nome);
            break;
        case NO_OP:
            printf("(");
            imprimirAST(raiz->esquerda);
            printf(" %c ", raiz->operador);
            imprimirAST(raiz->direita);
            printf(")");
            break;
        default:
            fprintf(stderr, "Erro: tipo de nó desconhecido.\n");
    }
}

// Libera toda a memória da AST
void liberarAST(NoAST *raiz) {
    if (!raiz) return;
    liberarAST(raiz->esquerda);
    liberarAST(raiz->direita);
    free(raiz);
}

// Avalia a AST (somente números e operadores aritméticos básicos)
int avaliarAST(const NoAST *raiz) {
    if (!raiz) {
        fprintf(stderr, "Erro: AST nula.\n");
        exit(EXIT_FAILURE);
    }

    switch (raiz->tipo) {
        case NO_NUM:
            return raiz->valor;

        case NO_OP: {
            int esq = avaliarAST(raiz->esquerda);
            int dir = avaliarAST(raiz->direita);
            switch (raiz->operador) {
                case '+': return esq + dir;
                case '-': return esq - dir;
                case '*': return esq * dir;
                case '/':
                    if (dir == 0) {
                        fprintf(stderr, "Erro: divisão por zero.\n");
                        exit(EXIT_FAILURE);
                    }
                    return esq / dir;
                default:
                    fprintf(stderr, "Erro: operador desconhecido '%c'.\n", raiz->operador);
                    exit(EXIT_FAILURE);
            }
        }

        case NO_ID:
            fprintf(stderr, "Erro: tentativa de avaliar identificador '%s' sem valor.\n", raiz->nome);
            exit(EXIT_FAILURE);

        default:
            fprintf(stderr, "Erro: tipo de nó inválido.\n");
            exit(EXIT_FAILURE);
    }
}
