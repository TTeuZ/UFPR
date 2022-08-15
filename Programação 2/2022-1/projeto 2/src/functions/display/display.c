#include "display.h"

int create_display (ALLEGRO_DISPLAY **display, ALLEGRO_BITMAP **buffer) {
    al_set_new_display_option (ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option (ALLEGRO_SAMPLES, 1, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags (ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
    
    if (! (*display = al_create_display (DISPLAY_WIDTH, DISPLAY_HEIGHT))) 
        return EXIT_FAILURE;
    if (! (*buffer = al_create_bitmap (BUFFER_WIDTH, BUFFER_HEIGHT))) 
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void flip_buffer_display (ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *buffer) {
    al_set_target_backbuffer (display);
    al_draw_scaled_bitmap (buffer, 0, 0, BUFFER_WIDTH, BUFFER_HEIGHT, 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0);
    al_flip_display ();
}

void destroy_display (ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *buffer) {
    al_destroy_display (display);
    al_destroy_bitmap (buffer);
}