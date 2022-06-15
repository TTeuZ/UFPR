#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "bicycles.h"
#include "bicycle.h"
#include "parser.h"
#include "reader.h"

void flush_stdin () {
    int buf = 0;
    while (buf != '\n' && buf != EOF) 
        buf = getchar(); 
}

int main (int argc, char *argv[]) {
    bicycles_f *bicycles;
    directory_f *directory;
    char *dir_name, bicycle_name[256];
    int action, is_number, bicycle_pos;

    dir_name = parse_command_line (argv, argc);
    bicycles = inicialize_bicycles ();

    fprintf (stdout, YELLOW "[PROCESSANDO] " NC "Iniciando leitura dos logs...\n");
    directory = get_logs (dir_name);
    fprintf (stdout, YELLOW "[PROCESSANDO] " NC "Processando os logs carregados...\n");
    load_logs (directory, dir_name, bicycles);
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
        is_number = scanf("%d", &action);               
        flush_stdin ();

        if (is_number == 1 && (action == 2 || action == 6)) {
            fprintf (stdout, "Informe o nome da bicicleta: ");
            scanf("%[^\n]", bicycle_name);
        }

        fprintf (stdout, "-------------------------------------------------------------------\n\n");
        if (is_number != 1) {
            fprintf (stderr, RED "[ERROR] " NC "Entrada invalida!\n\n");
            action = -1;
        } else {
            switch (action) {
                case 1: {
                    list_bicycles (bicycles);
                    break;
                }
                case 2: {
                    bicycle_pos = already_added (bicycles, bicycle_name);
                    if (bicycle_pos != -1)
                        print_bicycle_resume (bicycles->bicycles[bicycle_pos]);
                    else
                        fprintf(stderr, "Bicicleta não encontrada!\n\n");
                    break;
                }
                case 3: {
                    printf_all_activities (bicycles, DATE_SORT, GROUPED);
                    break;
                }
                case 4: {
                    printf_all_activities (bicycles, DISTANCE_SORT, GROUPED);
                    break;
                }
                case 5: {
                    printf_all_activities (bicycles, ALTIMETRY_SORT, NOT_GROUPED);
                    break;
                }
                case 6: {
                    printf("hora do histograma\n");
                    break;
                }
                case 0: {
                    fprintf(stdout, "Saindo...\n\n");
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
    clean_directory (directory);
    exit (EXIT_SUCCESS);
}