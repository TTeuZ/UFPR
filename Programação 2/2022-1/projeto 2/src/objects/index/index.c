#include "index.h"

int start_game_objects (player_game_t p_game, game_objects_t **g_obj) {
    game_objects_t *temp;
    int count;

    if (! (temp = malloc (sizeof (game_objects_t))))
        return GAME_OBJECTS_ERROR;
    
    // bolinhas
    temp->balls_qtd = p_game.balls_qtd;
    if ((temp->balls = malloc (sizeof (ball_t) * temp->balls_qtd))) {
        for (count = 0; count < temp->balls_qtd; count++) {
            if (! (temp->balls[count] = add_ball (p_game.initial_x))) return ADD_BALL_ERROR;
        }
    } else return ADD_BALL_ERROR;

    *g_obj = temp;
    return EXIT_SUCCESS;
}

int restart_game_objects (game_objects_t *g_obj) {
    // Desaloca as estruturas alocadas anteriormente
    free (g_obj->balls);

    // bolinhas
    g_obj->balls_qtd = 1;
    if ((g_obj->balls = malloc (sizeof (ball_t)))) {
        if (! (g_obj->balls[0] = add_ball (INITIAL_X_POSITION))) return ADD_BALL_ERROR;
    } else return ADD_BALL_ERROR;

    return EXIT_SUCCESS;
}

void persist_objects_changes (player_game_t *p_game, game_objects_t *g_obj) {
    p_game->balls_qtd = g_obj->balls_qtd;
}

void destroy_game_objects (game_objects_t *g_obj) {
    int count;
    
    for (count = 0; count < g_obj->balls_qtd; count++)
        free (g_obj->balls[count]);
    free (g_obj->balls);

    free (g_obj);
}
