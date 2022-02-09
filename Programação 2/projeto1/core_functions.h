#include "entities.h"

/*
* Função pardrao para exibição de erros
*/
void emit_error (char *message);

/*
* Limpa todos os malocs feitos durante a execução do filtro.
*/
void clean_structs (image_f *image, paramns_f *paramns);

/*
* Inicializa a struct da imagem utilizada no filtro (Não faz maloc para a matrix da imagem)
*/
image_f *initialize_image ();

/*
* Inicializa a struct dos parametros do filtro.
*/
paramns_f *initialize_paramns ();

/*
* Função que ajusta os parametros enviados enviados na chamada do filtro
*/
void treat_paramns (char *paramns[], int qtd, paramns_f *param);