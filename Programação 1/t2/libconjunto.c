#include <stdio.h>
#include <stdlib.h>
#include "libconjunto.h"

/* Funções internas */
/* Busca iterativa o elemento x dentro do conjunto. */
/* Retorna a posição do elemento se ele foi encontrado e -1 caso ele não esteja no conjunto */
int busca_binaria (int x, conjunto_t *c) {
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

/* Insere o elemento x no conjunto, de maneira a manter ele ordenado. */
void sorted_insertion (int x, conjunto_t *c) {
    int count = c->card;
    /* Caso o array esteja vazio, insere no primeiro espaço */
    /* feito para evitar acessar um espaço fora do maloc */
    if (c->card == 0) 
        *(c->v+c->card) = x;
    else {
        /* Enquanto o valor da posição foi maior que o elemento empurra as valores uma 'casa' para frente */
        while (count != 0 && x <= *(c->v+count-1)) {
            *(c->v+count) = *(c->v+count-1);
            count--;
        }
        /* Insere o elemento na poisção correta, mantendo ordenado */
        *(c->v+count) = x;
    }
}

/* Remove o elemento x no conjunto, de maneira a manter ele ordenado. */
void sorted_remove (int x, conjunto_t *c) {
    int pos, count;
    /* busca a posição que o elemento no conjunto precisa somar +1 porque a busca binaria retorna exatamente a posição, e precisamos de 1 acima*/
    pos = busca_binaria (x, c)+1;
    /* Faz a remoção de maneira a manter o conjunto ordenado */
    for (count = pos; count <= c->card; count++) {
        *(c->v+count-1) = *(c->v+count);
    }
}
/* Funções internas */

/* Funções publicas */
/* A utilização do (max+1) nos mallocs veio por conta de um erro encontrado pelo valgrind */
/* De 'invalid write of size 4' */
conjunto_t * cria_conjunto (int max) {
    conjunto_t *conj;
    /* Testa o malloc para toda a estrutura do conjunto e inicia as variaveis */
    if ((conj = malloc (sizeof(conjunto_t)))) {
        conj->max = max;
        conj->card = 0;
        /* Testa o malloc para o vetor do conjunto */
        /* Em caso de falha livra o espaço posteriormente alocado e retorna 0 */
        if ((conj->v = (int*) malloc (sizeof(int)*(max+1))))
            return conj;
        else {
            free (conj);
            return NULL;
        }
    } else return NULL;
}

/* Libera os espaços alocados par ao conjunto. */
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
int insere_conjunto (conjunto_t *c, int elemento) {
    /* Verifica se o elemento ja esta no conjunto */
    if (busca_binaria (elemento, c) == -1) {
        /* verifica se adicionarmor o elemento a tamanho maximo do conjunto nao sera excedido*/
        if (c->card + 1 > c->max) return -1;
        else {
           sorted_insertion (elemento, c); /* insere o elemento */
           c->card++;
           return 1;
        }
    } else return 0;
}

/* remove o elemento do conjunto mantendo a ornedacao */
int retira_conjunto (conjunto_t *c, int elemento) {
    /* verifica se o elemento existe no conjunto */
    if (busca_binaria (elemento, c) != -1) {
        sorted_remove (elemento, c); /* remove o elemento */
        c->card--;
        return 1;
    } else return 0;
}

/* Retorna se o elemento pertence ao conjunto */
int pertence (conjunto_t *c, int elemento) {
   /* return busca_binaria(elemento, c); */
   if (busca_binaria (elemento, c) == -1) return 0;
   return 1;
}

/* Testa se o c1 esta contido no c2*/
int contido (conjunto_t *c1, conjunto_t *c2) {
    int count;
    /* se c1 for maior que c2 ele não tem como estar contido */
    if (c1->card > c2->card) return 0;
    else {
        /* verifica se cada elemento de c1 esta em c2 */
        for (count = 0; count < c1->card; count++) 
            if (busca_binaria (*(c1->v+count), c2) == -1) return 0;
        return 1;
    }
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
    if ((conj = cria_conjunto (c1->max)) != NULL) {
        /* Passa por cada elemento do c1 */
        for (count = 0; count < c1->card; count++) {
            /* insere ele no conjunto de diferença caso ele não esteja em c2 */
            if (busca_binaria (*(c1->v+count), c2) == -1) 
                insere_conjunto (conj, *(c1->v+count));
        }
        return conj;
    } else return 0;
}

/* O max do conjunto nunca passa do max do menor conjunto. */
conjunto_t * cria_interseccao (conjunto_t *c1, conjunto_t *c2) {
    conjunto_t *conj, *min;
    int count;

    if (c1->card < c2->card) min = c1;
    else min = c2;

    /* Verifica se a criação do conjunto para a diferença ocorreu corretamente */
    if ((conj = cria_conjunto (min->max)) != NULL) {
        /* Passa por cada elemento do menor conjunto */
        for (count = 0; count < c1->card; count++) {
            /* insere ele no conjunto de interseccao caso ele esteja no maior conjunto */
            if (busca_binaria (*(c1->v+count), c2) != -1) 
                insere_conjunto (conj, *(c1->v+count));
            }
        return conj;
    } else return 0;
}

/* O max do conjunto é equivalente a soma dos maximos de embos os conjuntos */
conjunto_t * cria_uniao (conjunto_t *c1, conjunto_t *c2) {
    conjunto_t *conj;
    int count, max;
    /* O max do conujnto de união pode ser no maximo a soma do maximo dos dois demais conjuntos */
    max = (c1->max) + (c2->max);

    /* Verifica se a criação do conjunto para a diferença ocorreu corretamente */
    if ((conj = cria_conjunto (max)) != NULL) {
        /* Inicia um for que vai até o ultimo elemento do maior conjunto */
        for (count = 0; count < c1->card; count++) 
            /* insere o elemento da vez no conjunto união ** regras do insere aplicadas ** */
            insere_conjunto (conj, *(c1->v+count));

        for (count = 0; count < c2->card; count++) 
            /* insere o elemento da vez no conjunto união ** regras do insere aplicadas ** */
            insere_conjunto (conj, *(c2->v+count));
        
        return conj;
    } else return NULL;
}

/* cria uma copia do conjunto enviado como parametro */
conjunto_t * cria_copia (conjunto_t *c) {
    conjunto_t *conj;
    int count;

    /* Verifica se a criação do conjunto para a copia ocorreu corretamente */
    if ((conj = cria_conjunto (c->max)) != NULL) {
        /* insere cada elemento do conjunto enviado como parametro na copia */
        for (count = 0; count < c->card; count++) {
            insere_conjunto (conj, *(c->v+count));
        }
        return conj;
    } else return 0;
}

conjunto_t * cria_subconjunto (conjunto_t *c, int n) {
    conjunto_t *conj;
    int count = 0;
    /* Se o n for maior que a cardinalidade retorna uma copia do conjunto */
    if (n >= c->card) return cria_copia (c);
    /* consideramos o max do subconjunto sendo o max do conjunto enviado */
    if ((conj = cria_conjunto (c->max)) != NULL) {
        if (c->card == 0) return conj;
        while (count < n) {
            /* Se a inserção ocorrer ok, ou seja, o elemento nao existir no conjunto, soma + 1 no count */
            if (insere_conjunto (conj, (rand() % (cardinalidade (c)))))
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
    /* Testa se o realoc deu certo */
    if ((temp = realloc (c->v, sizeof(int)*(c->max+1)*2))) {
        /* caso tenha dado certo faz as atribuicoes necessarias */
        c->v = temp;
        c->max = c->max*2;
        return 1;
    } else return 0;
}

/* Incicializa o iterador em 0 */
void iniciar_iterador (conjunto_t *c) {
    c->ptr = 0;
}

int incrementar_iterador (conjunto_t *c, int *elemento) {
    /* Verifica se o ponteiro vai passar do fim do conjunto */
    if (c->ptr == c->card) return 0;
    c->ptr++;
    /* Necessário retornar o valor do ponteiro -1 pois o array inicia na casa 0 e não 1 */
    *elemento = *(c->v+(c->ptr-1));
    return 1;
}

int retirar_um_elemento (conjunto_t *c) {
    return retira_conjunto (c, *(c->v+(rand() % c->card)));
}
/* Funções publicas */