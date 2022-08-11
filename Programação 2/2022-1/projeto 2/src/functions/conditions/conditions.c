#include "conditions.h"

void start_general_conditions (general_t *general) {
    general->all_init = 1;
    general->redraw = 1;
    general->restart = 0;
    general->sound_on = 1;
    general->close_game = 0;
}

void start_pages_conditions (pages_t *pages) {
    pages->in_home_page = 1;
    pages->in_help_page = 0;
    pages->in_pause_page = 0;
    pages->in_game_page = 0;
}

void start_stages_conditions (stages_t *stages) {
    stages->withdraw = 0;
    stages->in_game = 0;
    stages->end_phase = 0;
}

void start_withdraw_conditions (withdraw_t *withdraw) {
    withdraw->w_ball = 0;
    withdraw->in_game_balls = 0;
    withdraw->w_count = WITHDRAW_TIME;
    withdraw->all_played = 0;
}

void set_pages_to_false (pages_t *pages) {
    pages->in_home_page = 0;
    pages->in_help_page = 0;
    pages->in_pause_page = 0;
    pages->in_game_page = 0;
}


