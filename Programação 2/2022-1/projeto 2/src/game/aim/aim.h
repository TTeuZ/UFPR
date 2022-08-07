#ifndef __AIM_H__
#define __AIM_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "../../constants.h"
#include "../player/player.h"

typedef struct aim {
    int x, y;
    int pressed_x, pressed_y;
    int move_x;
    int distance;
    double sin, cos;
} aim_t;

/*!
    \brief Função que inicializa a estrutura de mira
    \param aim Ponteiro para a estrutura de mira
    
*/
void set_aim (aim_t *aim, player_game_t p_game);

/*!
    \brief Função que altera a posição da mira
    \param aim Ponteiro para a estrutura de mira
    \param p_game Ponteiro de acesso para a estrutura de game
    \param event Ponteiro de acesso para a estrutura de eventos da Allegro
*/
void treat_aim_move (aim_t *aim, player_game_t p_game, ALLEGRO_EVENT event);

/*!
    \brief Função que faz a impressão da mira da bolinha
    \param aim Ponteiro para a estrutura de mira
    \param p_game Ponteiro de acesso para a estrutura de game
*/
void draw_game_aim (aim_t aim, player_game_t p_game);

#endif