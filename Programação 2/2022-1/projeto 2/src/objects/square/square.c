#include "square.h"

// ------------------------- Funções internas -------------------------

/*!
    \brief Função que seta as posições x e y iniciais e finais do quadrado
    \param s_x Posição x inicial
    \param e_x Posição x final
    \param s_y Posição y inicial
    \param e_y Posição y final
    \param col Coluna em que o quadrado esta
*/
void set_square_pos (int *s_x, int *e_x, int *s_y, int *e_y, int col) {
    *s_x += SQUARE_MARGIN;
    *e_x += (SQUARE_SIZE - SQUARE_MARGIN);
    *s_y += SQUARE_MARGIN;
    *e_y += (SQUARE_SIZE - SQUARE_MARGIN);
    if (col == 0) *s_x += SQUARE_MARGIN;
    if (col == MAP_COLS - 1) *e_x -= SQUARE_MARGIN;
}

/*!
    \brief função que seta os valores iniciais de coloração para os quadrados
    \param square Ponteiro de acesso para a estrutura de um quadrado
*/
void set_initial_color (square_t *square) {
    if (square->points <= 5) {
        square->r = 255;
        square->g = 160;
        square->b = 0;
    } else if (square->points <= 12) {
        square->r = 0;
        square->g = 150;
        square->b = 0;
    } else if (square->points <= 30) {
        square->r = 255;
        square->g = 0;
        square->b = 100;
    } else if (square->points > 30) {
        square->r = 170;
        square->g = 0;
        square->b = 110;
    }
}

// ------------------------- Funções internas -------------------------

void add_square (square_t *square, int points, int line, int col) {
    square->points = points;
    square->x = col * SQUARE_SIZE;
    square->y = (line + 1) * SQUARE_SIZE;
    set_initial_color (square);
}

void draw_squares (square_t squares[MAP_LINES][MAP_COLS], fonts_t fonts) {
    int line, col;
    int s_x, e_x, s_y, e_y;
    int points;

    for (line = 0; line < MAP_LINES; line++)    
        for (col = 0; col < MAP_COLS; col++) {
            points = squares[line][col].points;
            if (points != 0) {
                s_x = e_x = squares[line][col].x;
                s_y = e_y = squares[line][col].y;
                set_square_pos (&s_x, &e_x, &s_y, &e_y, col);

                al_draw_filled_rectangle (s_x, s_y, e_x, e_y, al_map_rgb (squares[line][col].r, squares[line][col].g, squares[line][col].b));
                al_draw_textf (fonts.square, al_map_rgb (DARK_GRAY), (s_x + e_x)/2, (s_y + 11), ALLEGRO_ALIGN_CENTER, "%d", points);
            }
        }
}