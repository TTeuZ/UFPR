#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include "constants.h"
#include "parser.h"

char *parse_command_line (char *argv[], int argc, char *options) {
    char *dirName;
    int option;
    while ((option = getopt (argc, argv, options)) != -1) {
        switch (option) {
            case 'd': {
                dirName = optarg;
                break;
            }
            case '?': {
                if (optopt == 'd' && optarg == NULL) {
                    fprintf (stderr, RED "[ERROR] " NC "é necessário indicar um diretorio de logs!\n");
                    fprintf (stderr, RED "[ERROR] " NC "encerrando...\n\n");
                } else {
                    fprintf (stderr, RED "[ERROR] " NC "parametro invalido!\n");
                    fprintf (stderr, RED "[ERROR] " NC "encerrando...\n\n");
                }
                exit (EXIT_FAILURE);
                break;
            }
        }
    }
    return dirName;
}