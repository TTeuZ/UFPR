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