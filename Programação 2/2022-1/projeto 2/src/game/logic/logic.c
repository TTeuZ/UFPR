#include "logic.h"

int verify_first_line (game_objects_t *g_obj) {
    int col;
    for (col = 0; col < MAP_COLS; col++) {
        if (g_obj->squares[0][col].points != 0) return true;
    }
    return false;
}

int verify_last_line (game_objects_t *g_obj) {
    int col;
    for (col = 0; col < MAP_COLS; col++) {
        if (g_obj->squares[MAP_LINES - 2][col].points != 0) return true;
    }
    return false;
}

void treat_end_phase (player_game_t *p_game, stages_t *stages, withdraw_t *withdraw) {
    if (withdraw->in_game_balls == 0) {
        stages->in_game = false;
        stages->end_phase = true;

        withdraw->w_count = WITHDRAW_TIME;
        withdraw->all_played = false;
        withdraw->first_reach = false;
        withdraw->w_ball = 0;

        p_game->initial_x = p_game->temp_init_x;
        p_game->points++;
    }
}

void restart_game (player_game_t *p_game) {
    p_game->initial_x = INITIAL_X_POSITION;
    p_game->points = 1; 
}
