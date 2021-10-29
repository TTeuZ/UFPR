#include <stdio.h>
int f(int v[], int a, int b);

void main() {
    int v[10] = {10, 2, 40, 23, 43, 12};
    printf("Valor minimo: %d\n", v[f(v, 0, 5)]);
}

int f(int v[], int a, int b) {
    if (a == b) return a;
    int m = (a+b)/2;
    int m1 = f(v, a, m);
    int m2 = f(v, m+1, b);
    if (v[m1] <= v[m2]) return m1;
    else return m2;
}