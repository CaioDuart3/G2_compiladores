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

# Função de compilação
compile() {
    local target="$1"

    echo "Compilando Bison..."
    if ! bison -d -o "$PARSER_C" "$PARSER_SRC"; then
        echo "Falha na compilação do parser"
        exit 1
    fi

    echo "Compilando Flex..."
    if ! flex -o "$LEXER_C" "$LEXER_SRC"; then
        echo "Falha na compilação do lexer"
        exit 1
    fi

    if [ "$target" = "lexer" ]; then
        echo "Compilando executável do lexer..."
        if ! gcc "$LEXER_C" -o "$ANALISADOR_LEX" -lfl; then
            echo "Falha na compilação do analisador léxico"
            exit 1
        fi
    else
        echo "Compilando compilador..."
        if ! gcc "$PARSER_C" "$LEXER_C" -o "$COMPILADOR" -lfl; then
            echo "Falha na compilação do compilador"
            exit 1
        fi
    fi
}

# Compila se necessário
[ ! -x "$ANALISADOR_LEX" ] || [ "$LEXER_SRC" -nt "$ANALISADOR_LEX" ] && compile "lexer"
[ ! -x "$COMPILADOR" ] || [ "$PARSER_SRC" -nt "$COMPILADOR" ] || [ "$LEXER_SRC" -nt "$COMPILADOR" ] && compile "compilador"

mkdir -p "$OUTPUTS_DIR"
shopt -s nullglob

# Arrays para erros
declare -a erros
total=0
failures=0

# Itera pelos tipos de teste
for tipo in lexico sintatico semantico; do
    TIPO_DIR="$TESTS_DIR/$tipo"
    [ -d "$TIPO_DIR" ] || continue

    mkdir -p "$OUTPUTS_DIR/$tipo"

    for f in "$TIPO_DIR"/*.py; do
        base=$(basename "$f" .py)
        total=$((total+1))

        # Escolhe executável e mensagem de erro
        case "$tipo" in
            lexico) EXEC="$ANALISADOR_LEX"; ERRO="Token desconhecido ou inválido";;
            sintatico) EXEC="$COMPILADOR"; ERRO="Erro de sintaxe no parser";;
            semantico) EXEC="$COMPILADOR"; ERRO="Erro semântico detectado";;
        esac

        # Executa e captura saída
        OUTPUT=$("$EXEC" < "$f" 2>&1)
        echo "$OUTPUT" > "$OUTPUTS_DIR/$tipo/$base.out"

        # Verifica erro
        if echo "$OUTPUT" | grep -q "ERRO"; then
            echo -n "E"
            failures=$((failures+1))
            erros+=("[$tipo] $base: $ERRO")
        else
            echo -n "."
        fi
    done
done

shopt -u nullglob

# Linha de separação e relatório detalhado
echo
echo
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

# --- Limpeza de arquivos residuais ---
rm -f "$LEXER_C" "$PARSER_C" "$PARSER_H" "$ANALISADOR_LEX" "$COMPILADOR"
