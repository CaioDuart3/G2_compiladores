
# Escopo Geral do Compilador

O desenvolvimento do compilador contemplou um conjunto de funcionalidades essenciais para garantir a tradução correta de programas escritos em Python para sua correspondente implementação em linguagem C. O escopo atingido reflete tanto os requisitos mínimos para a execução de programas básicos quanto a viabilidade técnica dentro do prazo estabelecido.

Abaixo, estão descritos os elementos implementados, suas respectivas capacidades junto a amostras de casos de testes:

## Atribuições
Implementado suporte para declarações e atribuições de variáveis dos tipos primitivos mais comuns da linguagem Python, incluindo:

int, float, string, booleanos (True, False) e none.
Durante o processo de compilação, cada tipo é convertido para o tipo C equivalente, garantindo compatibilidade semântica. Além disso o compilador tem suporte para vetor de inteiros.

<details>
  <summary><strong>Código Python testado que contempla esse escopo</strong></summary>
/src/tests/inputs/sintatico/ok_01_declaracao.py

``` python
a =1
b= 2
c = True
d = "ola mundo"
f = 1.4
vetor_int = [1,2,3,4]
soma = a + b
if a < b:
    f = 3.14
    c = False
    vetor_int[0] = 0
```
</details>

<details>
  <summary><strong>Código C gerado que contempla o caso de teste acima</strong></summary>
/src/tests/outputs/sintatico/ok_01_declaracao.c

```C
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
```
</details>

## Operadores Aritméticos
Suporte completo aos operadores: +, -, *, /.

<details>
  <summary><strong>Código Python testado que contempla esse escopo</strong></summary>
/src/tests/inputs/sintatico/ok_02_expressoesMat.py
``` python
b = 1
c = 1
a = (6+2)/2*4
d = a+(b +c)*2
e = 2/2
```
</details>

<details>
  <summary><strong>Código C gerado que contempla o caso de teste acima</strong></summary>
/src/tests/outputs/sintatico/ok_02_expressoesMat.c

```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 /* Declarações de variáveis globais */
 int a = 16;
 int b = 1;
 int c = 1;
 int d = 20;
 int e = 1;


int main() {
 b = 1;
 c = 1;
 a = (((6 + 2) / 2) * 4);
 d = (a + ((b + c) * 2));
 e = (2 / 2);
    return 0;
}
```
</details>

## Expressões Matemáticas
Expressões numéricas envolvendo operações combinadas e precedência de operadores são reconhecidas e corretamente traduzidas.
Garantiu-se análise sintática adequada para expressões simples e compostas.


<details>
  <summary><strong>Código Python testado que contempla esse escopo</strong></summary>
/src/tests/inputs/sintatico/ok_02_expressoesMat.py
``` python
b = 1
c = 1
a = (6+2)/2*4
d = a+(b +c)*2
e = 2/2
```
</details>

<details>
  <summary><strong>Código C gerado que contempla o caso de teste acima</strong></summary>
/src/tests/outputs/sintatico/ok_02_expressoesMat.c

```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 /* Declarações de variáveis globais */
 int a = 16;
 int b = 1;
 int c = 1;
 int d = 20;
 int e = 1;


int main() {
 b = 1;
 c = 1;
 a = (((6 + 2) / 2) * 4);
 d = (a + ((b + c) * 2));
 e = (2 / 2);
    return 0;
}
```
</details>

## Estruturas Condicionais
Implementação de condicionais aninhadas utilizando if e else.
Embora a linguagem Python disponha de elif, essa construção foi propositalmente omitida. Casos que envolvem múltiplas condições são tratados por encadeamento aninhado de else-if.

<details>
  <summary><strong>Código Python testado que contempla esse escopo</strong></summary>
/src/tests/inputs/sintatico/ok_06_decisaoIf.py

``` python
def testar_condicionais(a, b, c):
    if a == b:
        print("a é igual a b (==)")
    else:
        if a != b and b < c:
            print("a é diferente de b (!=) E b é menor que c (<)")
        else:
            if a > b or c <= b:
                print("a é maior que b (>) OU c é menor ou igual a b (<=)")
            else:
                print("Nenhuma condição anterior satisfeita")



testar_condicionais(5, 3, 10)
```
</details>
<details>
  <summary><strong>Código C gerado que contempla o caso de teste acima</strong></summary>
/src/tests/outputs/sintatico/ok_06_decisaoIf.c


```C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 /* Declarações de variáveis globais */


int testar_condicionais(int a, int b, int c) {
 if ((a ! 0)) {
  printf("negado");
 }
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

```
</details>

## Operadores Lógicos
O compilador reconhece e traduz corretamente operadores lógicos e relacionais, como:
and, or, >, >=, <, <=, !=.


<details>
  <summary><strong>Código Python testado que contempla esse escopo</strong></summary>
/src/tests/inputs/sintatico/ok_06_decisaoIf.py

``` python
def testar_condicionais(a, b, c):
    if a == b:
        print("a é igual a b (==)")
    else:
        if a != b and b < c:
            print("a é diferente de b (!=) E b é menor que c (<)")
        else:
            if a > b or c <= b:
                print("a é maior que b (>) OU c é menor ou igual a b (<=)")
            else:
                print("Nenhuma condição anterior satisfeita")



testar_condicionais(5, 3, 10)
```
</details>
<details>
  <summary><strong>Código C gerado que contempla o caso de teste acima</strong></summary>
/src/tests/outputs/sintatico/ok_06_decisaoIf.c


```C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 /* Declarações de variáveis globais */


int testar_condicionais(int a, int b, int c) {
 if ((a ! 0)) {
  printf("negado");
 }
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

```
</details>



## Laços de Repetição
Implementação dos dois principais laços utilizados no recorte do projeto:

### while

<details>
  <summary><strong>Código Python testado que contempla esse escopo</strong></summary>
/src/tests/inputs/sintatico/ok_04_lacosWhile.py

``` python
i =0
while i <10:
    print(i)
    i=i+1
```
</details>

<details>
  <summary><strong>Código C gerado que contempla o caso de teste acima</strong></summary>
/src/tests/outputs/sintatico/ok_04_lacosWhile.c

```C
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
```
</details>



### for i in range(n) (com suporte para range simples)
Ambos são traduzidos para estruturas de repetição equivalentes em C, mantendo controle de fluxo e variáveis de iteração.

<details>
  <summary><strong>Código Python testado que contempla esse escopo</strong></summary>
/src/tests/outputs/sintatico/ok_05_for.py

``` python
for i in range(0,5):
    print(f"i: {i}")
```
</details>

<details>
  <summary><strong>Código C gerado que contempla o caso de teste acima</strong></summary>
/src/tests/outputs/sintatico/ok_05_for.c

```C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 /* Declarações de variáveis globais */


int main() {
 for (int __i = 0; __i < 5; __i++) {
  i = __i;
  printf("%d", i);
 }
    return 0;
}

```
</details>

## Funções, Chamadas e Retornos
O compilador suporta a declaração e utilização de funções com retorno void e int.
Há suporte para, parâmetros, chamadas a funções, retorno de valores.

escopo local de variáveis.
As funções em Python são mapeadas diretamente para funções em C, conforme os tipos permitidos.

<details>
  <summary><strong>Código Python testado que contempla esse escopo</strong></summary>
/src/tests/inputs/sintatico/ok_03_chamadaFuncao.py

``` python
a = 2
b = 2
def soma(a ,b):
    return a+b
print(soma(a,b))

def soma2(c ,d):
    print(c+d)
```
</details>

<details>
  <summary><strong>Código C gerado que contempla o caso de teste acima</strong></summary>
/src/tests/outputs/sintatico/ok_03_chamadaFuncao.c

```C
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
 printf("%d", (c + d));
}

int main() {
 a = 2;
 b = 2;
 printf("%d", soma(a, b));
    return 0;
}
```
</details>






## Histórico de Versões 
<p style="text-align: center; font-size: 14px;">
Tabela 1: Histórico de versões
</p>

| Versão | Descrição | Autor | Data | Revisor |
|:-:     | :-:       | :-:   | :-:  | :-:     |
| 1.0    | Criação do documento | [Laryssa Felix](https://github.com/felixlaryssa) | 01/10/2025 | [Caio Duarte](https://github.com/caioduart3) |
| 1.0    | Adiciona documentação | [Caio Duarte](https://github.com/caioduart3)  | 26/11/2025 | [Laryssa Felix](https://github.com/felixlaryssa) |

