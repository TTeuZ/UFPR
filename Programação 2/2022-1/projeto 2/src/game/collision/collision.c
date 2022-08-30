#include "collision.h"

void check_square_collision (game_objects_t *g_obj, speeder_t speeder, general_t general, audios_t audios) {
    square_t *center, *left, *right;
    float last_x, last_y, next_x, next_y;
    int last_l, last_c, next_l, next_c;
    int x_direction, y_direction;
    int left_c, right_l;
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
                left_c = last_c + x_direction;
                right_l = last_l + y_direction;

                if (left_c >= MAP_COLS || left_c < 0) left_c = last_c;
                if (right_l >= MAP_LINES || right_l < 0) right_l = last_l;

                center = &g_obj->squares[right_l][left_c];
                left = &g_obj->squares[right_l][last_c];
                right = &g_obj->squares[last_l][left_c];

                if (left->points != 0 && right->points != 0) {
                    g_obj->balls[count]->dy *= -1;
                    g_obj->balls[count]->dx *= -1;
                    right->points--;
                    left->points--;
                    if (general.sound_on) play_audio (audios.hit, HIT_GAIN, HIT_SPEED);
                } else if (right->points != 0 && center->points != 0) {
                    right->points--;
                    center->points--;
                    g_obj->balls[count]->dx *= -1;
                    if (general.sound_on) play_audio (audios.hit, HIT_GAIN, HIT_SPEED);
                } else if (left->points != 0 && center->points != 0) {
                    left->points--;
                    center->points--;
                    g_obj->balls[count]->dy *= -1;
                    if (general.sound_on) play_audio (audios.hit, HIT_GAIN, HIT_SPEED);
                } else if (center->points != 0) {            
                    h = sqrt (pow ((next_x - last_x), 2) + pow ((next_y - last_y), 2));
                    co = sqrt (pow ((next_y - last_y), 2));
                    ca = sqrt (pow ((next_x - last_x), 2));

                    cos = ca / h;
                    sin = co / h;

                    if (next_y < last_y) g_obj->balls[count]->dy = BALL_SPEED * cos;
                    else g_obj->balls[count]->dy = -BALL_SPEED * cos;
                    
                    if (next_x < last_x) g_obj->balls[count]->dx = BALL_SPEED * sin;
                    else g_obj->balls[count]->dx = -BALL_SPEED * sin;

                    center->points--;
                    if (general.sound_on) play_audio (audios.hit, HIT_GAIN, HIT_SPEED);
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
                    if (general.sound_on) play_audio (audios.hit, HIT_GAIN, HIT_SPEED);
                }
            }
        }
    }
}

void check_add_ball_collision (game_objects_t *g_obj) {
    add_ball_t *add_ball;
    float x, y;
    int line, col, c_x, c_y; 
    int count;

    for (count = 0; count < g_obj->balls_qtd; count++) {
        x = g_obj->balls[count]->x;
        y = g_obj->balls[count]->y;

        line = ((y - SQUARE_SIZE) / SQUARE_SIZE);
        col = (x / SQUARE_SIZE);
        if (col >= MAP_COLS) col = MAP_COLS - 1;
        if (line >= MAP_LINES) line = MAP_LINES - 1;

        add_ball = &g_obj->add_balls[line][col];

        if (add_ball->show) {
            c_x = add_ball->x + (SQUARE_SIZE / 2);
            c_y = add_ball->y + (SQUARE_SIZE / 2);
            if (x >= (c_x - ARC_LIMIT) && x <= (c_x + ARC_LIMIT) && y >= (c_y - ARC_LIMIT) && y <= (c_y + ARC_LIMIT)) {
                pre_add_ball (g_obj->pre_add_balls, &g_obj->pre_add_qtd, c_x, c_y);
                add_ball->show = false;
            }
        }
    }
}
void check_coin_collision (player_points_t *p_points, game_objects_t *g_obj, audios_t audios) {
    coin_t *coin;
    float x, y;
    int line, col, c_x, c_y; 
    int count;

    for (count = 0; count < g_obj->balls_qtd; count++) {
        x = g_obj->balls[count]->x;
        y = g_obj->balls[count]->y;

        line = ((y - SQUARE_SIZE) / SQUARE_SIZE);
        col = (x / SQUARE_SIZE);
        if (col >= MAP_COLS) col = MAP_COLS - 1;
        if (line >= MAP_LINES) line = MAP_LINES - 1;

        coin = &g_obj->coins[line][col];

        if (coin->show) {
            c_x = coin->x + (SQUARE_SIZE / 2);
            c_y = coin->y + (SQUARE_SIZE / 2);
            if (x >= (c_x - COIN_IN_GAME_RADIUS) && x <= (c_x + COIN_IN_GAME_RADIUS) && y >= (c_y - COIN_IN_GAME_RADIUS) && y <= (c_y + COIN_IN_GAME_RADIUS)) {
                coin->show = false;
                p_points->coins++;
                play_audio (audios.coin, COIN_GAIN, COIN_SPEED);
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