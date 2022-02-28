#include <stdio.h>
#include <stdlib.h>
#include "core_functions.h"
#include "image_functions.h"

int main (int argc, char *argv[]) {
    image_f *image;
    params_f *params;
    int row, col;

    params = initialize_params ();
    treat_params (params, "", 0, argv, argc);
    image = read_image (params, argv);
    
    for (row = 0; row < image->height; row++)
        for (col = 0; col < image->width; col++) 
            image->data[(row * image->width) + col] = image->max_value - image->data[(row * image->width) + col];

    send_image (image, params, argv);

    clean_structs (image, params);

    exit (EXIT_SUCCESS);
}