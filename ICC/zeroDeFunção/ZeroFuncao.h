#ifndef __ZEROFUNCAO_H__
#define __ZEROFUNCAO_H__

#include <float.h>

// Aproximação aceitável como valor zero
#define ZERO DBL_EPSILON

// Parâmetros para teste de convergência
#define MAXIT 500
#define EPS 1.0e-8

typedef struct {
  double *p;
  int n;
} Polinomio;

// ALocação de Polinônimos
Polinomio *aloc_polinomio (int n);
Polinomio *read_polinomio ();
void free_polinomio (Polinomio *p);

// Métodos
double bisseccao (Polinomio *p, double a, double b, double eps, int *it, double *raiz, int type);
double newtonRaphson (Polinomio *p, double x0, double eps, int *it, double *raiz, int type);
double secante (Polinomio *p, double x0, double x1, double eps, int *it, double *raiz, int type);

// Cálculo de Polinômios
void calcPolinomio_rapido(Polinomio *p, double x, double *px, double *dpx );
void calcPolinomio_lento(Polinomio *p, double x, double *px, double *dpx );

#endif // __ZEROFUNCAO_H__

