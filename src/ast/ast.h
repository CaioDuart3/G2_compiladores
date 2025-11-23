#include "../st/st.h"
#ifndef AST_H
#define AST_H
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
    NO_LISTA_COMANDOS,
    NO_VAZIO,
    NO_CHAMADA_FUNCAO,
    NO_RETORNO,
    NO_INDEX,
    NO_LISTA
} TipoNo;

typedef struct NoAST {
    TipoNo tipo;
    
    // Para nós "folha" (literais)
    int valor_int;          // Usado por NO_NUM, NO_BOOL (1=True, 0=False)
    char *valor_string;     // Usado por NO_ID, NO_STRING (requer strdup/free)
    double valor_double;    /* Usado por NO_FLOAT */
    
    // Para tipagem e verificação
    Tipo tipo_dado;
    // Para nós de operação
    char operador;          // Usado por NO_OP_BINARIA (ex: '+', '-', etc.)

    // Filhos genéricos. O significado depende do 'TipoNo':
    // NO_OP_BINARIA: filho1=esquerda, filho2=direita
    // NO_ATRIBUICAO: filho1=id, filho2=expressao
    // NO_IF:         filho1=condicao, filho2=bloco_then, filho3=bloco_else
    // NO_LISTA_COMANDOS: filho1=comando_atual
    struct NoAST *filho1;
    struct NoAST *filho2;
    struct NoAST *filho3;

    // Ponteiro para encadear comandos em um bloco
    struct NoAST *proximo;

    struct NoAST *listaIds;
    struct NoAST *listaExps;

} NoAST;

// --- Funções de Criação de Nós ("Fábricas") ---

// Nós para vetores
NoAST *criarNoIndex(NoAST *lista, NoAST *indice);

// Nós Folha
NoAST *criarNoNum(int valor);
NoAST *criarNoId(char *nome);
NoAST *criarNoString(char *texto);
NoAST *criarNoBool(int valor);
NoAST *criarNoVazio();

// Nós de Expressão
NoAST *criarNoOp(char operador, NoAST *esq, NoAST *dir);
NoAST *criarNoOpLogicaAnd(NoAST *esq, NoAST *dir);
NoAST *criarNoOpLogicaOr(NoAST *esq, NoAST *dir);

// Nós de Comando
NoAST *criarNoAtribuicao(NoAST *id, NoAST *expr);
NoAST *criarNoIf(NoAST *cond, NoAST *blocoThen, NoAST *blocoElse);
NoAST *criarNoLista(NoAST *comando, NoAST *proximaLista);
NoAST *criarNoWhile(NoAST *condicao, NoAST *bloco);

NoAST *criarNoFuncao(char *nome, NoAST *params, NoAST *corpo);
NoAST *criarNoReturn(NoAST *expr);

// Nós de atribuição múltipla
NoAST* criarListaIds(char* nome);
NoAST* adicionaIdNaLista(NoAST* lista, char* nome);

NoAST* criarListaExp(NoAST* exp);
NoAST* adicionaExpNaLista(NoAST* lista, NoAST* exp);

NoAST* criarNoAtribuicaoMultipla(NoAST* listaIds, NoAST* listaExp);

NoAST *criarNoChamadaFuncao(NoAST *id, NoAST *args);
NoAST *criarNoFor(NoAST *var, NoAST *iterable, NoAST *bloco);

Tipo inferirTipo(NoAST *no);

void registrarParametros( NoAST *parametros);

// --- Funções de Gerenciamento ---

// Imprime a árvore (com indentação)
void imprimirAST(const NoAST *raiz, int indent);

// Libera toda a memória da AST
void liberarAST(NoAST *raiz);
int avaliarExpressao(NoAST *no);
double avaliarExpressaoFloat(NoAST *no);
NoAST *criarNoFloat(double valor);
void executarAtribuicao(NoAST *no); 
void executarAST(NoAST *raiz);
double avaliarExpressaoFloat(NoAST *no);

#endif


