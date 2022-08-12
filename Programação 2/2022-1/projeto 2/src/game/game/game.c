#include "game.h"

void play_balls (player_game_t *p_game, aim_t aim) {
    int count;
    float dx, dy;

    dy = -BALL_SPEED * aim.sin;
    if (aim.move_x < aim.pressed_x) dx = BALL_SPEED * aim.cos;
    else dx = -BALL_SPEED * aim.cos;

    for (count = 0; count < p_game->balls_qtd; count++) {
        p_game->balls[count]->dx = dx;
        p_game->balls[count]->dy = dy;
    }
    p_game->initial_x = -1;
}

void check_wall_collision (player_game_t *p_game, withdraw_t *withdraw) {
    int count;
    float x, y, diference;

    for (count = 0; count < p_game->balls_qtd; count++) {
        x = p_game->balls[count]->x;
        y = p_game->balls[count]->y;

        // Verifica os cantos superiores
        if ((x - BALL_RADIUS) < START_X_AREA && (y - BALL_RADIUS) < START_Y_AREA) {
            p_game->balls[count]->dx *= -1;
            p_game->balls[count]->dy *= -1;
            p_game->balls[count]->y = START_Y_AREA + BALL_RADIUS;
            p_game->balls[count]->x = START_X_AREA + BALL_RADIUS;
        } else if ((x + BALL_RADIUS) >= END_X_AREA && (y - BALL_RADIUS) <= START_Y_AREA) {
            p_game->balls[count]->dx *= -1;
            p_game->balls[count]->dy *= -1;
            p_game->balls[count]->y = START_Y_AREA + BALL_RADIUS;
            p_game->balls[count]->x = END_X_AREA - BALL_RADIUS;
        }
        
        // Bounce normal da tela
        else if ((x - BALL_RADIUS) < START_X_AREA) {
            p_game->balls[count]->dx *= -1;
            p_game->balls[count]->x = START_X_AREA + BALL_RADIUS;
        }
        else if ((y - BALL_RADIUS) < START_Y_AREA) {
            p_game->balls[count]->dy *= -1;
            p_game->balls[count]->y = START_Y_AREA + BALL_RADIUS;
        }
        else if ((x + BALL_RADIUS) > END_X_AREA){
            p_game->balls[count]->dx *= -1;
            p_game->balls[count]->x = END_X_AREA - BALL_RADIUS;
        }
        else if ((y + BALL_RADIUS) >= END_Y_AREA && p_game->balls[count]->playable) {
            p_game->balls[count]->y = INITIAL_Y_POSITION;
            if (p_game->initial_x == -1) {
                stop_ball (p_game->balls[count]);
                p_game->initial_x = x;
                withdraw->in_game_balls--;
            } else {
                diference = x - p_game->initial_x;
                if (ABS (diference) < __FLT_EPSILON__ * 10000) {
                    stop_ball (p_game->balls[count]);
                    withdraw->in_game_balls--;
                } else p_game->balls[count]->dx = -1 * (diference / 10.0f);
            }
        }
    }
}

void treat_end_phase (player_game_t *p_game, stages_t *stages, withdraw_t *withdraw) {
    if (withdraw->in_game_balls == 0) {
        stages->in_game = false;
        stages->end_phase = true;
        withdraw->w_count = WITHDRAW_TIME;
        withdraw->all_played = false;
        withdraw->w_ball = 0;
        p_game->points++;
    }
}

void restart_game (player_game_t *p_game) {
    int count;

    p_game->initial_x = INITIAL_X_POSITION;
    p_game->balls_qtd = 1;
    p_game->points = 1; 

    for (count = 0; count < p_game->balls_qtd; count++) {
        p_game->balls[count]->x = INITIAL_X_POSITION;
        p_game->balls[count]->y = INITIAL_Y_POSITION;
        stop_ball (p_game->balls[count]);
    }
}

void destroy_game (player_game_t *p_game) {
    int count;
    
    for (count = 0; count < p_game->balls_qtd; count++)
        free (p_game->balls[count]);
    free (p_game->balls);
}

void draw_balls (player_game_t p_game, fonts_t fonts, stages_t stages) {
    int count;

    // draws das bolinhas
    if (! stages.in_game)
        al_draw_textf (fonts.balls, al_map_rgb (WHITE), p_game.initial_x - 10, INITIAL_Y_POSITION - 30, 0, "%dx", p_game.balls_qtd);

    for (count = 0; count < p_game.balls_qtd; count++) 
        draw_ball (p_game.balls[count]);
}