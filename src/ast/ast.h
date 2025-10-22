#ifndef AST_H
#define AST_H

#define TAM_NOME 64

typedef enum {
    NO_NUM,
    NO_ID,
    NO_OP
} TipoNo;

typedef struct NoAST {
    TipoNo tipo;
    int valor;
    char nome[TAM_NOME];
    char operador;
    struct NoAST *esquerda;
    struct NoAST *direita;
} NoAST;

// Funções da AST
NoAST *criarNoNum(int valor);
NoAST *criarNoId(const char *nome);
NoAST *criarNoOp(char operador, NoAST *esq, NoAST *dir);
void imprimirAST(const NoAST *raiz);
void liberarAST(NoAST *raiz);
int avaliarAST(const NoAST *raiz);

#endif
