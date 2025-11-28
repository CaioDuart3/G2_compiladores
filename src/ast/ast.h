#ifndef AST_H
#define AST_H

#include "../st/st.h"

typedef enum {
    NO_NUM,
    NO_ID,
    NO_INT,
    NO_FLOAT,
    
    NO_FUNCAO,
    NO_STRING,
    NO_BOOL,
    NO_OP_BINARIA,
    NO_OP_LOGICA_AND,
    NO_OP_LOGICA_OR,
    NO_ATRIBUICAO,
    NO_ATRIBUICAO_MULTIPLA,
    NO_IF,
    NO_WHILE,
    NO_FOR,
    NO_LISTA_COMANDOS, // Usado para blocos de código
    NO_VAZIO,
    NO_CHAMADA_FUNCAO,
    NO_RETORNO,
    NO_INDEX,
    NO_LISTA           // Usado para vetores [1,2,3]
} TipoNo;

typedef struct NoAST {
    TipoNo tipo;
    
    // Para nós "folha" (literais)
    int valor_int;          
    char *valor_string;     
    double valor_double;    
    
    // Para tipagem e verificação
    Tipo tipo_dado;
    // Para nós de operação
    char operador;          

    struct NoAST *filho1;
    struct NoAST *filho2;
    struct NoAST *filho3;

    // Ponteiro para encadear comandos em um bloco
    struct NoAST *proximo;

    struct NoAST *listaIds;
    struct NoAST *listaExps;

} NoAST;


NoAST *criarNoIndex(NoAST *lista, NoAST *indice);
NoAST *criarNoNum(int valor);
NoAST *criarNoId(char *nome);
NoAST *criarNoString(char *texto);
NoAST *criarNoBool(int valor);
NoAST *criarNoFloat(double valor);
NoAST *criarNoVazio();

NoAST *criarNoOp(char operador, NoAST *esq, NoAST *dir);
NoAST *criarNoOpLogicaAnd(NoAST *esq, NoAST *dir);
NoAST *criarNoOpLogicaOr(NoAST *esq, NoAST *dir);

NoAST *criarNoAtribuicao(NoAST *id, NoAST *expr);
NoAST *criarNoIf(NoAST *cond, NoAST *blocoThen, NoAST *blocoElse);
NoAST *criarNoWhile(NoAST *condicao, NoAST *bloco);
NoAST *criarNoFor(NoAST *var, NoAST *iterable, NoAST *bloco);

NoAST *criarNoLista(NoAST *comando, NoAST *proximaLista);          // Para vetores
NoAST *criarNoListaComandos(NoAST *comando, NoAST *proximo);       // Para blocos de código


NoAST *criarNoFuncao(char *nome, NoAST *params, NoAST *corpo);
NoAST *criarNoReturn(NoAST *expr);

NoAST* criarListaIds(char* nome);
NoAST* adicionaIdNaLista(NoAST* lista, char* nome);

NoAST* criarListaExp(NoAST* exp);
NoAST* adicionaExpNaLista(NoAST* lista, NoAST* exp);

NoAST* criarNoAtribuicaoMultipla(NoAST* listaIds, NoAST* listaExp);

NoAST *criarNoChamadaFuncao(NoAST *id, NoAST *args);

Tipo inferirTipo(NoAST *no);
void registrarParametros(NoAST *parametros);

void imprimirAST(const NoAST *raiz, int indent);
void liberarAST(NoAST *raiz);

int avaliarExpressao(NoAST *no);
double avaliarExpressaoFloat(NoAST *no);
void executarAST(NoAST *raiz);

#endif