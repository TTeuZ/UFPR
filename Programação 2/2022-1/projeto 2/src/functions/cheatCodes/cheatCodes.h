#ifndef __CHEAT_CODES_H__
#define __CHEAT_CODES_H__

#include <allegro5/allegro5.h>

#include "../../constants.h"

#include "../conditions/conditions.h"

#include "../../loadables/audio/audio.h"

typedef struct cheats {
    unsigned char yudi[YUDI_CHEAT_SIZE];
} cheats_t;

/*!
    \brief Funcao que inicializa os valores dad estrutura de cheatCodes
    \param cheats Ponteiro para a estrutura de cheats
    \return CHEAT_CODE_ERROR em caso de falha. EXIT_SUCCESS em caso de sucesso
*/
int start_cheats (cheats_t *cheats);

#endif