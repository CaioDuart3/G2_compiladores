#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    /* Declarações de variáveis globais */
    int a = 1;
    int b = 0;


int main() {
  a = 1;
  b = 0;
  if (a) {
    if (b) {
      printf("não entra aqui");
    } else {
      printf("entra aqui");
    }
  }
    return 0;
}
