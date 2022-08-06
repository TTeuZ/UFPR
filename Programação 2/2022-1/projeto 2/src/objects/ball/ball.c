#include "ball.h"

ball_t *add_ball () {
    ball_t *ball;

    if ((ball = malloc (sizeof (ball_t)))) {
        ball->x = BUFFER_WIDTH/2;
        ball->y = (SQUARE_SIZE * 9) - BALL_RADIUS;
        ball->speed = 1;
        return ball;
    } else return NULL;
}

void draw_ball (ball_t *ball) {
    al_draw_filled_circle (ball->x, ball->y, BALL_RADIUS, al_map_rgb (WHITE));
}