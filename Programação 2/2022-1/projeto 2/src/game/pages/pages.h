#ifndef __PAGES_H__
#define __PAGES_H__

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "../../constants.h"

#include "../player/player.h"

#include "../../functions/conditions/conditions.h"

#include "../../loadables/images/images.h"
#include "../../loadables/fonts/fonts.h"

/*!
    \brief Função responsavel por construir a tela inicial (Home) do jogo
    \param p_points Ponteiro de acesso para a estrutura de pontos do jogador
    \param fonts Ponteiro para a estrutura de fonts
    \param general Ponteiro de acesso para a estrutura de flags gerais do jogo
    \param images Ponteiro para a estrutura de imagens
*/
void draw_home_page (player_points_t p_points, fonts_t fonts, general_t general, images_t images);

/*!
    \brief Função responsavel por construir a tela de ajuda (Help) do jogo
    \param fonts Ponteiro para a estrutura de fonts
    \param images Ponteiro para a estrutura de imagens
*/
void draw_help_page (fonts_t fonts, images_t images);

/*!
    \brief Função responsável por construir a tela de pause do jogo
    \param fonts Ponteiro para a estrutura de fonts
    \param images Ponteiro para a estrutura de imagens
    \param general Ponteiro de acesso para a estrutura de flags gerais do jogo
*/
void draw_pause_page (fonts_t fonts, images_t images, general_t general);

/*!
    \brief Função responsável por construir a estrutura 'geral' da tela de jogo
    \param p_game Ponteiro para a estrutura do jogo
    \param p_points Ponteiro de acesso para a estrutura de dados de pontuação
    \param fonts Ponteiro para a estrutura de fonts
    \param images Ponteiro para a estrutura de imagens
*/
void draw_game_page (player_game_t p_game, player_points_t p_points, fonts_t fonts, images_t images);

#endif