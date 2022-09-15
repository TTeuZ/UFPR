#include "matrix.h"

matrix_t* alloc_matrix (unsigned int n) {
    int i, internal_n;
    double log_2;
    matrix_t *matrix = malloc (sizeof (matrix_t));

    if ( matrix ) {
        matrix->n = n;
        internal_n = n;

        log_2 = log10 (n) / log10 (2);
        if (fabs (ceil (log_2) - floor (log_2)) < DBL_EPSILON)
            internal_n++;

        matrix->coef = (double **) malloc (n * sizeof(double *));

        if (! (matrix->coef)) {
            free_matrix (matrix);
            return NULL;
        }

        // Matriz como vetor de N ponteiros para um único vetor com N*N elementos
        matrix->coef[0] = (double *) aligned_alloc (ALING_SIZE, n * n * sizeof(double));
        if (! (matrix->coef[0])) {
            free_matrix (matrix);
            return NULL;
        }
        for (i = 1; i < n; ++i) 
            matrix->coef[i] = matrix->coef[i-1]+n;
    }
    return matrix;
}

void free_matrix (matrix_t *matrix) {
    if (matrix) {
        if (matrix->coef) {
            if (matrix->coef[0]) free (matrix->coef[0]);
            free (matrix->coef);
        }
        free (matrix);
    }
}

void copy_matrix (matrix_t *restrict font, matrix_t *restrict target) {
    int line, col;

    for (line = 0; line < font->n; line++) {
        for (col = 0; col < font->n; col++)
            target->coef[line][col] = font->coef[line][col];
    }
}

void random_matrix (matrix_t *matrix, double coef_max) {
    unsigned int n = matrix->n;
    double invRandMax = ((double) coef_max / (double) RAND_MAX);

    for (unsigned int i=0; i<n; ++i) 
        for (unsigned int j=0; j<n; ++j)  
            matrix->coef[i][j] = (double) rand() * invRandMax;
}

void generate_identity_matrix (matrix_t *matrix) {
    int unroll_limit, size;
    int count;

    size = matrix->n;
    unroll_limit = size - (size % UNROLL_SIZE);

    memset (matrix->coef[0], 0.0, size * size * sizeof (double));
    for (count = 0; count < unroll_limit; count += UNROLL_SIZE) {
        matrix->coef[count][count] = 1.0;
        matrix->coef[count + 1][count + 1] = 1.0;
        matrix->coef[count + 2][count + 2] = 1.0;
        matrix->coef[count + 3][count + 3] = 1.0;
    }
    for (count = unroll_limit; count < size; count++)
        matrix->coef[count][count] = 1.0;
}

matrix_t *read_from_file (parser_t *parser) {
    matrix_t *matrix;
    FILE *input_file;
    int n, line, col;

    if (! (input_file = fopen (parser->input, "r"))) 
        return NULL;

    if (! (fscanf (input_file, "%d" , &n))) return NULL;
    if (! (matrix = alloc_matrix (n))) return NULL;

    for(line = 0; line < n; ++line)
        for (col = 0; col < n; ++col)
            if (! (fscanf (input_file, "%lg" , &matrix->coef[line][col]))) return NULL;

    fclose (input_file);
    return matrix;
}

matrix_t *read_from_terminal () {
    matrix_t *matrix;
    unsigned int n;
    int line, col;
    
    if (! (scanf ("%d",&n))) return NULL;
    if (! (matrix = alloc_matrix (n)))
        return NULL;
    
    for(line = 0; line < n; ++line)
        for (col = 0; col < n; ++col)
            if (! (scanf ("%lg", &matrix->coef[line][col]))) return NULL;

    return matrix;
}

int print_result (matrix_t *inv_matrix, double *norma_vet, double lu_time, double iter_time, double residue_time, parser_t *parser) {
    int count, size, line, col;
    FILE *p_output;

    size = inv_matrix->n;

    if (parser->output != NULL) {
        if (! (p_output = fopen (parser->output, "w"))) {
            return FILE_ERROR;
        }
        for (count = 0; count < parser->iterations; count++) 
            fprintf (p_output, "iter %d: <||%.15g||>\n", (count + 1), norma_vet[count]);

        fprintf (p_output, "\nTempo LU: %lg\n", lu_time);
        fprintf (p_output, "Tempo iter: %lg\n", iter_time);
        fprintf (p_output, "Tempo residue: %lg\n\n", residue_time);

        fprintf (p_output, "%d\n", size);
        for(line = 0; line < size; line++) {
            for(col = 0; col < size; col++)
                fprintf (p_output, "%.15g ", inv_matrix->coef[col][line]);
            fprintf (p_output, "\n");
        }
        fprintf (p_output,"\n\n");
        fclose (p_output);
    } else {
        for (count = 0; count < parser->iterations; count++) 
            fprintf (stdout, "iter %d: <||%.15g||>\n", (count + 1), norma_vet[count]);

        fprintf (stdout, "%d\n", size);
        for(line = 0; line < size; line++) {
            for(col = 0; col < size; col++)
                fprintf (stdout, "%.15g ", inv_matrix->coef[col][line]);
            fprintf (stdout, "\n");
        }
        fprintf (stdout,"\n\n");
    }
    return EXIT_SUCCESS;
}