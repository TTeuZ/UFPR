#include "keyboard.h"

void treat_key_down (game_cond_t *game_cond, ALLEGRO_EVENT event) {
    int gaming, key;
    
    gaming = game_cond->in_game_page;
    key = event.keyboard.keycode;

    if (gaming && key == ALLEGRO_KEY_P) {
        game_cond->in_pause_page = true;
        game_cond->in_game_page = false;
    }
    if (!gaming && key == ALLEGRO_KEY_H) {
        set_pages_to_false (game_cond);
        game_cond->in_help_page = true;
    }
    if (key == ALLEGRO_KEY_S)
        game_cond->sound_on = ! game_cond->sound_on;
    if (key == ALLEGRO_KEY_ESCAPE)
        game_cond->close_game = true;
}