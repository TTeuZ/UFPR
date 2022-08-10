#include "game.h"

void draw_game_section (player_game_t p_game, fonts_t fonts, stages_t stages) {
    int count;
    // Área do jogo
    al_draw_filled_rectangle (0, SQUARE_SIZE, BUFFER_WIDTH, SQUARE_SIZE * 9, al_map_rgb (DARK_GRAY));

    // draws das bolinhas
    if (! stages.in_game)
        al_draw_textf (fonts.balls, al_map_rgb (WHITE), p_game.initial_x - 10, INITIAL_Y_POSITION - 30, 0, "%dx", p_game.balls_qtd);

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

void check_wall_collision (player_game_t *p_game, stages_t *stages) {
    int count;
    float x, y;

    for (count = 0; count < p_game->balls_qtd; count++) {
        x = p_game->balls[count]->x;
        y = p_game->balls[count]->y;

        // Verifica os cantos superiores
        if ((x - BALL_RADIUS) <= START_X_AREA && (y - BALL_RADIUS) <= START_Y_AREA) {
            p_game->balls[count]->dx *= -1;
            p_game->balls[count]->dy *= -1;
        } else if ((x + BALL_RADIUS) >= END_X_AREA && (y - BALL_RADIUS) <= START_Y_AREA) {
            p_game->balls[count]->dx *= -1;
            p_game->balls[count]->dy *= -1;
        }
        
        // Bounce normal da tela
        else if ((x - BALL_RADIUS) <= START_X_AREA)
            p_game->balls[count]->dx *= -1;
        else if ((y - BALL_RADIUS) <= START_Y_AREA) 
            p_game->balls[count]->dy *= -1;
        else if ((x + BALL_RADIUS) >= END_X_AREA)
            p_game->balls[count]->dx *= -1;
        else if ((y + BALL_RADIUS) >= END_Y_AREA) {
            p_game->balls[count]->dy *= 0;
            p_game->balls[count]->dx *= 0;

            p_game->initial_x = x;
            p_game->points++;
            stages->in_game = 0;
        }
    }
}

void destroy_game (player_game_t *p_game) {
    int count;
    
    for (count = 0; count < p_game->balls_qtd; count++)
        free (p_game->balls[count]);
    free (p_game->balls);
}