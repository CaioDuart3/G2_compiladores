%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "../st/st.h"
  #include "../tac/tac.h"
  #include "../ast/ast.h"
  #include "../codegen/gerarC.h" 

  #define YYERROR_VERBOSE 1

  int yylex(void);
  void yyerror(const char *s);

  extern int yylineno;
  extern void inicializa_pilha();

  /* Variável global que guardará a raiz da árvore */
  NoAST *raizAST = NULL;

  /* Auxiliares para passar dados do header do 'for' até depois do 'bloco' */
  static char *last_for_var = NULL;
  static NoAST *last_for_expr = NULL;

  static void set_last_for_var(char *s) { last_for_var = s; }
  static char *get_last_for_var(void) { return last_for_var; }
  static void set_last_for_expr(NoAST *n) { last_for_expr = n; }
  static NoAST *get_last_for_expr(void) { return last_for_expr; }
%}

%define parse.error verbose
%define parse.trace
%locations


/* * A %union define os "tipos" que os tokens e regras podem carregar.
 */
%union {
    int ival;            /* Para inteiros (TOKEN_INTEIRO) e Bools (0 ou 1) */
    char *sval;          /* Para strings (TOKEN_IDENTIFICADOR, TOKEN_STRING) */
    struct NoAST *no;    /* um ponteiro para um nó da AST */
}

/* --- Tokens que carregam valores --- */
%token <sval> TOKEN_IDENTIFICADOR TOKEN_STRING
%token <ival> TOKEN_INTEIRO TOKEN_PALAVRA_CHAVE_TRUE TOKEN_PALAVRA_CHAVE_FALSE
%type <no> expressao atribuicao_indexacao



/* --- Tokens que NÃO carregam valores --- */
%token TOKEN_FLOAT /* Não implementado na AST ainda */
%token TOKEN_PALAVRA_CHAVE_IF TOKEN_PALAVRA_CHAVE_ELSE TOKEN_PALAVRA_CHAVE_ELIF
%token TOKEN_PALAVRA_CHAVE_WHILE TOKEN_PALAVRA_CHAVE_FOR TOKEN_PALAVRA_CHAVE_RETURN TOKEN_PALAVRA_CHAVE_IN
%token TOKEN_OPERADOR_IGUAL TOKEN_OPERADOR_DIFERENTE TOKEN_OPERADOR_MENOR_IGUAL TOKEN_OPERADOR_MAIOR_IGUAL
%token TOKEN_OPERADOR_MENOR TOKEN_OPERADOR_MAIOR
%token TOKEN_OPERADOR_ATRIBUICAO
%token TOKEN_OPERADOR_MAIS TOKEN_OPERADOR_MENOS TOKEN_OPERADOR_MULTIPLICACAO TOKEN_OPERADOR_DIVISAO
%token TOKEN_DELIMITADOR_DOIS_PONTOS TOKEN_DELIMITADOR_VIRGULA
%token TOKEN_DELIMITADOR_ABRE_PARENTESES TOKEN_DELIMITADOR_FECHA_PARENTESES
%token TOKEN_DELIMITADOR_ABRE_CHAVES TOKEN_DELIMITADOR_FECHA_CHAVES
%token TOKEN_DELIMITADOR_ABRE_COLCHETES TOKEN_DELIMITADOR_FECHA_COLCHETES
%token TOKEN_DESCONHECIDO
%token TOKEN_NEWLINE TOKEN_INDENT TOKEN_DEDENT
%token TOKEN_PALAVRA_CHAVE_DEF
%token TOKEN_OPERADOR_LOGICO_AND TOKEN_OPERADOR_LOGICO_OR TOKEN_OPERADOR_LOGICO_NOT

/* --- Regras (não-terminais) que produzem um nó da AST --- */
%type <no> programa
%type <no> lista_comandos_opt lista_comandos comando
%type <no> atribuicao if_stmt while_stmt for_stmt 
%type <no> lista_identificadores lista_expressoes atribuicao_simples atribuicao_multipla atribuicao_encadeada
%type <no> chamada_funcao lista_argumentos
%type <no> bloco 
%type <no> atomo lista_valores chamada_index
%type <no> declaracao_funcao retorno

/* Precedência de operadores */
%right TOKEN_OPERADOR_ATRIBUICAO

/* Lógicos (menor precedência) */
%left TOKEN_OPERADOR_LOGICO_OR
%left TOKEN_OPERADOR_LOGICO_AND
%right TOKEN_OPERADOR_LOGICO_NOT

/* Comparações (não são associativas entre si) */
%nonassoc TOKEN_OPERADOR_IGUAL TOKEN_OPERADOR_DIFERENTE
%nonassoc TOKEN_OPERADOR_MENOR TOKEN_OPERADOR_MENOR_IGUAL
%nonassoc TOKEN_OPERADOR_MAIOR TOKEN_OPERADOR_MAIOR_IGUAL

/* Aritméticos */
%left TOKEN_OPERADOR_MAIS TOKEN_OPERADOR_MENOS
%left TOKEN_OPERADOR_MULTIPLICACAO TOKEN_OPERADOR_DIVISAO

/* Para resolver ambiguidade "dangling else" */
%nonassoc TOKEN_PALAVRA_CHAVE_ELSE

%nonassoc LOWER_THAN_ELSE
%%

programa:
    lista_comandos_opt newlines_opt
    { 
        raizAST = $1; /* Salva a raiz global */
        $$ = $1;
    }
  ;

newlines_opt:
    /* vazio */
  | newlines_opt TOKEN_NEWLINE
;

lista_comandos_opt:
    /* vazio */         { $$ = NULL; }
  | lista_comandos    { $$ = $1; }
  ;

/* * Um bloco de comandos é uma lista ligada.
 * Esta regra constrói a lista na ordem correta (cmd1 -> cmd2 -> ...).
 */
lista_comandos:
    comando
        { $$ = criarNoLista($1, NULL); }
  | lista_comandos comando
        {
            if ($2 != NULL)
                $$ = criarNoLista($1, $2);
            else
                $$ = $1;
        }
  ;

comando:
    atribuicao           { $$ = $1; }
  | expressao            { $$ = $1; }
  | if_stmt              { $$ = $1; }
  | while_stmt           { $$ = $1; }
  | for_stmt             { $$ = $1; }
  | TOKEN_NEWLINE        { $$ = NULL; } /* Newline não gera nó */
  | bloco                { $$ = $1; }
  | declaracao_funcao    { $$ = $1; }   
  | retorno              { $$ = $1; } 
  ;


declaracao_funcao:
    TOKEN_PALAVRA_CHAVE_DEF TOKEN_IDENTIFICADOR TOKEN_DELIMITADOR_ABRE_PARENTESES lista_identificadores TOKEN_DELIMITADOR_FECHA_PARENTESES TOKEN_DELIMITADOR_DOIS_PONTOS
    {
        openScope();

        registrarParametros($4); 
    }
    bloco
    {
        closeScope();
        
        $$ = criarNoFuncao($2, $4, $8);
        insertST($2, FUNCAO);
    }
;

retorno:
    TOKEN_PALAVRA_CHAVE_RETURN expressao
    {
        $$ = criarNoReturn($2);
    }
  ;

atribuicao:
      atribuicao_simples
    | atribuicao_multipla
    | atribuicao_encadeada
    | atribuicao_indexacao
;

atribuicao_indexacao:
    TOKEN_IDENTIFICADOR TOKEN_DELIMITADOR_ABRE_COLCHETES expressao TOKEN_DELIMITADOR_FECHA_COLCHETES TOKEN_OPERADOR_ATRIBUICAO expressao
    {

        NoAST *no_index = criarNoIndex(criarNoId($1), $3);
        $$ = criarNoAtribuicao(no_index, $6);

        free($1);
    }
;

atribuicao_simples:
    TOKEN_IDENTIFICADOR TOKEN_OPERADOR_ATRIBUICAO expressao
{
    $$ = criarNoAtribuicao(criarNoId($1), $3);

    Simbolo *s = searchST($1);
    if (!s) {
        insertST($1, inferirTipo($3));
        s = searchST($1);
    }

    s->inicializado = true;

    if ($3->tipo == NO_LISTA) {
        int tamanho = 0;
        NoAST *elem = $3;
        while(elem) { tamanho++; elem = elem->proximo; }
        s->vetor = malloc(sizeof(int) * tamanho);
        s->tamanho = tamanho;
        elem = $3;
        for(int i=0; i<tamanho; i++, elem=elem->proximo)
            s->vetor[i] = elem->valor_int;
    }

    switch(s->tipo) {
        case INT:
        case BOOL:
            s->valor.valor_int = avaliarExpressao($3);
            break;
        case STRING:
            if ($3->valor_string) s->valor.valor_string = strdup($3->valor_string);
            break;
        default:
            break;
    }
    free($1);
}
;

atribuicao_multipla:
      lista_identificadores TOKEN_OPERADOR_ATRIBUICAO lista_expressoes
      {
          $$ = criarNoAtribuicaoMultipla($1, $3);
      }
    ;

atribuicao_encadeada:
    TOKEN_IDENTIFICADOR TOKEN_OPERADOR_ATRIBUICAO atribuicao
{
    $$ = criarNoAtribuicao(criarNoId($1), $3);

    NoAST *rhs = $3;

    while (rhs->tipo == NO_ATRIBUICAO) {
        rhs = rhs->filho2;
    }

    Tipo t = inferirTipo(rhs);

    Simbolo *s = searchST($1);
    if (!s) insertST($1, t);
    else s->tipo = t;

switch (t) {
    case INT:
        s->valor.valor_int = $3->valor_int;
        break;
    case BOOL:
        s->valor.valor_bool = $3->valor_int;
        break;
    case STRING:
        if ($3->valor_string)
            s->valor.valor_string = strdup($3->valor_string);
        break;
    case FLOAT:
        fprintf(stderr, "[WARN] FLOAT não implementado ainda.\n");
        break;
    default:
        break;
}
    free($1);
}
;

lista_identificadores:
      TOKEN_IDENTIFICADOR
      {
          $$ = criarListaIds($1);
      }
    | lista_identificadores TOKEN_DELIMITADOR_VIRGULA TOKEN_IDENTIFICADOR
      {
          $$ = adicionaIdNaLista($1, $3);
      }
    ;

lista_expressoes:
      expressao
      {
          $$ = criarListaExp($1);
      }
    | lista_expressoes TOKEN_DELIMITADOR_VIRGULA expressao
      {
          $$ = adicionaExpNaLista($1, $3);
      }
    ;

/* --- CHAMADAS DE FUNÇÃO --- */
lista_argumentos:
      /* vazio */                        
        { $$ = NULL; }
    | expressao                          
        { $$ = criarListaExp($1); }
    | lista_argumentos TOKEN_DELIMITADOR_VIRGULA expressao
        { $$ = adicionaExpNaLista($1, $3); }
    ;

chamada_funcao:
      TOKEN_IDENTIFICADOR TOKEN_DELIMITADOR_ABRE_PARENTESES lista_argumentos TOKEN_DELIMITADOR_FECHA_PARENTESES
        {
            NoAST *id = criarNoId($1);
            $$ = criarNoChamadaFuncao(id, $3);
            free($1);
        }
    ;

/* Expressões */
expressao:
      expressao TOKEN_OPERADOR_MAIS expressao
        { $$ = criarNoOp('+', $1, $3); }
    | expressao TOKEN_OPERADOR_MENOS expressao
        { $$ = criarNoOp('-', $1, $3); }
    | expressao TOKEN_OPERADOR_MULTIPLICACAO expressao
        { $$ = criarNoOp('*', $1, $3); }
    | expressao TOKEN_OPERADOR_DIVISAO expressao
        { $$ = criarNoOp('/', $1, $3); }
    | expressao TOKEN_OPERADOR_IGUAL expressao
        { $$ = criarNoOp('=', $1, $3); }       /* == */
    | expressao TOKEN_OPERADOR_DIFERENTE expressao
        { $$ = criarNoOp('!', $1, $3); }       /* != */
    | expressao TOKEN_OPERADOR_MENOR expressao
        { $$ = criarNoOp('<', $1, $3); }       /* < */
    | expressao TOKEN_OPERADOR_MENOR_IGUAL expressao
        { $$ = criarNoOp('l', $1, $3); }       /* <= */
    | expressao TOKEN_OPERADOR_MAIOR expressao
        { $$ = criarNoOp('>', $1, $3); }       /* > */
    | expressao TOKEN_OPERADOR_MAIOR_IGUAL expressao
        { $$ = criarNoOp('g', $1, $3); }       /* >= */
    | expressao TOKEN_OPERADOR_LOGICO_AND expressao
        { $$ = criarNoOpLogicaAnd($1, $3); } 
    | expressao TOKEN_OPERADOR_LOGICO_OR expressao
        { $$ = criarNoOpLogicaOr($1, $3); }
    | TOKEN_OPERADOR_LOGICO_NOT expressao
        { $$ = criarNoOp('N', $2, NULL); }
    | atomo
        { $$ = $1; }
;


/* --- Atomos --- */
atomo:
      TOKEN_DELIMITADOR_ABRE_PARENTESES expressao TOKEN_DELIMITADOR_FECHA_PARENTESES
        { $$ = $2; } /* Apenas repassa o nó interno */
  | TOKEN_INTEIRO
        { $$ = criarNoNum($1); }
  | TOKEN_IDENTIFICADOR
        {
            $$ = criarNoId($1);

            Simbolo *s = searchST($1);
            if (!s) {
                fprintf(stderr, "[ERRO] Variável '%s' usada antes de ser declarada (linha %d)\n", $1, yylineno);
                insertST($1, NONE);
            }

            free($1);
        }
  | TOKEN_STRING
        { $$ = criarNoString($1); free($1); }
  | TOKEN_PALAVRA_CHAVE_TRUE
        { $$ = criarNoBool($1); }
  | TOKEN_PALAVRA_CHAVE_FALSE
        { $$ = criarNoBool($1); }
  | TOKEN_DELIMITADOR_ABRE_COLCHETES lista_valores TOKEN_DELIMITADOR_FECHA_COLCHETES
        {
            $$ = criarNoLista($2, NULL);
        }
  | chamada_index
        { $$ = $1; }
  | chamada_funcao       
        { $$ = $1; }
;

/* --- Lista de valores dentro de [ ... ] --- */
lista_valores:
      /* vazio */          { $$ = NULL; }
  | lista_expressoes       { $$ = $1; }
;

/* --- Indexação de listas/arrays --- */
chamada_index:
      atomo TOKEN_DELIMITADOR_ABRE_COLCHETES expressao TOKEN_DELIMITADOR_FECHA_COLCHETES
        {
            $$ = criarNoIndex($1, $3); /* cria nó AST de indexação: $1[$3] */
        }
;

/* 'bloco' agora só lida com indentação, não com escopo */
bloco:
    TOKEN_NEWLINE TOKEN_INDENT lista_comandos TOKEN_DEDENT
    {
        $$ = $3; // Apenas retorna a lista de comandos
    }
;

/* ---------- IF / ELIF / ELSE ---------- */
/* Regra 1: IF simples (sem ELSE) */
if_stmt:
    /* Caso simples: apenas if */
    TOKEN_PALAVRA_CHAVE_IF expressao TOKEN_DELIMITADOR_DOIS_PONTOS bloco
    {
        $$ = criarNoIf($2, $4, NULL);
    }

  | /* Caso com elif */
    TOKEN_PALAVRA_CHAVE_IF expressao TOKEN_DELIMITADOR_DOIS_PONTOS bloco
    TOKEN_PALAVRA_CHAVE_ELIF expressao TOKEN_DELIMITADOR_DOIS_PONTOS bloco
    {
        NoAST *elif_if = criarNoIf($6, $8, NULL);
        $$ = criarNoIf($2, $4, elif_if);
    }

  | /* Caso com elif e else */
    TOKEN_PALAVRA_CHAVE_IF expressao TOKEN_DELIMITADOR_DOIS_PONTOS bloco
    TOKEN_PALAVRA_CHAVE_ELIF expressao TOKEN_DELIMITADOR_DOIS_PONTOS bloco
    TOKEN_PALAVRA_CHAVE_ELSE TOKEN_DELIMITADOR_DOIS_PONTOS bloco
    {
        NoAST *elif_if = criarNoIf($6, $8, $11);
        $$ = criarNoIf($2, $4, elif_if);
    }

  | /* Caso com apenas if e else */
    TOKEN_PALAVRA_CHAVE_IF expressao TOKEN_DELIMITADOR_DOIS_PONTOS bloco
    TOKEN_PALAVRA_CHAVE_ELSE TOKEN_DELIMITADOR_DOIS_PONTOS bloco
    {
        $$ = criarNoIf($2, $4, $7);
    }
;


/* ---------- WHILE ---------- */
while_stmt:
    TOKEN_PALAVRA_CHAVE_WHILE expressao TOKEN_DELIMITADOR_DOIS_PONTOS
    {
        openScope();
    }
    bloco
    {
        closeScope();
        $$ = criarNoWhile($2, $5);
    }
;


/* ---------- FOR ---------- */
/* Observações:
   - Usamos ações intermediárias para duplicar o nome do identificador ($2)
     e salvar a expressão ($4) em variáveis estáticas para serem usadas
     depois do 'bloco'. Assim a variável de iteração já existe no ST
     quando o 'bloco' for parseado.
*/
for_stmt:
    TOKEN_PALAVRA_CHAVE_FOR TOKEN_IDENTIFICADOR TOKEN_PALAVRA_CHAVE_IN expressao TOKEN_DELIMITADOR_DOIS_PONTOS
    {
        openScope();
        
        if (!searchST($2)) {
            insertST($2, INT);
        }
    }
    bloco // $7
    {
        closeScope();
        $$ = criarNoFor(criarNoId($2), $4, $7);
        free($2);
    }
;
%%


void yyerror(const char *s) {
  fprintf(stderr, "ERRO SINTÁTICO (linha %d): %s\n", yylineno, s);
}


int main(void) {
    initST();
    inicializa_pilha();
    yylineno = 1;

    int result = yyparse();

    if (result == 0) {
        printf("Parsing concluído com sucesso!\n");

        printf("\n--- ÁRVORE SINTÁTICA ABSTRATA (AST) ---\n");
        if (raizAST) {
            imprimirAST(raizAST, 0);
        } else {
            printf("(AST está vazia)\n");
        }
        printf("---------------------------------------\n");

        printf("\n--- TABELA DE SÍMBOLOS ---\n");
        showST();   // Mostra as variáveis e valores
        printf("---------------------------------------\n");

        // ===== Geração de código C direto =====
        if (raizAST) {
            FILE *saida = fopen("saida.c", "w");
            if (!saida) {
                perror("Erro ao abrir arquivo de saída");
                return 1;
            }

            gerarCabecalhoC(saida);           // Includes e início de main()
            gerarDeclaracoesVariaveis(saida); // Declara variáveis globais
            gerarC(raizAST, saida);           // Percorre AST e gera comandos
            fprintf(saida, "return 0;\n}\n"); // Fecha main
            fclose(saida);

            printf("\nCódigo C gerado com sucesso em 'saida.c'\n");
        }

        if (raizAST) {
            liberarAST(raizAST);
        }

        freeST(); // libera tabela de símbolos

    } else {
        printf("Parsing interrompido por erro.\n");
    }

    return result;
}