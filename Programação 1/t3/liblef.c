#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        l->Primeiro = l->Primeiro->prox;
        free (nodo->evento); /* aponta o primeiro para o prox elemento */
        free (nodo); /* libera o espaço do nodo */
    }
    /* Libera o espaço da estrutura da lista ao final */
    free (l);
    return NULL;
}

int adiciona_inicio_lef (lef_t *l, evento_t *evento) {
    nodo_lef_t *nodo;
    evento_t *evento_copy;
    /* Cria uma copia do evento */
    if ((evento_copy = malloc (sizeof(evento_t)))) {
        evento_copy->tempo = evento->tempo;
        evento_copy->tipo = evento->tipo;
        evento_copy->tamanho = evento->tamanho;
        memcpy (&evento_copy->dados, &evento->dados, evento->tamanho);
    } else return 0;
    /* Verifica se o malloc para o nodo deu boa */
    if ((nodo =  malloc (sizeof (nodo_lef_t)))) {
        nodo->evento = evento_copy; /* seta o valor do evento */
        nodo->prox = NULL; /* Seta o prox do nodo como null */
    } else return 0;
    /* Se a lef estiver vazia, apenas da free em sua estrutura */
    if (l->Primeiro == NULL) 
        l->Primeiro = nodo;
    /* Se estiver vazia, altera a sequencia dos ponteiros */ 
    else {
        nodo->prox = l->Primeiro;
        l->Primeiro = nodo;
    }
    return 1;
}

void adiciona_ordem_lef  (lef_t *l, evento_t *evento) {
    nodo_lef_t *nodo, *temp_ante, *temp_atual;
    evento_t *evento_copy;
    /* Cria uma copia do evento */
    if ((evento_copy = malloc (sizeof(evento_t)))) {
        evento_copy->tempo = evento->tempo;
        evento_copy->tipo = evento->tipo;
        evento_copy->tamanho = evento->tamanho;
        memcpy (&evento_copy->dados, &evento->dados, evento->tamanho);
    } else return;
    /* faço o malloc do nodo que vai ser inserido */
    if (!(nodo =  malloc (sizeof (nodo_lef_t)))) return;
    /* inicia o auxiliar no primeiro elemento da lef */
    temp_atual = l->Primeiro;
    /* se a minha lista estiver vazia, adiciona de cara no inicio */
    if (temp_atual == NULL) {
        free (evento_copy); /* libera o espaço da copia criada aqui */
        free (nodo); /* libera espaço no nodo previamente malocado */
        adiciona_inicio_lef (l, evento);
        return;
    }
    /* While par encontrar a posicao que o elemento deve ser inserido */
    while (temp_atual->prox != NULL && temp_atual->evento->tempo < evento->tempo) {
        temp_ante = temp_atual;
        temp_atual = temp_atual->prox;
    }
    /* Se a posição encontrada for a primeira, insere no inicio e o tempo do evento for maior */
    if (temp_atual == l->Primeiro && temp_atual->evento->tempo > evento->tempo) {
        free (evento_copy); /* libera o espaço da copia criada aqui */
        free (nodo); /* libera espaço no nodo previamente malocado */
        adiciona_inicio_lef (l, evento);
    } else if (temp_atual->prox == NULL) { /* verifica se ficou na ultima posicao */
        nodo->evento = evento_copy; /* seta o valor do evento */
        temp_atual->prox = nodo; /* Aponta o prox do anterior para o noco nodo */
        nodo->prox = NULL; /* aponta o prox do novo nodo para o nodo da seguencia */
    } else { /* para o caso mais generico */
        nodo->evento = evento_copy; /* seta o valor do evento */
        temp_ante->prox = nodo; /* Aponta o prox do anterior para o noco nodo */
        nodo->prox = temp_atual; /* aponta o prox do novo nodo para o nodo da seguencia */
    }
}

evento_t * obtem_primeiro_lef (lef_t *l) {
    nodo_lef_t *nodo;
    evento_t *evento;
    
    if (!l->Primeiro) return NULL; /* Se a lista ficou vazia retorna null */

    evento = l->Primeiro->evento; /* recebe o evento atual */
    nodo = l->Primeiro; /* armazena o nodo que tinha o evento */

    l->Primeiro = l->Primeiro->prox; /* aponta o ponteiro do primeiro para o prox da lista */
    free (nodo); /* libera o espaço do nodo */
    return evento; /* retorna o evento */
}
/* -------------------------------------------------------------------------- */
/* Funções publicas */