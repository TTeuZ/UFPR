#ifndef __SPEEDER_H__
#define __SPEEDER_H__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "../../constants.h"
#include "../../loadables/fonts/fonts.h"

typedef struct speeder {
    int is_enable;
    int frame;
    int color;
    float bust;
    ALLEGRO_BITMAP *icon;
} speeder_t;

/*!
    \brief Função que inicializa o speeder
    \param speeder Ponteiro para a estrutura do speeder
    \return 0 em caso de sucesso. 1 em caso de erro
*/
int start_speeder (speeder_t *speeder);

/*!
    \brief Função que trata o contador para a exibição do speeder
    \param speeder Ponteiro para a estrutura do speeder
*/
void treat_speeder (speeder_t *speeder);

/*!
    \brief Função que reseta os valores do speeder para a proxima fase
    \param speeder Ponteiro para a estrutura do speeder
*/
void restart_speeder (speeder_t *speeder);

/*!
    \brief Função que desenha o speeder na tela
    \param fonts Ponteiro para a estrutura de fonts
    \param speeder Ponteiro para a estrutura do speeder
*/
void draw_speeder (fonts_t fonts, speeder_t speeder);

/*!
    \brief Função que libera a memória armazenada pro speeder
    \param speeder Ponteiro para a estrutura do speederW
*/
void destroy_speeder (speeder_t *speeder);

#endif