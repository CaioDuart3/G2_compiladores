#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    /* Declarações de variáveis globais */
    int a = 2;
    int b = 1;
    int x = 0;
    int y = 0;


int soma(int x, int y) {
  return (x + y);
}

int main() {
  a = 1;
  b = 1;
  y = 0;
  x = 0;
  if ((a && b)) {
    b = (b + 1);
    if ((b || a)) {
      a = (a + 1);
    }
    b = 1;
    x = soma(a, b);
    if ((soma(a, b) > 10)) {
      a = (a + 2);
    } else {
      printf("acabou");
    }
  }
    return 0;
}
