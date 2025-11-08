#ifndef AST_H
#define AST_H

// Enumeração expandida para todos os tipos de nós
typedef enum {
    NO_NUM,                 // Nó para um número literal (ex: 123)
    NO_ID,                  // Nó para um identificador (ex: 'x')
    NO_STRING,              // Nó para um literal string (ex: "ola")
    NO_BOOL,                // Nó para um booleano (True, False)
    NO_OP_BINARIA,          // Nó para uma operação binária (ex: +, -, *, /)
    NO_ATRIBUICAO,          // Nó para uma atribuição (ex: x = 5)
    NO_ATRIBUICAO_MULTIPLA, // Nó para atribuição múltipla (ex: a, b = 1, 2)
    NO_IF,                  // Nó para um comando 'if' (com 'else' opcional)
    NO_LISTA_COMANDOS,      // Nó que representa um comando em uma lista (um 'bloco')
    NO_VAZIO,                // Nó especial para comandos que não fazem nada (ex: uma linha em branco)
    NO_CHAMADA_FUNCAO       // Nó para chamada de função (ex: foo())
} TipoNo;

typedef struct NoAST {
    TipoNo tipo;
    
    // Para nós "folha" (literais)
    int valor_int;          // Usado por NO_NUM, NO_BOOL (1=True, 0=False)
    char *valor_string;     // Usado por NO_ID, NO_STRING (requer strdup/free)

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

// Nós Folha
NoAST *criarNoNum(int valor);
NoAST *criarNoId(char *nome);
NoAST *criarNoString(char *texto);
NoAST *criarNoBool(int valor);
NoAST *criarNoVazio();

// Nós de Expressão
NoAST *criarNoOp(char operador, NoAST *esq, NoAST *dir);

// Nós de Comando
NoAST *criarNoAtribuicao(NoAST *id, NoAST *expr);
NoAST *criarNoIf(NoAST *cond, NoAST *blocoThen, NoAST *blocoElse);
NoAST *criarNoLista(NoAST *comando, NoAST *proximaLista);

// Nós de atribuição múltipla
NoAST* criarListaIds(char* nome);
NoAST* adicionaIdNaLista(NoAST* lista, char* nome);

NoAST* criarListaExp(NoAST* exp);
NoAST* adicionaExpNaLista(NoAST* lista, NoAST* exp);

NoAST* criarNoAtribuicaoMultipla(NoAST* listaIds, NoAST* listaExp);

NoAST *criarNoChamadaFuncao(NoAST *id, NoAST *args);



// --- Funções de Gerenciamento ---

// Imprime a árvore (com indentação)
void imprimirAST(const NoAST *raiz, int indent);

// Libera toda a memória da AST
void liberarAST(NoAST *raiz);

#endif