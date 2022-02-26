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
    int degree, cong_degree; /* variaveis para os angulas em graus */
    int n_height, n_width; /* variaveis para as altura e largura da nova imagem */
    int row, col, row_a, col_a; /* variaveis das linhas e colunas */
    double radian, cong_radian; /* variaveis para os angulos em radianos */
    double cos_r, sin_r, cos_g, sin_g; /* variaveis para os seno e cosseno do angulo de rotação */

    /* Inicializa as imagens e os parametros */
    params = initialize_params ();
    /* tratamento dos parametros enviados para o filtro */
    treat_params (params, "-a", 0, argv, argc);
    /* chama a função que lê o pgm */
    image = read_image (params, argv);

    /* verifica se o parametro para rotação foi enviado */
    if (params->ex_param == -1)
        degree = 90;
    else degree =  atoi (argv[(int) params->ex_param]);

    /* calcula o algulo congruente da imagem (considerando o 90° da borda a imagem) */
    cong_degree = 90 - degree; 

    /* calcula o angulo em radianos */
    radian = (M_PI * degree) / 180;
    cong_radian = (M_PI * cong_degree) / 180;

    /* calcula os senos e cossenos */
    cos_r = cos (radian);
    sin_r = sin (radian);
    cos_g = cos (cong_radian);
    sin_g = sin (cong_radian);

    n_width = abs (round ((cos_g * image->height) + (cos_r * image->width)));
    n_height = abs (round ((sin_g * image->height) + (sin_r * image->width)));

    intern_image = initialize_image (image->type, n_height, n_width, 255, params);

    for (row = 0; row < intern_image->height; row++)
        for (col = 0; col < intern_image->width; col++) {
            if (row == 0 || row == intern_image->height - 1) 
                intern_image->data[(row * intern_image->width) + col] = 0;
            else if (col == 0 || col == intern_image->width - 1)
                intern_image->data[(row * intern_image->width) + col] = 0;
            else
                intern_image->data[(row * intern_image->width) + col] = 255;
        }

    for (row = 0; row < intern_image->height; row++)
        for (col = 0; col < intern_image->width; col++) {
            row_a = ((row * cos_r) - (col * sin_r));
            col_a = ((col * cos_r) + (row * sin_r));
            
            if (row_a >= 0 && row_a < image->height && col_a >= 0 && col_a < image->width) {
                intern_image->data[(row * intern_image->width) + col] = image->data[(row_a * image->width) + col_a];  
            } else {
                printf ("(%d, %d) ", row_a, col_a);
            }
        }

    /* chama a função que grava a nova pgm */
    send_image (intern_image, params, argv);
    /* Libera todo o espaço alocado */
    clean_structs (image, params);

    exit (EXIT_SUCCESS);
}