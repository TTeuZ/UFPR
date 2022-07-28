#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"
#include "ZeroFuncao.h"

int main () {;
  Polinomio *polinomio;
  double a, b, x0, x1;
  int count;

  polinomio = read_polinomio ();

  fprintf (stdout, "Informe os limites inicias para o método da Bissecção: \n");
  scanf ("%lg %lg", &a, &b);
  fprintf (stdout, "Informe os chutes inicias para o método de Newton-Raphson e Secante: \n");
  scanf ("%lg %lg", &x0, &x1);

  printf ("batata\n");

  free_polinomio (polinomio);
  return 0;
}

