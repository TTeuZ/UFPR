#ifndef __LOGIC_H__
#define __LOGIC_H__

#include <math.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "../../constants.h"

#include "../aim/aim.h"
#include "../player/player.h"
#include "../speeder/speeder.h"
#include "../withdraw/withdraw.h"

#include "../../functions/conditions/conditions.h"

#include "../../loadables/fonts/fonts.h"

#include "../../objects/index/index.h"
#include "../../objects/ball/ball.h"

/*!
    \brief Função que verifica se a bolinha colidiu com algum dos quadrados
    \param g_obj Ponteiro de acesso para a estrutura de objetos do jogo
    \param speeder Ponteiro para a estrutura do speeder
*/
void check_square_collision (game_objects_t *g_obj, speeder_t speeder);

/*!
    \brief Função que verifica se a bolinha colidiu com alguma das paredes
    \param p_game Ponteiro de acesso para a estrutura de game
    \param g_obj Ponteiro de acesso para a estrutura de objetos do jogo
    \param withdraw Ponteiro de acesso para a estrutura de saque do jogos
*/
void check_wall_collision (player_game_t *p_game, game_objects_t *g_obj, withdraw_t *withdraw);

/*!
    \brief Função que verifica se existe algum objeto na primeira linha
    \param g_obj Ponteiro de acesso para a estrutura de objetos do jogo
    \return true caso tenha. False caso nao tenha
*/
int verify_first_line (game_objects_t *g_obj);

/*!
    \brief Função que verifica se existe algum objeto na ultima linha
    \param g_obj Ponteiro de acesso para a estrutura de objetos do jogo
    \return true caso tenha. False caso nao tenha
*/
int verify_last_line (game_objects_t *g_obj);

/*!
    \brief Função responsavel por verificar se a fase atual se encerrou.
    \param p_game Ponteiro de acesso para a estrutura de game
    \param stages Ponteiro de acesso para a estrutura de estágios do jogo
    \param withdraw Ponteiro de acesso para a estrutura de saque do jogos
*/
void treat_end_phase (player_game_t *p_game, stages_t *stages, withdraw_t *withdraw);

/*!
    \brief Função que reinicializa o jogo atual
    \param p_game Ponteiro de acesso para a estrutura de game
*/
void restart_game (player_game_t *p_game);

#endif