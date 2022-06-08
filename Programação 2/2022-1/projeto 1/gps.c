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

    /* executa a função de parser, verificando se o correto/necessário foi indicado */
    dir_name = parse_command_line (argv, argc, "d:");

    /* inicializa a estrutura de dados que irá armazenar as bicicletas */
    bicycles = inicialize_bicycles ();

    directory = get_logs (dir_name);

    /* Iniciando o processo de leitura dos logs */
    fprintf (stdout, YELLOW "[PROCESSANDO] " NC "Iniciando leitura dos logs...\n\n");
    fprintf (stdout, GREEN "[PROCESSADO] " NC "Leitura finalizada com sucesso\n\n");

    /* limpa os espaços alocados durante a execução do programa */
    clean_bicycles (bicycles);
    exit (EXIT_SUCCESS);
}