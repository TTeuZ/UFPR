#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>

#include "../../constants.h"

typedef struct game_cond {
    // Inicializações e escrita
    int all_init;
    int redraw;
    // Draw de telas
    int in_home_page;
    int in_help_page;
    int in_pause_page;
    int in_game_page;
    // Condições de jogo
    int sound_on;
    int restart;
    int end_game;
} game_cond_t;

/*!
    \brief Função de inicialização dos valores inicias para o jogo
    \param game_cond ponteiro de acesso para a estrutura de consições de jogo
*/
void start_game_conditions (game_cond_t *game_cond);

/*!
    \brief Função que seta todas as variaveis de telas para falso
    \param game_cond ponteiro de acesso para a estrutura de consições de jogo
*/
void set_pages_to_false (game_cond_t *game_cond);

/*!
    \brief FUnção de lançamento de erro.
    notifica algum erro na stderr
    \param error_code Código de erro, utilizado para a exibição da mensagem
*/
void emit_error (int error_code);

#endif