#include "logic.h"

void check_wall_collision (player_game_t *p_game, game_objects_t *g_obj, withdraw_t *withdraw) {
    int count;
    float x, y, diference;

    for (count = 0; count < g_obj->balls_qtd; count++) {
        x = g_obj->balls[count]->x;
        y = g_obj->balls[count]->y;

        // Verifica os cantos superiores
        if ((x - BALL_RADIUS) < START_X_AREA && (y - BALL_RADIUS) < START_Y_AREA) {
            g_obj->balls[count]->dx *= -1;
            g_obj->balls[count]->dy *= -1;
            g_obj->balls[count]->y = START_Y_AREA + BALL_RADIUS;
            g_obj->balls[count]->x = START_X_AREA + BALL_RADIUS;
        } else if ((x + BALL_RADIUS) >= END_X_AREA && (y - BALL_RADIUS) <= START_Y_AREA) {
            g_obj->balls[count]->dx *= -1;
            g_obj->balls[count]->dy *= -1;
            g_obj->balls[count]->y = START_Y_AREA + BALL_RADIUS;
            g_obj->balls[count]->x = END_X_AREA - BALL_RADIUS;
        }
        
        // Bounce normal da tela
        else if ((x - BALL_RADIUS) < START_X_AREA) {
            g_obj->balls[count]->dx *= -1;
            g_obj->balls[count]->x = START_X_AREA + BALL_RADIUS;
        } else if ((y - BALL_RADIUS) < START_Y_AREA) {
            g_obj->balls[count]->dy *= -1;
            g_obj->balls[count]->y = START_Y_AREA + BALL_RADIUS;
        } else if ((x + BALL_RADIUS) > END_X_AREA){
            g_obj->balls[count]->dx *= -1;
            g_obj->balls[count]->x = END_X_AREA - BALL_RADIUS;
        } else if ((y + BALL_RADIUS) >= END_Y_AREA && g_obj->balls[count]->playable) {
            g_obj->balls[count]->y = INITIAL_Y_POSITION;

            if (! withdraw->first_reach) {
                stop_ball (g_obj->balls[count]);
                p_game->temp_init_x = x;
                withdraw->first_reach = true;
                withdraw->in_game_balls--;
            } else {
                diference = x - p_game->temp_init_x;
                if (ABS (diference) < STOP_EPSILON) {
                    stop_ball (g_obj->balls[count]);
                    withdraw->in_game_balls--;
                } else g_obj->balls[count]->dx = -1 * (diference / 10.0f);
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
        withdraw->first_reach = false;
        withdraw->w_ball = 0;

        p_game->initial_x = p_game->temp_init_x;
        p_game->points++;
    }
}

void restart_game (player_game_t *p_game) {
    // int count;

    // p_game->initial_x = INITIAL_X_POSITION;
    // p_game->balls_qtd = 1;
    // p_game->points = 1; 

    // for (count = 0; count < p_game->balls_qtd; count++) {
    //     p_game->balls[count]->x = INITIAL_X_POSITION;
    //     p_game->balls[count]->y = INITIAL_Y_POSITION;
    //     stop_ball (p_game->balls[count]);
    // }
}
