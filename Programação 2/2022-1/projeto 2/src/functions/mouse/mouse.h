#ifndef __MOUSE_H__
#define __MOUSE_H__

#include <allegro5/allegro5.h>

#include "../../game/game/game.h"
#include "../../constants.h"

typedef struct mouse {
    ALLEGRO_BITMAP *cursor;
    int x;
    int y;
} mouse_t;

/*!
    \brief Função que inicializa os valored de X e Y do mouse
    \param mouse Ponteiro de acesso para a estrutura do mouse
    \return 1 para erro, 0 para sucesso
*/
int start_mouse (mouse_t *mouse);

/*!
    \brief Função que seta o mouse para o display do jogo
    \param cursor Ponteiro para um ALLEGRO_MOUSE_CURSOR
    \param display Ponteiro apra um ALLEGRO_DISPLAY
    \param mouse Ponteiro para a estrutura de dados do mouse
*/
int set_mouse_display (ALLEGRO_MOUSE_CURSOR *cursor, ALLEGRO_DISPLAY *display, mouse_t mouse);

/*!
    \brief Função que seta a posição atual do mouse no display do jogo
    \param display POnteiro de acesso para a estrutura do display do jogo
    \param mouse Ponteiro de acesso para a estrutura do mouse
    \param event Ponteiro de acesso para a estrutura de eventos da Allegro
*/
void treat_mouse_move (ALLEGRO_DISPLAY *display, mouse_t *mouse, ALLEGRO_EVENT event);

/*!
    \brief Função de tratamendo do click do mouse no caso de estar na tela de home do jogo
    \param mouse Ponteiro de acesso para a estrutura do mouse
    \param game_cond Ponteiro de acesso para a estrutura da condiççoes atuais do jogo
    \param event Ponteiro de acesso para a estrutura de eventos da Allegro
*/
void treat_mouse_click_in_home (mouse_t *mouse, game_cond_t *game_cond, ALLEGRO_EVENT event);

/*!
    \brief Função de tratamendo do click do mouse no caso de estar na tela de execução do jogo
    \param mouse Ponteiro de acesso para a estrutura do mouse
    \param game_cond Ponteiro de acesso para a estrutura da condiççoes atuais do jogo
    \param event Ponteiro de acesso para a estrutura de eventos da Allegro
*/
void treat_mouse_click_in_game (mouse_t *mouse, game_cond_t *game_cond, ALLEGRO_EVENT event);
#endif