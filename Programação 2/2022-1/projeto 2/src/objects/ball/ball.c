#include "ball.h"

ball_t *add_ball () {
    ball_t *ball;

    if ((ball = malloc (sizeof (ball_t)))) {
        ball->x = BUFFER_WIDTH/2;
        ball->y = BUFFER_HEIGHT/2;
        ball->speed = 1;
        return ball;
    } else return NULL;
}