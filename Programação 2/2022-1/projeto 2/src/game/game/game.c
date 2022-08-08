#include "game.h"

void draw_game_section (player_game_t p_game, fonts_t fonts, game_cond_t game_cond) {
    int count;
    // Área do jogo
    al_draw_filled_rectangle (0, SQUARE_SIZE, BUFFER_WIDTH, SQUARE_SIZE * 9, al_map_rgb (DARK_GRAY));

    // draws das bolinhas
    if (! game_cond.in_game)
        al_draw_textf (fonts.balls, al_map_rgb (WHITE), p_game.initial_x - 10, INITIAL_Y_POSITION - 30, 0, "%dx", p_game.balls_qtd);
    // al_draw_textf (fonts.points, al_map_rgb (WHITE), BUFFER_WIDTH/2, 13, ALLEGRO_ALIGN_CENTER, "%d", p_game.points);
    for (count = 0; count < p_game.balls_qtd; count++) 
        draw_ball (p_game.balls[count]);
}

void play_balls (player_game_t *p_game, aim_t aim) {
    int count;

    for (count = 0; count < p_game->balls_qtd; count++) {
        p_game->balls[count]->dx = -1 * aim.cos;
        p_game->balls[count]->dy = -1 * aim.sin;
    }
}

void destroy_game (player_game_t *p_game) {
    int count;
    
    for (count = 0; count < p_game->balls_qtd; count++)
        free (p_game->balls[count]);
    free (p_game->balls);
}