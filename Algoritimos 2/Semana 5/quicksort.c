#include <stdio.h>
void quicksort(int v[], int a, int b);
int particiona(int v[], int a, int b, int pivo);
void print_array(int v[], int a, int b);

void main(int argc, char *argv[]) {
    int v[10] = {7, 58, 31, 92, 3, 10};
    quicksort(v, 0, 5);
    print_array(v, 0, 5);
}

void quicksort(int v[], int a, int b) {
    if (a >= b) return;
    int m = particiona(v, a, b, v[b]);
    quicksort(v, a, m-1);
    quicksort(v, m+1, b);
}

int particiona(int v[], int a, int b, int pivo) {
    int m = a - 1;
    for(int i = a; i <= b; i++) {
        if (v[i] <= pivo) {
            m += 1;
            int x = v[m];
            v[m] = v[i];
            v[i] = x;
        }
    }
    return m;
}

void print_array(int v[], int a, int b) {
    for(int i = a; i <= b; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}
