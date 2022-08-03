#include "display.h"

int create_display (ALLEGRO_DISPLAY **display, ALLEGRO_BITMAP **buffer) {
    if (! (*display = al_create_display (DISPLAY_WIDTH, DISPLAY_HEIGHT))) 
        return EXIT_FAILURE;
    if (! (*buffer = al_create_bitmap (BUFFER_WIDTH, BUFFER_HEIGHT))) 
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void destroy_display (ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *buffer) {
    al_destroy_display (display);
    al_destroy_bitmap (buffer);
}

void flip_buffer_display (ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *buffer) {
    al_set_target_backbuffer (display);
    al_draw_scaled_bitmap (buffer, 0, 0, BUFFER_WIDTH, BUFFER_HEIGHT, 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0);
    al_flip_display ();
}