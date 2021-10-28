#include <stdio.h>
int f(int v[], int a, int b);
int soma(int v[], int a, int b);

void main() {
    int v[10] = {10, 20, 20, 1, 4};
    int media;
    media = f(v, 0, 4);
    printf("media é: %d\n", media);
}

int f(int v[], int a, int b) {
    return soma(v, a, b) / (b - a + 1);
}

int soma(int v[], int a, int b) {
    if (b == a) return v[b];
    return v[b] + soma(v, a, b-1);
}

