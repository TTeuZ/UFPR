#ifndef __GAME_H__
#define __GAME_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct game_cond {
    int all_init;
    int redraw;
    int in_home_page;
    int end_game;
} game_cond_t;

/*!
    \brief Função de inicialização dos valores inicias para o jogo
    \param game_cond ponteiro de acesso para a estrutura de consições de jogo
*/
void start_game_conditions (game_cond_t *game_cond);

#endif