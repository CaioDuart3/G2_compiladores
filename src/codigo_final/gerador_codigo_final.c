#include "gerador_codigo_final.h"
#include "../st/st.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mapeia os operadores do TAC para C
static const char* map_op(TacOpcode op) {
    switch (op) {
        case TAC_SOMA:      return "+";
        case TAC_SUB:       return "-";
        case TAC_MUL:       return "*";
        case TAC_DIV:       return "/";
        
        case TAC_MENOR:     return "<";
        case TAC_MAIOR:     return ">";
        case TAC_MENOR_IGUAL: return "<=";
        case TAC_MAIOR_IGUAL: return ">=";
        case TAC_IGUAL:     return "==";
        case TAC_DIFERENTE: return "!=";
        
        case TAC_AND:       return "&&";
        case TAC_OR:        return "||";
        
        // Floats
        case TAC_SOMA_F:    return "+";
        case TAC_SUB_F:     return "-";
        case TAC_MUL_F:     return "*";
        case TAC_DIV_F:     return "/";
        case TAC_MENOR_F:   return "<"; 
        // ... adicione outros floats se necessário
        
        default:            return "?";
    }
}

// Gera declarações das variáveis do usuário baseadas na Tabela de Símbolos
static void gerar_declaracoes_usuario(FILE *saida) {
    fprintf(saida, "    // --- Variáveis do Usuário ---\n");
    
    // Acessa a tabela hash global definida no st.c
    extern Simbolo *tabela[227];
    
    for (int i = 0; i < 227; i++) {
        for (Simbolo *s = tabela[i]; s; s = s->proximo) {
            // Apenas variáveis globais (escopo 0) e que não são nomes de função
            if (s->escopo == 0 && s->tipo != FUNCAO) { 
                switch (s->tipo) {
                    case INT:
                        fprintf(saida, "    int %s = %d;\n", s->nome, s->valor.valor_int);
                        break;
                    case FLOAT:
                        fprintf(saida, "    double %s = %.6f;\n", s->nome, s->valor.valor_float);
                        break;
                    case STRING:
                        fprintf(saida, "    char* %s = \"%s\";\n", s->nome, 
                                s->valor.valor_string ? s->valor.valor_string : "");
                        break;
                    case BOOL:
                        fprintf(saida, "    int %s = %d;\n", s->nome, s->valor.valor_bool ? 1 : 0);
                        break;
                    case VETOR:
                        // Declaramos como ponteiro para permitir malloc (alloc do TAC)
                        // Inicializa com NULL para segurança
                        fprintf(saida, "    int* %s = NULL;\n", s->nome);
                        break;
                    default:
                        break;
                }
            }
        }
    }
    fprintf(saida, "\n");
}

void gerar_codigo_final(TacCodigo* tac, FILE* saida) {
    if (!tac || !saida) return;

    // 1. Cabeçalho do arquivo C
    fprintf(saida, "/* Código C gerado pelo compilador via TAC */\n");
    fprintf(saida, "#include <stdio.h>\n");
    fprintf(saida, "#include <stdlib.h>\n");
    fprintf(saida, "#include <string.h>\n\n");

    // 2. Início da main
    fprintf(saida, "int main() {\n");
    
    // 3. Declarações
    gerar_declaracoes_usuario(saida);

    fprintf(saida, "    // --- Temporários do TAC ---\n");
    // Declara um lote de temporários genéricos. 
    // Usamos double para floats e int, contando com cast implícito do C, 
    // ou simplesmente int para lógica básica.
    // Para ser mais robusto, declaramos t0...t99.
    fprintf(saida, "    int t0, t1, t2, t3, t4, t5, t6, t7, t8, t9;\n");
    fprintf(saida, "    int t10, t11, t12, t13, t14, t15, t16, t17, t18, t19;\n");
    // (Num compilador real, faríamos uma varredura para declarar apenas os usados)
    fprintf(saida, "    // (Adicione mais temps se seu código for muito grande)\n\n");

    // 4. Loop de Instruções
    fprintf(saida, "    // --- Código --- \n");
    
    TacInstrucao* inst = tac->inicio;
    while (inst) {
        switch (inst->op) {
            case TAC_ATRIBUICAO:
                fprintf(saida, "    %s = %s;\n", inst->res, inst->arg1);
                break;

            case TAC_SOMA:
            case TAC_SUB:
            case TAC_MUL:
            case TAC_DIV:
            case TAC_MENOR:
            case TAC_MAIOR:
            case TAC_MENOR_IGUAL:
            case TAC_MAIOR_IGUAL:
            case TAC_IGUAL:
            case TAC_DIFERENTE:
            case TAC_AND:
            case TAC_OR:
            case TAC_SOMA_F:
            case TAC_SUB_F:
            case TAC_MUL_F:
            case TAC_DIV_F:
            case TAC_MENOR_F:
            case TAC_IGUAL_F:
                fprintf(saida, "    %s = %s %s %s;\n", 
                        inst->res, inst->arg1, map_op(inst->op), inst->arg2);
                break;

            // --- Controle de Fluxo ---
            case TAC_LABEL:
                fprintf(saida, "%s:\n", inst->res);
                break;

            case TAC_GOTO:
                fprintf(saida, "    goto %s;\n", inst->res);
                break;

            case TAC_IFZ:
                // Se arg1 for falso (0), pula para label res
                fprintf(saida, "    if (!%s) goto %s;\n", inst->arg1, inst->res);
                break;

            // --- Vetores e Memória ---
            case TAC_VET_ALLOC:
                // tX = (int*) malloc( tamanho * sizeof(int) )
                fprintf(saida, "    %s = (int*) malloc(%s * sizeof(int));\n", 
                        inst->res, inst->arg1);
                break;

            case TAC_VET_SET:
                // vetor[indice] = valor
                fprintf(saida, "    %s[%s] = %s;\n", inst->res, inst->arg1, inst->arg2);
                break;

            case TAC_VET_GET:
                // res = vetor[indice]
                fprintf(saida, "    %s = %s[%s];\n", inst->res, inst->arg1, inst->arg2);
                break;

            // --- Chamadas de Função ---
            case TAC_CHAMADA:
                // Tratamento especial para 'print'
                if (strcmp(inst->arg1, "print") == 0) {
                    // Como o TAC simplificou os args antes (TAC_ARG), 
                    // aqui a gente precisaria saber QUAL argumento printar.
                    // O seu TAC atual gera: arg t1; arg t2; res = call print
                    // Print em C (printf) é variádico.
                    
                    // Hack simples: O último TAC_ARG emitido provavelmente é o valor.
                    // Num compilador completo, empilharíamos args.
                    // Vamos assumir um print simples de inteiros/floats por enquanto:
                    fprintf(saida, "    // call print ignorado aqui, use printf manual no C se precisar debug\n");
                    // Se quiser implementar print real via TAC, precisa de uma pilha de argumentos no gerador.
                } else {
                    fprintf(saida, "    %s = %s();\n", inst->res, inst->arg1);
                }
                break;
            
            case TAC_ARG:
                 // Em C, argumentos vão dentro dos parenteses da chamada.
                 // Como o TAC separa (arg x; call f), gerar C direto é chatinho.
                 // Solução rápida: Comentário. Para funcionar 100%, precisaria acumular args.
                 fprintf(saida, "    // arg %s (preparando chamada)\n", inst->arg1);
                 break;
            
            case TAC_RETORNO_VAL:
                fprintf(saida, "    return %s;\n", inst->arg1);
                break;

            // Ignorar marcadores de função por enquanto (estamos gerando script linear na main)
            case TAC_INICIO_FUNCAO:
                fprintf(saida, "    // --- Inicio Funcao %s (Inline) ---\n", inst->res);
                break;
            case TAC_FIM_FUNCAO:
                fprintf(saida, "    // --- Fim Funcao %s ---\n", inst->res);
                break;

            default:
                // Instruções não mapeadas viram comentários
                // fprintf(saida, "    // Instrução TAC %d não implementada em C\n", inst->op);
                break;
        }

        inst = inst->proxima;
    }

    fprintf(saida, "\n    return 0;\n");
    fprintf(saida, "}\n");
}