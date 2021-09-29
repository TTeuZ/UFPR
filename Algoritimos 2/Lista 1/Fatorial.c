#include <stdio.h>
// f(x) = x * f(x-1)
int fatorial (int x) {
    if (x == 0) return 1;
    return x * fatorial(x - 1);
}
void main (int argc, char **argv) {
    int x = 10;
    printf("%d \n", fatorial(x));
}

/*Caso devolvendo 1 na base
Seja m(n) o numero de multiplicaçoes realizadas pelo algoritimo.
n = x

m(n) = { 1, se n = 0; 1 + m(n-1), se n > 0 }

m(n) = 1 + m(n-1) --> 1 + 1 + m(n-2) --> 1 + 1 + 1 + m(n-3) --> i + m(n-i)

o algoritimo é finalizado em n - i = 0 --> n = i

n + m(n-n) --> n + m(o) --> n + 1
*/

/*Caso devolvendo 0 na base
Seja m(n) o numero de multiplicaçoes realizadas pelo algoritimo.
n = x

m(n) = { 0, se n = 0; 1 + m(n-1), se n > 0 }

m(n) = 1 + m(n-1) --> 1 + 1 + m(n-2) --> 1 + 1 + 1 + m(n-3) --> i + m(n-i)

o algoritimo é finalizado em n - i = 0 --> n = i

n + m(n-n) --> n + m(o) --> n + 0 --> n
*/