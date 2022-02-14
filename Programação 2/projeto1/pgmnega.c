#include <stdio.h>
#include <stdlib.h>
#include "core_functions.h"
#include "image_functions.h"

int main (int argc, char *argv[]) {
    image_f *image;
    params_f *params;

    /* Inicializa as imagens e os parametros */
    image = initialize_image ();
    params = initialize_params (image);

    /* tratamento dos parametros enviados para o filtro */
    treat_params (image, params, "", 0, argv, argc);

    /* chama a função que lê o pgm */
    read_image (image, params, argv);

    /* Libera todo o espaço alocado */
    clean_structs (image, params);

    exit (EXIT_SUCCESS);
}