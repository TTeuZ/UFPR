#include <dirent.h>
#include "bicycles.h"

#ifndef READER
#define READER

typedef struct directory {
    int files_qtd;
    struct dirent **files;
} directory_f;

/* 
* Função que inicializa a estrutura de dados de armazenamento dos arquivos de log do diretorio
* Realiza a alocação inicial de espaço da propia estrutura e retorna o ponteiro de acesso
*/
directory_f *inicialize_directory ();

/*
* Função que inicializa uma estrutura de diretorio e faz a leitura dos arquivos .log dentro do diretorio
* Retorna um ponteiro para a estrutura que armazena o array de arquivos do diretorio e sua quantidade
*/
directory_f *get_logs (char *dir_name);

/*
* Função que recebe os logs carregados do diretorio e aplica a função de leitura para cada log
* Constroi o nome correto de acesso ao arquivo
* Limpa o espaço armazenado para os arquivos do diretorio conforme realiza a leitura
*/
void load_logs (directory_f *directory, char *dir_name, bicycles_f *bicycles);

/*
* Função que realiza a leitura de um arquivo de log
* Ao fazer a leitura, armazena as informações relevantes do log em variaveis internas
* Apos a finalização da leitura, chama a função de adição do arquivo de log no array de bicicletas
*/
void read_log (char *log_path, char *log_name, bicycles_f *bicycles);

/*
* Função que limpa o espaço armazenado pela estrutura de arquivos no diretorio
*/
void clean_directory (directory_f *directory);
#endif