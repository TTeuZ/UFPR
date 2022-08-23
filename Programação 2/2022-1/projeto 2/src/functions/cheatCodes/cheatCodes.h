#ifndef __CHEAT_CODES_H__
#define __CHEAT_CODES_H__

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>

#include "../../constants.h"

#include "../conditions/conditions.h"

#include "../../loadables/audio/audio.h"

#include "../../objects/index/index.h"

typedef struct cheats {
    int yudi_used;
    int yudi_qtd;
    char yudi[YUDI_CHEAT_SIZE];
} cheats_t;

/*!
    \brief Funcao que inicializa os valores dad estrutura de cheatCodes
    \param cheats Ponteiro para a estrutura de cheats
    \return CHEAT_CODE_ERROR em caso de falha. EXIT_SUCCESS em caso de sucesso
*/
int start_cheats (cheats_t *cheats);

/*!
    \brief Funcao que trata a execucao do cheat code do yudi
    \param cheats Ponteiro para a estrutura de cheats
    \param g_obj Ponteiro de acesso para a estrutura de objetos do jogo
    \param event Ponteiro de acesso para a estrutura de eventos da Allegro
*/
int treat_yudi_cheat (cheats_t *cheats, game_objects_t *g_obj, ALLEGRO_EVENT event);

#endif