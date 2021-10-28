#include <stdio.h>
void heapsort(int v[], int n);
void build_max_heap(int v[], int n);
void max_heapify(int v[], int i, int n);
void troca(int v[], int a, int b);
void print_array(int v[], int a, int b);

void main() {
    int v[100] = {15, 35, 40, 10, 20, 5, 45, 70, 25, 90};
    heapsort(v, 10);
    print_array(v, 0, 9);
}

/* As diminuições de -1 ocorrem por conta dos arrays em c começarem da posição 0 e não 1 */
void heapsort(int v[], int n) {
    build_max_heap(v, 10);
    for (int i = n; i >= 1; i--) { // no pseudo código, o i vai até i >= 2, porem aqui colocamos até o 1 por conta dos arrays começarem em 0.
        troca(v, 0, i-1);
        n--;
        max_heapify(v, 0, n-1);
    }
}

void build_max_heap(int v[], int n) {
    for (int i = n/2; i >= 1; i--) 
        max_heapify(v, i-1, n);
}


void max_heapify(int v[], int i, int n) {
    int esq, dir, maior;
    esq = (i*2)+1;
    dir = (i*2)+2;
    if (esq <= n && v[esq] > v[i]) maior = esq;
    else maior = i;
    if (dir <= n && v[dir] > v[maior]) maior = dir;
    if (maior != i) {
        troca(v, i, maior);
        max_heapify(v, maior, n);
    }
}

void troca(int v[], int a, int b) {
  int aux = v[a];
  v[a] = v[b];
  v[b] = aux;
}
void print_array(int v[], int a, int b) {
    for(int i = a; i <= b; i++) 
        printf("%d ", v[i]);
    printf("\n");
}
