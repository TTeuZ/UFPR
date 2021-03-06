#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_functions.h"
#include "core_functions.h"

/*
* Função responsavel por ler e armazenas as informações da imagem de tipo P2
*/
void read_p2_file (image_f *image, params_f *params, FILE *image_r) {
    int row, col, value;
    
    for (row = 0; row < image->height; row++)
        for (col = 0; col < image->width; col++) {
            fscanf (image_r,"%d", &value);
            image->data[(row * image->width) + col] = value;
        } 
}

/*
* Função responsavel por ler e armazenas as informações da imagem de tipo P5
*/
void read_p5_file (image_f *image, params_f *params, FILE *image_r) {
    int row, col;
    char value;

    for (row = 0; row < image->height; row++)
        for (col = 0; col < image->width; col++) {
            value = getc (image_r);
            image->data[(row * image->width) + col] = value;
        } 
}

image_f *read_image (params_f *params, char *param[]) {
    char type[3];
    int width, height, max_value;
    image_f *image;
    FILE *image_r;

    fprintf (stderr, YELLOW "[PROCESSANDO] "  NC "Lendo a imagem enviada...\n\n");

    /* verifica se vai carregar a imagem do parametro ou do stdin */
    if (params->input != 0) {
        if (! (image_r = fopen (param[params->input], "r")))
            emit_error (NULL, params, "A imagem enviada é invalida");
    } else image_r = stdin;

    fgets (type, 3, image_r);

    /* verifica se o arquivo enviado é de um tipo permitido */
    if (strcmp (type, "P2") && strcmp (type, "P5")) {
        fclose (image_r);
        emit_error (NULL, params, "O tipo de imagem não é compátivel!");
    }

    while (getc (image_r) != '\n'); /* Vai até o fim da linha */
    while (getc (image_r) == '#') { /* Pula os comentarios */
        while (getc (image_r) != '\n');
    }
    fseek (image_r, -1, SEEK_CUR); /* volta um caracter para traz */
    
    fscanf (image_r, "%d", &width);
    fscanf (image_r, "%d", &height);
    fscanf (image_r, "%d", &max_value);
    
    image = initialize_image (type, height, width, max_value, params);

    if (! strcmp (image->type, "P2")) 
        read_p2_file (image, params, image_r);
    else read_p5_file (image, params, image_r);

    fclose (image_r);
    return image;
}

void send_image (image_f *image, params_f *params, char *param[]) {
    int row, col;
    FILE *new_image;

    fprintf (stderr, YELLOW "[PROCESSANDO] "  NC "Gravando a imagem resultante...\n\n"); 

    /* verifica se vai carregar a imagem do parametro ou do stdout */
    if (params->output != 0) {
        if (! (new_image = fopen(param[params->output], "w")))
            emit_error (image, params, "A imagem enviada é invalida");
    } else new_image = stdout;

    fprintf (new_image, "%s\n", image->type);
    fprintf (new_image, "%d %d\n", image->width, image->height);
    fprintf (new_image, "%d\n", image->max_value);

    if (! strcmp (image->type, "P2")) {
        for (row = 0; row < image->height; row++) 
            for (col = 0; col < image->width; col++) 
                fprintf (new_image, "%d ", image->data[(row * image->width) + col]);
    } else {
        for (row = 0; row < image->height; row++) 
            for (col = 0; col < image->width; col++) 
                putc (image->data[(row * image->width) + col], new_image);
    }
    fprintf (new_image, "\n");

    fprintf (stderr, GREEN "[SUCESSO] "  NC "Gravando efetuada com sucesso!\n\n");
    fclose (new_image);
}