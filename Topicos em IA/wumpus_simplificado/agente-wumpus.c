/***********************************************************************
 * Implementação de um protótipo de agente inteligente para o
 * o Mundo de Wumpus Simplificado.
 *
 * Tópicos em Inteligência Artificial
 *
 * Autor: prof. Guilherme Derenievicz
 * Departamento de Informática - UFPR
 *
 * Arquivo agente-wumpus: agente para resolver o Mundo de Wumpus Simplificado
 *                        usando busca exaustiva e uma base de conhecimento CNF
 *                        para percorrer apenas posições seguras.
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agente-wumpus.h"

// insere as regras do jogo na BC.
// É necessário saber apenas o tamanho do mapa
void popula_BaseCon(BaseCon *BC, int tam_mapa) {
  
  // única regra do Mundo de Wumpus Simplificado:
  // B(i,j) <=> P(i-1,j) v P(i+1,j) v P(i,j-1) v P(i,j+1)

  for (int i = 0; i < tam_mapa; ++i)
    for (int j = 0; j < tam_mapa; ++j) {
      // B(i,j) => (P(i-1,j) v P(i+1,j) v P(i,j-1) v P(i,j+1))
      int l = 0;
      Clausula alfa;
      alfa.literais[l++] = -B(i,j,tam_mapa);
      if (i > 0)
        alfa.literais[l++] = P(i-1,j,tam_mapa);
      if (i < tam_mapa-1)
        alfa.literais[l++] = P(i+1,j,tam_mapa);
      if (j > 0)
        alfa.literais[l++] = P(i,j-1,tam_mapa);
      if (j < tam_mapa-1)
        alfa.literais[l++] = P(i,j+1,tam_mapa);
      alfa.n_lit = l;
      TELL(alfa, BC);
      
      // (P(i-1,j) v P(i+1,j) v P(i,j-1) v P(i,j+1)) => B(i,j)
      if (i > 0) {
        alfa.literais[0] = B(i,j,tam_mapa);
        alfa.literais[1] = -P(i-1,j,tam_mapa);
        alfa.n_lit = 2;
        TELL(alfa, BC);
      }
      if (i < tam_mapa-1) {
        alfa.literais[0] = B(i,j,tam_mapa);
        alfa.literais[1] = -P(i+1,j,tam_mapa);
        alfa.n_lit = 2;
        TELL(alfa, BC);
      }
      if (j > 0) {
        alfa.literais[0] = B(i,j,tam_mapa);
        alfa.literais[1] = -P(i,j-1,tam_mapa);
        alfa.n_lit = 2;
        TELL(alfa, BC);
      }
      if (j < tam_mapa-1) {
        alfa.literais[0] = B(i,j,tam_mapa);
        alfa.literais[1] = -P(i,j+1,tam_mapa);
        alfa.n_lit = 2;
        TELL(alfa, BC);
      }
    }
}

// busca exaustiva para encontrar caminho até o Ouro, usando
// a BC para percorrer apenas posições seguras.
// O parâmetro 'caminho' deve conter o caminho parcial já percorrido,
// sendo inicializado com a posição inicial (0,0).
void busca(Mapa *map, BaseCon *BC, Ponto *caminho, int tam_caminho) {
  
  imprime_Mapa(map, caminho, tam_caminho);

  Ponto p = caminho[tam_caminho-1];
  int percep = percepcao(p, map);

  if (percep == BRISA) {
    Clausula alfa;
    alfa.literais[0] = B(p.x,p.y,map->n);
    alfa.n_lit = 1;
    TELL(alfa, BC);
  }
  else if (percep == VAZIO) {
    Clausula alfa;
    alfa.literais[0] = -B(p.x,p.y,map->n);
    alfa.n_lit = 1;
    TELL(alfa, BC);
  }

  if (p.x > 0) {
    Ponto prox = {p.x-1, p.y};
    if (ponto_seguro(prox, caminho, tam_caminho, map->n, BC)) {
      caminho[tam_caminho] = prox;
      busca(map, BC, caminho, tam_caminho+1);
    }
  }
  if (p.x < map->n-1) {
    Ponto prox = {p.x+1, p.y};
    if (ponto_seguro(prox, caminho, tam_caminho, map->n, BC)) {
      caminho[tam_caminho] = prox;
      busca(map, BC, caminho, tam_caminho+1);
    }
  }
  if (p.y > 0) {
    Ponto prox = {p.x, p.y-1};
    if (ponto_seguro(prox, caminho, tam_caminho, map->n, BC)) {
      caminho[tam_caminho] = prox;
      busca(map, BC, caminho, tam_caminho+1);
    }
  }
  if (p.y < map->n-1) {
    Ponto prox = {p.x, p.y+1};
    if (ponto_seguro(prox, caminho, tam_caminho, map->n, BC)) {
      caminho[tam_caminho] = prox;
      busca(map, BC, caminho, tam_caminho+1);
    }
  }
}

// verifica se o ponto p já foi percorrido no caminho atual
int pertence(Ponto p, Ponto *caminho, int tam_caminho) {
  for (int i = 0; i < tam_caminho; ++i)
    if (p.x == caminho[i].x && p.y == caminho[i].y)
      return 1;
  return 0;
}

// verifica se o ponto p é seguro e promissor (não forma ciclo)
int ponto_seguro(Ponto p, Ponto *caminho, int tam_caminho, int tam_mapa, BaseCon *BC) {
  if (!pertence(p, caminho, tam_caminho)) {
    Clausula alfa;
    alfa.literais[0] = -P(p.x,p.y,tam_mapa);
    alfa.n_lit = 1;
    return ASK(alfa, BC);
  }
  return 0;
}

