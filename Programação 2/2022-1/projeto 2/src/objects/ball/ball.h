#ifndef __BALL_H__
#define __BALL_H__

#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "../../constants.h"
#include "../../game/speeder/speeder.h"

typedef struct ball {
    int playable;
    float x, y;
    float dx, dy;
} ball_t;

/*!
    \brief Função que realiza a alocação de memória para a estrutura da bola e seta seus valores iniciais
    \param x posição inicial da bolinha
    \return Ponteiro de acesso para a estrutura. Null em caso de erro
*/
ball_t *add_ball (int x);

/*!
    \brief Função que atualiza a posição x e y das bolinhas
    \param balls Ponteiro para a estrutura da bolinha
    \param qtd quantidade de bolinhas
    \param speeder Ponteiro para a estrutura do speeder
*/
void update_balls (ball_t **balls, int qtd, speeder_t speeder);

/*!
    \brief Função que desenha abolinha na tela do jogo
    \param ball Ponteiro para a estrutura da bolinha
*/
void draw_ball (ball_t *ball);
#endif