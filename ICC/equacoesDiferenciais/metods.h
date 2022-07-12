#include "edo.h"
#include "sisLin.h"

#ifndef __METODS_H__
#define __METODS_H__

#define MAX_ITE 50

// Erros
#define NAN_INF_ERROR -1
#define ALOC_ERROR -2

/*!
    \brief Método de solução do sistema linear tridiagonal por meio de Gauss-Seidel utilizando
    os vetores do sistema linear
    \param edo Estrutura de dados do EDO
    \param sislin Estrutura de dados do Sistema Linear Tridiagonal
    \param x Vetor das soluções do Sistema linear Tridiagonal
    \param norma Valor da norma L2 do residuo da solução do Sistema linear
    \param time tempo que foi necessário para executar a solução
*/
int vet_gauss_seidel (edo_h *edo, sl_tridiag *sislin, double *x, double *norma, double *time);

/*!
    \brief Método de solução do sistema linear tridiagonal por meio de Gauss-Seidel utilizando
    o calculo do coeficiente diretamente na resolução
    \param edo Estrutura de dados do EDO
    \param x Vetor das soluções do Sistema linear Tridiagonal
    \param norma Valor da norma L2 do residuo da solução do Sistema linear
    \param time tempo que foi necessário para executar a solução
*/
int coef_gauss_seidel (edo_h *edo, double *x, double *norma, double *time);

#endif