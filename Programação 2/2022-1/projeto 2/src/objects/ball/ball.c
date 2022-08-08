#include "ball.h"

ball_t *add_ball (int x) {
    ball_t *ball;

    if ((ball = malloc (sizeof (ball_t)))) {
        ball->x = x;
        ball->y = INITIAL_Y_POSITION;
        ball->dx = 0;
        ball->dy = 0;
        return ball;
    } else return NULL;
}

void update_balls (ball_t **balls, int qtd) {
    int count;
    for (count = 0; count < qtd; count++) {
        balls[count]->x += balls[count]->dx;
        balls[count]->y += balls[count]->dy;
    }
}

void draw_ball (ball_t *ball) {
    al_draw_filled_circle (ball->x, ball->y, BALL_RADIUS, al_map_rgb (WHITE));
}