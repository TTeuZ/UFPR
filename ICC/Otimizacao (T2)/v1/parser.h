#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "constants.h"

typedef struct parser {
    char *input;
    char *output;
    int n;
    int iterations;
} parser_t;

/*!
    \brief Função de alocação/inicialização dos valores do parser
    \return Ponteiro de acesso para a estrutura de dados parser
*/
parser_t *init_parser ();

/*!
    \brief Função parser da linha de comando
    varre os parametros de entrada e armazena na estrutura de dados
    \param parser Estrutura de dados previamente alocadas
    \param arqc numero de argumentos da entrada
    \param arqv array com os argumentos da entrada
    \return 0 em caso de sucesso. MISSING_REQUIRED_ARG_ERROR em caso de falha
*/
int parse_input (parser_t *parser, int argc, char *argv[]);
#endif