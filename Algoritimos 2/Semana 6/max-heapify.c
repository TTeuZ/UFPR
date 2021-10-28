#include <stdio.h>
void max_heapify(int v[], int i, int n);
void troca(int v[], int a, int b);

void max_heapify(int v[], int i, int n) {
    int esq, dir, maior;
    esq = i*2; // encontra o nodo da esquerda do heap
    dir = (i*2)+1; // encontra o nodo da direita do heap

    /* verifica se o valor do nodo da esquerda esta dentro do array do heap e e ele é maior que o nodo raiz da atual execução */
    if (esq <= n && v[esq] > v[i]) maior = esq;
    else maior = i;

    /* verifica se o valor do nodo da direita esta dentro do array do heap e e ele é maior que o maior nodo encontrado até o momento */
    if (dir <= n && v[dir] > v[maior]) maior = dir;

     /* verifica se o valor do maior nodo é iqual ao atual nodo raiz, caso não, troca os
      valores dos nodos e chama recursivamente o max-heapify para verificaar se o nodo modificado respeita a regra. */
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