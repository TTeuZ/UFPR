#include <stdio.h>
int f(int n);

void main() {
    printf("Numero de 1's: %d\n", f(8));
}

int f(int n) {
    if (n <= 1) return 1;
    return n%2 + f(n/2);
}