#include <stdio.h>
#include "mouse.h"

int start_mouse (mouse_t *mouse) {
    mouse->x = 0;
    mouse->y = 0;
    mouse->pressed = 0;
    if (! (mouse->arrow = al_load_bitmap ("./resources/images/cursor.png")))
        return EXIT_FAILURE;
    if (! (mouse->cursor = al_create_mouse_cursor (mouse->arrow, 0, 0)))
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int set_mouse_display (ALLEGRO_DISPLAY *display, mouse_t mouse) {
    if (! al_set_mouse_cursor (display, mouse.cursor))
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void treat_mouse_move (ALLEGRO_DISPLAY *display, mouse_t *mouse, ALLEGRO_EVENT event) {
    mouse->x = event.mouse.x;
    mouse->y = event.mouse.y;
    al_set_mouse_xy (display, mouse->x, mouse->y);
}

void treat_mouse_click_in_home (mouse_t *mouse, pages_t *pages, general_t *general, audios_t audios, ALLEGRO_EVENT event) {
    int play_click, help_click, sound_click, shop_click;

    play_click = event.mouse.x >= 90 && event.mouse.x <= 330 && event.mouse.y >= 380 && event.mouse.y <= 430;
    help_click = event.mouse.x >= 12 && event.mouse.x <= 45 && event.mouse.y >= 9 && event.mouse.y <= 39;
    sound_click = event.mouse.x >= 145 && event.mouse.x <= 205 && event.mouse.y >= 516 && event.mouse.y <= 577;
    shop_click = event.mouse.x >= 215 && event.mouse.x <= 275 && event.mouse.y >= 516 && event.mouse.y <= 577;

    if (play_click) {
        pages->in_home_page = false;
        pages->in_help_page = false;
        pages->in_game_page = true;
        if (general->sound_on) play_audio (audios.click, CLICK_GAIN, CLICK_SPEED);
    }
    if (help_click) {
        pages->in_home_page = false;
        pages->in_game_page = false;
        pages->in_help_page = true;
    }
    if (sound_click) {
        general->sound_on = ! general->sound_on;
        if (general->sound_on) play_audio (audios.click, CLICK_GAIN, CLICK_SPEED);
    }
    if (shop_click) {
        pages->in_home_page = false;
        pages->in_shop_page = true;
    }
}

void treat_mouse_click_in_shop (mouse_t *mouse, player_points_t *p_points, shop_item_t items[ITEMS_SIZE], pages_t *pages, general_t *general, ALLEGRO_EVENT event) {
    int back_click;
    int line, col, pos;

    line = col = -1;
    pos = p_points->ball_in_use;

    back_click = event.mouse.x >= 20 && event.mouse.x <= 37 && event.mouse.y >= 18 && event.mouse.y <= 42;

    if (event.mouse.x >= 30 && event.mouse.x <= 130) col = 0;
    if (event.mouse.x >= 160 && event.mouse.x <= 260) col = 1;
    if (event.mouse.x >= 290 && event.mouse.x <= 390) col = 2;

    if (event.mouse.y >= 190 && event.mouse.y <= 290) line = 0;
    if (event.mouse.y >= 320 && event.mouse.y <= 420) line = 1;
    if (event.mouse.y >= 459 && event.mouse.y <= 550) line = 2;

    if (line != -1 && col != -1) pos = (line * MAX_ITEM_COL) + col;

    if (pos != p_points->ball_in_use) {
        if (items[pos].buyed) {
            items[pos].in_use = true;
            items[p_points->ball_in_use].in_use = false;
            p_points->ball_in_use = pos;
        } else {
            verify_and_buy (items, p_points, pos);
        }
    }

    if (back_click) {
        pages->in_home_page = true;
        pages->in_shop_page = false;
    }
}

void treat_mouse_click_in_help (mouse_t *mouse, pages_t *pages, ALLEGRO_EVENT event) {
    int back_click;
    
    back_click = event.mouse.x >= 20 && event.mouse.x <= 37 && event.mouse.y >= 18 && event.mouse.y <= 42;

    if (back_click) {
        pages->in_home_page = true;
        pages->in_help_page = false;
    }
}

void treat_mouse_click_in_pause (pages_t *pages, general_t *general, audios_t audios, ALLEGRO_EVENT event) {
    int continue_click, restart_click, menu_click, sound_click;

    continue_click = event.mouse.x >= 90 && event.mouse.x <= 330 && event.mouse.y >= 262 && event.mouse.y <= 312;
    restart_click = event.mouse.x >= 90 && event.mouse.x <= 330 && event.mouse.y >= 332 && event.mouse.y <= 382;
    menu_click = event.mouse.x >= 90 && event.mouse.x <= 330 && event.mouse.y >= 402 && event.mouse.y <= 452;
    sound_click = event.mouse.x >= 176 && event.mouse.x <= 238 && event.mouse.y >= 516 && event.mouse.y <= 577;

    if (continue_click) {
        pages->in_pause_page = false;
        pages->in_game_page = true;
        if (general->sound_on) play_audio (audios.click, CLICK_GAIN, CLICK_SPEED);
    }
    if (restart_click) {
        pages->in_pause_page = false;
        pages->in_game_page = true;
        general->restart = true;
        if (general->sound_on) play_audio (audios.click, CLICK_GAIN, CLICK_SPEED);
    }
    if (menu_click) {
        pages->in_pause_page = false;
        pages->in_game_page = false;
        pages->in_home_page = true;
    }
    if (sound_click) {
        general->sound_on = ! general->sound_on;
        if (general->sound_on) play_audio (audios.click, CLICK_GAIN, CLICK_SPEED);
    }
}

void treat_mouse_click_in_end_game (pages_t *pages, general_t *general, ALLEGRO_EVENT event) {
    int restart_click, menu_click;

    restart_click = event.mouse.x >= 90 && event.mouse.x <= 362 && event.mouse.y >= 332 && event.mouse.y <= 412;
    menu_click = event.mouse.x >= 90 && event.mouse.x <= 362 && event.mouse.y >= 442 && event.mouse.y <= 492;

    if (restart_click) {
        pages->in_end_game_page = false;
        pages->in_game_page = true;
        general->restart = true;
    }
    if (menu_click) {
        pages->in_end_game_page = false;
        pages->in_home_page = true;
        general->restart = true;
    } 

}

void treat_mouse_click_in_game (mouse_t *mouse, pages_t *pages, aim_t *aim, speeder_t *speeder, ALLEGRO_EVENT event) {
    int hud_click, pause_click, speeder_click;

    hud_click = event.mouse.y <= START_Y_AREA;
    pause_click = hud_click && (event.mouse.x >= 20 && event.mouse.x <= 40 && event.mouse.y >= 20 && event.mouse.y <= 43);
    speeder_click = (event.mouse.x >= 258 && event.mouse.x <= 405 && event.mouse.y >= 70 && event.mouse.y <= 90);

    if (pause_click) {
        pages->in_pause_page = true;
        pages->in_game_page = false;
    }
    if (speeder->is_enable && speeder_click) 
        speeder->bust = SPEEDER_BUST;
    if (! hud_click) {
        mouse->pressed = true;
        aim->pressed_x = event.mouse.x;
        aim->pressed_y = event.mouse.y;
    }
}   

void destroy_mouse (mouse_t *mouse) {
    al_destroy_bitmap (mouse->arrow);
    al_destroy_mouse_cursor (mouse->cursor);
}
