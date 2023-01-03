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
    int diff;

    freeSpace = NULL;

    if (topoInicialHeap != topoAtualHeap) {
        iterator = topoInicialHeap;
        while (iterator < topoAtualHeap) {
            if (*(int*)iterator == 0) {
                iterator = iterator + 8;
                if (*(int*)iterator >= num_bytes) {
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

        temp = sbrk(0);
        diff = temp - topoAtualHeap;
        if (diff < num_bytes) {
            printf("teve que alocar\n");
            sbrk((1 + (num_bytes / 4096)) * 4096);
        }

        temp = topoAtualHeap;
        *(int*)temp = 1;

        temp = temp + 8;
        *(int*)temp = num_bytes;
        temp = temp + 8;

        topoAtualHeap = temp + num_bytes;
    } else {
        printf("achou\n");

        *(int*)(freeSpace - 16) = 1;
        temp = freeSpace;
    }

    return temp;
}

int main(int argc, char** argv) {
    printf(" ");
    iniciaAlocador();

    printf("Topo Inicial da heap: %p\n", topoInicialHeap);

    printf("\nAlocação de teste = 150\n");
    void* teste = alocaMen(150);

    printf("\nAlocação de teste2 = 90\n");
    void* teste2 = alocaMen(90);

    printf("\nliberando de teste = 150\n");
    liberaMen(teste);

    printf("\nAlocação de teste3 = 180\n");
    void* teste3 = alocaMen(180);

    printf("\nAlocação de teste4 = 50\n");
    void* teste4 = alocaMen(50);

    printf("\nliberando de test4 = 50\n");
    liberaMen(teste4);

    printf("\nliberando de test3 = 180\n");
    liberaMen(teste3);

    printf("\nAlocação de teste5 = 40\n");
    void* teste5 = alocaMen(40);

    printf("\nAlocação de teste6 = 160\n");
    void* teste6 = alocaMen(160);

    printf("\nAlocação de teste7 = 200\n");
    void* teste7 = alocaMen(200);

    finalizarAlocador();
}