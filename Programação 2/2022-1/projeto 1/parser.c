#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "parser.h"

char *parse_command_line (char *argv[], int argc) {
    char *dir_name = "";
    int count;

    if (argc < 3) {
        fprintf (stderr, RED "[ERROR] " NC "É necessário indicar um diretorio de logs!\n\n");
        return NULL;
    } else {
        for (count = 1; count < argc; count++) {
            if (! strcmp (argv[count], "-d")) {
                dir_name = argv[count + 1];
                count++;
            } else {
                fprintf (stderr, RED "[ERROR] " NC "Parametro invalido!\n\n");
                return NULL;
            }
        }
    }
    return dir_name;
}