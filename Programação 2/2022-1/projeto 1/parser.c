#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include "constants.h"
#include "parser.h"

char *parse_command_line (char *argv[], int argc, char *paramns) {
    char *dir_name = "";
    int parameter;
    if (strcmp(dir_name, "") == 0) {
        fprintf (stderr, RED "[ERROR] " NC "É necessário indicar um diretorio de logs!\n\n");
        fprintf (stderr, RED "[ERROR] " NC "Encerrando...\n\n");
        exit (EXIT_FAILURE);
    }
    while ((parameter = getopt (argc, argv, paramns)) != -1) {
        switch (parameter) {
            case 'd': {
                dir_name = optarg;
                break;
            }
            case '?': {
                if (optopt == 'd' && optarg == NULL) {
                    fprintf (stderr, RED "[ERROR] " NC "É necessário indicar um diretorio de logs!\n\n");
                    fprintf (stderr, RED "[ERROR] " NC "Encerrando...\n\n");
                } else {
                    fprintf (stderr, RED "[ERROR] " NC "Parametro invalido!\n\n");
                    fprintf (stderr, RED "[ERROR] " NC "Encerrando...\n\n");
                }
                exit (EXIT_FAILURE);
                break;
            }
        }
    }
    return dir_name;
}