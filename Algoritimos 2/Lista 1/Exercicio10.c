#include <stdio.h>
int f(int a, int b);

void main (int argc, char *argv[]) {
    printf("Resultado: %d\n", f(3, 3));
}

int f(int a, int b) {
    if (b == 0) return 0;
    if (b % 2 == 0) return f(a+a, b/2);
    return f(a+a,b/2) + a;
}