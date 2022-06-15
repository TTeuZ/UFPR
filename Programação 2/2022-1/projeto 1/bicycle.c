#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bicycle.h"
#include "constants.h"

/*---------------------------------------------- Funções internas ---------------------------------------------*/
int compare_dates (char *first, char *second) {
    char *inside_first, *inside_second;
    int day, month, year, first_time, second_time;
    inside_first = strdup (first);
    inside_second = strdup (second);

    day = atoi (strtok (inside_first, "/"));
    month = atoi (strtok (NULL, "/"));
    year = atoi (strtok (NULL, "/")) - 1900;
    first_time = (year * 1000) + (month * 100) + (day * 10);

    day = atoi (strtok (inside_second, "/"));
    month = atoi (strtok (NULL, "/"));
    year = atoi (strtok (NULL, "/")) - 1900;
    second_time = (year * 10000) + (month * 1000) + (day * 10);

    free (inside_first);
    free (inside_second);
    return second_time - first_time;
}
/*---------------------------------------------- Funções internas ---------------------------------------------*/

bicycle_f *create_bicycle (char *name) {
    bicycle_f *bicycle;

    if (! (bicycle = malloc (sizeof (bicycle_f)))) {
        fprintf (stderr, RED "[ERROR] " NC "Falha na alocação de memoria\n\n");
        fprintf (stderr, RED "[ERROR] " NC "Encerrando...\n\n");
        exit (EXIT_FAILURE);
    } else {
        bicycle->name = strdup (name);
        bicycle->activities_qtd = 0;
        bicycle->total_km = 0;
        bicycle->longest_ride = 0;
        bicycle->shorter_ride = 0;
        bicycle->average_distance = 0;
        bicycle->logs = NULL;
        return bicycle;
    }
}

bicycle_log_f *create_log (char *bicycle_name, char *date, float distance, float average_speed, float max_speed, int average_hr, int max_hr, int average_cadence, float altimetry_gain) {
    bicycle_log_f *log;
    
    if (! (log = malloc (sizeof (bicycle_log_f)))) {
        fprintf (stderr, RED "[ERROR] " NC "Falha na alocação de memoria\n\n");
        fprintf (stderr, RED "[ERROR] " NC "Encerrando...\n\n");
        exit (EXIT_FAILURE);
    } else {
        log->bicycle_name = bicycle_name;
        log->date = date;
        log->distance = distance;
        log->average_speed = average_speed;
        log->max_speed = max_speed;
        log->average_hr = average_hr;
        log->max_hr = max_hr;
        log->average_cadence = average_cadence;
        log->altimetry_gain = altimetry_gain;
    }
    return log;
}

void add_bicycle_log (bicycle_f *bicycle, bicycle_log_f *log) {
    int count;
    if (bicycle->activities_qtd == 0) {
        if (! (bicycle->logs = malloc (sizeof (bicycle_log_f)))) {
            fprintf (stderr, RED "[ERROR] " NC "Falha na alocação de memoria\n\n");
            fprintf (stderr, RED "[ERROR] " NC "Encerrando...\n\n");
            exit (EXIT_FAILURE);
        } else {
            bicycle->logs[bicycle->activities_qtd] = log;
            bicycle->activities_qtd = 1;
        }
    } else {
        if (! (bicycle->logs = realloc (bicycle->logs, (sizeof (bicycle_log_f) * (bicycle->activities_qtd + 1))))) {
            fprintf (stderr, RED "[ERROR] " NC "Falha na alocação de memoria\n\n");
            fprintf (stderr, RED "[ERROR] " NC "Encerrando...\n\n");
            exit (EXIT_FAILURE);
        } else {
            count = bicycle->activities_qtd;
            while (count != 0 && compare_dates (log->date, bicycle->logs[count-1]->date) <= 0) {
                bicycle->logs[count] = bicycle->logs[count - 1];
                count--;
            }
            bicycle->logs[count] = log;
            bicycle->activities_qtd++;
        }
    }
    treat_bicycle_resume (bicycle, log);
}

void treat_bicycle_resume (bicycle_f *bicycle, bicycle_log_f *log) {
    bicycle->total_km += log->distance;
    bicycle->longest_ride = bicycle->longest_ride < log->distance ? log->distance : bicycle->longest_ride;

    if (bicycle->shorter_ride != 0) {
        bicycle->shorter_ride = bicycle->shorter_ride > log->distance ? log->distance : bicycle->shorter_ride;
    } else bicycle->shorter_ride = log->distance;
    
    bicycle->average_distance = bicycle->total_km / bicycle->activities_qtd;
}

void print_bicycle_resume (bicycle_f *bicycle) {
    int exit = 1, count;
    fprintf (stdout, "Bicicleta: %s\n\n", bicycle->name);

    fprintf (stdout, "Data\t\tDistância(Km)\t\tVelocidade Média(Km/h)\t\tVelocidade Máxima(Km/h)\t\tHR Médio(bpm)\t\tHR Máximo(bpm)\t\tCadência Média(rpm)\t\tSubida Acomulada(m)\n");
    for (count = 0; count < 203; count++)
        printf("-");
    printf("\n");
    for (count = 0; count < bicycle->activities_qtd; count++) {
        fprintf (stdout, "%-10s\t\t%5.2f\t\t%22.2f\t\t%23.2f\t\t%13d\t\t%14d\t\t%19d\t\t%19.2f\n", bicycle->logs[count]->date, (bicycle->logs[count]->distance / 1000), 
                                                                                                   bicycle->logs[count]->average_speed, bicycle->logs[count]->max_speed, 
                                                                                                   bicycle->logs[count]->average_hr, bicycle->logs[count]->max_hr, 
                                                                                                   bicycle->logs[count]->average_cadence, bicycle->logs[count]->altimetry_gain);
    }

    fprintf(stdout, "\nQuantidade de atividades: %d\t", bicycle->activities_qtd);
    fprintf(stdout, "Total percorrido: %5.2f Km\t", (bicycle->total_km / 1000));
    fprintf(stdout, "Pedal mais longo: %5.2f Km\t", (bicycle->longest_ride / 1000));
    fprintf(stdout, "Pedal mais curto: %5.2f Km\t", (bicycle->shorter_ride / 1000));
    fprintf(stdout, "Distância Média: %5.2f Km\n\n", (bicycle->average_distance / 1000));

    fprintf (stdout, "Aperte 0 para sair: ");
    while (exit != 0)
        scanf ("%d", &exit);
}

void print_logs_with_name (bicycle_log_f **logs, int qtd) {
    int count;
    for (count = 0; count < qtd; count++) {
        fprintf (stdout, "%-10s\t\t%-20s\t\t\t\t%5.2f\t\t%22.2f\t\t%23.2f\t\t%13d\t\t%14d\t\t%19d\t\t%19.2f\n", logs[count]->date, logs[count]->bicycle_name, (logs[count]->distance / 1000), 
                                                                                                   logs[count]->average_speed, logs[count]->max_speed, 
                                                                                                   logs[count]->average_hr, logs[count]->max_hr, 
                                                                                                   logs[count]->average_cadence, logs[count]->altimetry_gain);
    }
}

void clean_bicycle (bicycle_f *bicycle) {
    int count;
    for (count = 0; count < bicycle->activities_qtd; count++) {
        free (bicycle->logs[count]->bicycle_name);
        free (bicycle->logs[count]->date);
        free (bicycle->logs[count]);
    }
    free (bicycle->name);
    free (bicycle->logs);
    free (bicycle);
}