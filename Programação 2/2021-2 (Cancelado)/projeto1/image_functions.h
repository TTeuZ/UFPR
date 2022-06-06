#include "entities.h"

/*
* Função que faz a leitura e constroi o imagem que vai ser utilizada no filtro
* Dentro da função é verificado o tipo de imagem e chamado a função especifica de preenchimento da matriz
*/
image_f *read_image (params_f *params, char *param[]);

/*
* Função que retorna a nova imagem construida para o output
*/
void send_image (image_f *image, params_f *params, char *param[]);