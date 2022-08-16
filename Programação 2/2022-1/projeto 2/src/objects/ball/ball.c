#include "ball.h"

ball_t *add_ball (int x) {
    ball_t *ball;

    if ((ball = malloc (sizeof (ball_t)))) {
        ball->playable = false;
        ball->x = x;
        ball->y = INITIAL_Y_POSITION;
        ball->dx = 0;
        ball->dy = 0;
        return ball;
    } else return NULL;
}

void play_balls (ball_t **balls, int qtd, aim_t aim) {
    int count;
    float dx, dy;

    dy = -BALL_SPEED * aim.sin;
    if (aim.move_x < aim.pressed_x) dx = BALL_SPEED * aim.cos;
    else dx = -BALL_SPEED * aim.cos;

    for (count = 0; count < qtd; count++) {
        balls[count]->dx = dx;
        balls[count]->dy = dy;
    }
}

void update_balls (ball_t **balls, int qtd, speeder_t speeder) {
    int count;
    for (count = 0; count < qtd; count++) {
        if (balls[count]->playable) {
            balls[count]->x += balls[count]->dx * speeder.bust;
            balls[count]->y += balls[count]->dy * speeder.bust;
        }
    }
}

void stop_ball (ball_t *ball) {
    ball->dy *= 0;
    ball->dx *= 0;
    ball->playable = false;
}

void draw_balls (ball_t **balls, int qtd, int initial_x, fonts_t fonts, stages_t stages) {
    int count;

    // draws das bolinhas
    if (! stages.in_game)
        al_draw_textf (fonts.balls, al_map_rgb (WHITE), initial_x - 10, INITIAL_Y_POSITION - 30, 0, "%dx", qtd);

    for (count = 0; count < qtd; count++) 
        al_draw_filled_circle (balls[count]->x, balls[count]->y, BALL_RADIUS, al_map_rgb (WHITE));
}