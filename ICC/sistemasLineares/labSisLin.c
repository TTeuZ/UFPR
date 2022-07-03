#include <stdio.h>
#include <math.h>
#include <string.h>

#include "utils.h"
#include "sislin.h"
#include "Metodos.h"

#define TEST_SIZE 9

void printResult (int n, tipoAloc_t aloc, tipoSistLinear_t sisLin, double egp_time, double gs_time, double ref_time, int gs_ite, int ref_ite, int egp_error, int gs_error, int ref_error) {
  char s_aloc[20], s_sisLin[30];
  switch (aloc) {
    case pontVet: {
      strcpy (s_aloc, "pontVet");
      break;
    }
    case pontPont: {
      strcpy (s_aloc, "pontPont");
      break;
    }
  }
  switch (sisLin) {
    case hilbert: {
      strcpy (s_sisLin, "hilbert");
      break;
    }
    case diagDominante: {
      strcpy (s_sisLin, "diagDom");
      break;
    }
  }

  fprintf (stdout, "Tamanho\t\tAlocação\tTipo\t\tTempo EGP\tTempo GS\tIterações gs\tTempo REF\tIterações REF\n");
  fprintf (stdout, "%7d\t%16s\t%7s\t", n, s_aloc, s_sisLin);
  if (! egp_error) fprintf (stdout, "%17.6f\t", egp_time);
  else fprintf (stdout, "        ---------       ");
  if (! gs_error) fprintf (stdout, "%8.6f\t%12d\t", gs_time, gs_ite);
  else fprintf (stdout, "       --------\t------------\t");
  if (! ref_error) fprintf (stdout, "%9.6f\t%13d\n\n", ref_time, ref_ite);
  else fprintf (stdout, "---------\t -------------\t");
}

void printfErro (int n, char *metod, tipoAloc_t aloc, tipoSistLinear_t sisLin) {
  char s_aloc[20], s_sisLin[30];
  switch (aloc) {
    case pontVet: {
      strcpy (s_aloc, "pontVet");
      break;
    }
    case pontPont: {
      strcpy (s_aloc, "pontPont");
      break;
    }
  }
  switch (sisLin) {
    case hilbert: {
      strcpy (s_sisLin, "hilbert");
      break;
    }
    case diagDominante: {
      strcpy (s_sisLin, "diagDom");
      break;
    }
  }
  fprintf (stderr, "Erro de operaçôes - Infinito | NaN -- %s Tamanho: %d Aloc: %s Tipo: %s\n\n", metod, n, s_aloc, s_sisLin);
}


int main () {
  int sizes[TEST_SIZE] = {10, 30, 50, 128, 256, 512, 1000, 2000, 3000};
  int count, sol_count;
  // vetor de soluções e matrizes fonte
  SistLinear_t *vet_d, *pont_d, *vet_h, *pont_h, *sisLin;
  real_t *sol;
  // tempos
  double egp_time, gs_time, ref_time;
  // iterações
  int gs_ite, ref_ite;
  // Erros
  int egp_error, gs_error, ref_error;
  srand(202201);
  egp_error = gs_error = ref_error = 0;

  for (count = 0; count < TEST_SIZE; count++) {
    if ((vet_d = alocaSisLin (sizes[count], pontVet))) {
      iniSisLin (vet_d, diagDominante, COEF_MAX);
    } else fprintf (stderr, "Erro de alocação\n");

    if ((pont_d = alocaSisLin (sizes[count], pontPont))) {
      iniSisLin (pont_d, diagDominante, COEF_MAX);
    } else fprintf (stderr, "Erro de alocação\n");

    if ((vet_h = alocaSisLin (sizes[count], pontVet))) {
      iniSisLin (vet_h, hilbert, COEF_MAX);
    } else fprintf (stderr, "Erro de alocação\n");

    if ((pont_h = alocaSisLin (sizes[count], pontPont))) {
      iniSisLin (pont_h, hilbert, COEF_MAX);
    } else fprintf (stderr, "Erro de alocação\n");

    if ((sol = malloc (sizeof (real_t) * sizes[count]))) {
      if ((sisLin = alocaSisLin (sizes[count], pontVet))) {
        if (vet_d) {
          CpySisLin (vet_d, sisLin);
          if (eliminacaoGauss (sisLin, sol, &egp_time) == OPE_ERROR) 
            egp_error = 1;
          CpySisLin (vet_d, sisLin);
          for (sol_count = 0; sol_count < sizes[count]; sol_count++) 
            sol[sol_count] = 0;
          if ((gs_ite = gaussSeidel (sisLin, sol, ERRO, &gs_time)) == OPE_ERROR) 
            gs_error = 1;
          CpySisLin (vet_d, sisLin);
          if ((ref_ite = refinamento (sisLin, sol, ERRO, &ref_time)) == OPE_ERROR) 
            ref_error = 1;

          if (egp_error) printfErro (sizes[count], "EGP", pontVet, diagDominante);
          if (gs_error) printfErro (sizes[count], "GS", pontVet, diagDominante);
          if (ref_error) printfErro (sizes[count], "REF", pontVet, diagDominante);
          printResult (sizes[count], pontVet, diagDominante, egp_time, gs_time, ref_time, gs_ite, ref_ite, egp_error, gs_error, ref_error);
        }
        egp_error = gs_error = ref_error = 0;

        if (vet_h) {
          CpySisLin (vet_h, sisLin);
          if (eliminacaoGauss (sisLin, sol, &egp_time) == OPE_ERROR)
            egp_error = 1;
          CpySisLin (vet_h, sisLin);
          for (sol_count = 0; sol_count < sizes[count]; sol_count++) 
            sol[sol_count] = 0;
          if ((gs_ite = gaussSeidel (sisLin, sol, ERRO, &gs_time)) == OPE_ERROR)
            gs_error = 1;
          CpySisLin (vet_h, sisLin);
          if ((ref_ite = refinamento (sisLin, sol, ERRO, &ref_time)) == OPE_ERROR) 
            ref_error = 1;

          if (egp_error) printfErro (sizes[count], "EGP", pontVet, hilbert);
          if (gs_error) printfErro (sizes[count], "GS", pontVet, hilbert);
          if (ref_error) printfErro (sizes[count], "REF", pontVet, hilbert);
          printResult (sizes[count], pontVet, hilbert, egp_time, gs_time, ref_time, gs_ite, ref_ite, egp_error, gs_error, ref_error);
        }
        egp_error = gs_error = ref_error = 0;
      } else fprintf (stderr, "Erro de alocação\n");
      liberaSisLin (sisLin);

      if ((sisLin = alocaSisLin (sizes[count], pontPont))) {
        if (pont_d) {
          CpySisLin (pont_d, sisLin);
          if (eliminacaoGauss (sisLin, sol, &egp_time) == OPE_ERROR)
            egp_error = 1;
          CpySisLin (pont_d, sisLin);
          for (sol_count = 0; sol_count < sizes[count]; sol_count++) 
            sol[sol_count] = 0;
          if ((gs_ite = gaussSeidel (sisLin, sol, ERRO, &gs_time)) == OPE_ERROR)
            gs_error = 1;
          CpySisLin (pont_d, sisLin);
          if ((ref_ite = refinamento (sisLin, sol, ERRO, &ref_time)) == OPE_ERROR)
            ref_error = 1;

          if (egp_error) printfErro (sizes[count], "EGP", pontPont, diagDominante);
          if (gs_error) printfErro (sizes[count], "GS", pontPont, diagDominante);
          if (ref_error) printfErro (sizes[count], "REF", pontPont, diagDominante);
          printResult (sizes[count], pontPont, diagDominante, egp_time, gs_time, ref_time, gs_ite, ref_ite, egp_error, gs_error, ref_error);
        }
        egp_error = gs_error = ref_error = 0;

        if (pont_h) {
          CpySisLin (pont_h, sisLin);
          if (eliminacaoGauss (sisLin, sol, &egp_time) == OPE_ERROR)
            egp_error = 1;
          CpySisLin (pont_h, sisLin);
          for (sol_count = 0; sol_count < sizes[count]; sol_count++) 
            sol[sol_count] = 0;
          if ((gs_ite = gaussSeidel (sisLin, sol, ERRO, &gs_time)) == OPE_ERROR)
            gs_error = 1;
          CpySisLin (pont_h, sisLin);
          if ((ref_ite = refinamento (sisLin, sol, ERRO, &ref_time)) == OPE_ERROR)
            ref_error = 1;

          if (egp_error) printfErro (sizes[count], "EGP", pontPont, hilbert);
          if (gs_error) printfErro (sizes[count], "GS", pontPont, hilbert);
          if (ref_error) printfErro (sizes[count], "REF", pontPont, hilbert);
          printResult (sizes[count], pontPont, hilbert, egp_time, gs_time, ref_time, gs_ite, ref_ite, egp_error, gs_error, ref_error);
        }
        egp_error = gs_error = ref_error = 0;
      } else fprintf (stderr, "Erro de alocação\n");
      liberaSisLin (sisLin);

      fprintf(stdout, "=============================================================================================================================\n\n");
    } 
  }
  liberaSisLin (vet_d);
  liberaSisLin (pont_d);
  liberaSisLin (vet_h);
  liberaSisLin (pont_h);
  free (sol);
}