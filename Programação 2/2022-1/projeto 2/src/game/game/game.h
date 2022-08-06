#ifndef __GAME_H__
#define __GAME_H__

#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "../../constants.h"
#include "../player/player.h"

/*!
    \brief Função resposável por escrever a tela do jogo
    \param p_game Ponteiro de acesso para a estrutura de game
*/
void draw_game_section (player_game_t p_game);
#endif