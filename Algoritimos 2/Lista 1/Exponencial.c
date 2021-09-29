#include <stdio.h>
#include <stdlib.h>
// f(x, y) = x*f(x, y-1)
int exponencial(int x, int y) {
    if (y == 0) return 1;
    return x * exponencial(x, y-1);
}
void main(int argc, char *argv[]) {
    int x = 2;
    int y = 4;
    printf("%d \n", exponencial(atoi(argv[1]), atoi(argv[2])));
}

// ./exp 2 4 --> 16

/* Caso devolvendo 1 na base
seja m(n) o numero de multiplicações efetuadas pelo algoritimo.
n = y;

m(n) = { 1, se n = 0; 1 + m(n-1), se n > 0 }

m(n) = 1 + m(n-1) --> 1 + 1 + m(n-2) --> 1 + 1 + 1 + m(n-3) --> i + m(n-i)

o algoritimo é finalizado em n - i = 0 --> n = i

n + m(n-n) --> n + m(o) --> n + 1
*/

/* Caso devolvendo 0 na base
seja m(n) o numero de multiplicações efetuadas pelo algoritimo.
n = y;

m(n) = { 0, se n = 0; 1 + m(n-1), se n > 0 }

m(n) = 1 + m(n-1) --> 1 + 1 + m(n-2) --> 1 + 1 + 1 + m(n-3) --> i + m(n-i)

o algoritimo é finalizado em n - i = 0 --> n = i

n + m(n-n) --> n + m(o) --> n + 0 --> n
*/

/* 
Se eu devolver 0 na base o negócio ta certo, mas não sei se pode isso.
Mas se for seguir a logica de se no caso base eu não entro em nenhuma 
multiplicação e por isso retorna 0 então da boa.
*/