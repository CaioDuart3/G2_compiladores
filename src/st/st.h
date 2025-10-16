#ifndef TABELA_H
#define TABELA_H
#define TAM 1000

#include <stdbool.h>

// tipos de dados
typedef enum { INT, FLOAT, STRING, BOOL, NONE, FUNCAO } Tipo;

// Colunas da tabela
typedef struct simbolo {
    char nome[33]; // + \0
    Tipo tipo;
    int escopo;
    struct simbolo *proximo;
} Simbolo;


// Função hash para string
unsigned hash(char *s);

// Inicializa a tabela de símbolos
void initST();

// Insere um novo símbolo na tabela
void insertST(char *nome, Tipo tipo);

// Busca um símbolo na tabela
Simbolo *searchST(char *nome);

// Converte tipo enum para string
const char *tipoParaString(Tipo tipo);

// Imprime o conteúdo da tabela de símbolos
void showST();

// Libera a memória alocada para a tabela de símbolos
void freeST();

// Funções de controle de escopo
void openScope();
void closeScope();
int getScope();

#endif