#include <stdio.h>
int f(int v[], int a, int b);

void main(int argc, char *argv[]) {
    int v[10] = {4, 3, 2, 5, 6, 10};
    printf("Resultdado: %d\n", f(v, 0, 5));
}

int f(int v[], int a, int b) {
    if (a == b) return a;
    int m = f(v, a+1, b);
    if (v[a] < v[m]) m = a;
    return m;
}