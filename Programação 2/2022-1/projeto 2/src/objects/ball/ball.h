#ifndef __BALL_H__
#define __BALL_H__

#include <stdio.h>
#include <stdlib.h>

#include "../../constants.h"

typedef struct ball {
    float x, y;
    float speed;
} ball_t;

/*!
    \brief Função que realiza a alocação de memória para a estrutura da bola e seta seus valores iniciais
    \return Ponteiro de acesso para a estrutura. Null em caso de erro
*/
ball_t *add_ball ();

#endif