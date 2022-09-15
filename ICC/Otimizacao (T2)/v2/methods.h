#ifndef __METHODS_H__
#define __METHODS_H__

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>
#include <immintrin.h>
#include <likwid.h>

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
int lu_factorization (matrix_t *restrict u_matrix, matrix_t *restrict l_matrix, pivot_steps_t *pivot_steps, double *lu_time);


/*!
    \brief Calcula a primeira versao da matris inversa
    \param inv_matrix Ponteiro para a matriz inversa (Retorno)
    \param l_matrix Ponteiro para a matriz L 
    \param u_matrix Ponteiro para a matriz U
    \param pivot_steps Ponteiro para a estrutura de passos de pivotamento
    \returns 0 em caso de sucesso. NAN_INF_ERROR ou ALLOC_ERROR em caso de falha
*/
int calc_inverse_matrix (matrix_t *restrict inv_matrix, matrix_t *restrict l_matrix, matrix_t *restrict u_matrix, pivot_steps_t *steps);

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
int matrix_refinement (matrix_t *restrict inv_matrix, matrix_t *restrict matrix, matrix_t *restrict l_matrix, matrix_t *restrict u_matrix, pivot_steps_t *steps, double *restrict norma_vet, int iterations, double *restrict iter_time, double *restrict residue_time);

#endif