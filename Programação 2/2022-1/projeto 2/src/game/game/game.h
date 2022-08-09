#ifndef __GAME_H__
#define __GAME_H__

#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "../../constants.h"
#include "../../functions/utils/utils.h"
#include "../../loadables/fonts/fonts.h"
#include "../player/player.h"
#include "../aim/aim.h"

/*!
    \brief Função resposável por escrever a tela do jogo
    \param p_game Ponteiro de acesso para a estrutura de game
    \param fonts Ponteiro de acesso para a estrutura de fontes
    \param game_cound Ponteiro de acesso para as condições atuais do jogo
*/
void draw_game_section (player_game_t p_game, fonts_t fonts, game_cond_t game_cond);

/*!
    \brief Função que inicializa a jogada das bolinhas no jogo
    \param p_game Ponteiro de acesso para a estrutura de game
    \param aim Ponteiro para a estrutura de mira
*/
void play_balls (player_game_t *p_game, aim_t aim);

/*!
    \brief Função que verifica se a bolinha colidiu com alguma das paredes
    \param p_game Ponteiro de acesso para a estrutura de game
    \param game_cound Ponteiro de acesso para as condições atuais do jogo
*/
void check_wall_collision (player_game_t *p_game, game_cond_t *game_cond);

/*!
    \brief Função que realiza a limpesa de memória das estruturas alocadas do jogo
    \param p_game Ponteiro de acesso para a estrutura de game
*/
void destroy_game (player_game_t *p_game);
#endif