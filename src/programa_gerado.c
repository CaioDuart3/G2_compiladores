#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    /* Declarações de variáveis globais */
    float soma_variaveis = 3.141500;
    float pi = 3.141500;
    float soma_com_constante = 4.141500;
    float flutuante = 2.000000;


int main() {
  pi = 3.141500;
  flutuante = 1.000000;
  flutuante = 0.000000;
  soma_variaveis = (pi + flutuante);
  soma_com_constante = (soma_variaveis + 1.000000);
  if (flutuante) {
    flutuante = 2.000000;
  }
    return 0;
}
