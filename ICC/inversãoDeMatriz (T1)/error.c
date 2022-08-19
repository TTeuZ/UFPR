#include "error.h"

void emit_error (int error_code, parser_t *parser, double *norma_vet, matrix_t *input_matrix, matrix_t *l_matrix, matrix_t *u_matrix, matrix_t *inv_matrix, pivot_steps_t *pivot_steps) {
    // Verifica se cada parametro é diferente de null, se for, chama a função de clean
    if (input_matrix) free_matrix (input_matrix);
    if (l_matrix) free_matrix (l_matrix);
    if (u_matrix) free_matrix (u_matrix);
    if (inv_matrix) free_matrix (inv_matrix);
    if (norma_vet) free (norma_vet);
    if (parser) free (parser);
    if (pivot_steps) free_steps (pivot_steps);

    // Emit da mensagem de erro
    switch (error_code) {
        case ALLOC_ERROR:
            fprintf (stderr, "Erro de alocação de memoria!\n\n");
        break;
        case NAN_INF_ERROR:
            fprintf (stderr, "Nan ou Inf na resolução da inversa!\n\n");
        break;
        case INVERTIBLE_ERROR:
            fprintf (stderr, "Matriz não invertivel!\n\n");
        break;
    }
}