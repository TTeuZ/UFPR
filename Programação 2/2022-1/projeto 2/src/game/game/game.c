#include "game.h"
#include <stdio.h>

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
}

void treat_withdraw (player_game_t *p_game, withdraw_t *withdraw){
    if (withdraw->w_ball == p_game->balls_qtd) 
        withdraw->all_played = true;
    else if (withdraw->w_count == WITHDRAW_TIME) {
        p_game->balls[withdraw->w_ball]->playable = true;
        withdraw->in_game_balls++;
        withdraw->w_count = 0;
        withdraw->w_ball++;
    }

    if (!withdraw->all_played) withdraw->w_count++;
}

void check_wall_collision (player_game_t *p_game, withdraw_t *withdraw) {
    int count;
    float x, y;

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
            if (withdraw->w_ball == p_game->balls_qtd) {
                p_game->balls[count]->dy *= 0;
                p_game->balls[count]->dx *= 0;
                p_game->balls[count]->playable = false;
                p_game->initial_x = x;
                withdraw->w_ball--;
                withdraw->in_game_balls--;
            } else {
                if (ABS (x - p_game->initial_x) < __FLT_EPSILON__) {
                    p_game->balls[count]->playable = false;
                    withdraw->in_game_balls--;
                }
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

void destroy_game (player_game_t *p_game) {
    int count;
    
    for (count = 0; count < p_game->balls_qtd; count++)
        free (p_game->balls[count]);
    free (p_game->balls);
}