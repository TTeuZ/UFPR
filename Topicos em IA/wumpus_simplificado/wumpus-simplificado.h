/***********************************************************************
 * Implementação de um protótipo de agente inteligente para o
 * o Mundo de Wumpus Simplificado.
 *
 * Tópicos em Inteligência Artificial
 *
 * Autor: prof. Guilherme Derenievicz
 * Departamento de Informática - UFPR
 *
 * Arquivo wumpus-simplificado: funções básicas do jogo
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#ifndef _WUMPUS_SIMP_
#define _WUMPUS_SIMP_

#define VAZIO 0
#define BRISA 1
#define POCO  2
#define OURO  3

#define SLEEP 300000    // para impressão do mapa, em useg

typedef struct {
  int x;
  int y;
} Ponto;

typedef struct {
  int **mat;
  int n;
} Mapa;

Mapa *cria_Mapa();

void imprime_Mapa(Mapa *map, Ponto *caminho, int tam_caminho);

int percepcao(Ponto p, Mapa *map);

#endif
