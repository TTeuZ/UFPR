#ifndef __FONTS_H__
#define __FONTS_H__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "../../constants.h"

typedef struct fonts {
    ALLEGRO_FONT *title_h1;
    ALLEGRO_FONT *title_h2;
    ALLEGRO_FONT *text_help;
    ALLEGRO_FONT *text_record;
    ALLEGRO_FONT *button;
    ALLEGRO_FONT *points;
    ALLEGRO_FONT *coins;
    ALLEGRO_FONT *balls;
    ALLEGRO_FONT *speeder;
} fonts_t;

/*!
    \brief Função que inicializa a estrutura de armazenamento das fontes do jogo
    \param fonts Ponteiro de acesso para a estrutura de fontes
*/
int load_fonts (fonts_t *fonts);

/*!
    \brief Função que destroi as estruturas de fontes alocadas
    \param fonts Ponteiro de acesso para a estrutura de fontes
*/
void destroy_fonts (fonts_t *fonts);
#endif