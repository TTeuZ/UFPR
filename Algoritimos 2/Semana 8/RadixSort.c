#include <stdio.h>
/* Ordenar strings de mesmo tamanho */

/* 
v = vetor;
n = tamanho do vetor/
k = tamanho da string
 */
void radix_sort (int v[], int n, int k);

/*
    Utiliza o counting sort;
    basicamente vai passar por cada posição da string de todas as strings,
    e ordenar de acordo com o ultimo até o primeiro.

    Implemente usando um for na string e aplicando o counting_sort para cada etapa.

    Exemplo e melhor explicação no pdf da aula da semana.

*/