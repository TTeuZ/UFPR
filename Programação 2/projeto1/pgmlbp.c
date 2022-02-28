#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "core_functions.h"
#include "image_functions.h"

int main (int argc, char *argv[]) {
    image_f *image, *intern_image;
    int row, col, row_l, col_l;
    int lbp, limiar, count, count_i;
    int values_array[7];
    params_f *params;

    params = initialize_params ();
    /* tratamento dos parametros enviados para o filtro */
    treat_params (params, "", 0, argv, argc);
    /* chama a função que lê o pgm */
    image = read_image (params, argv);

    /* cria a imagem interna que vai ser enviada */
    intern_image = initialize_image (image->type, image->height, image->width, image->max_value, params);

    /* Aplicação do filtro */
    for (row = 0; row < intern_image->height; row++)
        for (col = 0; col < intern_image->width; col++) {
            count = 0;
            /* gera a 'matriz interna' com os valores desejados */
            for (row_l = -1; row_l < 2; row_l++) 
                for (col_l = -1; col_l < 2; col_l++) 
                    /* verifica se os valores dessa nova matriz vão 'extrapolar' as bordas da imagem */
                    if (((row + row_l) >= 0 && (col + col_l) >= 0) && ((row + row_l) < image->height && (col + col_l) < image->width)) {
                        limiar = image->data[(row * image->width) + col];
                        /* pula o valor do meio */
                        if (row_l != 0 || col_l != 0) {
                            values_array[count] = image->data[((row + row_l) * image->width) + (col + col_l)] >= limiar ? 1 : 0;
                            count++;
                        }
                    }
            lbp = 0;
            /* executa a varredura dos valores computados e soma em lbp */
            for (count_i = 0; count_i < count; count_i++) {
                values_array[count_i] = values_array[count_i] * pow (2, count_i);
                lbp += values_array[count_i];
            }
            intern_image->data[(row * intern_image->width) + col] = lbp;
        } 

    /* chama a função que grava a nova pgm */
    send_image (intern_image, params, argv);
    /* Libera todo o espaço alocado */
    clean_structs (image, params);
    clean_structs (intern_image, NULL);

    exit (EXIT_SUCCESS);
}