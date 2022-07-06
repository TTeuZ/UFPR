#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "utils.h"
#include "sislin.h"
#include "Metodos.h"

int encontra_max (SistLinear_t *sisLin, int line) {
  int count, max_line;
  real_t iterator = sisLin->A[line][line];
  iterator = sisLin->A[line][line];
  max_line = line;

  for (count = line+1; count < sisLin->n; count++) 
    max_line = iterator > sisLin->A[line][count] ? max_line : count;
  return max_line;
}

int troca_linha (SistLinear_t *sisLin, int line, int line_pivo) {
  int count;
  real_t *temp, temp_b;
  if ((temp = malloc (sizeof(real_t) * sisLin->n))) {
    for (count = 0; count < sisLin->n; count++) {
      temp[count] = sisLin->A[count][line];
      sisLin->A[count][line] = sisLin->A[count][line_pivo];
      sisLin->A[count][line_pivo] = temp[count];
    }
    temp_b = sisLin->b[line];
    sisLin->b[line] = sisLin->b[line_pivo];
    sisLin->b[line_pivo] = temp_b;
    free (temp);
    return EXIT_SUCCESS;
  } else return OPE_ERROR;
}

int retros_subs (SistLinear_t *sisLin, real_t *x) {
  int line, col;
  for (line = sisLin->n-1; line >= 0; --line) {
    x[line] = sisLin->b[line];
    for (col = line+1; col <sisLin->n; ++col)
      x[line] -= sisLin->A[line][col] * x[col];
    x[line] /= sisLin->A[line][line];
    if (isnan (x[line]) || isinf (x[line])) 
      return OPE_ERROR;
  }
  return EXIT_SUCCESS;
}

/*!
  \brief Método da Eliminação de Gauss

  \param SL Ponteiro para o sistema linear
  \param x ponteiro para o vetor solução
  \param tTotal tempo total em milisegundos gastos pelo método

  \return código de erro. 0 em caso de sucesso.
*/
int eliminacaoGauss (SistLinear_t *sisLin, real_t *x, double *tTotal) {
  int line, line_pivo, col, i_line;
  real_t m;
  *tTotal = timestamp ();
  for (line = 0; line < sisLin->n; ++line) {
    line_pivo = encontra_max (sisLin, line);
    if (line != line_pivo)
      if (troca_linha (sisLin, line, line_pivo) == OPE_ERROR)
        return OPE_ERROR;

    for (i_line = line + 1; i_line < sisLin->n; ++i_line) {
      m = sisLin->A[i_line][line] / sisLin->A[line][line];
      if (isnan (m) || isinf (m)) 
        return OPE_ERROR;

      sisLin->A[i_line][line] = 0.0;
      for (col = line + 1; col < sisLin->n; ++col)
        sisLin->A[i_line][col] -= sisLin->A[line][col] * m;
      sisLin->b[i_line] -= sisLin->b[line] * m;
    }
  }
  if (retros_subs (sisLin,x) == OPE_ERROR)
    return OPE_ERROR;
  *tTotal = timestamp () - *tTotal;
  return EXIT_SUCCESS;
}

/*!
  \brief Essa função calcula a norma L2 do resíduo de um sistema linear 

  \param SL Ponteiro para o sistema linear
  \param x Solução do sistema linear
*/
real_t normaL2Residuo (SistLinear_t *sisLin) {
  int count;
  real_t norma = 0.0;
  for (count = 0; count < sisLin->n; count++) 
    norma += pow (sisLin->b[count], 2);
  return sqrt (norma);
}


/*!
  \brief Método de Gauss-Seidel

  \param SL Ponteiro para o sistema linear
  \param x ponteiro para o vetor solução
  \param erro menor erro aproximado para encerrar as iterações
  \param tTotal tempo total em milisegundos gastos pelo método

  \return código de erro. Um nr positivo indica sucesso e o nr
          de iterações realizadas. Um nr. negativo indica um erro.
  */
int gaussSeidel (SistLinear_t *sisLin, real_t *x, real_t erro, double *tTotal) {
  real_t actual_sol = 0.0;
  real_t stop = 100.0, max = 0.0; 
  int ite_count = 0.0;
  int line, col, count;
  *tTotal = timestamp ();

  while (ite_count < MAXIT && isgreater (stop, erro)) {
    max = 0.0;
    for (line = 0; line < sisLin->n; line++) {
      actual_sol = sisLin->b[line];
      for (col = 0; col < sisLin->n; col++) 
        if (col != line) 
          actual_sol -= sisLin->A[line][col] * x[col];

      actual_sol /= sisLin->A[line][line];
      if (isnan (actual_sol) || isinf (actual_sol)) 
        return OPE_ERROR;

      max = isgreater (ABS (actual_sol - x[line]), max) ? ABS (actual_sol - x[line]) : max;
      x[line] = actual_sol;
      actual_sol = 0.0;
    }
    stop = max;
    ite_count++;
  }

  *tTotal = timestamp () - *tTotal;
  return ite_count;
}


/*!
  \brief Método de Refinamento

  \param SL Ponteiro para o sistema linear
  \param actual_sol ponteiro para o vetor solução
  \param erro menor erro aproximado para encerrar as iterações
  \param tTotal tempo total em milisegundos gastos pelo método

  \return código de erro. Um nr positivo indica sucesso e o nr
          de iterações realizadas. Um nr. negativo indica um erro.
  */
int refinamento (SistLinear_t *sisLin, real_t *x, real_t erro, double *tTotal) {
  real_t gsTime, *temp_sol;
  real_t norma = 100.0;
  int ite_count = 0, line, col;
  *tTotal = timestamp ();

  if (! (temp_sol = malloc (sizeof (real_t) * sisLin->n)))
    return OPE_ERROR;

  for (int line = 0; line < sisLin->n; line++) {
    temp_sol[line] = 0;
    x[line] = 0;
  }

  while (ite_count < MAXIT && isgreater (norma, erro)) {
    if (gaussSeidel (sisLin, temp_sol, ERRO, &gsTime) == OPE_ERROR)
      return OPE_ERROR;
    
    for (line = 0; line < sisLin->n; line++) {
      x[line] += temp_sol[line];
      for (col = 0; col < sisLin->n; col++)
        sisLin->b[line] -= sisLin->A[line][col] * temp_sol[col];
    }

    norma = normaL2Residuo (sisLin);
    ite_count++;
  }

  *tTotal = timestamp () - *tTotal;
  free (temp_sol);
  return ite_count;
}

