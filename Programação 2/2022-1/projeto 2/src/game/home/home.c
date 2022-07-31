#include "home.h"

void draw_home_page (player_points_t p_points, ALLEGRO_FONT *font) {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(font, al_map_rgb(255, 255, 255), (DISPLAY_WIDTH/2 - 12), DISPLAY_HEIGHT/2, 0, "Home");
    al_flip_display();
}