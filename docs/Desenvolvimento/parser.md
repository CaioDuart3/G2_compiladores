# Parser - Análise Sintática

## 1. Introdução

O parser (analisador sintático) é responsável por verificar se a sequência de *tokens* produzida pelo analisador léxico segue as regras definidas pela gramática da linguagem-alvo, que, neste caso, é um subconjunto de Python implementado para o compilador Python -> C.
Além de validar a estrutura sintática, o parser constrói a base para a geração da *Abstract Syntax Tree* (AST), que será usada posteriormente na tradução para código C.

Este compilador suporta:

- Atribuições (simples, múltiplas, encadeadas e indexadas);
- Expressões aritméticas e lógicas;
- Chamadas de funções;
- Listas e indexações;
- Estruturas condicionais (`if`, `elif`, `else`);
- Laços (`while`, `for`);
- Declarações de função e instruções de retorno;
- Blocos estruturados por indentação, assim como em Python.

## 2. Metodologia

O parser foi implementado utilizando Bison, seguindo o padrão clássico de compiladores baseados em gramáticas livres de contexto. A metodologia adotada inclui:

**Integração com o Analisador Léxico**

O parser consome *tokens* produzidos pelo Flex, incluindo informações sobre valores e localização (``%locations``), permitindo melhor rastreamento de erros.

**Implementação das Primeiras Regras**

A implementação inicial do Parser concentrou-se nas regras gramaticais fundamentais, como expressões aritméticas, atribuições e chamadas de função. Essas primeiras definições foram essenciais para que o grupo adquirisse domínio sobre a ferramenta de geração de analisadores e compreendesse, na prática, como estruturar a gramática, integrar ações semânticas e lidar com potenciais conflitos de análise. Esse alicerce tornou possível, posteriormente, a expansão da linguagem com construções mais complexas e dependentes de escopo.

**Tratamento de Blocos com Indentação**

A implementação dos tokens ``INDENT`` e ``DEDENT`` foi fundamental para reproduzir o comportamento de blocos estruturais do Python, onde a delimitação de escopos depende exclusivamente da identação. Essa etapa exigiu atenção especial do grupo, pois o tratamento correto desses *tokens* é pré-requisito para o funcionamento de estruturas como ``if/else``, ``for``, ``while`` e ``def``.

A complexidade surgiu principalmente da necessidade de sincronizar o analisador léxico com o parser, garantindo que cada mudança no nível de indentação fosse refletida com precisão na gramática. Esse mecanismo não apenas define os escopos corretamente, mas também permite a construção consistente dos blocos na AST, evitando ambiguidades e garantindo que o compilador reconheça a hierarquia entre instruções.

**Uso de AST como Representação Intermediária**

O parser opera em integração direta com o módulo de AST, construindo a árvore sintática abstrata à medida que cada regra gramatical é reconhecida. Para cada produção válida, ações semânticas específicas criam e conectam nós definidos em ``ast.h``, garantindo que a estrutura sintática e semântica do programa seja representada fielmente desde os primeiros estágios da análise.

**Tabela de Símbolos**

Durante a análise, o parser utiliza e atualiza a Tabela de Símbolos (``st.h``) para:

- Registrar variáveis e funções;
- Verificar uso antes da definição;
- Inferir tipos;
- Armazenar valores e tamanhos de vetores.

**Ações semânticas integradas**

Além de construir a AST, o parser já resolve:

- Inferência de tipos;
- Avaliação constante de expressões simples;
- Registro de parâmetros de função;
- Verificação de escopo com funções como openScope() e closeScope().

## 3. Papel do Parser no Compilador

O compilador segue o pipeline:

**Código Python -> Lexer (Flex) -> Parser (Bison) -> AST/TAC -> Gerador de Código Final -> Código C**

O parser cumpre as seguintes funções essenciais:

**Detecção de Erros Sintáticos**

Mensagens detalhadas, indicando *token* problemático, linha e tipo de erro.

**Construção da Estrutura Sintática**

Cada construção Python é convertida em um nó semântico representando elementos como:

- Atribuições;
- Condicionais;
- Laços;
- Chamada de funções;
- Operações aritméticas e lógicas.

**Interação com Demais Módulos**

Durante a análise, o parser:

- Atualiza a Tabela de Símbolos;
- Constrói a AST;
- Prepara dados para geração de código intermediário (TAC) e final (C);
- Marca variáveis como inicializadas ou vetores quando necessário.

## 4. Implementação

A implementação do parser está localizada em `parser/parser.y`

Ele é dividido nas seguintes seções:

### 4.1 Cabeçalho em C (`%{ ... %}`)

Inclui:

- Bibliotecas padrão (`stdio.h`, `stdlib.h`, `string.h`);
- Módulos internos do compilador:
- Tabela de Símbolos (`st.h`);
- AST (`ast.h`);
- Código Intermediário (TAC) (`tac.h`);
- Gerador de código final (`gerador_codigo_final.h`);
- Declarações de `yylex()` e `yyerror()`;
- Variável global `raizAST`, que guarda a árvore gerada.

### 4.2 Definições do Bison

Incluindo:

- `%define parse.error verbose`: mensagens de erro detalhadas;
- `%define parse.trace`: rastreamento opcional do parser;
- `%locations`: suporte a linha/coluna;

Definição da union que armazena inteiros, floats, strings e ponteiros para nós AST.

### 4.3 *Tokens*

O parser reconhece:

- Identificadores, inteiros, floats, strings;
- Palavras-chave (`if`, `while`, `for`, `return`, `def`, etc.);
- Operadores aritméticos, lógicos e relacionais;
- Delimitadores e símbolos de estrutura;
- *Tokens* estruturais: `INDENT`, `DEDENT`, `NEWLINE`.

### 4.4 Regras de Precedência

Definidas para evitar ambiguidades, incluindo:

- Atribuições (right associative);
- Operadores lógicos (`and`, `or`, `not`);
- Comparações;
- Operadores aritméticos.

### 4.5 Gramática

Cobre:

- Programa com lista de comandos;
- Blocos indentados;
- `if` / `elif` / `else`;
- Laços `while` e `for`;
- Atribuições (simples, múltipla, encadeada, indexada);
- Chamadas de função;
- Declaração de funções com parâmetros;
- Retorno de função;
- Expressões aritméticas, lógicas e relacionais;
- Literais: inteiros, floats, booleanos, strings, listas;
- Indexações.

Ações semânticas constroem nós AST com funções como:

- `criarNoAtribuicao`
- `criarNoOp`
- `criarNoBool`
- `criarNoChamadaFuncao`
- `criarNoLista`
- `criarNoIndex`

Entre outras

### 4.6 Integração com Tabela de Símbolos

Em regras como atribuição simples:

- A variável é registrada caso ainda não exista;
- Tipo é inferido a partir da expressão;
- Valores são avaliados para constantes;
- Vetores têm tamanho inferido automaticamente.

### 4.7 Tratamento de Erros

`yyerror()` gera mensagens como:

```text
ERRO (linha X): syntax error próximo de '...'
```

Além disso, erros semânticos como uso de variável não declarada também são reportados.

## 5. Execução

Ao executar a análise léxica, há dois resultados possíveis:

## 5.1. Caso a análise sintática seja bem-sucedida

Quando a entrada está de acordo com as regras gramaticais, o parser imprime:

```text
Parsing concluído com sucesso!
```

Essa mensagem indica que:

- todos os *tokens* foram consumidos corretamente;
- não houve violação de nenhuma regra da gramática;
- a estrutura do programa é sintaticamente válida.

Nenhum detalhe adicional é mostrado pelo parser nessa etapa, apenas a confirmação de sucesso.

## 5.2. Caso a análise sintática encontre erro

Quando ocorre qualquer inconsistência gramatical, o parser interrompe a análise e apresenta uma mensagem de erro como:

```text
ERRO SINTÁTICO (linha X): syntax error, unexpected TOKEN_X, expecting Y
Parsing interrompido por erro sintático.
```

Essa apresentação sempre inclui:

- a linha onde o erro foi detectado,
- o *token* inesperado que causou a falha,
- o que era esperado naquele ponto,
- e a mensagem final informando a interrupção da análise.


## Histórico de Versões 

| Versão |Descrição     |Autor                                       |Data    |Revisor|
|:-:     | :-:          | :-:                                        | :-:    |:-:    |
|1.0     | Criação da v1 da documentação do parser | [Ludmila Nunes](https://github.com/ludmilaaysha)   | 01/10/2025 | [Isaque Camargos](https://github.com/isaqzin)|
|2.0     | Criação da versão final da documentação do parser | [Ludmila Nunes](https://github.com/ludmilaaysha)   | 26/11/2025 | [Isaque Camargos](https://github.com/isaqzin)|