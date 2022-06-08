#include <dirent.h>

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

// Funçãoq ue le o arquivo e envia as informações pro lugar necessario
// função que limpa o espaço dos arquivos lidos

#endif