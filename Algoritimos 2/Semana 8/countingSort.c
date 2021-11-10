#include <stdio.h>
/* Todos os elementos do vetor estão entre dois limites, ou seja, não saõ menores que um valor e não são maiores que o limite */
void countingSort_iterativo(int v[], int max, int lim_inf, int lim_sup);
void print_array(int v[], int a, int b);

void main () {
    int v[10] = {0, 4, 3, 1, 4, 2, 2, 5, 6, 1};
    countingSort_iterativo(v, 9, 0, 6);
    print_array(v, 0, 9);
}

void countingSort_iterativo(int v[], int max, int lim_inf, int lim_sup) {
    int temp[lim_sup], saida[max+1];
    int count;
    for (count = 0; count < lim_sup; count++) 
        temp[count] = 0;
    for (count = 0; count <= max; count++) 
        temp[v[count]] = temp[v[count]] + 1;
    for (count = 1; count <= lim_sup; count++) 
        temp[count] = temp[count] + temp[count - 1];
    for (count = max; count >= 0; count--) {
        saida[temp[v[count]]] = v[count];
        temp[v[count]] = temp[v[count]] - 1;
    }
    for (count = 0; count <= max; count++) 
        v[count] = saida[count];
}

void print_array(int v[], int a, int b) {
    for(int i = a; i <= b; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

/* ta dando um erro, averiguar depois. */