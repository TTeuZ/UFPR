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
    } else {
        p_points->record = 0;
        p_points->coins = 0;
    }
}

int read_player_game (player_game_t *g_player) {
    FILE *game_file;
    char temp_string[BUFSIZ];
    game_file = fopen ("./resources/data/game.txt", "r");

    if (game_file) {
        fgets (temp_string, BUFSIZ, game_file);
        g_player->points = atoi (temp_string);
        // ...
    } else {
        g_player->points = 0;
        // ...
        return READ_GAME_ERROR;
    }
    return EXIT_SUCCESS;
}