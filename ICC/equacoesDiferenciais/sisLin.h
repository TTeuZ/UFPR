#include "edo.h"

#ifndef __SISLIN_H__
#define __SISLIN_H__

typedef struct {
	double *d, *di, *ds, *b;
	int n;
} sl_tridiag;


/*!
	\brief Aloca o espaço em mêmoria para o sistema linear tridiagonal
	\param n tamanho dos vetores da matriz
	\return Ponteiro de acesso para o espaço alocado em caso de sucesso. NULL em caso de falha
*/
sl_tridiag *aloc_sislin (int n);

/*!
    \brief Libera o espaço alocado para o sistema linear tridiagonal
    \param sislin Estrutura de dados do Sistema Linear Tridiagonal
*/
void free_sislin (sl_tridiag *sislin);

/*!
    \brief Constroi o sistema linear tridiagonal com base nas informações do EDO
    \param edo Estrutura de dados do EDO
    \param sislin Estrutura de dados do Sistema Linear Tridiagonal
*/
void build_tridiag (edo_h *edo, sl_tridiag *sislin);

/*!
    \brief Printa o sistema linear na saida de dados
    \param sislin Estrutura de dados do Sistema Linear Tridiagonal
*/
void print_sislin (sl_tridiag *sislin);
#endif