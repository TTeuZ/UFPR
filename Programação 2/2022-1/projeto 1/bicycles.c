#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bicycles.h"
#include "bicycle.h"
#include "constants.h"

/*---------------------------------------------- Funções internas ---------------------------------------------*/
bicycle_log_f **join_all_logs_and_altimetry_sort (bicycles_f *bicycles, int *logs_qtd) {
    bicycle_log_f **temp_log;
    int count, b_count, l_count, actual_log_size = 0;
    for (b_count = 0; b_count < bicycles->qtd; b_count++) 
        *logs_qtd += bicycles->bicycles[b_count]->activities_qtd;
    
    if (! (temp_log = malloc (sizeof(bicycle_log_f) * *logs_qtd))) {
        fprintf (stderr, RED "[ERROR] " NC "Falha na alocação de memoria\n\n");
        fprintf (stderr, RED "[ERROR] " NC "Encerrando...\n\n");
        exit (EXIT_FAILURE);
    } else {
        for (b_count = 0; b_count < bicycles->qtd; b_count++) {
            for (l_count = 0; l_count < bicycles->bicycles[b_count]->activities_qtd; l_count++) {
                if (actual_log_size == 0) {
                    temp_log[actual_log_size] = bicycles->bicycles[b_count]->logs[l_count];
                    actual_log_size++;
                } else {
                    count = actual_log_size;
                    while (count != 0 && bicycles->bicycles[b_count]->logs[l_count]->altimetry_gain <= temp_log[count - 1]->altimetry_gain) {
                        temp_log[count] = temp_log[count - 1];
                        count--;
                    }
                    temp_log[count] = bicycles->bicycles[b_count]->logs[l_count];
                    actual_log_size++;
                }
            }
        }
    }
    return temp_log;
}
/*---------------------------------------------- Funções internas ---------------------------------------------*/

bicycles_f *inicialize_bicycles () {
    bicycles_f *bicycles;
    if (! (bicycles = malloc (sizeof (bicycles_f)))) {
        fprintf (stderr, RED "[ERROR] " NC "Falha na alocação de memoria\n\n");
        fprintf (stderr, RED "[ERROR] " NC "Encerrando...\n\n");
        exit (EXIT_FAILURE);
    } else {
        bicycles->qtd = 0;
        bicycles->bicycles = NULL;
        return bicycles;
    }
}

int already_added (bicycles_f *bicycles, char *bicycle_name) {
    int count;
    if (bicycles->qtd == 0) return -1;
    for (count = 0; count < bicycles->qtd; count++) 
        if (strcmp (bicycle_name, bicycles->bicycles[count]->name) == 0)
            return count;
    return -1;
}

void verify_and_add_bicycle (bicycles_f *bicycles, bicycle_log_f *log) {
    bicycle_f *bicycle;
    int pos;
    pos = already_added (bicycles, log->bicycle_name);
    if (pos != -1) {
        add_bicycle_log (bicycles->bicycles[pos], log);
    } else {
        bicycle = create_bicycle (log->bicycle_name);
        add_bicycle_log (bicycle, log);
        add_bicycle_to_array (bicycles,  bicycle);
    }
}

void add_bicycle_to_array (bicycles_f *bicycles, bicycle_f *bicycle) {
    int count;
    if (bicycles->qtd == 0) {
        if (! (bicycles->bicycles = malloc (sizeof (bicycle_f)))) {
            fprintf (stderr, RED "[ERROR] " NC "Falha na alocação de memoria\n\n");
            fprintf (stderr, RED "[ERROR] " NC "Encerrando...\n\n");
            exit (EXIT_FAILURE);
        } else {
            bicycles->bicycles[bicycles->qtd] = bicycle;
            bicycles->qtd = 1;
        }
    } else {
        if (! (bicycles->bicycles = realloc (bicycles->bicycles, (sizeof (bicycle_f) * (bicycles->qtd * 1))))) {
            fprintf (stderr, RED "[ERROR] " NC "Falha na alocação de memoria\n\n");
            fprintf (stderr, RED "[ERROR] " NC "Encerrando...\n\n");
            exit (EXIT_FAILURE);
        } else {
            count = bicycles->qtd;
            while (count != 0 && strcmp (bicycle->name, bicycles->bicycles[count-1]->name) <= 0) {
                bicycles->bicycles[count] = bicycles->bicycles[count - 1];
                count--;
            }
            bicycles->bicycles[count] = bicycle;
            bicycles->qtd++;
        }
    }
}

void list_bicycles (bicycles_f *bicycles) {
    int count;
    for (count = 0; count < bicycles->qtd; count++) 
        fprintf (stdout, "Nome: %s - Quantidade de atividades: %d\n", bicycles->bicycles[count]->name, bicycles->bicycles[count]->activities_qtd);
    fprintf (stdout, "\n");
}

void printf_all_activities (bicycles_f *bicycles, int sort) {
    bicycle_log_f **temp_log;
    int count, logs_qtd = 0, exit = 1;

    fprintf (stdout, "Data\t\tBicicleta\tDistância(Km)\tVelocidade Média(Km/h)\tVelocidade Máxima(Km/h)\tHR Médio(bpm)\tHR Máximo(bpm)\tCadência Média(rpm)\tSubida Acomulada(m)\n");
    for (count = 0; count < 171; count++)
        fprintf (stdout, "-");
    fprintf(stdout, "\n");

    switch (sort) {
        case DATE_SORT: {
            for (count = 0; count < bicycles->qtd; count++)
                print_logs_with_name (bicycles->bicycles[count]->logs, bicycles->bicycles[count]->activities_qtd);
            break;
        }
        case DISTANCE_SORT: {
            for (count = 0; count < bicycles->qtd; count++) {
                temp_log = create_temp_distance_sorted_log (bicycles->bicycles[count]);
                print_logs_with_name (temp_log, bicycles->bicycles[count]->activities_qtd);
                free (temp_log);
            }
            break;
        }
        case ALTIMETRY_SORT: {
            temp_log = join_all_logs_and_altimetry_sort (bicycles, &logs_qtd);
            print_logs_with_name (temp_log, logs_qtd);
            free (temp_log);
            break;
        }
    }

    fprintf (stdout, "\nAperte 0 para sair: ");
    while (exit != 0)
        scanf ("%d", &exit);
}

void clean_bicycles (bicycles_f *bicycles) {
    int count;
    if (bicycles->qtd != 0) 
        for (count = 0; count < bicycles->qtd; count++)
            clean_bicycle (bicycles->bicycles[count]);
    free (bicycles->bicycles);
    free (bicycles);
}