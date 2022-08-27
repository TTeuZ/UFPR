#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

/*!
    \brief Função que calcula o fatorial do numero indicado
    \param number Numero o qual vai ser calculado o fatorial
    \return Valor do fatorial do numero
*/
int fat (int number);

/*!
    \brief Função que verifica se o numero já foi inserido no array
    \param number Numero da verificação
    \param size tamanho do array
    \param array Array da verificação
    \return true em caso de estar inserio. false em caso de não estar
*/
int includes (int number, int size, int *array);

#endif