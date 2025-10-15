# Nome do executável final
TARGET = py2c

# Arquivos fonte
BISON_SOURCE = parser.y
FLEX_SOURCE = lexer.l

# Arquivos gerados pelo bison e flex
BISON_OUTPUT_C = parser.tab.c
BISON_OUTPUT_H = parser.tab.h # Gerado pelo bison -d
FLEX_OUTPUT_C = lex.yy.c

# Flags do compilador
CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lfl # Linka com a biblioteca flex/lex

# ----------------------------------------------------------------------
# Regra principal (all)
# O comando 'make' sem argumentos tentará construir o TARGET.
.PHONY: all
all: $(TARGET)

# ----------------------------------------------------------------------
# Construção do executável final (py2c)
# Depende dos arquivos C gerados e os compila com o gcc.
$(TARGET): $(BISON_OUTPUT_C) $(FLEX_OUTPUT_C)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# ----------------------------------------------------------------------
# Geração do código C e H do parser (parser.tab.c e parser.tab.h)
# Roda: bison -d parser.y
$(BISON_OUTPUT_C) $(BISON_OUTPUT_H): $(BISON_SOURCE)
	bison -d $<

# ----------------------------------------------------------------------
# Geração do código C do lexer (lex.yy.c)
# Roda: flex lexer.l
$(FLEX_OUTPUT_C): $(FLEX_SOURCE)
	flex $<

# ----------------------------------------------------------------------
# Regra de Limpeza
# Remove os arquivos gerados.
.PHONY: clean
clean:
	rm -f $(TARGET) $(BISON_OUTPUT_C) $(BISON_OUTPUT_H) $(FLEX_OUTPUT_C)

# ----------------------------------------------------------------------
# Regra para rodar o executável (Opcional, mas útil)
.PHONY: run
run: $(TARGET)
	./$(TARGET) teste.py
