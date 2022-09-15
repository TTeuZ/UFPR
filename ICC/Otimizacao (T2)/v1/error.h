#ifndef __ERROR_H__
#define __ERROR_H__

#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "parser.h"
#include "steps.h"
#include "matrix.h"

/*!
    \brief Função de exibição de erro em caso de falha no código.
    Realiza as limpezas de memoria.
    \param error_code Código de erro
    \param parser Ponteiro para o parser
    \param norma_vet Ponteiro para o vetor das normas
    \param input_matrix Ponteiro para a matriz de entrada
    \param inv_matrix Ponteiro para a matriz inversa
    \param l_matrix Ponteiro para a matriz L
    \param u_matrix Ponteiro para a matriz U
    \param pivot_steps Ponteiro para o vetor de passos do pivotamento
    
*/
void emit_error (int error_code, parser_t *parser, double *norma_vet, matrix_t *input_matrix, matrix_t *l_matrix, matrix_t *u_matrix, matrix_t *inv_matrix, pivot_steps_t *pivot_steps);
#endif
