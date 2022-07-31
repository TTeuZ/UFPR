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