#include "index.h"

int start_game_objects (player_game_t p_game, game_objects_t **g_obj) {
    game_objects_t *temp;
    int count, line, col;

    if (! (temp = malloc (sizeof (game_objects_t))))
        return GAME_OBJECTS_ERROR;

    temp->balls_qtd = p_game.balls_qtd;
    temp->squares_qtd = 0;
    temp->coins_qtd = 0;

    if ((temp->balls = malloc (sizeof (ball_t) * temp->balls_qtd))) {
        for (count = 0; count < temp->balls_qtd; count++) {
            if (! (temp->balls[count] = add_ball (p_game.initial_x))) return ADD_BALL_ERROR;
        }
    } else return ADD_BALL_ERROR;

    for (line = 0; line < MAP_LINES; line++) {
        for (col = 0; col < MAP_COLS; col++) {
            temp->squares[line][col].points = 0;
            temp->coins[line][col].show = false;
            if (p_game.map[line][col] > 0) {
                temp->squares_qtd++;
                add_square (&temp->squares[line][col], p_game.map[line][col], line, col);
            } else if (p_game.map[line][col] == -1) {
                temp->coins_qtd++;
                add_coin (&temp->coins[line][col], line, col);
            }
        }
    }

    if (temp->squares_qtd == 0 && temp->coins_qtd == 0)
        generate_randow_objs (p_game, temp);

    *g_obj = temp;
    return EXIT_SUCCESS;
}

int restart_game_objects (game_objects_t *g_obj) {
    int line, col;
    int count;
    // Desaloca as estruturas alocadas anteriormente
    for (count = 0; count < g_obj->balls_qtd; count++)
        free (g_obj->balls[count]);
    free (g_obj->balls);

    // bolinhas
    g_obj->balls_qtd = 1;
    if ((g_obj->balls = malloc (sizeof (ball_t)))) {
        if (! (g_obj->balls[0] = add_ball (INITIAL_X_POSITION))) return ADD_BALL_ERROR;
    } else return ADD_BALL_ERROR;

    // Quadrados, moedas e addBalls
    for (line = 0; line < MAP_LINES; line++) {
        for (col = 0; col < MAP_COLS; col++) {
            g_obj->squares[line][col].points = 0;
            g_obj->coins[line][col].show = false;
        }
    }

    return EXIT_SUCCESS;
}

void generate_randow_objs (player_game_t p_game, game_objects_t *g_obj) {
    int squares_qtd, add_ball_qtd, coin_qtd;
    int pos, count = 0;

    squares_qtd = 2 + (rand () % MAX_SQUARES);
    add_ball_qtd = rand () % 2;
    coin_qtd = rand () % 2;

    while (count < squares_qtd) {
        pos = rand () % 6;
        if (g_obj->squares[0][pos].points == 0) {
            add_square (&g_obj->squares[0][pos], p_game.points, 0, pos);
            count++;
        }
    }
    count = 0;
    while (count < coin_qtd) {
        pos = rand () % 6;
        if (g_obj->squares[0][pos].points == 0 && g_obj->coins[0][pos].show == false) {
            add_coin (&g_obj->coins[0][pos], 0, pos);\
            count++;
        }
    }
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
            if (g_obj->coins[line][col].show) {
                g_obj->coins[line][col].y += 5;
                if (line == 0 && g_obj->coins[line][col].y == (SQUARE_SIZE *2)) has_reach = true;
            }
        }
    }

    if (has_reach) {
        for (line = (MAP_LINES - 1); line >= 0; line--) {
            for (col = 0; col < MAP_COLS; col++) {
                if (line != 0) {
                    g_obj->squares[line][col] = g_obj->squares[line - 1][col];
                    g_obj->coins[line][col] = g_obj->coins[line - 1][col];
                } else {
                    g_obj->squares[line][col].points = 0;
                    g_obj->coins[line][col].show = false;
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
            if (g_obj->coins[line][col].show)
                p_game->map[line][col] = -1;
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
