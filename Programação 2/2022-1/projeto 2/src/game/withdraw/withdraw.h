#ifndef __WITHDRAW_H__
#define __WITHDRAW_H__

#include "../../constants.h"
#include "../player/player.h"

typedef struct withdraw {
    int w_ball;
    int in_game_balls;
    int w_count;
    int all_played;
    int first_reach;
} withdraw_t;

/*!
    \brief Função de inicialização dos valores inicias para o jogo
    \param withdraw Ponteiro de acesso para a estrutura de saque do jogo
*/
void start_withdraw_conditions (withdraw_t *withdraw);

/*!
    \brief Função responsavel por atualizar o saque das bolinhas
    \param p_game Ponteiro de acesso para a estrutura de game
    \param withdraw Ponteiro de acesso para a estrutura de saque do jogoas
*/
void treat_withdraw (player_game_t *p_game, withdraw_t *withdraw);

#endif