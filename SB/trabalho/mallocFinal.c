#include <stdio.h>
#include <unistd.h>
#include <limits.h>

// Teve que usar o sbrk pq de acordo com o man, não da para fazer o que queremos com o brk

void* topoInicialHeap;
void* topoAtualHeap;

void iniciaAlocador() {
    topoInicialHeap = topoAtualHeap = sbrk(0);
}

void finalizarAlocador() {
    brk(topoInicialHeap);
}

int liberaMen(void* bloco) {
    *(int*)(bloco - 16) = 0;
    return 0;
}

void* alocaMen(int num_bytes) {
    void* temp, * iterator, * freeSpace;
    int bytesQtd, diff;

    freeSpace = NULL;
    bytesQtd = INT_MAX;

    iterator = topoInicialHeap;
    while (iterator < topoAtualHeap) {
        if (*(int*)iterator == 0) {
            iterator = iterator + 8;
            if (*(int*)iterator >= num_bytes && *(int*)iterator <= bytesQtd) {
                bytesQtd = *(int*)iterator;
                iterator = iterator + 8;
                freeSpace = iterator;
            } else iterator = iterator + 8;
        } else iterator = iterator + 16;

        iterator = iterator + *(int*)(iterator - 8);
    }

    if (freeSpace == NULL) {

        temp = sbrk(0);
        diff = temp - topoAtualHeap;
        if (diff < num_bytes)
            sbrk((1 + (num_bytes / 4096)) * 4096);


        temp = topoAtualHeap;
        *(int*)temp = 1;

        temp = temp + 8;
        *(int*)temp = num_bytes;
        temp = temp + 8;

        topoAtualHeap = temp + num_bytes;
    } else {

        *(int*)(freeSpace - 16) = 1;
        temp = freeSpace;
    }

    return temp;
}

int main()
{
    printf("\n");
    iniciaAlocador();
    long int* new_mem = alocaMen(8);
    printf("\n");
    long int* new_mem2 = alocaMen(16);
    printf("\n");
    long int* new_mem3 = alocaMen(32);
    printf("\n");
    long int* new_mem4 = alocaMen(12);
    printf("\n");

    liberaMen(new_mem2);
    liberaMen(new_mem4);

    long int* reused_mem = alocaMen(10);
    long int* reused_mem2 = alocaMen(15);
    long int* new_mem5 = alocaMen(3948);
    long int* new_mem6 = alocaMen(8);

    finalizarAlocador();
    return 0;
}