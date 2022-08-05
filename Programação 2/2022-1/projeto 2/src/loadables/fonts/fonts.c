#include "fonts.h"

int load_fonts (fonts_t *fonts) {
    if (! (fonts->title_home = al_load_ttf_font ("./resources/fonts/poppins.ttf", TITLE_HOME, 0)))
        return EXIT_FAILURE;
    if (! (fonts->title_help = al_load_ttf_font ("./resources/fonts/poppins.ttf", TITLE_HELP, 0)))
        return EXIT_FAILURE;
    if (! (fonts->text_help = al_load_ttf_font ("./resources/fonts/poppins.ttf", TEXT_HELP, 0)))
        return EXIT_FAILURE;
    if (! (fonts->text_record = al_load_ttf_font ("./resources/fonts/poppins.ttf", TEXT_RECORD, 0)))
        return EXIT_FAILURE;
    if (! (fonts->button = al_load_ttf_font ("./resources/fonts/poppins.ttf", BUTTON, 0)))
        return EXIT_FAILURE;
    if (! (fonts->points = al_load_ttf_font ("./resources/fonts/poppins.ttf", POINTS, 0)))
        return EXIT_FAILURE;
    if (! (fonts->coins = al_load_ttf_font ("./resources/fonts/poppins.ttf", COINS, 0)))
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void destroy_fonts (fonts_t *fonts) {
    al_destroy_font (fonts->title_home);
    al_destroy_font (fonts->title_help);
    al_destroy_font (fonts->text_help);
    al_destroy_font (fonts->text_record);
    al_destroy_font (fonts->button);
    al_destroy_font (fonts->points);
    al_destroy_font (fonts->coins);
}