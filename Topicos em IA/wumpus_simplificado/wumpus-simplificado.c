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
#include "wumpus-simplificado.h"
#include <unistd.h>

// aloca memória e faz a leitura do mapa
Mapa *cria_Mapa() {
  int n;
  Mapa *map = (Mapa *) malloc(sizeof(Mapa));
  scanf("%d", &n);
  map->n = n;
  map->mat = (int **) malloc(sizeof(int *) * n);
  for (int i = 0; i < n; ++i) {
    map->mat[i] = (int *) malloc(sizeof(int) * n);
    for (int j = 0; j < n; ++j)
      scanf("%d", &(map->mat[i][j]));
  }
  return map;
}

void imprime_Mapa(Mapa *map, Ponto *caminho, int tam_caminho) {
#ifdef SHOW
  system("clear");
  usleep(SLEEP);
  for (int i = 0; i < map->n; ++i) {
    for (int j = 0; j < map->n; ++j) {
      int imprimiu = 0;
      for (int k = 0; k < tam_caminho-1 && !imprimiu; ++k)
        if (i == caminho[k].x && j == caminho[k].y) {
          printf("~ ");         // posições pelas quais passou neste caminho
          imprimiu = 1;
        }
      if (!imprimiu) {
        if (i == caminho[tam_caminho-1].x && j == caminho[tam_caminho-1].y)
          printf("# ");                         // posição atual
        else if (map->mat[i][j] == VAZIO)
          printf(". ");
        else if (map->mat[i][j] == BRISA)
          printf("* ");
        else if (map->mat[i][j] == POCO)
          printf("@ ");
        else if (map->mat[i][j] == OURO)
          printf("$ ");
      }
    }
    printf("\n");
  }
#endif
}

// percebe o que há na posição atual do mapa, dada
// pelo Ponto p.
int percepcao(Ponto p, Mapa *map) {
  int percep = map->mat[p.x][p.y];
  if (percep == POCO) {
    printf("PERDEU: caiu em um buraco!\n");
    exit(0);
  }
  if (percep == OURO) {
    printf("GANHOU: achou o ouro!\n");
    exit(0);
  }
  return percep;
}

