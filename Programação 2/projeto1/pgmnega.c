#include <stdio.h>
#include <stdlib.h>
#include "core_functions.h"
#include "image_functions.h"

int main (int argc, char *argv[]) {
    image_f *image;
    params_f *params;
    int row, col;

    params = initialize_params ();
    /* tratamento dos parametros enviados para o filtro */
    treat_params (params, "", 0, argv, argc);
    /* chama a função que lê o pgm */
    image = read_image (params, argv);
    
    /* aplica o efeito de negativo */
    for (row = 0; row < image->height; row++)
        for (col = 0; col < image->width; col++) {
            image->data[(row * image->width) + col] = image->max_value - image->data[(row * image->width) + col];
        } 

    /* chama a função que grava a nova pgm */
    send_image (image, params, argv);
    /* Libera todo o espaço alocado */
    clean_structs (image, params);

    exit (EXIT_SUCCESS);
}