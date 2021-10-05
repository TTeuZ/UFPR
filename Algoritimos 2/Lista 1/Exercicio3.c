#include <stdio.h>
int fibonacci (int number);

void main (int argc, char *argv[]) {
    printf("seguencia de Fibonacci até a 10 casa: \n");
    for (int n; n <= 10; ++n) {
        printf("%d \n", fibonacci(n));
    }
}

int fibonacci (int number) {
    if (number <= 1) return number;
    return fibonacci(number - 1) + fibonacci(number - 2);
}

/*
seja s(n) o numero de somas efetuadas pelo algoritimo.
n = number 

s(n) = { 0, se n <= 1; 1 + s(n-1) + s(n-2) }

Seja r(n) o número de chamadas recursivas efetuadas pelo seu algoritimo. Expresse r(n) como uma recorrencia.

r(n) = {0, se n <= 1, 2 + (s(n-1) + s(n-2))}
*/
