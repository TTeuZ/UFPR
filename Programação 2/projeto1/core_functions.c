#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "core_functions.h"

void emit_error (image_f *image, params_f *params, char *message) {
    fprintf (stderr, RED "[ERROR] " NC "%s\n\n", message);
    clean_structs (image, params);
    exit (EXIT_FAILURE);
}

void clean_structs (image_f *image, params_f *params) {
    if (image != NULL) {
        if (image->data != NULL)
            free (image->data);
        free (image);
    }
    if (params != NULL)
        free (params);
}

image_f *initialize_image () {
    image_f *image;
    if (! (image = malloc (sizeof (image_f)))) {
        emit_error (NULL, NULL, "Falha na alocação de memória para a imagem!\n");
        exit (EXIT_FAILURE);
    } else {
        image->data = NULL;
        return image;
    }
}

params_f *initialize_params (image_f *image) {
    params_f *params;
    if (! (params = malloc (sizeof (params_f)))) {
        emit_error (image, NULL, "Falha na alocação de memória para os parametros!\n");
        exit (EXIT_FAILURE);
    } else {
        params->input = 0;
        params->output = 0;
        params->ex_param = -1;
        return params;
    }
}

/*
* Recebe o argv e o argc como parametros, e varre eles armazenando os parametros
* Se o -i não for indicado, e não tiver nada na entrada padrão, encerra o filtro com erro
* Se o -o não for indicado, e não tive nada na saida padrão, encerra o filtro com erro
* need_extra indica se teremos erro caso o parametro extra não seja indicado.
*/
void treat_params (image_f *image, params_f *params, char *extra_param, int need_extra, char *param[], int qtd) {
    int count;
    /* caso o parametro exista, armazena a sua posição na struct */
    for (count = 1; count < qtd; count++) {
        if (! strcmp (param[count], "-i")) 
            params->input = count+1;
        if (! strcmp (param[count], "-o")) 
            params->output = count+1;
        if (! strcmp (param[count], extra_param))
            params->ex_param = count+1;
    }
    /* Verifica se os paramentros não indicados possuem respando nas entradas e saidas padrões
    Verifica se o parametro extra é obrigatório, e se for, verifica se foi preenchido */
    if ((params->input == 0) && fseek (stdin, 0, SEEK_END)) 
        emit_error (image, params, "Você não indicou um arquivo de entrada");
    else rewind (stdin);
    if ((params->output == 0) && fseek (stdout, 0, SEEK_END)) 
        emit_error (image, params,"Você não indicou um arquivo de saida");
    else rewind (stdout);
    if ((params->ex_param == -1) &&  need_extra) 
        emit_error (image, params, "Você não indicou o parametro de configuração");
}