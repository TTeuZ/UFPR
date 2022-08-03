#include <stdio.h>
#include "mouse.h"

int start_mouse (mouse_t *mouse) {
    mouse->x = 0;
    mouse->y = 0;
    if (! (mouse->cursor = al_load_bitmap ("./resources/images/cursor.png")))
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int set_mouse_display (ALLEGRO_MOUSE_CURSOR *cursor, ALLEGRO_DISPLAY *display, mouse_t mouse) {
    if (! (cursor = al_create_mouse_cursor (mouse.cursor, 0, 0)))
        return EXIT_FAILURE;
    if (! al_set_mouse_cursor (display, cursor))
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void treat_mouse_move (ALLEGRO_DISPLAY *display, mouse_t *mouse, ALLEGRO_EVENT event) {
    mouse->x = event.mouse.x;
    mouse->y = event.mouse.y;
    al_set_mouse_xy (display, mouse->x, mouse->y);
}

void treat_mouse_click_in_home (mouse_t *mouse, game_cond_t *game_cond, ALLEGRO_EVENT event) {
    int play_click, sound_click, help_click;

    play_click = event.mouse.x >= 88 && event.mouse.x <= 328 && event.mouse.y >= 378 && event.mouse.y <= 429;
    sound_click = event.mouse.x >= 176 && event.mouse.x <= 238 && event.mouse.y >= 516 && event.mouse.y <= 577;
    help_click = event.mouse.x >= 12 && event.mouse.x <= 45 && event.mouse.y >= 9 && event.mouse.y <= 39;

    if (play_click) {
        game_cond->in_home_page = false;
        game_cond->in_help_page = false;
    }
    if (help_click) {
        game_cond->in_home_page = false;
        game_cond->in_help_page = true;
    }
    if (sound_click) game_cond->sound_on = ! game_cond->sound_on;
}

void treat_mouse_click_in_help (mouse_t *mouse, game_cond_t *game_cond, ALLEGRO_EVENT event) {
    int back_click;
    
    back_click = event.mouse.x >= 20 && event.mouse.x <= 37 && event.mouse.y >= 18 && event.mouse.y <= 42;

    if (back_click) {
        game_cond->in_home_page = true;
        game_cond->in_help_page = false;
    }
}

void treat_mouse_click_in_game (mouse_t *mouse, game_cond_t *game_cond, ALLEGRO_EVENT event) {
    printf ("Posição x do click: %d\n", event.mouse.x);
    printf ("Posição y do mouse: %d\n",event.mouse.y);
    printf ("Botão apertado: %d\n", event.mouse.button);
}