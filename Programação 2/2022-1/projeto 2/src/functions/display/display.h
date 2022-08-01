#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <allegro5/allegro5.h>

#include "../../constants.h"

/*!
    \brief Função de inicialização do display da Alegro
    \param display Ponteiro de acesso para a estrutura de display da Allegro
    \param buffer Ponteiro de acesso para o buffer de escrita
    \return 0 em caso de sucesso 1 em caso de falha
*/
int create_display (ALLEGRO_DISPLAY **display, ALLEGRO_BITMAP **buffer);

/*! 
    \brief Função que altera entre o buffer e o display para escrita no jogo
    \param display Ponteiro de acesso para a estrutura de display da Allegro
    \param buffer Ponteiro de acesso para o buffer de escrita
*/
void flip_buffer_display (ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *buffer);

#endif