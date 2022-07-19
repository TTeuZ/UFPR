#include <stdio.h>
#include <stdlib.h>

#include "sisLin.h"

sl_tridiag *aloc_sislin (int n) {
    sl_tridiag *sislin;

    if ((sislin = malloc (sizeof (sl_tridiag)))) {
        sislin->n = n;

        if (! (sislin->d = malloc (sizeof (double) * n))) {
            free (sislin);
            return NULL;
        }
        if (! (sislin->di = malloc (sizeof (double) * n))) {
            free (sislin->d);
            free (sislin);
            return NULL;
        }
        if (! (sislin->ds = malloc (sizeof (double) * n))) {
            free (sislin->d);
            free (sislin->di);
            free (sislin);
            return NULL;
        }
        if (! (sislin->b = malloc (sizeof (double) * n))) {
            free (sislin->d);
            free (sislin->di);
            free (sislin->ds);
            free (sislin);
            return NULL;
        }

        return sislin;
    } else return NULL;
}

void free_sislin (sl_tridiag *sislin) {
    free (sislin->di);
    free (sislin->d);
    free (sislin->ds);
    free (sislin->b);
    free (sislin);
}

void build_tridiag (edo_h *edo, sl_tridiag *sislin) {
    double xi, h;
    int count;
	h = (edo->b - edo->a) / (edo->n+1.0);
	for (count = 0; count < edo->n; count++) {
		xi = edo->a + (count+1)*h;
		sislin->di[count] = 1 - h * edo->p(xi)/2.0;
		sislin->d[count] = -2 + h*h * edo->q(xi);
		sislin->ds[count] = 1 + h * edo->p(xi)/2.0;
		sislin->b[count] = h*h * edo->r(xi);
	}
	sislin->b[0] -= edo->ya * (1 - h*edo->p(edo->a+h)/2.0);
	sislin->b[edo->n-1] -= edo->yb * (1 + h*edo->p(edo->b-h)/2.0);
}

void print_sislin (sl_tridiag *sislin) {
  int line, col;
  int d_pivo = 0, di_pivo = 0, ds_pivo = 1;
  for(line = 0; line < sislin->n; line++) {
    printf("\n  ");
    for(col = 0; col < sislin->n; col++) {
        if (col == d_pivo) printf ("%10g", sislin->d[col]);
        else if (col == ds_pivo) printf ("%10g", sislin->ds[col]);
        else if (col == di_pivo) printf ("%10g", sislin->di[col]);
        else printf ("%10d", 0);
    }
    printf ("   |   %g", sislin->b[line]);
    d_pivo++;
    ds_pivo++;
    if (line != 0) di_pivo++;
  }
  printf("\n\n");

}