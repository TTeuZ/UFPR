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
#include "./src/functions/conditions/conditions.h"
#include "./src/functions/display/display.h"
#include "./src/functions/error/error.h"
#include "./src/functions/keyboard/keyboard.h"
#include "./src/functions/mouse/mouse.h"

// Carregaveis
#include "./src/loadables/audio/audio.h"
#include "./src/loadables/fonts/fonts.h"
#include "./src/loadables/images/images.h"

// Composição do jogo
#include "./src/game/aim/aim.h"
#include "./src/game/game/game.h"
#include "./src/game/pages/pages.h"
#include "./src/game/player/player.h"
#include "./src/game/speeder/speeder.h"

int main () {
    int error;

    // Condições do jogo
    general_t general;
    pages_t pages;
    stages_t stages;
    withdraw_t withdraw;
    start_general_conditions (&general);
    start_pages_conditions (&pages);
    start_stages_conditions (&stages);
    start_withdraw_conditions (&withdraw);

    // inicialização dos dados do jogo
    player_points_t p_points;
    player_game_t p_game;
    aim_t aim;
    read_player_points (&p_points);
    error = read_player_game (&p_game);

    if (error != 0) emit_error (error);
    if (error == ADD_BALL_ERROR) return EXIT_FAILURE;

    set_aim (&aim, p_game);

    // Inicializações gerais
    if (! al_init ()) general.all_init = INIT_ERROR;
    else if (! (al_init_primitives_addon ())) general.all_init = INIT_ERROR;

    // FPS e eventos
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_EVENT event;
    if (! (timer = al_create_timer (FPS))) general.all_init = INIT_ERROR;
    else if (! (queue = al_create_event_queue ())) general.all_init = INIT_ERROR;

    // Display
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_BITMAP *buffer = NULL;
    if (create_display (&display, &buffer)) general.all_init = INIT_ERROR;

    // Keybord
    if (! al_install_keyboard ()) general.all_init = INIT_ERROR;

    // imagens
    images_t images;
    if (! (al_init_image_addon ())) general.all_init = INIT_ERROR;
    else if (load_images (&images)) general.all_init = INIT_ERROR;

    // Speeder
    speeder_t speeder;
    if (start_speeder (&speeder)) general.all_init = INIT_ERROR;

    // Audios
    audios_t audios;
    if (! al_install_audio ()) general.all_init = INIT_ERROR;
    else if (! al_init_acodec_addon ()) general.all_init = INIT_ERROR;
    else if (! al_reserve_samples (AUDIO_QTD)) general.all_init = INIT_ERROR;
    else if (load_audios (&audios)) general.all_init = INIT_ERROR;

    // fontes
    fonts_t fonts;
    if (! (al_init_font_addon ())) general.all_init = INIT_ERROR;
    else if (! (al_init_ttf_addon ())) general.all_init = INIT_ERROR;
    else if (load_fonts (&fonts)) general.all_init = INIT_ERROR;

    // mouse
    mouse_t mouse;
    if (! al_install_mouse ()) general.all_init = INIT_ERROR;
    else if (start_mouse (&mouse)) general.all_init = INIT_ERROR;
    else if (set_mouse_display (display, mouse)) general.all_init = INIT_ERROR;

    if (! general.all_init) {
        emit_error (general.all_init);
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
                if (pages.in_game_page && stages.in_game) {
                    if (! withdraw.all_played) treat_withdraw (&p_game, &withdraw);

                    update_balls (p_game.balls, p_game.balls_qtd);
                    check_wall_collision (&p_game, &withdraw);
                    treat_speeder (&speeder);

                    if (withdraw.all_played) treat_end_phase (&p_game, &stages, &withdraw);
                    if (stages.end_phase) reset_speeder (&speeder);
                }
                
                general.redraw = true;
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                treat_mouse_move (display, &mouse, event);
                if (mouse.pressed && !stages.in_game) treat_aim_move (&aim, p_game, event);

                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if (pages.in_home_page) treat_mouse_click_in_home (&mouse, &pages, &general, audios, event);
                else if (pages.in_help_page) treat_mouse_click_in_help (&mouse, &pages, event);
                else if (pages.in_pause_page) treat_mouse_click_in_pause (&mouse, &pages, &general, audios, event);
                else treat_mouse_click_in_game (&mouse, &pages, &aim, &speeder, event);

                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                if (pages.in_game_page && !stages.in_game) {
                    if (event.mouse.y > aim.pressed_y) {
                        stages.in_game = true;
                        stages.end_phase = false;
                        play_balls (&p_game, aim);
                    }
                    mouse.pressed = false;
                    set_aim (&aim, p_game);
                }

                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                treat_key_down (&pages, &general, event);

                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                general.close_game = true;

                break;
        }

        if (general.close_game) {
            if (save_player_points (p_points) == SAVE_POINTS_ERROR)
                emit_error (SAVE_POINTS_ERROR);
            if (save_player_game (p_game) == SAVE_GAME_ERROR)
                emit_error (SAVE_GAME_ERROR);
            break;
        }
        
        if (general.redraw && al_is_event_queue_empty (queue)) {
            al_set_target_bitmap (buffer);

            if (pages.in_home_page)
                draw_home_page (p_points, fonts, general, images);
            else if (pages.in_help_page)
                draw_help_page (fonts, images);
            else if (pages.in_pause_page)
                draw_pause_page (fonts, images, general);
            else {
                draw_game_page (p_game, p_points, fonts, images);
                draw_game_section (p_game, fonts, stages);
                if (speeder.is_enable && stages.in_game) draw_speeder (fonts, speeder);
                if (mouse.pressed && !stages.in_game) draw_game_aim (aim, p_game);
            }

            flip_buffer_display (display, buffer);
            general.redraw = false;
        }
    }

    // Limpesa de memória
    al_destroy_timer (timer);
    al_destroy_event_queue (queue);
    destroy_display (display, buffer);
    destroy_images (&images);
    destroy_speeder (&speeder);
    destroy_audios (&audios);
    destroy_fonts (&fonts);
    destroy_mouse (&mouse);
    destroy_game (&p_game);
    return EXIT_SUCCESS;
}