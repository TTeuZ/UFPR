#include <stdio.h>
#include <stdlib.h>

// Allegro
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

// Objetos
#include "./src/objects/addBall/addBall.h"
#include "./src/objects/ball/ball.h"
#include "./src/objects/coin/coin.h"
#include "./src/objects/square/square.h"

// Funções
#include "./src/functions/display/display.h"
#include "./src/functions/mouse/mouse.h"
#include "./src/functions/utils/utils.h"

// Composição do jogo
#include "./src/game/game/game.h"
#include "./src/game/pages/pages.h"
#include "./src/game/player/player.h"

int main () {
    // inicialização dos dados do jogo
    game_cond_t game_cond;
    player_points_t p_points;
    start_game_conditions (&game_cond);
    read_player_points (&p_points);

    // Inicializações gerais
    if (! al_init ()) game_cond.all_init = INIT_ERROR;
    else if (! al_install_keyboard ()) game_cond.all_init = INIT_ERROR;
    else if (! (al_init_primitives_addon ())) game_cond.all_init = INIT_ERROR;

    // FPS e eventos
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_EVENT event;
    if (! (timer = al_create_timer (FPS))) game_cond.all_init = INIT_ERROR;
    else if (! (queue = al_create_event_queue ())) game_cond.all_init = INIT_ERROR;

    // Display
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_BITMAP *buffer = NULL;
    if (create_display (&display, &buffer)) game_cond.all_init = INIT_ERROR;

    // imagens
    ALLEGRO_BITMAP *sound;
    if (! (al_init_image_addon ())) game_cond.all_init = INIT_ERROR;
    else if (! (sound = al_load_bitmap ("./resources/images/music.png"))) game_cond.all_init = INIT_ERROR;

    // mouse
    mouse_t mouse;
    ALLEGRO_MOUSE_CURSOR *cursor = NULL;
    if (! al_install_mouse ()) game_cond.all_init = INIT_ERROR;
    else if (start_mouse (&mouse)) game_cond.all_init = INIT_ERROR;
    else if (set_mouse_display (cursor, display, mouse)) game_cond.all_init = INIT_ERROR;

    // fontes
    ALLEGRO_FONT *title_font;
    ALLEGRO_FONT *button_font;
    ALLEGRO_FONT *points_font;
    if (! (al_init_font_addon ())) game_cond.all_init = INIT_ERROR;
    else if (! (al_init_ttf_addon ())) game_cond.all_init = INIT_ERROR;
    else if (! (title_font = al_load_ttf_font ("./resources/fonts/poppins.ttf", 90, 0))) game_cond.all_init = INIT_ERROR;
    else if (! (button_font = al_load_ttf_font ("./resources/fonts/poppins.ttf", 25, 0))) game_cond.all_init = INIT_ERROR;
    else if (! (points_font = al_load_ttf_font ("./resources/fonts/poppins.ttf", 20, 0))) game_cond.all_init = INIT_ERROR;

    if (! game_cond.all_init) {
        emit_error (game_cond.all_init);
        return EXIT_FAILURE;
    }

    // Registros de Eventos
    al_register_event_source (queue, al_get_keyboard_event_source ());
    al_register_event_source (queue, al_get_mouse_event_source ());
    al_register_event_source (queue, al_get_display_event_source (display));
    al_register_event_source (queue, al_get_timer_event_source (timer));

    // Loop do jogo
    al_start_timer (timer);
    while (true) {
        al_wait_for_event (queue, &event);

        switch (event.type) {
            case ALLEGRO_EVENT_TIMER: 
                game_cond.redraw = true;
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                treat_mouse_move (display, &mouse, event);
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if (game_cond.in_home_page) treat_mouse_click_in_home (&mouse, &game_cond, event);
                else treat_mouse_click_in_game (&mouse, &game_cond, event);
                game_cond.redraw = true;
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                game_cond.end_game = true;
                break;
        }

        if (game_cond.end_game) break;
        
        if (game_cond.redraw && al_is_event_queue_empty (queue)) {
            al_set_target_bitmap (buffer);

            if (game_cond.in_home_page)
                draw_home_page (p_points, title_font, button_font, points_font, game_cond, sound);
            else {
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_text(title_font, al_map_rgb(255, 255, 255), (DISPLAY_WIDTH/2 - 12), DISPLAY_HEIGHT/2, 0, "Hello world!");
                al_flip_display();
            }

            flip_buffer_display (display, buffer);
            game_cond.redraw = false;
        }
    }

    // Limpesa de memória
    al_destroy_timer (timer);
    al_destroy_event_queue (queue);
    al_destroy_display (display);
    al_destroy_bitmap (buffer);
    al_destroy_bitmap (sound);
    al_destroy_bitmap (mouse.cursor);
    al_destroy_mouse_cursor (cursor);
    al_destroy_font (title_font);
    al_destroy_font (button_font);
    al_destroy_font (points_font);
    return EXIT_SUCCESS;
}