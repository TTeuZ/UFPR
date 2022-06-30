#include <stdio.h>
#include <stdlib.h>

void flush_stdin () {
    int buf = 0;
    while (buf != '\n' && buf != EOF) 
        buf = getchar(); 
}

void wait_exit () {
    int exit = 1;
    fprintf (stdout, "\nAperte 0 para sair: ");
    while (exit != 0) {
        scanf ("%d", &exit);
        flush_stdin ();
    }
}
