#include <stdio.h>
#include <unistd.h>
#include <limits.h>

// Teve que usar o sbrk pq de acordo com o man, não da para fazer o que queremos com o brk

void* heapStart;
void* heapEnd;

void iniciaAlocador() {
    printf("\n");
    heapStart = heapEnd = sbrk(0);
}

void finalizaAlocador() {
    brk(heapStart);
}

int liberaMem(void* block) {
    void *temp;
    int bytesQtd, bytesAtual;

    *(int*)(block - 16) = 0;
    bytesQtd = *(int*)(block - 8);
    bytesAtual = *(int*)(block - 8);

    temp = block + bytesQtd;

    while (temp < sbrk(0) && *(int*)temp == 0) {
        bytesQtd = *(int*)(temp + 8);
        *(int*)(block - 8) += bytesQtd + 16;
        temp += bytesQtd + 16;
        if (temp == sbrk(0)) {
            heapEnd = heapEnd - (bytesAtual+ 32);
        } else {
            bytesQtd += bytesQtd + 16;
        }
    }

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
        bytesQtd = *(int*)(freeSpace - 8);

        bytesQtd = bytesQtd - numBytes;

        if (bytesQtd > 16) {
            *(int*)(freeSpace - 8) = numBytes;
            freeSpace = freeSpace + numBytes;
             *(int*)(freeSpace) = 0;
            freeSpace = freeSpace + 8;
            *(int*)(freeSpace) = bytesQtd - 16;
        }

        temp = freeSpace - 8 - numBytes;
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

int main (long int argc, char** argv) {
  void *a,*b,*c,*d,*e;

  iniciaAlocador(); 
  imprimeMapa();
  // 0) estado inicial

  a=(void *) alocaMem(100);
  imprimeMapa();
  b=(void *) alocaMem(130);
  imprimeMapa();
  c=(void *) alocaMem(120);
  imprimeMapa();
  d=(void *) alocaMem(110);
  imprimeMapa();
  // 1) Espero ver quatro segmentos ocupados

  liberaMem(b);
  imprimeMapa(); 
  liberaMem(d);
  imprimeMapa(); 
  // 2) Espero ver quatro segmentos alternando
  //    ocupados e livres

  b=(void *) alocaMem(50);
  imprimeMapa();
  d=(void *) alocaMem(90);
  imprimeMapa();
  e=(void *) alocaMem(40);
  imprimeMapa();
  // 3) Deduzam
	
  liberaMem(c);
  imprimeMapa(); 
  liberaMem(a);
  imprimeMapa();
  liberaMem(b);
  imprimeMapa();
  liberaMem(d);
  imprimeMapa();
  liberaMem(e);
  imprimeMapa();
   // 4) volta ao estado inicial

  finalizaAlocador();
}
