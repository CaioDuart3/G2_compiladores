%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

  /* Inclui a definição da nossa Árvore Sintática Abstrata */
  #include "../ast/ast.h" // <-- Ajuste este caminho se necessário

  #define YYERROR_VERBOSE 1

  int yylex(void);
  void yyerror(const char *s);

  extern int yylineno;
  extern void inicializa_pilha();

  /* Variável global que guardará a raiz da nossa árvore */
  NoAST *raizAST = NULL;
%}

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
%token <ival> TOKEN_INTEIRO
%token <sval> TOKEN_IDENTIFICADOR TOKEN_STRING
%token <ival> TOKEN_PALAVRA_CHAVE_TRUE TOKEN_PALAVRA_CHAVE_FALSE

/* --- Tokens que NÃO carregam valores --- */
%token TOKEN_FLOAT /* Não implementado na AST ainda */
%token TOKEN_PALAVRA_CHAVE_IF TOKEN_PALAVRA_CHAVE_ELSE TOKEN_PALAVRA_CHAVE_ELIF
%token TOKEN_PALAVRA_CHAVE_WHILE TOKEN_PALAVRA_CHAVE_FOR TOKEN_PALAVRA_CHAVE_DEF TOKEN_PALAVRA_CHAVE_RETURN TOKEN_PALAVRA_CHAVE_IN
%token TOKEN_OPERADOR_IGUAL TOKEN_OPERADOR_DIFERENTE TOKEN_OPERADOR_MENOR_IGUAL TOKEN_OPERADOR_MAIOR_IGUAL
%token TOKEN_OPERADOR_MENOR TOKEN_OPERADOR_MAIOR
%token TOKEN_OPERADOR_ATRIBUICAO
%token TOKEN_OPERADOR_MAIS TOKEN_OPERADOR_MENOS TOKEN_OPERADOR_MULTIPLICAACAO TOKEN_OPERADOR_DIVISAO
%token TOKEN_DELIMITADOR_DOIS_PONTOS TOKEN_DELIMITADOR_VIRGULA
%token TOKEN_DELIMITADOR_ABRE_PARENTESES TOKEN_DELIMITADOR_FECHA_PARENTESES
%token TOKEN_DELIMITADOR_ABRE_CHAVES TOKEN_DELIMITADOR_FECHA_CHAVES
%token TOKEN_DELIMITADOR_ABRE_COLCHETES TOKEN_DELIMITADOR_FECHA_COLCHETES
%token TOKEN_DESCONHECIDO
%token TOKEN_NEWLINE TOKEN_INDENT TOKEN_DEDENT


/* --- Regras (não-terminais) que produzem um nó da AST --- */
%type <no> programa
%type <no> lista_comandos_opt lista_comandos comando
%type <no> atribuicao expressao atomo bloco if_stmt

/* --- Precedência dos operadores --- */
%left TOKEN_OPERADOR_MAIS TOKEN_OPERADOR_MENOS
%left TOKEN_OPERADOR_MULTIPLICAACAO TOKEN_OPERADOR_DIVISAO
%right TOKEN_OPERADOR_ATRIBUICAO

/* Para resolver ambiguidade "dangling else" */
%nonassoc TOKEN_PALAVRA_CHAVE_ELSE

%%

/* O programa é uma lista opcional de comandos */
programa:
    lista_comandos_opt 
    { 
        raizAST = $1; /* Salva a raiz global */
        $$ = $1;
    }
  ;

lista_comandos_opt:
    /* vazio */         { $$ = NULL; }
  | lista_comandos    { $$ = $1; }
  ;

/* * Um bloco de comandos é uma lista ligada.
 * Esta regra constrói a lista na ordem correta (cmd1 -> cmd2 -> ...).
 */
lista_comandos:
    comando { $$ = $1; }
  | lista_comandos comando 
    {
        if ($2 != NULL) { // Ignora comandos nulos (ex: newlines)
            if ($1 == NULL) {
                $$ = $2; // A lista estava vazia (só tinha nulos), começa com este
            } else {
                // Anexa $2 no final da lista $1
                NoAST *temp = $1;
                while (temp->proximo != NULL) {
                    temp = temp->proximo;
                }
                temp->proximo = $2;
                $$ = $1;
            }
        } else {
            $$ = $1; // Ignora o comando nulo
        }
    }
  ;

comando:
    atribuicao           { $$ = $1; }
  | expressao            { $$ = $1; }
  | if_stmt              { $$ = $1; }
  | bloco                { $$ = $1; }
  | TOKEN_NEWLINE        { $$ = NULL; } /* Newline não gera nó */
  ;

/* Simplifiquei 'atribuicao' para um ID = expressao */
atribuicao:
    TOKEN_IDENTIFICADOR TOKEN_OPERADOR_ATRIBUICAO expressao 
    { 
        $$ = criarNoAtribuicao(criarNoId($1), $3); 
        free($1); /* Libera a string duplicada pelo lexer */
    }
  ;

expressao:
    expressao TOKEN_OPERADOR_MAIS expressao
        { $$ = criarNoOp('+', $1, $3); }
  | expressao TOKEN_OPERADOR_MENOS expressao
        { $$ = criarNoOp('-', $1, $3); }
  | expressao TOKEN_OPERADOR_MULTIPLICAACAO expressao
        { $$ = criarNoOp('*', $1, $3); }
  | expressao TOKEN_OPERADOR_DIVISAO expressao
        { $$ = criarNoOp('/', $1, $3); }
  | atomo
        { $$ = $1; }
  ;

/* 'atomo' são os elementos básicos de uma expressão */
atomo:
    TOKEN_DELIMITADOR_ABRE_PARENTESES expressao TOKEN_DELIMITADOR_FECHA_PARENTESES
        { $$ = $2; } /* Apenas repassa o nó interno */
  | TOKEN_INTEIRO
        { $$ = criarNoNum($1); }
  | TOKEN_IDENTIFICADOR
        { $$ = criarNoId($1); free($1); }
  | TOKEN_STRING
        { $$ = criarNoString($1); free($1); }
  | TOKEN_PALAVRA_CHAVE_TRUE
        { $$ = criarNoBool($1); }
  | TOKEN_PALAVRA_CHAVE_FALSE
        { $$ = criarNoBool($1); }
  ;

/* Um bloco é o que está dentro de um INDENT/DEDENT */
bloco:
    TOKEN_NEWLINE TOKEN_INDENT lista_comandos TOKEN_DEDENT
    { $$ = $3; } /* O nó do bloco é a própria lista de comandos */
  ;

/* Regras para IF e IF/ELSE */
if_stmt:
    TOKEN_PALAVRA_CHAVE_IF expressao TOKEN_DELIMITADOR_DOIS_PONTOS bloco
    {
        $$ = criarNoIf($2, $4, NULL); /* IF sem ELSE */
    }
  | TOKEN_PALAVRA_CHAVE_IF expressao TOKEN_DELIMITADOR_DOIS_PONTOS bloco TOKEN_PALAVRA_CHAVE_ELSE TOKEN_DELIMITADOR_DOIS_PONTOS bloco
    {
        $$ = criarNoIf($2, $4, $7); /* IF com ELSE */
    }
  ;

%%

void yyerror(const char *s) {
  fprintf(stderr, "ERRO SINTÁTICO (linha %d): %s\n", yylineno, s);
}

int main(void) {
  inicializa_pilha();
  yylineno = 1;
  int result = yyparse();
  
  if (result == 0) {
      printf("Parsing concluído com sucesso!\n");
      printf("\n--- ÁRVORE SINTÁTICA ABSTRATA (AST) ---\n");
      if (raizAST) {
          imprimirAST(raizAST, 0); // Imprime a árvore
          liberarAST(raizAST);     // Libera a memória
      } else {
          printf("(AST está vazia)\n");
      }
      printf("---------------------------------------\n");
  } else {
      printf("Parsing interrompido por erro.\n");
  }
  return result;
}