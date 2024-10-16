#ifndef __METHODS_H__
#define __METHODS_H__

#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "utils.h"
#include "steps.h"
#include "constants.h"


/*!
    \brief Fatoração LU
    a partir da input_matriz gera duas novas matrizes (L e U) utilizando Eliminação de Gauss
    com pivoteamento parcial.
    \param u_matrix Matriz enviada pelo usuário (Retorno)
    \param l_matrix Ponteiro para a matriz L (Retorno)
    \param lu_time tempo levado para executar a Fatoração LU (Retorno)
    \returns 0 em caso de sucesso. NAN_INF_ERROR ou INVERTIBLE_ERROR em caso de falha
*/
int lu_factorization (matrix_t *u_matrix, matrix_t *l_matrix, pivot_steps_t *pivot_steps, double *lu_time);

/*!
    \brief Refinamento
    Calcula o valor da matriz inversa por meio do refinamento do resultado a partir do resíduo
    \param input_matrix Matriz enviada pelo usuário
    \param l_matrix Ponteiro para a matriz L 
    \param u_matrix Ponteiro para a matriz U
    \param inv_matrix Ponteiro para a matriz inversa (Retorno)
    \param iterations Número de iterações fornecido pelo usuário
    \param iter_time tempo médio levado para executar a os passos do refinamento (Retorno)
    \param residue_time tempo médio levado para calcular o residuo
    \param norma_vet vetor de armazenamento das normas calculadas
    \returns 0 em caso de sucesso. NAN_INF_ERROR ou ALLOC_ERROR em caso de falha
*/
int matrix_refinement (matrix_t *inv_matrix, matrix_t *matrix, matrix_t *l_matrix, matrix_t *u_matrix, pivot_steps_t *steps, double *norma_vet, int iterations, double *iter_time, double *residue_time);

#endif