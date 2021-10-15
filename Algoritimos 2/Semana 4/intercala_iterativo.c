#include <stdio.h>
int *intercala(int v[], int a, int m, int b);

void main(int argc, char *argv[]) {
    int v[100] = {5, 9, 10, 2, 3, 4};
    int *vetor_ordenado = intercala(v, 0, 2, 5);
    for (int i = 0; i < 6; i++) {
        printf("%d ", vetor_ordenado[i]);
    }
    printf("\n");
}

int *intercala(int v[], int a, int m, int b) {
    if (a >= b) return v;
    int u[100];
    int i = a;
    int j = m + 1;
    for (int k = a; k <= b; k++) {
        if (j>b || (i<=m && v[i] <= v[j])) {
            u[k] = v[i];
            i += 1;
        } else {
            u[k] = v[j];
            j += 1;
        }
    }
    for (int p = a; p <= b; p++) {
        v[p] = u[p];
    }
    return v;
}