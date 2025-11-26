#include "gerador_codigo_final.h"
#include "../ast/ast.h"
#include "../st/st.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




#define MAX_EXPR_BUFFERS 64
#define EXPR_BUFFER_SIZE 2048

static char expr_buffers[MAX_EXPR_BUFFERS][EXPR_BUFFER_SIZE];
static int expr_buffer_idx = 0;


static char* novo_buffer_expr(void) {
    if (expr_buffer_idx >= MAX_EXPR_BUFFERS) {
        expr_buffer_idx = 0; 
    }
    return expr_buffers[expr_buffer_idx++];
}


static void indenta(FILE *saida, int indent);


static const char* operador_para_c(char op) {
    switch (op) {
        case '+': return "+";
        case '-': return "-";
        case '*': return "*";
        case '/': return "/";
        case '<': return "<";
        case '>': return ">";
        case 'l': return "<=";
        case 'g': return ">=";
        case '=': return "==";
        case '!': return "!=";
        case 'N': return "!";
        default: return "?";
    }
}


static void indenta(FILE *saida, int indent) {
    for (int i = 0; i < indent; i++) {
        fprintf(saida, "  ");
    }
}

static const char* gerar_expressao(NoAST *expr, FILE *saida);


static int eh_print(NoAST *expr) {
    if (!expr || expr->tipo != NO_CHAMADA_FUNCAO) return 0;
    NoAST *func_id = expr->filho1;
    if (!func_id || func_id->tipo != NO_ID) return 0;
    return strcmp(func_id->valor_string, "print") == 0;
}


static void gerar_print(NoAST *expr, FILE *saida, int indent) {
    NoAST *args = expr->filho2;
    
    for (int i = 0; i < indent; i++) fprintf(saida, "  ");
    fprintf(saida, "printf(");
    
    int primeira = 1;
    while (args) {
        if (!primeira) fprintf(saida, " ");
        primeira = 0;
        
        if (args->tipo == NO_STRING) {
            
            fprintf(saida, "\"%s\"", args->valor_string);
        } else {
            
            const char* expr_c = gerar_expressao(args, saida);
            
            
            if (args->tipo == NO_ID) {
                Simbolo *s = searchST(args->valor_string);
                if (s && s->tipo == FLOAT) {
                    fprintf(saida, "\"%%f\", %s", expr_c);
                } else if (s && s->tipo == STRING) {
                    fprintf(saida, "\"%%s\", %s", expr_c);
                } else {
                    fprintf(saida, "\"%%d\", %s", expr_c);
                }
            } else if (args->tipo == NO_FLOAT) {
                fprintf(saida, "\"%%f\", %s", expr_c);
            } else if (args->tipo == NO_STRING) {
                fprintf(saida, "\"%%s\", %s", expr_c);
            } else {
                fprintf(saida, "\"%%d\", %s", expr_c);
            }
        }
        
        args = args->proximo;
        if (args && !primeira) fprintf(saida, ", ");
    }
    
    fprintf(saida, ");\n");
}


static const char* gerar_expressao(NoAST *expr, FILE *saida) {
    if (!expr) {
        char* buf = novo_buffer_expr();
        strcpy(buf, "0");
        return buf;
    }

    char* buf = novo_buffer_expr();

    switch (expr->tipo) {
        case NO_NUM:
            snprintf(buf, EXPR_BUFFER_SIZE, "%d", expr->valor_int);
            return buf;

        case NO_FLOAT:
            snprintf(buf, EXPR_BUFFER_SIZE, "%.6f", expr->valor_double);
            return buf;

        case NO_BOOL:
            snprintf(buf, EXPR_BUFFER_SIZE, "%d", expr->valor_int ? 1 : 0);
            return buf;

        case NO_STRING:
            snprintf(buf, EXPR_BUFFER_SIZE, "\"%s\"", expr->valor_string);
            return buf;

        case NO_ID:
            snprintf(buf, EXPR_BUFFER_SIZE, "%s", expr->valor_string);
            return buf;

        case NO_OP_BINARIA: {
            const char* esq = gerar_expressao(expr->filho1, saida);
            const char* dir = gerar_expressao(expr->filho2, saida);
            snprintf(buf, EXPR_BUFFER_SIZE, "(%s %s %s)", 
                     esq, operador_para_c(expr->operador), dir);
            return buf;
        }

        case NO_OP_LOGICA_AND: {
            const char* esq = gerar_expressao(expr->filho1, saida);
            const char* dir = gerar_expressao(expr->filho2, saida);
            snprintf(buf, EXPR_BUFFER_SIZE, "(%s && %s)", esq, dir);
            return buf;
        }

        case NO_OP_LOGICA_OR: {
            const char* esq = gerar_expressao(expr->filho1, saida);
            const char* dir = gerar_expressao(expr->filho2, saida);
            snprintf(buf, EXPR_BUFFER_SIZE, "(%s || %s)", esq, dir);
            return buf;
        }

        case NO_INDEX: {
            const char* array = gerar_expressao(expr->filho1, saida);
            const char* indice = gerar_expressao(expr->filho2, saida);
            snprintf(buf, EXPR_BUFFER_SIZE, "%s[%s]", array, indice);
            return buf;
        }

        case NO_CHAMADA_FUNCAO: {
            NoAST *id = expr->filho1;
            NoAST *args = expr->filho2;
            
            snprintf(buf, EXPR_BUFFER_SIZE, "%s(", id->valor_string);
            
            if (args) {
                NoAST *arg = args;
                int primeiro = 1;
                while (arg) {
                    if (!primeiro) strcat(buf, ", ");
                    const char* arg_str = gerar_expressao(arg, saida);
                    if (strlen(buf) + strlen(arg_str) < EXPR_BUFFER_SIZE - 10) {
                        strcat(buf, arg_str);
                    }
                    primeiro = 0;
                    arg = arg->proximo;
                }
            }
            strcat(buf, ")");
            return buf;
        }

        default:
            strcpy(buf, "0");
            return buf;
    }
}


static void gerar_declaracoes(FILE *saida) {
    fprintf(saida, "    /* Declarações de variáveis globais */\n");
    
    extern Simbolo *tabela[227];
    
    for (int i = 0; i < 227; i++) {
        for (Simbolo *s = tabela[i]; s; s = s->proximo) {
            if (s->escopo == 0 && s->tipo != FUNCAO) { 
                switch (s->tipo) {
                    case INT:
                        fprintf(saida, "    int %s = %d;\n", s->nome, s->valor.valor_int);
                        break;
                    case FLOAT:
                        fprintf(saida, "    float %s = %.6f;\n", s->nome, s->valor.valor_float);
                        break;
                    case STRING:
                        if (s->valor.valor_string) {
                            fprintf(saida, "    char* %s = \"%s\";\n", s->nome, s->valor.valor_string);
                        } else {
                            fprintf(saida, "    char* %s = \"\";\n", s->nome);
                        }
                        break;
                    case BOOL:
                        fprintf(saida, "    int %s = %d;\n", s->nome, s->valor.valor_bool ? 1 : 0);
                        break;
                    case VETOR:
                        
                        fprintf(saida, "    int %s[%d];\n", s->nome, s->tamanho > 0 ? s->tamanho : 1);
                        break;
                    default:
                        break;
                }
            }
        }
    }
    fprintf(saida, "\n");
}


static void gerar_inicializacoes_vetores(FILE *saida, int indent) {
    extern Simbolo *tabela[227];
    
    for (int i = 0; i < 227; i++) {
        for (Simbolo *s = tabela[i]; s; s = s->proximo) {
            if (s->escopo == 0 && s->tipo == VETOR && s->vetor && s->tamanho > 0) {
                for (int j = 0; j < s->tamanho; j++) {
                    indenta(saida, indent);
                    fprintf(saida, "%s[%d] = %d;\n", s->nome, j, s->vetor[j]);
                }
            }
        }
    }
}


static void gerar_comando(NoAST *no, FILE *saida, int indent);

static void gerar_funcoes(NoAST *no, FILE *saida) {
    if (!no) return;
    
    if (no->tipo == NO_FUNCAO) {
        gerar_comando(no, saida, 0);
    } else if (no->tipo == NO_LISTA || no->tipo == NO_LISTA_COMANDOS) {
        if (no->filho1) {
            gerar_funcoes(no->filho1, saida);
        }
        if (no->proximo) {
            gerar_funcoes(no->proximo, saida);
        }
    } else if (no->proximo) {
        gerar_funcoes(no->proximo, saida);
    }
}

static void gerar_bloco(NoAST *bloco, FILE *saida, int indent) {
    if (!bloco) return;

    if (bloco->tipo == NO_LISTA_COMANDOS || bloco->tipo == NO_LISTA) {
        if (bloco->filho1 && bloco->filho1->tipo != NO_FUNCAO) {
            gerar_comando(bloco->filho1, saida, indent);
        }
        if (bloco->proximo) {
            gerar_bloco(bloco->proximo, saida, indent);
        }
    } else if (bloco->tipo != NO_FUNCAO) {
        gerar_comando(bloco, saida, indent);
    }
}

static void gerar_comando(NoAST *no, FILE *saida, int indent) {
    if (!no || no->tipo == NO_VAZIO) return;

    switch (no->tipo) {
        case NO_ATRIBUICAO: {
            if (no->filho2 && no->filho2->tipo == NO_LISTA) {
                break; 
            }
            
            if (no->filho2 && eh_print(no->filho2)) {
                gerar_print(no->filho2, saida, indent);
            } else {
                const char* esq = gerar_expressao(no->filho1, saida);
                const char* dir = gerar_expressao(no->filho2, saida);
                indenta(saida, indent);
                fprintf(saida, "%s = %s;\n", esq, dir);
            }
            break;
        }

        case NO_CHAMADA_FUNCAO: {
            
            if (eh_print(no)) {
                gerar_print(no, saida, indent);
            } else {
                const char* expr = gerar_expressao(no, saida);
                indenta(saida, indent);
                fprintf(saida, "%s;\n", expr);
            }
            break;
        }

        case NO_ATRIBUICAO_MULTIPLA: {
            NoAST *id = no->listaIds;
            NoAST *exp = no->listaExps;
            while (id && exp) {
                const char* id_str = gerar_expressao(id, saida);
                const char* exp_str = gerar_expressao(exp, saida);
                indenta(saida, indent);
                fprintf(saida, "%s = %s;\n", id_str, exp_str);
                id = id->proximo;
                exp = exp->proximo;
            }
            break;
        }

        case NO_IF: {
            const char* cond = gerar_expressao(no->filho1, saida);
            indenta(saida, indent);
            fprintf(saida, "if (%s) {\n", cond);
            gerar_bloco(no->filho2, saida, indent + 1);
            
            if (no->filho3) {
                indenta(saida, indent);
                fprintf(saida, "} else {\n");
                gerar_bloco(no->filho3, saida, indent + 1);
            }
            
            indenta(saida, indent);
            fprintf(saida, "}\n");
            break;
        }

        case NO_WHILE: {
            const char* cond = gerar_expressao(no->filho1, saida);
            indenta(saida, indent);
            fprintf(saida, "while (%s) {\n", cond);
            gerar_bloco(no->filho2, saida, indent + 1);
            indenta(saida, indent);
            fprintf(saida, "}\n");
            break;
        }

        case NO_FOR: {
            NoAST *var = no->filho1;
            NoAST *iter = no->filho2;
            
            if (!var) break;
            
            indenta(saida, indent);
            
            if (iter && iter->tipo == NO_CHAMADA_FUNCAO) {
                NoAST *func_id = iter->filho1;
                if (func_id && func_id->tipo == NO_ID && strcmp(func_id->valor_string, "range") == 0) {
                    NoAST *args = iter->filho2;
                    if (args) {
                        const char *start = "0";
                        const char *end = "0";
                        if (args && args->tipo != NO_VAZIO) {
                            start = gerar_expressao(args, saida);
                            if (args->proximo) {
                                end = gerar_expressao(args->proximo, saida);
                            } else {
                                end = start;
                                start = "0";
                            }
                        }
                        fprintf(saida, "for (int __i = %s; __i < %s; __i++) {\n", start, end);
                        indenta(saida, indent + 1);
                        fprintf(saida, "%s = __i;\n", var->valor_string);
                        gerar_bloco(no->filho3, saida, indent + 1);
                        indenta(saida, indent);
                        fprintf(saida, "}\n");
                    }
                }
            }
            else if (iter && iter->tipo == NO_ID) {
                Simbolo *s = searchST(iter->valor_string);
                if (s && s->tipo == VETOR && s->tamanho > 0) {
                    fprintf(saida, "for (int __i = 0; __i < %d; __i++) {\n", s->tamanho);
                    indenta(saida, indent + 1);
                    fprintf(saida, "%s = %s[__i];\n", var->valor_string, iter->valor_string);
                    gerar_bloco(no->filho3, saida, indent + 1);
                    indenta(saida, indent);
                    fprintf(saida, "}\n");
                }
            }
            else if (iter && (iter->tipo == NO_LISTA || iter->tipo == NO_LISTA_COMANDOS)) {
                int count = 0;
                NoAST *elem = iter;
                while (elem && (elem->tipo == NO_LISTA || elem->tipo == NO_LISTA_COMANDOS)) {
                    if (elem->filho1) count++;
                    elem = elem->proximo;
                }
                
                fprintf(saida, "{\n");
                elem = iter;
                int idx = 0;
                while (elem && (elem->tipo == NO_LISTA || elem->tipo == NO_LISTA_COMANDOS)) {
                    if (elem->filho1) {
                        const char* val_str = gerar_expressao(elem->filho1, saida);
                        indenta(saida, indent + 1);
                        fprintf(saida, "%s = %s;\n", var->valor_string, val_str);
                        gerar_bloco(no->filho3, saida, indent + 1);
                        idx++;
                    }
                    elem = elem->proximo;
                }
                indenta(saida, indent);
                fprintf(saida, "}\n");
            }
            break;
        }

        case NO_RETORNO: {
            indenta(saida, indent);
            if (no->filho1) {
                const char* expr = gerar_expressao(no->filho1, saida);
                fprintf(saida, "return %s;\n", expr);
            } else {
                fprintf(saida, "return;\n");
            }
            break;
        }

        case NO_FUNCAO: {
            fprintf(saida, "\nint %s(", no->valor_string);
            
            if (no->filho1) {
                NoAST *param = no->filho1;
                int primeiro = 1;
                while (param) {
                    if (!primeiro) fprintf(saida, ", ");
                    fprintf(saida, "int %s", param->valor_string);
                    primeiro = 0;
                    param = param->proximo;
                }
            }
            fprintf(saida, ") {\n");
            gerar_bloco(no->filho2, saida, 1);
            fprintf(saida, "}\n");
            break;
        }

        case NO_LISTA_COMANDOS:
        case NO_LISTA:
            gerar_bloco(no, saida, indent);
            break;

        default:
            break;
    }
}


void gerar_codigo_final(TacCodigo* tac, FILE* saida) {
    if (!saida) return;

    extern NoAST *raizAST;
    fprintf(saida, "#include <stdio.h>\n");
    fprintf(saida, "#include <stdlib.h>\n");
    fprintf(saida, "#include <string.h>\n\n");

    gerar_declaracoes(saida);

    if (raizAST) {
        gerar_funcoes(raizAST, saida);
    }

    fprintf(saida, "\nint main() {\n");
    gerar_inicializacoes_vetores(saida, 1);
    gerar_bloco(raizAST, saida, 1);
    fprintf(saida, "    return 0;\n");
    fprintf(saida, "}\n");
}
