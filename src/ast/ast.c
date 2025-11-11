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

NoAST *criarNoIndex(NoAST *lista, NoAST *indice) {
    NoAST *no = malloc(sizeof(NoAST));
    if (!no) {
        fprintf(stderr, "Erro: falha ao alocar memória para nó de index.\n");
        exit(EXIT_FAILURE);
    }

    no->tipo = NO_INDEX;
    no->filho1 = lista;   // variável ou expressão que representa a lista
    no->filho2 = indice;  // expressão do índice
    no->filho3 = NULL;
    no->proximo = NULL;
    no->listaIds = NULL;
    no->listaExps = NULL;
    no->valor_int = 0;
    no->valor_string = NULL;
    no->operador = '\0';

    return no;
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

void registrarParametros( NoAST *parametros) {
    
    // 'no_atual' começa no primeiro parâmetro (ex: 'c' em soma2)
    NoAST *no_atual = parametros;

    // Percorre a lista ligada até o final (NULL)
    while (no_atual != NULL) {
        
        // Verificamos se o nó é do tipo esperado (NO_ID)
        // (Assumindo que sua AST usa 'NO_ID' e 'valor_string' 
        //  com base nas regras 'atomo' e 'atribuicao')
        if (no_atual->tipo == NO_ID) {
            
            char *nome_param = no_atual->valor_string;

            // 1. Insere o símbolo na Tabela de Símbolos
            //    Usamos INT como tipo padrão, conforme sua sugestão.
            //    Em um sistema de tipos mais complexo, poderia ser 'NONE' ou 'ANY'.
            insertST(nome_param, INT);

            // 2. [RECOMENDADO] Marca o parâmetro como INICIALIZADO.
            //    Parâmetros são "inicializados" pelo próprio ato da
            //    chamada da função, então é seguro definir isso como 'true'.
            Simbolo *s = searchST(nome_param);
            if (s != NULL) {
                s->inicializado = true;
            }
            
        } else {
            // Isso não deveria acontecer se a gramática estiver correta
            fprintf(stderr, "[ERRO INTERNO] Nó de parâmetro não é um NO_ID!\n");
        }

        // Avança para o próximo parâmetro na lista (ex: 'd' em soma2)
        no_atual = no_atual->proximo;
    }
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

NoAST *criarNoOpLogicaAnd(NoAST *esq, NoAST *dir) {
    // Usamos a função auxiliar que você já tem
    NoAST *no = alocarNo(NO_OP_LOGICA_AND);
    no->filho1 = esq;
    no->filho2 = dir;
    return no;
}

NoAST *criarNoOpLogicaOr(NoAST *esq, NoAST *dir) {
    NoAST *no = alocarNo(NO_OP_LOGICA_OR);
    no->filho1 = esq;
    no->filho2 = dir;
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

NoAST *criarNoWhile(NoAST *condicao, NoAST *bloco) {
    NoAST *no = (NoAST *) malloc(sizeof(NoAST));
    no->tipo = NO_WHILE;
    no->filho1 = condicao;
    no->filho2 = bloco;
    no->proximo = NULL;
    return no;
}

NoAST *criarNoFor(NoAST *id, NoAST *iteravel, NoAST *bloco) {
    NoAST *no = malloc(sizeof(NoAST));
    no->tipo = NO_FOR;
    no->filho1 = id;        // variável de iteração
    no->filho2 = iteravel;  // lista ou range
    no->filho3 = bloco;     // corpo do laço
    no->proximo = NULL;

    // Cria a variável do laço na tabela de símbolos
    if (id && id->valor_string) {
        insertST(id->valor_string, inferirTipo(iteravel));
    }

    return no;
}


NoAST *criarNoLista(NoAST *comando, NoAST *proximaLista) {
    NoAST *novo = alocarNo(NO_LISTA_COMANDOS);
    novo->filho1 = comando;
    novo->proximo = proximaLista;
    return novo;
}

NoAST *criarNoFuncao(char *nome, NoAST *params, NoAST *corpo) {
    NoAST *novo = alocarNo(NO_FUNCAO);
    novo->valor_string = strdup(nome); // nome da função
    novo->filho1 = params;             // parâmetros
    novo->filho2 = corpo;              // corpo (bloco)
    return novo;
}

NoAST *criarNoReturn(NoAST *expr) {
    NoAST *novo = alocarNo(NO_RETORNO);
    novo->filho1 = expr;
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

        case NO_OP_LOGICA_AND:
            printf("OP: AND\n"); 
            imprimirAST(raiz->filho1, indent + 1);
            imprimirAST(raiz->filho2, indent + 1);
            break;

        case NO_OP_LOGICA_OR:
            printf("OP: OR\n"); 
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

        case NO_WHILE:
            printf("WHILE:\n");
            printIndent(indent + 1); printf("COND:\n");
            imprimirAST(raiz->filho1, indent + 2);  // Condição

            printIndent(indent + 1); printf("BODY:\n");
            imprimirAST(raiz->filho2, indent + 2);  // Corpo do laço
            break;

        case NO_FOR:
            printf("FOR:\n");
            printIndent(indent + 1);
            printf("VAR:\n");
            imprimirAST(raiz->filho1, indent + 2);
            printIndent(indent + 1);
            printf("IN:\n");
            imprimirAST(raiz->filho2, indent + 2);
            printIndent(indent + 1);
            printf("BLOCO:\n");
            imprimirAST(raiz->filho3, indent + 2);
            break;


        case NO_FUNCAO:
            printf("DEF: %s\n", raiz->valor_string);
            if (raiz->filho1) {
                printIndent(indent + 1); printf("PARAMS:\n");
                NoAST *param = raiz->filho1;
                while (param) {
                    imprimirAST(param, indent + 2);
                    param = param->proximo;
                }
            }
            if (raiz->filho2) {
                printIndent(indent + 1); printf("BODY:\n");
                imprimirAST(raiz->filho2, indent + 2);
            }
            break;
            
        case NO_RETORNO:
            printf("RETURN:\n");
            imprimirAST(raiz->filho1, indent + 1);
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

        case NO_INDEX:
            printf("INDEX:\n");
            printIndent(indent + 1); printf("LISTA/VAR:\n");
            imprimirAST(raiz->filho1, indent + 2);
            printIndent(indent + 1); printf("INDICE:\n");
            imprimirAST(raiz->filho2, indent + 2);
            break;

        case NO_LISTA:
            printf("LISTA LITERAL:\n");
            const NoAST *elem = raiz;
            while (elem) {
                imprimirAST(elem->filho1, indent + 1);
                elem = elem->proximo;
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
    if (!no) return NONE;

    switch(no->tipo) {
        case NO_NUM:
            return INT;
        case NO_BOOL:
            return BOOL;
        case NO_STRING:
            return STRING;
        case NO_ID: {
            Simbolo *s = searchST(no->valor_string);
            if (!s) return NONE;
            return s->tipo;  // <--- pega o tipo da variável
        }
        case NO_LISTA:       // lista literal [1,2,3]
            return INT;       // vetor de inteiros
        case NO_OP_BINARIA:  // tipo do filho1 (esquerda)
            return inferirTipo(no->filho1);
        case NO_ATRIBUICAO:
            return inferirTipo(no->filho2);
        default:
            return NONE;
    }
}

int avaliarExpressao(NoAST *expr) {
    if(!expr) return 0;

    switch(expr->tipo) {
        case NO_NUM: return expr->valor_int;
        case NO_BOOL: return expr->valor_int;
        case NO_ID: {
            Simbolo *s = searchST(expr->valor_string);
            if(s && (s->tipo == INT || s->tipo == BOOL))
                return s->valor.valor_int;
            return 0;
        }
        case NO_OP_BINARIA: {
            int a = avaliarExpressao(expr->filho1);
            int b = avaliarExpressao(expr->filho2);
            switch(expr->operador) {
                case '+': return a + b;
                case '-': return a - b;
                case '*': return a * b;
                case '/': return a / b;
                case '<': return a < b;
                case '>': return a > b;
                case 'l': return a <= b;
                case 'g': return a >= b;
                case '=': return a == b;
                case '!': return a != b;
            }
        }
        
        case NO_OP_LOGICA_AND: {
            int esq = avaliarExpressao(expr->filho1);
            if (esq == 0) return 0; // Se a esquerda é Falsa, o resultado é Falso
            return (avaliarExpressao(expr->filho2) != 0); // Senão, o resultado é o da direita
        }

        case NO_OP_LOGICA_OR: {
            int esq = avaliarExpressao(expr->filho1);
            if (esq != 0) return 1; // Se a esquerda é Verdadeira, o resultado é Verdadeiro
            return (avaliarExpressao(expr->filho2) != 0); // Senão, o resultado é o da direita
        }

        default: return 0;
    }
}

// Executa atribuição simples ou indexada
void executarAtribuicao(NoAST *no) {
    if (!no) return;

    if (no->tipo == NO_ATRIBUICAO) {
        // Se for indexação: vetor[i] = valor
        if (no->filho1->tipo == NO_OP_BINARIA && no->filho1->operador == 'I') { 
            // 'I' usado como nó de indexação
            NoAST *indexNode = no->filho1;
            int valor = avaliarExpressao(no->filho2);
            int indice = avaliarExpressao(indexNode->filho2);
            int* vetor = getListaST(indexNode->filho1->valor_string);
            if (vetor) {
                vetor[indice] = valor;
            } else {
                fprintf(stderr, "Erro: vetor '%s' não existe.\n", indexNode->filho1->valor_string);
            }
        } else {
            int valor = avaliarExpressao(no->filho2);

            Simbolo *s = searchST(no->filho1->valor_string);
            if (!s) {
                insertST(no->filho1->valor_string, inferirTipo(no->filho2));
                s = searchST(no->filho1->valor_string);
            }

            switch (s->tipo) {
                case INT:
                    s->valor.valor_int = valor;
                    break;
                case BOOL:
                    s->valor.valor_bool = valor != 0;
                    break;
                default:
                    fprintf(stderr, "Erro: atribuição não suportada para variável '%s'\n", s->nome);
                    break;
            }
            s->inicializado = true;
        }
    } else if (no->tipo == NO_ATRIBUICAO_MULTIPLA) {
        // Implementação futura para múltiplas atribuições
    }
}

// Executa blocos de comandos ou AST geral
void executarAST(NoAST *raiz) {
    if (!raiz) return;

    NoAST *atual = raiz;

    while (atual) {
        switch (atual->tipo) {
            case NO_LISTA_COMANDOS:
                executarAST(atual->filho1);
                break;

            case NO_ATRIBUICAO:
            case NO_ATRIBUICAO_MULTIPLA:
                executarAtribuicao(atual);
                break;

            case NO_IF: {
                int cond = avaliarExpressao(atual->filho1);
                if (cond) {
                    executarAST(atual->filho2); // bloco then
                } else if (atual->filho3) {
                    executarAST(atual->filho3); // bloco else
                }
                break;
            }
            case NO_FOR: {
                NoAST *iterVar = atual->filho1;    // nó ID (i)
                NoAST *iterable = atual->filho2;   // nó lista literal ou ID (lista)
                NoAST *body = atual->filho3;       // corpo

                if (!iterVar || !iterable) break;

                // Garante que a variável exista na tabela (tipo INT por simplicidade)
                if (!searchST(iterVar->valor_string)) {
                    insertST(iterVar->valor_string, INT);
                }
                Simbolo *var = searchST(iterVar->valor_string);
                if (!var) break;

                // 1) Se for lista literal: NO_LISTA
                if (iterable->tipo == NO_LISTA) {
                    NoAST *elem = iterable;
                    while (elem) {
                        // Alguns implementações guardam o elemento em filho1, outras colocam diretamente.
                        // Tentamos suportar ambos:
                        NoAST *valueNode = elem->filho1 ? elem->filho1 : elem;
                        int valor = avaliarExpressao(valueNode);
                        var->valor.valor_int = valor;
                        var->inicializado = true;

                        // Executa o corpo (body é uma lista de comandos)
                        executarAST(body);

                        elem = elem->proximo;
                    }
                }
                // 2) Se for variável que representa lista/array: NO_ID
                else if (iterable->tipo == NO_ID) {
                    Simbolo *s = searchST(iterable->valor_string);
                    if (!s) {
                        fprintf(stderr, "Erro: lista '%s' não encontrada em tempo de execução.\n", iterable->valor_string);
                        break;
                    }
                    if (!s->vetor) {
                        fprintf(stderr, "Erro: '%s' não é uma lista inicializada.\n", s->nome);
                        break;
                    }
                    // usa s->tamanho quando definido (atribuicao_simples preenche s->tamanho)
                    int tamanho = s->tamanho;
                    for (int i = 0; i < tamanho; i++) {
                        var->valor.valor_int = s->vetor[i];
                        var->inicializado = true;
                        executarAST(body);
                    }
                }
                // 3) Caso expressões que resultem em outras coleções — implementar depois
                else {
                    fprintf(stderr, "Erro: iterável do for não é suportado (linha ?).\n");
                }

                break;
            }

            default:
                // Expressões avulsas
                avaliarExpressao(atual);
        }

        atual = atual->proximo;
    }
}
