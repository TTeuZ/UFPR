#ifndef __ADD_BALL_H__
#define __ADD_BALL_H__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "../../constants.h"

typedef struct add_ball {
    int show;
    int x, y;
    int arc_radius;

    // animacao
    int adder;
} add_ball_t;

/*!
    \brief Função que cria uma add_ball na posicao indicada
    \param add_ball pontiero para a estrutura de uma add_ball
    \param line Linha em que o quadrado está
    \param col Coluna em que o quadrado está
*/
void add_add_ball (add_ball_t *add_ball, int line, int col);

/*!
    \brief Função que desenha as add_ball na tela
    \param add_ball Ponteiro de acesso para a matriz de add_balls
    \param a_frame frame atual dos add_balls para animacao
*/
void draw_add_balls (add_ball_t add_balls[MAP_LINES][MAP_COLS], int a_frame);

#endif