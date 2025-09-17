

rodar teste:
```
cd lexer
flex lexer.l
gcc lex.yy.c -o analisador -lfl
./analisador < ../tests/lexico/test_lexico_func.py

```