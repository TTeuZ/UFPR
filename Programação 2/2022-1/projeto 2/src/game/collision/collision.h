#ifndef __COLLISION_H__
#define __COLLISION_H__

#include <math.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "../../constants.h"

#include "../player/player.h"
#include "../speeder/speeder.h"
#include "../withdraw/withdraw.h"

#include "../../functions/conditions/conditions.h"

#include "../../loadables/audio/audio.h"

#include "../../objects/index/index.h"
#include "../../objects/addBall/addBall.h"
#include "../../objects/ball/ball.h"

/*!
    \brief Função que verifica se a bolinha colidiu com algum dos quadrados
    \param g_obj Ponteiro de acesso para a estrutura de objetos do jogo
    \param speeder Ponteiro para a estrutura do speeder
    \param general Ponteiro de acesso para a estrutura de condições gerais do jogo
    \param audios Ponteiro de aceso para a estrutura de sons do jogo
*/
void check_square_collision (game_objects_t *g_obj, speeder_t speeder, general_t general, audios_t audios);

/*!
    \brief Função que verifica se a bolinha colidiu com alguma add_ball
    \param g_obj Ponteiro de acesso para a estrutura de objetos do jogo
    \param general Ponteiro de acesso para a estrutura de condições gerais do jogo
    \param audios Ponteiro de aceso para a estrutura de sons do jogo
*/
void check_add_ball_collision (game_objects_t *g_obj, general_t general, audios_t audios);

/*!
    \brief Função que verifica se a bolinha colidiu com alguma moeda
    \param p_points Ponteiro de acesso para a estrutura de dados de pontuação
    \param g_obj Ponteiro de acesso para a estrutura de objetos do jogo
    \param general Ponteiro de acesso para a estrutura de condições gerais do jogo
    \param audios Ponteiro de aceso para a estrutura de sons do jogo
*/
void check_coin_collision (player_points_t *p_points, game_objects_t *g_obj, general_t general, audios_t audios);

/*!
    \brief Função que verifica se a bolinha colidiu com alguma das paredes
    \param p_game Ponteiro de acesso para a estrutura de game
    \param g_obj Ponteiro de acesso para a estrutura de objetos do jogo
    \param withdraw Ponteiro de acesso para a estrutura de saque do jogos
*/
void check_wall_collision (player_game_t *p_game, game_objects_t *g_obj, withdraw_t *withdraw);

#endif