#include "addBall.h"

void add_add_ball (add_ball_t *add_ball, int line, int col) {
    add_ball->x = col * SQUARE_SIZE;
    add_ball->y = (line + 1) * SQUARE_SIZE;
    add_ball->show = true;
    add_ball->arc_radius = INITIAL_ARC_RADIUS;
    add_ball->adder = 1;
}

void pre_add_ball (ball_t balls[MAP_COLS], int *qtd, int x, int y) {
    balls[*qtd].x = x;
    balls[*qtd].y = y;
    *qtd  += 1;
}

void update_pre_add_balls (ball_t balls[MAP_COLS], int qtd) {
    int count;

    for (count = 0; count < qtd; count++) {
        if (balls[count].y >= INITIAL_Y_POSITION) balls[count].y = INITIAL_Y_POSITION;
        else balls[count].y += BALL_SPEED;
    }
}

void draw_pre_add_balls (ball_t balls[MAP_COLS], int qtd) {
    int count;

    for (count = 0; count < qtd; count++) 
        al_draw_filled_circle (balls[count].x, balls[count].y, BALL_RADIUS, al_map_rgb (GREEN));
}

void draw_add_balls (add_ball_t add_balls[MAP_LINES][MAP_COLS], int a_frame) {
    int line, col;
    int c_x, c_y;

     for (line = 0; line < MAP_LINES; line++)    
        for (col = 0; col < MAP_COLS; col++) {
            if (add_balls[line][col].show) {
                c_x = add_balls[line][col].x + (SQUARE_SIZE / 2);
                c_y = add_balls[line][col].y + (SQUARE_SIZE / 2);

                if (! (a_frame % ADD_BALL_ARC_ANIMATION)) {
                    add_balls[line][col].arc_radius += add_balls[line][col].adder;
                    if (add_balls[line][col].arc_radius == ARC_LIMIT || add_balls[line][col].arc_radius == INITIAL_ARC_RADIUS) add_balls[line][col].adder *= -1;
                }

                al_draw_filled_circle (c_x, c_y, ADD_BALL_RADIUS, al_map_rgb (WHITE));
                al_draw_circle (c_x, c_y, add_balls[line][col].arc_radius, al_map_rgb (WHITE), 3);
            }
        }
}