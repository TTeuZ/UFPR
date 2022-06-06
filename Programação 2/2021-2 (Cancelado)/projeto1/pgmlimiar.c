#include <stdio.h>
#include <stdlib.h>
#include "core_functions.h"
#include "image_functions.h"

int main (int argc, char *argv[]) {
    image_f *image;
    params_f *params;
    float limiar;
    int divider, row, col;

    params = initialize_params ();
    treat_params (params, "-l", 0, argv, argc);
    image = read_image (params, argv);

    /* verifica se o parametro do limiar foi enviado */
    if (params->ex_param == -1)
        limiar = 0.5;
    else limiar = atof (argv[(int) params->ex_param]);

    /* valida se o valor informado é valido */
    if (limiar > 1 || limiar < 0)
        emit_error (image, params, "O limiar deve ser um numero entre 0 e 1!");

    /* seta o valor limite para decidir se o bit vai virar preto ou branco */
    divider = (int) image->max_value * limiar;
    image->max_value = 255;
    
    for (row = 0; row < image->height; row++)
        for (col = 0; col < image->width; col++) {
            if (image->data[(row * image->width) + col] >= divider) 
                image->data[(row * image->width) + col] = 255;
            else image->data[(row * image->width) + col] = 0;
        } 

    send_image (image, params, argv);

    clean_structs (image, params);

    exit (EXIT_SUCCESS);
}