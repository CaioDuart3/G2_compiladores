# Apresentação

Projeto de um compilador Python para C elaborado como parte da disciplina **"Compiladores"**, ministrada pelo professor Sergio Freitas.  
O sistema é desenvolvido pela equipe **Runtime Terrors** e tem como objetivo criar um compilador utilizando as ferramentas **Flex** e **Bison**.

## Estrutura do Projeto

```
            
├── docs                 // Documentação          
│   ├── Desenvolvimento   
│   ├── Dificuldades      
│   ├── Escopo            
│   ├── Metodologia       
│   └── Planejamento      
├── site                 // Interface da documentação pelo MKdocs
├── src                  // código-fonte do compilador de Python para C  
│   ├── lexer           
│   ├── parser           
│   ├── ast               
│   ├── st                
│   ├── tac               
│   ├── codigo_final     
│   └── tests             
├── run_tests.sh
├── compilador          // executável do compilador
├── compiler            // script bash para utilizar o compilador
├── README.md 
└── mkdocs.yml
```

## Como Executar o Projeto


### Pré-requisitos

Antes de iniciar, certifique-se de ter instalado:

- **Python 3.8+**
- **Flex** – Gerador de analisadores léxicos
- **Bison** – Gerador de analisadores sintáticos
- **GCC** ou outro compilador C
- **Make** 

#### Instalação no Ubuntu/Debian

```bash
sudo apt update
sudo apt install flex bison build-essential
```

#### Instalação no macOS 

```bash
brew install flex bison
```

## Como Executar o Compilador (Python para C)

Após compilar o projeto, volte para a raiz do repositório.

1. Insira seu arquivo Python na raiz do projeto

você pode usar o comando abaixo para criar um arquivo Python

```bash
touch seu_codigo.py
```

em seguida insira o seu código python no arquivo criado.

2. Torne o compilador executável (somente na primeira execução)

```bash
chmod +x compiler
```

Obs: `compiler` é um script bash utilizado para executar o compilador.

3. Rodar o compilador

**Modo normal (gera o arquivo C, só mostra mensagens se der erro)**

```bash
./compiler seu_codigo.py saida.c
```

**Modo debug (mostra lexer, parser, AST, ST, TAC, etc.)**

```bash
./compiler -d seu_codigo.py saida.c
```

4. Saída gerada

Se não houver erros, será criado um arquivo C na raiz chamado `saida.c`

- Você pode trocar `saida.c` por outro nome de arquivo à sua escolha.

5. Em caso de erro

- O compilador não gera o arquivo .c
- Uma mensagem detalhada de erro é exibida no terminal

## Como Executar os Testes

Na pasta raiz do projeto: 

```bash
chmod +x run_tests.sh && ./run_tests.sh
```

O script irá:

- Executar os arquivos de teste em `src/tests/inputs/`
- Passar cada arquivo pelo compilador
- Gerar saídas em `src/tests/outputs/`

---

## Integrantes

| [<img src="https://avatars.githubusercontent.com/u/134105981?v=4" width="120px"><br>Caio Duarte](https://github.com/caioduart3) | [<img src="https://avatars.githubusercontent.com/u/145882190?v=4" width="120px"><br>Isaque Camargos](https://github.com/isaqzin) | [<img src="https://avatars.githubusercontent.com/u/143897458?v=4" width="120px"><br>Laryssa Felix](https://github.com/felixlaryssa) | [<img src="https://avatars.githubusercontent.com/u/91512745?v=4" width="120px"><br>Ludmila Aysha](https://github.com/ludmilaaysha) | [<img src="https://avatars.githubusercontent.com/u/179030119?v=4" width="120px"><br>Rafael Welz](https://github.com/RafaelSchadt)  | 
|---|---|---|---|---|

---

## Histórico de Versões  

**Tabela 1: Histórico de versões**

| Versão | Descrição            | Autor                                         | Data       | Revisor |
|--------|----------------------|-----------------------------------------------|------------|---------|
| 1.0    | Criação do documento | [Caio Duarte](https://github.com/caioduart3)  | 02/05/2025 | [Laryssa Felix](https://github.com/felixlaryssa) |
| 1.1    | Atualização do documento | [Isaque Camargos](https://github.com/isaqzin)  | 26/11/2025 | [Laryssa Felix](https://github.com/felixlaryssa) |
| 1.2    | Insere como compilar código | [Ludmila Aysha](https://github.com/ludmilaaysha)  | 27/11/2025 | [Caio Duarte](https://github.com/caioduart3) |

---

Fonte: [Caio Duarte](https://github.com/caioduart3), [Ludmila Aysha](https://github.com/ludmilaaysha), [Rafael Welz](https://github.com/RafaelSchadt), [Isaque Camargos](https://github.com/isaqzin), [Laryssa Felix](https://github.com/felixlaryssa), 2025.
