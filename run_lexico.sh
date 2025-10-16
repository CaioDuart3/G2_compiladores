#!/bin/bash

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"

LEXER_DIR="$ROOT_DIR/src/lexer"
LEXER_SRC="$LEXER_DIR/lexer.l"
LEXER_C="$LEXER_DIR/lex.yy.c"
ANALISADOR="$LEXER_DIR/analisador_lexico"

TESTS_DIR="$ROOT_DIR/src/tests/inputs"
OUTPUTS_DIR="$ROOT_DIR/src/tests/outputs"

# --- Função para compilar o lexer ---
compile_lexer() {
    echo "⚙️ Compilando lexer..."
    flex -o "$LEXER_C" "$LEXER_SRC" >/dev/null 2>&1 || { echo "❌ Erro no flex"; exit 1; }
    gcc "$LEXER_C" -o "$ANALISADOR" -lfl >/dev/null 2>&1 || { echo "❌ Erro na compilação com gcc"; exit 1; }
    echo "✅ Lexer compilado com sucesso."
}

# --- Recompila se necessário ---
[ ! -x "$ANALISADOR" ] || [ "$LEXER_SRC" -nt "$ANALISADOR" ] && compile_lexer

# --- Cria diretório de saídas ---
mkdir -p "$OUTPUTS_DIR"
shopt -s nullglob

# --- Arrays para erros ---
declare -a erros
total=0
failures=0

# --- Executa apenas testes léxicos ---
tipo="lexico"
TIPO_DIR="$TESTS_DIR/$tipo"
[ -d "$TIPO_DIR" ] || { echo "Nenhum diretório de testes encontrado em $TIPO_DIR."; exit 0; }

mkdir -p "$OUTPUTS_DIR/$tipo"

for f in "$TIPO_DIR"/*.py; do
    base=$(basename "$f" .py)
    total=$((total+1))

    # Executa o analisador e captura a saída
    OUTPUT=$("$ANALISADOR" < "$f" 2>&1)
    echo "$OUTPUT" > "$OUTPUTS_DIR/$tipo/$base.out"

    # Verifica erros na saída (palavra 'ERRO')
    if echo "$OUTPUT" | grep -q "ERRO"; then
        echo -n "E"
        failures=$((failures+1))
        erros+=("[$tipo] $base: Token desconhecido ou inválido")
    else
        echo -n "."
    fi
done

shopt -u nullglob
echo
echo

# --- Relatório final ---
if [ $failures -gt 0 ]; then
    echo "===================="
    for e in "${erros[@]}"; do
        echo "E: $e"
    done
    echo "===================="
    echo "$total casos de testes, $failures teste(s) falharam."
else
    echo "Todos os testes passaram ($total casos)."
fi

# --- Limpeza final ---
rm -f "$LEXER_C" "$ANALISADOR"
