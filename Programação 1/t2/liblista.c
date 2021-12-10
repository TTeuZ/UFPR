#include <stdio.h>
#include <stdlib.h>
#include "liblista.h"

/* Funções internas */
/* -------------------------------------------------------------------------- */
/* Seta o prox e o prev para null, por ser o unico elemento atual */
/* Aponta o inicio e o fim para este unico nodo */
int insere_lista_vazia (lista_t *l, int elemento) {
    nodo_t *nodo;
    if ((nodo = (nodo_t *) malloc (sizeof (nodo_t)))) {
        nodo->elemento = elemento;
        nodo->prox = NULL;
        nodo->prev = NULL;

        l->ini = nodo;
        l->fim = nodo;
        l->tamanho++;
        return 1;
    } else return 0;
}
/* -------------------------------------------------------------------------- */
/* Funções internas */

/* Funções publicas */
/* -------------------------------------------------------------------------- */
/* Necessario inicializar o tamanho por conta do erro */
/* Conditional jump or move depends on uninitialised value(s) */
/* que é apontado pelo valgrind quando utilizamos a função 'lista_vazia' para uma lista recem criada. */
lista_t * cria_lista () {
    lista_t *list;
    if ((list = malloc (sizeof (lista_t)))) {
        list->tamanho = 0;
        return list;
    }
    return NULL;
}

/* Passa por cada nodo da lista e libera seu espaço */
/* So preciso dar free no l->ini pq nesta situacao, tanto o l->ini e o l->fim estao apontando para o mesmo nodo */
lista_t * destroi_lista (lista_t *l) {
    nodo_t *nodo;
    if (lista_vazia (l)) {
        free (l);
        return NULL;
    }
    while (l->ini != NULL) {
        nodo = l->ini;
        l->ini = l->ini->prox;
        l->tamanho--;
        free (nodo);
    }
    l->tamanho--;
    free (l);
    return NULL;
} 

/* retorna 1 se o tamanho for 0, e 0 caso contrario */
int lista_vazia (lista_t *l) {
    return l->tamanho == 0;
}

int tamanho_lista (lista_t *l) {
    return l->tamanho;
}

/* Se a minha lista for vazia, chama uma função especifica para esse caso */
/* Aponta o prev do 'antigo primeiro elemento' para o 'novo primeiro elemento' */
/* Altera o apontador do inicio para o nodo (insirindo no começo) */
int insere_inicio_lista (lista_t *l, int elemento) {
    nodo_t *nodo;
    if (lista_vazia (l)) return insere_lista_vazia (l, elemento);
    if ((nodo = (nodo_t *) malloc (sizeof (nodo_t)))) {
        nodo->elemento = elemento;
        nodo->prox = l->ini; 
        nodo->prev = NULL; 
        l->ini->prev = nodo;
        l->ini = nodo;
        l->tamanho++;
        return 1;
    } else return 0;
}

/* Se a minha lista for vazia, chama uma função especifica para esse caso */
/* Aponta o prox do 'antigo ultimo elemento' para o 'novo ultimo elemento' */
/* Altera o apontador do fim para o nodo (inserindo no final) */
int insere_fim_lista (lista_t *l, int elemento) {
    nodo_t *nodo;
    if (lista_vazia (l)) return insere_lista_vazia (l, elemento);
    if ((nodo = (nodo_t *) malloc (sizeof (nodo_t)))) {
        nodo->elemento = elemento;
        nodo->prox = NULL;
        nodo->prev = l->fim; 
        l->fim->prox = nodo;
        l->fim = nodo;
        l->tamanho++;
        return 1;
    } else return 0;
}

/* Se a minha lista for vazia, chama uma função especifica para esse caso */
/* While par encontrar a posicao que o elemento deve ser inserido */
/* Se o elemento for menor que todos os demais, insere no inicio. Verifica
se o nodo->elemento é menor que o elemento pois no caso de termos apenas
1 item na lista, tando o l->ini e o l->fim apontam para o mesmo nodo */
/* Se o elemento for maior que todos os demais, insere no fim */
int insere_ordenado_lista (lista_t *l, int elemento) {
    nodo_t *nodo, *nodo_ante, *nodo_atual;
    if (lista_vazia (l)) return insere_lista_vazia (l, elemento);    

    nodo_atual = l->ini;
    while (nodo_atual->prox != NULL && nodo_atual->elemento <= elemento) {
        nodo_ante = nodo_atual;
        nodo_atual = nodo_atual->prox;
    }
    if (nodo_atual == l->ini && nodo_atual->elemento > elemento) 
        return insere_inicio_lista (l, elemento);
    else if (nodo_atual == l->fim) return insere_fim_lista (l, elemento);
    else {
        if ((nodo = (nodo_t *) malloc (sizeof (nodo_t)))) {
            nodo->elemento = elemento;
            nodo->prox = nodo_atual;
            nodo_atual->prev = nodo;
            nodo->prev = nodo_ante;
            nodo_ante->prox = nodo;
            l->tamanho++;
            return 1;
        } else return 0;
    }
}

/* Se a lista estiver vazia retorna 0 */
/* Se a lista nao tiver ficado vazia, aponta o prev para NULL */
int retira_inicio_lista (lista_t *l, int *elemento) {
    nodo_t *nodo;
    if (lista_vazia (l)) return 0;
    nodo = l->ini;
    l->ini = nodo->prox; 
    if (l->ini != NULL) 
        l->ini->prev = NULL;
    *elemento = nodo->elemento;
    free (nodo);
    l->tamanho--;
    return 1;
}

/* Se a lista estiver vazia retorna 0 */
/* Se a lista nao tiver ficado vazia, aponta o prox para NULL */
int retira_fim_lista (lista_t *l, int *elemento) {
    nodo_t *nodo;
    if (lista_vazia (l)) return 0;
    nodo = l->fim;
    l->fim = nodo->prev;
    if (l->fim != NULL) 
        l->fim->prox = NULL;
    *elemento = nodo->elemento;
    free (nodo);
    l->tamanho--;
    return 1;
}

/* Se a lista esta vazia, retorna 0 */
/* While par encontrar a posicao que o elemento deve ser inserido */
/* Verifica se o elemento foi encontrado, ou se o lista chegou no fim */
/* se o elemento estiver no inicio, chama a funcao para retirar do inicio */
/* Se o elemento estiver no fim, chama a funcao para retirar do fim */
int retira_elemento_lista (lista_t *l, int elemento) {
    nodo_t *nodo;
    int temp;
    if (lista_vazia (l)) return 0;

    nodo = l->ini;
    while (nodo->prox != NULL && nodo->elemento != elemento)
        nodo = nodo->prox;

    if (nodo->elemento == elemento) {
        if (nodo == l->ini) return retira_inicio_lista (l, &temp);
        else if (nodo == l->fim) return retira_fim_lista (l, &temp);
        else {
            nodo->prox->prev = nodo->prev;
            nodo->prev->prox = nodo->prox;
            l->tamanho--;
            free (nodo);
            return 1;
        }
    } else return 0;
}

/* Se a lista esta vazia, retorna 0 */
/* Passa por todos os elementos da lista, até seu final, ou até encontrar um nodo com o mesmo elemento procurado */
int pertence_lista (lista_t *l, int elemento) {
    nodo_t *nodo;
    if (lista_vazia (l)) return 0;
    nodo = l->ini;
    while (nodo != NULL && nodo->elemento != elemento) 
        nodo = nodo->prox;
    
    if (nodo == NULL) return 0;
    return 1;
}
/* -------------------------------------------------------------------------- */
/* Funções publicas */