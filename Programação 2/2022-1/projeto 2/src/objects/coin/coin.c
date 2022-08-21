#include "coin.h"

void add_coin (coin_t *coin, int line, int col) {
    coin->x = col * SQUARE_SIZE;
    coin->y = (line + 1) * SQUARE_SIZE;
    coin->show = true;
}

void draw_coins (coin_t coins[MAP_LINES][MAP_COLS]) {
    int line, col;
    int c_x, c_y;
    
     for (line = 0; line < MAP_LINES; line++)    
        for (col = 0; col < MAP_COLS; col++) {
            if (coins[line][col].show) {
                c_x = coins[line][col].x + (SQUARE_SIZE / 2);
                c_y = coins[line][col].y + (SQUARE_SIZE / 2);
                al_draw_circle (c_x, c_y, 12, al_map_rgb (GOLDEN), 3);
            }
        }
}