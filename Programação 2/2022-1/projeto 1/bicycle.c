#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "bicycle.h"
#include "constants.h"

/*---------------------------------------------- Funções internas ---------------------------------------------*/
/*
* Função que recebe duas strings de data e as transforma em valores inteiros
* os valores inteiros são comaparados retornando:
* valores negativos se first > second
* 0 se iguais
* valores positivos se first < second
*/
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

bicycle_log_f **create_temp_distance_sorted_log (bicycle_f *bicycle) {
    bicycle_log_f **temp_log;
    int count, iterator;
    if (! (temp_log = malloc (sizeof (bicycle_log_f) * bicycle->activities_qtd))) {
        fprintf (stderr, RED "[ERROR] " NC "Falha na alocação de memoria\n\n");
        fprintf (stderr, RED "[ERROR] " NC "Encerrando...\n\n");
        exit (EXIT_FAILURE);
    } else {
        for (count = 0; count < bicycle->activities_qtd; count++) {
            if (count == 0) {
                temp_log[count] = bicycle->logs[count];
            } else {
                iterator = count;
                while (iterator != 0 && bicycle->logs[count]->distance <= temp_log[iterator - 1]->distance) {
                    temp_log[iterator] = temp_log[iterator - 1];
                    iterator--;
                }
                temp_log[iterator] = bicycle->logs[count];
            }
        }
    }
    return temp_log;
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
    int count;
    fprintf (stdout, "Bicicleta: %s\n\n", bicycle->name);

    fprintf (stdout, "Data\t\tDistância(Km)\t\tVelocidade Média(Km/h)\t\tVelocidade Máxima(Km/h)\t\tHR Médio(bpm)\t\tHR Máximo(bpm)\t\tCadência Média(rpm)\t\tSubida Acomulada(m)\n");
    for (count = 0; count < 203; count++)
        fprintf (stdout, "-");
    fprintf (stdout, "\n");

    for (count = 0; count < bicycle->activities_qtd; count++) {
        fprintf (stdout, "%-10s\t\t", bicycle->logs[count]->date);
        fprintf (stdout, "%5.2f\t\t", (bicycle->logs[count]->distance / 1000));
        fprintf (stdout, "%22.2f\t\t", bicycle->logs[count]->average_speed);
        fprintf (stdout, "%23.2f\t\t", bicycle->logs[count]->max_speed);
        fprintf (stdout, "%13d\t\t", bicycle->logs[count]->average_hr);
        fprintf (stdout, "%14d\t\t", bicycle->logs[count]->max_hr);
        fprintf (stdout, "%19d\t\t", bicycle->logs[count]->average_cadence);
        fprintf (stdout, "%19.2f\n", bicycle->logs[count]->altimetry_gain);
    
    }

    fprintf(stdout, "\nQuantidade de atividades: %d\t", bicycle->activities_qtd);
    fprintf(stdout, "Total percorrido: %5.2f Km\t", (bicycle->total_km / 1000));
    fprintf(stdout, "Pedal mais longo: %5.2f Km\t", (bicycle->longest_ride / 1000));
    fprintf(stdout, "Pedal mais curto: %5.2f Km\t", (bicycle->shorter_ride / 1000));
    fprintf(stdout, "Distância Média: %5.2f Km\n\n", (bicycle->average_distance / 1000));
}

void print_logs_with_name (bicycle_log_f **logs, int qtd) {
    int count;
    for (count = 0; count < qtd; count++) {
        fprintf (stdout, "%-10s\t", logs[count]->date);
        fprintf (stdout, "%-20s\t", logs[count]->bicycle_name);
        fprintf (stdout, "%5.2f\t", (logs[count]->distance / 1000));
        fprintf (stdout, "%22.2f\t", logs[count]->average_speed);
        fprintf (stdout, "%23.2f\t", logs[count]->max_speed);
        fprintf (stdout, "%13d\t", logs[count]->average_hr);
        fprintf (stdout, "%14d\t", logs[count]->max_hr);
        fprintf (stdout, "%19d\t", logs[count]->average_cadence);
        fprintf (stdout, "%19.2f\n", logs[count]->altimetry_gain);
    }
}

void get_histogram (bicycle_f *bicycle) {
    FILE *temp_file, *gnuplot;
    bicycle_log_f **temp_log;
    int min, max, count;
    int higher_qtd, temp_qtd;

    temp_log = create_temp_distance_sorted_log (bicycle);
    if (! (temp_file = fopen ("data.temp", "w"))) {
        fprintf (stderr, RED "[ERROR] " NC "Erro na abertura do arquivo de dados temporarios\n\n");
        fprintf (stderr, RED "[ERROR] " NC "Encerrando...\n\n");
        exit (EXIT_FAILURE);
    }

    min = (int) (bicycle->shorter_ride - ((int) bicycle->shorter_ride % 10000)) / 1000;
    max = (int) (bicycle->longest_ride - ((int) bicycle->longest_ride % 10000)) / 1000;
    max += ((int) bicycle->longest_ride % 10000) > 9000 ? 11 : 10;

    fprintf (stdout, "Bicicleta: %s\n\n", bicycle->name);
    fprintf (temp_file, "#Range Count\n");

    count = 0;
    higher_qtd = 0;
    while (min < max) {
        fprintf (stdout, "%3d - %3d | ", min, min + 9);
        fprintf (temp_file, "%d-%d ", min, min + 9);

        temp_qtd = 0;
        while (count < bicycle->activities_qtd && (temp_log[count]->distance / 1000) < (min + 9)) {
            fprintf (stdout, "*");
            temp_qtd++;
            count++;
        }

        fprintf (stdout, "\n");
        fprintf (temp_file, "%d\n", temp_qtd);

        higher_qtd = temp_qtd > higher_qtd ? temp_qtd : higher_qtd;
        min += 10;
    }
    fclose (temp_file);

    higher_qtd = round (higher_qtd / 10) + 1;
    fprintf (stdout, "            ");
    for (count = 0; count < higher_qtd; count++)
        fprintf (stdout, "123456789#");
    fprintf (stdout, "\n");
    fprintf (stdout, "Distancia |\t\tquantidade\n\n");

    // print do grafico

    if (! (gnuplot = popen ("gnuplot -persistent", "w"))) {
        fprintf (stderr, RED "[ERROR] " NC "Erro na abertura do gnuplot\n\n");
        fprintf (stderr, RED "[ERROR] " NC "Encerrando...\n\n");
        exit (EXIT_FAILURE);
    }

    // configurando o histograma
    fprintf (gnuplot, "set xlabel 'Quantidade'\n");
    fprintf (gnuplot, "set size 1.0, 1.0\n");
    fprintf (gnuplot, "set xrange [0:*]\n");
    fprintf (gnuplot, "set yrange [:] reverse\n");
    fprintf (gnuplot, "set offsets 0,0,0.5,0.5\n");
    fprintf (gnuplot, "set style fill solid\n");

    // plotando o histograma e o exibindo em tempo de execução
    fprintf (gnuplot, "plot 'data.temp' using 2:0:(0):2:($0-%f/2.):($0+%f/2.):($0+1):ytic(1) with boxxyerror linecolor 'black' title 'Atividades de %s'\n", 0.8, 0.8, bicycle->name);
    fflush (gnuplot);
    pclose (gnuplot);
    free (temp_log);;
    remove ("data.temp");
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