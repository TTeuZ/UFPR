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

conjunto_t * bigger_conj (conjunto_t *c1, conjunto_t *c2) {
    if (c1->card > c2->card) return c1;
    else return c2;
}

conjunto_t * lower_conj (conjunto_t *c1, conjunto_t *c2) {
    if (c1->card < c2->card) return c1;
    else return c2;
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

int contido (conjunto_t *c1, conjunto_t *c2) {
    int count;
    if (c1->card > c2->card) return 0;
    else {
        for (count = 0; count < c1->card; count++) 
            if (!busca_binaria(*(c1->v+count), c2)) return 0;
        return 1;
    }
}

int cardinalidade (conjunto_t *c) {
    return c->card;
}

int eh_vazio (conjunto_t *c) {
    if (c->card == 0) return 1;
    else return 0;
}

int pertence (int n, conjunto_t *c) {
    if (!busca_binaria(n, c)) return 0;
    else return 1;
}

/* Como essa lib trabalha sempre deixando o conujnto ordenado, para testar se são iguais
basta verificar a igualdade de cada posição equivalente */
int sao_iguais (conjunto_t *c1, conjunto_t *c2) {
    int count;
    if (c1->card != c2->card) return 0;
    else {
        for (count = 0; count < c1->card; count++) 
            if (!(*(c1->v+count) == *(c2->v+count))) return 0;
        return 1;
    }
}

/* O max do conjunto nunca passa do max do c1 */
conjunto_t * cria_diferenca (conjunto_t *c1, conjunto_t *c2) {
    conjunto_t *conj;
    int count;

    if ((conj = cria_conjunto (c1->max))) {
        for (count = 0; count < c1->card; count++) {
            if (!busca_binaria(*(c1->v+count), c2)) 
                insere(*(c1->v+count), conj);
        }
        return conj;
    } else return 0;
}

/* O max do conjunto nunca passa do max do maior conjunto. */
conjunto_t * cria_interseccao (conjunto_t *c1, conjunto_t *c2) {
    conjunto_t *conj, *l_conj, *b_conj;
    int count;
    b_conj = bigger_conj(c1, c2);
    l_conj = lower_conj(c1, c2);

    if ((conj = cria_conjunto (b_conj->max))) {
        for (count = 0; count < l_conj->card; count++) {
            if (busca_binaria(*(l_conj->v+count), b_conj) == 1) 
                insere(*(l_conj->v+count), conj);
            }
        return conj;
    } else return 0;
}

/* O max do conjunto é equivalente a soma dos maximos de embos os conjuntos */
conjunto_t * cria_uniao (conjunto_t *c1, conjunto_t *c2) {
    conjunto_t *conj, *l_conj, *b_conj;
    int count, max;
    max = (c1->max)+(c2->max);
    b_conj = bigger_conj(c1, c2);
    l_conj = lower_conj(c1, c2);

    if ((conj = cria_conjunto (max))) {
        for (count = 0; count < b_conj->card; count++) {
            if (count < l_conj->card)
                insere(*(l_conj->v+count), conj);
            if (count < b_conj->card)
                insere(*(b_conj->v+count), conj);
        }
        return conj;
    } else return 0;
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