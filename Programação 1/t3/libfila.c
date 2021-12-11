#include <stdio.h>
#include <stdlib.h>
#include "libfila.h"

/* Funções internas */
/* -------------------------------------------------------------------------- */
/* Seta o prox e o prev para null, por ser o unico elemento atual */
/* Aponta o inicio e o fim para este unico nodo */
int insere_fila_vazia (fila_t *f, int elemento) {
    nodo_f_t *nodo;
    if ((nodo = (nodo_f_t *) malloc (sizeof (nodo_f_t)))) {
        nodo->chave = elemento;
        nodo->prox = NULL;
        nodo->prev = NULL;

        f->ini = nodo;
        f->fim = nodo;
        f->tamanho++;
        return 1;
    } else return 0;
}
/* -------------------------------------------------------------------------- */
/* Funções internas */

/* Funções publicas */
/* -------------------------------------------------------------------------- */
/* Necessario inicializar o tamanho e o atual por conta do erro */
/* Conditional jump or move depends on uninitialised value(s) */
/* que é apontado pelo valgrind quando utilizamos a função 'fila_vazia' para uma fila recem criada. */
fila_t * cria_fila () {
    fila_t *fila;
    if ((fila = malloc (sizeof (fila_t)))) {
        fila->tamanho = 0;
        fila->atual = NULL;
        return fila;
    }
    return NULL;
}

/* Passa por cada nodo da fila e libera seu espaço */
/* So preciso dar free no f->ini pq nesta situacao, tanto o f->ini e o f->fim estao apontando para o mesmo nodo */
fila_t * destroi_fila (fila_t *f) {
    nodo_f_t *nodo;
    if (fila_vazia (f)) {
        free (f);
        return NULL;
    }
    while (f->ini != NULL) {
        nodo = f->ini;
        f->ini = f->ini->prox;
        f->tamanho--;
        free (nodo);
    }
    f->tamanho--;
    free (f); 
    return NULL;
} 

/* retorna 1 se o tamanho for 0, e 0 caso contrario */
int fila_vazia (fila_t *f) {
    return f->tamanho == 0;
}

int tamanho_fila (fila_t *f) {
    return f->tamanho;
}

/* Se a minha fila for vazia, chama uma função especifica para esse caso */
/* Aponta prox para NULL por ser o ultimo elemento */
/* Aponta o prev para o antigo ulitmo elemento */
/* Aponta o prox do 'antigo ultimo elemento' para o 'novo ultimo elemento' */
/* Altera o apontador do fim para o nodo (inserindo no final) */
int insere_fila (fila_t *f, int elemento) {
    nodo_f_t *nodo;
    if (fila_vazia (f)) return insere_fila_vazia (f, elemento);
    if ((nodo = (nodo_f_t *) malloc (sizeof (nodo_f_t)))) {
        nodo->chave = elemento;
        nodo->prox = NULL;
        nodo->prev = f->fim;
        f->fim->prox = nodo;
        f->fim = nodo;
        f->tamanho++;
        return 1;
    } else return 0;
}

/* Se a fila estiver vazia retorna 0 */
/* Se a fila nao tiver ficado vazia, aponta o prev para NULL */
/* Se o atual estiver apontando para o primeiro elemento, faz ele apontar para o prox */
/* se o fila ficar vazia, aponta o atual para NULL */
int retira_fila (fila_t *f, int *elemento) {
    nodo_f_t *nodo;
    if (fila_vazia (f)) return 0;
    nodo = f->ini;
    f->ini = nodo->prox; 
    if (f->ini != NULL) {
        f->ini->prev = NULL;
        if (f->atual != NULL && f->atual->chave == nodo->chave)
            f->atual = nodo->prox;
    } else {
        f->atual = NULL;
    }
    *elemento = nodo->chave;
    free (nodo);
    f->tamanho--;
    return 1;
}

/* Se a fila estiver vazia retorna 0. Inicia o 'atual' apontanto para o inicio da fila */
int inicializa_atual_fila (fila_t *f) {
    if (fila_vazia (f)) return 0;
    f->atual = f->ini;
    return 1;
}

/* Se a fila estiver vazia retorna NULL. Aponta o atual para o proximo nodo */
void incrementa_atual_fila (fila_t *f) {
    if (fila_vazia (f)) return;
    if (f->atual != NULL)
        f->atual = f->atual->prox;
}

/* Se a fila estiver vazia retorna 0. Se o atual estiver apontando para NULL retorna 0 */
int consulta_atual_fila (fila_t *atual, int *elemento) {
    if (fila_vazia (atual)) return 0;
    if (atual->atual == NULL) return 0;
    *elemento = atual->atual->chave;
    return 1;
}

/* Se a fila estiver vazia retorna 0 */
/* Se o atual estiver apontando para NULL retorna 0 */
/* Verifica se o atual esta apontando para o ultimo elemento. Se a fila nao tiver ficado vazia, aponta o prox para NULL */
/* Verifica se o atual esta apontando para o primeiro elemento. Se a lista nao tiver ficado vazia, aponta o prev para NULL */
/* Aponta o novo atual para o sucessor; */
int retira_atual_fila (fila_t *f, int *elemento) {
    nodo_f_t *nodo;
    if (fila_vazia (f)) return 0;
    if (f->atual == NULL) return 0;

    nodo = f->atual;
    *elemento = nodo->chave;
    f->tamanho--;
    if (f->atual->prox == NULL) {
        f->fim = nodo->prev;
        if (f->fim != NULL) 
            f->fim->prox = NULL;
        f->atual = f->atual->prev;
    } 
    else if (f->atual->prev == NULL) {
        f->ini = nodo->prox;
        if (f->ini != NULL) 
            f->ini->prev = NULL;
        f->atual = f->atual->prox;
    }
    else {
        nodo->prox->prev = nodo->prev;
        nodo->prev->prox = nodo->prox;
        f->atual = f->atual->prox;
    }
    free (nodo);
    return 1;
}
/* -------------------------------------------------------------------------- */
/* Funções publicas */