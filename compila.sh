#!/bin/bash

# ==============================
# Script de compilação Python -> C
# ==============================

# Caminhos
ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
SRC_DIR="$ROOT_DIR/src"

AST_DIR="$SRC_DIR/ast"
LEXER_DIR="$SRC_DIR/lexer"
PARSER_DIR="$SRC_DIR/parser"
ST_DIR="$SRC_DIR/st"
CODEGEN_DIR="$SRC_DIR/codegen"

COMPILADOR="$ROOT_DIR/compilador"

# --- Arquivos principais ---
AST_C="$AST_DIR/ast.c"
AST_H="$AST_DIR/ast.h"
LEXER_SRC="$LEXER_DIR/lexer.l"
LEXER_C="$LEXER_DIR/lex.yy.c"
LEXER_MAIN="$LEXER_DIR/lexer_main.c"
PARSER_SRC="$PARSER_DIR/parser.y"
PARSER_C="$PARSER_DIR/parser.tab.c"
PARSER_H="$PARSER_DIR/parser.tab.h"
ST_C="$ST_DIR/st.c"
ST_H="$ST_DIR/st.h"
GERAR_C_C="$CODEGEN_DIR/gerarC.c"
GERAR_C_H="$CODEGEN_DIR/gerarC.h"

# ----------------------------
# Função de compilação do compilador
# ----------------------------
build_compiler() {
    echo "Compilando parser (Bison)..."
    bison -d -v -o "$PARSER_C" "$PARSER_SRC" || { echo "Erro parser"; exit 1; }

    echo "Compilando lexer (Flex)..."
    flex -o "$LEXER_C" "$LEXER_SRC" || { echo "Erro lexer"; exit 1; }

    echo "Compilando compilador..."
    gcc -g -Wall \
        "$PARSER_C" "$LEXER_C" "$AST_C" "$ST_C" "$GERAR_C_C" \
        -I"$AST_DIR" -I"$PARSER_DIR" -I"$ST_DIR" -I"$CODEGEN_DIR" \
        -o "$COMPILADOR" -lfl || { echo "Erro compilando compilador"; exit 1; }

    echo "Compilador pronto!"
}

# ----------------------------
# Verifica se compilador existe
# ----------------------------
if [ ! -x "$COMPILADOR" ]; then
    build_compiler
fi

# ----------------------------
# Recebe arquivo de entrada
# ----------------------------
if [ $# -lt 1 ]; then
    echo "Uso: $0 <arquivo_entrada.py>"
    exit 1
fi

INPUT_FILE="$1"
if [ ! -f "$INPUT_FILE" ]; then
    echo "Arquivo '$INPUT_FILE' não encontrado!"
    exit 1
fi

# ----------------------------
# Executa o compilador
# ----------------------------
echo "Compilando $INPUT_FILE..."
"$COMPILADOR" < "$INPUT_FILE"

if [ -f "saida.c" ]; then
    echo "Código C gerado em 'saida.c'"
    echo "Para compilar: gcc saida.c -o saida && ./saida"
else
    echo "Erro: não foi possível gerar 'saida.c'"
    exit 1
fi
