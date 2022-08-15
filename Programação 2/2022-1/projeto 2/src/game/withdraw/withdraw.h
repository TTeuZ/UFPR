#ifndef __WITHDRAW_H__
#define __WITHDRAW_H__

#include "../../constants.h"

#include "../player/player.h"

#include "../../objects/index/index.h"

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
    \param g_obj Ponteiro de acesso para a estrutura de objetos do jogo
    \param withdraw Ponteiro de acesso para a estrutura de saque do jogoas
*/
void treat_withdraw (game_objects_t *g_obj, withdraw_t *withdraw);

#endif