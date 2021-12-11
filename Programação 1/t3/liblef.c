#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liblef.h"

/* Funções publicas */
/* -------------------------------------------------------------------------- */
/* Seta o Primeiro como NULL (lef vazia) */
lef_t * cria_lef () {
    lef_t *lef;
    if ((lef = malloc (sizeof (lef_t)))) {
        lef->Primeiro = NULL;
        return lef;
    } else return NULL;
}

/* Se a lef estiver vazia, apenas da free em sua estrutura */
/* Equanto a lista não ficar vazia, vai liberando os nodos */
/* Libera o espaço da estrutura da lista ao final */
lef_t * destroi_lef (lef_t *l) {
    nodo_lef_t *nodo;
    if (l->Primeiro == NULL) {
        free (l);
        return NULL;
    }
    while (l->Primeiro != NULL) {
        nodo = l->Primeiro;
        l->Primeiro = l->Primeiro->prox;
        free (nodo->evento->dados);
        free (nodo->evento);
        free (nodo);
    }
    free (l);
    return NULL;
}

 /* Cria uma copia do evento */
  /* Se estiver vazia, altera a sequencia dos ponteiros */ 
int adiciona_inicio_lef (lef_t *l, evento_t *evento) {
    nodo_lef_t *nodo;
    evento_t *evento_copy;
    if ((evento_copy = malloc (sizeof(evento_t)))) {
        evento_copy->tempo = evento->tempo;
        evento_copy->tipo = evento->tipo;
        evento_copy->tamanho = evento->tamanho;
        evento_copy->dados = malloc (evento->tamanho);
        memcpy (evento_copy->dados, evento->dados, evento->tamanho);
    } else return 0;

    if ((nodo = malloc (sizeof (nodo_lef_t)))) {
        nodo->evento = evento_copy; 
        nodo->prox = NULL;
    } else return 0;
    if (l->Primeiro == NULL) 
        l->Primeiro = nodo;
    else {
        nodo->prox = l->Primeiro;
        l->Primeiro = nodo;
    }
    return 1;
}

/* Cria uma copia do evento */
/* antes de chamar a funcao de insercao no inicio, libera as estruturas alocadas */
/* se a minha lista estiver vazia, adiciona no inicio */
/* Se a posição encontrada for a primeira, insere no inicio e o tempo do evento for maior */
void adiciona_ordem_lef  (lef_t *l, evento_t *evento) {
    nodo_lef_t *nodo, *temp_ante, *temp_atual;
    evento_t *evento_copy;
    if ((evento_copy = (evento_t*) malloc (sizeof(evento_t)))) {
        evento_copy->tempo = evento->tempo;
        evento_copy->tipo = evento->tipo;
        evento_copy->tamanho = evento->tamanho;
        evento_copy->dados = malloc (evento->tamanho);
        memcpy (evento_copy->dados, evento->dados, evento->tamanho);
    } else return;
    if (!(nodo = malloc (sizeof (nodo_lef_t)))) return;
    temp_atual = l->Primeiro;
    if (temp_atual == NULL) {
        free (evento_copy->dados);
        free (evento_copy);
        free (nodo);
        adiciona_inicio_lef (l, evento);
        return;
    }
    while (temp_atual->prox != NULL && temp_atual->evento->tempo < evento->tempo) {
        temp_ante = temp_atual;
        temp_atual = temp_atual->prox;
    }
    if (temp_atual == l->Primeiro && temp_atual->evento->tempo >= evento->tempo) {
        free (evento_copy->dados); 
        free (evento_copy); 
        free (nodo); 
        adiciona_inicio_lef (l, evento);
        return;
    } else if (temp_atual->prox == NULL) {
        nodo->evento = evento_copy;
        temp_atual->prox = nodo;
        nodo->prox = NULL;
    } else { 
        nodo->evento = evento_copy; 
        temp_ante->prox = nodo; 
        nodo->prox = temp_atual;
    }
}

/* Se a lista ficou vazia retorna null */
/* aponta o ponteiro do primeiro para o prox da lista */
evento_t * obtem_primeiro_lef (lef_t *l) {
    nodo_lef_t *nodo;
    evento_t *evento;
    
    if (!l->Primeiro) return NULL;

    evento = l->Primeiro->evento; 
    nodo = l->Primeiro;

    l->Primeiro = l->Primeiro->prox;
    free (nodo);
    return evento;
}
/* -------------------------------------------------------------------------- */
/* Funções publicas */