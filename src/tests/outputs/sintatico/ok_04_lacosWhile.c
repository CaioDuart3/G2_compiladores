#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    /* Declarações de variáveis globais */
    int i = 0;


int main() {
  i = 0;
  while ((i < 10)) {
    printf("%d", i);
    i = (i + 1);
  }
    return 0;
}
