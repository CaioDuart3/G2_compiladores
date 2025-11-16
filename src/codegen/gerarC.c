#include <stdio.h>
#include "ast.h"
#include "st.h"


extern Simbolo* tabela[TAM]; // Torna a tabela visível aqui

// --- Cabeçalho ---
void gerarCabecalhoC(FILE *saida) {
    fprintf(saida, "#include <stdio.h>\n\n");
    fprintf(saida, "int main() {\n");
}

// --- Declaração de variáveis ---
void gerarDeclaracoesVariaveis(FILE *saida) {
    for (int i = 0; i < TAM; i++) {
        Simbolo *s = tabela[i];
        while (s) {
            switch (s->tipo) {
                case INT:
                    fprintf(saida, "int %s = %d;\n", s->nome, s->valor.valor_int);
                    break;
                case FLOAT:
                    fprintf(saida, "float %s = %f;\n", s->nome, s->valor.valor_float);
                    break;
                case BOOL:
                    fprintf(saida, "int %s = %d;\n", s->nome, s->valor.valor_bool);
                    break;
                case STRING:
                    if (s->valor.valor_string)
                        fprintf(saida, "char *%s = \"%s\";\n", s->nome, s->valor.valor_string);
                    else
                        fprintf(saida, "char *%s = NULL;\n", s->nome);
                    break;
                default:
                    break;
            }
            s = s->proximo;
        }
    }
    fprintf(saida, "\n");
}

// --- Função recursiva para gerar código C ---
void gerarC(NoAST *no, FILE *saida, int indent);

static void printIndent(FILE *saida, int indent) {
    for (int i = 0; i < indent; i++) {
        fprintf(saida, "    "); // 4 espaços
    }
}

void gerarC(NoAST *no, FILE *saida, int indent) {
    if (!no) return;

    switch (no->tipo) {
        case NO_NUM:
            fprintf(saida, "%d", no->valor_int);
            break;

        case NO_ID:
            fprintf(saida, "%s", no->valor_string);
            break;

        case NO_BOOL:
            fprintf(saida, "%d", no->valor_int);
            break;

        case NO_OP_BINARIA:
            fprintf(saida, "(");
            gerarC(no->filho1, saida, indent);
            fprintf(saida, " %c ", no->operador);
            gerarC(no->filho2, saida, indent);
            fprintf(saida, ")");
            break;

        case NO_ATRIBUICAO:
            printIndent(saida, indent);
            if (no->filho1 && no->filho1->tipo == NO_ID)
                fprintf(saida, "%s", no->filho1->valor_string);
            else
                gerarC(no->filho1, saida, indent);

            fprintf(saida, " = ");
            gerarC(no->filho2, saida, indent);
            fprintf(saida, ";\n");
            break;

        case NO_LISTA_COMANDOS: {
            NoAST *cmd = no;
            while (cmd) {
                NoAST *c = cmd->filho1;
                /* Gera o conteúdo do comando */
                gerarC(c, saida, indent);

                /*
                 * Se o comando for uma expressão "simples" (ID, NUM, BIN_OP, BOOL, STRING, lista de valores, etc.)
                 * então acrescentamos o terminador de sentença para formar um statement válido em C.
                 *
                 * Para nós que já imprimem seus próprios terminadores (atribuição, chamada, return, if, while, for, ...)
                 * não imprimimos nada extra.
                 */
                if (c) {
                    switch (c->tipo) {
                        case NO_ATRIBUICAO:
                        case NO_CHAMADA_FUNCAO:
                        case NO_RETORNO:
                        case NO_IF:
                        case NO_WHILE:
                        case NO_FOR:
                        case NO_LISTA_COMANDOS:
                            /* esses já imprimem newline/terminador por si só */
                            break;
                        default:
                            /* expressão avulsa — transforma em statement */
                            fprintf(saida, ";\n");
                            break;
                    }
                }

                cmd = cmd->proximo;
            }
            break;
        }

        case NO_IF:
            printIndent(saida, indent);
            fprintf(saida, "if (");
            gerarC(no->filho1, saida, indent);
            fprintf(saida, ") {\n");
            gerarC(no->filho2, saida, indent + 1);
            printIndent(saida, indent);
            fprintf(saida, "}");
            if (no->filho3) {
                fprintf(saida, " else {\n");
                gerarC(no->filho3, saida, indent + 1);
                printIndent(saida, indent);
                fprintf(saida, "}");
            }
            fprintf(saida, "\n");
            break;

        case NO_WHILE:
            printIndent(saida, indent);
            fprintf(saida, "while (");
            gerarC(no->filho1, saida, indent);
            fprintf(saida, ") {\n");
            gerarC(no->filho2, saida, indent + 1);
            printIndent(saida, indent);
            fprintf(saida, "}\n");
            break;

        case NO_FOR:
            printIndent(saida, indent);
            fprintf(saida, "for (%s = 0; %s < ", no->filho1->valor_string, no->filho1->valor_string);
            gerarC(no->filho2, saida, indent);
            fprintf(saida, "; %s++) {\n", no->filho1->valor_string);
            gerarC(no->filho3, saida, indent + 1);
            printIndent(saida, indent);
            fprintf(saida, "}\n");
            break;

        case NO_CHAMADA_FUNCAO:
            printIndent(saida, indent);
            fprintf(saida, "%s(", no->filho1->valor_string);
            if (no->filho2) {
                NoAST *arg = no->filho2;
                while (arg) {
                    gerarC(arg->filho1, saida, indent);
                    if (arg->proximo) fprintf(saida, ", ");
                    arg = arg->proximo;
                }
            }
            fprintf(saida, ");\n");
            break;

        case NO_RETORNO:
            printIndent(saida, indent);
            fprintf(saida, "return ");
            gerarC(no->filho1, saida, indent);
            fprintf(saida, ";\n");
            break;

        default:
            break;
    }

    if (no->proximo) {
        gerarC(no->proximo, saida, indent);
    }
}
