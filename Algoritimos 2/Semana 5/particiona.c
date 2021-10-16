#include <stdio.h>
int particiona(int v[], int a, int b, int pivo);
void print_array(int v[], int a, int b);

void main(int argc, char *argv[]) {
    int v[10] = {7, 58, 31, 92, 3, 10};
    int m = particiona(v, 0, 5, 10);
    print_array(v, 0, 5);
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

// So funciona se o pivo for o ultimo elemento do vetor
// Executando o particiona, o pivo fica na posição correta caso o array fosse ordenado.