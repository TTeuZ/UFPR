#include <stdio.h>
#include <stdlib.h>
#include "core_functions.h"
#include "image_functions.h"

int main (int argc, char *argv[]) {
    image_f *image;
    params_f *params;
    float limiar;
    int divider, row, col;

    /* Inicializa as imagens e os parametros */
    image = initialize_image ();
    params = initialize_params (image);
    /* tratamento dos parametros enviados para o filtro */
    treat_params (image, params, "-l", 0, argv, argc);
    /* chama a função que lê o pgm */
    read_image (image, params, argv);

    /* verifica se o parametro do limiar foi enviado */
    if (params->ex_param == -1)
        limiar = 0.5;
    else limiar =  atof (argv[(int) params->ex_param]);

    /* seta o valor limite para decidir se o bit vai virar preto ou branco */
    divider = (int) image->max_value * limiar;

    /* aplica o efeito de limiar */
    for (row = 0; row < image->height; row++)
        for (col = 0; col < image->width; col++) {
            if (image->data[(row * image->width) + col] >= divider) 
                image->data[(row * image->width) + col] = image->max_value;
            else image->data[(row * image->width) + col] = 0;
        } 

    /* chama a função que grava a nova pgm */
    send_image (image, params, argv);
    /* Libera todo o espaço alocado */
    clean_structs (image, params);

    exit (EXIT_SUCCESS);
}