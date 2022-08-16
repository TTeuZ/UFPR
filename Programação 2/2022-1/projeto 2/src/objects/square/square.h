#ifndef __SQUARE_H__
#define __SQUARE_H__

#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "../../constants.h"

typedef struct square {
    int points;
    int x, y;
    int color;
} square_t;

/*!
    \brief Função que cria um quadrado com a quantidade de pontos indicada
    \param square ponteiro de acesso para a estrutura de um quadrado
    \param points Pontos do quadrado
    \param line Linha em que o quadrado está
    \param col Coluna em que o quadrado está
*/
void add_square (square_t *square, int points, int line, int col);

/*!
    \brief Função que cria um quadrado com a quantidade de pontos indicada
    \param squares POnteiro de acesso para a matriz de quadrados
*/
void draw_squares (square_t squares[MAP_LINES][MAP_COLS]);

#endif