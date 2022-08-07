#include "game.h"

void draw_game_section (player_game_t p_game) {
    int count;
    // Área do jogo
    al_draw_filled_rectangle (0, SQUARE_SIZE, BUFFER_WIDTH, SQUARE_SIZE * 9, al_map_rgb (DARK_GRAY));

    // draws das bolinhas
    for (count = 0; count < p_game.balls_qtd; count++) 
        draw_ball (p_game.balls[count]);
}

void destroy_game (player_game_t *p_game) {
    int count;
    
    for (count = 0; count < p_game->balls_qtd; count++)
        free (p_game->balls[count]);
    free (p_game->balls);
}