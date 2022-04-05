#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

int main () {
    int t1[0][M], t2[0][M];
    char action;
    int key;

    inicialize_hash_table (t1);
    inicialize_hash_table (t2);

    /* busca a primeira ação e o primeiro valor do stdin */
    fscanf (stdin, "%c %d", &action, &key);
    getc (stdin);

      /* começa a executar até o arquivo acabar */
    while (! feof (stdin)) {
        /* seleciona e executa a ação indicada */
        if (action == 'i') 
            hash_insert (key, t1, t2);
        else if (hash_search (key, t1, t2) != -1) {
            hash_delete (key, t1, t2);
        }

        /* busca a proxima ação e valor do stdin */
        fscanf (stdin, "%c %d", &action, &key);
        getc (stdin);
    }

    hash_print (t1, t2);

    return 0;
}