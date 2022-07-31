#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

// Objetos
#include "./src/objects/addBall/addBall.h"
#include "./src/objects/ball/ball.h"
#include "./src/objects/coin/coin.h"
#include "./src/objects/square/square.h"

// Funções
#include "./src/functions/display/display.h"
#include "./src/functions/utils/utils.h"

// Composição do jogo
#include "./src/game/game/game.h"
#include "./src/game/home/home.h"
#include "./src/game/player/player.h"

int main () {
    // Estruturas da Allegro
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_FONT *title_font;
    ALLEGRO_FONT *button_font;
    ALLEGRO_FONT *points_font;
    ALLEGRO_EVENT event;

    // Estruturas do jogo
    game_cond_t game_cond;
    player_points_t p_points;

    // inicialização dos dados do jogo
    start_game_conditions (&game_cond);
    read_player_points (&p_points);

    // Inicializações
    if (! al_init ()) game_cond.all_init = INIT_ERROR;
    else if (create_display (&display)) game_cond.all_init = INIT_ERROR;
    else if (! al_install_keyboard ()) game_cond.all_init = INIT_ERROR;
    else if (! (al_init_font_addon ())) game_cond.all_init = INIT_ERROR;
    else if (! (al_init_ttf_addon ())) game_cond.all_init = INIT_ERROR;
    else if (! (al_init_primitives_addon ())) game_cond.all_init = INIT_ERROR;
    else if (! (timer = al_create_timer (1.0 / 60.0))) game_cond.all_init = INIT_ERROR;
    else if (! (queue = al_create_event_queue ())) game_cond.all_init = INIT_ERROR;

    // fontes
    if (! (title_font = al_load_ttf_font ("./resources/fonts/poppins.ttf", 90, 0))) game_cond.all_init = INIT_ERROR;
    if (! (button_font = al_load_ttf_font ("./resources/fonts/poppins.ttf", 25, 0))) game_cond.all_init = INIT_ERROR;
    if (! (points_font = al_load_ttf_font ("./resources/fonts/poppins.ttf", 20, 0))) game_cond.all_init = INIT_ERROR;

    if (! game_cond.all_init) {
        emit_error (game_cond.all_init);
        return EXIT_FAILURE;
    }

    // Registros de Eventos
    al_register_event_source (queue, al_get_keyboard_event_source ());
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
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                game_cond.end_game = true;
                break;
        }

        if (game_cond.end_game)
            break;
        
        if (game_cond.redraw && al_is_event_queue_empty (queue)) {
            if (game_cond.in_home_page)
                draw_home_page (p_points, title_font, button_font, points_font);
            else {
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_text(title_font, al_map_rgb(255, 255, 255), (DISPLAY_WIDTH/2 - 12), DISPLAY_HEIGHT/2, 0, "Hello world!");
                al_flip_display();
            }
            game_cond.redraw = false;
        }
    }

    // Limpesa de memória
    al_destroy_timer (timer);
    al_destroy_event_queue (queue);
    al_destroy_display (display);
    al_destroy_font (title_font);
    al_destroy_font (button_font);
    al_destroy_font (points_font);
    return EXIT_SUCCESS;
}