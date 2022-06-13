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

void add_bicycle_log (bicycles_f *bicycles, bicycle_log_f *log) {
    printf ("Nome: %s\n", log->bicycle_name);
    printf ("data: %s\n", log->date);
    printf ("Distancia: %f\n", log->distance);
    printf ("velocidade media: %f\n", log->average_speed);
    printf ("Velocidade maxima: %f\n", log->max_speed);
    printf ("hr media: %d\n", log->average_hr);
    printf ("hr maxima: %d\n", log->max_hr);
    printf ("cadencia media: %d\n", log->average_cadence);
    printf ("ganho de altimetria: %f\n", log->altimetry_gain);
    printf ("\n");
}


void clean_bicycles (bicycles_f *bicycles) {
    int count;
    if (bicycles->qtd != 0) 
        for (count = 0; count < bicycles->qtd; count++)
            clean_bicycle (bicycles->bicycles[count]);
    free (bicycles);
}