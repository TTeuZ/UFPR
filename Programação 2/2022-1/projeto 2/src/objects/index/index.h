#ifndef __INDEX_H__
#define __INDEX_H__

#include "../../constants.h"
#include "../../game/player/player.h"

#include "../addBall/addBall.h"
#include "../ball/ball.h"
#include "../coin/coin.h"
#include "../square/square.h"

typedef struct game_objects {
    int balls_qtd;
    ball_t **balls;
    //...
} game_objects_t;

/*!
    \brief Função que inicializa os objetos que estarão no jogo
    \param p_game Ponteiro de acesso para a estrutura de game
    \return GAME_OBJECTS_ERROR em caso de falha de alocação para a estrutura de objetos de jogo
            ADD_BALL_ERROR em caso de falaha de alocação das bolinahs do jogo
*/
int start_game_objects (player_game_t p_game, game_objects_t **g_obj);

#endif