#include <stdio.h>
#include <unistd.h>
#include <limits.h>

// Teve que usar o sbrk pq de acordo com o man, não da para fazer o que queremos com o brk

void* heapStart;
void* heapEnd;

void startAllocator() {
    heapStart = heapEnd = sbrk(0);
}

void endAllocator() {
    brk(heapStart);
}

int freeMemory(void* block) {
    *(int*)(block - 16) = 0;
    return 0;
}

void* allocateMemory(int numBytes) {
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
    } else {
        *(int*)(freeSpace - 16) = 1;
        temp = freeSpace;
    }

    return temp;
}

void imprimeMapa() {
    int count;

    count = heapStart;
    while (count < heapEnd) {

    }
}

int main()
{
    printf("\n");
    startAllocator();
    long int* new_mem = allocateMemory(8);
    printf("\n");
    long int* new_mem2 = allocateMemory(16);
    printf("\n");
    long int* new_mem3 = allocateMemory(32);
    printf("\n");
    long int* new_mem4 = allocateMemory(12);
    printf("\n");

    freeMemory(new_mem2);
    freeMemory(new_mem4);

    long int* new_mem2 = allocateMemory(10);
    long int* reused_mem2 = allocateMemory(15);
    long int* new_mem5 = allocateMemory(3948);
    long int* new_mem6 = allocateMemory(8);

    endAllocator();
    return 0;
}