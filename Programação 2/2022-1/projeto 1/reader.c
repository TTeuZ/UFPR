#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "constants.h"
#include "reader.h"
/*---------------------------------------------- Funções internas ----------------------------------------------*/
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
/*---------------------------------------------- Funções internas ----------------------------------------------*/

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