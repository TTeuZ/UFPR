#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <math.h>
#include "constants.h"
#include "bicycles.h"
#include "bicycle.h"
#include "reader.h"

/*---------------------------------------------- Funções internas ---------------------------------------------*/
/*
*   Função que retorna se o arquivo indicado possui '.log' em seu nome,
*/
int is_log_file (const char *file_name) {
    size_t len = strlen (file_name);
    return len > 4 && strcmp (file_name + len - 4, ".log") == 0;
}

/*
*   Função que le o header do log
*/
int read_log_header (FILE *log_file, char **bicycle_name, char **untreated_date) {
    char temp_string[BUFSIZ];
    char *name, *date;

    fgets (temp_string, sizeof (temp_string), log_file);
    strtok (temp_string, " ");
    name = strtok (NULL, "\n");
    if (! (*bicycle_name = malloc (sizeof (char) * BUFSIZ))) {
        fprintf (stderr, RED "[ERROR] " NC "Falha na alocação de memoria\n\n");
        return ALOCATION_ERROR;
    }
    strcpy (*bicycle_name, name);

    fgets (temp_string, sizeof (temp_string), log_file);
    strtok (temp_string, " ");
    date = strtok (NULL, "\n");
    if (! (*untreated_date = malloc (sizeof (char) * BUFSIZ))) {
        fprintf (stderr, RED "[ERROR] " NC "Falha na alocação de memoria\n\n");
        return ALOCATION_ERROR;
    }
    strcpy (*untreated_date, date);

    return EXIT_SUCCESS;
}

/*
*   Função que le o registro atual do log e retorna as suas informações
*/
int read_log_reg (FILE *log_file, reg_f *reg) {
    char temp_string[BUFSIZ], *field, *value;
    int r_cadence = -1, r_hr = -1;
    float r_altimetry = -1, r_distance = -1, r_speed = -1;

    fgets (temp_string, sizeof (temp_string), log_file);
    if (feof (log_file))
        return END_FILE;
    
    while (strcmp (temp_string, "\n") != 0) {
        field = strtok (temp_string, ":");

        if (strcmp (field, "altitude") == 0) {
            value = strtok (NULL, " ");
            r_altimetry = atof (value);
        } else if (strcmp (field, "cadence") == 0) {
            value = strtok (NULL, " ");
            r_cadence = atoi (value);
        } else if (strcmp (field, "distance") == 0) {
            value = strtok (NULL, " ");
            r_distance = atof (value);
        } else if (strcmp (field, "heart_rate") == 0) {
            value = strtok (NULL, " ");
            r_hr = atoi (value);
        } else if (strcmp (field, "speed") == 0) {
            value = strtok (NULL, " ");
            r_speed = atof (value);
        } else if (strcmp (field, "timestamp") == 0) {
            value = strtok (NULL, "\n");
            strcpy (reg->timestamp, value);
        }
        fgets (temp_string, sizeof (temp_string), log_file);
    }

    reg->altimetry = r_altimetry;
    reg->cadence = r_cadence;
    reg->distance = r_distance;
    reg->hr = r_hr;
    reg->speed = r_speed;
    return EXIT_SUCCESS;
}

/*
*   Função que recebe uma string com o nome do mes no formato indicado (3 letras em ingles)
*   Retorna a string correspondente no formado mm 
*/
char *get_month (char *month) {
    if (strcmp (month, "Jan") == 0)
        return "01";
    else if (strcmp (month, "Feb") == 0)
        return "02";
    else if (strcmp (month, "Mar") == 0)
        return "03";
    else if (strcmp (month, "Apr") == 0)
        return "04";
    else if (strcmp (month, "May") == 0)
        return "05";
    else if (strcmp (month, "Jun") == 0)
        return "06";
    else if (strcmp (month, "Jul") == 0)
        return "07";
    else if (strcmp (month, "Aug") == 0)
        return "08";
    else if (strcmp (month, "Sep") == 0)
        return "09";
    else if (strcmp (month, "Oct") == 0)
        return "10";
    else if (strcmp (month, "Nov") == 0)
        return "11";
    else if (strcmp (month, "Dec") == 0)
        return "12";
    else return "00";
}

/*
*   Função que recebe a string de data e a formata para dd/mm/yyyy
*/
char *treat_date (char *date) {
    char *day, *month, *year;
    char *temp_date;

    month = get_month (strtok (date,", "));
    day = strtok (NULL, ",");
    year = strtok (NULL, ", ");
    if (! (temp_date =  malloc (sizeof (char) * (strlen (day) + strlen (month) + strlen (year) + 3)))) {
        fprintf (stderr, RED "[ERROR] " NC "Erro de alocação de memoria\n\n");
        return NULL;
    } 

    temp_date[0] = '\0';
    strcat (temp_date, day);
    strcat (temp_date, "/");
    strcat (temp_date, month);
    strcat (temp_date, "/");
    strcat (temp_date, year);
    return temp_date;
}

/*
*   Função que recebe uma string de timestamp e retorna o valor das horas em segundos
*/
int get_timestamp_sec (char *timestamp) {
    char *sec, *min, *hour;

    strtok (timestamp, " :");
    hour = strtok (NULL, " :");
    min = strtok (NULL, " :");
    sec = strtok (NULL, " :");

    return (atoi (hour) * 3600) + (atoi (min) * 60) + atoi (sec);
    return 0;
}

/*---------------------------------------------- Funções internas ---------------------------------------------*/
int read_directory (char *dir_name, bicycles_f *bicycles) {
    DIR *directory_stream;
    bicycle_log_f *log;
    struct dirent *file;
    char file_path[BUFSIZ];

    if (! (directory_stream = opendir (dir_name))) {
        fprintf (stderr, RED "[ERROR] " NC "Diretorio não encontrado\n\n");
        return OPEN_DIR_ERROR;
    }
    while ((file = readdir (directory_stream)) != NULL) {
        if (file->d_type == REG_FILE && is_log_file (file->d_name)) {
            file_path[0] = '\0';
            strcat (file_path, dir_name);
            strcat (file_path, "/");
            strcat (file_path, file->d_name);
            if ((log = read_log (file_path, file->d_name)) != NULL) {
                printf("%s - ", file->d_name);
                printf("cad: %2d ", log->average_cadence);
                printf("hr: %3d ", log->average_hr);
                printf("hr_m: %3d ", log->max_hr);
                printf("s: %.2f ", log->average_speed);
                printf("s_m: %.2f ", log->max_speed);
                printf("dist: %3.2f ", log->distance / 1000);
                printf("elev: %4.2f\n", log->altimetry_gain);
                if (verify_and_add_bicycle (bicycles, log) != 0) 
                    fprintf (stderr, RED "[ERROR] " NC "Falha no armazenamento do log %s\n\n", file->d_name);
            }
        }
    }
    closedir (directory_stream);
    return EXIT_SUCCESS;
}

bicycle_log_f *read_log (char *log_path, char *log_name) {
    FILE *log_file;
    reg_f *reg;
    int count;
    char temp_string[BUFSIZ];
    /* contadores dos valores do log */
    int qtd_log_speed = 0, qtd_log_hr = 0, qtd_log_cadence = 0, timestamp_qtd = 1;
    float last_altitude = 0, actual_altitude = 0, last_speed = -1, actual_speed;
    int last_hr = -1, actual_hr = 0, last_cadence = -1, actual_cadence = 0;
    /* timestamps */
    int last_timestamp_sec = 0, actual_timestamp_sec = 0, temp_timestamp_sec = 0;
    /* valores do log */
    char *bicycle_name = NULL, *untreated_date = NULL, *date;
    float distance = 0, average_speed = 0, max_speed = 0, altimetry_gain = 0;
    int average_hr = 0, max_hr = 0, average_cadence = 0;

    if (! (log_file = fopen (log_path, "r"))) {
        fprintf (stderr, RED "[ERROR]file " NC "Erro ao ler o log %s\n", log_name);
        return NULL;
    }
    if (read_log_header (log_file, &bicycle_name, &untreated_date) != 0) {
        fprintf (stderr, RED "[ERROR] " NC "Erro ao ler o log %s\n", log_name);
        return NULL;
    }
    if (! (date = treat_date (untreated_date))) {
        fprintf (stderr, RED "[ERROR] " NC "Erro ao ler o log %s\n", log_name);
        free (bicycle_name);
        free (date);
        fclose (log_file);
        return NULL;
    }
    if (! (reg = inicializa_reg ())) {
        fprintf (stderr, RED "[ERROR] " NC "Erro ao ler o log %s\n", log_name);
        free (bicycle_name);
        free (date);
        fclose (log_file);
        return NULL;
    }

    fgets (temp_string, sizeof (temp_string), log_file);
    while (! feof (log_file)) {
        if (read_log_reg (log_file, reg) == 0) {
            temp_timestamp_sec = get_timestamp_sec (reg->timestamp);
            last_timestamp_sec = last_timestamp_sec == 0 ? temp_timestamp_sec : actual_timestamp_sec;
            actual_timestamp_sec = temp_timestamp_sec;
            timestamp_qtd = actual_timestamp_sec - last_timestamp_sec;

            if (reg->distance != -1) 
                distance = reg->distance;

            if (reg->altimetry != -1) {
                last_altitude = last_altitude == 0 ? reg->altimetry : actual_altitude;
                actual_altitude = reg->altimetry;
                if (actual_altitude > last_altitude) 
                    altimetry_gain += actual_altitude - last_altitude;
            }

            if (reg->speed != -1) {
                max_speed = max_speed < reg->speed ? reg->speed : max_speed;
                last_speed = last_speed == -1 ? reg->speed : actual_speed;
                actual_speed = reg->speed;
                if (timestamp_qtd > 1 && last_speed != 0) {
                    for (count = 0; count < timestamp_qtd; count++) {
                        average_speed += last_speed;
                        qtd_log_speed++;
                    }
                } else if (actual_speed != 0) {
                    average_speed += reg->speed;
                    qtd_log_speed++;
                }
                // if (timestamp_qtd > 1) 
                //     printf ("s_a: %f, s_l: %f, timestamp: %d\n", reg->speed, last_speed, timestamp_qtd);
                // if (reg->speed == 0)
                //     printf ("s_a: %f, s_l: %f, timestamp: %d\n", reg->speed, last_speed, timestamp_qtd);
            }

            if (reg->hr != -1) {
                max_hr = max_hr < reg->hr ? reg->hr : max_hr;
                last_hr = last_hr == -1 ? reg->hr : actual_hr;
                actual_hr = reg->hr;
                if (reg->hr != 0) {
                    if (timestamp_qtd > 1 && last_hr != 0) {
                        for (count = 0; count < timestamp_qtd; count++) {
                            average_hr += last_hr;
                            qtd_log_hr++;
                        }
                    } else {
                        average_hr += reg->hr;
                        qtd_log_hr++;
                    }
                }   
            }

            if (reg->cadence != -1) {
                last_cadence = last_cadence == -1 ? reg->cadence : actual_cadence;
                actual_cadence = reg->cadence;
                if (reg->cadence != 0) {
                    if (timestamp_qtd > 1 && last_cadence != 0) {
                        for (count = 0; count < timestamp_qtd; count++) {
                            average_cadence += last_cadence;
                            qtd_log_cadence++;
                        }
                    } else {
                        average_cadence += reg->cadence;
                        qtd_log_cadence++;
                    }
                }
            }
        }
    }
    if (qtd_log_speed != 0) average_speed = average_speed / qtd_log_speed;
    average_speed = average_speed * 3.6f;
    max_speed = max_speed * 3.6f;
    if (qtd_log_hr != 0) average_hr = average_hr / qtd_log_hr;
    if (qtd_log_cadence != 0) average_cadence = average_cadence / qtd_log_cadence;

    free (reg);
    free (untreated_date);
    fclose (log_file);
    return create_log (bicycle_name, date, distance, average_speed, max_speed, average_hr, max_hr, average_cadence, altimetry_gain);
}