#ifndef __PAGES_H__
#define __PAGES_H__

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "../player/player.h"
#include "../game/game.h"
#include "../../loadables/images/images.h"
#include "../../loadables/fonts/fonts.h"
#include "../../constants.h"

/*!
    \brief Função responsavel por construir a tela inicial (Home) do jogo
    \param p_points Ponteiro de acesso para a estrutura de pontos do jogador
    \param title_font Ponteiro para a fonte do titulo da home
    \param button_font Ponteiro para a fonte dos botões da home
    \param points_font Ponteiro para a fonte das pontuações da home
    \param game_cound Ponteiro de acesso para as condições atuais do jogo
    \param images Ponteiro para a estrutura de imagens
*/
void draw_home_page (player_points_t p_points, fonts_t fonts, game_cond_t game_cond, images_t images);

/*!
    \brief Função responsavel por construir a tela de ajuda (Help) do jogo
    \param title_font Ponteiro para a fonte do titulo da tela help
    \param text_font Ponteiro para a fonte dos botões da tela help
    \param images Ponteiro para a estrutura de imagens
*/
void draw_help_page (fonts_t fonts, images_t images);

#endif