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
#include "bc.h"
#include "wumpus-simplificado.h"

#ifndef _AGENTE_WUMPUS_
#define _AGENTE_WUMPUS_

// Índices de variáveis para o SAT solver:
// Considerando um mapa n x n,
// x1, x2, ..., xm: variáveis que representam se tem Brisa, onde m = n*n
// xm+1, xm+2, ..., xl: variáveis que representam se tem Poço, onde l = 2*n*n

#define B(x,y,n) ((x)*(n)+(y)+1)        // tem Brisa na posição (x,y) do mapa de tamanho n
#define P(x,y,n) ((n)*(n)+(x)*n+(y)+1)  // tem Poço  na posição (x,y) do mapa de tamanho n

// insere as regras do jogo na BC.
// É necessário saber apenas o tamanho do mapa
void popula_BaseCon(BaseCon *BC, int tam_mapa);

// busca exaustiva para encontrar caminho até o Ouro, usando
// a BC para percorrer apenas posições seguras.
// O parâmetro 'caminho' deve conter o caminho parcial já percorrido,
// sendo inicializado com a posição inicial (0,0).
void busca(Mapa *map, BaseCon *BC, Ponto *caminho, int tam_caminho);

// verifica se o ponto p já foi percorrido no caminho atual
int pertence(Ponto p, Ponto *caminho, int tam_caminho);

// verifica se o ponto p é seguro e promissor (não forma ciclo)
int ponto_seguro(Ponto p, Ponto *caminho, int tam_caminho, int tam_mapa, BaseCon *BC);

#endif
