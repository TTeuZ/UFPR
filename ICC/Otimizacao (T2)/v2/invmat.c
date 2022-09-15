#include <likwid.h>

#include "matrix.h"
#include "utils.h"
#include "methods.h"
#include "parser.h"
#include "error.h"
#include "constants.h"

int main (int argc, char *argv[]) {
    parser_t *parser;
    matrix_t *input_matrix, *l_matrix, *u_matrix, *inv_matrix;
    pivot_steps_t *pivot_steps;
    double lu_time, iter_time, residue_time;
    double *norma_vet;
    int error = 0;

    srand (20221);

    LIKWID_MARKER_INIT;

    if (! (parser = init_parser ())) {
        fprintf (stderr, "Erro de alocação para a estrutura do parser!\n");
        return EXIT_FAILURE;
    }
    if (parse_input (parser, argc, argv) == MISSING_REQUIRED_ARG_ERROR) {
        fprintf (stderr, "Faltando arqumento obrigatório '-i' numero de iterações\n");
        free (parser);
        return EXIT_FAILURE;
    }
    
    // Caso o parametro n for mandado, gera uma matriz aleatoria
    if (parser->n != -1) {
        if (! (input_matrix = alloc_matrix (parser->n))) error = ALLOC_ERROR;
        else random_matrix (input_matrix, COEF_MAX);
    } else {
        // Verifica se a leitura vai ser da stdin ou do arquivo
        if (parser->input != NULL) {
            if (! (input_matrix = read_from_file (parser))) error = ALLOC_ERROR;
        } else {
            if (! (input_matrix = read_from_terminal ())) error = ALLOC_ERROR;
        }
    }

    // Aloca as estruturas necessárias
    if (! (norma_vet = malloc (sizeof (double) * parser->iterations))) error = ALLOC_ERROR;
    if (! (l_matrix = alloc_matrix (input_matrix->n))) error = ALLOC_ERROR;
    if (! (u_matrix = alloc_matrix (input_matrix->n))) error = ALLOC_ERROR;
    if (! (inv_matrix = alloc_matrix (input_matrix->n))) error = ALLOC_ERROR;
    if (error != 0) {
        emit_error (error, parser, norma_vet, input_matrix, l_matrix, u_matrix, inv_matrix, NULL);
        return EXIT_FAILURE;
    }

    copy_matrix (input_matrix, u_matrix);

    if (! (pivot_steps = alloc_steps (input_matrix->n))) error = ALLOC_ERROR;
    if (error != 0) {
        emit_error (error, parser, norma_vet, input_matrix, l_matrix, u_matrix, inv_matrix, pivot_steps);
        return EXIT_FAILURE;
    }
    
    LIKWID_MARKER_START ("lu-factorization");
    // Processo de calculo da inversa
    error = lu_factorization (u_matrix, l_matrix, pivot_steps, &lu_time);
    LIKWID_MARKER_STOP ("lu-factorization");
    
    // if (error != 0) {
    //     emit_error (error, parser, norma_vet, input_matrix, l_matrix, u_matrix, inv_matrix, pivot_steps);
    //     return EXIT_FAILURE;
    // }

    error = calc_inverse_matrix (inv_matrix, l_matrix, u_matrix, pivot_steps);
    // if (error != 0) {
    //     emit_error (error, parser, norma_vet, input_matrix, l_matrix, u_matrix, inv_matrix, pivot_steps);
    //     return EXIT_FAILURE;
    // }

    error = matrix_refinement (inv_matrix, input_matrix, l_matrix, u_matrix, pivot_steps, norma_vet, parser->iterations, &iter_time, &residue_time);
    // if (error != 0) {
    //     emit_error (error, parser, norma_vet, input_matrix, l_matrix, u_matrix, inv_matrix, pivot_steps);
    //     return EXIT_FAILURE;
    // }

    // print_result (inv_matrix, norma_vet, lu_time, iter_time, residue_time, parser);

    LIKWID_MARKER_CLOSE;

    free (parser);
    free (norma_vet);
    free_matrix (input_matrix);
    free_matrix (inv_matrix);
    free_matrix (l_matrix);
    free_matrix (u_matrix);
    free_steps (pivot_steps);
    return EXIT_SUCCESS;
}