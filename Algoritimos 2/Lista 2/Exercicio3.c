#include <stdio.h>
void fatores(int n, int pivo);
void fatores_iterativo(int n, int pivo);

void main() {
    fatores(16, 1);
    printf("\n");
    fatores_iterativo(16, 1);
    printf("\n");
}
void fatores(int n, int pivo) {
    if (pivo > n) return;
    if (n % pivo == 0) printf(" %d ", pivo);
    fatores(n, pivo+1);
}

void fatores_iterativo(int n, int pivo) {
    while (pivo <= n) {
        if (n % pivo == 0) printf(" %d ", pivo);
        pivo++;
    }
}