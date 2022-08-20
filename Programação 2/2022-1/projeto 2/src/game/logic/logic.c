#include "logic.h"

void check_square_collision (game_objects_t *g_obj, speeder_t speeder) {
    square_t *center, *left, *right;
    float last_x, last_y, next_x, next_y;
    int last_l, last_c, next_l, next_c;
    int x_direction, y_direction;
    int left_x, right_y;
    int count;

    double ca, co, h;
    double cos, sin;


    for (count = 0; count < g_obj->balls_qtd; count++) {
        last_x = g_obj->balls[count]->x - (g_obj->balls[count]->dx * speeder.bust);
        last_y = g_obj->balls[count]->y - (g_obj->balls[count]->dy * speeder.bust);
        next_x = g_obj->balls[count]->x + (g_obj->balls[count]->dx * speeder.bust);
        next_y = g_obj->balls[count]->y + (g_obj->balls[count]->dy * speeder.bust);

        last_l = ((last_y - SQUARE_SIZE) / SQUARE_SIZE);
        last_c = (last_x / SQUARE_SIZE);
        next_l = ((next_y - SQUARE_SIZE) / SQUARE_SIZE);
        next_c = (next_x / SQUARE_SIZE);
        if (last_c < 0) last_c = 0;
        if (last_l < 0) last_l = 0;
        if (next_c >= MAP_COLS) next_c = MAP_COLS - 1;
        if (next_l >= MAP_LINES) next_l = MAP_LINES - 1;

        x_direction = next_c - last_c;
        y_direction = next_l - last_l;

        if (! (x_direction == 0 && y_direction == 0)) {
            if (x_direction != 0 && y_direction != 0) {
                left_x = last_c + x_direction;
                right_y = last_l + y_direction;

                if (left_x >= MAP_COLS || left_x <= 0) left_x = last_c;
                if (right_y >= MAP_LINES || right_y <= 0) right_y = last_l;

                center = &g_obj->squares[right_y][left_x];
                left = &g_obj->squares[right_y][last_c];
                right = &g_obj->squares[last_l][left_x];

                if (left->points != 0 && right->points != 0) {
                    g_obj->balls[count]->dy *= -1;
                    g_obj->balls[count]->dx *= -1;
                    right->points--;
                    left->points--;
                } else if (center->points != 0) {
                    h = sqrt (pow ((next_x - last_x), 2) + pow ((next_y - last_y), 2));
                    co = sqrt (pow ((next_y - last_y), 2));
                    ca = sqrt (pow ((next_x - last_x), 2));

                    cos = ca / h;
                    sin = co / h;

                    g_obj->balls[count]->dy = BALL_SPEED * sin;
                    if (next_x < last_x) g_obj->balls[count]->dx = BALL_SPEED * cos;
                    else g_obj->balls[count]->dx = -BALL_SPEED * cos;
                    center->points--;
                }
            } else {
                center = &g_obj->squares[next_l][next_c];
                if (center->points != 0) {
                    if (x_direction == 1 || x_direction == -1) {
                        g_obj->balls[count]->dx *= -1;
                    } else if (y_direction == 1 || y_direction == -1) {
                        g_obj->balls[count]->dy *= -1;
                    }
                    center->points--;
                }
            }
        }
    }
}

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
                } else g_obj->balls[count]->dx = -1 * (diference / 5.0f);
            }
        }
    }
}

int verify_first_line (game_objects_t *g_obj) {
    int col;
    for (col = 0; col < MAP_COLS; col++) {
        if (g_obj->squares[0][col].points != 0) return true;
    }
    return false;
}

int verify_last_line (game_objects_t *g_obj) {
    int col;
    for (col = 0; col < MAP_COLS; col++) {
        if (g_obj->squares[MAP_LINES - 2][col].points != 0) return true;
    }
    return false;
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
    p_game->initial_x = INITIAL_X_POSITION;
    p_game->points = 1; 
}
