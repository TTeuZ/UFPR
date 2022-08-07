#include "ball.h"

ball_t *add_ball () {
    ball_t *ball;

    if ((ball = malloc (sizeof (ball_t)))) {
        ball->x = INITIAL_X_POSITION;
        ball->y = INITIAL_Y_POSITION;
        ball->speed = 1;
        return ball;
    } else return NULL;
}

void draw_ball (ball_t *ball) {
    al_draw_filled_circle (ball->x, ball->y, BALL_RADIUS, al_map_rgb (WHITE));
}