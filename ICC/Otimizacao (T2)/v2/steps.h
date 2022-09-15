#ifndef __STEPS_H__
#define __STEPS_H__

#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

typedef struct pivot_steps {
    int *lines;
    int *pivots;
    int qtd;
} pivot_steps_t;

/*!
    \brief Aloca espaço para a struct de passos de pivotamento
    \param n quantidade maxima de pivotamentos (tamanho da matriz)
    \returns Ponteiro de acesso para a estrutura steps em caso de sucesso. Null em caso de falha
*/
pivot_steps_t *alloc_steps (int n);

/*!
    \brief função que adiciona o passo de pivotamento na estrutura
    \param pivot_steps Ponteiro para a estrutura de passos
    \param line  linha que vai ser trocada
    \param pivot pivo da troca
    \returns 0 em caso de sucesso. ALLOC_ERROR em caso de falha
*/
void add_pivot_step (pivot_steps_t *pivot_steps, int line, int pivot);

/*!
    \brief Função que aplica as etapas de pivotamento na Matriz indicada
    \param matrix Ponteiro para Matriz que será pivoteada
    \param steps Ponteiro para passos que serão aplicados
*/
void apply_pivot_steps (matrix_t *matrix, pivot_steps_t *steps);

/*!
    \brief Função que aplica as etapas de pivotamento na Matriz indicada trasposta
    \param matrix Ponteiro para Matriz que será pivoteada
    \param steps Ponteiro para passos que serão aplicados
*/
void apply_transpost_pivot_steps (matrix_t *matrix, pivot_steps_t *steps);

/*!
    \brief Função que realiza a troca da linha com a linha pivo
    \param matrix Ponteiro para a Matriz de execução
    \param line Linha atual
    \param pivot Posição do Pivo atual
*/
void swap_line (matrix_t *matrix, int line, int pivot);

/*!
    \brief Função que realiza a troca da linha com a linha pivo em uma matriz trasposta
    \param matrix Ponteiro para a Matriz de execução
    \param line Linha atual
    \param pivot Posição do Pivo atual
*/
void swap_transpost_line (matrix_t *matrix, int line, int pivot);

/*!
    \brief Libera o espaço alocado para o pivot_steps
    \param steps Ponteiro de acesso para lista de passos
*/
void free_steps (pivot_steps_t *steps);

#endif