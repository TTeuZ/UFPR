#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <math.h>
#include "constants.h"
#include "bicycles.h"
#include "reader.h"
/*---------------------------------------------- Funções internas ---------------------------------------------*/
/*
* Função que retorna se o arquivo indicado possui '.log' em seu nome,
* ou seja, é um arquivo de log
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
* Função que recebe uma string com o nome do mes do log no formato indicado
* Retorna um int relacionado ao mês, de acordo coma especificação 
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

    free (date);
    return temp_date;
}

/*
* Busca uma string dentro do arquivo caracter por caracter até chegar ao token indicado
* Inicia alocando espaço para o primeiro caracter
* A cada caractere realoca o espaço necessário
*/
char *get_string_until_token (FILE *log_file, char token) {
    char iterator, *temp_string;
    int count;

    count = 0;
    if (! (temp_string = malloc (sizeof (char)))) {
        fprintf (stderr, RED "[ERROR] " NC "Erro de alocação de memoria\n\n");
        fprintf (stderr, RED "[ERROR] " NC "Encerrando...\n\n");
        exit (EXIT_FAILURE);
    }

    iterator = getc (log_file);
    while (iterator != token && iterator != -1) {
        temp_string[count] = iterator;
        iterator = getc (log_file);
        count++;
        if (! (temp_string = realloc (temp_string, sizeof (char) * (count + 1)))) {
            fprintf (stderr, RED "[ERROR] " NC "Erro de alocação de memoria realoc\n\n");
            fprintf (stderr, RED "[ERROR] " NC "Encerrando...\n\n");
            exit (EXIT_FAILURE);
        }
    }
    temp_string[count] = '\0';
    return temp_string;
}

/*
* Funçãoq eu recebe o arquivo de log é pega o timestamp do bloco atual
* Utiliza o ponteiro atual do arquivo para buscar o timestamps
* Retorna uma string com o valor do timestamp ou null caso não seja possivel computar a string
*/
char* get_timestamp (FILE *log_file) {
    char iterator, *temp_string, *timestamp = NULL;
    int qtd = 0, has_found = 0;

    iterator = getc (log_file);
    if (iterator != -1) {
        fseek (log_file, -1, SEEK_CUR);
        while (has_found == 0) {
            temp_string = get_string_until_token (log_file, ':');
            qtd += strlen (temp_string);

            if (strcmp (temp_string, "timestamp") == 0) {
                fseek (log_file, 1, SEEK_CUR);
                timestamp = get_string_until_token (log_file, '\n');
                qtd += strlen (timestamp) + 3;
                has_found = 1;
            } else {
                temp_string = get_string_until_token (log_file, '\n');
                qtd += strlen (temp_string) + 2;
            }
        }
        fseek (log_file, (qtd * -1), SEEK_CUR);
    }

    return timestamp;
}

int get_timestamp_sec (char *timestamp) {
    char *sec, *min, *hour;

    strtok (timestamp, " :");
    hour = strtok (NULL, " :");
    min = strtok (NULL, " :");
    sec = strtok (NULL, " :");

    return (atoi (hour) * 3600) + (atoi (min) * 60) + atoi (sec);
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
    int count;
    char file_path[256];

    for (count = 0; count < directory->files_qtd; count++) {
        file_path[0] = '\0';
        strcat (file_path, dir_name);
        strcat (file_path, "/");
        strcat (file_path, directory->files[count]->d_name);

        read_log (file_path, directory->files[count]->d_name, bicycles);
        free (directory->files[count]);
    }
    free (directory->files);
}

void read_log (char *log_path, char *log_name, bicycles_f *bicycles) {
    FILE *log_file;
    char *temp_string;
    char iterator;
    int count;
    /* timestamps */
    char *timestamp;
    int last_timestamp_sec = 0, actual_timestamp_sec = 0;
    /* contadores dos valores do log */
    int qtd_log_speed = 0, qtd_log_hr = 0, qtd_log_cadence = 0, timestamp_qtd = 0;
    float last_altitude = 0, actual_altitude = 0;
    /* valores do log */
    char *bicycle_name, *date;
    float distance = 0, avarage_speed = 0, max_speed = 0, altimetry_gain = 0;
    int avarage_hr = 0, max_hr = 0, avarage_cadence = 0;

    if (! (log_file = fopen (log_path, "r"))) {
        fprintf (stderr, RED "[ERROR] " NC "Erro ao ler o log %s\n\n", log_name);
        return ;
    }

    /* Pulando a frase 'Gear: ' e buscando o nome da bicicleta*/
    fseek (log_file, 6, SEEK_CUR);
    bicycle_name = get_string_until_token (log_file, '\n');

    /* Pulando a frase 'Date: ' e buscando a data e a formatando para dd/mm/yyyy*/
    fseek (log_file, 6, SEEK_CUR);
    date = get_string_until_token (log_file, '\n');
    date = treat_date (date);

    iterator = getc (log_file);
    while (! feof (log_file)) {
        if (iterator != 10) {
            fseek (log_file, -1, SEEK_CUR);
            temp_string = get_string_until_token (log_file, ':');

            if (strcmp (temp_string, "altitude") == 0) {
                fseek (log_file, 1, SEEK_CUR);

                temp_string = get_string_until_token (log_file, ' ');
                if (last_altitude == 0) {
                    last_altitude = atof (temp_string );
                    actual_altitude = atof (temp_string );
                } else {
                    last_altitude = actual_altitude;
                    actual_altitude = atof (temp_string );
                }

                if (actual_altitude > last_altitude) 
                    altimetry_gain += actual_altitude - last_altitude;

                fseek (log_file, 2, SEEK_CUR);
            } else if (strcmp (temp_string, "cadence") == 0) {
                fseek (log_file, 1, SEEK_CUR);

                temp_string = get_string_until_token (log_file, ' ');

                if (timestamp_qtd != 0) {
                    for (count = 0; count < timestamp_qtd; count++) {
                        avarage_cadence += atoi (temp_string);
                        qtd_log_cadence++;
                    }
                } else {
                    avarage_cadence += atoi (temp_string);
                    qtd_log_cadence++;
                }

                fseek (log_file, 4, SEEK_CUR);
            } else if (strcmp (temp_string, "distance") == 0) {
                fseek (log_file, 1, SEEK_CUR);

                temp_string = get_string_until_token (log_file, ' ');
                distance = atof (temp_string);

                fseek (log_file, 2, SEEK_CUR);
            } else if (strcmp (temp_string, "heart_rate") == 0) {
                fseek (log_file, 1, SEEK_CUR);

                temp_string = get_string_until_token (log_file, ' ');
                max_hr = max_hr < atoi (temp_string) ? atoi (temp_string) : max_hr;

                if (timestamp_qtd != 0) {
                    for (count = 0; count < timestamp_qtd; count++) {
                        avarage_hr += atoi (temp_string);
                        qtd_log_hr++;
                    }
                } else {
                    avarage_hr += atoi (temp_string);
                    qtd_log_hr++;
                }

                fseek (log_file, 4, SEEK_CUR);
            } else if (strcmp (temp_string, "speed") == 0) {
                fseek (log_file, 1, SEEK_CUR);

                temp_string = get_string_until_token (log_file, ' ');
                max_speed = max_speed < atof (temp_string) ? atof (temp_string) : max_speed;
                avarage_speed += atof (temp_string);
                qtd_log_speed++;

                fseek (log_file, 4, SEEK_CUR);
            } else {
                temp_string = get_string_until_token (log_file, '\n');
            }
            free (temp_string);
        } else {
            timestamp = get_timestamp (log_file);
            if (timestamp != NULL) {
                if (last_timestamp_sec == 0) {
                    last_timestamp_sec = get_timestamp_sec (timestamp);
                    actual_timestamp_sec = last_timestamp_sec;
                } else {
                    last_timestamp_sec = actual_timestamp_sec;
                    actual_timestamp_sec = get_timestamp_sec (timestamp);
                    timestamp_qtd = actual_timestamp_sec - last_timestamp_sec;
                }
            }
        }
        iterator = getc (log_file);
    }

    avarage_speed = avarage_speed / qtd_log_speed;
    avarage_hr = round (avarage_hr / qtd_log_hr);
    avarage_cadence = round (avarage_cadence / qtd_log_cadence);

    printf ("Nome: %s\n", bicycle_name);
    printf ("data: %s\n", date);
    printf ("Distancia: %f\n", distance);
    printf ("velocidade media: %f\n", avarage_speed);
    printf ("Velocidade maxima: %f\n", max_speed);
    printf ("hr media: %d\n", avarage_hr);
    printf ("hr maxima: %d\n", max_hr);
    printf ("cadencia media: %d\n", avarage_cadence);
    printf ("ganho de altimetria: %f\n", altimetry_gain);
    printf ("\n");
}