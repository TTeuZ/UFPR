#include <dirent.h>
#include "bicycles.h"
#include "bicycle.h"

#ifndef READER
#define READER

/*
*   Função que faz a leitura dos arquivos .log dentro do diretorio
*   Para cada log, executa a rotina de leitura e adição no array
*/
int read_directory (char *dir_name, bicycles_f *bicycles);

/*
*   Função que realiza a leitura de um arquivo de log
*   Ao fazer a leitura, armazena as informações relevantes do log em variaveis internas
*   Apos a finalização da leitura, retorna o objeto de log gerado
*/
bicycle_log_f *read_log (char *log_path, char *log_name);
#endif