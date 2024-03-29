#include "fonts.h"

int load_fonts (fonts_t *fonts) {
    if (! (fonts->title_h1 = al_load_ttf_font ("./resources/fonts/poppins.ttf", TITLE_H1, 0)))
        return EXIT_FAILURE;
    if (! (fonts->title_h2 = al_load_ttf_font ("./resources/fonts/poppins.ttf", TITLE_H2, 0)))
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
    if (! (fonts->balls = al_load_ttf_font ("./resources/fonts/poppins.ttf", BALLS, 0)))
        return EXIT_FAILURE;
    if (! (fonts->speeder = al_load_ttf_font ("./resources/fonts/poppins.ttf", SPEEDER, 0)))
        return EXIT_FAILURE;
    if (! (fonts->square = al_load_ttf_font ("./resources/fonts/poppins.ttf", SQUARE, 0)))
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void destroy_fonts (fonts_t *fonts) {
    al_destroy_font (fonts->title_h1);
    al_destroy_font (fonts->title_h2);
    al_destroy_font (fonts->text_help);
    al_destroy_font (fonts->text_record);
    al_destroy_font (fonts->button);
    al_destroy_font (fonts->points);
    al_destroy_font (fonts->coins);
    al_destroy_font (fonts->balls);
    al_destroy_font (fonts->speeder);
    al_destroy_font (fonts->square);
}