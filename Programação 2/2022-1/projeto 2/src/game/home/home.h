#ifndef __HOME_H__
#define __HOME_H__

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "../player/player.h"
#include "../game/game.h"
#include "../../constants.h"

/*!
    \brief Função responsavel por construir a tela inicial (Home) do jogo
    \param p_points Ponteiro de acesso para a estrutura de pontos do jogador
    \param font Ponteiro para a fonte do titulo da home
    \param button_font Ponteiro para a fonte dos botões da home
    \param points_font Ponteiro para a fonte das pontuações da home
    \param game_cound Ponteiro de acesso para as condições atuais do jogo
    \param sound Ponteiro para o icone de som da home
*/
void draw_home_page (player_points_t p_points, ALLEGRO_FONT *font, ALLEGRO_FONT *button_font, ALLEGRO_FONT *points_font, game_cond_t game_cond, ALLEGRO_BITMAP *sound);

#endif