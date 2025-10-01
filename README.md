# G2_compiladores


  ![Untitled design](https://github.com/user-attachments/assets/d3f39c04-847b-4bb3-9bb6-db7d11f84ba4)


This is a repository for a Python-to-C compiler built using **Flex** and **Bison**.

## Project Structure
```
/G2_compiladores
├─ /site              # GitHub Pages site
├─ /docs              # Project documentation
├─ /src               # Compiler source code
│   ├─ lexer/         # Lexical analysis (tokenization)
│   ├─ parser/        # Syntax analysis (parse tree construction)
│   ├─ outputs/       # Output from tested analyzers
│   ├─ tests/         # Python code to be tested by the analyzers
│   ├─ ST/            # Symbol Table for syntax analysis
│   └─ main.py        # Compiler entry point
```
## How to Run the Project

This section will guide you through setting up and running the Python-to-C compiler.

### Prerequisites

Before running the project, make sure you have the following installed:

- Python 3.8+

- Flex (lexical analyzer generator)

- Bison (parser generator)

- GCC or another C compiler

- Make (optional, but helpful)

You can install Flex and Bison via:
````
# On Ubuntu/Debian:
sudo apt update
sudo apt install flex bison build-essential

# On macOS (using Homebrew):
brew install flex bison
````
### Running the Compiler

To run the compiler manually:

Navigate to the src/ directory:
```
cd src
```
### How to Run the Tests
To automatically run all test cases:
```
chmod +x run_tests.sh && ./run_tests.sh
```

This script will:

- Run all Python test files in src/tests/
- Process them through the compiler
S- ave the output C code in src/outputs/
