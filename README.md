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
## How to Run the Tests

Run the following in your terminal:
```
chmod +x run_tests.sh && ./run_tests.sh
```
