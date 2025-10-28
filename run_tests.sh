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
LEXER_MAIN="$LEXER_DIR/lexer_main.c" # <-- NOVO

PARSER_DIR="$SRC_DIR/parser"
PARSER_SRC="$PARSER_DIR/parser.y"
PARSER_C="$PARSER_DIR/parser.tab.c"
PARSER_H="$PARSER_DIR/parser.tab.h"

# --- Nossos dois executáveis ---
COMPILADOR="$ROOT_DIR/compilador"
ANALISADOR_LEX="$ROOT_DIR/analisador_lexico" # <-- NOVO

TESTS_DIR="$SRC_DIR/tests/inputs"
OUTPUTS_DIR="$SRC_DIR/tests/outputs"

# --- Função de Compilação Atualizada ---
compile_all() {
    echo "Compilando o parser (Bison)..."
    if ! bison -d -v -o "$PARSER_C" "$PARSER_SRC"; then
        echo "Falha na compilação do parser (Bison)"
        exit 1
    fi

    echo "Compilando o lexer (Flex)..."
    if ! flex -o "$LEXER_C" "$LEXER_SRC"; then
        echo "Falha na compilação do lexer (Flex)"
        exit 1
    fi

    echo "Compilando o COMPILADOR completo (parser+lexer+ast)..."
    if ! gcc -g -Wall \
             "$PARSER_C" "$LEXER_C" "$AST_C" \
             -I"$AST_DIR" -I"$PARSER_DIR" \
             -o "$COMPILADOR" -lfl; then
        echo "Falha na compilação final do COMPILADOR"
        exit 1
    fi

    echo "Compilando o ANALISADOR LÉXICO (lexer_main+lexer)..."
    if ! gcc -g -Wall \
             "$LEXER_MAIN" "$LEXER_C" \
             -I"$PARSER_DIR" \
             -o "$ANALISADOR_LEX" -lfl; then
        echo "Falha na compilação do ANALISADOR LÉXICO"
        exit 1
    fi
    
    echo "Compilação concluída."
}

# --- Lógica Principal ---

# Compila se qualquer executável estiver faltando ou se fontes forem mais novas
if [ ! -x "$COMPILADOR" ] || [ ! -x "$ANALISADOR_LEX" ] || \
   [ "$PARSER_SRC" -nt "$COMPILADOR" ] || [ "$LEXER_SRC" -nt "$COMPILADOR" ] || \
   [ "$AST_C" -nt "$COMPILADOR" ] || [ "$AST_H" -nt "$COMPILADOR" ] || \
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

    # --- ESCOLHE O EXECUTÁVEL CORRETO ---
    case "$tipo" in
        lexico)
            EXEC="$ANALISADOR_LEX"
            ;;
        sintatico|semantico)
            EXEC="$COMPILADOR"
            ;;
        *)
            echo "Tipo de teste desconhecido: $tipo"
            continue
            ;;
    esac

    for f in "$TIPO_DIR"/*.py; do
        base=$(basename "$f" .py)
        total=$((total+1))

        # Executa e captura saída (stdout e stderr)
        OUTPUT=$("$EXEC" < "$f" 2>&1)
        # Salva o código de saída (0 = sucesso, 1 = erro)
        STATUS=$? 
        
        echo "$OUTPUT" > "$OUTPUTS_DIR/$tipo/$base.out"
        
        # Verifica se o programa retornou erro (STATUS != 0) ou se imprimiu "ERRO"
        DEU_ERRO=
        if [ $STATUS -ne 0 ] || [ -n "$(echo "$OUTPUT" | grep "ERRO")" ]; then
            DEU_ERRO=1
        fi
        
        ERRO_DETALHADO=$(echo "$OUTPUT" | grep "ERRO")

        # --- Lógica de Sucesso/Falha Baseada no Nome ---
        case "$base" in
            ok_*)
                # Teste deve PASSAR (não deve ter erro)
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
                # Teste deve FALHAR (deve ter erro)
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
                echo -n "W" # 'W' de Warning (Aviso)
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
rm -f "$COMPILADOR" "$ANALISADOR_LEX"