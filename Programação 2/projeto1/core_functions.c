#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "core_functions.h"

#define RED "\e[0;31m"
#define NC "\e[0m"

void emit_error (image_f *image, paramns_f *paramns, char *message) {
    fprintf (stderr, RED "[ERROR] " NC "%s\n", message);
    clean_structs (image, paramns);
    exit (EXIT_FAILURE);
}

void clean_structs (image_f *image, paramns_f *paramns) {
    if (image != NULL) {
        if (image->image_data != NULL)
            free (image->image_data);
        free (image);
    }
    if (paramns != NULL)
        free (paramns);
}

image_f *initialize_image () {
    image_f *image;
    if (! (image = malloc (sizeof (image_f)))) {
        emit_error (NULL, NULL, "Falha na alocação de memória para a imagem!\n");
        exit (EXIT_FAILURE);
    } else {
        image->image_data = NULL;
        return image;
    }
}

paramns_f *initialize_paramns (image_f *image) {
    paramns_f *paramns;
    if (! (paramns = malloc (sizeof (paramns_f)))) {
        emit_error (image, NULL, "Falha na alocação de memória para os parametros!\n");
        exit (EXIT_FAILURE);
    } else {
        paramns->input = 0;
        paramns->output = 0;
        paramns->ex_param = 0;
        return paramns;
    }
}

/*
* Recebe o argv e o argc como parametros, e varre eles armazenando os parametros
* Se o -i não for indicado, e não tiver nada na entrada padrão, encerra o filtro com erro
* Se o -o não for indicado, e não tive nada na saida padrão, encerra o filtro com erro
* need_extra indica se teremos erro caso o parametro extra não seja indicado.
*/
void treat_paramns (image_f *image, paramns_f *paramns, char *extra_param, int need_extra, char *param[], int qtd) {
    int count;
    /* caso o parametro exista, armazena a sua posição na struct */
    for (count = 1; count < qtd; count++) {
        if (! strcmp (param[count], "-i")) 
            paramns->input = count+1;
        if (! strcmp (param[count], "-o")) 
            paramns->output = count+1;
        if (! strcmp (param[count], extra_param))
            paramns->ex_param = count+1;
    }
    /* Verifica se os paramentros não indicados possuem respando nas entradas e saidas padrões
    Verifica se o parametro extra é obrigatório, e se for, verifica se foi preenchido */
    if ((paramns->input == 0) && fseek(stdin, 0, SEEK_END)) 
        emit_error (image, paramns, "Você não indicou um arquivo de entrada");
    else rewind (stdin);
    if ((paramns->output == 0) && fseek(stdout, 0, SEEK_END)) 
        emit_error (image, paramns,"Você não indicou um arquivo de saida");
    else rewind (stdout);
    if ((paramns->ex_param == 0) &&  need_extra) 
        emit_error (image, paramns, "Você não indicou o parametro de configuração");
}

/*----------------------------------  Image Functions ----------------------------------------*/
void read_image (image_f *image, paramns_f *paramns, char *param[]) {
    FILE *image_r;
    char line[100];

    if (paramns->input != 0) {
        if (! (image_r = fopen(param[paramns->input], "r")))
            emit_error (image, paramns, "A imagem enviada é invalida");
    } else image_r = stdin;

    fgets (line, 1024, image_r);
    printf ("%s\n",line);
}
/*----------------------------------  Image Functions ----------------------------------------*/