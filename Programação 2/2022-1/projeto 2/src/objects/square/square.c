#include "square.h"

// ------------------------- Funções internas -------------------------

void set_square_pos (int *s_x, int *e_x, int *s_y, int *e_y, int col) {
    *s_x += SQUARE_PADDING;
    *e_x += (SQUARE_SIZE - SQUARE_PADDING);
    *s_y += SQUARE_PADDING;
    *e_y += (SQUARE_SIZE - SQUARE_PADDING);
    if (col == 0) *s_x += SQUARE_PADDING;
    if (col == MAP_COLS - 1) *e_x -= SQUARE_PADDING;
}

// ------------------------- Funções internas -------------------------

void add_square (square_t *square, int points, int line, int col) {
    square->points = points;
    square->x = col * SQUARE_SIZE;
    square->y = (line + 1) * SQUARE_SIZE;
}

void draw_squares (square_t squares[MAP_LINES][MAP_COLS]) {
    int line, col;
    int s_x, e_x, s_y, e_y;

    for (line = 0; line < MAP_LINES; line++)
        for (col = 0; col < MAP_COLS; col++) {
            if (squares[line][col].points != 0) {
                s_x = e_x = squares[line][col].x;
                s_y = e_y = squares[line][col].y;
                set_square_pos (&s_x, &e_x, &s_y, &e_y, col);
                al_draw_filled_rectangle (s_x, s_y, e_x, e_y, al_map_rgb ((255 - (5 * squares[line][col].points)), ((255 - 5 * squares[line][col].points)), (5 * squares[line][col].points)));
            }
        }
}