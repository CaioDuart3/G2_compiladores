# G2_compiladores


  ![Untitled design](https://github.com/user-attachments/assets/d3f39c04-847b-4bb3-9bb6-db7d11f84ba4)


Projeto de um compilador Python para C elaborado como parte da disciplina **"Compiladores"**, ministrada pelo professor Sergio Freitas.  
O sistema é desenvolvido pela equipe **Runtime Terrors** e tem como objetivo criar um compilador utilizando as ferramentas **Flex** e **Bison**.

# Estrutura do Projeto

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

# Como Executar o Projeto


## Pré-requisitos

Antes de iniciar, certifique-se de ter instalado:

- **Python 3.8+**
- **Flex** – Gerador de analisadores léxicos
- **Bison** – Gerador de analisadores sintáticos
- **GCC** ou outro compilador C
- **Make** 

### Instalação no Ubuntu/Debian

```bash
sudo apt update
sudo apt install flex bison build-essential
```

### Instalação no macOS 

```bash
brew install flex bison
```

# Como Compilar o Projeto



```bash
cd src
make clean && make
```

# Como Executar os Testes

Na pasta raiz do projeto: 

```bash
chmod +x run_tests.sh && ./run_tests.sh
```

O script irá:

- Executar os arquivos de teste em `src/tests/inputs/`
- Passar cada arquivo pelo compilador
- Gerar saídas em `src/tests/outputs/`