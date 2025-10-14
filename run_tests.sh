#!/bin/bash

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"

LEXER_DIR="$ROOT_DIR/src/lexer"
LEXER_SRC="$LEXER_DIR/lexer.l"
LEXER_C="$LEXER_DIR/lex.yy.c"
ANALISADOR_LEX="$LEXER_DIR/analisador_lexico"

PARSER_DIR="$ROOT_DIR/src/parser"
PARSER_SRC="$PARSER_DIR/parser.y"
PARSER_C="$PARSER_DIR/parser.tab.c"
PARSER_H="$PARSER_DIR/parser.tab.h"
COMPILADOR="$PARSER_DIR/compilador"

TESTS_DIR="$ROOT_DIR/src/tests/inputs"
OUTPUTS_DIR="$ROOT_DIR/src/tests/outputs"

# Função para compilar lexer
compile_lexer() {
    echo "⚙️ Compilando lexer..."
    bison -d -o "$PARSER_C" "$PARSER_SRC" || { echo "❌ Falha no bison"; exit 1; }
    flex -o "$LEXER_C" "$LEXER_SRC" || { echo "❌ Falha no flex"; exit 1; }
    gcc "$LEXER_C" -o "$ANALISADOR_LEX" -lfl || { echo "❌ Falha na compilação"; exit 1; }
    echo "✅ Lexer compilado com sucesso."
}

# Função para compilar parser + lexer
compile_parser() {
    echo "⚙️ Compilando compilador (parser + lexer)..."
    bison -d -o "$PARSER_C" "$PARSER_SRC" || { echo "❌ Falha no bison"; exit 1; }
    flex -o "$LEXER_C" "$LEXER_SRC" || { echo "❌ Falha no flex"; exit 1; }
    gcc "$PARSER_C" "$LEXER_C" -o "$COMPILADOR" -lfl || { echo "❌ Falha na compilação"; exit 1; }
    echo "✅ Compilador compilado com sucesso."
}

# Compila se necessário
[ ! -x "$ANALISADOR_LEX" ] || [ "$LEXER_SRC" -nt "$ANALISADOR_LEX" ] && compile_lexer && compile_parser
[ ! -x "$COMPILADOR" ] || [ "$PARSER_SRC" -nt "$COMPILADOR" ] || [ "$LEXER_SRC" -nt "$COMPILADOR" ] && compile_parser

mkdir -p "$OUTPUTS_DIR"
shopt -s nullglob

# Itera pelos tipos de teste
for tipo in lexico sintatico semantico; do
    TIPO_DIR="$TESTS_DIR/$tipo"
    [ -d "$TIPO_DIR" ] || continue

    mkdir -p "$OUTPUTS_DIR/$tipo"

    for f in "$TIPO_DIR"/*.py; do
        base=$(basename "$f" .py)
        echo "----- Rodando $tipo -> $base -----"

        # Escolhe o executável correto
        if [ "$tipo" = "lexico" ]; then
            EXEC="$ANALISADOR_LEX"
            ERRO="Token desconhecido encontrado."
        elif [ "$tipo" = "sintatico" ]; then
            EXEC="$COMPILADOR"
            ERRO="Erro de sintaxe"
        else
            EXEC="$COMPILADOR"
            ERRO="Erro semântico"
        fi

        # Executa o analisador e captura a saída
        OUTPUT=$("$EXEC" < "$f" 2>&1)

        # Salva a saída
        echo "$OUTPUT" > "$OUTPUTS_DIR/$tipo/$base.out"

        # Verifica se há erro
        if echo "$OUTPUT" | grep -q "ERRO"; then
            echo "⚠️ Erro detectado em $base: $ERRO"
        fi
    done
done

shopt -u nullglob
echo "✔ Todos os testes executados."

# --- LIMPEZA FINAL ---
echo "🧹 Limpando arquivos gerados pelo Flex/Bison..."
rm -f "$LEXER_C" "$PARSER_C" "$PARSER_H" "$ANALISADOR_LEX" "$COMPILADOR"
echo "✅ Limpeza concluída."
