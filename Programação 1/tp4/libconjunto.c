#include <stdio.h>
#include <stdlib.h>
#include "libconjunto.h"

/* Funções internas */

/* Busca iterativa o elemento x dentro do conjunto.
Retorna 1 se o elemento foi encontrado e 0 caso ele não esteja no conjunto */
int busca_binaria(int x, conjunto_t *c) {
    int begin, end, iterator;
    begin = 0;
    end = c->card;
    while (end > begin) {
        iterator = (begin + end) / 2;
        if (*(c->v+iterator) == x) return 1;
        if (*(c->v+iterator) < x) begin = iterator + 1;
        else end = iterator;
    }
    return 0;
}

/* Busca para encontrar a posição que o valor indicado deveria estar no vetor,
para que ele se mantenha ordenado e retorna esta posição.*/
int find_pos (int x, conjunto_t *c) {
    int iterator = 0;
    while (iterator < c->card) {
        if (x < *(c->v+iterator)) return iterator;
        iterator++;
    }
    return c->card;
}

/* Insere o elemento x no conjunto, de maneira a manter ele ordenado.
*/
void sort_insertion(int x, conjunto_t *c) {
    int pos, count;
    pos = find_pos(x, c);
    for (count = c->card-1; count >= pos; count--) {
        *(c->v+count+1) = *(c->v+count);
    }
    *(c->v+pos) = x;
}

void sort_remove(int x, conjunto_t *c) {
    int pos, count;
    pos = find_pos(x, c);
    for (count = pos; count <= c->card; count++) {
        *(c->v+count-1) = *(c->v+count);
    }
}

/* Funções internas */

/* Funções publicas */

/* A utilização do (max+1) nos mallocs veio por conta de um erro encontrado pelo valgrind
De 'invalid write of size 4' */
conjunto_t * cria_conjunto(int max) {
    conjunto_t *conj;
    if ((conj = malloc(sizeof(conjunto_t)*(max+1)))) {
        conj->max = max;
        conj->card = 0;
        conj->v = (int*) malloc(sizeof(int)*(max+1));
        return conj;
    } else return 0;
}

void destroi_conjunto (conjunto_t *c) {
    free (c->v);
    free (c);
}

int cardinalidade (conjunto_t *c) {
    return c->card;
}

int eh_vazio (conjunto_t *c) {
    if (c->card == 0) return 1;
    else return 0;
}

int insere (int n, conjunto_t *c) {
    if (!busca_binaria (n, c)) {
        if (c->card + 1 > c->max) return -1;
        else {
           sort_insertion (n, c); 
           c->card++;
           return 1;
        }
    } else return 0;
}

int retira (int n, conjunto_t *c) {
    if (busca_binaria (n, c) == 1) {
        sort_remove (n, c); 
        c->card--;
        return 1;
    } else return 0;
}

void imprime (conjunto_t *c) {
    int count;
    for (count = 0; count < c->card; count++) 
        printf(" %d ", *(c->v+count));
    printf("\n");
}
/* Funções publicas */