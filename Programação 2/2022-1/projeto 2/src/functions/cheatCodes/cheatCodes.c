#include "cheatCodes.h"

int start_cheats (cheats_t *cheats) {
    cheats->yudi_used = false; 
    cheats->yudi_qtd = 0;
    memset (cheats->yudi, 0, sizeof (cheats->yudi));

    cheats->rain_used = false;
    cheats->rain_clicks = 0;
    return EXIT_SUCCESS;
}

int treat_yudi_cheat (cheats_t *cheats, game_objects_t *g_obj, ALLEGRO_EVENT event) {
    char yudi_res[YUDI_CHEAT_SIZE] = {31, 27, 27, 29, 35, 36, 29, 29};

    if (! cheats->yudi_used) {
        cheats->yudi[cheats->yudi_qtd] = event.keyboard.keycode;
        cheats->yudi_qtd++;
        if (strncmp (cheats->yudi, yudi_res, cheats->yudi_qtd) != 0) {
            memset (cheats->yudi, 0, sizeof (cheats->yudi));
            cheats->yudi_qtd = 0;
        }
        if (cheats->yudi_qtd == YUDI_CHEAT_SIZE) {
            cheats->yudi_used = true;
            return double_balls (g_obj);
        }
    }
    return EXIT_SUCCESS;
}

void treat_rain_cheat (cheats_t *cheats, game_objects_t *g_obj, ALLEGRO_EVENT event) {
    int x, y, pos, count;
    int ball_click;

    if (! cheats->rain_used) {
        x = g_obj->balls[0]->x;
        y = g_obj->balls[0]->y;

        ball_click = event.mouse.x > (x - BALL_RADIUS) && event.mouse.x < (x + BALL_RADIUS) && event.mouse.y > ( - BALL_RADIUS) && event.mouse.y < (y + BALL_RADIUS);

        if (ball_click) cheats->rain_clicks++;
        if (cheats->rain_clicks == RAIN_CHEAT_CLIKS_TO_ACTIVE) {
            for (count = 0; count < RAIN_CHEAT_CLIKS_TO_ACTIVE; count++) {
                pos = 10 + rand () % (BUFFER_WIDTH - 10);
                pre_add_ball (g_obj->pre_add_balls, &g_obj->pre_add_qtd, pos, (START_Y_AREA + BALL_RADIUS));
            }
            cheats->rain_used = true;
        }
    }
}