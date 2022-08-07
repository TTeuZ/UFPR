#include "aim.h"

void set_aim (aim_t *aim) {
    aim->x = INITIAL_X_POSITION;
    aim->y = INITIAL_Y_POSITION - 20;
    aim->pressed_x = 0;
    aim->pressed_y = 0;
    aim->move_x = 0;
    aim->distance = 0;
    aim->sin = 0;
    aim->cos = 0;
}

/*!
    Processo de calculo da mira

    A
 ab |    ca
    |    
    B-----------C
        bc

    A partir do triangulo formado podemos calcular o seno e cosseno
    seno: ab / ca
    cosseno: bc / ca

    com estes valores a partir das seguintes equações é posivel calcular a nova posição x e y da mira
    x' = INITIAL_X_POSITION +- (AIM_RADIUS * cosseno)
    y' = INITIAL_Y_POSITION + (AIM_RADIUS * seno)

    OBS: o +- da posição x e para fazer o cortorno certo de 180 graus.
*/
void treat_aim_move (aim_t *aim, ALLEGRO_EVENT event) {
    double ca, ab, bc;
    double cos, sin;

    ca = sqrt (pow ((aim->pressed_x - event.mouse.x), 2) + pow ((aim->pressed_y - event.mouse.y), 2));
    ab = sqrt (pow ((event.mouse.y - aim->pressed_y), 2));
    bc = sqrt (pow ((event.mouse.x - aim->pressed_x), 2));
    
    cos = bc / ca;
    sin = ab / ca;

    aim->sin = sin;
    aim->cos = cos;
    aim->move_x = event.mouse.x;
    aim->distance = ca;

    if (event.mouse.y <= aim->pressed_y) {
        aim->x = 0;
        aim->y = 0;
    } else {
        if (event.mouse.x < aim->pressed_x) aim->x = INITIAL_X_POSITION + (AIM_RADIUS * cos);
        else aim->x = INITIAL_X_POSITION - (AIM_RADIUS * cos);
        aim->y = INITIAL_Y_POSITION - (AIM_RADIUS * sin);
    }
}

void draw_game_aim (aim_t aim) {
    int count, x, y, distance;

    if (aim.x != 0 && aim.y != 0) {
        for (count = 0; count < AIM_SIZE; count++) {
            if (aim.distance > 125) distance = 125;
            else distance = aim.distance;


            if (aim.move_x < aim.pressed_x) 
                x = INITIAL_X_POSITION + ((((AIM_RADIUS + (distance * 0.08)) * count)) * aim.cos);
            else 
                x = INITIAL_X_POSITION - ((((AIM_RADIUS + (distance * 0.08)) * count)) * aim.cos);

            y = INITIAL_Y_POSITION - ((((AIM_RADIUS + (distance * 0.08)) * count)) * aim.sin);

            al_draw_filled_circle (x, y, 3 + (distance * 0.015), al_map_rgb (WHITE));
        }
    }
}