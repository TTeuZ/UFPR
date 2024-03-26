/***********************************************************************
 * Implementação de um protótipo de agente inteligente para o
 * o Mundo de Wumpus Simplificado.
 *
 * Tópicos em Inteligência Artificial
 *
 * Autor: prof. Guilherme Derenievicz
 * Departamento de Informática - UFPR
 *
 * Arquivo bc: funções para manipulação da Base de Conhecimento em CNF,
 *             usando um SAT solver externo
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bc.h"

// Aloca memória para a Base de Conhecimento e a retorna
// parâmetros: números máximos de cláusulas e de variáveis na BC
BaseCon *cria_BaseCon(int MAX_claus, int MAX_vars) {
  BaseCon *BC = (BaseCon *) malloc(sizeof(BaseCon));
  BC->n_vars  = MAX_vars;   // TODO: SAT solver trabalha bem com mais variáveis que o necessário?
  BC->n_claus = 0;                              
  BC->clausulas = (Clausula *) malloc(sizeof(Clausula)*MAX_claus);
  return BC;
}

// informa nova cláusula alfa à BC
void TELL(Clausula alfa, BaseCon *BC) {
  int in = 0;                           // verifica se alfa já está na BC.
  for (int i = 0; i < BC->n_claus && !in; ++i) {
    int iguais = (BC->clausulas[i].n_lit == alfa.n_lit); 
    for (int j = 0; j < BC->clausulas[i].n_lit && iguais; ++j)
      if (BC->clausulas[i].literais[j] != alfa.literais[j])
        iguais = 0;
    if (iguais)
      in = 1;
  }
  if (!in) {
    memcpy(BC->clausulas[BC->n_claus].literais, alfa.literais, sizeof(int) * alfa.n_lit);
    BC->clausulas[BC->n_claus].n_lit = alfa.n_lit;
    BC->n_claus++;
  }
}

// devolve 1 se clausula alfa é consequência lógica da BC
int ASK(Clausula alfa, BaseCon *BC) {

  // BC |= alfa sse BC => alfa é válida, i.e., ~BC v alfa é válida
  // Ou ainda, ~(~BC v alfa) não é sat, i.e., BC ^ ~alfa não é sat
  // (prova por redução ao absurdo)
  
  // cria arquivo de entrada para o SAT solver
  FILE *f = fopen(ARQ_IN, "w+");
  fprintf(f, "p cnf %u %u\n", BC->n_vars, BC->n_claus+1);
  for (int i = 0; i < BC->n_claus; ++i) {
    for (int j = 0; j < BC->clausulas[i].n_lit; ++j)
      fprintf(f, "%d ", BC->clausulas[i].literais[j]);
    fprintf(f, "0\n");
  }
  // ~(alfa1 v ... v alfak) <=> (~alfa1) ^ ... ^ (~alfak)
  for (int j = 0; j < alfa.n_lit; ++j)
    fprintf(f, "%d 0\n", -alfa.literais[j]);
  fclose(f);

  // chama o SAT solver
  char comando[100];
  sprintf(comando, "%s %s %s > /dev/null 2> /dev/null", SAT_SOLVER, ARQ_IN, ARQ_OUT);
  if (system(comando) == -1) {
    printf("ERRO ao executar SAT Solver com comando %s\n", comando);
    exit(-1);
  }
  
  // processa saída
  f = fopen(ARQ_OUT, "r");
  char res[30];
  fscanf(f, "%s", res);
  fclose(f);
  return strcmp(res, "SAT"); // retorna 0 se for SAT, isto é, não é consequência lógica
}
