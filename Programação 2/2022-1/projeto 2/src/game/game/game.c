#include "game.h"

void play_balls (player_game_t *p_game, aim_t aim) {
    int count;
    float dx, dy;

    dy = -8 * aim.sin;
    if (aim.move_x < aim.pressed_x) dx = 8 * aim.cos;
    else dx = -8 * aim.cos;

    for (count = 0; count < p_game->balls_qtd; count++) {
        p_game->balls[count]->dx = dx;
        p_game->balls[count]->dy = dy;
    }
}

void treat_withdraw (player_game_t *p_game, withdraw_t *withdraw){
    if (withdraw->w_ball == p_game->balls_qtd) 
        withdraw->all_played = true;
    else if (withdraw->w_count == WITHDRAW_TIME) {
        p_game->balls[withdraw->w_ball]->playable = true;
        withdraw->in_game_balls++;
        withdraw->w_count = 0;
        withdraw->w_ball++;
    }

    if (!withdraw->all_played) withdraw->w_count++;
}

void check_wall_collision (player_game_t *p_game, withdraw_t *withdraw) {
    int count;
    float x, y;

    for (count = 0; count < p_game->balls_qtd; count++) {
        x = p_game->balls[count]->x;
        y = p_game->balls[count]->y;

        // Verifica os cantos superiores
        if ((x - BALL_RADIUS) <= START_X_AREA && (y - BALL_RADIUS) <= START_Y_AREA) {
            p_game->balls[count]->dx *= -1;
            p_game->balls[count]->dy *= -1;
        } else if ((x + BALL_RADIUS) >= END_X_AREA && (y - BALL_RADIUS) <= START_Y_AREA) {
            p_game->balls[count]->dx *= -1;
            p_game->balls[count]->dy *= -1;
        }
        
        // Bounce normal da tela
        else if ((x - BALL_RADIUS) <= START_X_AREA)
            p_game->balls[count]->dx *= -1;
        else if ((y - BALL_RADIUS) <= START_Y_AREA) 
            p_game->balls[count]->dy *= -1;
        else if ((x + BALL_RADIUS) >= END_X_AREA)
            p_game->balls[count]->dx *= -1;
        else if ((y + BALL_RADIUS) >= END_Y_AREA && p_game->balls[count]->playable) {
            p_game->balls[count]->dy *= 0;
            p_game->balls[count]->dx *= 0;
            p_game->balls[count]->playable = false;
            if (withdraw->w_ball == p_game->balls_qtd) p_game->initial_x = x;
            withdraw->in_game_balls--;
        }
    }
}

void treat_end_phase (player_game_t *p_game, stages_t *stages, withdraw_t *withdraw) {
    if (withdraw->in_game_balls == 0) {
        stages->in_game = 0;
        withdraw->w_count = WITHDRAW_TIME;
        withdraw->all_played = false;
        withdraw->w_ball = 0;
        p_game->points++;
    }
}

void destroy_game (player_game_t *p_game) {
    int count;
    
    for (count = 0; count < p_game->balls_qtd; count++)
        free (p_game->balls[count]);
    free (p_game->balls);
}