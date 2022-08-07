#ifndef __AIM_H__
#define __AIM_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "../../constants.h"

typedef struct aim {
    int x, y;
    int pressed_x, pressed_y;
} aim_t;

/*!
    \brief Função que inicializa a estrutura de mira
    \param aim Ponteiro para a estrutura de mira
*/
void set_aim (aim_t *aim);

/*!
    \brief Função que altera a posição da mira
    \param aim Ponteiro para a estrutura de mira
    \param event Ponteiro de acesso para a estrutura de eventos da Allegro
*/
void treat_aim_move (aim_t *aim, ALLEGRO_EVENT event);

/*!
    \brief Função que faz a impressão da mira da bolinha
    \param aim Ponteiro para a estrutura de mira
*/
void draw_game_aim (aim_t aim);

#endif