#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hash.h"

int h1 (int key) {
    return key % M;
}

int h2 (int key) {
    return floor (M * (key * 0.9 - floor (key * 0.9)));
}

void inicialize_hash_table (int hash[][M]) {
    int count;
    for (count = 0; count <= M; count++) {
        hash[count][0] = -1;
    }
}

int hash_search (int key, int t1[][M], int t2[][M]) {
    int pos = h1 (key);

    if (t1[pos][0] != -1) {
        if (t1[pos][0] != key)
            pos = h2 (key);
        return pos;
    } else return -1;
}

void hash_insert (int key, int t1[][M], int t2[][M]) {
    int pos_t1, pos_t2, old_key;
    pos_t1 = h1 (key);

    if (! (t1[pos_t1][0] == -1 || t1[pos_t1][0] == -2))  {
        old_key = t1[pos_t1][0];
        pos_t2 = h2 (old_key);
        t2[pos_t2][0] = old_key;
    }
    t1[pos_t1][0] = key;
}

void hash_delete (int key, int t1[][M], int t2[][M]) {
    int pos = h2 (key);

    if (t2[pos][0] != key) {
        pos = h1 (key);
        t1[pos][0] = -2;
    } else 
        t2[pos][0] = -1;
}

void hash_print (int key, int t1[][M], int t2[][M]) {
    int count = 0;

    printf("T1: ");
    for (count = 0; count < M; count++) {
        printf(" %d ", t1[count][0]);
    }
    printf("\n");

    printf("T2: ");
    for (count = 0; count < M; count++) {
        printf(" %d ", t2[count][0]);
    }
    printf("\n");
}