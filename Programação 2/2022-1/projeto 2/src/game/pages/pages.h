#ifndef __PAGES_H__
#define __PAGES_H__

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "../player/player.h"
#include "../../functions/conditions/conditions.h"
#include "../../loadables/images/images.h"
#include "../../loadables/fonts/fonts.h"
#include "../../constants.h"

/*!
    \brief Função responsavel por construir a tela inicial (Home) do jogo
    \param p_points Ponteiro de acesso para a estrutura de pontos do jogador
    \param fonts Ponteiro para a estrutura de fonts
    \param game_cound Ponteiro de acesso para as condições atuais do jogo
    \param images Ponteiro para a estrutura de imagens
*/
void draw_home_page (player_points_t p_points, fonts_t fonts, game_cond_t game_cond, images_t images);

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
    \param game_cound Ponteiro de acesso para as condições atuais do jogo
*/
void draw_pause_page (fonts_t fonts, images_t images, game_cond_t game_cond);

/*!
    \brief Função responsável por construir a estrutura 'geral' da tela de jogo
    \param p_game Ponteiro para a estrutura de jogo atual
    \param p_points Ponteiro de acesso para a estrutura de pontos do jogado
    \param fonts Ponteiro para a estrutura de fonts
    \param game_cound Ponteiro de acesso para as condições atuais do jogo
    \param images Ponteiro para a estrutura de imagens
*/
void draw_game_page (player_game_t p_game, player_points_t p_points, fonts_t fonts, game_cond_t game_cond, images_t images);

#endif