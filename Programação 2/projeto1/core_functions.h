#include "entities.h"
/*
* Função pardrao para exibição de erros
*/
void emit_error (image_f *image, params_f *params, char *message);

/*
* Limpa todos os malocs feitos durante a execução do filtro.
*/
void clean_structs (image_f *image, params_f *params);

/*
* Inicializa a struct da imagem utilizada no filtro
*/
image_f *initialize_image (char *type, int height, int width, int max_value, params_f *params);

/*
* Inicializa a struct dos parametros do filtro.
* Recebe image como parametro apenas para caso de erro no malloc, poder limpar as estruturas já alocadas
*/
params_f *initialize_params ();

/*
* Função que ajusta os parametros enviados enviados na chamada do filtro
* Imagem é enviada para caso de falha nos parametros, poder limpar as estruturas
*/
void treat_params (params_f *params, char *extra_param, int need_extra, char *param[], int qtd);