#ifndef __ADD_BALL_H__
#define __ADD_BALL_H__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "../../constants.h"

#include "../ball/ball.h"

typedef struct add_ball {
    int show;
    int x, y;
    int arc_radius;

    // animacao
    int adder;
} add_ball_t;

/*!
    \brief Função que cria uma add_ball na posicao indicada
    \param add_ball pontero para a estrutura de uma add_ball
    \param line Linha em que o quadrado está
    \param col Coluna em que o quadrado está
*/
void add_add_ball (add_ball_t *add_ball, int line, int col);

/*!
    \brief Função que pre adiciona um bolinha
    \param balls pontero para o array de bolinhas pre adicionadas
    \param qtd Quantidade de bolinahs pre adicionadas
    \param x Posicao x da bolinha
    \param y Posicao y da bolinha
*/
void pre_add_ball (ball_t balls[MAP_COLS], int *qtd, int x, int y);

/*!
    \brief Função que atuaiza a posicao y das bolinhas pre adicionadas
    \param balls pontero para o array de bolinhas pre adicionadas
    \param qtd Quantidade de bolinahs pre adicionadas
*/
void update_pre_add_balls (ball_t balls[MAP_COLS], int qtd);

/*!
    \brief Função que desenha as bolinhas pre adicionadads
    \param balls pontero para o array de bolinhas pre adicionadas
    \param qtd Quantidade de bolinahs pre adicionadas
*/
void draw_pre_add_balls (ball_t balls[MAP_COLS], int qtd);

/*!
    \brief Função que desenha as add_ball na tela
    \param add_ball Ponteiro de acesso para a matriz de add_balls
    \param a_frame frame atual dos add_balls para animacao
*/
void draw_add_balls (add_ball_t add_balls[MAP_LINES][MAP_COLS], int a_frame);

#endif