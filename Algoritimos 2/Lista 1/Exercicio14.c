#include <stdio.h>
int *invert(int v[], int a, int b);

void main (int argc, char *argv[]) {
    int v[10] = {10, 2, 34};
    int *v_invertido = invert(v, 0, 2);
    for (int i = 0; i <= 4; i++) {
        printf("%d ", v_invertido[i]);
    }
    printf("\n");
}

int *invert(int v[], int a, int b) {
    if (a == b) return v;
    invert(v, a+1, b-1);
    int begin = v[a];
    int end = v[b];
    v[a] = end;
    printf("troca 1");
    v[b] = begin;
    printf("troca 2");
    return v;
}