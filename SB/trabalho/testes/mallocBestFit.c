#include <stdio.h>
#include <unistd.h>
#include <limits.h>

// Teve que usar o sbrk pq de acordo com o man, não da para fazer o que queremos com o brk

void* heapStart;

void startAllocator() {
    heapStart = sbrk(0);
}

void endAllocator() {
    brk(heapStart);
}

int freeMemory(void* block) {
    *(int*)(block - 16) = 0;
    return 0;
}

void* allocateMemory(int numBytes) {
    void* temp, * iterator;
    void* freeSpace;
    int bytesQtd;

    temp = sbrk(0);
    freeSpace = NULL;

    if (heapStart != temp) {
        iterator = heapStart;
        bytesQtd = INT_MAX;

        while (iterator < temp) {
            if (*(int*)iterator == 0) {
                iterator = iterator + 8;
                if (*(int*)iterator >= numBytes && *(int*)iterator <= bytesQtd) {
                    bytesQtd = *(int*)iterator;
                    iterator = iterator + 8;
                    freeSpace = iterator;
                } else iterator = iterator + 8;
            } else iterator = iterator + 16;

            printf("Esta alocado: %d - Quantidade de bytes alocados: %d\n", *(int*)(iterator - 16), *(int*)(iterator - 8));
            iterator = iterator + *(int*)(iterator - 8);
        }
    }

    if (freeSpace == NULL) {
        printf("não achou\n");
        temp = sbrk(numBytes + 16);
        *(int*)temp = 1;

        temp = temp + 8;
        *(int*)temp = numBytes;

        temp = temp + 8;
    } else {
        printf("achou\n");
        *(int*)(freeSpace - 16) = 1;
        temp = freeSpace;
    }

    return temp;
}

int main(int argc, char** argv) {
    printf(" ");
    startAllocator();

    printf("Topo Inicial da heap: %p\n", heapStart);

    printf("\nAlocação de teste = 150\n");
    void* teste = allocateMemory(150);

    printf("\nAlocação de teste2 = 90\n");
    void* teste2 = allocateMemory(90);

    printf("\nliberando de teste = 150\n");
    freeMemory(teste);

    printf("\nAlocação de teste3 = 180\n");
    void* teste3 = allocateMemory(180);

    printf("\nAlocação de teste4 = 50\n");
    void* teste4 = allocateMemory(50);

    printf("\nliberando de test4 = 50\n");
    freeMemory(teste4);

    printf("\nliberando de test3 = 180\n");
    freeMemory(teste3);

    printf("\nAlocação de teste5 = 40\n");
    void* teste5 = allocateMemory(40);

    printf("\nAlocação de teste6 = 160\n");
    void* teste6 = allocateMemory(160);

    printf("\nAlocação de teste7 = 200\n");
    void* teste7 = allocateMemory(200);

    endAllocator();
}