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
* Função que retorna se o arquivo indicado possui '.log' em seu nome,
*/
int is_log_file (const char *file_name) {
    size_t len = strlen (file_name);
    return len > 4 && strcmp (file_name + len - 4, ".log") == 0;
}

/*
* Função de filtro dos arquivos no diretorio, para deixar passar na função apenas os arquivos .log
*/
int filterFiles (const struct dirent *current_dir) {
    if (current_dir->d_type == DT_REG && is_log_file (current_dir->d_name)) 
        return 1;
    else return 0;
}

/*
* Função que recebe uma string com o nome do mes no formato indicado (3 letras em ingles)
* Retorna a string correspondente no formado mm 
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
* Função que recebe a string de data e a formata para dd/mm/yyyy
*/
char *treat_date (char *date) {
    char *day, *month, *year;
    char *temp_date;

    month = get_month (strtok (date,", "));
    day = strtok (NULL, ",");
    year = strtok (NULL, ", ");
    if (! (temp_date =  malloc (sizeof (char) * (strlen (day) + strlen (month) + strlen (year) + 3)))) {
        fprintf (stderr, RED "[ERROR] " NC "Erro de alocação de memoria\n\n");
        fprintf (stderr, RED "[ERROR] " NC "Encerrando...\n\n");
        exit (EXIT_FAILURE);
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
* Função que recebe uma string de timestamp e retorna o valor das horas em segundos
*/
int get_timestamp_sec (char *timestamp) {
    char *sec, *min, *hour;

    strtok (timestamp, " :");
    hour = strtok (NULL, " :");
    min = strtok (NULL, " :");
    sec = strtok (NULL, " :");

    return (atoi (hour) * 3600) + (atoi (min) * 60) + atoi (sec);
}

/*
* Função que inicializa a estrutura de armazenamento das informações do bloco de informações do log
*/
reg_f *inicializa_reg () {
    reg_f *reg;
    if (! (reg = malloc (sizeof (reg_f)))) {
        fprintf (stderr, RED "[ERROR] " NC "Falha na alocação de memoria\n\n");
        fprintf (stderr, RED "[ERROR] " NC "Encerrando...\n\n");
        exit (EXIT_FAILURE);
    } else {
        reg->distance = 0.0;
        reg->speed = 0.0;
        reg->hr = 0;
        reg->cadence = 0;
        reg->altimetry = 0.0;
        return reg;
    }
}

/*
* Função que le o header do log
*/
void read_log_header (FILE *log_file, char **bicycle_name, char **untreated_date) {
    char temp_string[BUFSIZ];
    fgets (temp_string, sizeof (temp_string), log_file);
    strtok (temp_string, " ");
    *bicycle_name = strdup (strtok (NULL, "\n"));

    fgets (temp_string, sizeof (temp_string), log_file);
    strtok (temp_string, " ");
    *untreated_date = strdup (strtok (NULL, "\n"));
}

/*
* Função que le o registro atual do log e retorna as suas informações
*/
int read_log_reg (FILE *log_file, reg_f *reg) {
    char temp_string[BUFSIZ], *field, *value;
    int r_cadence = -1, r_hr = -1;
    float r_altimetry = -1, r_distance = -1, r_speed = -1;
    fgets (temp_string, sizeof (temp_string), log_file);
    if (feof (log_file))
        return 0;

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
    return 1;
}
/*---------------------------------------------- Funções internas ---------------------------------------------*/

directory_f *inicialize_directory () {
    directory_f *directory;
    if (! (directory = malloc (sizeof (directory_f)))) {
        fprintf (stderr, RED "[ERROR] " NC "Falha na alocação de memoria\n\n");
        fprintf (stderr, RED "[ERROR] " NC "Encerrando...\n\n");
        exit (EXIT_FAILURE);
    } else {
        directory->files_qtd = 0;
        directory->files = NULL;
        return directory;
    }
}

directory_f *get_logs (char *dir_name) {
    directory_f *directory;

    directory = inicialize_directory ();
    directory->files_qtd = scandir (dir_name, &directory->files, filterFiles, alphasort);

    if (directory->files_qtd == -1) {
        fprintf (stderr, RED "[ERROR] " NC "Diretorio não encontrado\n\n");
        fprintf (stderr, RED "[ERROR] " NC "Encerrando...\n\n");
        exit (EXIT_FAILURE);
    } else return directory;
}

void load_logs (directory_f *directory, char *dir_name, bicycles_f *bicycles) {
    bicycle_log_f *log;
    char file_path[BUFSIZ];
    int count;

    for (count = 0; count < directory->files_qtd; count++) {
        file_path[0] = '\0';
        strcat (file_path, dir_name);
        strcat (file_path, "/");
        strcat (file_path, directory->files[count]->d_name);
        log = read_log (file_path, directory->files[count]->d_name);

        printf("%3d %s - ", count, directory->files[count]->d_name);
        printf("cad: %2d ", log->average_cadence);
        printf("hr: %3d ", log->average_hr);
        printf("hr_m: %3d ", log->max_hr);
        printf("s: %.2f ", log->average_speed);
        printf("s_m: %.2f ", log->max_speed);
        printf("dist: %3.2f ", log->distance / 1000);
        printf("elev: %4.2f\n", log->altimetry_gain);

        // verify_and_add_bicycle (bicycles, log);
    }
}

bicycle_log_f *read_log (char *log_path, char *log_name) {
    FILE *log_file;
    reg_f *reg;
    int count;
    char temp_string[BUFSIZ];
    /* contadores dos valores do log */
    int qtd_log_speed = 0, qtd_log_hr = 0, qtd_log_cadence = 0, timestamp_qtd = 1;
    float last_altitude = 0, actual_altitude = 0, last_speed = 0, actual_speed;
    int last_hr = 0, actual_hr = 0, last_cadence = 0, actual_cadence = 0;
    /* timestamps */
    int last_timestamp_sec = 0, actual_timestamp_sec = 0, temp_timestamp_sec = 0;
    /* valores do log */
    char *bicycle_name = NULL, *untreated_date = NULL, *date;
    float distance = 0, average_speed = 0, max_speed = 0, altimetry_gain = 0;
    int average_hr = 0, max_hr = 0, average_cadence = 0;

    if (! (log_file = fopen (log_path, "r"))) {
        fprintf (stderr, RED "[ERROR] " NC "Erro ao ler o log %s\n\n", log_name);
        return NULL;
    }
    reg = inicializa_reg ();

    read_log_header (log_file, &bicycle_name, &untreated_date);
    date = treat_date (untreated_date);

    fgets (temp_string, sizeof (temp_string), log_file);
    while (! feof (log_file)) {
        if (read_log_reg (log_file, reg) != 0) {
            count++;
            temp_timestamp_sec = get_timestamp_sec (reg->timestamp);
            last_timestamp_sec = last_timestamp_sec == 0 ? temp_timestamp_sec : actual_timestamp_sec;
            actual_timestamp_sec = temp_timestamp_sec;
            timestamp_qtd = (actual_timestamp_sec - last_timestamp_sec) == 0 ? 1 :actual_timestamp_sec - last_timestamp_sec;

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
                last_speed = last_speed == 0 ? reg->speed : actual_speed;
                actual_speed = reg->speed;
                if (timestamp_qtd > 1) 
                    printf ("s_a: %f, s_l: %f, timestamp: %d\n", reg->speed, last_speed, timestamp_qtd);
                if (reg->speed == 0)
                    printf ("s_a: %f, s_l: %f, timestamp: %d\n", reg->speed, last_speed, timestamp_qtd);
                // if (timestamp_qtd > 1) {
                    // for (count = 0; count < timestamp_qtd; count++) {
                    //     average_speed += last_speed;
                    //     qtd_log_speed++;
                    // }
                // } else {
                    average_speed += reg->speed;
                    qtd_log_speed++;
                // }
            }

            if (reg->hr != -1) {
                max_hr = max_hr < reg->hr ? reg->hr : max_hr;
                last_hr = last_hr == 0 ? reg->hr : actual_hr;
                actual_hr = reg->hr;
                if (reg->hr != 0) {
                    if (timestamp_qtd > 1) {
                        // for (count = 0; count < timestamp_qtd; count++) {
                        //     average_hr += last_hr;
                        //     qtd_log_hr++;
                        // }
                    } else {
                        average_hr += reg->hr;
                        qtd_log_hr++;
                    }
                }   
            }

            if (reg->cadence != -1) {
                last_cadence = last_cadence == 0 ? reg->cadence : actual_cadence;
                actual_cadence = reg->cadence;
                if (reg->cadence != 0) {
                    if (timestamp_qtd > 1) {
                        // for (count = 0; count < timestamp_qtd; count++) {
                        //     average_cadence += last_cadence;
                        //     qtd_log_cadence++;
                        // }
                    } else {
                        average_cadence += reg->cadence;
                        qtd_log_cadence++;
                    }
                }
            }
            // if (reg->cadence != 0) {
            //     average_cadence += reg->cadence;
            //     qtd_log_cadence++;
            // }
            // max_hr = max_hr < reg->hr ? reg->hr : max_hr;
            // if (reg->hr != 0) {
            //     average_hr += reg->hr;
            //     qtd_log_hr++;
            // }
            // max_speed = max_speed < reg->speed ? reg->speed : max_speed;
            // for (count = 0; count < timestamp_qtd;count++) {
            //     average_speed += reg->speed;
            //     qtd_log_speed++;
            // }
        }
    }

    if (qtd_log_speed != 0) average_speed = average_speed / qtd_log_speed;
    average_speed = average_speed * 3.6f;
    max_speed = max_speed * 3.6f;
    if (qtd_log_hr != 0) average_hr = round (average_hr / qtd_log_hr);
    if (qtd_log_cadence != 0) average_cadence = round (average_cadence / qtd_log_cadence);

    printf("registros lidos: %d\n", count);
    printf("Quantidade de speeds: %d\n", qtd_log_speed);

    free (reg);
    free (untreated_date);
    fclose (log_file);
    return create_log (bicycle_name, date, distance, average_speed, max_speed, average_hr, max_hr, average_cadence, altimetry_gain);
}

void clean_directory (directory_f *directory) {
    int count; 
    for (count = 0; count < directory->files_qtd; count++) {
        free (directory->files[count]);
    }
    free (directory->files);
    free (directory);
}