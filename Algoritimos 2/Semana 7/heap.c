#include <stdio.h>

#define MAX 100

int pai(int i) {
    return (i-1)/2;
}
int esquerda(int i) {
    return 2*i + 1;
}
int direita(int i) {
    return 2*i + 2;
}
void troca(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void max_heapify(int v[], int i, int n) {
    int maior, esq, dir;
    esq = esquerda(i);
    dir = direita(i);

    if (esq < n && v[esq] > v[i]) maior = esq;
    else maior = i;

    if (dir < n && v[dir] > v[maior]) maior = dir;

    if (maior != i) {
        troca(&v[i], &v[maior]);
        max_heapify(v, i+1, n);
    }
}

void buildmaxheap(int v[], int n) {
    for (int i = n/2 - 1; i >= 0; i--) {
        max_heapify(v,i,n);
    }
}

void print_array(int v[], int a, int b) {
    for(int i = a; i < b; i++) 
        printf("%d ", v[i]);
    printf("\n");
}

void main() {
    int n;
    int v[MAX];

    printf("Digite o tamanho do heap\n");
    scanf("%d", &n);
    
    printf("Digite os valores\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
    buildmaxheap(v, n);
    print_array(v, 0, n);
}