#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "core_functions.h"

#define RED "\e[0;31m"
#define NC "\e[0m"

void emit_error(char *message) {
    fprintf(stderr, RED "[ERROR] "
    NC "%s\n", message);
    exit(EXIT_FAILURE);
}

void clean_structs (image_f *image, paramns_f *paramns) {
    free (image);
    free (paramns);
}

image_f *initialize_image () {
    image_f *image;
    if (!(image = malloc (sizeof(image_f)))) {
        emit_error("Falha na alocação de memória para a imagem!\n");
        exit(EXIT_FAILURE);
    } else return image;
}

paramns_f *initialize_paramns () {
    paramns_f *paramns;
    if (!(paramns = malloc (sizeof(paramns_f)))) {
        emit_error("Falha na alocação de memória para os parametros!\n");
        exit(EXIT_FAILURE);
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
void treat_paramns (char *paramns[], int qtd, paramns_f *param, char *extra_param, int need_extra) {
    int count;
    /* caso o parametro exista, armazena a sua posição na struct */
    for (count = 1; count < qtd; count++) {
        if (! strcmp (paramns[count], "-i")) 
            param->input = count+1;
        if (! strcmp (paramns[count], "-o")) 
            param->output = count+1;
        if (! strcmp (paramns[count], extra_param))
            param->ex_param = count+1;
    }
    /* Verifica se os paramentros não indicados possuem respando nas entradas e saidas padrões
    Verifica se o parametro extra é obrigatório, e se for, verifica se foi preenchido */
    if ((param->input == 0) && fseek(stdin, 0, SEEK_END)) 
        emit_error("Você não indicou um arquivo de entrada");
    if ((param->output == 0) && fseek(stdout, 0, SEEK_END)) 
        emit_error("Você não indicou um arquivo de saida");
    if ((param->ex_param == 0) &&  need_extra) 
        emit_error("Você não indicou o parametro de configuração");
}

/*----------------------------------  Image Functions ----------------------------------------*/
void read_image (image_f *image, paramns_f *param, char *paramns[]) {
    FILE *image_r;
    char line[100];

    if (param->input != 0) 
        image_r = fopen(paramns[param->input], "r");
    else image_r = stdin;

    fgets (line, 1024, image_r);
    printf ("%s\n",line) ;
}
/*----------------------------------  Image Functions ----------------------------------------*/