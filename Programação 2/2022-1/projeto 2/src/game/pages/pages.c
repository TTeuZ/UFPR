#include "pages.h"

void draw_home_page (player_points_t p_points, fonts_t fonts, general_t general, images_t images) {
    int intern_coins = p_points.coins;
    int decimal_cases = 0;
    while ((intern_coins = intern_coins / 10) > 0) decimal_cases++;

    al_clear_to_color (al_map_rgb (GRAY));

    // Icone de duvida
    al_draw_filled_circle (30, 26, 15, al_map_rgb (WHITE));
    al_draw_textf (fonts.button, al_map_rgb (BLACK), 27, 9, 0, "I");

    // moedas
    al_draw_textf (fonts.coins, al_map_rgb (WHITE), 375 - ((6 + decimal_cases)  * decimal_cases), 10, 0, "%d", p_points.coins);
    al_draw_circle (400, 24, 7, al_map_rgb (GOLDEN), 2);

    // titulo
    al_draw_textf (fonts.title_h1, al_map_rgb (PINK), 110, 100, 0, "B");
    al_draw_textf (fonts.title_h1, al_map_rgb (GOLDEN), 163, 100, 0, "a");
    al_draw_textf (fonts.title_h1, al_map_rgb (BLUE), 220, 100, 0, "l");
    al_draw_textf (fonts.title_h1, al_map_rgb (GREEN), 240, 100, 0, "l");
    al_draw_textf (fonts.title_h1, al_map_rgb (LIGHT_GREEN), 263, 100, 0, "z");

    // botão de play
    al_draw_filled_rounded_rectangle (90, 380, 330, 430, 25, 25, al_map_rgb (PINK));
    al_draw_textf (fonts.button, al_map_rgb (WHITE), BUFFER_WIDTH/2, 386, ALLEGRO_ALIGN_CENTER, "PLAY");

    // icone de som
    if (general.sound_on) 
        al_draw_circle (175, 550, 30, al_map_rgb (PINK), 2);
    else 
        al_draw_circle (175, 550, 30, al_map_rgb (LIGHT_GRAY), 2);
    al_draw_bitmap (images.sound, 157, 535, 0);

    // icone de loja
    al_draw_circle (245, 550, 30, al_map_rgb (LIGHT_GREEN), 2);
    al_draw_bitmap (images.balls, 229, 534, 0);
}

void draw_shop_page (player_points_t p_points, fonts_t fonts, images_t images, shop_item_t items[ITEMS_SIZE]){
    int line, col, count;
    int i_x, e_x, i_y, e_y;
    int intern_coins = p_points.coins;
    int decimal_cases = 0;
    while ((intern_coins = intern_coins / 10) > 0) decimal_cases++;

    al_clear_to_color (al_map_rgb (NORMAL_GRAY));

    // Icone de retorno
    al_draw_bitmap (images.back, 20, 20, 0);

    // Moedas
    al_draw_textf (fonts.coins, al_map_rgb (WHITE), 375 - ((6 + decimal_cases)  * decimal_cases), 18, 0, "%d", p_points.coins);
    al_draw_circle (400, 32, 7, al_map_rgb (GOLDEN), 2);

    // Titulo
    al_draw_textf (fonts.title_h2, al_map_rgb (WHITE), BUFFER_WIDTH/2, 80, ALLEGRO_ALIGN_CENTER, "Shop");

    // Linha de separacao
    al_draw_filled_rectangle (START_X_AREA + 20, 160, END_X_AREA - 20, 165, al_map_rgb (DARK_GRAY));

    for (line = 0; line < MAX_ITEM_LINE; line++) {
        for (col = 0; col < MAX_ITEM_COL; col++) {
            count = (line * MAX_ITEM_COL) + col;
            i_x = (30 * (col + 1)) + (100 * col);
            e_x = (30 * (col + 1)) + (100 * (col + 1));
            i_y = 190 + (100 * line) + (30 * line);
            e_y = 190 + (100 * (line + 1)) + (30 * line);

            al_draw_filled_rectangle (i_x, i_y, e_x, e_y, al_map_rgb (DARK_GRAY));

            if (items[count].buyed) {
                al_draw_filled_circle ((i_x + e_x) / 2, (i_y + e_y) / 2, BALL_RADIUS + 5, al_map_rgb (items[count].r, items[count].g, items[count].b));
                if (items[count].in_use) al_draw_rectangle (i_x, i_y, e_x, e_y, al_map_rgb (YELLOW), 2); 
            } else {
                al_draw_bitmap (images.lock, ((i_x + e_x) / 2) - 15, ((i_y + e_y) / 2) - 30, ALLEGRO_ALIGN_CENTER);

                if (p_points.coins >= items[count].price) {
                    al_draw_textf (fonts.coins, al_map_rgb (WHITE), ((i_x + e_x) / 2), ((i_y + e_y) / 2) + 10, ALLEGRO_ALIGN_CENTER, "%d", items[count].price);
                    al_draw_circle (((i_x + e_x) / 2) + 30, ((i_y + e_y) / 2) + 25, 7, al_map_rgb (GOLDEN), 2);
                } else {
                    al_draw_textf (fonts.coins, al_map_rgb (LIGHT_GRAY), ((i_x + e_x) / 2), ((i_y + e_y) / 2) + 10, ALLEGRO_ALIGN_CENTER, "%d", items[count].price);
                    al_draw_circle (((i_x + e_x) / 2) + 30, ((i_y + e_y) / 2) + 25, 7, al_map_rgb (LIGHT_GRAY), 2);
                } 
            }
        }
    }
}

void draw_help_page (fonts_t fonts, images_t images) {
    al_clear_to_color (al_map_rgb (NORMAL_GRAY));

    // Icone de retorno
    al_draw_bitmap (images.back, 20, 20, 0);

    // Titulo
    al_draw_textf (fonts.title_h2, al_map_rgb (WHITE), BUFFER_WIDTH/2, 130, ALLEGRO_ALIGN_CENTER, "Como jogar");

    // Mira
    al_draw_textf (fonts.text_help, al_map_rgb (WHITE), BUFFER_WIDTH/2, 200, ALLEGRO_ALIGN_CENTER, "Pressione com o mouse para ajustar");
    al_draw_textf (fonts.text_help, al_map_rgb (WHITE), BUFFER_WIDTH/2, 220, ALLEGRO_ALIGN_CENTER, "o angulo de tiro");

    // final de jogo
    al_draw_textf (fonts.text_help, al_map_rgb (WHITE), 25, 270, 0, "Se os quadrados chegarem na ultima");
    al_draw_textf (fonts.text_help, al_map_rgb (WHITE), 125, 290, 0, "linha você perde!");

    // Adicionar bolas
    al_draw_filled_circle (75, 475, ADD_BALL_RADIUS, al_map_rgb (WHITE));
    al_draw_circle (75, 475, ARC_LIMIT, al_map_rgb (WHITE), 3);
    al_draw_textf (fonts.text_help, al_map_rgb (WHITE), 125, 460, 0, "+ 1  bola no jogo!");

    // Moedas
    al_draw_circle (75, 575, COIN_IN_GAME_RADIUS, al_map_rgb (GOLDEN), 3);
    al_draw_textf (fonts.text_help, al_map_rgb (WHITE), 125, 560, 0, "+ 1  moeda!");
}

void draw_pause_page (fonts_t fonts, images_t images, general_t general) {
    al_clear_to_color (al_map_rgb (NORMAL_GRAY));

    // Titulo
    al_draw_textf (fonts.title_h2, al_map_rgb (WHITE), BUFFER_WIDTH/2, 180, ALLEGRO_ALIGN_CENTER, "PAUSE");

    // Botão de continue
    al_draw_filled_rounded_rectangle (90, 262, 330, 312, 25, 25, al_map_rgb (PINK));
    al_draw_textf (fonts.button, al_map_rgb (WHITE), BUFFER_WIDTH/2, 270, ALLEGRO_ALIGN_CENTER, "CONTINUE");

    // botão de restart
    al_draw_filled_rounded_rectangle (90, 332, 330, 382, 25, 25, al_map_rgb (YELLOW));
    al_draw_textf (fonts.button, al_map_rgb (WHITE), BUFFER_WIDTH/2, 340, ALLEGRO_ALIGN_CENTER, "RESTART");

    // botão de main menu
    al_draw_filled_rounded_rectangle (90, 402, 330, 452, 25, 25, al_map_rgb (CIANO));
    al_draw_textf (fonts.button, al_map_rgb (WHITE), BUFFER_WIDTH/2, 410, ALLEGRO_ALIGN_CENTER, "MAIN MENU");

    // icone do som
    if (general.sound_on) 
        al_draw_circle (210, 550, 30, al_map_rgb (PINK), 2);
    else 
        al_draw_circle (210, 550, 30, al_map_rgb (LIGHT_GRAY), 2);
    al_draw_bitmap (images.sound, 192, 535, 0);
}

void draw_end_game_page (player_game_t p_game, player_points_t p_points, fonts_t fonts) {
    al_clear_to_color (al_map_rgb (NORMAL_GRAY));

    al_draw_textf (fonts.title_h1, al_map_rgb (WHITE), BUFFER_WIDTH/2, 150, ALLEGRO_ALIGN_CENTER, "%d", p_game.points);
    al_draw_textf (fonts.title_h2, al_map_rgb (WHITE), BUFFER_WIDTH/2, 260, ALLEGRO_ALIGN_CENTER, "BEST %d", p_points.record);

    // botão de restart
    al_draw_filled_rounded_rectangle (90, 362, 330, 412, 25, 25, al_map_rgb (PINK));
    al_draw_textf (fonts.button, al_map_rgb (WHITE), BUFFER_WIDTH/2, 370, ALLEGRO_ALIGN_CENTER, "RESTART");

    // botão de main menu
    al_draw_filled_rounded_rectangle (90, 442, 330, 492, 25, 25, al_map_rgb (CIANO));
    al_draw_textf (fonts.button, al_map_rgb (WHITE), BUFFER_WIDTH/2, 450, ALLEGRO_ALIGN_CENTER, "MAIN MENU");
}

void draw_game_page (player_game_t p_game, player_points_t p_points, fonts_t fonts, images_t images) {
    int intern_coins = p_points.coins;
    int decimal_cases = 0;
    while ((intern_coins = intern_coins / 10) > 0) decimal_cases++;

    al_clear_to_color (al_map_rgb (NORMAL_GRAY));
    
    // Icone de pausa
    al_draw_bitmap (images.pause, 20, 20, ALLEGRO_ALIGN_CENTER);

    // Record Atual
    al_draw_textf (fonts.text_record, al_map_rgb (WHITE), (SQUARE_SIZE/2)*3, 12, ALLEGRO_ALIGN_CENTER, "BEST");
    al_draw_textf (fonts.coins, al_map_rgb (WHITE), (SQUARE_SIZE/2)*3, 27, ALLEGRO_ALIGN_CENTER, "%d", p_points.record);

    // Pontuação atual
    al_draw_textf (fonts.points, al_map_rgb (WHITE), BUFFER_WIDTH/2, 13, ALLEGRO_ALIGN_CENTER, "%d", p_game.points);

    // moedas
    al_draw_textf (fonts.coins, al_map_rgb (WHITE), 375 - ((6 + decimal_cases)  * decimal_cases), 18, 0, "%d", p_points.coins);
    al_draw_circle (400, 32, 7, al_map_rgb (GOLDEN), 2);

    // Área do jogo
    al_draw_filled_rectangle (START_X_AREA, START_Y_AREA, END_X_AREA, END_Y_AREA, al_map_rgb (DARK_GRAY));
}