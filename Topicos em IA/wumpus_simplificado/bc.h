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

#ifndef _BC_
#define _BC_

#define MAX_LIT 5      // no máximo 5 literais por cláusula

#define SAT_SOLVER "./minisat"   // comandos do SAT solver
#define ARQ_IN     "tmp.cnf"
#define ARQ_OUT    "tmp.out"

typedef struct {
  int literais[MAX_LIT];
  int n_lit;
} Clausula;

typedef struct {
  int n_vars;
  int n_claus;
  Clausula *clausulas;
} BaseCon;

// Aloca memória para a Base de Conhecimento e a retorna
// parâmetros: números máximos de cláusulas e de variáveis na BC
BaseCon *cria_BaseCon(int MAX_claus, int MAX_vars);

// informa nova cláusula alfa à BC
void TELL(Clausula alfa, BaseCon *BC);

// devolve 1 se clausula alfa é consequência lógica da BC
int ASK(Clausula alfa, BaseCon *BC);

#endif
