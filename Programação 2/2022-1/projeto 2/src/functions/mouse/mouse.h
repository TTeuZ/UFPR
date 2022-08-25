#ifndef __MOUSE_H__
#define __MOUSE_H__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#include "../../constants.h"

#include "../conditions/conditions.h"

#include "../../game/aim/aim.h"
#include "../../game/player/player.h"
#include "../../game/shop/shop.h"
#include "../../game/speeder/speeder.h"

#include "../../loadables/audio/audio.h"

typedef struct mouse {
    ALLEGRO_MOUSE_CURSOR *cursor;
    ALLEGRO_BITMAP *arrow;
    int x;
    int y;
    int pressed;
} mouse_t;

/*!
    \brief Função que inicializa os valor de X e Y do mouse
    \param mouse Ponteiro de acesso para a estrutura do mouse
    \return EXIT_SUCCESS para sucesso, EXIT_FAILURE para erro
*/
int start_mouse (mouse_t *mouse);

/*!
    \brief Função que seta o mouse para o display do jogo
    \param display Ponteiro apra um ALLEGRO_DISPLAY
    \param mouse Ponteiro para a estrutura do mouse
*/
int set_mouse_display (ALLEGRO_DISPLAY *display, mouse_t mouse);

/*!
    \brief Função que seta a posição atual do mouse no display do jogo
    \param display Ponteiro de acesso para a estrutura do display do jogo
    \param mouse Ponteiro de acesso para a estrutura do mouse
    \param event Ponteiro de acesso para a estrutura de eventos da Allegro
*/
void treat_mouse_move (ALLEGRO_DISPLAY *display, mouse_t *mouse, ALLEGRO_EVENT event);

/*!
    \brief Função de tratamendo do click do mouse no caso de estar na tela de home do jogo
    \param mouse Ponteiro de acesso para a estrutura do mouse
    \param pages Ponteiro de acesso para a estrutura de condições das telas
    \param general Ponteiro de acesso para a estrutura de condições gerais do jogo
    \param audios Ponteiro de aceso para a estrutura de sons do jogo
    \param event Ponteiro de acesso para a estrutura de eventos da Allegro
*/
void treat_mouse_click_in_home (mouse_t *mouse, pages_t *pages, general_t *general, audios_t audios, ALLEGRO_EVENT event);

/*!
    \brief Função de tratamendo do click do mouse no caso de estar na tela de shop do jogo
    \param mouse Ponteiro de acesso para a estrutura do mouse
    \param p_points Ponteiro de acesso para a estrutura de dados de pontuação
    \param items Ponteiro de acesso para o arra de items
    \param pages Ponteiro de acesso para a estrutura de condições das telas
    \param general Ponteiro de acesso para a estrutura de condições gerais do jogo
    \param event Ponteiro de acesso para a estrutura de eventos da Allegro
*/
void treat_mouse_click_in_shop (mouse_t *mouse, player_points_t *p_points, shop_item_t items[ITEMS_SIZE], pages_t *pages, general_t *general, ALLEGRO_EVENT event);

/*!
    \brief Função de tratamendo do click do mouse no caso de estar na tela de help do jogo
    \param mouse Ponteiro de acesso para a estrutura do mouse
    \param pages Ponteiro de acesso para a estrutura de condições das telas
    \param event Ponteiro de acesso para a estrutura de eventos da Allegro
*/
void treat_mouse_click_in_help (mouse_t *mouse, pages_t *pages, ALLEGRO_EVENT event);

/*!
    \brief Função de tratamendo do click do mouse no caso de estar na tela de home do jogo
    \param pages Ponteiro de acesso para a estrutura de condições das telas
    \param general Ponteiro de acesso para a estrutura de condições gerais do jogo
    \param audios Ponteiro de aceso para a estrutura de sons do jogo
    \param event Ponteiro de acesso para a estrutura de eventos da Allegro
*/
void treat_mouse_click_in_pause (pages_t *pages, general_t *general, audios_t audios, ALLEGRO_EVENT event);

/*!
    \brief Função de tratamendo do click do mouse no caso de estar na tela de fim de jogo
    \param pages Ponteiro de acesso para a estrutura de condições das telas
    \param general Ponteiro de acesso para a estrutura de condições gerais do jogo
    \param event Ponteiro de acesso para a estrutura de eventos da Allegro
*/
void treat_mouse_click_in_end_game (pages_t *pages, general_t *general, ALLEGRO_EVENT event);

/*!
    \brief Função de tratamendo do click do mouse no caso de estar na tela de execução do jogo
    \param mouse Ponteiro de acesso para a estrutura do mouse
    \param pages Ponteiro de acesso para a estrutura de condições das telas
    \param aim Ponteiro para a estrutura de mira
    \param event Ponteiro de acesso para a estrutura de eventos da Allegro
*/
void treat_mouse_click_in_game (mouse_t *mouse, pages_t *pages, aim_t *aim, speeder_t *speeder, ALLEGRO_EVENT event);

/*!
    \brief Função que desaloca as estruturas alocadas para o mouse
    \param mouse Ponteiro de acesso para a estrutura do mouse
*/
void destroy_mouse (mouse_t *mouse);

#endif