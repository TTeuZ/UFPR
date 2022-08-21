#ifndef __COIN_H__
#define __COIN_H__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "../../constants.h"

typedef struct coin {
    int show;
    int x, y;
} coin_t;

/*!
    \brief Função que cria uma moeda na posicao indicada
    \param coin pontiero para a estrutura de uma moeda
    \param line Linha em que o quadrado está
    \param col Coluna em que o quadrado está
*/
void add_coin (coin_t *coin, int line, int col);

/*!
    \brief Função que desenha as moedas na tela
    \param coins Ponteiro de acesso para a matriz de moedas
*/
void draw_coins (coin_t coins[MAP_LINES][MAP_COLS]);

#endif