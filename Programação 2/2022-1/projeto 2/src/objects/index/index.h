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
    \brief Função que inicializa os objetos do jogo
    \param p_game Ponteiro de acesso para a estrutura de game
    \param g_obj Ponteiro de acesso para a estrutura de objetos do jogo
    \return GAME_OBJECTS_ERROR em caso de falha de alocação para a estrutura de objetos de jogo
            ADD_BALL_ERROR em caso de falaha de alocação das bolinahs do jogo
*/
int start_game_objects (player_game_t p_game, game_objects_t **g_obj);

/*!
    \brief Função que reinicializa os objetos do jogo
    \param g_obj Ponteiro de acesso para a estrutura de objetos do jogo
    \return ADD_BALL_ERROR em caso de falaha de alocação das bolinahs do jogo
*/
int restart_game_objects (game_objects_t *g_obj);

/*!
    \brief Função que salva as mudanças feitas nos objetos do jogo para o jogo atual para salvar em memória
    \param p_game Ponteiro de acesso para a estrutura de game
    \param g_obj Ponteiro de acesso para a estrutura de objetos do jogo
*/
void persist_objects_changes (player_game_t *p_game, game_objects_t *g_obj);

/*!
    \brief Função que desaloca os objetos do jogo
    \param g_obj Ponteiro de acesso para a estrutura de objetos do jogo
*/
void destroy_game_objects (game_objects_t *g_obj);

#endif