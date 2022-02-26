#include <stdio.h>
#include <stdlib.h>
#include "core_functions.h"
#include "image_functions.h"

int main (int argc, char *argv[]) {
    image_f *image;
    params_f *params;

    params = initialize_params ();
    /* tratamento dos parametros enviados para o filtro */
    treat_params (params, "", 0, argv, argc);
    /* chama a função que lê o pgm */
    image = read_image (params, argv);

    /* chama a função que grava a nova pgm */
    send_image (image, params, argv);
    /* Libera todo o espaço alocado */
    clean_structs (image, params);

    exit (EXIT_SUCCESS);
}