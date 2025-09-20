#!/bin/bash

# Caminho absoluto da raiz do repositório (pasta onde está este script)
ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"

# Caminhos importantes
ANALISADOR="$ROOT_DIR/src/lexer/analisador"
TESTS_DIR="$ROOT_DIR/src/tests"
OUTPUTS_DIR="$ROOT_DIR/src/outputs"

# Verifica se o executável do analisador existe
if [ ! -x "$ANALISADOR" ]; then
    echo "❌ Executável não encontrado: $ANALISADOR"
    echo "Compile o analisador antes de rodar os testes (ex: cd src/lexer && flex lexer.l && gcc lex.yy.c -o analisador)."
    exit 1
fi

# Garante a pasta de saídas
mkdir -p "$OUTPUTS_DIR"

# Ativa nullglob para não expandir *.py em literal * quando a pasta está vazia
shopt -s nullglob

# Loop por cada categoria de teste
for tipo in lexico sintatico semantico; do
    TIPO_DIR="$TESTS_DIR/$tipo"
    [ -d "$TIPO_DIR" ] || continue

    # Garante pasta de saída para cada tipo
    mkdir -p "$OUTPUTS_DIR/$tipo"

    for f in "$TIPO_DIR"/*.py; do
        base=$(basename "$f" .py)
        echo "----- Rodando $tipo -> $base -----"
        
        # Executa o analisador e redireciona a saída para o arquivo .out correspondente
        "$ANALISADOR" < "$f" > "$OUTPUTS_DIR/$tipo/$base.out" 2>&1
    done
done

# Desativa nullglob
shopt -u nullglob

echo "✔ Todos os testes executados."
