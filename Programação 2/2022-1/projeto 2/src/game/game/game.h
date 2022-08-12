#ifndef __GAME_H__
#define __GAME_H__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "../../constants.h"
#include "../../functions/conditions/conditions.h"
#include "../../loadables/fonts/fonts.h"
#include "../../objects/ball/ball.h"
#include "../player/player.h"
#include "../aim/aim.h"

/*!
    \brief Função que inicializa a jogada das bolinhas no jogo
    \param p_game Ponteiro de acesso para a estrutura de game
    \param aim Ponteiro para a estrutura de mira
*/
void play_balls (player_game_t *p_game, aim_t aim);

/*!
    \brief Função responsavel por atualizar o saque das bolinhas
    \param p_game Ponteiro de acesso para a estrutura de game
    \param withdraw Ponteiro de acesso para a estrutura de saque do jogoas
*/
void treat_withdraw (player_game_t *p_game, withdraw_t *withdraw);

/*!
    \brief Função que verifica se a bolinha colidiu com alguma das paredes
    \param p_game Ponteiro de acesso para a estrutura de game
    \param withdraw Ponteiro de acesso para a estrutura de saque do jogos
*/
void check_wall_collision (player_game_t *p_game, withdraw_t *withdraw);

/*!
    \brief Função responsavel por verificar se a fase atual se encerrou.
    \param p_game Ponteiro de acesso para a estrutura de game
    \param stages Ponteiro de acesso para a estrutura de estágios do jogo
    \param withdraw Ponteiro de acesso para a estrutura de saque do jogos
*/
void treat_end_phase (player_game_t *p_game, stages_t *stages, withdraw_t *withdraw);

/*!
    \brief Função que realiza a limpesa de memória das estruturas alocadas do jogo
    \param p_game Ponteiro de acesso para a estrutura de game
*/
void destroy_game (player_game_t *p_game);
#endif