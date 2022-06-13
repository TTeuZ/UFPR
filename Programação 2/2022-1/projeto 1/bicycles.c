#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bicycles.h"
#include "bicycle.h"
#include "constants.h"

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

void clean_bicycles (bicycles_f *bicycles) {
    int count;
    if (bicycles->qtd != 0) 
        for (count = 0; count < bicycles->qtd; count++)
            clean_bicycle (bicycles->bicycles[count]);
    free (bicycles->bicycles);
    free (bicycles);
}