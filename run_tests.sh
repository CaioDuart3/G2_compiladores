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

TAC_DIR="$SRC_DIR/tac"
TAC_C="$TAC_DIR/tac.c"
TAC_H="$TAC_DIR/tac.h"

CODEGEN_DIR="$SRC_DIR/codigo_final"
CODEGEN_C="$CODEGEN_DIR/gerador_codigo_final.c"
CODEGEN_H="$CODEGEN_DIR/gerador_codigo_final.h"

# --- Executáveis ---
COMPILADOR="$ROOT_DIR/compilador"
ANALISADOR_LEX="$ROOT_DIR/analisador_lexico"

TESTS_DIR="$SRC_DIR/tests/inputs"
OUTPUTS_DIR="$SRC_DIR/tests/outputs"

# --- Função de Compilação ---
compile_all() {
    echo "--------------------------------------------------"
    echo "Iniciando Compilação..."
    
    # 1. Bison
    if bison -d -o "$PARSER_C" "$PARSER_SRC"; then
        echo "[OK] Parser (Bison) compilado."
    else
        echo "[ERRO] Falha no Bison."
        exit 1
    fi

    # 2. Flex
    if flex -o "$LEXER_C" "$LEXER_SRC"; then
        echo "[OK] Lexer (Flex) compilado."
    else
        echo "[ERRO] Falha no Flex."
        exit 1
    fi

    # 3. Compilador Completo
    if gcc -g -Wall \
        "$PARSER_C" "$LEXER_C" "$AST_C" "$ST_C" "$TAC_C" "$CODEGEN_C" \
        -I"$AST_DIR" -I"$PARSER_DIR" -I"$ST_DIR" -I"$TAC_DIR" -I"$CODEGEN_DIR" \
        -o "$COMPILADOR" -lfl; then
        echo "[OK] Executável COMPILADOR criado."
    else
        echo "[ERRO] Falha ao linkar o COMPILADOR."
        exit 1
    fi

    # 4. Analisador Léxico (Debug)
    if gcc -g -Wall \
        "$LEXER_MAIN" "$LEXER_C" \
        -I"$PARSER_DIR" -I"$ST_DIR" -I"$AST_DIR" \
        -o "$ANALISADOR_LEX" -lfl; then
        echo "[OK] Executável ANALISADOR_LEX criado."
    else
        echo "[ERRO] Falha ao linkar o ANALISADOR LÉXICO."
        exit 1
    fi
    echo "--------------------------------------------------"
}

# --- Checagem de Recompilação ---
if [ ! -x "$COMPILADOR" ] || [ ! -x "$ANALISADOR_LEX" ] || \
   [ "$PARSER_SRC" -nt "$COMPILADOR" ] || [ "$LEXER_SRC" -nt "$COMPILADOR" ] || \
   [ "$AST_C" -nt "$COMPILADOR" ] || [ "$AST_H" -nt "$COMPILADOR" ] || \
   [ "$ST_C" -nt "$COMPILADOR" ] || [ "$ST_H" -nt "$COMPILADOR" ] || \
   [ "$TAC_C" -nt "$COMPILADOR" ] || [ "$TAC_H" -nt "$COMPILADOR" ] || \
   [ "$LEXER_MAIN" -nt "$ANALISADOR_LEX" ]; then
    compile_all
fi

# Cria diretório de outputs se não existir
mkdir -p "$OUTPUTS_DIR"
shopt -s nullglob

declare -a erros
total=0
failures=0
passes=0

echo
echo "Executando testes..."
echo "Legenda: '.' = Passou | 'F' = Falhou"
echo

# Itera pelos tipos de teste (pastas)
for tipo in lexico sintatico semantico; do
    TIPO_DIR="$TESTS_DIR/$tipo"
    [ -d "$TIPO_DIR" ] || continue

    mkdir -p "$OUTPUTS_DIR/$tipo"

    # Define qual executável usar
    case "$tipo" in
        lexico) EXEC="$ANALISADOR_LEX" ;;
        *)      EXEC="$COMPILADOR" ;;
    esac

    for f in "$TIPO_DIR"/*.py; do
        base=$(basename "$f" .py)
        total=$((total+1))

        # --- EXECUÇÃO DO TESTE ---
        # Captura stdout e stderr combinados
        OUTPUT=$("$EXEC" < "$f" 2>&1)
        STATUS=$?

        # Salva o output num arquivo .out
        echo "$OUTPUT" > "$OUTPUTS_DIR/$tipo/$base.out"

        # --- NOVO TRECHO AQUI ---
        # Verifica se o compilador gerou o arquivo 'programa_gerado.c'
        if [ -f "programa_gerado.c" ]; then
            # Move e renomeia para a pasta de outputs com o nome do teste (ex: ok_01.c)
            mv "programa_gerado.c" "$OUTPUTS_DIR/$tipo/$base.c"
            echo "   -> Gerado: $base.c" # Opcional: só para você ver no terminal
        fi

        
        # Verifica se houve erro na execução
        # Critério: Exit code != 0 OU a palavra "ERRO" (case insensitive) apareceu no output
        DEU_ERRO=0
        if [ $STATUS -ne 0 ] || echo "$OUTPUT" | grep -iq "ERRO"; then
            DEU_ERRO=1
        fi

        # Pega a linha do erro para o relatório (se houver)
        MSG_ERRO=$(echo "$OUTPUT" | grep -i "ERRO" | head -n 1)

        # --- NOVA LÓGICA DE VALIDAÇÃO ---
        # Se o nome do arquivo contém "erro", esperamos que falhe.
        # Caso contrário, esperamos que passe.
        if [[ "$base" == *"erro"* ]]; then
            # --- ESPERADO: FALHA ---
            if [ $DEU_ERRO -eq 1 ]; then
                echo -n "." # Passou (deu erro como esperado)
                passes=$((passes+1))
            else
                echo -n "F"
                failures=$((failures+1))
                erros+=("[$tipo] $base: FALHOU. Esperava erro, mas executou com sucesso.")
            fi
        else
            # --- ESPERADO: SUCESSO ---
            if [ $DEU_ERRO -eq 0 ]; then
                echo -n "." # Passou (sucesso como esperado)
                passes=$((passes+1))
            else
                echo -n "F"
                failures=$((failures+1))
                # Se tiver mensagem de erro capturada, mostra ela, senão mostra status
                if [ -z "$MSG_ERRO" ]; then MSG_ERRO="Exit code $STATUS"; fi
                erros+=("[$tipo] $base: FALHOU. Esperava sucesso, mas deu erro: $MSG_ERRO")
            fi
        fi
    done
done

shopt -u nullglob

# --- Relatório Final ---
echo
echo
if [ $failures -gt 0 ]; then
    echo "==================== RELATÓRIO DE FALHAS ===================="
    printf '%s\n' "${erros[@]}"
    echo "============================================================="
    echo "Resumo: $failures testes falharam. $passes passaram."
    echo "Verifique os detalhes em: $OUTPUTS_DIR"
    exit 1
else
    echo "Tudo verde! Todos os $total testes passaram."
    echo "Saídas geradas em: $OUTPUTS_DIR"
    exit 0
fi