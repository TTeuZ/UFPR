#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <allegro5/allegro5.h>

#include "../../constants.h"

#include "../conditions/conditions.h"

/*!
    \brief Função de tratamendo de teclado
    \param pages Ponteiro de acesso para a estrutura de condições das telas
    \param general Ponteiro de acesso para a estrutura de flags gerais do jogo
    \param event Ponteiro de acesso para a estrutura de eventos da Allegro
*/
void treat_key_down (pages_t *pages, general_t *general, ALLEGRO_EVENT event);

#endif