#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "sislin.h"
#include "Metodos.h"

int main () {
  real_t *sol;
  SistLinear_t *sisLin, *sisLin2;
  double time;

  sisLin = alocaSisLin (5, pontVet);
  iniSisLin (sisLin, diagDominante, COEF_MAX);
  sol = malloc (sizeof (real_t) * 5);

  printf ("Para Eliminação de Gauss\n");
  prnSisLin (sisLin);
  eliminacaoGauss (sisLin, sol, &time);
  printf ("    ");
  for (int count = 0; count < 5; count++) 
    printf ("%f  ", sol[count]);
  printf ("\n");
  printf ("tempo: %f\n", time);


  sisLin2 = alocaSisLin (5, pontVet);
  iniSisLin (sisLin2, diagDominante, COEF_MAX);
  printf ("Para Gauss-Seidel\n");
  prnSisLin (sisLin2);
  for (int count = 0; count < 5; count++) 
    sol[count] = 0;
  gaussSeidel (sisLin2, sol, ERRO, &time);
  printf ("    ");
  for (int count = 0; count < 5; count++) 
    printf ("%f  ", sol[count]);
  printf ("\n");
  printf ("tempo: %f\n", time);

}