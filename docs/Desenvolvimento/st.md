# ST - Symbol Table (Tabela de Símbolos)

## 1. Introdução

A Tabela de Símbolos (*Symbol Table - ST*) é uma das estruturas fundamentais do compilador, responsável por registrar e gerenciar informações sobre identificadores durante a análise semântica. Toda variável, função ou vetor declarado no código-fonte deve ser armazenado na ST, para permitir verificações como: uso antes da declaração, tipos incompatíveis, escopo válido e inicialização.

Na linguagem do projeto, a ST também oferece suporte a vetores, aos tipos básicos e ao controle explícito de escopos, permitindo uma análise semântica mais completa e segura.

## 2. Metodologia

A implementação da Tabela de Símbolos (ST) foi iniciada assim que o parser alcançou uma estrutura básica estável, permitindo reconhecer declarações, blocos e início de escopos. Com essa fundação, tornou-se possível integrar a ST ao processo de análise sintática para registrar identificadores conforme apareciam no código-fonte.

A metodologia adotada seguiu os seguintes princípios:

- Uso de uma tabela hash estática, de tamanho fixo (`TAM = 227`), escolhida para minimizar colisões sem exigir realocação dinâmica.
- Tratamento de colisões via encadeamento externo, mantendo listas ligadas em cada posição da tabela.
- Gerenciamento explícito de escopos, através do contador escopo_atual, permitindo diferenciar símbolos declarados em blocos distintos.
- Estrutura de nó de símbolo bem definida, contendo:

    - nome do identificador,
    - tipo,
    - escopo onde foi declarado,
    - valor (quando inicializado),
    - informações extras para vetores,
    - ponteiro para o próximo símbolo da lista no caso de colisão.

Essa abordagem permitiu ao grupo evoluir gradualmente o compilador: primeiro garantindo uma análise sintática estável, e em seguida adicionando a lógica de armazenamento e controle de identificadores de forma consistente com os escopos definidos pela linguagem.

## 3. Papel da ST no Compilador

A ST é utilizada durante:

- declaração de variáveis: é realizada inserção na tabela;
- uso de variáveis: é feita busca para validar existência e tipo;
- atribuições: há verificação de inicialização e compatibilidade de tipos;
- controle de escopos: entrada e saída de blocos com remoção automática dos símbolos daquele nível;
- operações com vetores: verificação de existência e acesso seguro.

Assim, ela atua como o núcleo da análise semântica, garantindo que o programa seja consistente e evitando que o compilador aceite operações inválidas.


## 4. Implementação

A implementação está concentrada nos seguintes componentes:

### 4.1 Estrutura de Hash

A função `hash()` mapeia strings para índices dentro de `TAM`, utilizando uma combinação simples mas eficiente (`h * 32 + caractere`).

### 4.2 Inserção

A função `insertST()`:

- cria um novo símbolo,
- inicializa seu valor padrão,
- atribui o escopo atual,
- o insere no início da lista ligada do bucket correspondente.

### 4.3 Busca

A função `searchST()` percorre a lista do bucket associado ao hash do nome, retornando o símbolo encontrado.

### 4.4 Controle de Escopo

- `openScope()` incrementa o escopo e inicia um novo nível.
- `closeScope()` remove todos os símbolos pertencentes ao escopo atual.
- `getScope()` retorna o nível atual.

Essa estratégia garante que variáveis locais desapareçam ao final de blocos.

### 4.5 Impressão

`showST()` exibe:

- nome,
- tipo,
- escopo,
- se foi inicializada,
- valor atual ou elementos do vetor.

### 4.6 Liberação de Memória

`freeST()` percorre toda a tabela e libera:

- vetores alocados,
- strings,
- nós de símbolos.

## 5. Execução

Durante a execução do compilador, o comportamento da Tabela de Símbolos se apresenta da seguinte forma:

### 5.1. Quando o programa contém declarações válidas

Os símbolos são registrados com sucesso, e a tabela pode ser exibida ao final com `showST()`, apresentando:

- tipos,
- escopos,
- estado de inicialização,
- valores atribuídos.

Exemplo típico de entrada válida:

```text
===== TABELA DE SÍMBOLOS =====
Nome: soma       | Tipo: INT     | Escopo: 0 | Inicializado: SIM | Valor: 3
Nome: c          | Tipo: BOOL    | Escopo: 0 | Inicializado: SIM | Valor: FALSE
Nome: d          | Tipo: STRING  | Escopo: 0 | Inicializado: SIM | Valor: "ola mundo"
Nome: f          | Tipo: FLOAT   | Escopo: 0 | Inicializado: SIM | Valor: 3.140000
Nome: vetor_int  | Tipo: VETOR   | Escopo: 0 | Inicializado: SIM | Valor: [0, 2, 3, 4]
===============================
```

### 5.2. Quando ocorre erro semântico envolvendo símbolos

A ST fornece mensagens como:

- uso de variável não existente,
- acesso a vetor não inicializado,
- consulta a identificador inexistente.

Exemplos:

```text
Erro: vetor 'a' não existe na tabela de símbolos.
Erro: vetor 'x' não foi inicializado.
```

## Histórico de Versões 

| Versão |Descrição     |Autor                                       |Data    |Revisor|
|:-:     | :-:          | :-:                                        | :-:    |:-:    |
|1.0     | Criação da v1 da documentação da st | [Ludmila Nunes](https://github.com/ludmilaaysha)   | 26/11/2025 | |