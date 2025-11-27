#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    /* Declarações de variáveis globais */


int testar_condicionais(int a, int b, int c) {
  if ((a == b)) {
    printf("a é igual a b (==)");
  } else {
    if (((a != b) && (b < c))) {
      printf("a é diferente de b (!=) E b é menor que c (<)");
    } else {
      if (((a > b) || (c <= b))) {
        printf("a é maior que b (>) OU c é menor ou igual a b (<=)");
      } else {
        printf("Nenhuma condição anterior satisfeita");
      }
      testar_condicionais(5, 3, 10);
    }
  }
}

int main() {
    return 0;
}
