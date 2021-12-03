#include <stdio.h>

void imprime_vetor(int v[], int a) {
    for(int i = 0; i < a; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

// gera todas strings bin ́arias
void backtrack(int v[], int n, int i) {
    if (i == n) {
        imprime_vetor(v, n);
        return;
    }
    v[i] = 0;
    backtrack(v, n, i + 1);
    v[i] = 1;
    backtrack(v, n, i + 1);
    v[i] = 2;
    backtrack(v, n, i + 1);
}

void main() {
    int vetor[100], n;
    n = 3;
    backtrack(vetor, n, 0);
}