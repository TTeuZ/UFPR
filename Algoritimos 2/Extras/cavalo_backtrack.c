#include <stdio.h>

#define N 5

/* imprime a solução */
void print_solution (int sol[N][N]) {
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) 
            printf(" %2d ", sol[x][y]);
        printf("\n");
    }
}

/* verifica se a proxima casa é segura para ir, ou seja, não esta fora dos limites e já não foi ocupada */
int is_safe (int sol[N][N], int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && sol[x][y] == -1);
    
}

/* Busca por meio do backtrack a solução para o problema */
int solve_kt_util (int x, int y, int movei, int sol[N][N], int xMove[], int yMove[]) {
    if (movei == N*N) return 1; /* se o movei chegou no tamanho do quadrado retorna que achou */
    for (int count = 0; count < 8; count++) {
        int next_x = x + xMove[count]; /* pega a proxima posição de x */
        int next_y = y + yMove[count]; /* pega a proxima posicao de y */
        if (is_safe (sol, next_x, next_y)) { /* se puder avançar, seta o prox movei e chama recursivamente */
            sol[next_x][next_y] = movei;
            if (solve_kt_util (next_x, next_y, movei+1, sol, xMove, yMove))
                return 1; /* se encontrou a solução retorna 1 */
            else 
                sol[next_x][next_y] = -1; /* se nçao encontrou solução, vai voltando e marcando as casas com -1 (não passou) */
        }
    }
    return 0; /* se ficou empacado, retorna 0 */
}

/* inicializa a variaveis necessarias */
void solvekt () {
    int sol[N][N];

    /* inicializacao da matrix */
    for (int x = 0; x < N; x++) 
        for (int y = 0; y < N; y++)
            sol[x][y] = -1;

    sol[0][0] = 0; /* posicao inicial do cavalo. */
    int xMove[8] = {2, 1, -1, -2, -2, -1, 1, 2}; /* posivel posição x que o cavalo pode assumir */
    int yMove[8] = {1, 2, 2, 1, -1, -2, -2, -1}; /* posivel posição y que o cavalo pode assumir */

    /* Se encontrar uma solução, imprime ela. */
    if (solve_kt_util (0, 0, 1, sol, xMove, yMove))
        print_solution(sol);
    else
        printf("Solução não existe!\n");
}

void main () {
    solvekt ();
}