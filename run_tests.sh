#!/bin/bash

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"

LEXER_DIR="$ROOT_DIR/src/lexer"
LEXER_SRC="$LEXER_DIR/lexer.l"
LEXER_C="$LEXER_DIR/lex.yy.c"
ANALISADOR="$LEXER_DIR/analisador"
TESTS_DIR="$ROOT_DIR/src/tests"
OUTPUTS_DIR="$ROOT_DIR/src/outputs"

# Função para compilar o lexer
compile_lexer() {
    echo "⚙️ Compilando lexer..."
    flex -o "$LEXER_C" "$LEXER_SRC" || { echo "❌ Falha no flex"; exit 1; }
    gcc "$LEXER_C" -o "$ANALISADOR" -lfl || { echo "❌ Falha na compilação"; exit 1; }
    echo "✅ Lexer compilado com sucesso."
}

# Recompila se o analisador não existir ou se lexer.l for mais novo que o analisador
if [ ! -x "$ANALISADOR" ] || [ "$LEXER_SRC" -nt "$ANALISADOR" ]; then
    echo "⚠️ Necessário compilar o analisador."
    compile_lexer
fi

# Garante a pasta de saídas
mkdir -p "$OUTPUTS_DIR"

shopt -s nullglob

for tipo in lexico sintatico semantico; do
    TIPO_DIR="$TESTS_DIR/$tipo"
    [ -d "$TIPO_DIR" ] || continue

    mkdir -p "$OUTPUTS_DIR/$tipo"

    for f in "$TIPO_DIR"/*.py; do
        base=$(basename "$f" .py)
        echo "----- Rodando $tipo -> $base -----"

        # Executa o analisador e captura a saída
        OUTPUT=$("$ANALISADOR" < "$f" 2>&1)

        # Sobrescreve a saída anterior
        echo "$OUTPUT" > "$OUTPUTS_DIR/$tipo/$base.out"

        # Verifica se há ERROR na saída
        if echo "$OUTPUT" | grep -q "ERROR:"; then
            echo "⚠️ Erro detectado em $base: token desconhecido encontrado."
        fi
    done
done

shopt -u nullglob

echo "✔ Todos os testes executados."
