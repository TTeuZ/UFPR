#include "keyboard.h"

void treat_key_down (pages_t *pages, general_t *general, ALLEGRO_EVENT event) {
    int gaming, key;
    
    gaming = pages->in_game_page;
    key = event.keyboard.keycode;

    if (gaming && key == ALLEGRO_KEY_P) {
        pages->in_pause_page = true;
        pages->in_game_page = false;
    }
    if (!gaming && key == ALLEGRO_KEY_H) {
        set_pages_to_false (pages);
        pages->in_help_page = true;
    }
    if (key == ALLEGRO_KEY_S)
        general->sound_on = ! general->sound_on;
    if (key == ALLEGRO_KEY_ESCAPE)
        general->close_game = true;
}