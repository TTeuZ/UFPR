#ifndef __BALL_H__
#define __BALL_H__

#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "../../constants.h"

#include "../../functions/conditions/conditions.h"

#include "../../game/speeder/speeder.h"
#include "../../game/aim/aim.h"

#include "../../loadables/fonts/fonts.h"

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
    \brief Função que inicializa a jogada das bolinhas no jogo
    \param balls Ponteiro para a um array de bolinhas
    \param qtd quantidade de bolinhas
    \param aim Ponteiro para a estrutura de mira
*/
void play_balls (ball_t **balls, int qtd, aim_t aim);

/*!
    \brief Função que atualiza a posição x e y das bolinhas
    \param balls Ponteiro para a um array de bolinahs
    \param qtd quantidade de bolinhas
    \param speeder Ponteiro para a estrutura do speeder
*/
void update_balls (ball_t **balls, int qtd, speeder_t speeder);

/*!
    \brief Função que para os valores da bolonha
    \param ball Ponteiro para a estrutura da bolinha
*/
void stop_ball (ball_t *ball);

/*!
    \brief Função resposável por desenhar os bolinhas em jogo
    \param balls Ponteiro para a um array de bolinahs
    \param qtd quantidade de bolinhas
    \param fonts Ponteiro de acesso para a estrutura de fontes
    \param stages Ponteiro de acesso para a estrutura de estágios do jogo
*/
void draw_balls (ball_t **balls, int qtd, int initial_x, int r, int g, int b, fonts_t fonts, stages_t stages);

#endif