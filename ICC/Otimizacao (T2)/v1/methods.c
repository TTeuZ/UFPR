#include "methods.h"

// --------------------------- Funções Internas ---------------------------
/*!
    \brief Função que encontra o valor máximo da coluna
    \param matrix Ponteiro para a Matriz
    \param line linha atual da execução da fatoração LU
    \return linha do pivo de maior valor
*/
int find_max (matrix_t *matrix, int line) {
    int count, max_line;
    double iterator;
    iterator = ABS (matrix->coef[line][line]);
    max_line = line;

    for (count = line + 1; count < matrix->n; count++) {
        max_line = iterator >= ABS (matrix->coef[count][line]) ? max_line : count;
        iterator = iterator >= ABS (matrix->coef[count][line]) ? iterator : ABS (matrix->coef[count][line]);
    }
    return max_line;
}

/*!
    \brief Função que realiza a troca da linha com a linha pivo
    \param matrix Ponteiro para a Matriz de execução
    \param line Linha atual
    \param pivot Posição do Pivo atual
*/
void swap_line (matrix_t *matrix, int line, int pivot) {
    double m_aux;
    int count;

    for (count = 0; count < matrix->n; count++) {
        m_aux = matrix->coef[line][count];
        matrix->coef[line][count] = matrix->coef[pivot][count];
        matrix->coef[pivot][count] = m_aux;
    }
}

/*!
    \brief função que adiciona o passo de pivotamento na estrutura
    \param pivot_steps Ponteiro para a estrutura de passos
    \param line  linha que vai ser trocada
    \param pivot pivo da troca
    \returns 0 em caso de sucesso. ALLOC_ERROR em caso de falha
*/
int add_pivot_step (pivot_steps_t *pivot_steps, int line, int pivot) {
    steps_t *step;

    if (! (step = malloc (sizeof (steps_t))))
        return ALLOC_ERROR;

    step->line = line;
    step->pivot = pivot;

    if (pivot_steps->qtd == 0) {
        if (! (pivot_steps->list = malloc (sizeof (steps_t))))
            return ALLOC_ERROR;
    } else {
        if (! (pivot_steps->list = realloc (pivot_steps->list, sizeof (steps_t) * (pivot_steps->qtd + 1))))
            return ALLOC_ERROR;
    }
    pivot_steps->list[pivot_steps->qtd] = step;
    pivot_steps->qtd++;
    return EXIT_SUCCESS;
}

/*!
    \brief Função que aplica as etapas de pivotamento na Matriz indicada
    \param matrix Ponteiro para Matriz que será pivoteada
    \param steps Ponteiro para passos que serão aplicados
*/
void apply_pivot_steps (matrix_t *matrix, pivot_steps_t *steps) {
    int count;
    for (count = 0; count < steps->qtd;count++) 
        swap_line (matrix, steps->list[count]->line, steps->list[count]->pivot);
}

/*!
    \brief função que calcula o determiante e retorna o seu valor
    \param matrix Matriz que vai ser calculada o determinante
    \returns valor do determinante
*/
double calc_determinant (matrix_t *matrix) {
    int count;
    double determinant = 1.0;

    for (count = 0; count < matrix->n; count++)
        determinant = determinant * matrix->coef[count][count];

    return determinant;
}

/*!
    \brief Função que calcula o valor do sistema linear de uma matriz triangular inferior
    \param l_matrix Ponteiro para a Matriz L
    \param b_matrix Ponteiro para a Matriz de termos independentes
    \param solution vetor com a solução da retrosubstituição
    \param ls_b coluna da Matriz identidade (B do sistema linear)
    \return 0 em caso de sucesso. NAN_INF_ERROR em caso de falha.
*/
int inv_retro_subs (matrix_t *l_matrix, matrix_t *b_matrix, double *solution, int ls_b) {    
    int line, col, size;

    size = l_matrix->n;

    for (line = 0; line < size; line++) {
        solution[line] = b_matrix->coef[line][ls_b];
        for (col = line - 1; col >= 0; col--) 
            solution[line] -= l_matrix->coef[line][col] * solution[col];
        solution[line] /= l_matrix->coef[line][line];
        // if (isnan (solution[line]) || isinf (solution[line]))
        //     return NAN_INF_ERROR;
    }
    return EXIT_SUCCESS;
}

/*!
    \brief Função que calcula o valor do sistema linear de uma matriz triangular superior
    \param u_matrix Ponteiro para a Matriz U
    \param inv_matrix Ponteiro para Matriz Inversa
    \param solution matrix com a solução da retrosubstituição anterior
    \param ls_b coluna da Matriz identidade (B do sistema linear)
    \return 0 em caso de sucesso. NAN_INF_ERROR em caso de falha.
*/
int retro_subs (matrix_t *u_matrix, matrix_t *inv_matrix, matrix_t *solution, int ls_b) {    
    int line, col, size;

    size = u_matrix->n;

    for (line = size - 1; line >= 0; line--) {
        inv_matrix->coef[line][ls_b] = solution->coef[line][ls_b];
        for (col = line + 1; col < size; col++) 
            inv_matrix->coef[line][ls_b] -= u_matrix->coef[line][col] * inv_matrix->coef[col][ls_b];
        inv_matrix->coef[line][ls_b] /= u_matrix->coef[line][line];
        // if (isnan (inv_matrix->coef[line][ls_b]) || isinf (inv_matrix->coef[line][ls_b]))
        //     return NAN_INF_ERROR;
    }
    return EXIT_SUCCESS;
}

/*!
    \brief Função que calcula a matrix de residuos do resultado
    \param residue_matrix Ponteiro para a Matriz de Residuos (Retorno)
    \param matrix Ponteiro para Matriz enviada pelo usuário
    \param inv_matrix Ponteiro para a Matriz inversa calculada
    \return 0 em caso de sucesso, ALLOC_ERROR em caso de falha de alocação
*/
void calc_residue (matrix_t *residue_matrix, matrix_t *matrix, matrix_t *inv_matrix) {
    int line, col, pivot_col, size;
    double temp = 0;

    size = matrix->n;
    generate_identity_matrix (residue_matrix);

    for (pivot_col = 0; pivot_col < size ; pivot_col++) {
        for (line = 0; line < size; line++) {
            for (col = 0; col < size; col++) 
                temp += matrix->coef[line][col] * inv_matrix->coef[col][pivot_col];
            residue_matrix->coef[line][pivot_col] -= temp;
            temp = 0;
        }
    }
}

/*!
    \brief Função que calcula a norma L2 do resíduo
    \param residue_matrix Ponteiro para a Matriz de resíduos
    \param residue_time tempo para calcular a norma do resíduo
    \return o valor da norma
*/
double calc_norma (matrix_t *residue_matrix, double *residue_time) {
    int line, col, size;
    double norma = 0.0;

    size = residue_matrix->n;

    *residue_time = timestamp ();
    for (line = 0; line < size; line++)
        for (col = 0; col < size; col++) 
            norma += pow (residue_matrix->coef[line][col], 2);

    *residue_time = timestamp () - *residue_time;
    return sqrt (norma);
}

// --------------------------- Funções Externas ---------------------------
int lu_factorization (matrix_t *u_matrix, matrix_t *l_matrix, pivot_steps_t *pivot_steps, double *lu_time) {
    int line, i_line, col, pivot, size;
    double m;

    size = u_matrix->n;
    for (line = 0; line < size; line++)
        for (col = 0; col < size; col++)
            l_matrix->coef[line][col] = 0.0;

    *lu_time = timestamp ();

    for (line = 0; line < size; line++) {
        pivot = find_max (u_matrix, line);
        if (line != pivot) {
            swap_line (u_matrix, line, pivot);
            swap_line (l_matrix, line, pivot);
            add_pivot_step (pivot_steps, line, pivot);
        }

        l_matrix->coef[line][line] = 1.0;
        for (i_line = line + 1; i_line < size; i_line++) {
            m = u_matrix->coef[i_line][line] / u_matrix->coef[line][line];
            // if (isnan (m) || isinf (m)) 
            //     return NAN_INF_ERROR;
            
            u_matrix->coef[i_line][line] = 0.0;
            l_matrix->coef[i_line][line] = m;
            for (col = line + 1; col < size; col++) 
                u_matrix->coef[i_line][col] -= u_matrix->coef[line][col] * m;
        }
    }
    *lu_time = timestamp () - *lu_time;

    // if (fabs (calc_determinant (u_matrix) - 0) < DBL_EPSILON)
    //     return INVERTIBLE_ERROR;

    return EXIT_SUCCESS;
}

int calc_inverse_matrix (matrix_t *inv_matrix, matrix_t *l_matrix, matrix_t *u_matrix, pivot_steps_t *steps) {
    matrix_t *i_matrix, *solution;
    double *temp_sol;
    int line, col;
    int count, sol_count; 
    int size;

    size = inv_matrix->n;

    if (! (i_matrix = alloc_matrix (size)) || ! (solution = alloc_matrix (size)))
        return ALLOC_ERROR;
    if (! (temp_sol = malloc (sizeof (double) * size))) 
        return ALLOC_ERROR;
    for (line = 0; line < size; line++) {
        temp_sol[line] = 0.0;
        for (col = 0; col < size; col++) 
            solution->coef[line][col] = 0.0;
    }
    generate_identity_matrix (i_matrix);

    LIKWID_MARKER_START ("retrosubs");
    apply_pivot_steps (i_matrix, steps);
    for (count = 0; count < size; count++) {
        // if (inv_retro_subs (l_matrix, i_matrix, temp_sol, count) == NAN_INF_ERROR)
        //     return NAN_INF_ERROR;
        inv_retro_subs (l_matrix, i_matrix, temp_sol, count);

        // adição da solução temporaria da execução do refinamento
        for (sol_count = 0; sol_count < size; sol_count++)
            solution->coef[sol_count][count] += temp_sol[sol_count];

        // if (retro_subs (u_matrix, inv_matrix, solution, count) == NAN_INF_ERROR)
        //     return NAN_INF_ERROR;
        retro_subs (u_matrix, inv_matrix, solution, count);
    }
    LIKWID_MARKER_STOP ("retrosubs");
    
    free_matrix (solution);
    free_matrix (i_matrix);
    free (temp_sol);
    return EXIT_SUCCESS;
}

int matrix_refinement (matrix_t *inv_matrix, matrix_t *matrix, matrix_t *l_matrix, matrix_t *u_matrix, pivot_steps_t *steps, double *norma_vet, int iterations, double *iter_time, double *residue_time) {
    matrix_t *residue_matrix, *solution;
    double act_iter_time, act_residue_time;
    double *temp_sol;
    int size, line, col, count, ls_count, sol_count;

    *iter_time = 0;
    *residue_time = 0;

    size = matrix->n;

    // Alocação e inicialização dos vetores/Matrizes internas
    if (! (solution = alloc_matrix (size)) || ! (residue_matrix = alloc_matrix (size)))
        return ALLOC_ERROR;
    if (! (temp_sol = malloc (sizeof (double) * size))) 
        return ALLOC_ERROR;
    for (line = 0; line < size; line++) {
        temp_sol[line] = 0.0;
        for (col = 0; col < size; col++) 
            solution->coef[line][col] = 0.0;
    }

    // passos do refinamento
    for (count = 0; count < iterations; count++) {
        LIKWID_MARKER_START ("calc-residue");
        calc_residue (residue_matrix, matrix, inv_matrix);
        LIKWID_MARKER_STOP ("calc-residue");
        
        apply_pivot_steps (residue_matrix, steps);

        act_iter_time = timestamp ();
        for (ls_count = 0; ls_count < size; ls_count++) {
            // if (inv_retro_subs (l_matrix, residue_matrix, temp_sol, ls_count) == NAN_INF_ERROR)
            //     return NAN_INF_ERROR;
            inv_retro_subs (l_matrix, residue_matrix, temp_sol, ls_count);

            // adição da solução temporaria da execução do refinamento
            for (sol_count = 0; sol_count < size; sol_count++)
                solution->coef[sol_count][ls_count] += temp_sol[sol_count];

            // if (retro_subs (u_matrix, inv_matrix, solution, ls_count) == NAN_INF_ERROR)
            //     return NAN_INF_ERROR;
            retro_subs (u_matrix, inv_matrix, solution, ls_count);
        }
        act_iter_time = timestamp () - act_iter_time;

        norma_vet[count] = calc_norma (residue_matrix, &act_residue_time);

        *residue_time += act_residue_time;
        *iter_time += act_iter_time;
    }

    *iter_time = *iter_time / count;
    *residue_time = *residue_time / count;

    free_matrix (solution);
    free_matrix (residue_matrix);
    free (temp_sol);
    return EXIT_SUCCESS;
}