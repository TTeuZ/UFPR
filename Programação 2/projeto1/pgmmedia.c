#include <stdio.h>
#include <stdlib.h>
#include "core_functions.h"
#include "image_functions.h"

int main (int argc, char *argv[]) {
    image_f *image, *intern_image;
    int row, col, row_a, col_a, average;
    params_f *params;

    params = initialize_params ();
    treat_params (params, "", 0, argv, argc);
    image = read_image (params, argv);
    
    intern_image = initialize_image (image->type, image->height, image->width, image->max_value, params);

    for (row = 0; row < intern_image->height; row++)
        for (col = 0; col < intern_image->width; col++) {
            average = 0;
            /* gera o 'array interno' com os valores desejados */
            for (row_a = -1; row_a < 2; row_a++) 
                for (col_a = -1; col_a < 2; col_a++) 
                    /* verifica se os valores desse novo array vão 'extrapolar' as bordas da imagem */
                    if (((row + row_a) >= 0 && (col + col_a) >= 0) && ((row + row_a) < image->height && (col + col_a) < image->width))
                        average = average + image->data[((row + row_a) * image->width) + (col + col_a)];
            average = (average / 9);
            intern_image->data[(row * intern_image->width) + col] = average;
        } 

    send_image (intern_image, params, argv);

    clean_structs (image, params);
    clean_structs (intern_image, NULL);

    exit (EXIT_SUCCESS);
}