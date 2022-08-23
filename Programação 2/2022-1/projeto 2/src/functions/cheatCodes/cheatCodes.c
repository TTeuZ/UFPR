#include "cheatCodes.h"

int start_cheats (cheats_t *cheats) {
    cheats->yudi_used = false; 
    cheats->yudi_qtd = 0;
    memset (cheats->yudi, 0, sizeof (cheats->yudi));
    return EXIT_SUCCESS;
}

int treat_yudi_cheat (cheats_t *cheats, game_objects_t *g_obj, ALLEGRO_EVENT event) {
    char yudi_res[YUDI_CHEAT_SIZE] = {31, 27, 27, 29, 35, 36, 29, 29};

    if (! cheats->yudi_used) {
        cheats->yudi[cheats->yudi_qtd] = event.keyboard.keycode;
        cheats->yudi_qtd++;
        if (strncmp (cheats->yudi, yudi_res, cheats->yudi_qtd) != 0) {
            memset (cheats->yudi, 0, sizeof (cheats->yudi));
            cheats->yudi_qtd = 0;
        }
        if (cheats->yudi_qtd == YUDI_CHEAT_SIZE) {
            cheats->yudi_used = true;
            return double_balls (g_obj);
        }
    }
    return EXIT_SUCCESS;
}