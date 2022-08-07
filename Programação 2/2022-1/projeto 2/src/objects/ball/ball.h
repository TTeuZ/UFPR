#ifndef __BALL_H__
#define __BALL_H__

#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "../../constants.h"

typedef struct ball {
    int x, y;
    float dx, dy;
} ball_t;

/*!
    \brief Função que realiza a alocação de memória para a estrutura da bola e seta seus valores iniciais
    \param x posição inicial da bolinha
    \return Ponteiro de acesso para a estrutura. Null em caso de erro
*/
ball_t *add_ball (int x);

/*!
    \brief Função que desenha abolinha na tela do jogo
    \param ball Ponteiro para a estrutura da bolinha
*/
void draw_ball (ball_t *ball);
#endif