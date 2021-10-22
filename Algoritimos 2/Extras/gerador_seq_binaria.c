#include <stdio.h>
void f(int vetor[], int vetor_length, int enpty_pos);
void print_array(int v[], int a, int b);

void main() {
    int vetor[100], n;
    printf("Digite o tamanho da seguencia de BITS: \n");
    scanf("%d", &n);
    f(vetor, n, 0);
}

void f(int vetor[], int vetor_length, int enpty_pos) {
    if (enpty_pos == vetor_length) return print_array(vetor, 0, vetor_length - 1);
    vetor[enpty_pos] = 0;
    f(vetor, vetor_length, enpty_pos+1);
    vetor[enpty_pos] = 1;
    f(vetor, vetor_length, enpty_pos+1);
}

void print_array(int v[], int a, int b) {
    for(int i = a; i <= b; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}