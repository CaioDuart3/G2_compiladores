%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "../st/st.h"

  #include "../ast/ast.h"


  #define YYERROR_VERBOSE 1

  int yylex(void);
  void yyerror(const char *s);

  extern int yylineno;
  extern void inicializa_pilha();

  /* Variável global que guardará a raiz da nossa árvore */
  NoAST *raizAST = NULL;
%}

%define parse.error verbose
%define parse.trace
%locations


/* * A %union define os "tipos" que os tokens e regras podem carregar.
 */
%union {
    int ival;            /* Para inteiros (TOKEN_INTEIRO) e Bools (0 ou 1) */
    char *sval;          /* Para strings (TOKEN_IDENTIFICADOR, TOKEN_STRING) */
    struct NoAST *no;    /* O tipo mais importante: um ponteiro para um nó da AST */
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
%left TOKEN_OPERADOR_IGUAL TOKEN_OPERADOR_DIFERENTE
%left TOKEN_OPERADOR_MENOR TOKEN_OPERADOR_MENOR_IGUAL
%left TOKEN_OPERADOR_MAIOR TOKEN_OPERADOR_MAIOR_IGUAL
%left TOKEN_OPERADOR_MAIS TOKEN_OPERADOR_MENOS
%left TOKEN_OPERADOR_MULTIPLICACAO TOKEN_OPERADOR_DIVISAO
%right TOKEN_OPERADOR_ATRIBUICAO


/* Para resolver ambiguidade "dangling else" */
%nonassoc TOKEN_PALAVRA_CHAVE_ELSE

%nonassoc LOWER_THAN_ELSE

%%

/* O programa é uma lista opcional de comandos */
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
  | for_stmt             { $$ = $1; }     /* <-- ADICIONADO */
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
    bloco // <-- O 'bloco' é processado aqui, *depois* das ações acima
    {
        // Ação 3: Executa DEPOIS do 'bloco' ser analisado
        closeScope();
        
        // Ação 4: Agora sim, cria o nó da função
        $$ = criarNoFuncao($2, $4, $8); // $8 é o 'bloco'
        insertST($2, FUNCAO); // Insere o nome da função no escopo *anterior*
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
    | atribuicao_indexacao   /* adiciona suporte a ID[expr] = expr */
;

atribuicao_indexacao:
    TOKEN_IDENTIFICADOR TOKEN_DELIMITADOR_ABRE_COLCHETES expressao TOKEN_DELIMITADOR_FECHA_COLCHETES TOKEN_OPERADOR_ATRIBUICAO expressao
    {
        // $1 = char* (nome do vetor)
        // $3 = NoAST* (índice)
        // $6 = NoAST* (valor a atribuir)

        NoAST *no_index = criarNoIndex(criarNoId($1), $3); // cria vetor_int[0]
        $$ = criarNoAtribuicao(no_index, $6);              // cria vetor_int[0] = 0

        free($1); // libera string
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

    // Se for lista, cria vetor
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

    // Avalia expressões
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

    // Todos os nós da cadeia de atribuição
    NoAST *rhs = $3;

    while (rhs->tipo == NO_ATRIBUICAO) {
        rhs = rhs->filho2; // vai para o próximo RHS
    }

    // Inferir tipo do RHS final
    Tipo t = inferirTipo(rhs);

    // Atualizar ST para o LHS
    Simbolo *s = searchST($1);
    if (!s) insertST($1, t);
    else s->tipo = t;

    // Atualizar valor do LHS com nomes corretos do union
switch (t) {
    case INT:
        s->valor.valor_int = $3->valor_int; // $3 é NoAST*, NO_NUM
        break;
    case BOOL:
        s->valor.valor_bool = $3->valor_int; // NO_BOOL armazena booleano em valor_int
        break;
    case STRING:
        if ($3->valor_string)
            s->valor.valor_string = strdup($3->valor_string); // NO_STRING ou NO_ID
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
                insertST($1, NONE); // opcional para continuar parsing
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
            $$ = criarNoLista($2, NULL); /* Lista literal */
        }
  | chamada_index
        { $$ = $1; }
  | chamada_funcao       
        { $$ = $1; }
;

/* --- Lista de valores dentro de [ ... ] --- */
lista_valores:
      /* vazio */          { $$ = NULL; }  /* lista vazia */
  | lista_expressoes       { $$ = $1; }    /* lista de expressões */
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
        $$ = $3;        // Apenas retorna a lista de comandos
    }
;




if_stmt:
    /* IF simples (sem ELSE) */
    TOKEN_PALAVRA_CHAVE_IF expressao TOKEN_DELIMITADOR_DOIS_PONTOS
    {
        openScope(); // Abre o escopo ANTES de analisar o bloco
    }
    bloco
    {
        closeScope(); // Fecha o escopo DEPOIS de analisar o bloco
        $$ = criarNoIf($2, $5, NULL); // $2 = expressao, $5 = bloco
    }
  |
    /* IF com ELSE */
    TOKEN_PALAVRA_CHAVE_IF expressao TOKEN_DELIMITADOR_DOIS_PONTOS
    {
        openScope(); // Abre o escopo do bloco 'if'
    }
    bloco
    {
        closeScope(); // Fecha o escopo do 'if'
    }
    TOKEN_PALAVRA_CHAVE_ELSE TOKEN_DELIMITADOR_DOIS_PONTOS
    {
        openScope(); // Abre o escopo do bloco 'else'
    }
    bloco
    {
        closeScope(); // Fecha o escopo do 'else'
        $$ = criarNoIf($2, $5, $10);
        // $2 = expressao
        // $5 = bloco do 'if'
        // $10 = bloco do 'else'
    }
;

while_stmt:
    TOKEN_PALAVRA_CHAVE_WHILE expressao TOKEN_DELIMITADOR_DOIS_PONTOS
    {
        openScope(); // Abre o escopo ANTES do bloco
    }
    bloco // $5
    {
        closeScope(); // Fecha o escopo DEPOIS do bloco
        $$ = criarNoWhile($2, $5);
    }
;

for_stmt:
    TOKEN_PALAVRA_CHAVE_FOR TOKEN_IDENTIFICADOR TOKEN_PALAVRA_CHAVE_IN expressao TOKEN_DELIMITADOR_DOIS_PONTOS
    {
        openScope(); // Abre o escopo ANTES do bloco
        
        // Adiciona a variável de iteração ($2) ao *novo* escopo
        if (!searchST($2)) {
            insertST($2, INT); // Ou o tipo que você inferir da expressão $4
        }
        // Você pode querer marcar como inicializada aqui também
    }
    bloco // $7
    {
        closeScope(); // Fecha o escopo DEPOIS do bloco
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
            imprimirAST(raizAST, 0); // Imprime a árvore
        } else {
            printf("(AST está vazia)\n");
        }
        printf("---------------------------------------\n");

        printf("\n--- EXECUÇÃO DA AST ---\n");
        if (raizAST) {
            NoAST *cmd = raizAST;
            while (cmd) {
                // Executa comandos de atribuição
                if (cmd->tipo == NO_ATRIBUICAO || cmd->tipo == NO_ATRIBUICAO_MULTIPLA) {
                    executarAtribuicao(cmd);
                }
                // Para expressões isoladas, você pode avaliar e imprimir
                else if (cmd->tipo == NO_OP_BINARIA) {
                    int val = avaliarExpressao(cmd);
                    printf("Resultado da expressão: %d\n", val);
                }
                cmd = cmd->proximo;
            }
        }

        printf("\n--- TABELA DE SÍMBOLOS ---\n");
        showST();   // Mostra as variáveis e valores
        freeST();   // Libera a tabela de símbolos

        if (raizAST) {
            liberarAST(raizAST); // Libera a memória da AST após a execução
        }
    } else {
        printf("Parsing interrompido por erro.\n");
    }

    return result;
}
