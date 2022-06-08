#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "constants.h"
#include "reader.h"
/*---------------------------------------------- Funções internas ----------------------------------------------*/
int filterFiles (const struct dirent *current_dir) {
    printf("teste: %d\n", current_dir->d_type);
    return 1;
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
    // for (int teste = 0; teste < directory->files_qtd; teste++) {
    //     printf("TESTE\n");
    // }
    return directory;
}