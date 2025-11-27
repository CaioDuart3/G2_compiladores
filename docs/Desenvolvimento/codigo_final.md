# Código Final

## 1. Introdução
Este documento descreve o funcionamento do módulo responsável por gerar o código final em C. O objetivo dessa etapa é transformar a representação intermediária do programa em um código C, permitindo sua compilação e execução.

---

## 2. Metodologia
A implementação segue uma abordagem sistemática baseada nos seguintes passos:

1. **Mapeamento da AST para C**: Cada nó da AST é analisado para determinar o equivalente em código C.
2. **Tratamento de comandos**: Estruturas como atribuições, laços, condições, chamadas de função e retornos são traduzidas diretamente para sua sintaxe correspondente em C.
3. **Tradução de tipos e operadores**: Tipos primitivos e operadores da linguagem fonte são convertidos para seus equivalentes em C.
4. **Criação de funções e bloco principal**: Funções definidas pelo usuário são geradas antes do `main()`, e o bloco principal executa comandos globais e inicialização de vetores.
5. **Integração com tabela de símbolos**: A geração de declarações utiliza informações da tabela de símbolos para mapear tipos corretos, valores iniciais e estruturas como vetores.

---

## 3. Papel do Código Final no Compilador
O módulo analisado corresponde à **última etapa do compilador**. Seu papel inclui:

- **Gerar código C válido, legível e compilável**.
- **Trabalhar junto com o analisador semântico e tabela de símbolos**.
- **Aplicar semântica operacional**, por exemplo:
  - Tradução de `print()` para `printf()`;
  - Expansão de `for` usando `range()` em laços `for` C;
  - Mapeamento de listas e vetores.

Sem essa etapa, o compilador não produziria saída executável.

---

## 4. Implementação
A implementação contém os seguintes elementos principais:

### 4.1 Buffers de Expressão
Um pool circular evita alocação dinâmica repetida para expressões C.

### 4.2 Conversão de Operadores
A função `operador_para_c()` traduz operadores aritméticos e lógicos de Python para C.

### 4.3 Geração de Declarações
`gerar_declaracoes()` percorre a tabela de símbolos gerando variáveis globais com valores iniciais apropriados.

### 4.4 Geração de Expressões
`gerar_expressao()` converte nós da AST em representações C:
- números;
- strings;
- booleanos;
- identificadores;
- operações binárias e lógicas;
- indexação de vetores;
- chamadas de função.



### 4.5 Geração de Comandos
`gerar_comando()` cobre:
- atribuições;
- atribuições múltiplas;
- `if/else`;
- `while`;
- `for` com `range`;
- retornos;
- funções.



### 4.6 Geração do Main
O compilador inclui:
- inicializações de vetores;
- comandos globais da AST;
- retorno padrão para terminar o programa.

A função principal é `gerar_codigo_final()`, que organiza todos os elementos gerados, inclui bibliotecas padrão e monta o arquivo final em C.

---

## 5. Execução

Para a execução do código final, na pasta raiz do projeto execute : 

```bash
chmod +x run_tests.sh && ./run_tests.sh
```

Procure por qualquer arquivo .cd dentro de src/tests/outputs/sintatico

```bash
cd src
cd tests
cd outputs
cd sintatico
```

## Histórico de Versões 

| Versão |Descrição     |Autor |Data    |Revisor|
|:-:     | :-:          | :-:  | :-:    |:-:    |
| 1.1    | Atualização do documento | [Isaque Camargos](https://github.com/isaqzin)  | 26/11/2025 | [Rafael Welz](https://github.com/RafaelSchadt) |