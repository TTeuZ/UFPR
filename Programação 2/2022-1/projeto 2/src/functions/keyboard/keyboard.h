#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <allegro5/allegro5.h>

#include "../../constants.h"
#include "../../game/game/game.h"

/*!
    \brief Função de tratamendo de teclas do teclado
    \param game_cond Ponteiro de acesso para a estrutura da condiççoes atuais do jogo
    \param event Ponteiro de acesso para a estrutura de eventos da Allegro
*/
void treat_key_down (game_cond_t *game_cond, ALLEGRO_EVENT event);

#endif