#include <stdio.h>
int f(int v[], int a, int u[], int p, int l, int d);

void main() {
    int v[10] = {0, 0, 10, 2, 3, 4, 1};
    int u[10] = {10, 2, 3, 4, 1};
    printf("valor: %d\n", f(v, 2, u, 0, 4, 0));
}

int f(int v[], int a, int u[], int p, int l, int d) {
    if (a+d == a+l) return l + 1;
    if (v[a+d] != u[p+d]) return a;
    else return f(v, a, u, p, l, d+1);
}