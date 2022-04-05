#ifndef HASH_H
#define HASH_H

#define M 11

void inicialize_hash_table (int hash[][M]);

int hash_search (int key, int t1[][M], int t2[][M]);

void hash_insert (int key, int t1[][M], int t2[][M]);

void hash_delete (int key, int t1[][M], int t2[][M]);

void hash_print (int key, int t1[][M], int t2[][M]);
#endif