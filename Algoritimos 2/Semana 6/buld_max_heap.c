#include <stdio.h>
void build_max_heap(int v[], int n);
void max_heapify(int v[], int i, int n);
void troca(int v[], int a, int b);
void print_array(int v[], int a, int b);

void main() {
    int v[100] = {15, 35, 40, 10, 20, 5, 45, 70, 25, 90};
    build_max_heap(v, 10);
    print_array(v, 0, 9);
}

/* Pelo fato de que no C os arrays começão na posição zero, temo sque mandar o i-1 na chamada do max_heapify */
void build_max_heap(int v[], int n) {
    for (int i = n/2; i >= 1; i--) 
        max_heapify(v, i-1, n);
}

/* Para o algoritimo funcionar, tive que alterar os vaores de esquerda e direita (somando + 1), pois em C os arrays começão na pozição 0 */
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
