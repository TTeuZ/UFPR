#include <stdio.h>
#include <stdlib.h>
#include "libfila.h"

/* Funções internas */
/* -------------------------------------------------------------------------- */
int insere_fila_vazia (fila_t *f, int elemento) {
    nodo_f_t *nodo;
    /* Testa se o malloc ocorreu certo para continuar */
    if ((nodo = (nodo_f_t *) malloc (sizeof (nodo_f_t)))) {
        nodo->chave = elemento;
        /* Seta o prox e o prev para null, por ser o unico elemento atual */
        nodo->prox = NULL;
        nodo->prev = NULL;
        /* Aponta o inicio e o fim para este unico nodo */
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
    /* Testa se o malloc da fila deu certo */
    if ((fila = malloc (sizeof (fila_t)))) {
        fila->tamanho = 0;
        fila->atual = NULL;
        return fila;
    }
    return NULL;
}

fila_t * destroi_fila (fila_t *f) {
    nodo_f_t *nodo;
    if (fila_vazia (f)) {
        free (f); /* Libero o espaço alocado para a estrutura da fila */
        return NULL;
    }
    /* Passa por cada nodo da fila e libera seu espaço */
    while (f->ini != NULL) {
        nodo = f->ini;
        f->ini = f->ini->prox;
        f->tamanho--;
        free (nodo);
    }
    /* So preciso dar free no f->ini pq nesta situacao, tanto o f->ini e o f->fim estao apontando para o mesmo nodo */
    f->tamanho--;
    free (f); /* Libero o espaço alocado para a estrutura da fila */
    return NULL;
} 

/* retorna 1 se o tamanho for 0, e 0 caso contrario */
int fila_vazia (fila_t *f) {
    return f->tamanho == 0;
}

int tamanho_fila (fila_t *f) {
    return f->tamanho;
}

int insere_fila (fila_t *f, int elemento) {
    nodo_f_t *nodo;
    /* Se a minha fila for vazia, chama uma função especifica para esse caso */
    if (fila_vazia (f)) return insere_fila_vazia (f, elemento);
    /* Testa se o malloc ocorreu certo para continuar */
    if ((nodo = (nodo_f_t *) malloc (sizeof (nodo_f_t)))) {
        /* Setando os valores e apontadores do novo nodo */
        nodo->chave = elemento;
        nodo->prox = NULL; /* Aponta prox para NULL por ser o ultimo elemento */
        nodo->prev = f->fim; /* Aponta o prev para o antigo ulitmo elemento */
        /* Aponta o prox do 'antigo ultimo elemento' para o 'novo ultimo elemento' */
        f->fim->prox = nodo;
        /* Altera o apontador do fim para o nodo (inserindo no final) */
        f->fim = nodo;
        f->tamanho++;
        return 1;
    } else return 0;
}

int retira_fila (fila_t *f, int *elemento) {
    nodo_f_t *nodo;
    /* Se a fila estiver vazia retorna 0 */
    if (fila_vazia (f)) return 0;
    nodo = f->ini; /* Armazena o antigo nodo de inicio */
    f->ini = nodo->prox; /* Aponta o ini para o prox nodo */
    /* Se a fila nao tiver ficado vazia, aponta o prev para NULL */
    if (f->ini != NULL) {
        f->ini->prev = NULL;
        /* Se o atual estiver apontando para o primeiro elemento, faz ele apontar para o prox */
        if (f->atual != NULL && f->atual->chave == nodo->chave)
            f->atual = nodo->prox;
    } else {
        f->atual = NULL; /* se o fila ficar vazia, aponta o atual para NULL */
    }
    *elemento = nodo->chave; /* Retorna o elemento removido */
    free (nodo);
    f->tamanho--;
    return 1;
}

int inicializa_atual_fila (fila_t *f) {
    /* Se a fila estiver vazia retorna 0 */
    if (fila_vazia (f)) return 0;
    /* Inicia o 'atual' apontanto para o inicio da fila */
    f->atual = f->ini;
    return 1;
}

void incrementa_atual_fila (fila_t *f) {
    /* Se a fila estiver vazia retorna NULL */
    if (fila_vazia (f)) return;
    /* Aponta o atual para o proximo nodo */
    if (f->atual->prox != NULL)
        f->atual = f->atual->prox;
}

int consulta_atual_fila (fila_t *atual, int *elemento) {
     /* Se a fila estiver vazia retorna 0 */
    if (fila_vazia (atual)) return 0;
    /* Se o atual estiver apontando para NULL retorna 0 */
    if (atual->atual == NULL) return 0;
    *elemento = atual->atual->chave;
    return 1;
}

int retira_atual_fila (fila_t *f, int *elemento) {
    nodo_f_t *nodo;
    /* Se a fila estiver vazia retorna 0 */
    if (fila_vazia (f)) return 0;

    nodo = f->atual; /* Armazena o nodo atual */
    *elemento = nodo->chave; /* Retorna o elemento removido */
    f->tamanho--;
    /* Verifica se o atual esta apontando para o ultimo elemento */
    if (f->atual->prox == NULL) {
        f->fim = nodo->prev; /* Aponta o fim para o nodo anterior */
        /* Se a fila nao tiver ficado vazia, aponta o prox para NULL */
        if (f->fim != NULL) 
            f->fim->prox = NULL;
        /* Aponta o novo atual para o antecessor; */
        f->atual = f->atual->prev;
    } 
    /* Verifica se o atual esta apontando para o primeiro elemento */
    else if (f->atual->prev == NULL) {
        f->ini = nodo->prox; /* Aponta o ini para o prox nodo */
        /* Se a lista nao tiver ficado vazia, aponta o prev para NULL */
        if (f->ini != NULL) 
            f->ini->prev = NULL;
        /* Aponta o novo atual para o sucessor; */
        f->atual = f->atual->prox;
    }
    /* Atual apontando para um elemento no interio da fila */
    else {
        /* faz o prev do nodo da frente apontar para o prev do nodo que vai ser removido */
        nodo->prox->prev = nodo->prev;
        /* faz o prox do nodo de traz apontar para o prox do nodo que vai ser removido */
        nodo->prev->prox = nodo->prox;
        /* Aponta o novo atual para o sucessor; */
        f->atual = f->atual->prox;
    }
    free (nodo);
    return 1;
}
/* -------------------------------------------------------------------------- */
/* Funções publicas */