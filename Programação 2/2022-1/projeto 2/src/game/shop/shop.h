#ifndef __SHOP_H__
#define __SHOP_H__

#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#include "../player/player.h"

#include "../../constants.h"

typedef struct shop_item {
    int price;
    int buyed;
    int in_use;
    int r, g, b;
} shop_item_t;

/*!
    \brief Funcao que le o arquivo com o estado atual dos items do shop
    \param items Ponteiro de acesso para o array de items
    \return erro READ_SHOP_ERROR em caso de nao conseguir ler o estado salvo
*/
int read_shop_items (shop_item_t items[ITEMS_SIZE]);

/*!
    \brief Funcao que salva o estado atual do shop em memoria
    \param items Ponteiro de acesso para o array de items
    \return erro SAVE_SHOP_ERROR em caso de nao conseguir ler o estado salvo
*/
int save_shop_items (shop_item_t items[ITEMS_SIZE]);

/*!
    \brief Funcao que realiza a compra da bolinha se possivel
    \param items Ponteiro de acesso para o array de items
    \param p_points Ponteiro de acesso para a estrutura de dados de pontuação
    \param pos posicao do item do array
*/
void verify_and_buy (shop_item_t items[ITEMS_SIZE], player_points_t *p_points, int pos);

#endif