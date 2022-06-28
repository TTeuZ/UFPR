#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "utils.h"
#include "sislin.h"
#include "Metodos.h"

/*!
  \brief Método da Eliminação de Gauss

  \param SL Ponteiro para o sistema linear
  \param x ponteiro para o vetor solução
  \param tTotal tempo total em milisegundos gastos pelo método

  \return código de erro. 0 em caso de sucesso.
*/
int eliminacaoGauss (SistLinear_t *sisLin, real_t *x, double *tTotal) {
  int line, line_pivo;
  for (line = 0; line < sisLin->n; ++line) {
    prnSisLin (sisLin);
    // line_pivo = encontraMax (sisLin->A, line);
  }
  // for (int i = 0; i < SL->n; ++i) {
  //   int iPivo = encontraMax(SL->A, i);
  //   if (i != iPivo)
  //     trocaLinha (SL, i, iPivo);

  //   for (int k = i+1; k < SL->n; ++k) {
  //     double m = SL->A[k][i] / SL->A[i][i];
  //     SL->A[k][i] = 0.0;
  //     for (int j = i+1; j < SL->n; ++j)
  //       SL->A[k][j] -= SL->A[i][j] * m;
  //     SL->b[k] -= SL->b[i] * m;
  //   }
  // }
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

