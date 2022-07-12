#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "metods.h"
#include "edo.h"
#include "sisLin.h"
#include "utils.h"

double calc_norma (double *x, int n) {
  int count;
  double norma = 0.0;
  for (count = 0; count < n; count++) 
    norma += pow (x[count], 2);
  return sqrt (norma);
}

int vet_gauss_seidel (edo_h *edo, sl_tridiag *sislin, double *x, double *norma, double *time) {
    int count, line;
    double temp_x, *residue;

    *time = timestamp ();
    if ((residue = malloc (sizeof (double) * sislin->n))) {
        for (count = 0; count < 50; count++) {
            for (line = 0; line < sislin->n; line++) {
                temp_x = sislin->b[line];
                if (line == 0)  temp_x -= (sislin->ds[line] * x[line+1]);
                else if (line == sislin->n-1)  temp_x -= (sislin->di[line] * x[line-1]);
                else temp_x -= (sislin->ds[line] * x[line+1]) + (sislin->di[line] * x[line-1]);

                x[line] = temp_x / sislin->d[line];
                if (isnan (x[line]) || isinf (x[line])) 
                    return NAN_INF_ERROR;
            }
            
            for (line = 0; line < sislin->n; line++) {
                temp_x = sislin->b[line] - (sislin->d[line] * x[line]);
                if (line == 0)  temp_x -= (sislin->ds[line] * x[line+1]);
                else if (line == sislin->n-1)  temp_x -= (sislin->di[line] * x[line-1]);
                else temp_x -= (sislin->ds[line] * x[line+1]) + (sislin->di[line] * x[line-1]);
                residue[line] = temp_x;
            }
            *norma = calc_norma (residue, sislin->n);
        }
    } else return ALOC_ERROR;

    free (residue);
    *time = timestamp () - *time;
    return EXIT_SUCCESS;
}

int coef_gauss_seidel (edo_h *edo, double *x, double *norma, double *time) {
    int count, line;
	double h, xi, bi, d, di, ds;
    double *residue;

    *time = timestamp ();
    if ((residue = malloc (sizeof (double) * edo->n))) {
        h = (edo->b - edo->a) / (edo->n + 1);
        for (count = 0; count < 50; count++) {
            for (line = 0; line < edo->n; line++) {
                xi = edo->a + (line+1)*h;
                bi = h*h * edo->r(xi);
                di = 1 - h * edo->p(xi)/2.0;
                d = -2 + h*h * edo->q(xi);
                ds = 1 + h * edo->p(xi)/2.0;

                if (line == 0) bi -= edo->ya * (1 - h*edo->p(edo->a+h)/2.0) + (ds * x[line+1]);
                else if (line == edo->n-1) bi -= edo->yb * (1 + h*edo->p(edo->b-h)/2.0) + (di * x[line-1]);
                else bi -= ds * x[line+1] + di * x[line-1];

                x[line] = bi / d;
                if (isnan (x[line]) || isinf (x[line])) 
                    return NAN_INF_ERROR;
            }
            *norma = calc_norma (residue, edo->n);
        }
    } else return ALOC_ERROR;

    *time = timestamp () - *time;
    return EXIT_SUCCESS;
}