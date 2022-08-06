#include "game.h"

void draw_game_section (player_game_t p_game) {
    // Área do jogo
    al_draw_filled_rectangle (0, SQUARE_SIZE, BUFFER_WIDTH, SQUARE_SIZE * 9, al_map_rgb (20, 20, 20));
}