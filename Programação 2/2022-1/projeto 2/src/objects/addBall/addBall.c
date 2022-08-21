#include "addBall.h"

void add_add_ball (add_ball_t *add_ball, int line, int col) {
    add_ball->x = col * SQUARE_SIZE;
    add_ball->y = (line + 1) * SQUARE_SIZE;
    add_ball->show = true;
    add_ball->arc_radius = INITIAL_ARC_RADIUS;
    add_ball->adder = 1;
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