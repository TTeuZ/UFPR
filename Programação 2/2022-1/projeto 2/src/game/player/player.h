#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <stdio.h>
#include <stdlib.h>

#include "../../constants.h"

typedef struct player_points {
    int coins;
    int record;
} player_points_t;

typedef struct player_game {
    int points;
    // ...
} player_game_t;

/*!
    \brief Função que realiza a leitura dos dados salvos do usuario caso existam.
    Se for a primeira vez abrindo o jogo inicia os dados salvos como 0
    \param p_points Ponteiro de acesso para a estrutura de dados de pontuação
*/
void read_player_points (player_points_t *p_points);

/*!
    \brief Função que realiza a leitura do antigo jogo em andamento do usuario.
    Caso seja o primeiro jogo, inicia as estruturas como 0.
    \param g_player Ponteiro de acesso para a estrutura de game
    \return erro READ_GAME_ERROR em caso de não conseguir ler o antigo estado salvo
*/
int read_player_game (player_game_t *g_player);

#endif