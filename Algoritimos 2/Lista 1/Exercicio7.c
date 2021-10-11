#include <stdio.h>
int f(int n, int a, int r);

void main(int argc, char *argv[]) {
    printf("Resultado: %d\n", f(3, 3, 3));
}

int f(int n, int a, int r) {
    if (n == 1) return a;
    return f(n-1, a, r) + r;
}