#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "bicycles.h"
#include "bicycle.h"
#include "parser.h"
#include "reader.h"

int main (int argc, char *argv[]) {
    bicycles_f *bicycles;
    directory_f *directory;
    char *dir_name;

    dir_name = parse_command_line (argv, argc);
    bicycles = inicialize_bicycles ();

    fprintf (stdout, YELLOW "[PROCESSANDO] " NC "Iniciando leitura dos logs...\n\n");

    directory = get_logs (dir_name);

    fprintf (stdout, YELLOW "[PROCESSANDO] " NC "Processando os logs carregados...\n\n");

    load_logs (directory, dir_name, bicycles);

    fprintf (stdout, GREEN "[PROCESSADO] " NC "Leitura finalizada com sucesso\n\n");

    /* limpa os espaços alocados durante a execução do programa */
    clean_bicycles (bicycles);
    free (directory);
    exit (EXIT_SUCCESS);
}