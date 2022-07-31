#include "game.h"

void start_game_conditions (game_cond_t *game_cond) {
    game_cond->redraw = 1;
    game_cond->end_game = 0;
    game_cond->all_init = 1;
}