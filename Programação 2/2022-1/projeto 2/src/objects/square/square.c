#include "square.h"

void add_square (square_t *square, int points, int line, int col) {
    square->points = points;
    square->x = col * SQUARE_SIZE;
    square->y = (line + 1) * SQUARE_SIZE;
}

void draw_squares (square_t squares[MAP_LINES][MAP_COLS]) {
    int line, col;
    for (line = 0; line < MAP_LINES; line++)
        for (col = 0; col < MAP_COLS; col++) {
            if (squares[line][col].points != 0) {
                al_draw_filled_rectangle (squares[line][col].x, squares[line][col].y, squares[line][col].x + SQUARE_SIZE, squares[line][col].y + SQUARE_SIZE, al_map_rgb (GREEN));
            }
        }
}