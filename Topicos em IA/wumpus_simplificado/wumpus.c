/***********************************************************************
 * Implementação de um protótipo de agente inteligente para o
 * o Mundo de Wumpus Simplificado.
 *
 * Tópicos em Inteligência Artificial
 *
 * Autor: prof. Guilherme Derenievicz
 * Departamento de Informática - UFPR
 *
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bc.h"
#include "wumpus-simplificado.h"
#include "agente-wumpus.h"

// Comentários:
// 1 - um algoritmo exponencial para SAT é chamado a cada 
//     passo de outro algoritmo exponencial (enumeração de 
//     todos os caminhos possíveis);
// 2 - únicas podas na árvore de busca quando ASK(BC) retorna
//     que não é seguro seguir por aquele caminho;
// 3 - dependendo do mapa o algoritmo não é completo, pois 
//     nunca arrisca um caminho que pode ter poço.

int main() {
  
  Mapa *map = cria_Mapa();

  // Cinco cláusulas para cada regra que relaciona Brisa com Poço,
  // e no máximo uma cláusula para cada Poço.
  // No máximo 2 variáveis para cada posição (tem Poço e tem Brisa)
  BaseCon *BC = cria_BaseCon(6*(map->n)*(map->n), 2*(map->n)*(map->n));

  popula_BaseCon(BC, map->n);

  // Um caminho pode passar por todo o mapa
  Ponto *caminho = (Ponto *) malloc(sizeof(Ponto)*(map->n * map->n + 1));

  // ponto inicial
  int tam_caminho = 0;
  Ponto p = {0,0};
  caminho[tam_caminho++] = p;
 
  busca(map, BC, caminho, tam_caminho);
}

