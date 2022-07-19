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

    if (! (residue = malloc (sizeof (double) * sislin->n))) 
        return ALOC_ERROR;

    *time = timestamp ();
    for (count = 0; count < 50; count++) {
        for (line = 0; line < sislin->n; line++) {
            temp_x = sislin->b[line];
            if (line == 0)  temp_x -= (sislin->ds[line] * x[line+1]);
            else if (line == sislin->n-1) temp_x -= (sislin->di[line] * x[line-1]);
            else temp_x -= (sislin->ds[line] * x[line+1]) + (sislin->di[line] * x[line-1]);

            x[line] = temp_x / sislin->d[line];
            if (isnan (x[line]) || isinf (x[line])) 
                return NAN_INF_ERROR;
        }
            
        for (line = 0; line < sislin->n; line++) {
            temp_x = sislin->b[line] - (sislin->d[line] * x[line]);
            if (line == 0)  temp_x -= (sislin->ds[line] * x[line+1]);
            else if (line == sislin->n-1) temp_x -= (sislin->di[line] * x[line-1]);
            else temp_x -= (sislin->ds[line] * x[line+1]) + (sislin->di[line] * x[line-1]);
            residue[line] = temp_x;
        }
        *norma = calc_norma (residue, sislin->n);
    }

    free (residue);
    *time = timestamp () - *time;
    return EXIT_SUCCESS;
}

int coef_gauss_seidel (edo_h *edo, double *x, double *norma, double *time) {
    int count, line;
	double h, xi, bi, d, di, ds, temp_x;
    double *residue, *b_vet, *di_vet, *d_vet, *ds_vet;

    if (! (b_vet =  malloc (sizeof (double) * edo->n))) 
        return ALOC_ERROR;
    if (! (di_vet =  malloc (sizeof (double) * edo->n))) 
        return ALOC_ERROR;
    if (! (d_vet =  malloc (sizeof (double) * edo->n))) 
        return ALOC_ERROR;
    if (! (ds_vet =  malloc (sizeof (double) * edo->n))) 
        return ALOC_ERROR;
    if (! (residue = malloc (sizeof (double) * edo->n))) 
        return ALOC_ERROR;

    *time = timestamp ();
    h = (edo->b - edo->a) / (edo->n + 1);
    for (count = 0; count < 50; count++) {
        for (line = 0; line < edo->n; line++) {
            xi = edo->a + (line+1)*h;
            bi = h*h * edo->r(xi);
            di = 1 - h * edo->p(xi)/2.0;
            d = -2 + h*h * edo->q(xi);
            ds = 1 + h * edo->p(xi)/2.0;

            if (count == 0) {
                b_vet[line] = bi;
                di_vet[line] = di;
                d_vet[line] = d;
                ds_vet[line] = ds;
            }

            if (line == 0) bi -= edo->ya * (1 - h*edo->p(edo->a+h)/2.0) + (ds * x[line+1]);
            else if (line == edo->n-1) bi -= edo->yb * (1 + h*edo->p(edo->b-h)/2.0) + (di * x[line-1]);
            else bi -= ds * x[line+1] + di * x[line-1];

            x[line] = bi / d;
            if (isnan (x[line]) || isinf (x[line])) 
                return NAN_INF_ERROR;
        }

        for (line = 0; line < edo->n; line++) {
            temp_x = b_vet[line] - (d_vet[line] * x[line]);
            if (line == 0)  temp_x -= (ds_vet[line] * x[line+1]);
            else if (line == edo->n-1) temp_x -= (di_vet[line] * x[line-1]);
            else temp_x -= (ds_vet[line] * x[line+1]) + (di_vet[line] * x[line-1]);
            residue[line] = temp_x;
        }
        *norma = calc_norma (residue, edo->n);
    }

    *time = timestamp () - *time;
    return EXIT_SUCCESS;
}