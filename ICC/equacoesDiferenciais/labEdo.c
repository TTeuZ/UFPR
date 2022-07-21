#include <stdio.h>
#include <stdlib.h>

#include "edo.h"
#include "sisLin.h"
#include "metods.h"
#include "coefficients.h"
#include "utils.h"

#define TEST_SIZE 3

int main () {
    edo_h *edo;
    sl_tridiag *sislin;
    double *x;
    double norma, vet_gs_time, coef_gs_time;
    int tests[TEST_SIZE] = {5, 10, 100};
    int count, i_count;
    
    if (! (edo = aloc_edo ())) {
        fprintf (stdout, "Erro de alocação de memôria!\n");
        return EXIT_FAILURE;
    }

    for (count = 0; count < TEST_SIZE; count++) {
        // primeira equação diferencial y'' = 6x - 0.5^2 x E (0,12), y(0) = 0, y(12) = 0;
        set_edo_conditions (edo, 0, 12, 0, 0);
        set_edo_coefficients (edo, p1, q1, r1);

        fprintf (stdout, "Aplicando para n = %d na primeira equação\n\n", tests[count]);
        set_edo_mesh (edo, tests[count]);

        if ((sislin = aloc_sislin (tests[count]))) {
            build_tridiag (edo, sislin);
            print_sislin (sislin);

            if ((x = malloc (sizeof (double) * tests[count]))) {
                fprintf (stdout, "Método vet-gauss-seidel\n");
                for (i_count = 0; i_count < tests[count]; i_count++)
                    x[i_count] = 0;
                if (vet_gauss_seidel (edo, sislin, x, &norma, &vet_gs_time) == 0) {
                    fprintf (stdout, "Solução: ");
                    print_vet (x, tests[count]);
                    fprintf (stdout, "Norma: %f\n", norma);
                    fprintf (stdout, "Tempo: %f\n\n", vet_gs_time);
                } else fprintf (stdout, "Erro - vet_gauss-seidel - primeira equação - n = %d\n\n", tests[count]);
                
                fprintf (stdout, "Método coef-gauss-seidel\n");
                for (i_count = 0; i_count < tests[count]; i_count++)
                    x[i_count] = 0;
                if (coef_gauss_seidel (edo, x, &norma, &coef_gs_time) == 0) {
                    fprintf (stdout, "Solução: ");
                    print_vet (x, tests[count]);
                    fprintf (stdout, "Norma: %f\n", norma);
                    fprintf (stdout, "Tempo: %f\n", coef_gs_time);
                } else fprintf (stdout, "Erro - coef_gauss-seidel - primeira equação - n = %d\n\n", tests[count]);

                free (x);
            } else {
                fprintf (stdout, "Erro de alocação para a primeira equação - n = %d\n\n", tests[count]);
                free_sislin (sislin);
            }
            free_sislin (sislin);
        } else fprintf (stdout, "Erro de alocação para a primeira equação - n = %d\n\n", tests[count]);

        // segunda equação diferencial y'' + y = 0
        set_edo_conditions (edo, 0, 1, 0, 1);
        set_edo_coefficients (edo, p2, q2, r2);

        fprintf (stdout, "Aplicando para n = %d na segunda equação\n\n", tests[count]);
        set_edo_mesh (edo, tests[count]);

        if ((sislin = aloc_sislin (tests[count]))) {
            build_tridiag (edo, sislin);
            print_sislin (sislin);

            if ((x = malloc (sizeof (double) * tests[count]))) {
                fprintf (stdout, "Método vet-gauss-seidel\n");
                for (i_count = 0; i_count < tests[count]; i_count++)
                    x[i_count] = 0;
                if (vet_gauss_seidel (edo, sislin, x, &norma, &vet_gs_time) == 0) {
                    fprintf (stdout, "Solução: ");
                    print_vet (x, tests[count]);
                    fprintf (stdout, "Norma: %f\n", norma);
                    fprintf (stdout, "Tempo: %f\n\n", vet_gs_time);
                } else fprintf (stdout, "Erro - vet_gauss-seidel - segunda equação - n = %d\n\n", tests[count]);
                
                fprintf (stdout, "Método coef-gauss-seidel\n");
                for (i_count = 0; i_count < tests[count]; i_count++)
                    x[i_count] = 0;
                if (coef_gauss_seidel (edo, x, &norma, &coef_gs_time) == 0) {
                    fprintf (stdout, "Solução: ");
                    print_vet (x, tests[count]);
                    fprintf (stdout, "Norma: %f\n", norma);
                    fprintf (stdout, "Tempo: %f\n", coef_gs_time);
                } else fprintf (stdout, "Erro - coef_gauss-seidel - segunda equação - n = %d\n\n", tests[count]);

                free (x);
            } else {
                fprintf (stdout, "Erro de alocação para a segunda equação - n = %d\n\n", tests[count]);
                free_sislin (sislin);
            }
            free_sislin (sislin);
        } else fprintf (stdout, "Erro de alocação para a segunda equação - n = %d\n\n", tests[count]);

        // terceira equação diferencial y'' + (x+1)y' - 2y = (1-x^2)e^-x
        set_edo_conditions (edo, 0, 1, -1, 0);
        set_edo_coefficients (edo, p3, q3, r3);

        fprintf (stdout, "Aplicando para n = %d na terceira equação\n\n", tests[count]);
        set_edo_mesh (edo, tests[count]);

        if ((sislin = aloc_sislin (tests[count]))) {
            build_tridiag (edo, sislin);
            print_sislin (sislin);

            if ((x = malloc (sizeof (double) * tests[count]))) {
                fprintf (stdout, "Método vet-gauss-seidel\n");
                for (i_count = 0; i_count < tests[count]; i_count++)
                    x[i_count] = 0;
                if (vet_gauss_seidel (edo, sislin, x, &norma, &vet_gs_time) == 0) {
                    fprintf (stdout, "Solução: ");
                    print_vet (x, tests[count]);
                    fprintf (stdout, "Norma: %f\n", norma);
                    fprintf (stdout, "Tempo: %f\n\n", vet_gs_time);
                } else fprintf (stdout, "Erro - vet_gauss-seidel - terceira equação - n = %d\n\n", tests[count]);
                
                fprintf (stdout, "Método coef-gauss-seidel\n");
                for (i_count = 0; i_count < tests[count]; i_count++)
                    x[i_count] = 0;
                if (coef_gauss_seidel (edo, x, &norma, &coef_gs_time) == 0) {
                    fprintf (stdout, "Solução: ");
                    print_vet (x, tests[count]);
                    fprintf (stdout, "Norma: %f\n", norma);
                    fprintf (stdout, "Tempo: %f\n", coef_gs_time);
                } else fprintf (stdout, "Erro - coef_gauss-seidel - terceira equação - n = %d\n\n", tests[count]);

                free (x);
            } else {
                fprintf (stdout, "Erro de alocação para a terceira equação - n = %d\n\n", tests[count]);
                free_sislin (sislin);
            }
            free_sislin (sislin);
        } else fprintf (stdout, "Erro de alocação para a terceira equação - n = %d\n\n", tests[count]);
    }

    free (edo);
    return EXIT_SUCCESS;
}