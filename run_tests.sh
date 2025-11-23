#!/bin/bash

# --- Configuração de Caminhos ---
ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
SRC_DIR="$ROOT_DIR/src"

AST_DIR="$SRC_DIR/ast"
AST_C="$AST_DIR/ast.c"
AST_H="$AST_DIR/ast.h"

LEXER_DIR="$SRC_DIR/lexer"
LEXER_SRC="$LEXER_DIR/lexer.l"
LEXER_C="$LEXER_DIR/lex.yy.c"
LEXER_MAIN="$LEXER_DIR/lexer_main.c"

PARSER_DIR="$SRC_DIR/parser"
PARSER_SRC="$PARSER_DIR/parser.y"
PARSER_C="$PARSER_DIR/parser.tab.c"
PARSER_H="$PARSER_DIR/parser.tab.h"

ST_DIR="$SRC_DIR/st"
ST_C="$ST_DIR/st.c"
ST_H="$ST_DIR/st.h"

# --- ADICIONADO: Configuração do TAC ---
TAC_DIR="$SRC_DIR/tac"
TAC_C="$TAC_DIR/tac.c"
TAC_H="$TAC_DIR/tac.h"

# --- Nossos dois executáveis ---
COMPILADOR="$ROOT_DIR/compilador"
ANALISADOR_LEX="$ROOT_DIR/analisador_lexico"

TESTS_DIR="$SRC_DIR/tests/inputs"
OUTPUTS_DIR="$SRC_DIR/tests/outputs"

# --- Função de Compilação ---
compile_all() {
    echo "Compilando o parser (Bison)..."
    bison -d -v -o "$PARSER_C" -Wcounterexamples "$PARSER_SRC" || { echo "Falha na compilação do parser"; exit 1; }

    echo "Compilando o lexer (Flex)..."
    flex -o "$LEXER_C" "$LEXER_SRC" || { echo "Falha na compilação do lexer"; exit 1; }

    echo "Compilando o COMPILADOR completo (parser+lexer+ast+st+tac)..."
    # ADICIONADO: $TAC_C e -I$TAC_DIR
    gcc -g -Wall \
        "$PARSER_C" "$LEXER_C" "$AST_C" "$ST_C" "$TAC_C" \
        -I"$AST_DIR" -I"$PARSER_DIR" -I"$ST_DIR" -I"$TAC_DIR" \
        -o "$COMPILADOR" -lfl || { echo "Falha na compilação do COMPILADOR"; exit 1; }

    echo "Compilando o ANALISADOR LÉXICO (lexer_main + lexer)..."
    gcc -g -Wall \
        "$LEXER_MAIN" "$LEXER_C" \
        -I"$PARSER_DIR" -I"$ST_DIR" -I"$AST_DIR" \
        -o "$ANALISADOR_LEX" -lfl || { echo "Falha na compilação do ANALISADOR LÉXICO"; exit 1; }

    echo "Compilação concluída."
}

# --- Verifica se precisa compilar ---
# ADICIONADO: Checagem de ST e TAC nas datas de modificação
if [ ! -x "$COMPILADOR" ] || [ ! -x "$ANALISADOR_LEX" ] || \
   [ "$PARSER_SRC" -nt "$COMPILADOR" ] || [ "$LEXER_SRC" -nt "$COMPILADOR" ] || \
   [ "$AST_C" -nt "$COMPILADOR" ] || [ "$AST_H" -nt "$COMPILADOR" ] || \
   [ "$ST_C" -nt "$COMPILADOR" ] || [ "$ST_H" -nt "$COMPILADOR" ] || \
   [ "$TAC_C" -nt "$COMPILADOR" ] || [ "$TAC_H" -nt "$COMPILADOR" ] || \
   [ "$LEXER_MAIN" -nt "$ANALISADOR_LEX" ]; then
    compile_all
fi

mkdir -p "$OUTPUTS_DIR"
shopt -s nullglob

declare -a erros
total=0
failures=0
passes=0

echo
echo "Executando testes ('.'=Passou, 'F'=Falhou)"

# Itera pelos tipos de teste
for tipo in lexico sintatico semantico; do
    TIPO_DIR="$TESTS_DIR/$tipo"
    [ -d "$TIPO_DIR" ] || continue

    mkdir -p "$OUTPUTS_DIR/$tipo"

    # Escolhe executável correto
    case "$tipo" in
        lexico) EXEC="$ANALISADOR_LEX" ;;
        sintatico|semantico) EXEC="$COMPILADOR" ;;
        *) echo "Tipo de teste desconhecido: $tipo"; continue ;;
    esac

    for f in "$TIPO_DIR"/*.py; do
        base=$(basename "$f" .py)
        total=$((total+1))

        OUTPUT=$("$EXEC" < "$f" 2>&1)
        STATUS=$?

        echo "$OUTPUT" > "$OUTPUTS_DIR/$tipo/$base.out"

        DEU_ERRO=
        if [ $STATUS -ne 0 ] || grep -q "ERRO" <<< "$OUTPUT"; then
            DEU_ERRO=1
        fi

        ERRO_DETALHADO=$(grep "ERRO" <<< "$OUTPUT")

        case "$base" in
            ok_*)
                if [ -n "$DEU_ERRO" ]; then
                    echo -n "F"
                    failures=$((failures+1))
                    erros+=("[$tipo] $base: FALHOU. Teste deveria passar, mas deu erro: $ERRO_DETALHADO")
                else
                    echo -n "."
                    passes=$((passes+1))
                fi
                ;;
            erro_*)
                if [ -n "$DEU_ERRO" ]; then
                    echo -n "."
                    passes=$((passes+1))
                else
                    echo -n "F"
                    failures=$((failures+1))
                    erros+=("[$tipo] $base: FALHOU. Teste deveria dar erro, mas passou.")
                fi
                ;;
            *)
                echo -n "W"
                erros+=("[$tipo] $base: AVISO. Nome não começa com 'ok_' ou 'erro_'.")
                ;;
        esac
    done
done

shopt -u nullglob

# --- Relatório Final ---
echo
echo
if [ $failures -gt 0 ]; then
    echo "==================== FALHAS DETECTADAS ===================="
    printf '%s\n' "${erros[@]}"
    echo "=========================================================="
    echo "Resultado: $failures falha(s), $passes acerto(s) em $total testes."
else
    echo "Todos os $total testes passaram!"
fi

# --- Limpeza ---
rm -f "$LEXER_C" "$PARSER_C" "$PARSER_H"
# rm -f "$COMPILADOR" "$ANALISADOR_LEX"  <-- Comentei isso para ele não recompilar toda vez sem necessidade