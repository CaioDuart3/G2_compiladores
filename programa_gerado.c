#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    /* Declarações de variáveis globais */
    int a = 2;
    int b = 2;


int soma(int a, int b) {
  return (a + b);
}

int soma2(int c, int d) {
  return (c + d);
}

int main() {
  a = 2;
  b = 2;
  printf("%d", soma(a, b));
  printf("%d", soma(1, 2));
    return 0;
}
