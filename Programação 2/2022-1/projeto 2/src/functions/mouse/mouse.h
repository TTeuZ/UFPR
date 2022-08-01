#ifndef __MOUSE_H__
#define __MOUSE_H__

#include <allegro5/allegro5.h>

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

#endif