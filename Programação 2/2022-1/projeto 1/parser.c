#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include "constants.h"
#include "parser.h"

char *parse_command_line (char *argv[], int argc, char *paramns) {
    char *dirName = "";
    int parameter;
    while ((parameter = getopt (argc, argv, paramns)) != -1) {
        switch (parameter) {
            case 'd': {
                dirName = optarg;
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
    if (strcmp(dirName, "") == 0) {
        fprintf (stderr, RED "[ERROR] " NC "É necessário indicar um diretorio de logs!\n\n");
        fprintf (stderr, RED "[ERROR] " NC "Encerrando...\n\n");
        exit (EXIT_FAILURE);
    }
    return dirName;
}