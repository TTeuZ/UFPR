#include <stdio.h>
int mcCarthy (int n);

void main (int argc, char *argv[]) {
    printf("mcCarthy: %d \n", mcCarthy(2));
}

int mcCarthy (int n) {
    if (n > 100) return n - 10;
    else return mcCarthy(mcCarthy(n + 11));
}

/*
f(n)
Se n > 100
    Devolva n − 10
Devolva F(F(n + 11))
f(n) -> para qualquer numero menor do que 100 ele retorna 91.
f(n) -> para qualquer numero maior do que 100 ele retorna decrescido de 10.
Função de recorrencia:

f(n) = {n - 10,  se n > 100; f(f(n + 11)) se n <= 100 }
*/