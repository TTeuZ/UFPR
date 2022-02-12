#include <stdio.h>
#include <stdlib.h>
#include "core_functions.h"

int main (int argc, char *argv[]) {
    image_f *image;
    paramns_f *paramns;

    /* Inicializa as imagens e os parametros */
    image = initialize_image ();
    paramns = initialize_paramns (image);

    /* tratamento dos parametros enviados para o filtro */
    treat_paramns (image, paramns, "", 0, argv, argc);

    /* chama a função que lê o pgm */
    read_image (image, paramns, argv);

    /* Libera todo o espaço alocado */
    clean_structs (image, paramns);

    exit (EXIT_SUCCESS);
}