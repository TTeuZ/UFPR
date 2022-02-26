#include "entities.h"

/*
* Função que faz a leitura e constroi o imagem que vai ser utilizada no filtro
*/
image_f *read_image (params_f *params, char *param[]);

/*
* Função que retorna a nova imagem construida para o output
*/
void send_image (image_f *image, params_f *params, char *param[]);