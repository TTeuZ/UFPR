#include <stdio.h>
int busca(int x, int v[], int a, int b);

void main() {
    int v[10]={9,2,23,10,3};
    printf("Posição de 10: %d\n", busca(10, v, 0, 4));
}

int busca(int x, int v[], int a, int b) {
    if (a >= b) return -1;
    int m = (a+b)/2;
    if (x == v[m]) return m;
    int r = busca(x, v, a, m-1);
    if (r != -1) return r;
    return busca(x, v, m+1, b);
}