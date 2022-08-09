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
    float dx, dy;

    dy = -8 * aim.sin;
    if (aim.move_x < aim.pressed_x) dx = 8 * aim.cos;
    else dx = -8 * aim.cos;

    for (count = 0; count < p_game->balls_qtd; count++) {
        p_game->balls[count]->dx = dx;
        p_game->balls[count]->dy = dy;
    }
}

void check_wall_collision (player_game_t *p_game, game_cond_t *game_cond) {
    int count;
    float x, y;

    for (count = 0; count < p_game->balls_qtd; count++) {
        x = p_game->balls[count]->x;
        y = p_game->balls[count]->y;

        if ((x - BALL_RADIUS) <= 0)
            p_game->balls[count]->dx *= -1;
        else if ((y - BALL_RADIUS) <= 60) 
            p_game->balls[count]->dy *= -1;
        else if ((x + BALL_RADIUS) >= BUFFER_WIDTH)
            p_game->balls[count]->dx *= -1;
        else if ((y + BALL_RADIUS) >= 540) {
            p_game->balls[count]->dy *= 0;
            p_game->balls[count]->dx *= 0;

            p_game->initial_x = x;
            p_game->points++;
            game_cond->in_game = 0;
        }
    }
}

void destroy_game (player_game_t *p_game) {
    int count;
    
    for (count = 0; count < p_game->balls_qtd; count++)
        free (p_game->balls[count]);
    free (p_game->balls);
}