#include "conditions.h"

void start_game_conditions (game_cond_t *game_cond) {
    game_cond->all_init = 1;
    game_cond->redraw = 1;
    game_cond->in_home_page = 1;
    game_cond->in_help_page = 0;
    game_cond->in_pause_page = 0;
    game_cond->in_game_page = 0;
    game_cond->sound_on = 1;
    game_cond->restart = 0;
    game_cond->withdraw = 0;
    game_cond->in_game = 0;
    game_cond->close_game = 0;
}

void set_pages_to_false (game_cond_t *game_cond) {
    game_cond->in_home_page = 0;
    game_cond->in_help_page = 0;
    game_cond->in_pause_page = 0;
    game_cond->in_game_page = 0;
}