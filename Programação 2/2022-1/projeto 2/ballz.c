#include <stdio.h>
#include <stdlib.h>

// Allegro
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>

// Objetos
#include "./src/objects/addBall/addBall.h"
#include "./src/objects/ball/ball.h"
#include "./src/objects/coin/coin.h"
#include "./src/objects/square/square.h"

// Funções
#include "./src/functions/display/display.h"
#include "./src/functions/keyboard/keyboard.h"
#include "./src/functions/mouse/mouse.h"
#include "./src/functions/utils/utils.h"

// Carregaveis
#include "./src/loadables/audio/audio.h"
#include "./src/loadables/fonts/fonts.h"
#include "./src/loadables/images/images.h"

// Composição do jogo
#include "./src/game/aim/aim.h"
#include "./src/game/game/game.h"
#include "./src/game/pages/pages.h"
#include "./src/game/player/player.h"

int main () {
    int error;

    // inicialização dos dados do jogo
    game_cond_t game_cond;
    player_points_t p_points;
    player_game_t p_game;
    aim_t aim;
    start_game_conditions (&game_cond);
    read_player_points (&p_points);
    error = read_player_game (&p_game);

    if (error != 0) emit_error (error);
    if (error == ADD_BALL_ERROR) return EXIT_FAILURE;

    set_aim (&aim, p_game);

    // Inicializações gerais
    if (! al_init ()) game_cond.all_init = INIT_ERROR;
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

    // Keybord
    if (! al_install_keyboard ()) game_cond.all_init = INIT_ERROR;

    // imagens
    images_t images;
    if (! (al_init_image_addon ())) game_cond.all_init = INIT_ERROR;
    else if (load_images (&images)) game_cond.all_init = INIT_ERROR;

    // Audios
    audios_t audios;
    if (! al_install_audio ()) game_cond.all_init = INIT_ERROR;
    else if (! al_init_acodec_addon ()) game_cond.all_init = INIT_ERROR;
    else if (! al_reserve_samples (AUDIO_QTD)) game_cond.all_init = INIT_ERROR;
    else if (load_audios (&audios)) game_cond.all_init = INIT_ERROR;

    // fontes
    fonts_t fonts;
    if (! (al_init_font_addon ())) game_cond.all_init = INIT_ERROR;
    else if (! (al_init_ttf_addon ())) game_cond.all_init = INIT_ERROR;
    else if (load_fonts (&fonts)) game_cond.all_init = INIT_ERROR;

    // mouse
    mouse_t mouse;
    if (! al_install_mouse ()) game_cond.all_init = INIT_ERROR;
    else if (start_mouse (&mouse)) game_cond.all_init = INIT_ERROR;
    else if (set_mouse_display (display, mouse)) game_cond.all_init = INIT_ERROR;

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
                if (game_cond.in_game_page) {
                    update_balls (p_game.balls, p_game.balls_qtd);
                    check_wall_collision (&p_game, &game_cond);   
                }
                
                game_cond.redraw = true;
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                treat_mouse_move (display, &mouse, event);
                if (mouse.pressed && !game_cond.in_game) treat_aim_move (&aim, p_game, event);

                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if (game_cond.in_home_page) treat_mouse_click_in_home (&mouse, &game_cond, audios, event);
                else if (game_cond.in_help_page) treat_mouse_click_in_help (&mouse, &game_cond, event);
                else if (game_cond.in_pause_page) treat_mouse_click_in_pause (&mouse, &game_cond, audios, event);
                else treat_mouse_click_in_game (&mouse, &game_cond, &aim, event);

                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                if (game_cond.in_game_page && !game_cond.in_game) {
                    if (event.mouse.y > aim.pressed_y) {
                        game_cond.in_game = true;
                        play_balls (&p_game, aim);
                    }
                    mouse.pressed = 0;
                    set_aim (&aim, p_game);
                }

                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                treat_key_down (&game_cond, event);

                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                game_cond.close_game = true;

                break;
        }

        if (game_cond.close_game) {
            if (save_player_points (p_points) == SAVE_POINTS_ERROR)
                emit_error (SAVE_POINTS_ERROR);
            if (save_player_game (p_game) == SAVE_GAME_ERROR)
                emit_error (SAVE_GAME_ERROR);
            break;
        }
        
        if (game_cond.redraw && al_is_event_queue_empty (queue)) {
            al_set_target_bitmap (buffer);

            if (game_cond.in_home_page)
                draw_home_page (p_points, fonts, game_cond, images);
            else if (game_cond.in_help_page)
                draw_help_page (fonts, images);
            else if (game_cond.in_pause_page)
                draw_pause_page (fonts, images, game_cond);
            else {
                draw_game_page (p_game, p_points, fonts, game_cond, images);
                draw_game_section (p_game, fonts, game_cond);
                if (mouse.pressed && !game_cond.in_game) draw_game_aim (aim, p_game);
                // if (game_cond.in_game) {
                //     printf ("jogando\n");
                //     game_cond.in_game = false;
                // }
            }

            flip_buffer_display (display, buffer);
            game_cond.redraw = false;
        }
    }

    // Limpesa de memória
    al_destroy_timer (timer);
    al_destroy_event_queue (queue);
    destroy_display (display, buffer);
    destroy_images (&images);
    destroy_audios (&audios);
    destroy_fonts (&fonts);
    destroy_mouse (&mouse);
    destroy_game (&p_game);
    return EXIT_SUCCESS;
}