#include "index.h"

int start_game_objects (player_game_t p_game, game_objects_t **g_obj) {
    game_objects_t *temp;
    int count, line, col;

    if (! (temp = malloc (sizeof (game_objects_t))))
        return GAME_OBJECTS_ERROR;

    temp->balls_qtd = p_game.balls_qtd;
    temp->squares_qtd = 0;

    if ((temp->balls = malloc (sizeof (ball_t) * temp->balls_qtd))) {
        for (count = 0; count < temp->balls_qtd; count++) {
            if (! (temp->balls[count] = add_ball (p_game.initial_x))) return ADD_BALL_ERROR;
        }
    } else return ADD_BALL_ERROR;

    for (line = 0; line < MAP_LINES; line++) {
        for (col = 0; col < MAP_COLS; col++) {
            temp->squares[line][col].points = 0;
            if (p_game.map[line][col] > 0) {
                temp->squares_qtd++;
                add_square (&temp->squares[line][col], p_game.map[line][col], line, col);
            }
        }
    }

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

void drawing_down_objs (game_objects_t *g_obj) {
    int line, col;
    int has_reach = false;

    for (line = 0; line < MAP_LINES; line++) {
        for (col = 0; col < MAP_COLS; col++) {
            if (g_obj->squares[line][col].points != 0) {
                g_obj->squares[line][col].y += 5;
                if (line == 0 && g_obj->squares[line][col].y == (SQUARE_SIZE * 2)) has_reach = true;
            }
        }
    }

    if (has_reach) {
        for (line = (MAP_LINES - 1); line >= 0; line--) {
            for (col = 0; col < MAP_COLS; col++) {
                if (line != 0) {
                    g_obj->squares[line][col] = g_obj->squares[line - 1][col];
                } else {
                    g_obj->squares[line][col].points = 0;
                }
            }
        }
    }
}

void persist_objects_changes (player_game_t *p_game, game_objects_t *g_obj) {
    int line, col;

    p_game->balls_qtd = g_obj->balls_qtd;

    for (line = 0; line < MAP_LINES; line++) {
        for (col = 0; col < MAP_COLS; col++) {
            p_game->map[line][col] = 0;
            if (g_obj->squares[line][col].points != 0)
                p_game->map[line][col] = g_obj->squares[line][col].points;
        }
    }
}

void destroy_game_objects (game_objects_t *g_obj) {
    int count;
    
    for (count = 0; count < g_obj->balls_qtd; count++)
        free (g_obj->balls[count]);
    free (g_obj->balls);

    free (g_obj);
}
