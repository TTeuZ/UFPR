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

// Funções
#include "./src/functions/cheatCodes/cheatCodes.h"
#include "./src/functions/conditions/conditions.h"
#include "./src/functions/display/display.h"
#include "./src/functions/error/error.h"
#include "./src/functions/keyboard/keyboard.h"
#include "./src/functions/mouse/mouse.h"

// Composição do jogo
#include "./src/game/aim/aim.h"
#include "./src/game/collision/collision.h"
#include "./src/game/logic/logic.h"
#include "./src/game/pages/pages.h"
#include "./src/game/player/player.h"
#include "./src/game/shop/shop.h"
#include "./src/game/speeder/speeder.h"
#include "./src/game/withdraw/withdraw.h"

// Carregaveis
#include "./src/loadables/audio/audio.h"
#include "./src/loadables/fonts/fonts.h"
#include "./src/loadables/images/images.h"

// Objetos
#include "./src/objects/index/index.h"
#include "./src/objects/addBall/addBall.h"
#include "./src/objects/ball/ball.h"
#include "./src/objects/coin/coin.h"
#include "./src/objects/square/square.h"

int main () {
    int error;

    srand (time (NULL));

    // Condições do jogo
    general_t general;
    pages_t pages;
    stages_t stages;
    start_general_conditions (&general);
    start_pages_conditions (&pages);
    start_stages_conditions (&stages);

    // inicialização dos dados do jogo
    player_points_t p_points;
    player_game_t p_game;
    if (read_player_points (&p_points)) emit_error (READ_POINTS_ERROR);
    if (read_player_game (&p_game)) emit_error (READ_GAME_ERROR);

    // Objetos do jogo
    game_objects_t *g_obj = NULL;
    error = start_game_objects (p_game, &g_obj);

    if (error) {
        emit_error (error);
        return EXIT_FAILURE;
    }

    // Mira
    aim_t aim;
    set_aim (&aim, p_game.initial_x);

    // Estrutura de saque
    withdraw_t withdraw;
    start_withdraw_conditions (&withdraw);

    // cheatCodes
    cheats_t cheats;
    start_cheats (&cheats);

    // Shop
    shop_item_t items[ITEMS_SIZE];
    if (read_shop_items (items)) {
        emit_error (READ_SHOP_ERROR);
        return EXIT_FAILURE;
    }

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
                if (general.restart) {
                    start_cheats (&cheats);
                    start_stages_conditions (&stages);
                    restart_game (&p_game);
                    restart_speeder (&speeder);
                    start_withdraw_conditions (&withdraw);
                    set_aim (&aim, p_game.initial_x);
                    error = restart_game_objects (g_obj);
                    generate_randow_objs (p_game, g_obj);

                    if (error) {
                        emit_error (error);
                        general.close_game = true;
                    }
                    general.restart = false;
                }

                if (pages.in_game_page) {
                    if (stages.start_phase) {
                        stages.drawing_down = verify_first_line (g_obj);

                        if (stages.drawing_down) drawing_down_objs (g_obj);
                        else stages.start_phase = false;
                    } 

                    if (stages.in_game) {
                        if (! withdraw.all_played) treat_withdraw (g_obj, &withdraw);

                        update_balls (g_obj->balls, g_obj->balls_qtd, speeder);
                        update_pre_add_balls (g_obj->pre_add_balls, g_obj->pre_add_qtd);
                        check_square_collision (g_obj, speeder, general, audios);
                        check_add_ball_collision (g_obj, general, audios);
                        check_coin_collision (&p_points, g_obj, general, audios);
                        check_wall_collision (&p_game, g_obj, &withdraw);
                        treat_speeder (&speeder);

                        if (withdraw.all_played && withdraw.in_game_balls == 0 && g_obj->pre_add_qtd != 0) {
                            error = add_pre_added_balls (g_obj, &withdraw);
                            
                            if (error) {
                                emit_error (error);
                                general.close_game = true;
                            }
                        } 
                        if (withdraw.all_played) treat_end_phase (&p_game, &stages, &withdraw);
                    } 

                    if (stages.end_phase) {
                        if (p_game.points > p_points.record) p_points.record = p_game.points;
                        restart_speeder (&speeder);

                        if ((stages.end_game = verify_last_line (g_obj))) {
                            pages.in_end_game_page = true;
                            pages.in_game_page = false;
                        } else {
                            generate_randow_objs (p_game, g_obj);
                            stages.end_phase = false;
                            stages.start_phase = true;
                            if (general.sound_on) play_audio (audios.level_pass, LEVEL_GAIN, LEVEL_SPEED);
                        }
                    }
                }
                g_obj->a_frame++;
                general.redraw = true;

                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                treat_mouse_move (display, &mouse, event);
                if (mouse.pressed && !stages.in_game) treat_aim_move (&aim, p_game.initial_x, event);

                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if (pages.in_home_page) treat_mouse_click_in_home (&mouse, &pages, &general, audios, event);
                else if (pages.in_shop_page) treat_mouse_click_in_shop (&mouse,&p_points, items, &pages, &general, audios, event);
                else if (pages.in_help_page) treat_mouse_click_in_help (&mouse, &pages, event);
                else if (pages.in_pause_page) treat_mouse_click_in_pause (&pages, &general, audios, event);
                else if (pages.in_end_game_page) treat_mouse_click_in_end_game (&pages, &general, event);
                else {
                    treat_mouse_click_in_game (&mouse, &pages, &aim, &speeder, event);
                    treat_rain_cheat (&cheats, g_obj, event);
                }

                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                if (pages.in_game_page && !stages.in_game) {
                    if (event.mouse.y > aim.pressed_y + AIM_LIMIT) {
                        stages.in_game = true;
                        play_balls (g_obj->balls, g_obj->balls_qtd, aim);
                    }
                    set_aim (&aim, p_game.initial_x);
                }
                mouse.pressed = false;

                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                treat_key_down (&pages, &general, event);
                if (pages.in_game_page && ! stages.in_game)
                    if (treat_yudi_cheat (&cheats, g_obj, event)) {
                        emit_error (ADD_BALL_ERROR);
                        general.close_game = true;
                    }

                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                general.close_game = true;

                break;
        }

        if (general.close_game) {
            if (pages.in_end_game_page) {
                restart_game (&p_game);
                restart_game_objects (g_obj);
            }
            persist_objects_changes (&p_game, g_obj);

            if (save_player_points (p_points) == SAVE_POINTS_ERROR)
                emit_error (SAVE_POINTS_ERROR);
            if (save_player_game (p_game) == SAVE_GAME_ERROR)
                emit_error (SAVE_GAME_ERROR);
            if (save_shop_items (items) == SAVE_SHOP_ERROR)
                emit_error (SAVE_SHOP_ERROR);
            break;
        }
        
        if (general.redraw && al_is_event_queue_empty (queue)) {
            al_set_target_bitmap (buffer);

            if (pages.in_home_page)
                draw_home_page (p_points, fonts, general, images);
            else if (pages.in_shop_page)
                draw_shop_page (p_points, fonts, images, items);
            else if (pages.in_help_page)
                draw_help_page (fonts, images);
            else if (pages.in_pause_page)
                draw_pause_page (fonts, images, general);
            else if (pages.in_end_game_page)
                draw_end_game_page (p_game, p_points, fonts);
            else {
                draw_game_page (p_game, p_points, fonts, images);
                draw_squares (g_obj->squares, fonts);
                draw_add_balls (g_obj->add_balls, g_obj->a_frame);
                draw_coins (g_obj->coins);
                draw_balls (g_obj->balls, g_obj->balls_qtd, p_game.initial_x, items[p_points.ball_in_use].r, items[p_points.ball_in_use].g , items[p_points.ball_in_use].b, fonts, stages);
                if (stages.in_game) draw_pre_add_balls (g_obj->pre_add_balls, g_obj->pre_add_qtd);
                if (speeder.is_enable && stages.in_game) draw_speeder (fonts, speeder);
                if (mouse.pressed && !stages.in_game) draw_game_aim (aim, p_game.initial_x);
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
    destroy_game_objects (g_obj);
    return EXIT_SUCCESS;
}