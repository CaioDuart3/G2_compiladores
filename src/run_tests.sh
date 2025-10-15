#!/bin/bash

# Caminho base (src)
ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"

# Caminhos dos arquivos e executáveis
LEXER_SRC="$ROOT_DIR/lexer.l"
PARSER_SRC="$ROOT_DIR/parser.y"
LEXER_C="$ROOT_DIR/lex.yy.c"
PARSER_C="$ROOT_DIR/parser.tab.c"
PARSER_H="$ROOT_DIR/parser.tab.h"
ANALISADOR_LEX="$ROOT_DIR/analisador_lexico"
COMPILADOR="$ROOT_DIR/compilador"

# Diretórios de testes
TESTS_DIR="$ROOT_DIR/tests/inputs"
OUTPUTS_DIR="$ROOT_DIR/tests/outputs"

# --- Função para compilar ---
compile() {
    local target="$1"

    # Gera código do Bison e do Flex
    bison -d -o "$PARSER_C" "$PARSER_SRC" >/dev/null 2>&1 || { echo "Erro no Bison"; exit 1; }
    flex -o "$LEXER_C" "$LEXER_SRC" >/dev/null 2>&1 || { echo "Erro no Flex"; exit 1; }

    # Compila o executável adequado
    if [ "$target" = "lexer" ]; then
        gcc "$LEXER_C" -o "$ANALISADOR_LEX" -lfl >/dev/null 2>&1 || { echo "Erro compilando analisador léxico"; exit 1; }
    else
        gcc "$PARSER_C" "$LEXER_C" -o "$COMPILADOR" -lfl >/dev/null 2>&1 || { echo "Erro compilando compilador"; exit 1; }
    fi
}

# --- Compila se necessário ---
if [ ! -x "$ANALISADOR_LEX" ] || [ "$LEXER_SRC" -nt "$ANALISADOR_LEX" ]; then
    compile "lexer"
fi

if [ ! -x "$COMPILADOR" ] || [ "$PARSER_SRC" -nt "$COMPILADOR" ] || [ "$LEXER_SRC" -nt "$COMPILADOR" ]; then
    compile "compilador"
fi

# --- Cria diretórios de saída ---
mkdir -p "$OUTPUTS_DIR"
shopt -s nullglob

# --- Variáveis de contagem ---
declare -a erros
total=0
failures=0

# --- Loop pelos tipos de teste ---
for tipo in lexico sintatico semantico; do
    TIPO_DIR="$TESTS_DIR/$tipo"
    [ -d "$TIPO_DIR" ] || continue

    mkdir -p "$OUTPUTS_DIR/$tipo"

    for f in "$TIPO_DIR"/*.py; do
        base=$(basename "$f" .py)
        total=$((total + 1))

        # Escolhe o executável e mensagem de erro
        case "$tipo" in
            lexico) EXEC="$ANALISADOR_LEX"; ERRO="Token desconhecido ou inválido";;
            sintatico) EXEC="$COMPILADOR"; ERRO="Erro de sintaxe no parser";;
            semantico) EXEC="$COMPILADOR"; ERRO="Erro semântico detectado";;
        esac

        # Executa o analisador e salva saída
        OUTPUT=$("$EXEC" < "$f" 2>&1)
        echo "$OUTPUT" > "$OUTPUTS_DIR/$tipo/$base.out"

        # Marca resultado
        if echo "$OUTPUT" | grep -q "ERRO"; then
            echo -n "E"
            failures=$((failures + 1))
            erros+=("[$tipo] $base: $ERRO")
        else
            echo -n "."
        fi
    done
done

shopt -u nullglob

# --- Relatório final ---
echo
echo
if [ $failures -gt 0 ]; then
    echo "===================="
    for e in "${erros[@]}"; do
        echo "E: $e"
    done
    echo "===================="
    echo "$total casos de teste, $failures falharam."
else
    echo "Todos os testes passaram ($total casos)."
fi

# --- Limpeza de arquivos temporários (opcional) ---
rm -f "$LEXER_C" "$PARSER_C" "$PARSER_H" "$ANALISADOR_LEX" "$COMPILADOR"
