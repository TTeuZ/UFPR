#include <stdio.h>
int search(int x,int v[], int a, int b);
void main (int argc, char *argv[]) {
    int v[10] = {20, 32, 31, 10, 6, 9};
    printf("achado: %d\n", search(10, v, 0, 5));
}

int search(int x,int v[], int a, int b) {
    if (a > b) return a-1;
    if (x >= v[b]) return b;
    return search(x, v, a, b-1);
}

// Analise do circuito no pdf a05.
//  Analise é a mesma do ultima busca.