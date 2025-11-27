# TAC - Three Adress Code (Código de Três Endereços)

## 1. Introdução

O **Código de Três Endereços (TAC - Three-Address Code)** é uma forma de **código intermediário** fundamental no processo de compilação.

O **TAC** tem como objetivo traduzir as construções de alto nível da linguagem de programação, conforme reconhecidas e validadas pelo analisador sintático (**parser**), em uma sequência de instruções mais simples e primitivas.

Cada instrução do TAC, como o nome sugere, tipicamente envolve no máximo **três endereços** (referências a variáveis, constantes ou valores temporários), tornando-o uma representação linear, explícita e fácil de manipular, servindo como uma ponte essencial entre a análise sintática e a geração final do código de máquina.

---

## 2. Metodologia

A geração do Código de Três Endereços (**TAC**) é implementada como uma fase de tradução que se segue diretamente à Análise Semântica, utilizando a **Árvore de Sintaxe Abstrata (AST)** como representação de entrada. 

O gerador de TAC percorre a AST de forma recursiva, emitindo uma sequência linear de instruções que desconstroem as **expressões complexas** e as **estruturas de controle** em formas elementares de no máximo três operandos.

O coração da metodologia reside na função estática recursiva `static char* processar_no(NoAST* no)`.

* **Expressões:** Para nós que representam **expressões** (`NO_OP_BINARIA`, `NO_ID`, `NO_NUM`), a função retorna uma *string alocada* (nome) que contém o **endereço** do resultado da expressão (ex: o nome de uma variável temporária como `"t1"`, o nome de uma variável como `"x"`, ou uma constante como `"5"`).
* **Comandos:** Para nós que representam **comandos** ou estruturas de controle (`NO_ATRIBUICAO`, `NO_IF`, `NO_WHILE`), a função retorna `NULL`, pois seu objetivo é apenas emitir as instruções TAC correspondentes.


Para garantir que o código TAC mantenha sua forma explícita de três endereços, são utilizadas funções auxiliares que geram identificadores únicos:

| Função | Finalidade | Exemplo |
| :--- | :--- | :--- |
| `static char* novo_temp()` | Cria **variáveis temporárias** para armazenar resultados de sub-expressões. | `t0`, `t1`, `t2` |
| `static char* novo_label()` | Cria **rótulos** para controle de fluxo. | `L0`, `L1`, `L_INICIO` |

---

## 3. Papel do TAC no Compilador
O Código de Três Endereços (TAC) estabelece-se como uma fase de código intermediário no pipeline do compilador, servindo como uma abstração essencial que isola as etapas de 
análise da linguagem das etapas de otimização e geração do código final.

---

## 4. Implementação

### 4.1. Código

A implementação do gerador de Código de Três Endereços (TAC) está contida no arquivo **`tac.c`** e é baseada em uma abordagem de **tradução orientada por sintaxe**, onde cada nó da Árvore de Sintaxe Abstrata (AST) é mapeado para uma ou mais instruções de código intermediário.

#### Estruturas Principais (`tac.h`)

As definições essenciais para o TAC estão no cabeçalho `tac.h`:

1.  **`TacOpcode` (Enumeração):** Define o conjunto de operações atômicas suportadas pelo código intermediário (ex: `TAC_SOMA`, `TAC_GOTO`, `TAC_CHAMADA`, `TAC_VET_SET`).
2.  **`TacInstrucao` (Struct):** Representa uma instrução individual, contendo o `op` (opcode) e as três strings de endereço (`res`, `arg1`, `arg2`). A lista é construída por meio do ponteiro `proxima`.
3.  **`TacCodigo` (Struct):** Serve como o contêiner principal para o código gerado, mantendo ponteiros para o `inicio` e o `fim` da lista de instruções, facilitando a adição (append) no tempo constante O(1).

#### Funções de Gerenciamento

O arquivo `tac.c` utiliza variáveis estáticas para manter o estado da geração de código e funções auxiliares para manipular endereços:

* **`static int contador_temp` e `static int contador_label`:** Contadores utilizados pelas funções `novo_temp()` e `novo_label()` para garantir a unicidade dos identificadores gerados (ex: `t0`, `t1`, `L0`, `L1`).
* **`static void emitir(TacOpcode op, char* res, char* arg1, char* arg2)`:** Função crucial que **aloca** uma nova estrutura `TacInstrucao`, **copia** as *strings* de endereço fornecidas, e adiciona a nova instrução ao final da lista global.

#### O Mecanismo de Tradução

A tradução é realizada por meio de uma única função recursiva, que processa a AST em ordem pós-fixada (depth-first traversal):

* **`static char* processar_no(NoAST* no)`:** Esta função implementa a lógica de tradução para cada tipo de nó da AST.
    * **Expressões:** Obtém os endereços dos argumentos (`esq`, `dir`), aloca um novo temporário (`res = novo_temp()`), emite a instrução TAC correspondente (ex: `t0 = a + b`), e **retorna** o nome desse temporário (`res`) para o nó pai.
    * **Comandos:** Emite as instruções de controle de fluxo (ex: `TAC_IFZ`, `TAC_GOTO`, `TAC_LABEL`) e retorna `NULL`, já que comandos não produzem um valor.

A manipulação de estruturas como **operadores lógicos (AND/OR)** e **loops (`while`, `for`)** exige a emissão de sequências de instruções, utilizando os rótulos gerados por `novo_label()` para implementar a lógica de *short-circuit* e a repetição controlada.

---

## 5. Execução

### 5.1. Código Fonte

O código de teste utilizado (`ok_03_chamadaFuncao.py`) define duas variáveis e duas funções de soma, chamando a primeira função com variáveis e a segunda com constantes:

```python
a = 2
b = 2

def soma(a, b):
    return a + b

print(soma(a, b))

def soma2(c, d):
    return c + d

print(soma(1, 2))

```
TAC gerado na execução desse caso de teste:

![TAC gerado](../assets/desenvolvimento/image.png)

---

## Histórico de Versões 

| Versão |Descrição     |Autor                                       |Data    |Revisor|
|:-:     | :-:          | :-:                                        | :-:    |:-:    |
|1.0     | Criação do Documento | [Rafael Schadt](https://github.com/RafaelSchadt) |  26/11/2025 |  [Ludmila Nunes](https://github.com/ludmilaaysha) |