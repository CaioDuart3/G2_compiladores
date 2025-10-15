#!/bin/bash

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"

PARSER_DIR="$ROOT_DIR/src/parser"
LEXER_DIR="$ROOT_DIR/src/lexer"
PARSER_SRC="$PARSER_DIR/parser.y"
LEXER_SRC="$LEXER_DIR/lexer.l"
PARSER_C="$PARSER_DIR/parser.tab.c"
LEXER_C="$LEXER_DIR/lex.yy.c"
COMPILADOR="$PARSER_DIR/compilador"
TESTS_DIR="$ROOT_DIR/src/tests/sintatico"
OUTPUTS_DIR="$ROOT_DIR/src/outputs/sintatico"

# Função para compilar o parser
compile_parser() {
    echo "⚙️ Compilando compilador (parser + lexer)..."
    bison -d -o "$PARSER_C" "$PARSER_SRC" || { echo "❌ Falha no bison"; exit 1; }
    flex -o "$LEXER_C" "$LEXER_SRC" || { echo "❌ Falha no flex"; exit 1; }
    gcc "$PARSER_C" "$LEXER_C" -o "$COMPILADOR" -lfl || { echo "❌ Falha na compilação"; exit 1; }
    echo "✅ Compilador (parser + lexer) compilado com sucesso."
}

# Recompila se necessário
if [ ! -x "$COMPILADOR" ] || [ "$PARSER_SRC" -nt "$COMPILADOR" ] || [ "$LEXER_SRC" -nt "$COMPILADOR" ]; then
    echo "⚠️ Necessário compilar o compilador."
    compile_parser
fi

mkdir -p "$OUTPUTS_DIR"

shopt -s nullglob
for f in "$TESTS_DIR"/*.py; do
    base=$(basename "$f" .py)
    echo "----- Rodando sintático -> $base -----"
    OUTPUT=$("$COMPILADOR" < "$f" 2>&1)
    echo "$OUTPUT" > "$OUTPUTS_DIR/$base.out"
    if echo "$OUTPUT" | grep -q "Erro de sintaxe"; then
        echo "⚠️ Erro detectado em $base: Syntax Error."
    fi
done
shopt -u nullglob

echo "✔ Todos os testes sintáticos executados."
