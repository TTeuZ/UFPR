#include <stdio.h>
#include <stdlib.h>
#include "core_functions.h"

int main (int argc, char *argv[]) {
    image_f *image;
    paramns_f *paramns;

    /* Inicializa as imagens e os parametros */
    image = initialize_image ();
    paramns = initialize_paramns ();

    printf("endereço da imagem: %p\n", &image);
    printf("endereço dos parametros: %p\n", &paramns);

    /* Libera todo o espaço alocado */
    clean_structs (image, paramns);

    exit(EXIT_SUCCESS);
}