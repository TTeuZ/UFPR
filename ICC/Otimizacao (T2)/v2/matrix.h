#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <math.h>
#include <float.h>
#include <string.h>

#include "constants.h"
#include "parser.h"

#define ALING_SIZE 64

// Estrutura de dados para a Matriz
typedef struct {
  double **coef; // coeficientes
  unsigned int n; // tamanho do Matriz
} matrix_t;

/*!
    \brief Aloca dinamicamente uma Matriz
    \param n Tamanho da Matriz
    \return Ponteiro de acesso para a Matriz em caso de sucesso. Null em caso de erro
*/
matrix_t *alloc_matrix (unsigned int n);

/*!
    \brief Função de limpeza de memoria para uma Matriz
    \param matrix* Ponteiro para uma Matriz
*/
void free_matrix (matrix_t *matrix);

/*!
    \brief Função que realiza uma copia da matrix font para a target
    \param font* Ponteiro para uma Matriz fonte, que terá seus valores copiados
    \param target* Ponteiro para uma Matriz destino
*/
void copy_matrix (matrix_t *restrict font, matrix_t *restrict target);

/*!
    \brief Inicializa um Matriz com valores aleatórios
    \param matrix* Ponteiro para um Matriz,
    \param coef_max Maior valor para coeficientes
*/
void random_matrix (matrix_t *matrix, double coef_max);

/*!
    \brief Preenche uma Matriz com a Matriz identidade
    \param matrix* Ponteiro para uma Matriz,
*/
void generate_identity_matrix (matrix_t *matrix);

/*!
    \brief Função que realiza a leitura da Matriz apartir um arquivo (txt)
    \param parser Ponteiro de acesso para a estrutura do parser
    \return Ponteiro de acesso para a estrutura alocada para a Matriz em caso de sucesso. Null em caso de erro
*/
matrix_t* read_from_file (parser_t *parser);

/*!
    \brief Função que realiza a leitura da Matriz inviada pelo input padrão (Terminal)
    \return Ponteiro de acesso para a estrutura alocada para a Matriz em caso de sucesso. Null em caso de erro
*/
matrix_t* read_from_terminal ();

/*!
    \brief função de print do resultado da Matriz inversa
    \param inv_matrix Ponteiro para a matrix inversa
    \param norma_vet Ponteiro para o vetor com as normas calculadas
    \param lu_time Tempo para a fatoração LU
    \param iter_time Tempo médio para calcular as retrosubstituições
    \param residue_time Tempo médio para cálculo do resíduo
    \param parser Ponteiro para o parser
*/
int print_result (matrix_t *inv_matrix, double *norma_vet, double lu_time, double iter_time, double residue_time, parser_t *parser);
#endif