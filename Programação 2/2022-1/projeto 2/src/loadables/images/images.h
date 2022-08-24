#ifndef __IMAGES_H__
#define __IMAGES_H__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#include "../../constants.h"

typedef struct images {
    ALLEGRO_BITMAP *sound;
    ALLEGRO_BITMAP *back;
    ALLEGRO_BITMAP *pause;
    ALLEGRO_BITMAP *balls;
    ALLEGRO_BITMAP *lock;
} images_t;

/*!
    \brief Função que inicializa a estrutura de armazenamento das imagens do jogo
    \param images Ponteiro de acesso para a estrutura de imagens
*/
int load_images (images_t *images);

/*!
    \brief Função que destroi as estruturas de imagens alocadas
    \param images Ponteiro de acesso para a estrutura de imagens
*/
void destroy_images (images_t *images);

#endif