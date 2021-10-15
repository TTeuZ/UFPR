#include <stdio.h>
int exercicio(int a, int b);

void main (int argc, char *argv[]) {
    printf("3 elevado a 3: %d \n", exercicio(3, 3));
    printf("2 elevado a 4: %d \n", exercicio(2, 4));
}

int exercicio(int a, int b) {
    if (b == 0) return 1;
    if (b % 2 == 0) return exercicio(a*a, b/2);
    return exercicio(a*a, b/2)*a;
}

/*
A função f(n) retorna: a^n;

Formula de recorrencia:

f(a, b) = { 0 ,se b=0; f(a^2, b/2) ,se b é par|b > 0; f(a^2, b/2)*a ,se b é impar }

ERRADOOOOOOOOOOO

O certo esta na folha da aula do dia 15/10/2021.
*/