#include <stdio.h>

int busca_binaria(int x, int [], int a, int b) {
    if (a > b) return "NÃO";
    int m = (a + b) / 2;
    if (x = v[m]) return m;
    if x < v[m] return busca_binaria(x, v, a, m-1);
    return busca_binaria(x, v, m+1, b);
}