#include <stdio.h>
int f(int n, int r, int a);
void main(int argc, char *argv[]) {
    printf("resultado: %d \n", f(4, 3, 2));
}

int f(int n, int r, int a) {
    if (n == 1) return a;
    return f(n-1, r, a) + r*(n-1) + a;
}