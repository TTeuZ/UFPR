#include "display.h"

int create_display (ALLEGRO_DISPLAY **display) {
    if (! (*display = al_create_display (DISPLAY_WIDTH, DISPLAY_HEIGHT))) 
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}