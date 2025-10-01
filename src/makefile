# Compilador e flags
CC = gcc
FLEX = flex
BISON = bison
CFLAGS = -Wall -g

# Arquivos de entrada
LEXER = lexer/lexer.l
PARSER = parser/parser.y
MAIN = tests/main.c

# Arquivos gerados
LEXER_C = lexer/lex.yy.c
PARSER_C = parser/parser.tab.c
PARSER_H = parser/parser.tab.h
EXEC = compilador

# Regra padrão
all: $(EXEC)

# Gera o analisador léxico
$(LEXER_C): $(LEXER)
	$(FLEX) -o $(LEXER_C) $(LEXER)

# Gera o analisador sintático
$(PARSER_C) $(PARSER_H): $(PARSER)
	$(BISON) -d -o $(PARSER_C) $(PARSER)

# Compila tudo
$(EXEC): $(LEXER_C) $(PARSER_C) $(MAIN)
	$(CC) $(CFLAGS) -o $(EXEC) $(LEXER_C) $(PARSER_C) $(MAIN) -lfl

# Limpeza
clean:
	rm -f $(LEXER_C) $(PARSER_C) $(PARSER_H) $(EXEC)
