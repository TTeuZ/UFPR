#include <stdio.h>
int log_flow (int base, int n);

void main (int argc, char *argv[]) {
    int n;
    printf("Qual valor desejá saber o piso do log? \n");
    scanf ("%d", &n);
    printf("Log: %d \n", log_flow(1, n));
}

int log_flow (int base, int n) {
    if (base > n/2) return 0;
    else {
        base = base * 2;
        return log_flow(base, n) + 1;
    }
}