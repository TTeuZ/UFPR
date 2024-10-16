#ifndef __CONDITIONS_H__
#define __CONDITIONS_H__

#include <stdbool.h>

#include "../../constants.h"

typedef struct general {
    int all_init;
    int redraw;
    int restart;
    int sound_on;
    int close_game;
} general_t;

typedef struct pages {
    int in_home_page;
    int in_shop_page;
    int in_help_page;
    int in_pause_page;
    int in_game_page;
    int in_end_game_page;
} pages_t;

typedef struct stages {
    int start_phase;
    int drawing_down;
    int in_game;
    int end_phase;
    int end_game;
} stages_t;

/*!
    \brief Função de inicialização das flags gerais do jogo
    \param general Ponteiro de acesso para a estrutura de condições gerais do jogo
*/
void start_general_conditions (general_t *general);

/*!
    \brief Função de inicialização das flags de telas do jogo
    \param pages Ponteiro de acesso para a estrutura de condições das telas
*/
void start_pages_conditions (pages_t *pages);

/*!
    \brief Função de inicialização das flags de estágios do jogo
    \param stages Ponteiro de acesso para a estrutura de estágios do jogo
*/
void start_stages_conditions (stages_t *stages);

/*!
    \brief Função que seta todas as variaveis de telas para falso
    \param game_cond ponteiro de acesso para a estrutura de consições de jogo
*/
void set_pages_to_false (pages_t *pages);

#endif