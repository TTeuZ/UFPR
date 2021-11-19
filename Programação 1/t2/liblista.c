#include <stdio.h>
#include <stdlib.h>
#include "liblista.h"

/* Funções internas */
/* -------------------------------------------------------------------------- */

int insere_lista_vazia(lista_t *l, int elemento) {
    nodo_t *nodo;

    /* Testa se o malloc ocorreu certo para continuar */
    if ((nodo = (nodo_t *) malloc (sizeof (nodo_t)))) {
        nodo->elemento = elemento;
        /* Seta o prox e o prev para null, por ser o unico elemento atual */
        nodo->prox = NULL;
        nodo->prev = NULL;

        /* Aponta o inicio e o fim para este unico nodo */
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
    /* Testa se o malloc da lista deu certo */
    if ((list = malloc (sizeof (lista_t)))) {
        list->tamanho = 0;
        return list;
    }
    return NULL;
}

lista_t * destroi_lista (lista_t *l) {
    nodo_t *nodo;
    if (lista_vazia(l)) {
        free (l); /* Libero o espaço alocado para a estrutura da lista */
        return NULL;
    }
    /* Passa por cada nodo da lista e libera seu espaço */
    while (l->ini != NULL) {
        nodo = l->ini;
        l->ini = l->ini->prox;
        l->tamanho--;
        free (nodo);
    }
    /* So preciso dar free no l->ini pq nesta situacao, tanto o l->ini e o l->fim estao apontando para o mesmo nodo */
    /* free (l->ini); */
    /* free (l); */ /* Libero o espaço alocado para a estrutura da lista */
    l->tamanho--;
    return NULL;
} 

/* retorna 1 se o tamanho for 0, e 0 caso contrario */
int lista_vazia (lista_t *l) {
    return l->tamanho == 0;
}

int tamanho_lista (lista_t *l) {
    return l->tamanho;
}

int insere_inicio_lista (lista_t *l, int elemento) {
    nodo_t *nodo;

    /* Se a minha lista for vazia, chama uma função especifica para esse caso */
    if (lista_vazia (l)) 
        return insere_lista_vazia(l, elemento);
    
    /* Testa se o malloc ocorreu certo para continuar */
    if ((nodo = (nodo_t *) malloc (sizeof (nodo_t)))) {
        /* Aponta o prev do antigo primeiro elemento para o novo primeiro elemento */
        l->ini->prev = nodo;
        /* Setando os valores e apontadores do novo nodo */
        nodo->elemento = elemento;
        nodo->prox = l->ini; /* Aponta prox para o antigo primeiro elemento */
        nodo->prev = NULL; /* Aponta prev para NULL */
        /* Altera o apontador do inicio apenas, por estar inserindo no começo */
        l->ini = nodo;
        l->tamanho++;
        return 1;
    } else return 0;
}
/* -------------------------------------------------------------------------- */
/* Funções publicas */
