

rodar teste:
```
cd lexer
flex lexer.l
gcc lex.yy.c -o analisador -lfl
./analisador < ../tests/exemplos/test_lexico.py
```