# Apresentação do projeto

Projeto de um compilador Python para C elaborado como parte da disciplina **"Compiladores"**, ministrada pelo professor Sergio Freitas.  
O sistema é desenvolvido pela equipe **Runtime Terrors** e tem como objetivo criar um compilador utilizando as ferramentas **Flex** e **Bison**.

---

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
- **Flex** 
- **Bison** 
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
---

## Integrantes

| [<img src="https://avatars.githubusercontent.com/u/134105981?v=4" width="120px"><br>Caio Duarte](https://github.com/caioduart3) | [<img src="https://avatars.githubusercontent.com/u/91512745?v=4" width="120px"><br>Ludmila Aysha](https://github.com/ludmilaaysha) | [<img src="https://avatars.githubusercontent.com/u/179030119?v=4" width="120px"><br>Rafael Welz](https://github.com/RafaelSchadt) | [<img src="https://avatars.githubusercontent.com/u/145882190?v=4" width="120px"><br>Isaque Camargos](https://github.com/isaqzin) | [<img src="https://avatars.githubusercontent.com/u/143897458?v=4" width="120px"><br>Laryssa Felix](https://github.com/felixlaryssa) |
|---|---|---|---|---|

---

## Histórico de Versões  

**Tabela 1: Histórico de versões**

| Versão | Descrição            | Autor                                         | Data       | Revisor |
|--------|----------------------|-----------------------------------------------|------------|---------|
| 1.0    | Criação do documento | [Caio Duarte](https://github.com/caioduart3)  | 02/05/2025 | [Laryssa Felix](https://github.com/felixlaryssa) |
| 1.1    | Atualização do documento | [Isaque Camargos](https://github.com/isaqzin)  | 26/11/2025 | [Laryssa Felix](https://github.com/felixlaryssa) |

---

Fonte: [Caio Duarte](https://github.com/caioduart3), [Ludmila Aysha](https://github.com/ludmilaaysha), [Rafael Welz](https://github.com/RafaelSchadt), [Isaque Camargos](https://github.com/isaqzin), [Laryssa Felix](https://github.com/felixlaryssa), 2025.
