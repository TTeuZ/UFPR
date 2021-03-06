#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "bicycles.h"
#include "bicycle.h"
#include "parser.h"
#include "reader.h"
#include "utils.h"

int main (int argc, char *argv[]) {
    bicycles_f *bicycles;
    char *dir_name, bicycle_name[BUFSIZ];
    int action, is_number, bicycle_pos;

    if (! (dir_name = parse_command_line (argv, argc)))
        return EXIT_FAILURE;
    if (! (bicycles = inicialize_bicycles ())) 
        return EXIT_FAILURE;

    fprintf (stdout, YELLOW "[PROCESSANDO] " NC "Iniciando leitura dos logs...\n");
    if ((read_directory (dir_name, bicycles)) == -1) {
        clean_bicycles (bicycles);
        return EXIT_FAILURE;
    }
    fprintf (stdout, GREEN "[PROCESSADO] " NC "Leitura finalizada com sucesso\n\n");

    do {
        fprintf (stdout, "------------------------------ AÇÕES ------------------------------\n\n");
        fprintf (stdout, "1 - Listar bicicletas\n");
        fprintf (stdout, "2 - Apresentar resumo\n");
        fprintf (stdout, "3 - Listar todas as atividades | agrupado por bicicleta, ordenado pela data\n");
        fprintf (stdout, "4 - Listar todas as atividades | agrupado por bicicleta, ordenado pela distancia\n");
        fprintf (stdout, "5 - Listar todas as atividades | ordenado pela subida acumulada\n");
        fprintf (stdout, "6 - Histograma da bicicleta\n");
        fprintf (stdout, "0 - Sair\n\n");
        fprintf (stdout, "Selecione uma ação: ");
        is_number = scanf ("%d", &action);               
        flush_stdin ();

        if (is_number == 1 && (action == 2 || action == 6)) {
            fprintf (stdout, "Informe o nome da bicicleta: ");
            scanf ("%[^\n]", bicycle_name);
        }

        fprintf (stdout, "-------------------------------------------------------------------\n\n");
        if (is_number != 1) {
            fprintf (stderr, RED "[ERROR] " NC "Entrada invalida!\n\n");
            action = -1;
        } else {
            switch (action) {
                case 1: {
                    list_bicycles (bicycles);
                    wait_exit ();
                    break;
                }
                case 2: {
                    bicycle_pos = already_added (bicycles, bicycle_name);
                    if (bicycle_pos != -1) {
                        print_bicycle_resume (bicycles->list[bicycle_pos]);
                        wait_exit ();
                    } else
                        fprintf (stderr, "Bicicleta não encontrada!\n\n");
                    break;
                }
                case 3: {
                    printf_all_activities (bicycles, DATE_SORT);
                    wait_exit ();
                    break;
                }
                case 4: {
                    printf_all_activities (bicycles, DISTANCE_SORT);
                    wait_exit ();
                    break;
                }
                case 5: {
                    printf_all_activities (bicycles, ALTIMETRY_SORT);
                    wait_exit ();
                    break;
                }
                case 6: {
                    bicycle_pos = already_added (bicycles, bicycle_name);
                    if (bicycle_pos != -1) {
                        if ((get_histogram (bicycles->list[bicycle_pos])) == 0)
                             wait_exit ();
                    } else
                        fprintf (stderr, "Bicicleta não encontrada!\n\n");
                    break;
                }
                case 0: {
                    fprintf (stdout, "Saindo...\n\n");
                    break;
                }
                default: {
                    fprintf (stderr, "Comando invalido!\n\n");
                    break;
                }
            }
        }
    } while (action != 0);

    /* limpa os espaços alocados durante a execução do programa */
    clean_bicycles (bicycles);
    exit (EXIT_SUCCESS);
}