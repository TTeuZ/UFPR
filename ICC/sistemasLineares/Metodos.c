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

void troca_linha (SistLinear_t *sisLin, int line, int line_pivo) {
  int count;
  real_t *temp, temp_b;
  printf("dentro do troca de linha\n");
  prnSisLin (sisLin);

  if (temp = malloc (sizeof(real_t) * sisLin->n)) {
    for (count = 0; count < sisLin->n; count++) {
      temp[count] = sisLin->A[count][line];
      sisLin->A[count][line] = sisLin->A[count][line_pivo];
      sisLin->A[count][line_pivo] = temp[count];
    }
    temp_b = sisLin->b[line];
    sisLin->b[line] = sisLin->b[line_pivo];
    sisLin->b[line_pivo] = temp_b;
    free (temp);
  }
}

void retros_subs (SistLinear_t *sisLin, real_t *x) {
  int line, col;
  for (line = sisLin->n-1; line >= 0; --line) {
    x[line] = sisLin->b[line];
    for (col = line+1; col <sisLin->n; ++col)
      x[line] -= sisLin->A[line][col] *x[col];
    x[line] /= sisLin->A[line][line];
  }
}

/*!
  \brief Método da Eliminação de Gauss

  \param SL Ponteiro para o sistema linear
  \param x ponteiro para o vetor solução
  \param tTotal tempo total em milisegundos gastos pelo método

  \return código de erro. 0 em caso de sucesso.
*/
int eliminacaoGauss (SistLinear_t *sisLin, real_t *x, double *tTotal) {
  int line, line_pivo, i_line, col;
  real_t m;
  *tTotal = timestamp ();
  prnSisLin (sisLin);
  for (line = 0; line < sisLin->n; ++line) {
    line_pivo = encontra_max (sisLin, line);
    if (line != line_pivo)
      troca_linha (sisLin, line, line_pivo);

    for (col = line + 1; col < sisLin->n; ++col) {
      m = sisLin->A[col][line] / sisLin->A[line][line];
      sisLin->A[col][line] = 0.0;
      for (i_line = line + 1; i_line < sisLin->n; ++i_line)
        sisLin->A[col][i_line] -= sisLin->A[line][i_line] * m;
      sisLin->b[col] -= sisLin->b[line] * m;
    }
  }
  prnSisLin (sisLin);
  retros_subs (sisLin,x);
  *tTotal = timestamp () - *tTotal;
}

/*!
  \brief Essa função calcula a norma L2 do resíduo de um sistema linear 

  \param SL Ponteiro para o sistema linear
  \param x Solução do sistema linear
*/
real_t normaL2Residuo(SistLinear_t *SL, real_t *x) {
  
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
int gaussSeidel (SistLinear_t *SL, real_t *x, real_t erro, double *tTotal) {
  
}


/*!
  \brief Método de Refinamento

  \param SL Ponteiro para o sistema linear
  \param x ponteiro para o vetor solução
  \param erro menor erro aproximado para encerrar as iterações
  \param tTotal tempo total em milisegundos gastos pelo método

  \return código de erro. Um nr positivo indica sucesso e o nr
          de iterações realizadas. Um nr. negativo indica um erro.
  */
int refinamento (SistLinear_t *SL, real_t *x, real_t erro, double *tTotal) {

}

