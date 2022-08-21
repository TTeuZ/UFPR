#ifndef __SQUARE_H__
#define __SQUARE_H__

#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "../../constants.h"

#include "../../loadables/fonts/fonts.h"

typedef struct square {
    int points;
    int x, y;
    int r, g, b;
} square_t;

/*!
    \brief Função que cria um quadrado com a quantidade de pontos indicada
    \param square Ponteiro de acesso para a estrutura de um quadrado
    \param points Pontos do quadrado
    \param line Linha em que o quadrado está
    \param col Coluna em que o quadrado está
*/
void add_square (square_t *square, int points, int line, int col);

/*!
    \brief Função que desenha os quadrados na tela
    \param squares Ponteiro de acesso para a matriz de quadrados
    \param fonts Ponteiro de acesso para a estrutura de fontes
*/
void draw_squares (square_t squares[MAP_LINES][MAP_COLS], fonts_t fonts);

#endif