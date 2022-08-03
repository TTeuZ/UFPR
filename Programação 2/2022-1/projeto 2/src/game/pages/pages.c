#include "pages.h"

void draw_home_page (player_points_t p_points, ALLEGRO_FONT *title_font, ALLEGRO_FONT *button_font, ALLEGRO_FONT *points_font, game_cond_t game_cond, ALLEGRO_BITMAP *sound) {
    int intern_coins = p_points.coins;
    int decimal_cases = 0;
    while ((intern_coins = intern_coins / 10) > 0) decimal_cases++;

    al_clear_to_color (al_map_rgb(32, 32, 32));

    // Icone de duvida
    al_draw_filled_circle (30, 26, 15, al_map_rgb(255, 255, 255));
    al_draw_textf (button_font, al_map_rgb(0, 0, 0), 27, 9, 0, "I");

    // moedas
    al_draw_textf (points_font, al_map_rgb(255, 255, 255), 375 - ((6 + decimal_cases)  * decimal_cases), 10, 0, "%d", p_points.coins);
    al_draw_circle (400, 24, 7, al_map_rgb(255, 178, 102), 2);

    // titulo
    al_draw_textf (title_font, al_map_rgb(255, 255, 255), 110, 100, 0, "B");
    al_draw_textf (title_font, al_map_rgb(255, 178, 102), 163, 100, 0, "a");
    al_draw_textf (title_font, al_map_rgb(0, 102, 204), 220, 100, 0, "l");
    al_draw_textf (title_font, al_map_rgb(0, 153, 76), 240, 100, 0, "l");
    al_draw_textf (title_font, al_map_rgb(153, 255, 51), 263, 100, 0, "z");

    // botão de play
    al_draw_filled_rounded_rectangle (90, 380, 330, 430, 25, 25, al_map_rgb (204, 0, 102));
    al_draw_textf (button_font, al_map_rgb(255, 255, 255), 180, 386, 0, "PLAY");

    // icone de som
    if (game_cond.sound_on) 
        al_draw_circle (210, 550, 30, al_map_rgb(204, 0, 102), 2);
    else 
        al_draw_circle (210, 550, 30, al_map_rgb(160, 160, 160), 2);
    al_draw_bitmap (sound, 192, 535, 0);
}

void draw_help_page (ALLEGRO_FONT *title_font, ALLEGRO_FONT *text_font, ALLEGRO_BITMAP *back) {
    al_clear_to_color (al_map_rgb(32, 32, 32));

    // Icone de retorno
    al_draw_bitmap (back, 20, 20, 0);

    // Titulo
    al_draw_textf (title_font, al_map_rgb(255, 255, 255), 75, 130, 0, "Como jogar");

    // Mira
    al_draw_textf (text_font, al_map_rgb(255, 255, 255), 30, 200, 0, "Pressione com o mouse para ajustar");
    al_draw_textf (text_font, al_map_rgb(255, 255, 255), 135, 220, 0, "o angulo de tiro");

    // final de jogo
    al_draw_textf (text_font, al_map_rgb(255, 255, 255), 25, 270, 0, "Se os quadrados chegarem na ultima");
    al_draw_textf (text_font, al_map_rgb(255, 255, 255), 125, 290, 0, "linha você perde!");

    // Adicionar bolas
    al_draw_filled_rectangle (50, 450, 100, 500, al_map_rgb (255, 255, 255));
    al_draw_textf (text_font, al_map_rgb(255, 255, 255), 125, 460, 0, "+ 1  bola no jogo!");

    // Moedas
    al_draw_filled_rectangle (50, 550, 100, 600, al_map_rgb (255, 255, 255));
    al_draw_textf (text_font, al_map_rgb(255, 255, 255), 125, 560, 0, "+ 1  moeda!");
}