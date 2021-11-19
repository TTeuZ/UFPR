#include <stdio.h>
void vetores_binarios(int set[], int vetor[], int vetor_length, int pos);
void print_array(int set[], int v[], int a, int b);
void todos_subconjuntos(int set[], int n);

void main() {
    int set[] = {23, 10, 20, 11, 12, 6, 7};
    int size = sizeof(set)/sizeof(set[0]);

    todos_subconjuntos(set, size);
}

void vetores_binarios(int set[], int vetor[], int vetor_length, int pos) {
    if (pos == vetor_length) {
        print_array(set, vetor, 0, vetor_length - 1);
        return;
    }
    vetor[pos] = 0;
    vetores_binarios(set, vetor, vetor_length, pos+1);
    vetor[pos] = 1;
    vetores_binarios(set, vetor, vetor_length, pos+1);
}

void todos_subconjuntos(int set[], int n) {
    int vetor[n];
    vetores_binarios(set, vetor, n, 0);

}

void print_array(int set[], int v[], int a, int b) {
    for(int i = a; i <= b; i++) {
        if (v[i])
            printf("%d ", set[i]);
    }
    printf("\n");
}