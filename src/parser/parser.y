%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "../st/st.h"
  #include "../tac/tac.h"
  #include "../ast/ast.h"
  #include "../codigo_final/gerador_codigo_final.h"

  #define YYERROR_VERBOSE 1

  int yylex(void);
  void yyerror(const char *s);

  extern int yylineno;
  extern void inicializa_pilha();

  /* Variável global que guardará a raiz da árvore */
  NoAST *raizAST = NULL;
%}

%define parse.error verbose
%define parse.trace
%locations

/* Union */
%union {
    int ival;            
    double dval;         
    char *sval;          
    struct NoAST *no;    
}

/* Tokens */
%token <sval> TOKEN_IDENTIFICADOR TOKEN_STRING
%token <ival> TOKEN_INTEIRO TOKEN_PALAVRA_CHAVE_TRUE TOKEN_PALAVRA_CHAVE_FALSE
%token <dval> TOKEN_FLOAT
%type <no> expressao atribuicao_indexacao

/* Tokens sem valor */
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

/* Tipos */
%type <no> programa
%type <no> lista_comandos_opt lista_comandos comando
%type <no> atribuicao if_stmt while_stmt for_stmt 
%type <no> lista_identificadores lista_expressoes atribuicao_simples atribuicao_multipla atribuicao_encadeada
%type <no> chamada_funcao lista_argumentos
%type <no> bloco 
%type <no> atomo lista_valores chamada_index
%type <no> declaracao_funcao retorno

/* Precedência */
%right TOKEN_OPERADOR_ATRIBUICAO
%left TOKEN_OPERADOR_LOGICO_OR
%left TOKEN_OPERADOR_LOGICO_AND
%right TOKEN_OPERADOR_LOGICO_NOT
%nonassoc TOKEN_OPERADOR_IGUAL TOKEN_OPERADOR_DIFERENTE
%nonassoc TOKEN_OPERADOR_MENOR TOKEN_OPERADOR_MENOR_IGUAL
%nonassoc TOKEN_OPERADOR_MAIOR TOKEN_OPERADOR_MAIOR_IGUAL
%left TOKEN_OPERADOR_MAIS TOKEN_OPERADOR_MENOS
%left TOKEN_OPERADOR_MULTIPLICACAO TOKEN_OPERADOR_DIVISAO
%nonassoc TOKEN_PALAVRA_CHAVE_ELSE
%nonassoc LOWER_THAN_ELSE

%%

programa:
    lista_comandos_opt newlines_opt
    { 
        raizAST = $1; 
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

/* --- REGRA CORRIGIDA --- */
lista_comandos:
    comando
        { $$ = criarNoListaComandos($1, NULL); }
  | lista_comandos comando
        {
            if ($2 != NULL)
                $$ = criarNoListaComandos($1, $2);
            else
                $$ = $1;
        }
  ;
/* ----------------------- */

comando:
    atribuicao           { $$ = $1; }
  | expressao            { $$ = $1; }
  | if_stmt              { $$ = $1; }
  | while_stmt           { $$ = $1; }
  | for_stmt             { $$ = $1; }
  | TOKEN_NEWLINE        { $$ = NULL; }
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
    { $$ = criarNoReturn($2); }
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
        Tipo t = ($3->tipo == NO_LISTA) ? VETOR : inferirTipo($3);
        insertST($1, t);
        s = searchST($1);
    }
    s->inicializado = true;

    if ($3->tipo == NO_LISTA) {
        s->tipo = VETOR;
        int tamanho = 0;
        NoAST *elem = $3->filho1; 
        while(elem) { 
            tamanho++; 
            elem = elem->proximo; 
        }
        if (s->vetor) free(s->vetor);
        s->vetor = malloc(sizeof(int) * tamanho);
        s->tamanho = tamanho;
        elem = $3->filho1;
        for(int i=0; i < tamanho; i++) {
            s->vetor[i] = avaliarExpressao(elem);
            elem = elem->proximo;
        }
    } else {
        switch(s->tipo) {
            case INT:
            case BOOL:
                s->valor.valor_int = avaliarExpressao($3); 
                break;
            case FLOAT:
                s->valor.valor_float = avaliarExpressaoFloat($3); 
                break;
            case STRING:
                if ($3->valor_string) s->valor.valor_string = strdup($3->valor_string);
                break;
            default: break;
        }
    }
    free($1);
}
;

atribuicao_multipla:
      lista_identificadores TOKEN_OPERADOR_ATRIBUICAO lista_expressoes
      { $$ = criarNoAtribuicaoMultipla($1, $3); }
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
        case INT: s->valor.valor_int = $3->valor_int; break;
        case BOOL: s->valor.valor_bool = $3->valor_int; break;
        case STRING: if ($3->valor_string) s->valor.valor_string = strdup($3->valor_string); break;
        default: break;
    }
    free($1);
}
;

lista_identificadores:
      TOKEN_IDENTIFICADOR
      { $$ = criarListaIds($1); }
    | lista_identificadores TOKEN_DELIMITADOR_VIRGULA TOKEN_IDENTIFICADOR
      { $$ = adicionaIdNaLista($1, $3); }
    ;

lista_expressoes:
      expressao
      { $$ = criarListaExp($1); }
    | lista_expressoes TOKEN_DELIMITADOR_VIRGULA expressao
      { $$ = adicionaExpNaLista($1, $3); }
    ;

lista_argumentos:
      /* vazio */ { $$ = NULL; }
    | expressao   { $$ = criarListaExp($1); }
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

expressao:
      expressao TOKEN_OPERADOR_MAIS expressao           { $$ = criarNoOp('+', $1, $3); }
    | expressao TOKEN_OPERADOR_MENOS expressao          { $$ = criarNoOp('-', $1, $3); }
    | expressao TOKEN_OPERADOR_MULTIPLICACAO expressao  { $$ = criarNoOp('*', $1, $3); }
    | expressao TOKEN_OPERADOR_DIVISAO expressao        { $$ = criarNoOp('/', $1, $3); }
    | expressao TOKEN_OPERADOR_IGUAL expressao          { $$ = criarNoOp('=', $1, $3); }
    | expressao TOKEN_OPERADOR_DIFERENTE expressao      { $$ = criarNoOp('!', $1, $3); }
    | expressao TOKEN_OPERADOR_MENOR expressao          { $$ = criarNoOp('<', $1, $3); }
    | expressao TOKEN_OPERADOR_MENOR_IGUAL expressao    { $$ = criarNoOp('l', $1, $3); }
    | expressao TOKEN_OPERADOR_MAIOR expressao          { $$ = criarNoOp('>', $1, $3); }
    | expressao TOKEN_OPERADOR_MAIOR_IGUAL expressao    { $$ = criarNoOp('g', $1, $3); }
    | expressao TOKEN_OPERADOR_LOGICO_AND expressao     { $$ = criarNoOpLogicaAnd($1, $3); } 
    | expressao TOKEN_OPERADOR_LOGICO_OR expressao      { $$ = criarNoOpLogicaOr($1, $3); }
    | TOKEN_OPERADOR_LOGICO_NOT expressao               { $$ = criarNoOp('N', $2, NULL); }
    | atomo                                             { $$ = $1; }
;

atomo:
      TOKEN_DELIMITADOR_ABRE_PARENTESES expressao TOKEN_DELIMITADOR_FECHA_PARENTESES { $$ = $2; }
    | TOKEN_INTEIRO           { $$ = criarNoNum($1); }
    | TOKEN_FLOAT             { $$ = criarNoFloat($1); }
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
    | TOKEN_STRING            { $$ = criarNoString($1); free($1); }
    | TOKEN_PALAVRA_CHAVE_TRUE  { $$ = criarNoBool($1); }
    | TOKEN_PALAVRA_CHAVE_FALSE { $$ = criarNoBool($1); }
    | TOKEN_DELIMITADOR_ABRE_COLCHETES lista_valores TOKEN_DELIMITADOR_FECHA_COLCHETES
        {
            /* Aqui continua sendo lista de vetor, então mantemos criarNoLista */
            $$ = criarNoLista($2, NULL);
        }
    | chamada_index   { $$ = $1; }
    | chamada_funcao  { $$ = $1; }
;

lista_valores:
      /* vazio */        { $$ = NULL; }
    | lista_expressoes   { $$ = $1; }
;

chamada_index:
      atomo TOKEN_DELIMITADOR_ABRE_COLCHETES expressao TOKEN_DELIMITADOR_FECHA_COLCHETES
        { $$ = criarNoIndex($1, $3); }
;

bloco:
    TOKEN_NEWLINE TOKEN_INDENT lista_comandos TOKEN_DEDENT
    { $$ = $3; }
;

if_stmt:
    TOKEN_PALAVRA_CHAVE_IF expressao TOKEN_DELIMITADOR_DOIS_PONTOS bloco
    { $$ = criarNoIf($2, $4, NULL); }
  | TOKEN_PALAVRA_CHAVE_IF expressao TOKEN_DELIMITADOR_DOIS_PONTOS bloco TOKEN_PALAVRA_CHAVE_ELIF expressao TOKEN_DELIMITADOR_DOIS_PONTOS bloco
    {
        NoAST *elif_if = criarNoIf($6, $8, NULL);
        $$ = criarNoIf($2, $4, elif_if);
    }
  | TOKEN_PALAVRA_CHAVE_IF expressao TOKEN_DELIMITADOR_DOIS_PONTOS bloco TOKEN_PALAVRA_CHAVE_ELIF expressao TOKEN_DELIMITADOR_DOIS_PONTOS bloco TOKEN_PALAVRA_CHAVE_ELSE TOKEN_DELIMITADOR_DOIS_PONTOS bloco
    {
        NoAST *elif_if = criarNoIf($6, $8, $11);
        $$ = criarNoIf($2, $4, elif_if);
    }
  | TOKEN_PALAVRA_CHAVE_IF expressao TOKEN_DELIMITADOR_DOIS_PONTOS bloco TOKEN_PALAVRA_CHAVE_ELSE TOKEN_DELIMITADOR_DOIS_PONTOS bloco
    { $$ = criarNoIf($2, $4, $7); }
;

while_stmt:
    TOKEN_PALAVRA_CHAVE_WHILE expressao TOKEN_DELIMITADOR_DOIS_PONTOS
    { openScope(); }
    bloco
    {
        closeScope();
        $$ = criarNoWhile($2, $5);
    }
;

for_stmt:
    TOKEN_PALAVRA_CHAVE_FOR TOKEN_IDENTIFICADOR TOKEN_PALAVRA_CHAVE_IN expressao TOKEN_DELIMITADOR_DOIS_PONTOS
    {
        openScope();
        if (!searchST($2)) insertST($2, INT);
    }
    bloco
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

int main(int argc, char *argv[]) {
    initST();
    inicializa_pilha();
    yylineno = 1;

    int result = yyparse();

    if (result == 0) {
        printf("Parsing concluído com sucesso!\n");

        printf("\n--- ÁRVORE SINTÁTICA ABSTRATA (AST) ---\n");
        if (raizAST) imprimirAST(raizAST, 0);
        else printf("(AST está vazia)\n");
        printf("---------------------------------------\n");

        printf("\n--- EXECUÇÃO DA AST ---\n");
        if (raizAST) executarAST(raizAST);

        printf("\n--- TABELA DE SÍMBOLOS ---\n");
        showST();
        printf("===============================\n");

        if (raizAST) {
            printf("\n--- CÓDIGO INTERMEDIÁRIO (TAC) ---\n");
            TacCodigo* codigo = gerar_tac(raizAST);
            
            if (codigo) {
                imprimir_tac(codigo);

                printf("\n--- GERAÇÃO DE CÓDIGO FINAL ---\n");
                FILE* out = fopen("programa_gerado.c", "w");
                if (out) {
                    gerar_codigo_final(codigo, out);
                    fclose(out);
                    
                } else {
                    fprintf(stderr, "[ERRO] Não foi possível criar 'programa_gerado.c'.\n");
                }
                printf("-----------------------------------\n");
                liberar_tac(codigo);
            } else {
                printf("(Código TAC vazio ou não gerado)\n");
            }
        }

        freeST();
        if (raizAST) liberarAST(raizAST);

    } else {
        printf("Parsing interrompido por erro sintático.\n");
    }

    return result;
}