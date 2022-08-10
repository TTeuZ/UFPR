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

void destroy_mouse (mouse_t *mouse) {
    al_destroy_bitmap (mouse->arrow);
    al_destroy_mouse_cursor (mouse->cursor);
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
    int play_click, sound_click, help_click;

    play_click = event.mouse.x >= 90 && event.mouse.x <= 330 && event.mouse.y >= 380 && event.mouse.y <= 430;
    sound_click = event.mouse.x >= 176 && event.mouse.x <= 238 && event.mouse.y >= 516 && event.mouse.y <= 577;
    help_click = event.mouse.x >= 12 && event.mouse.x <= 45 && event.mouse.y >= 9 && event.mouse.y <= 39;

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
}

void treat_mouse_click_in_help (mouse_t *mouse, pages_t *pages, ALLEGRO_EVENT event) {
    int back_click;
    
    back_click = event.mouse.x >= 20 && event.mouse.x <= 37 && event.mouse.y >= 18 && event.mouse.y <= 42;

    if (back_click) {
        pages->in_home_page = true;
        pages->in_help_page = false;
    }
}

void treat_mouse_click_in_pause (mouse_t *mouse, pages_t *pages, general_t *general, audios_t audios, ALLEGRO_EVENT event) {
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
        if (general->sound_on) play_audio (audios.click, CLICK_GAIN, CLICK_SPEED);;
    }
}

void treat_mouse_click_in_game (mouse_t *mouse, pages_t *pages, aim_t *aim, ALLEGRO_EVENT event) {
    int hud_click, pause_click;

    hud_click = event.mouse.y <= SQUARE_SIZE;
    pause_click = hud_click && (event.mouse.x >= 20 && event.mouse.x <= 40 && event.mouse.y >=20 && event.mouse.y <= 43);

    if (pause_click) {
        pages->in_pause_page = true;
        pages->in_game_page = false;
    }
    if (! hud_click) {
        mouse->pressed = 1;
        aim->pressed_x = event.mouse.x;
        aim->pressed_y = event.mouse.y;
    }
}