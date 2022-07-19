#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "ZeroFuncao.h"

Polinomio *aloc_polinomio (int n) {
	Polinomio *p;
	if (! (p = malloc (sizeof (Polinomio) * n))) {
		p->p = NULL;
		p->n = n;
		return p;
	} else return NULL;
}

void free_polinomio (Polinomio *p) {
	free (p->p);
	free (p);
}

double bisseccao (Polinomio *p, double a, double b, double eps, int *it, double *raiz) {

}

double newtonRaphson (Polinomio *p, double x0, double eps, int *it, double *raiz) {

}

double secante (Polinomio *p, double x0, double x1, double eps, int *it, double *raiz) {

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
