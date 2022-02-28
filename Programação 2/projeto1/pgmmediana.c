#include <stdio.h>
#include <stdlib.h>
#include "core_functions.h"
#include "image_functions.h"

int compare (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int main (int argc, char *argv[]) {
    image_f *image, *intern_image;
    int row, col, row_i, col_i;
    int median, mask, count;
    int *values_array;
    params_f *params;

    params = initialize_params ();
    /* tratamento dos parametros enviados para o filtro */
    treat_params (params, "-m", 0, argv, argc);
    /* chama a função que lê o pgm */
    image = read_image (params, argv);

    /* verifica se o parametro para a mediana foi enviado */
    if (params->ex_param == -1)
        mask = 3;
    else mask = atoi (argv[(int) params->ex_param]);

    if (mask % 2 == 0)
        emit_error (image, params, "O valor da máscara deve ser impar!");

    if (! (values_array = (int *) malloc (sizeof (int) * mask * mask)))
        emit_error (image, params, "Falha em alocação de memória interna!");

    /* cria a imagem interna que vai ser enviada */
    intern_image = initialize_image (image->type, image->height, image->width, image->max_value, params);

    /* preenche a nova imagem com a redução de ruido */
    for (row = 0; row < intern_image->height; row++)
        for (col = 0; col < intern_image->width; col++) {
            if (row < (mask / 2) || row >= (image->height - (mask / 2)) || (col < mask / 2) || col >= (image->width - (mask / 2)))
                intern_image->data[(row * intern_image->width) + col] = image->data[(row * image->width) + col];
            else {
                count = 0;
                for (row_i = -(mask / 2); row_i <= (mask / 2); row_i++) 
                    for (col_i = -(mask / 2); col_i <= (mask / 2); col_i++) {
                        values_array[count] = image->data[((row + row_i) * image->width) + (col + col_i)];
                        count++;           
                    }
                
                qsort (values_array, (mask * mask), sizeof (int), compare);
                median = ((mask * mask) / 2) + 1;
                intern_image->data[(row * intern_image->width) + col] = values_array[median];
            }
        }
    
    /* chama a função que grava a nova pgm */
    send_image (intern_image, params, argv);
    /* Libera todo o espaço alocado */
    clean_structs (image, params);
    clean_structs (intern_image, NULL);
    free (values_array);

    exit (EXIT_SUCCESS);
}