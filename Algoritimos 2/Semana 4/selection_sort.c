#include <stdio.h>
int *selection_sort(int v[], int a, int b);
int min(int v[], int a, int b);

void main(int argc, char *argv[]) {
    int v[10] = {20, 32, 31, 10, 6, 9};
    int *v_ordenado = selection_sort(v, 0, 5);
    for (int i = 0; i <= 5; i++) {
        printf("%d\n", v_ordenado[i]);
    }
}

int *selection_sort(int v[], int a, int b) {
    if ( a >= b ) return v;
    int x = v[a];
    v[a] = min(v, a, b);
    v[b] = x;
    return selection_sort(v, a+1, b);
}

int min(int v[], int a, int b) {
    if (a == b) return a;
    int m = min(v, a, b-1);
    if (v[b] < v[m]) m = b;
    return m;
}

// Não está funcional.