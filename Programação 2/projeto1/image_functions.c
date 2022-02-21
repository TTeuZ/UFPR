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
    
    /* le a matriz da imagem e armazena na struct */
    if ((image->data = malloc (sizeof (image->data) * image->height * image->width))) {
        for (row = 0; row < image->height; row++)
            for (col = 0; col < image->width; col++) {
                fscanf(image_r,"%d", &value);
                image->data[(row * image->width) + col] = value;
            } 
    } else emit_error (image, params, "Falha na alocação de memória para o data da imagem!\n");

    fclose (image_r);
}

/*
* Função responsavel por ler e armazenas as informações da imagem de tipo P5
*/
void read_p5_file (image_f *image, params_f *params, FILE *image_r) {
    int row, col;
    char value;

    /* le a matriz da imagem e armazena na struct */
    if ((image->data = malloc (sizeof (image->data) * image->height * image->width))) {
        for (row = 0; row < image->height; row++)
            for (col = 0; col < image->width; col++) {
                value = getc(image_r);
                image->data[(row * image->width) + col] = value;
            } 
    } else emit_error (image, params, "Falha na alocação de memória para o data da imagem!\n");

    fclose (image_r);
}

void read_image (image_f *image, params_f *params, char *param[]) {
    FILE *image_r;

    fprintf(stdout, YELLOW "[PROCESSANDO] "  NC "Lendo a imagem enviada...\n\n");

    /* verifica se vai carregar a imagem do parametro ou do stdin */
    if (params->input != 0) {
        if (! (image_r = fopen(param[params->input], "r")))
            emit_error (image, params, "A imagem enviada é invalida");
    } else image_r = stdin;

    /* Pegando o type da PMG */
    fgets (image->type, sizeof (image->type), image_r);

    /* verifica se o arquivo enviado é de um tipo permitido */
    if (strcmp (image->type, "P2") && strcmp (image->type, "P5")) {
        fclose (image_r);
        emit_error (image, params, "O tipo de imagem não é compátivel!");
    }

    while (getc(image_r) != '\n'); /* Vai até o fim da linha */
    while (getc(image_r) == '#') { /* Pula os comentarios */
        while (getc(image_r) != '\n'); /* Vai até o fim da linha */
    }
    fseek (image_r, -1, SEEK_CUR); /* volta um caracter para traz */
    /* armazena as informações da estrutura da pgm */
    fscanf (image_r, "%d", &image->width);
    fscanf (image_r, "%d", &image->height);
    fscanf (image_r, "%d", &image->max_value);
    
    if (! strcmp (image->type, "P2")) 
        read_p2_file (image, params, image_r);
    else read_p5_file (image, params, image_r);
}

void send_image (image_f *image, params_f *params, char *param[]) {
    int row, col;
    FILE *new_image;

    fprintf (stdout, YELLOW "[PROCESSANDO] "  NC "Gravando a imagem resultante...\n\n");

    /* abre um arquivo para escrita */
    if (! (new_image = fopen(param[params->output], "w")))
        emit_error (image, params, "A imagem enviada é invalida");

    /* adiciona os valores de configuração */
    fprintf (new_image, "%s\n", image->type);
    fprintf (new_image, "%d %d\n", image->width, image->height);
    fprintf (new_image, "%d\n", image->max_value);

    /* grava o novo image data */
    if (! strcmp (image->type, "P2")) {
        for (row = 0; row < image->height; row++) {
            for (col = 0; col < image->width; col++) 
                fprintf (new_image, "%d ", image->data[(row * image->width) + col]);
        }
    } else {
        for (row = 0; row < image->height; row++) {
            for (col = 0; col < image->width; col++) 
                putc (image->data[(row * image->width) + col], new_image);
        }
    }
    fprintf (new_image, "\n");

    fprintf(stdout, GREEN "[SUCESSO] "  NC "Gravando efetuada com sucesso!\n\n");
    fclose (new_image);
}