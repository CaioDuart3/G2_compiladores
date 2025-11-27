# Lexer - Análise Léxica

## 1. Introdução

O **lexer (analisador léxico)** tem como objetivo ler o código-fonte Python caractere por caractere e agrupá-los em sequências significativas chamadas **tokens**. Esses *tokens* representam as unidades atômicas (palavras-chave, identificadores, operadores, etc.) da linguagem e formam a entrada para a próxima fase: o analisador sintático (Parser).

Este compilador implementa o léxico de um subconjunto de Python, com foco, no momento, em:

- **Tokens Essenciais:** Palavras-chave, identificadores, literais (inteiros, floats, strings).
- **Operadores Comuns:** Aritméticos e de comparação.
- **Delimitadores:** Parênteses, vírgulas, dois-pontos, etc.
- **Tratamento de Indentação:** Gera os tokens especiais **`INDENT`** e **`DEDENT`**, essenciais para a sintaxe Python.

A ferramenta utilizada para a construção do analisador léxico é o **Flex (Fast Lexical Analyzer Generator)**.

## 2. Metodologia

O desenvolvimento do lexer começou logo após termos a estrutura base do parser definida, para garantir que ambos trabalhassem de forma integrada. A implementação foi feita de maneira incremental:

- Primeiro foram criados os *tokens* fundamentais (identificadores, números, operadores simples).
- Em seguida, adicionamos palavras-chave, delimitadores e padrões mais complexos, como floats e strings.
- Depois estruturamos o arquivo `lexer/lexer.l` com regex nomeadas para manter o código mais limpo e organizado.
- O tratamento de indentação foi incorporado cedo, já que a linguagem exige blocos definidos por recuo. Implementamos uma pilha de níveis e regras específicas para gerar `INDENT` e `DEDENT`.
- Por fim, ajustamos as regras para ignorar comentários e espaços irrelevantes e validamos tudo com testes simples para verificar o reconhecimento dos *tokens* e a detecção de erros.

Essa abordagem permitiu que o lexer evoluísse junto do parser, garantindo compatibilidade e facilitando o avanço das próximas etapas do compilador.

## 3. Papel do Lexer no Compilador

O pipeline geral do compilador é:

***Código Python -> Análise Léxica (Flex) -> Análise Sintática (Bison) -> Representação Intermediária / AST -> Geração de Código C -> Código C resultante***

A função do lexer é, portanto:

- **Converter a sequência de caracteres** do código-fonte em uma **sequência de tokens**.
- **Descartar** elementos irrelevantes, como **espaços em branco** (dentro das linhas) e **comentários** (`#`).
- **Detectar e reportar** caracteres inválidos.
- **Gerenciar o estado de indentação** para produzir *tokens* de `INDENT` e `DEDENT`.


## 4. Implementação
### 4.1. Estrutura do Arquivo lexer.l

O arquivo `lexer/lexer.l` é dividido nas seguintes seções:

#### 4.1.1. Seção de Definições em C

Contém código C necessário para o funcionamento do lexer e sua comunicação com o parser:

- **Inclusões:** `stdio.h`, `string.h` e o arquivo gerado pelo Bison (`../parser/parser.tab.h`) para acessar as definições dos *tokens*.
- **Gerenciamento de Indentação:** Declaração da pilha `indent_stack` e das funções auxiliares (`push_indent()`, `pop_indent()`, `top_indent()`) usadas para simular o comportamento de blocos do Python.
- **Valor do *Token*:** A variável global `yytoken_value` é usada para armazenar o lexema (o valor literal) de identificadores e literais.

#### 4.1.2 Seção de Definições de Regex e Regras

Esta seção define os padrões (expressões regulares) e as ações correspondentes:

- **Regex Nomeadas:** Definições como `DIGITO`, `LETRA` e `ID` são usadas para simplificar as regras.
- **Prioridade das Regras:** As palavras-chave (`"if"`, `"else"`, etc.) são listadas antes do padrão genérico de identificador (`{ID}`) para garantir que sejam reconhecidas corretamente.
- **Ações:** O código C associado a um padrão retorna o código **`TOKEN_*`** correspondente ao parser.

#### 4.1.3. Tratamento da Indentação

O tratamento de indentação é realizado pela regra `^[ \t]*` e pelo código C nas ações:

1.  O padrão casa com espaços ou tabs **apenas no início da linha**.
2.  O comprimento do recuo (`yyleng`) é comparado com o nível atual (`top_indent()`).
3.  Se a indentação aumentar, **`TOKEN_INDENT`** é retornado.
4.  Se a indentação diminuir, um ou mais **`TOKEN_DEDENT`** são retornados até que o nível correto seja atingido.



### 4.2. *Tokens* e Expressões Regulares Implementadas

A tabela a seguir lista os principais padrões de código Python reconhecidos:

| Padrão (Regex/Literal)                                                                           | Token Gerado                     | Descrição                                                     |                |                                   |
| ------------------------------------------------------------------------------------------------ | -------------------------------- | ------------------------------------------------------------- | -------------- | --------------------------------- |
| `"if"`, `"else"`, `"while"`, `"for"`, `"def"`, `"return"`, `"in"`, `"True"`, `"False"` | `TOKEN_PALAVRA_CHAVE_*`          | Palavras-chave reservadas.                                    |                |                                   |
| `{ID}`                                                                                           | `TOKEN_IDENTIFICADOR`            | Identificadores: nomes de variáveis e funções.                |                |                                   |
| `{DIGITO}+`                                                                                      | `TOKEN_INTEIRO`                  | Números inteiros.                                             |                |                                   |
| `{DIGITO}+\.({DIGITO}+)?([eE][+-]?{DIGITO}+)?`                                                   | `TOKEN_FLOAT`                    | Números de ponto flutuante, com suporte a notação científica. |                |                                   |
| `\"[^\"]*\"`, `\'[^\']*\'`                                                                       | `TOKEN_STRING`                   | Strings literais comuns.                                      |                |                                   |
| `[fF]"([^"\]                                                                                     | \.)*"`, `[fF]'([^'\]             | \.)*'`                                                        | `TOKEN_STRING` | *F-strings* (strings formatadas). |
| `==`, `!=`, `<`, `>`, `<=`, `>=`                                                                 | `TOKEN_OPERADOR_*`               | Operadores de comparação.                                     |                |                                   |
| `=`, `+`, `-`, `*`, `/`                                                                          | `TOKEN_OPERADOR_*`               | Operadores aritméticos e de atribuição.                       |                |                                   |
| `"and"`, `"or"`, `"not"`                                                                         | `TOKEN_OPERADOR_LOGICO_*`        | Operadores lógicos.                                           |                |                                   |
| `:`, `,`, `(`, `)`, `[`, `]`, `{`, `}`                                                           | `TOKEN_DELIMITADOR_*`            | Símbolos estruturais.                                         |                |                                   |
| `\n`                                                                                             | `TOKEN_NEWLINE`                  | Quebra de linha.                                              |                |                                   |
| Indentação no início da linha (conta espaços/tabs)                                               | `TOKEN_INDENT` ou `TOKEN_DEDENT` | Controle de blocos por indentação.                            |                |                                   |
| `[ \t]+`                                                                                         | *(Ignorado)*                     | Espaços e tabs dentro da linha.                               |                |                                   |
| `#.*`                                                                                            | *(Ignorado)*                     | Comentários de linha.                                         |                |                                   |
| `.`                                                                                              | `TOKEN_DESCONHECIDO`             | Símbolos inválidos.                                           |                |                                   |

## 5. Execução

Ao executar uma análise léxica , há dois resultados possíveis, dependendo se todos os caracteres da entrada formam *tokens* válidos segundo as regras definidas no arquivo lexer.l.

## 5.1. Caso a análise léxica seja bem-sucedida

Quando toda a entrada é formada apenas por *tokens* válidos , o analisador léxico processa corretamente cada lexema e imprime uma lista de *tokens* reconhecidos, um por linha, ou o formato definido no seu lexer_main.c.

Exemplo de impressao em caso de  a análise léxica seja bem-sucedida:

```text
TOKEN_ID (variavel)
TOKEN_NUM (123)
TOKEN_OP_SOMA (+)
```

Esse resultado indica que:

- Todos os caracteres foram lidos e convertidos corretamente em *tokens*;

- Nenhum lexema inválido foi encontrado;

- O fluxo da entrada está lexicalmente correto.

Nenhuma mensagem de erro é exibida nesse caso, apenas a listagem dos *tokens*.

## 5.2. Caso a análise léxica encontre erro

Se a entrada contiver um caractere ou sequência que não corresponda a nenhum *token* definido , o analisador léxico interrompeu o processamento e apresenta uma mensagem de erro

```text
ERRO LÉXICO (linha X): símbolo inválido encontrado: @
```

Após o erro, a análise é encerrada imediatamente e a saída do programa contém somente as mensagens até o ponto da falha.

## Histórico de Versões 

| Versão |Descrição     |Autor                                       |Data    |Revisor|
|:-:     | :-:          | :-:                                        | :-:        |:-:|
|1.0     | Criação da v1 da documentação do lexer | [Rafael Schadt](https://github.com/RafaelSchadt)   | 01/10/2025 | - |
|2.0     | Atualização do documento | [Laryssa Felix](https://github.com/felixlaryssa) | 01/10/2025 | [Caio Duarte](https://github.com/caioduart3) |
