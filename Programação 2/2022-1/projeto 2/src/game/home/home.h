#ifndef __HOME_H__
#define __HOME_H__

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "../player/player.h"
#include "../../constants.h"

/*!
    \brief Função responsavel por construir a tela inicial (Home) do jogo
*/
void draw_home_page (player_points_t p_points, ALLEGRO_FONT *font, ALLEGRO_FONT *button_font, ALLEGRO_FONT *points_font, ALLEGRO_BITMAP *sound);

#endif