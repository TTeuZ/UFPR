#include "entities.h"

/*
* Função que ajusta os parametros enviados enviados na chamada do filtro
*/
void treat_paramns (char *paramns, int qtd);

/*
* Inicia as estruturas bases que vão ser usadas nos filtros
*/
void iniciate_filter (image *image, paramns paramns);

/*
* Função que faz a leitura e constroi o imagem que vai ser utilizada no filtro
*/
image read_image ();

/*
* Função que retorna a nova imagem construida para o output
*/
void send_image ();