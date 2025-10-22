# Parser

## 1. Introdução

O parser (analisador sintático) tem como objetivo analisar a sequência de _tokens_ gerada pelo analisador léxico e verificar se ela está em conformidade com a gramática da linguagem Python definida para este projeto.

Este compilador implementa um subconjunto de Python, focando, até o momento, em construções fundamentais como:

- Atribuições
- Expressões aritméticas
- Chamadas de função
- Blocos com indentação

Outras implementções futuras estão descritas no tópico [6. Próximos Passos](#6-próximos-passos) deste documento

Após a análise sintática, o código reconhecido servirá de base para tradução para código C, etapa posterior do compilador.

## 2. Papel do Parser no Compilador Python → C

O _pipeline_ geral do compilador funciona da seguinte forma:

***Código Python → Análise Léxica (Flex) → Análise Sintática (Bison) → Representação Intermediária / AST → Geração de Código C → Código C resultante***


A função do parser é, portanto:

- Detectar erros sintáticos e reportá-los com precisão.
- Construir a estrutura sintática do programa em Python.
- Preparar dados para a etapa de geração de código C.

## 3. Estrutura do Arquivo parser.y

O arquivo ``parser/parser.y`` contém:

- Cabeçalho em C
    - Inclusão de bibliotecas padrão (``stdio.h``, ``stdlib.h``).
    - Definições de ``yylex()`` e ``yyerror()``.
    - Acesso a ``yytext`` e ``yylineno`` para mensagens de erro detalhadas.
- Declarações do Bison
    - _Tokens_ recebidos do lexer (definidos em ``lexer.l``).
    - Regras de precedência de operadores (+, -, *, /, =).
    - Configuração de rastreamento (``%define parse.trace``) e localização de erros (``%locations``).
- Gramática
    - Regras que definem a sintaxe do subconjunto de Python aceito.
    - Estruturas como atribuição múltipla, expressões encadeadas e blocos indentados.
- Funções auxiliares
    - Implementação de ``yyerror()`` para reportar erros sintáticos amigáveis.
    - Função ``main()`` para testar o parser de forma isolada.

## 4. Gramática Implementada

A gramática foi inspirada na sintaxe de Python, adaptada para fins didáticos.
Alguns dos não-terminais principais:

| Não-terminal   | Descrição                                                           |
| -------------- | ------------------------------------------------------------------- |
| programa       | Raiz da gramática; conjunto de comandos                             |
| comando        | Pode ser atribuição, chamada de função, expressão, bloco ou newline |
| atribuicao     | Suporta atribuições simples e encadeadas                            |
| expressao      | Expressões aritméticas com operadores infixos                       |
| bloco          | Início de conjunto indentado de comandos, simulando blocos Python   |
| chamada_funcao | Reconhece chamadas com e sem argumentos                             |

Exemplo de regra de expressão:

```y
expressao:
    chamada_funcao
  | expressao TOKEN_OPERADOR_MAIS expressao
  | expressao TOKEN_OPERADOR_MENOS expressao
  | expressao TOKEN_OPERADOR_MULTIPLICACAO expressao
  | expressao TOKEN_OPERADOR_DIVISAO expressao
  ;
```

## 5. Executando o Parser Individualmente

Durante o desenvolvimento, é possível compilar e executar apenas a etapa do parser para verificar se a análise sintática está correta.

Os comandos são:

**1. Acessar a pasta ``src``**

```bash
cd src
```

**2. Gerar arquivos do parser com Bison**

```bash
bison -d -o "parser/parser.tab.c" "parser/parser.y"
```

**3. Gerar arquivos do lexer com Flex**

```bash
flex -o "lexer/lex.yy.c" "lexer/lexer.l"
```

**4. Compilar parser + lexer**

```bash
gcc parser/parser.tab.c lexer/lex.yy.c -o parser/compilador -lfl
```

**5. Executar testes de parser**

```bash
parser/compilador < tests/sintatico/<test>
```

Onde ``<test>`` representa um arquivo de teste contendo código Python válido ou inválido, localizado em tests/parser.

- Exemplo de teste válido (``tests/sintatico/parser_01_declaracao.py``):
```python
a= 1
a ,b,c=2,3,4
d=e= f=5
```

- Saída esperada:
```bash
Iniciando parser...
Parsing concluído com sucesso!
```

- Exemplo de teste com erro (``tests/sintatico/parser_04_erro1Declaracao.py``):

```python
a=1=b=c 
```

- Saída esperada:
```bash
Iniciando parser...
ERRO (linha 1): syntax error próximo de '='
Parsing interrompido por erro.
```

## 6. Próximos Passos

- Ampliar a gramática para incluir:
    - Condicionais (if, elif, else)
    - Laços (while, for)
    - Definição de funções
    - Declaração e uso de listas
    - Dicionários
- Associar ações semânticas às regras do parser para gerar árvores sintáticas abstratas (AST) ou diretamente código C.
- Implementar mensagens de erro mais específicas para cada regra gramatical.
- Traduzir estruturas Python para C na etapa seguinte do compilador.