#include <stdio.h>

void imprime_vetor(int v[], int a) {
    for(int i = 0; i < a; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

// gera todas strings bin ́arias
void backtrack(int v[], int n, int i, int k) {
    int count;
    if (i == n) {
        imprime_vetor(v, n);
        return;
    }
    for (count = 0; count <= k; count++) {
        v[i] = count;
        backtrack(v, n, i + 1, k);
    }
}

void main() {
    int vetor[100], n;
    n = 3;
    backtrack(vetor, n, 0, 4);
}