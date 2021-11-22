#include <stdio.h>
#include <stdlib.h>
#include "liblista.h"

/* Funções internas */
/* -------------------------------------------------------------------------- */
int insere_lista_vazia (lista_t *l, int elemento) {
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
    if (lista_vazia (l)) {
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
    l->tamanho--;
    free (l); /* Libero o espaço alocado para a estrutura da lista */
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
    if (lista_vazia (l)) return insere_lista_vazia (l, elemento);
    /* Testa se o malloc ocorreu certo para continuar */
    if ((nodo = (nodo_t *) malloc (sizeof (nodo_t)))) {
        /* Setando os valores e apontadores do novo nodo */
        nodo->elemento = elemento;
        nodo->prox = l->ini; /* Aponta prox para o antigo primeiro elemento */
        nodo->prev = NULL; /* Aponta prev para NULL */
        /* Aponta o prev do 'antigo primeiro elemento' para o 'novo primeiro elemento' */
        l->ini->prev = nodo;
        /* Altera o apontador do inicio para o nodo (insirindo no começo) */
        l->ini = nodo;
        l->tamanho++;
        return 1;
    } else return 0;
}

int insere_fim_lista (lista_t *l, int elemento) {
    nodo_t *nodo;
    /* Se a minha lista for vazia, chama uma função especifica para esse caso */
    if (lista_vazia (l)) return insere_lista_vazia (l, elemento);
    /* Testa se o malloc ocorreu certo para continuar */
    if ((nodo = (nodo_t *) malloc (sizeof (nodo_t)))) {
        /* Setando os valores e apontadores do novo nodo */
        nodo->elemento = elemento;
        nodo->prox = NULL; /* Aponta prox para NULL por ser o ultimo elemento */
        nodo->prev = l->fim; /* Aponta o prev para o antigo ulitmo elemento */
        /* Aponta o prox do 'antigo ultimo elemento' para o 'novo ultimo elemento' */
        l->fim->prox = nodo;
        /* Altera o apontador do fim para o nodo (inserindo no final) */
        l->fim = nodo;
        l->tamanho++;
        return 1;
    } else return 0;
}

int insere_ordenado_lista (lista_t *l, int elemento) {
    nodo_t *nodo, *nodo_ante, *nodo_atual;
    /* Se a minha lista for vazia, chama uma função especifica para esse caso */
    if (lista_vazia (l)) return insere_lista_vazia (l, elemento);    

    nodo_atual = l->ini;
    /* While par encontrar a posicao que o elemento deve ser inserido */
    while (nodo_atual->prox != NULL && nodo_atual->elemento <= elemento) {
        nodo_ante = nodo_atual;
        nodo_atual = nodo_atual->prox;
    }
    /* Se o elemento for menor que todos os demais, insere no inicio. Verifica
    se o nodo->elemento é menor que o elemento pois no caso de termos apenas
    1 item na lista, tando o l->ini e o l->fim apontam para o mesmo nodo */
    if (nodo_atual == l->ini && nodo_atual->elemento > elemento) 
        return insere_inicio_lista (l, elemento);
    /* Se o elemento for maior que todos os demais, insere no fim */
    else if (nodo_atual == l->fim) return insere_fim_lista (l, elemento);
    /* insere o elemento entre o anterior e o prox*/
    else {
        if ((nodo = (nodo_t *) malloc (sizeof (nodo_t)))) {
            nodo->elemento = elemento;
            /* vinculos com o elemento posterior */
            nodo->prox = nodo_atual;
            nodo_atual->prev = nodo;
            /* vinculos com o elementoanterior */
            nodo->prev = nodo_ante;
            nodo_ante->prox = nodo;
            l->tamanho++;
            return 1;
        } else return 0;
    }
}

int retira_inicio_lista (lista_t *l, int *elemento) {
    nodo_t *nodo;
    /* Se a lista estiver vazia retorna 0 */
    if (lista_vazia (l)) return 0;
    nodo = l->ini; /* Armazena o antigo nodo de inicio */
    l->ini = nodo->prox; /* Aponta o ini para o prox nodo */
    /* Se a lista nao tiver ficado vazia, aponta o prev para NULL */
    if (l->ini != NULL) 
        l->ini->prev = NULL;
    *elemento = nodo->elemento; /* Retorna o elemento removido */
    free (nodo);
    l->tamanho--;
    return 1;
}

int retira_fim_lista (lista_t *l, int *elemento) {
    nodo_t *nodo;
    /* Se a lista estiver vazia retorna 0 */
    if (lista_vazia (l)) return 0;
    nodo = l->fim; /* Armazena o antigo nodo de fim */
    l->fim = nodo->prev; /* Aponta o fim para o nodo anterior */
    /* Se a lista nao tiver ficado vazia, aponta o prox para NULL */
    if (l->fim != NULL) 
        l->fim->prox = NULL;
    *elemento = nodo->elemento; /* Retorna o elemento removido */
    free (nodo);
    l->tamanho--;
    return 1;
}

int retira_elemento_lista (lista_t *l, int elemento) {
    nodo_t *nodo;
    int temp; /* inteiro para receber os retornos do retira inicio/fim (nao utilizado) */
    /* Se a lista esta vazia, retorna 0 */
    if (lista_vazia (l)) return 0;

    nodo = l->ini;
    /* While par encontrar a posicao que o elemento deve ser inserido */
    while (nodo->prox != NULL && nodo->elemento != elemento)
        nodo = nodo->prox;

    /* Verifica se o elemento foi encontrado, ou se o lista chegou no fim */
    if (nodo->elemento == elemento) {
        /* se o elemento estiver no inicio, chama a funcao para retirar do inicio */
        if (nodo == l->ini) return retira_inicio_lista (l, &temp);
        /* Se o elemento estiver no fim, chama a funcao para retirar do fim */
        else if (nodo == l->fim) return retira_fim_lista (l, &temp);
        /* Se o elemento estiver no meio */
        else {
            /* faz o prev do nodo da frente apontar para o prev do nodo que vai ser removido */
            nodo->prox->prev = nodo->prev;
            /* faz o prox do nodo de traz apontar para o prox do nodo que vai ser removido */
            nodo->prev->prox = nodo->prox;
            l->tamanho--;
            free (nodo);
            return 1;
        }
    } else return 0;
}

int pertence_lista (lista_t *l, int elemento) {
    nodo_t *nodo;
    /* Se a lista esta vazia, retorna 0 */
    if (lista_vazia (l)) return 0;
    nodo = l->ini; /* Inicializa com a primeira posicao */
    /* Passa por todos os elementos da lista, até seu final, ou até encontrar um nodo com o mesmo elemento procurado */
    while (nodo != NULL && nodo->elemento != elemento) 
        nodo = nodo->prox;
    
    if (nodo == NULL) return 0; /* Se chegou no fim e não encontrou retorna 0*/
    return 1; /* Caso o nodo seja diferente de NULL, retorna 1 */
}
/* -------------------------------------------------------------------------- */
/* Funções publicas */