#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "core_functions.h"
#include "image_functions.h"

# define M_PI 3.14159265358979323846

int main (int argc, char *argv[]) {
    image_f *image, *intern_image;
    params_f *params;
    int degrees, row, col;
    double radians, cos_a, sin_a;

    /* Inicializa as imagens e os parametros */
    image = initialize_image ();
    params = initialize_params (image);

    /* tratamento dos parametros enviados para o filtro */
    treat_params (image, params, "-a", 0, argv, argc);
    /* chama a função que lê o pgm */
    read_image (image, params, argv);

    if (! (intern_image = malloc (sizeof (image_f)))) 
        emit_error (image, params, "Alocação da imagem de passagem falhou!");
    
    /* gera uma copia da imagem que foi enviada*/
    strcpy (intern_image->type, image->type);
    intern_image->max_value = image-> max_value;
    intern_image->width = image->width;
    intern_image->height = image->height;
    intern_image->data = malloc (sizeof (intern_image->data) * intern_image->height * intern_image->width);
    for (row = 0; row < intern_image->height; row++)
        for (col = 0; col < intern_image->width; col++) {
            intern_image->data[(row * intern_image->width) + col] = image->data[(row * image->width) + col];
        } 

    /* verifica se o parametro para rotação foi enviado */
    if (params->ex_param == -1)
        degrees = 90;
    else degrees =  atoi (argv[(int) params->ex_param]);

    /* Calcula o algulo dado para radianos, seu seno e seu cosseno */
    radians = (M_PI * degrees) / 180;
    cos_a = cos (radians);
    sin_a = sin (radians);


    /* chama a função que grava a nova pgm */
    send_image (intern_image, params, argv);
    /* Libera todo o espaço alocado */
    clean_structs (image, params);

    exit (EXIT_SUCCESS);
}