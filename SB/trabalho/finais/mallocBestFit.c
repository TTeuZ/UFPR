#include <stdio.h>
#include <unistd.h>
#include <limits.h>

// Teve que usar o sbrk pq de acordo com o man, não da para fazer o que queremos com o brk

void* heapStart;
void* heapEnd;

void iniciaAlocador() {
    heapStart = heapEnd = sbrk(0);
}

void finalizaAlocador() {
    brk(heapStart);
}

int liberaMem(void* block) {
    *(int*)(block - 16) = 0;
    return 0;
}

void* alocaMem(int numBytes) {
    void* temp, * iterator, * freeSpace;
    int bytesQtd, diff;

    freeSpace = NULL;
    bytesQtd = INT_MAX;

    iterator = heapStart;
    while (iterator < heapEnd) {
        if (*(int*)iterator == 0) {
            iterator = iterator + 8;
            if (*(int*)iterator >= numBytes && *(int*)iterator <= bytesQtd) {
                bytesQtd = *(int*)iterator;
                iterator = iterator + 8;
                freeSpace = iterator;
            } else iterator = iterator + 8;
        } else iterator = iterator + 16;

        iterator = iterator + *(int*)(iterator - 8);
    }

    if (freeSpace == NULL) {
        temp = sbrk(0);
        diff = temp - heapEnd;
        if (diff < numBytes)
            sbrk((1 + (numBytes / 4096)) * 4096);

        temp = heapEnd;
        *(int*)temp = 1;

        temp = temp + 8;
        *(int*)temp = numBytes;
        temp = temp + 8;

        heapEnd = temp + numBytes;

        freeSpace = heapEnd;
        *(int*)freeSpace = 0;

        freeSpace = freeSpace + 8;

        *(int*)freeSpace = sbrk(0) - (heapEnd + 16);
    } else {
        *(int*)(freeSpace - 16) = 1;
        temp = freeSpace;
    }

    return temp;
}

void imprimeMapa() {
    void* iterator;
    int free, size, count;

    iterator = heapStart;
    while (iterator < sbrk(0)) {
        if (*(int*)iterator == 0) free = 1;
        else free = 0;

        iterator = iterator + 8;
        size = *(int*)iterator;

        printf("################");
        iterator = iterator + 8;
        for (count = 0; count < size; count++) {
            if (free == 1) printf("+");
            else printf("-");
        }
        iterator = iterator + size;
    }
    printf("\n");
}

int main() {
    void* a, * b;
    printf("\n");
    iniciaAlocador();
    imprimeMapa();

    a = alocaMem(32);
    imprimeMapa();

    b = alocaMem(50);
    imprimeMapa();

    liberaMem(a);
    imprimeMapa();

    a = alocaMem(10);
    imprimeMapa();

    // --------------
    liberaMem(b);
    imprimeMapa();

    b = alocaMem(200);
    imprimeMapa();
    // --------------

    finalizaAlocador();
    imprimeMapa();
}