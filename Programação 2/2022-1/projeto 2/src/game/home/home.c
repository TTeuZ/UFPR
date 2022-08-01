#include "home.h"

void draw_home_page (player_points_t p_points, ALLEGRO_FONT *font, ALLEGRO_FONT *button_font, ALLEGRO_FONT *points_font, game_cond_t game_cond, ALLEGRO_BITMAP *sound) {
    int intern_coins = p_points.coins;
    int decimal_cases = 0;
    while ((intern_coins = intern_coins / 10) > 0) decimal_cases++;

    al_clear_to_color(al_map_rgb(32, 32, 32));

    // Icone de duvida
    al_draw_filled_circle (30, 26, 15, al_map_rgb(255, 255, 255));
    al_draw_textf (button_font, al_map_rgb(0, 0, 0), 27, 9, 0, "I");

    // moedas
    al_draw_textf (points_font, al_map_rgb(255, 255, 255), 435 - ((6 + decimal_cases)  * decimal_cases), 10, 0, "%d", p_points.coins);
    al_draw_circle (460, 24, 7, al_map_rgb(255, 178, 102), 2);

    // titulo
    al_draw_textf (font, al_map_rgb(204, 0, 102), 140, 100, 0, "B");
    al_draw_textf (font, al_map_rgb(255, 178, 102), 193, 100, 0, "a");
    al_draw_textf (font, al_map_rgb(0, 102, 204), 250, 100, 0, "l");
    al_draw_textf (font, al_map_rgb(0, 153, 76), 270, 100, 0, "l");
    al_draw_textf (font, al_map_rgb(153, 255, 51), 293, 100, 0, "z");

    // botão de play
    al_draw_filled_rounded_rectangle (120, 380, 360, 430, 25, 25, al_map_rgb (204, 0, 102));
    al_draw_textf (button_font, al_map_rgb(255, 255, 255), 210, 386, 0, "PLAY");

    // icone de som
    if (game_cond.sound_on) 
        al_draw_circle (240, 550, 30, al_map_rgb(204, 0, 102), 2);
    else 
        al_draw_circle (240, 550, 30, al_map_rgb(160, 160, 160), 2);
    al_draw_bitmap (sound, 222, 535, 0);
}