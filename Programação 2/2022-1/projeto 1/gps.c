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
    int count, count2;

    dir_name = parse_command_line (argv, argc);
    bicycles = inicialize_bicycles ();

    fprintf (stdout, YELLOW "[PROCESSANDO] " NC "Iniciando leitura dos logs...\n\n");

    directory = get_logs (dir_name);

    fprintf (stdout, YELLOW "[PROCESSANDO] " NC "Processando os logs carregados...\n\n");

    load_logs (directory, dir_name, bicycles);

    fprintf (stdout, GREEN "[PROCESSADO] " NC "Leitura finalizada com sucesso\n\n");

    printf ("quantidade de bicicletas adicionadas: %d\n", bicycles->qtd);
    for (count = 0; count < bicycles->qtd; count++) {
        printf("Total de atividades: %d\n", bicycles->bicycles[count]->activities_qtd);
        for (count2 = 0; count2 < bicycles->bicycles[count]->activities_qtd; count2++) {
            printf("atividade %d data: %s (%s)\n", count2, bicycles->bicycles[count]->logs[count2]->date, bicycles->bicycles[count]->name);
            printf ("Distancia: %f\n", bicycles->bicycles[count]->logs[count2]->distance);
            printf ("velocidade media: %f\n", bicycles->bicycles[count]->logs[count2]->average_speed);
            printf ("Velocidade maxima: %f\n", bicycles->bicycles[count]->logs[count2]->max_speed);
            printf ("hr media: %d\n", bicycles->bicycles[count]->logs[count2]->average_hr);
            printf ("hr maxima: %d\n", bicycles->bicycles[count]->logs[count2]->max_hr);
            printf ("cadencia media: %d\n", bicycles->bicycles[count]->logs[count2]->average_cadence);
            printf ("ganho de altimetria: %f\n", bicycles->bicycles[count]->logs[count2]->altimetry_gain);
            printf ("\n");
        }
        printf("Total de km: %f\n", bicycles->bicycles[count]->total_km);
        printf("pedal mais longo: %f\n", bicycles->bicycles[count]->longest_ride);
        printf("pedal mais curto: %f\n", bicycles->bicycles[count]->shorter_ride);
        printf("distancia media: %f\n", bicycles->bicycles[count]->average_distance);
        printf("---------------------------------------------------------\n\n");
    }


    /* limpa os espaços alocados durante a execução do programa */
    clean_bicycles (bicycles);
    clean_directory (directory);
    exit (EXIT_SUCCESS);
}