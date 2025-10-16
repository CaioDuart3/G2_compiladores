#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "st.h"

Simbolo *tabela[TAM];
static int escopo_atual = 0;

// Função hash simples (mantém resultado dentro de TAM)
unsigned hash(char *s) {
    unsigned h = 0;
    for (int i = 0; s[i] != '\0'; i++)
        h = (h * 32 + s[i]) % TAM; //evitar segmentation fault
    return h;
}


// Inicializa a tabela de símbolos
void initST() {
    for (int i = 0; i < TAM; i++)
        tabela[i] = NULL;
    escopo_atual = 0;
}

// Insere um novo símbolo na tabela
void insertST(char *nome, Tipo tipo) {
    unsigned i = hash(nome);
    Simbolo *s = malloc(sizeof(Simbolo));

    if (!s) {
        printf("Erro: Falha ao alocar memória para símbolo\n");
        return;
    }

    strncpy(s->nome, nome, sizeof(s->nome) - 1);
    s->nome[sizeof(s->nome) - 1] = '\0'; //garante que no final tenha um \0
    s->tipo = tipo;
    s->escopo = escopo_atual;
    s->proximo = tabela[i];
    tabela[i] = s;
}

// Busca um símbolo na tabela
Simbolo *searchST(char *nome) {
    unsigned i = hash(nome);
    for (Simbolo *s = tabela[i]; s; s = s->proximo) {
        if (strcmp(s->nome, nome) == 0)
            return s;
    }
    return NULL;
}

// Converte enum Tipo para string
const char *tipoParaString(Tipo tipo) {
    switch (tipo) {
        case INT: return "INT";
        case FLOAT: return "FLOAT";
        case STRING: return "STRING";
        case BOOL: return "BOOL";
        case NONE: return "NONE";
        case FUNCAO: return "FUNCAO";
        default: return "DESCONHECIDO";
    }
}

// Imprime o conteúdo da tabela
void showST() {
    printf("\n===== TABELA DE SÍMBOLOS =====\n");
    for (int i = 0; i < TAM; i++) {
        for (Simbolo *s = tabela[i]; s; s = s->proximo) {
            printf("Nome: %-10s | Tipo: %-7s | Escopo: %d\n",
                   s->nome, tipoParaString(s->tipo), s->escopo);
        }
    }
    printf("===============================\n");
}

// Libera toda a memória da tabela
void freeST() {
    for (int i = 0; i < TAM; i++) {
        Simbolo *atual = tabela[i];
        while (atual) {
            Simbolo *proximo = atual->proximo;
            free(atual);
            atual = proximo;
        }
        tabela[i] = NULL;
    }
}

// Controle de escopo
void openScope() {
    escopo_atual++;
#ifdef DEBUG
    printf("[DEBUG] Entrando no escopo %d\n", escopo_atual);
#endif
}

void closeScope() {
    if (escopo_atual > 0) {
        for (int i = 0; i < TAM; i++) {
            Simbolo **atual = &tabela[i];
            while (*atual) {
                if ((*atual)->escopo == escopo_atual) {
                    Simbolo *temp = *atual;
                    *atual = (*atual)->proximo;
                    free(temp);
                } else {
                    atual = &((*atual)->proximo);
                }
            }
        }
#ifdef DEBUG
        printf("[DEBUG] Saindo do escopo %d\n", escopo_atual);
#endif
        escopo_atual--;
    }
}

int getScope() {
    return escopo_atual;
}
