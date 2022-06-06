#include "entities.h"
/*
* Função padrao para exibição de erros
* Internamente exibe a mensagem de erro no terminal, limpa as structs alocadas
* e encerra a execução do sistema.
*/
void emit_error (image_f *image, params_f *params, char *message);

/*
* Limpa todos os espaços de memoria alocados feitos durante a execução do filtro.
*/
void clean_structs (image_f *image, params_f *params);

/*
* Inicializa a struct da imagem utilizada no filtro
* Possui todos os parametros necessarios para inicializar a imagem com suas informçãoes e tamnho alocados.
* Recebe o params como parametro apenas para caso de erro no malloc, poder limpar as estruturas já alocadas
*/
image_f *initialize_image (char *type, int height, int width, int max_value, params_f *params);

/*
* Inicializa a struct dos parametros do filtro.
* Seus valores começam em 0 e -1 para o ex_param.
* Os valores serão preenchidos pela função parser.
*/
params_f *initialize_params ();

/*
* Função que ajusta os parametros enviados na linha de comando do filtro
* dentro da função é verificado se a entrada/saida padrão foram enviadas
* dentro da função verificamos se todos os parametros foram enviados e armazenamos as chaves de acesso a seus valores.
*/
void treat_params (params_f *params, char *extra_param, int need_extra, char *param[], int qtd);