#include <stdio.h>
#include <stdlib.h>
#include "liblef.h"

/* Funções publicas */
/* -------------------------------------------------------------------------- */
lef_t * cria_lef () {
    lef_t *lef;
    /* testa se o maloc deu certo */
    if ((lef = malloc (sizeof (lef_t)))) {
        /* Seta o Primeiro como NULL (lef vazia) */
        lef->Primeiro = NULL;
        return lef;
    } else return NULL;
}

lef_t * destroi_lef (lef_t *l) {
    nodo_lef_t *nodo;
    /* Se a lef estiver vazia, apenas da free em sua estrutura */
    if (l->Primeiro == NULL) {
        free (l);
        return NULL;
    }
    /* Alquanto a lista não ficar vazia, vai liberando os nodos */
    while (l->Primeiro != NULL) {
        nodo = l->Primeiro;
        l->Primeiro = l->Primeiro->prox; /* aponta o primeiro para o prox elemento */
        free (nodo); /* libera o espaço do nodo */
    }
    /* Libera o espaço da estrutura da lista ao final */
    free (l);
    return NULL;
}

int adiciona_inicio_lef (lef_t *l, evento_t *evento) {
    nodo_lef_t *nodo;
    /* Verifica se o malloc para o nodo deu boa */
    if ((nodo =  malloc (sizeof (nodo_lef_t)))) {
        nodo->evento = evento; /* seta o valor do evento */
        nodo->prox = NULL; /* Seta o prox do nodo como null */
    } else return 0;
    /* Se a lef estiver vazia, apenas da free em sua estrutura */
    if (l->Primeiro == NULL) {
        l->Primeiro = nodo;
    } 
    /* Se estiver vazia, altera a sequencia dos ponteiros */ 
    else {
        nodo->prox = l->Primeiro;
        l->Primeiro = nodo;
    }
    return 1;
}
/* -------------------------------------------------------------------------- */
/* Funções publicas */