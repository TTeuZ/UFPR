#include "withdraw.h"

void start_withdraw_conditions (withdraw_t *withdraw) {
    withdraw->w_ball = 0;
    withdraw->in_game_balls = 0;
    withdraw->w_count = WITHDRAW_TIME;
    withdraw->all_played = false;
    withdraw->first_reach = false;
}

void treat_withdraw (game_objects_t *g_obj, withdraw_t *withdraw) {
    if (withdraw->w_ball == g_obj->balls_qtd) 
        withdraw->all_played = true;
    else if (withdraw->w_count == WITHDRAW_TIME) {
        g_obj->balls[withdraw->w_ball]->playable = true;
        withdraw->w_count = 0;
        withdraw->in_game_balls++;
        withdraw->w_ball++;
    }

    if (!withdraw->all_played) withdraw->w_count++;
}