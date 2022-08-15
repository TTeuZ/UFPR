#include "withdraw.h"

void start_withdraw_conditions (withdraw_t *withdraw) {
    withdraw->w_ball = 0;
    withdraw->in_game_balls = 0;
    withdraw->w_count = WITHDRAW_TIME;
    withdraw->all_played = false;
}

void treat_withdraw (player_game_t *p_game, withdraw_t *withdraw){
    if (withdraw->w_ball == p_game->balls_qtd) 
        withdraw->all_played = true;
    else if (withdraw->w_count == WITHDRAW_TIME) {
        p_game->balls[withdraw->w_ball]->playable = true;
        withdraw->w_count = 0;
        withdraw->in_game_balls++;
        withdraw->w_ball++;
    }

    if (!withdraw->all_played) withdraw->w_count++;
}