#include <stdio.h>
int min(int v[], int a, int b);

void main(int argc, char *argv[]) {
    int v[100], a, b;
    printf("Número posição inicial: \n");
    scanf("%d", &a);
    printf("Número posição final: \n");
    scanf("%d", &b);
    printf("Elementos: \n");
    for (int i = a; i <= b; ++i)
        scanf("%d", &v[i]);
    printf("minimo: %d \n", v[min(v, a, b)]);
}

int min(int v[], int a, int b) {
    if (a == b) return a;
    int m = min(v, a, b-1);
    if (v[b] < v[m]) m = b;
    return m;
}