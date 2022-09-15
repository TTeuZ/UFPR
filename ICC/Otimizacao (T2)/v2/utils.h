#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h>

#define ABS(num) ((num) < 0.0 ? -(num) : (num))

/*!
    \brief Função de geração de valor timestamp
    \return valor Double do timestamp atual
*/
double timestamp (void);

/*!
    \brief Função que realiza a soma dos 4 valores armazenados em um registrador SIMD
    \param reg registrador que contem os valores
    \return valor da soma
*/
double avx_register_sum (__m256d reg);
#endif
