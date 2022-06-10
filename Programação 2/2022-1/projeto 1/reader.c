#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "constants.h"
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
    if (current_dir->d_type == D_FILE && is_log_file (current_dir->d_name)) 
        return 1;
    else return 0;
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
    while (iterator != token) {
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

void load_logs (directory_f *directory, char *dir_name) {
    int count;
    char file_path[256];

    for (count = 0; count < directory->files_qtd; count++) {
        file_path[0] = '\0';
        strcat (file_path, dir_name);
        strcat (file_path, "/");
        strcat (file_path, directory->files[count]->d_name);

        read_log (file_path, directory->files[count]->d_name);
        free (directory->files[count]);
    }
    free (directory->files);
}

void read_log (char *log_path, char *log_name) {
    FILE *log_file;
    int count;
    char *bicycle_name;
    char iterator;

    if (! (log_file = fopen (log_path, "r"))) {
        fprintf (stderr, RED "[ERROR] " NC "Erro ao ler o log %s\n\n", log_name);
        return ;
    }

    /* Pulando a frase 'Gear: ' */
    for (count = 0; count < 6; count++) 
        iterator = getc (log_file);
    
    bicycle_name = get_string_until_token (log_file, '\n');
    
    printf("\n");
}