#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_functions.h"
#include "core_functions.h"
/*
* Função responsavel por ler e armazenas as informações da imagem de tipo P2
*/
void read_p2_file (image_f *image, params_f *params, FILE *image_r) {
    printf("Boura ler um p2\n");
    fclose (image_r);
}

/*
* Função responsavel por ler e armazenas as informações da imagem de tipo P5
*/
void read_p5_file (image_f *image, params_f *params, FILE *image_r) {
    printf("Boura ler um p5\n");
    fclose (image_r);
}

void read_image (image_f *image, params_f *params, char *param[]) {
    FILE *image_r;

    /* verifica se vai carregar a imagem do parametro ou do stdin */
    if (params->input != 0) {
        if (! (image_r = fopen(param[params->input], "r")))
            emit_error (image, params, "A imagem enviada é invalida");
    } else image_r = stdin;

    /* Pegando o image_type da PMG */
    fgets (image->image_type, sizeof (image->image_type), image_r);

    /* verifica se o arquivo enviado é de um tipo permitido */
    if (strcmp (image->image_type, "P2") && strcmp (image->image_type, "P5")) {
        fclose (image_r);
        emit_error (image, params, "O tipo de imagem não é compátivel!");
    } else {
        if (! strcmp (image->image_type, "P2")) 
            read_p2_file (image, params, image_r);
        else read_p5_file (image, params, image_r);
    }
}
