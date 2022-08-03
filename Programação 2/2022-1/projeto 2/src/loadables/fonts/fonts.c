#include "fonts.h"

int load_fonts (fonts_t *fonts) {
    if (! (fonts->title_home = al_load_ttf_font ("./resources/fonts/poppins.ttf", 90, 0)))
        return EXIT_FAILURE;
    if (! (fonts->button_home = al_load_ttf_font ("./resources/fonts/poppins.ttf", 25, 0)))
        return EXIT_FAILURE;
    if (! (fonts->points_home = al_load_ttf_font ("./resources/fonts/poppins.ttf", 20, 0)))
        return EXIT_FAILURE;
    if (! (fonts->title_help = al_load_ttf_font ("./resources/fonts/poppins.ttf", 45, 0)))
        return EXIT_FAILURE;
    if (! (fonts->text_help = al_load_ttf_font ("./resources/fonts/poppins.ttf", 20, 0)))
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void destroy_fonts (fonts_t *fonts) {
    al_destroy_font (fonts->title_home);
    al_destroy_font (fonts->button_home);
    al_destroy_font (fonts->points_home);
    al_destroy_font (fonts->title_help);
    al_destroy_font (fonts->text_help);
}