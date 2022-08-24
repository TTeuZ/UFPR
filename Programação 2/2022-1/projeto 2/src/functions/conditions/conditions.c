#include "conditions.h"

void start_general_conditions (general_t *general) {
    general->all_init = true;
    general->redraw = true;
    general->restart = false;
    general->sound_on = true;
    general->close_game = false;
}

void start_pages_conditions (pages_t *pages) {
    pages->in_home_page = true;
    pages->in_shop_page = false;
    pages->in_help_page = false;
    pages->in_pause_page = false;
    pages->in_game_page = false;
    pages->in_end_game_page = false;
}

void start_stages_conditions (stages_t *stages) {
    stages->start_phase = true;
    stages->drawing_down = false;
    stages->in_game = false;
    stages->end_phase = false;
    stages->end_game = false;
}

void set_pages_to_false (pages_t *pages) {
    pages->in_home_page = false;
    pages->in_shop_page = false;
    pages->in_help_page = false;
    pages->in_pause_page = false;
    pages->in_game_page = false;
}


