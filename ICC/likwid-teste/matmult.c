#include <stdio.h>
#include <stdlib.h>    /* exit, malloc, calloc, etc. */
#include <string.h>
#include <getopt.h>    /* getopt */
#include <time.h>

#include "matriz.h"

/**
 * Exibe mensagem de erro indicando forma de uso do programa e termina
 * o programa.
 */

static void usage(char *progname)
{
  fprintf(stderr, "Forma de uso: %s [ -n <ordem> ] \n", progname);
  exit(1);
}



/**
 * Programa principal
 * Forma de uso: matmult [ -n <ordem> ]
 * -n <ordem>: ordem da matriz quadrada e dos vetores
 *
 */

int main (int argc, char *argv[]) 
{
  int c, n=DEF_SIZE;
  
  MatPtr mPtr_1, mPtr_2, resMatPtr;
  MatPtr mPtrRow_1, mPtrRow_2, resMatPtrRow;
  MatRow mRow_1, mRow_2, resMatRow;
  Vetor vet, resPtr, resPtrRow, resRow;
  
  /* =============== TRATAMENTO DE LINHA DE COMANDO =============== */

  char *opts = "n:";
  c = getopt (argc, argv, opts);
  
  while ( c != -1 ) {
    switch (c) {
    case 'n':  n = atoi(optarg);              break;
    default:   usage(argv[0]);
    }
      
    c = getopt (argc, argv, opts);
  }
  
  /* ================ FIM DO TRATAMENTO DE LINHA DE COMANDO ========= */
 
  // srand(time(NULL));
  srand(20212);
      
  resPtr = (double *) calloc (n, sizeof(double));
  resPtrRow = (double *) calloc (n, sizeof(double));
  resRow = (double *) calloc (n, sizeof(double));
  resMatPtr = geraMatPtr(n, n, 1);
  resMatPtrRow = geraMatPtrRow(n, n, 1);
  resMatRow = geraMatRow(n, n, 1);
    
  mPtr_1 = geraMatPtr (n, n, 0);
  mPtr_2 = geraMatPtr (n, n, 0);

  mPtrRow_1 = geraMatPtrRow (n, n, 0);
  mPtrRow_2 = geraMatPtrRow (n, n, 0);

  mRow_1 = geraMatRow (n, n, 0);
  mRow_2 = geraMatRow (n, n, 0);

  vet = geraVetor (n, 0);

#ifdef DEBUG
    prnMatPtr (mPtr_1, n, n);
    prnMatPtr (mPtr_2, n, n);
    prnMatPtr (mPtrRow_1, n, n);
    prnMatPtr (mPtrRow_2, n, n);
    prnMatRow (mRow_1, n, n);
    prnMatRow (mRow_2, n, n);
    prnVetor (vet, n);
    printf ("=================================\n\n");
#endif /* DEBUG */

  multMatPtrVet (mPtr_1, vet, n, n, resPtr);

  multMatPtrVet (mPtrRow_1, vet, n, n, resPtrRow);
    
  multMatRowVet (mRow_1, vet, n, n, resRow);
    
  multMatMatPtr (mPtr_1, mPtr_2, n, resMatPtr);

  multMatMatPtr (mPtrRow_1, mPtrRow_2, n, resMatPtrRow);
    
  multMatMatRow (mRow_1, mRow_2, n, resMatRow);
    
#ifdef DEBUG
    prnVetor (resPtr, n);
    prnVetor (resPtrRow, n);
    prnVetor (resRow, n);
    prnMatRow (resMatRow, n, n);
    prnMatPtr (resMatPtr, n, n);
    prnMatPtr (resMatPtrRow, n, n);
#endif /* DEBUG */

  liberaMatPtr (mPtr_1, n);
  liberaMatPtr (mPtr_2, n);
  liberaMatPtrRow (mPtrRow_1, n);
  liberaMatPtrRow (mPtrRow_2, n);
  liberaMatPtr (resMatPtr, n);
  liberaMatPtrRow (resMatPtrRow, n);
  liberaVetor ((void*)mRow_1);
  liberaVetor ((void*)mRow_2);
  liberaVetor ((void*)resMatRow);
  liberaVetor ((void*)vet);
    
  free(resRow);
  free(resPtr);
  free(resPtrRow);

  return 0;
}

