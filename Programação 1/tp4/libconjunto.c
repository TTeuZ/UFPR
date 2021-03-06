#include <stdio.h>
#include <stdlib.h>
#include "libconjunto.h"

/* Funções internas */

/* Busca iterativa o elemento x dentro do conjunto. */
/* Retorna 1 se o elemento foi encontrado e 0 caso ele não esteja no conjunto */
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

/* Busca para encontrar a posição que o valor indicado deveria estar no vetor, */
/* para que ele se mantenha ordenado e retorna esta posição. */
int find_pos (int x, conjunto_t *c) {
    int iterator = 0;
    /* Procura até encontrar o primeiro elemento do conjunto maior que o buscado */
    while (iterator < c->card) {
        if (x < *(c->v+iterator)) return iterator;
        iterator++;
    }
    /* Se não tiver um maior, retorna a ultima posiçõa do conjunto */
    return c->card;
}

/* Insere o elemento x no conjunto, de maneira a manter ele ordenado. */
void sort_insertion(int x, conjunto_t *c) {
    int pos, count;
    /* busca a posição que o elemento deveria estar no conjunto */
    pos = find_pos(x, c);
    /* Faz a inserção de maneira a manter o conjunto ordenado */
    for (count = c->card-1; count >= pos; count--) {
        *(c->v+count+1) = *(c->v+count);
    }
    *(c->v+pos) = x;
}

/* Remove o elemento x no conjunto, de maneira a manter ele ordenado. */
void sort_remove(int x, conjunto_t *c) {
    int pos, count;
    /* busca a posição que o elemento no conjunto */
    pos = find_pos(x, c);
    /* Faz a remoção de maneira a manter o conjunto ordenado */
    for (count = pos; count <= c->card; count++) {
        *(c->v+count-1) = *(c->v+count);
    }
}

/* Retorna o maior conjunto dentre os enviados. */
conjunto_t * bigger_conj (conjunto_t *c1, conjunto_t *c2) {
    if (c1->card > c2->card) return c1;
    else return c2;
}

/* Retorna o menor conjunto dentre os enviados. */
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
    /* Testa o malloc para toda a estrutura do conjunto e inicia as variaveis */
    if ((conj = malloc(sizeof(conjunto_t)))) {
        conj->max = max;
        conj->card = 0;
        /* Testa o malloc para o vetor do conjunto */
        /* Em caso de falha livra o espaço posteriormente alocado e retorna 0 */
        if ((conj->v = (int*) malloc(sizeof(int)*(max+1))))
            return conj;
        else {
            free (conj);
            return 0;
        }
    } else return 0;
}

/* Libera os espaços alocados par ao conujnto. */
void destroi_conjunto (conjunto_t *c) {
    free (c->v);
    free (c);
}

/* Testa se o c1 esta contido no c2*/
int contido (conjunto_t *c1, conjunto_t *c2) {
    int count;
    /* se c1 for maior que c2 ele não tem como estar contido */
    if (c1->card > c2->card) return 0;
    else {
        /* verifica se cada elemento de c1 esta em c2 */
        for (count = 0; count < c1->card; count++) 
            if (!busca_binaria(*(c1->v+count), c2)) return 0;
        return 1;
    }
}

/* Retorna a cardinalidade do conjunto */
int cardinalidade (conjunto_t *c) {
    return c->card;
}

/* Retorna se o conjunto eh vazio */
int eh_vazio (conjunto_t *c) {
    if (c->card == 0) return 1;
    else return 0;
}

/* Retorna se o elemento pertence ao conjunto */
int pertence (int n, conjunto_t *c) {
    if (!busca_binaria(n, c)) return 0;
    else return 1;
}

/* Como essa lib trabalha sempre deixando o conujnto ordenado, */
/* para testar se são iguais basta verificar a igualdade de cada posição equivalente */
int sao_iguais (conjunto_t *c1, conjunto_t *c2) {
    int count;
    /* Verifica se os conjuntos tem mesma cardinalidade */
    if (c1->card != c2->card) return 0;
    else {
        /* verifica se cada posição tem o mesmo valor */
        for (count = 0; count < c1->card; count++) 
            if (!(*(c1->v+count) == *(c2->v+count))) return 0;
        return 1;
    }
}

/* O max do conjunto nunca passa do max do c1 */
conjunto_t * cria_diferenca (conjunto_t *c1, conjunto_t *c2) {
    conjunto_t *conj;
    int count;

    /* Verifica se a criação do conjunto para a diferença ocorreu corretamente */
    if ((conj = cria_conjunto (c1->max)) != 0) {
        /* Passa por cada elemento do c1 */
        for (count = 0; count < c1->card; count++) {
            /* insere ele no conjunto de diferença caso ele não esteja em c2 */
            if (!busca_binaria(*(c1->v+count), c2)) 
                insere(*(c1->v+count), conj);
        }
        return conj;
    } else return 0;
}

/* O max do conjunto nunca passa do max do menor conjunto. */
conjunto_t * cria_interseccao (conjunto_t *c1, conjunto_t *c2) {
    conjunto_t *conj, *l_conj, *b_conj;
    int count;
    /* verificamos qual é o maior e menor conjunto dos parametros */
    b_conj = bigger_conj(c1, c2);
    l_conj = lower_conj(c1, c2);

    /* Verifica se a criação do conjunto para a diferença ocorreu corretamente */
    if ((conj = cria_conjunto (l_conj->max)) != 0) {
        /* Passa por cada elemento do menor conjunto */
        for (count = 0; count < l_conj->card; count++) {
            /* insere ele no conjunto de interseccao caso ele esteja no maior conjunto */
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
    /* O max do conujnto de união pode ser no maximo a soma do maximo dos dois demais conjuntos */
    max = (c1->max)+(c2->max);
    /* verificamos qual é o maior e menor conjunto dos parametros */
    b_conj = bigger_conj(c1, c2);
    l_conj = lower_conj(c1, c2);

    /* Verifica se a criação do conjunto para a diferença ocorreu corretamente */
    if ((conj = cria_conjunto (max)) != 0) {
        /* Inicia um for que vai até o ultimo elemento do maior conjunto */
        for (count = 0; count < b_conj->card; count++) {
            /* Verifica se o contador ja passou do tamanho do menor conjunto */
            if (count < l_conj->card)
                /* insere o elemento da vez no conjunto união ** regras do insere aplicadas ** */
                insere(*(l_conj->v+count), conj);
            /* Verifica se o contador ja passou do tamanho do maior conjunto */
            if (count < b_conj->card)
                /* insere o elemento da vez no conjunto união ** regras do insere aplicadas ** */
                insere(*(b_conj->v+count), conj);
        }
        return conj;
    } else return 0;
}

/* Insere o elemento no conjunto caso ele ja não exista. */
int insere (int n, conjunto_t *c) {
    /* Verifica se o elemento ja esta no conjunto */
    if (!busca_binaria (n, c)) {
        /* verifica se adicionarmor o elemento a tamanho maximo do conjunto nao sera excedido*/
        if (c->card + 1 > c->max) return -1;
        else {
           /* insere o elemento */
           sort_insertion (n, c); 
           c->card++;
           return 1;
        }
    } else return 0;
}

/* remove o elemento do conjunto mantendo a ornedacao */
int retira (int n, conjunto_t *c) {
    /* verifica se o elemento existe no conjunto */
    if (busca_binaria (n, c) == 1) {
        sort_remove (n, c); 
        c->card--;
        return 1;
    } else return 0;
}

/* imprime o conjunto */
void imprime (conjunto_t *c) {
    int count;
    for (count = 0; count < c->card; count++) 
        printf(" %d ", *(c->v+count));
    printf("\n");
}
/* Funções publicas */