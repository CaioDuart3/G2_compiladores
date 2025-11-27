#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    /* Declarações de variáveis globais */
    int a = 1;
    int b = 1;
    int c = 1;
    int d = 1;


int main() {
  a = 1;
  b = 1;
  c = 1;
  d = 1;
  if ((a || (c && d))) {
    printf("if");
  } else {
    printf("else");
  }
    return 0;
}
