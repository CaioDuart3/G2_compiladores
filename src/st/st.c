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
    unsigned h = hash(nome);
    Simbolo *novo = malloc(sizeof(Simbolo));
    strcpy(novo->nome, nome);
    novo->tipo = tipo;
    novo->escopo = getScope();
    novo->inicializado = false;
    
    // Valores padrão
    switch(tipo) {
        case INT: novo->valor.valor_int = 0; break;
        case FLOAT: novo->valor.valor_float = 0.0; break;
        case BOOL: novo->valor.valor_bool = false; break;
        case STRING: novo->valor.valor_string = NULL; break;
        default: break;
    }

    novo->proximo = tabela[h];
    tabela[h] = novo;
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
            printf("Nome: %-10s | Tipo: %-7s | Escopo: %d | Inicializado: %s | Valor: ",
                   s->nome, tipoParaString(s->tipo), s->escopo,
                   s->inicializado ? "SIM" : "NAO");
            
            if (!s->inicializado) {
                printf("NAO ATRIBUIDO");
            } else {
                switch(s->tipo) {
                    case INT: printf("%d", s->valor.valor_int); break;
                    case FLOAT: printf("%f", s->valor.valor_float); break;
                    case BOOL: printf("%s", s->valor.valor_bool ? "TRUE" : "FALSE"); break;
                    case STRING: printf("\"%s\"", s->valor.valor_string ? s->valor.valor_string : ""); break;
                    default: printf("N/A"); break;
                }
            }
            printf("\n");
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


// Retorna ponteiro para vetor de inteiros da variável
int *getListaST(const char *nome) {
    Simbolo *s = searchST((char*)nome);
    if (!s) {
        fprintf(stderr, "Erro: vetor '%s' não existe na tabela de símbolos.\n", nome);
        return NULL;
    }
    if (!s->vetor) {
        fprintf(stderr, "Erro: vetor '%s' não foi inicializado.\n", nome);
        return NULL;
    }
    return s->vetor;
}


