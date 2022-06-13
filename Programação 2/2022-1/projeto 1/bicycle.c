#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bicycle.h"
#include "constants.h"

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
            while (count != 0 && strcmp (log->date, bicycle->logs[count-1]->date) <= 0) {
                bicycle->logs[count] = bicycle->logs[count - 1];
                count--;
            }
            bicycle->logs[count] = log;
            bicycle->activities_qtd++;
        }
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