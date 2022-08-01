#include "mouse.h"
#include <stdio.h>

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