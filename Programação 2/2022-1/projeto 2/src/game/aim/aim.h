#ifndef __AIM_H__
#define __AIM_H__

#include <math.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "../../constants.h"

typedef struct aim {
    int x, y;
    int pressed_x, pressed_y;
    int move_x;
    int distance;
    double sin, cos;
} aim_t;

/*!
    \brief Função que seta valores iniciais para a mira
    \param aim Ponteiro para a estrutura de mira
    \param initial_x posição inicial atual do x das bolinhas
*/
void set_aim (aim_t *aim, int initial_x);

/*!
    \brief Função que altera a posição da mira
    \param aim Ponteiro para a estrutura de mira
    \param initial_x posição inicial atual do x das bolinhas
    \param event Ponteiro de acesso para a estrutura de eventos da Allegro
*/
void treat_aim_move (aim_t *aim, int initial_x, ALLEGRO_EVENT event);

/*!
    \brief Função que faz o desenho da mira da bolinha
    \param aim Ponteiro para a estrutura de mira
    \param initial_x posição inicial atual do x das bolinhas
*/
void draw_game_aim (aim_t aim, int initial_x);

#endif