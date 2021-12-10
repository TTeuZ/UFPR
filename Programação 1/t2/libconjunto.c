#include <stdio.h>
#include <stdlib.h>
#include "libconjunto.h"

/* Funções internas */
/* Busca iterativa o elemento x dentro do conjunto. */
/* Retorna a posição do elemento se ele foi encontrado e -1 caso ele não esteja no conjunto */
int busca_binaria (conjunto_t *c, int x) {
    int begin, end, iterator;
    begin = 0;
    end = c->card;
    while (end > begin) {
        iterator = (begin + end) / 2;
        if (*(c->v+iterator) == x) return iterator;
        if (*(c->v+iterator) < x) begin = iterator + 1;
        else end = iterator;
    }
    return -1;
}

/* Caso o array esteja vazio, insere no primeiro espaço */
/* Enquanto o valor da posição foi maior que o elemento empurra as valores uma 'casa' para frente */
/* Insere o elemento na poisção correta, mantendo ordenado */
void sorted_insertion (int x, conjunto_t *c) {
    int count = c->card;

    if (c->card == 0) 
        *(c->v+c->card) = x;
    else {
        while (count != 0 && x <= *(c->v+count-1)) {
            *(c->v+count) = *(c->v+count-1);
            count--;
        }
        *(c->v+count) = x;
    }
}
/* Funções internas */

/* Funções publicas */
/* Testa o malloc para o vetor do conjunto */
/* Em caso de falha livra o espaço posteriormente alocado e retorna 0 */
conjunto_t * cria_conjunto (int max) {
    conjunto_t *conj;
    if ((conj = malloc (sizeof(conjunto_t)))) {
        conj->max = max;
        conj->card = 0;

        if ((conj->v = (int*) malloc (sizeof(int)*(max+1))))
            return conj;
        else {
            free (conj);
            return NULL;
        }
    } else return NULL;
}

/* Libera os espaços alocados para o conjunto. */
conjunto_t * destroi_conjunto (conjunto_t *c) {
    int count;
    for (count = 0; count < c->card; count++) {
        retira_conjunto (c, *(c->v+count));
    }
    free (c->v);
    free (c);
    return NULL;
}

/* Retorna se o conjunto eh vazio */
int conjunto_vazio (conjunto_t *c) {
    return c->card == 0;
}

/* Retorna a cardinalidade do conjunto */
int cardinalidade (conjunto_t *c) {
    return c->card;
}

/* Insere o elemento no conjunto caso ele ja não exista. */
/* verifica se adicionarmor o elemento a tamanho maximo do conjunto nao sera excedido*/
int insere_conjunto (conjunto_t *c, int elemento) {
    if (!pertence (c, elemento)) {
        if (c->card + 1 > c->max) return -1;
        else {
           sorted_insertion (elemento, c);
           c->card++;
           return 1;
        }
    } else return 0;
}

/* verifica se o elemento existe no conjunto */
/* remove o elemento do conjunto mantendo a ornedacao */
int retira_conjunto (conjunto_t *c, int elemento) {
    int pos, count;
    if ((pos = busca_binaria (c, elemento)) != -1) {
        pos = pos + 1;
        for (count = pos; count <= c->card; count++) 
            *(c->v+count-1) = *(c->v+count);
        c->card--;
        return 1;
    } else return 0;
}

/* Retorna se o elemento pertence ao conjunto */
int pertence (conjunto_t *c, int elemento) {
   if (busca_binaria (c, elemento) == -1) return 0;
   return 1;
}

/* Testa se o c1 esta contido no c2*/
/* se c1 for maior que c2 ele não tem como estar contido */
/* verifica se cada elemento de c1 esta em c2 */
int contido (conjunto_t *c1, conjunto_t *c2) {
    int count;
    if (c1->card > c2->card) return 0;
    else {
        for (count = 0; count < c1->card; count++) 
            if (!pertence (c2, *(c1->v+count))) return 0;
        return 1;
    }
}

/* Verifica se os conjuntos tem mesma cardinalidade */
/* para testar se são iguais basta verificar a igualdade de cada posição equivalente */
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
/* Passa por cada elemento do c1 insere ele no conjunto de diferença caso ele não esteja em c2 */
conjunto_t * cria_diferenca (conjunto_t *c1, conjunto_t *c2) {
    conjunto_t *conj;
    int count;

    if ((conj = cria_conjunto (c1->max)) != NULL) {
        for (count = 0; count < c1->card; count++) {
            if (!pertence (c2, *(c1->v+count))) 
                insere_conjunto (conj, *(c1->v+count));
        }
        return conj;
    } else return 0;
}

/* se os valores são iguas, adiciona no conjunto, se forem diferentes, faz o iterador que ponta para o 
menor numero andar uma 'casa' para frente. */
/* finaliza o processo quando um dos iteradores chegar ao fim do conjunto */
conjunto_t * cria_interseccao (conjunto_t *c1, conjunto_t *c2) {
    int ite1 = 0, ite2 = 0;
    conjunto_t *conj;

    if ((conj = cria_conjunto (c1->max)) != NULL) {
        while (ite1 < c1->card && ite2 < c2->card) {
            if (*(c1->v+ite1) == *(c2->v+ite2)) {
                insere_conjunto (conj, *(c1->v+ite1));
                ite1++;
                ite2++;
            } 
            else if (*(c1->v+ite1) < *(c2->v+ite2)) ite1++;
            else ite2++;
        }
        return conj;
    } else return 0;
}

/* O max do conjunto é equivalente a soma dos maximos de embos os conjuntos */
conjunto_t * cria_uniao (conjunto_t *c1, conjunto_t *c2) {
    conjunto_t *conj;
    int ite1 = 0, ite2 = 0, max;
    max = (c1->max) + (c2->max);

    if ((conj = cria_conjunto (max)) != NULL) {
        while (ite1 < c1->card || ite2 < c2->card) {
            if (ite1 >= c1->card) {
                insere_conjunto (conj, *(c2->v+ite2));
                ite2++;
            }
            else if (ite2 >= c2->card) {
                insere_conjunto (conj, *(c1->v+ite1));
                ite1++;
            }
            else if (*(c1->v+ite1) <= *(c2->v+ite2)) {
                insere_conjunto (conj, *(c1->v+ite1));
                ite1++;
            } else {
                insere_conjunto (conj, *(c2->v+ite2));
                ite2++;
            }
        }
        return conj;
    } else return 0;
}

/* cria uma copia do conjunto enviado como parametro */
/* insere cada elemento do conjunto enviado como parametro na copia */
conjunto_t * cria_copia (conjunto_t *c) {
    conjunto_t *conj;
    int count;

    if ((conj = cria_conjunto (c->max)) != NULL) {
        for (count = 0; count < c->card; count++) {
            insere_conjunto (conj, *(c->v+count));
        }
        return conj;
    } else return 0;
}

/* Se o n for maior que a cardinalidade retorna uma copia do conjunto */
/* consideramos o max do subconjunto sendo o max do conjunto enviado */
/* Se a inserção ocorrer ok, ou seja, o elemento nao existir no conjunto, soma + 1 no count */
conjunto_t * cria_subconjunto (conjunto_t *c, int n) {
    conjunto_t *conj;
    int count = 0;
    if (n >= c->card) return cria_copia (c);
    if ((conj = cria_conjunto (c->max)) != NULL) {
        if (c->card == 0) return conj;
        while (count < n) {
            if (insere_conjunto (conj, 1 + (rand() % (cardinalidade (c)))))
                count++;
        }
        return conj;
    } else return NULL;
}

/* imprime o conjunto */
void imprime (conjunto_t *c) {
    int count;
    for (count = 0; count < c->card; count++) 
        printf (" %d ", *(c->v+count));
    printf ("\n");
}

int redimensiona (conjunto_t *c) {
    int * temp;
    if ((temp = realloc (c->v, sizeof(int)*(c->max+1)*2))) {
        c->v = temp;
        c->max = c->max*2;
        return 1;
    } else return 0;
}

/* Incicializa o iterador em 0 */
void iniciar_iterador (conjunto_t *c) {
    c->ptr = 0;
}

/* Verifica se o ponteiro vai passar do fim do conjunto */
/* Necessário retornar o valor do ponteiro -1 pois o array inicia na casa 0 e não 1 */
int incrementar_iterador (conjunto_t *c, int *elemento) {
    if (c->ptr == c->card) return 0;
    c->ptr++;
    *elemento = *(c->v+(c->ptr-1));
    return 1;
}

int retirar_um_elemento (conjunto_t *c) {
    return retira_conjunto (c, *(c->v+(rand() % c->card)));
}
/* Funções publicas */