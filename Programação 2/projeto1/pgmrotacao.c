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
    int temp_h, temp_w; /* variaveis para armazenar valores de altura e largura temporarios */
    int min_col, min_row; /* variaveis que armazeman o min da altura e largura */
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

    /* calcula o algulo congruente da imagem (considerando o 90° da borda a imagem 180 - 90 - degree == 90 - degree) */
    cong_degree = 90 - degree; 
    /* calcula o angulo em radianos */
    radian = (M_PI * degree) / 180;
    cong_radian = (M_PI * cong_degree) / 180;
    /* calcula os senos e cossenos */
    cos_r = cos (radian);
    sin_r = sin (radian);
    cos_g = cos (cong_radian);
    sin_g = sin (cong_radian);

    /* busca as novas altura e largura da imagem */
    temp_w = abs (round (abs (cos_g * image->height) + abs (cos_r * image->width)));
    temp_h = abs (round (abs (sin_g * image->height) + abs (sin_r * image->width)));
    /* inicializa a imagem interna */
    intern_image = initialize_image (image->type, temp_h, temp_w, 255, params);

    /* Busca os valores min de cada eixo da nova imagem */
    min_col = (image->width * cos_r);
    min_row = (image->width * sin_r);

    temp_w = (image->width * cos_r) - (image->height * sin_r);
    temp_h = (image->width * sin_r) + (image->height * cos_r);

    if (temp_w < min_col) min_col = temp_w;
    if (temp_h < min_row) min_row = temp_h;

    temp_w = (0 * cos_r) - (image->height * sin_r);
    temp_h = (0 * sin_r) + (image->height * cos_r);

    if (temp_w < min_col) min_col = temp_w;
    if (temp_h < min_row) min_row = temp_h;

    if (degree <= 90) min_row = 0;
    if (degree <= 360 && degree > 270) min_col = 0;

    /* preenche a nova imagem rotacionada */
    for (row = 0; row < intern_image->height; row++)
        for (col = 0; col < intern_image->width; col++) {
            row_a = (((row + 1 + min_row) * cos_r) - ((col + 1 + min_col) * sin_r));
            col_a = (((col + 1 + min_col) * cos_r) + ((row + 1 + min_row) * sin_r)); 

            if (row_a >= 0 && row_a < image->height && col_a >= 0 && col_a < image->width) 
                intern_image->data[(row * intern_image->width) + col] = image->data[(row_a * image->width) + col_a];
            else {
                if (row == 0 || row == intern_image->height - 1) 
                intern_image->data[(row * intern_image->width) + col] = 0;
            else if (col == 0 || col == intern_image->width - 1)
                intern_image->data[(row * intern_image->width) + col] = 0;
            else
                intern_image->data[(row * intern_image->width) + col] = 255;
            }  
        } 

    /* chama a função que grava a nova pgm */
    send_image (intern_image, params, argv); 
    /* Libera todo o espaço alocado */
    clean_structs (image, params);
    clean_structs (intern_image, NULL);

    exit (EXIT_SUCCESS);
}