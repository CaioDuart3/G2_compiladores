#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    /* Declarações de variáveis globais */
    int soma = 3;
    int a = 1;
    int b = 2;
    int c = 0;
    char* d = "ola mundo";
    float f = 3.140000;
    int vetor_int[4];


int main() {
  vetor_int[0] = 0;
  vetor_int[1] = 2;
  vetor_int[2] = 3;
  vetor_int[3] = 4;
  a = 1;
  b = 2;
  c = 1;
  d = "ola mundo";
  f = 1.400000;
  soma = (a + b);
  if ((a < b)) {
    f = 3.140000;
    c = 0;
    vetor_int[0] = 0;
  }
    return 0;
}
