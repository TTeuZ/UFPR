#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>


int main () {
    // Estruturas da Allegro
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_DISPLAY *display;
    ALLEGRO_FONT *font;
    ALLEGRO_EVENT event;

    // Variaveis
    int end_game, redraw;

    // Inicializações
    if (! al_init ()) {
        fprintf (stderr, "Erro ao inicializar a Allegro!\n");
        return EXIT_FAILURE;
    }
    if (! al_install_keyboard ()) {
        fprintf (stderr, "Erro ao inicializar o teclado\n");
        return EXIT_FAILURE;
    }
    if (! (timer = al_create_timer (1.0 / 60.0))) {
        fprintf (stderr, "Erro ao inicializar o timer\n");
        return EXIT_FAILURE;
    }
    if (! (queue = al_create_event_queue ())) {
        fprintf (stderr, "Erro ao inicializar a queue\n");
        return EXIT_FAILURE;
    }
    if (! (display = al_create_display (480, 720))) {
        fprintf (stderr, "Erro ao inicializar o display!\n");
        return EXIT_FAILURE;
    }
    if (! (font = al_create_builtin_font ())) {
        fprintf (stderr, "Erro ao inicializar a fonte!\n");
        return EXIT_FAILURE;
    }

    // Registros de Eventos
    al_register_event_source (queue, al_get_keyboard_event_source ());
    al_register_event_source (queue, al_get_display_event_source (display));
    al_register_event_source (queue, al_get_timer_event_source (timer));

    // Loop do jogo
    al_start_timer (timer);
    end_game = false;
    redraw = true;
    while (true) {
        al_wait_for_event (queue, &event);

        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                end_game = true;
                break;
            case ALLEGRO_EVENT_TIMER: 
                redraw = true;
                break;
        }

        if (end_game)
            break;
        
        if (redraw && al_is_event_queue_empty (queue)) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Hello world!");
            al_flip_display();

            redraw = false;
        }
    }

    // Limpesa de memória
    al_destroy_timer (timer);
    al_destroy_event_queue (queue);
    al_destroy_display (display);
    al_destroy_font (font);
    return EXIT_SUCCESS;
}