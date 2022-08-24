#include "speeder.h"

int start_speeder (speeder_t *speeder) {
    speeder->is_enable = 0;
    speeder->frame = 0;
    speeder->color = 0;
    speeder->bust = NONE_BUST;
    if (! (speeder->icon = al_load_bitmap ("./resources/images/lightning.png")))
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void treat_speeder (speeder_t *speeder) {
    if (speeder->frame == SPEEDER_TIME) {
        speeder->is_enable = true;
        speeder->frame = 0;
    }
    if (! (speeder->frame % SPEEDER_ANIMATION))
            speeder->color = !speeder->color;

    speeder->frame++;
}

void restart_speeder (speeder_t *speeder) {
    speeder->is_enable = false;
    speeder->frame = 0;
    speeder->color = false;
    speeder->bust = NONE_BUST;
}

void draw_speeder (fonts_t fonts, speeder_t speeder) {
    if (speeder.color)
        al_draw_textf (fonts.speeder, al_map_rgb (WHITE), END_X_AREA - 160, START_Y_AREA + 12, 0, "fast foward now  ->");
    else
        al_draw_textf (fonts.speeder, al_map_rgb (LIGHT_GRAY), END_X_AREA - 160, START_Y_AREA + 12, 0, "fast foward now  ->");
    
    al_draw_bitmap (speeder.icon, END_X_AREA - 25, START_Y_AREA + 15, 0);
}

void destroy_speeder (speeder_t *speeder) {
    al_destroy_bitmap (speeder->icon);
}