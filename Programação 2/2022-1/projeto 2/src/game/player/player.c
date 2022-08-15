#include "player.h"

void read_player_points (player_points_t *p_points) {
    FILE *points_file;
    char temp_string[BUFSIZ];
    points_file = fopen ("./resources/data/playerPoints.txt", "r");

    if (points_file) {
        fgets (temp_string, BUFSIZ, points_file);
        p_points->record = atoi (temp_string);

        fgets (temp_string, BUFSIZ, points_file);
        p_points->coins = atoi (temp_string);
        fclose (points_file);
    } else {
        p_points->record = 0;
        p_points->coins = 0;
    }
}

int read_player_game (player_game_t *p_game) {
    FILE *game_file;
    char temp_string[BUFSIZ];
    int count;
    game_file = fopen ("./resources/data/game.txt", "r");

    if (game_file) {
        fgets (temp_string, BUFSIZ, game_file);
        p_game->points = atoi (temp_string);
        
        fgets (temp_string, BUFSIZ, game_file);
        p_game->balls_qtd = atoi (temp_string);

        fgets (temp_string, BUFSIZ, game_file);
        p_game->initial_x = atoi (temp_string);
        p_game->temp_init_x = p_game->initial_x;
        fclose (game_file);
    } else {
        p_game->points = 1;
        p_game->balls_qtd = 1;
        p_game->initial_x = INITIAL_X_POSITION;
        p_game->temp_init_x = INITIAL_X_POSITION;
    }

    if ((p_game->balls = malloc (sizeof (ball_t)* p_game->balls_qtd))) {
        for (count = 0; count < p_game->balls_qtd; count++) {
            if (! (p_game->balls[count] = add_ball (p_game->initial_x))) return ADD_BALL_ERROR;
        }
    } else return ADD_BALL_ERROR;

    if (! game_file) return READ_GAME_ERROR;
    return EXIT_SUCCESS;
}

int save_player_points (player_points_t p_points) {
    FILE *points_file;
    points_file = fopen ("./resources/data/playerPoints.txt", "w");

    if (points_file) {
        fprintf (points_file, "%d\n", p_points.record);
        fprintf (points_file, "%d", p_points.coins);
        fclose (points_file);
    } else return SAVE_POINTS_ERROR;
    return EXIT_SUCCESS;
}

int save_player_game (player_game_t p_game) {
    FILE *game_file;
    game_file = fopen ("./resources/data/game.txt", "w");

    if (game_file) {
        fprintf (game_file, "%d\n", p_game.points);
        fprintf (game_file, "%d\n", p_game.balls_qtd);
        fprintf (game_file, "%f", p_game.initial_x);
        fclose (game_file);
    } else return SAVE_GAME_ERROR;
    return EXIT_SUCCESS;
}