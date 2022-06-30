#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "sislin.h"
#include "Metodos.h"

#define TEST_SIZE 9

int main ()
{
  // inicializa gerador de números aleatóreos
  srand(202201);
  int sizes[TEST_SIZE] = {10, 30, 50, 128, 256, 512, 1000, 2000, 3000};
  int count;
  double time_vet_egp, time_vet_gs, time_vet_ref, time_pont_egp, time_pont_gs, time_pont_ref;
  int it_vet_gs, it_vet_ref, it_pont_gs, it_pont_ref;
  real_t *solVet, *solPont;
  SistLinear_t *s_vet, *s_pont;
  
  // loop de execução dos testes para diagDominante
  for (count = 0; count < 1; count++) {
    s_vet = alocaSisLin (sizes[count], pontVet);
    s_pont = alocaSisLin (sizes[count], pontPont);

    /* verificação se a alocação ocorreu certo */
    if (s_vet == NULL) {
      fprintf (stderr, "Erro de alocação para o tipo pontVet!\n");
    } else {
      iniSisLin (s_vet, diagDominante, COEF_MAX);
      /* verificação da alocação do vetor de resultados */
      if (! (solVet = malloc (sizeof (real_t) * sizes[count]))) {
        fprintf (stderr, "Erro de alocação para o vetor de resultados do tipo pontVet!\n");
        liberaSisLin (s_vet);
      } else {
        /* aplicação da eliminação de gauss */
        eliminacaoGauss (s_vet, solVet, &time_vet_egp);
        printf ("total de gauss para vet dominante: %f\n", time_vet_egp);

        liberaSisLin (s_vet);
      }
    }

    /* verificação se a alocação ocorreu certo */
    if (s_pont == NULL) {
      fprintf (stderr, "Eror de alocação para o tipo pontPont!\n");
    } else {
      iniSisLin (s_pont, diagDominante, COEF_MAX);
      /* verificação da alocação do vetor de resultados */
      if (! (solPont = malloc (sizeof (real_t) * sizes[count]))) {
        fprintf (stderr, "Erro de alocação para o vetor de resultados do tipo pontPont!\n");
        liberaSisLin (s_pont);
      } else {
        /* aplicação da eliminação de gauss */
        eliminacaoGauss (s_pont, solPont, &time_pont_egp);
        printf ("total de gauss para pont dominante: %f\n", time_pont_egp);


        liberaSisLin (s_pont);
      }
    }
  } 

  // loop de execução dos testes para hilbert
  for (count = 0; count < 1; count++) {
    s_vet = alocaSisLin (sizes[count], pontVet);
    s_pont = alocaSisLin (sizes[count], pontPont);

    /* verificação se a alocação ocorreu certo */
    if (s_vet == NULL) {
      fprintf (stderr, "Erro de alocação para o tipo pontVet!\n");
    } else {
      iniSisLin (s_vet, hilbert, COEF_MAX);
      /* verificação da alocação do vetor de resultados */
      if (! (solVet = malloc (sizeof (real_t) * sizes[count]))) {
        fprintf (stderr, "Erro de alocação para o vetor de resultados do tipo pontVet!\n");
        liberaSisLin (s_vet);
      } else {
        /* aplicação da eliminação de gauss */
        eliminacaoGauss (s_vet, solVet, &time_vet_egp);
        printf ("total de gauss para vet hilbert: %f\n", time_vet_egp);

        liberaSisLin (s_vet);
      }
    }

    /* verificação se a alocação ocorreu certo */
    if (s_pont == NULL) {
      fprintf (stderr, "Eror de alocação para o tipo pontPont!\n");
    } else {
      iniSisLin (s_pont, hilbert, COEF_MAX);
      /* verificação da alocação do vetor de resultados */
      if (! (solPont = malloc (sizeof (real_t) * sizes[count]))) {
        fprintf (stderr, "Erro de alocação para o vetor de resultados do tipo pontPont!\n");
        liberaSisLin (s_pont);
      } else {
        /* aplicação da eliminação de gauss */
        eliminacaoGauss (s_pont, solPont, &time_pont_egp);
        printf ("total de gauss para pont hilbert: %f\n", time_pont_egp);


        liberaSisLin (s_pont);
      }
    }
  }
}

