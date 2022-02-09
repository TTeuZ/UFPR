#include <stdio.h>
#include <stdlib.h>
#include "core_functions.h"

#define RED "\e[0;31m"
#define NC "\e[0m"

void emit_error(char *message) {
    fprintf(stderr, RED "[ERROR]\n"
    NC "%s\n", message);
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
*/
void treat_paramns (char *paramns[], int qtd, paramns_f *param) {
    int count;
    for (count = 0; count < qtd; count++) {
        printf("%s\n", paramns[count]);
    }
}