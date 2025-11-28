# G2_compiladores


  ![Untitled design](https://github.com/user-attachments/assets/d3f39c04-847b-4bb3-9bb6-db7d11f84ba4)


Projeto de um compilador Python para C elaborado como parte da disciplina **"Compiladores"**, ministrada pelo professor Sergio Freitas.  
O sistema é desenvolvido pela equipe **Runtime Terrors** e tem como objetivo criar um compilador utilizando as ferramentas **Flex** e **Bison**.

## Estrutura do Projeto

```
            
├── docs                  
│   ├── Desenvolvimento   
│   ├── Dificuldades      
│   ├── Escopo            
│   ├── Metodologia       
│   └── Planejamento      
├── site                  
├── src                   
│   ├── lexer           
│   ├── parser            
│   ├── ast               
│   ├── st                
│   ├── tac               
│   ├── codigo_final     
│   └── tests             
├── run_tests.sh          
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

## Como Compilar o Projeto

Dentro da pasta `src/`:

```bash
cd src
make clean && make
```

Isso irá gerar o binário `compiler` dentro da pasta `src/`.

## Como Executar o Compilador (Python para C)

Após compilar o projeto, volte para a raiz do repositório.

1. Coloque seu arquivo Python na raiz

Caso esteja em `src/` volte à raiz com

```bash
cd ..
```

Insira o arquivo. Por exemplo: `seu_codigo.py`

Caso queira criar um novo arquivo, você pode usar o comando abaixo

```bash
touch seu_codigo.py
```

2. Torne o compilador executável (somente na primeira execução)

```bash
chmod +x compiler
```

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