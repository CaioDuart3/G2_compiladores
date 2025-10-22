
# Escopo Geral do Compilador

O compilador deste projeto foi delimitado de forma clara, de modo a assegurar que sua implementação seja realizável dentro do tempo disponível. As funcionalidades selecionadas foram definidas levando em conta tanto a importância para a utilização prática da linguagem Python quanto a possibilidade de conversão adequada para a linguagem C.

## Tipos de Dados Suportados

O compilador oferece suporte aos seguintes tipos de dados:

* int;
* float;
* double;
* char;
* string;

## Operações e Expressões
As operações implementadas incluem:

* **Operações aritméticas básicas:** adição (+), subtração (-), multiplicação (*), divisão (/) e módulo (%)

* **Operadores relacionais(de comparação):** ==, !=, <, <=, >, >=

* **Operadores lógicos:** and, or, not (traduzidos para &&, || e ! em C)

## Entrada e Saída
São suportadas as seguintes funções de entrada e saída:

```print``` — para exibir valores na saída padrão

```scan``` — para leitura de valores da entrada padrão

## Estruturas de Controle
O compilador reconhece e traduz as seguintes estruturas de controle de fluxo:

* **Condicionais:** if, elif, else

* **Laços de repetição:** for, while

## Funções
Por fim, também está incluído no escopo o suporte à definição e chamada de funções, permitindo reutilização de trechos lógicos.

<br>

-------
# Escopo do Primeiro Ponto de Controle

 Neste primeiro ponto de controle do projeto, já foi possível implementar parte significativa das funcionalidades previstas para o compilador. A seguir, descrevemos o que foi concluído até o momento, separando os avanços alcançados no **analisador léxico** e no **analisador sintático**.

### Léxico
A etapa léxica está completa, sendo capaz de reconhecer:

- Variáveis
- Estruturas condicionais
- Laços de repetição
- Tipos de dados

Além disso, o léxico já trata mensagens de erro e contempla casos de teste específicos.

### Sintático
No analisador sintático, já foram definidas as regras para:

- Expressões matemáticas
- Atribuição de variáveis
- Chamadas de funções
- Início da estrutura de indentação

Também foram incorporadas regras para mensagens de erro e casos de teste.

### Pendências
Ainda falta implementar no sintático:

- Condicionais: `if`, `elif`, `else`
- Laços: `while`, `for`
- Definição de funções
- Declaração e uso de listas
- Declaração e uso de dicionários

Além disso, é necessário adicionar mais regras e estruturar corretamente a indentação para permitir a implementação completa de laços e condicionais.

## Histórico de Versões 
<p style="text-align: center; font-size: 14px;">
Tabela 1: Histórico de versões
</p>

| Versão | Descrição | Autor | Data | Revisor |
|:-:     | :-:       | :-:   | :-:  | :-:     |
| 1.0    | Criação do documento | [Laryssa Felix](https://github.com/felixlaryssa) | 01/10/2025 | [Caio Duarte](https://github.com/caioduart3) |

<p style="text-align: center; font-size: 10px; margin-top: 0;">
Fonte: <a href="https://github.com/caioduart3">Caio Duarte</a>, 
<a href="https://github.com/ludmilaaysha">Ludmila Aysha</a>, 
<a href="https://github.com/RafaelSchadt">Rafael Welz</a>, 
<a href="https://github.com/isaqzin">Isaque Camargos</a>, 
<a href="https://github.com/felixlaryssa">Laryssa Felix</a>, 2025.
</p>    