#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <stdio.h>
#include <stdlib.h>

#include "../../constants.h"
#include "../../objects/ball/ball.h"

typedef struct player_points {
    int coins;
    int record;
    int ball_in_use;
} player_points_t;

typedef struct player_game {
    int points;
    float initial_x;
    float temp_init_x;
    
    int balls_qtd;
    int map[MAP_LINES][MAP_COLS];
} player_game_t;

/*!
    \brief Função que realiza a leitura dos dados salvos do usuario caso existam.
    Se for a primeira vez abrindo o jogo inicia um jogo novo
    \param p_points Ponteiro de acesso para a estrutura de dados de pontuação
    \return erro READ_POINTS_ERROR em caso de nao conseguir ler o estado salvo
*/
int read_player_points (player_points_t *p_points);

/*!
    \brief Função que realiza a leitura do antigo jogo em andamento do usuario.
    Caso seja o primeiro jogo, inicia um novo jogo.
    \param p_game Ponteiro de acesso para a estrutura de game
    \return erro READ_GAME_ERROR em caso de não conseguir ler o antigo estado salvo
*/
int read_player_game (player_game_t *p_game);

/*!
    \brief Função que salva os pontos atuais do jogador em memória
    \param p_points Ponteiro de acesso para a estrutura de dados de pontuação
    \return erro SAVE_POINTS_ERROR em caso de não conseguir salvar
*/
int save_player_points (player_points_t p_points);

/*!
    \brief Função que salva o jogo atual do jogador
    \param p_game Ponteiro de acesso para a estrutura do jogo
    \return erro SAVE_GAME_ERROR em caso de não conseguir salvar
*/
int save_player_game (player_game_t p_game);

#endif