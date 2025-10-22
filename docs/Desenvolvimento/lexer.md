# Lexer

## 1. Introdução

O **lexer (analisador léxico)** tem como objetivo ler o código-fonte Python caractere por caractere e agrupá-los em sequências significativas chamadas **tokens**. Esses tokens representam as unidades atômicas (palavras-chave, identificadores, operadores, etc.) da linguagem e formam a entrada para a próxima fase: o analisador sintático (Parser).

Este compilador implementa o léxico de um subconjunto de Python, com foco, no momento, em:

- **Tokens Essenciais:** Palavras-chave, identificadores, literais (inteiros, floats, strings).
- **Operadores Comuns:** Aritméticos e de comparação.
- **Delimitadores:** Parênteses, vírgulas, dois-pontos, etc.
- **Tratamento de Indentação:** Gera os tokens especiais **`INDENT`** e **`DEDENT`**, essenciais para a sintaxe Python.

A ferramenta utilizada para a construção do analisador léxico é o **Flex (Fast Lexical Analyzer Generator)**.



## 2. Papel do Lexer no Compilador Python → C

O pipeline geral do compilador é:

***Código Python → Análise Léxica (**Flex**) → Análise Sintática (Bison) → Representação Intermediária / AST → Geração de Código C → Código C resultante***

A função do lexer é, portanto:

- **Converter a sequência de caracteres** do código-fonte em uma **sequência de tokens**.
- **Descartar** elementos irrelevantes, como **espaços em branco** (dentro das linhas) e **comentários** (`#`).
- **Detectar e reportar** caracteres inválidos.
- **Gerenciar o estado de indentação** para produzir tokens de `INDENT` e `DEDENT`.



## 3. Estrutura do Arquivo lexer.l

O arquivo `lexer/lexer.l` é dividido nas seguintes seções:

### 3.1. Seção de Definições em C

Contém código C necessário para o funcionamento do lexer e sua comunicação com o parser:

- **Inclusões:** `stdio.h`, `string.h` e o arquivo gerado pelo Bison (`../parser/parser.tab.h`) para acessar as definições dos tokens.
- **Gerenciamento de Indentação:** Declaração da pilha `indent_stack` e das funções auxiliares (`push_indent()`, `pop_indent()`, `top_indent()`) usadas para simular o comportamento de blocos do Python.
- **Valor do Token:** A variável global `yytoken_value` é usada para armazenar o lexema (o valor literal) de identificadores e literais.

### 3.2. Seção de Definições de Regex e Regras

Esta seção define os padrões (expressões regulares) e as ações correspondentes:

- **Regex Nomeadas:** Definições como `DIGITO`, `LETRA` e `ID` são usadas para simplificar as regras.
- **Prioridade das Regras:** As palavras-chave (`"if"`, `"else"`, etc.) são listadas antes do padrão genérico de identificador (`{ID}`) para garantir que sejam reconhecidas corretamente.
- **Ações:** O código C associado a um padrão retorna o código **`TOKEN_*`** correspondente ao parser.

### 3.3. Tratamento da Indentação

O tratamento de indentação é realizado pela regra `^[ \t]*` e pelo código C nas ações:

1.  O padrão casa com espaços ou tabs **apenas no início da linha**.
2.  O comprimento do recuo (`yyleng`) é comparado com o nível atual (`top_indent()`).
3.  Se a indentação aumentar, **`TOKEN_INDENT`** é retornado.
4.  Se a indentação diminuir, um ou mais **`TOKEN_DEDENT`** são retornados até que o nível correto seja atingido.



## 4. Tokens e Expressões Regulares Implementadas

A tabela a seguir lista os principais padrões de código Python reconhecidos:

| Padrão (Regex/Literal) | Token Gerado | Descrição |
| :--- | :--- | :--- |
| `"if"`, `"while"`, `"def"`, etc. | `TOKEN_PALAVRA_CHAVE_*` | Palavras-chave reservadas. |
| `{ID}` | `TOKEN_IDENTIFICADOR` | Nomes de variáveis e funções. |
| `{DIGITO}+` | `TOKEN_INTEIRO` | Números inteiros. |
| `{DIGITO}+("."{DIGITO}+)?` | `TOKEN_FLOAT` | Números de ponto flutuante. |
| `\"[^\"]*\"` ou `\'[^\']*\'` | `TOKEN_STRING` | Literais de *string*. |
| `==`, `!=`, `<`, `>`, etc. | `TOKEN_OPERADOR_*` | Operadores de comparação. |
| `=`, `+`, `-`, `*`, `/` | `TOKEN_OPERADOR_*` | Operadores de atribuição e aritméticos. |
| `:`, `,`, `(`, `)`, `[`, `]`, `{`, `}` | `TOKEN_DELIMITADOR_*` | Símbolos estruturais. |
| `\n` | `TOKEN_NEWLINE` | Quebra de linha. |
| `^[ \t]*` | `TOKEN_INDENT` ou `TOKEN_DEDENT` | Indentação de bloco. |
| `[ \t]+` | *(Ignorado)* | Espaços e tabs dentro da linha. |
| `"#".*` | *(Ignorado)* | Comentários. |



## Histórico de Versões 

| Versão |Descrição     |Autor                                       |Data    |Revisor|
|:-:     | :-:          | :-:                                        | :-:        |:-:|
|1.0     | Criação da v1 da documentação do lexer | [Rafael Schadt](https://github.com/RafaelSchadt)   | 01/10/2025 | - |

