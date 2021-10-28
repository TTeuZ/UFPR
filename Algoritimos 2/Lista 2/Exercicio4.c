#include <stdio.h>
int exponencial(int x, int y);
int polinomio(int v[], int a, int b, int x);

void main() {
    int vetor[10] = {1, 2, 3};
    printf("Valor: %d\n", polinomio(vetor, 0, 2, 2));
}

int exponencial(int x, int y) {
    if (y == 0) return 1;
    return x * exponencial(x, y-1);
}

int polinomio(int v[], int a, int b, int x) {
    if (a == b+1) return 0;
    return v[a]*exponencial(x,a) + polinomio(v, a+1, b, x);
}