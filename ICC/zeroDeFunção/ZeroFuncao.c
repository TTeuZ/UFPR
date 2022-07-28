#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "ZeroFuncao.h"

Polinomio *aloc_polinomio (int n) {
	Polinomio *p;
	if ((p = malloc (sizeof (Polinomio) * n))) {
		p->p = NULL;
		p->n = n;
		return p;
	} else return NULL;
}

Polinomio *read_polinomio (){
	Polinomio *p;
	int n, count;

	fprintf (stdout, "Informe o grau do polinomio: \n");
	scanf ("%d", &n);

	if (! (p = aloc_polinomio (n))) 
		return NULL;

	fprintf (stdout, "Informe os coeficientes do polinomio: \n");
	for (count = 0; count <= n; count++)
		scanf ("%lg", &p->p[count]);

	return p;
}

void free_polinomio (Polinomio *p) {
	free (p->p);
	free (p);
}

double bisseccao (Polinomio *p, double a, double b, double eps, int *it, double *raiz, int type) {
	double root, actual_xm, old_xm, error;
	double fa, fxm, trash;
	int count;

	actual_xm = (a + b) / 2;

	if (type) {
		calcPolinomio_rapido (p, a, &fa, &trash);
		calcPolinomio_rapido (p, actual_xm, &fxm, &trash);
	} else {
		calcPolinomio_lento (p, a, &fa, &trash);
		calcPolinomio_lento (p, actual_xm, &fxm, &trash);
	}

	if (fa * fxm < 0) b = actual_xm;
	else a = actual_xm;

	do {
		old_xm = actual_xm;
		actual_xm = (a + b) / 2;

		if (type) {
			calcPolinomio_rapido (p, a, &fa, &trash);
			calcPolinomio_rapido (p, a, &fxm, &trash);
		} else {
			calcPolinomio_lento (p, actual_xm, &fa, &trash);
			calcPolinomio_lento (p, actual_xm, &fxm, &trash);
		}

		if (fa * fxm < 0) b = actual_xm;
		else a = actual_xm;

		error = fabs ((actual_xm - old_xm) / actual_xm);
		count++;
	} while ( count < MAXIT && error > EPS);

	*raiz = actual_xm;
	*it = count;
	return error;
}

double newtonRaphson (Polinomio *p, double x0, double eps, int *it, double *raiz, int type) {

}

double secante (Polinomio *p, double x0, double x1, double eps, int *it, double *raiz, int type) {

}

void calcPolinomio_rapido(Polinomio *p, double x, double *px, double *dpx) {
	double temp_x, temp_dx;
	int count;
	for (count = p->n; count > 0; count--) {
		temp_x = temp_x*x + p->p[count];
		temp_dx = temp_dx*x + temp_x;
	}
	temp_x = temp_x*x + p->p[0];
	*px = temp_x;
	*dpx = temp_dx;
}

void calcPolinomio_lento(Polinomio *p, double x, double *px, double *dpx) {
	
}
