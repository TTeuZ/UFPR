#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct player_points {
    int coins;
    int record;
} player_points_t;

// estrutura do jogo atua..

/*!
    \brief Função que realiza a leitura dos dados salvos do usuario caso existam.
    Se for a primeira vez abrindo o jogo inicia os dados salvos como 0
    \param p_points Ponteiro de acesso para a estrutura de dados de pontuação
*/
void read_player_points (player_points_t *p_points);

#endif