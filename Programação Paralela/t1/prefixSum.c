// TRABALHO1: CI1316 1o semestre 2023
// Aluno: Paulo Mateus Luza Alves
// GRR: GRR20203945

#include "chrono.c"
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <typeinfo>

#define DEBUG 0
#define MAX_THREADS 64
#define MAX_TOTAL_ELEMENTS (500 * 1000 * 1000)
#define NTIMES 1000
#define TYPE long

int nThreads, nTotalElements;
TYPE *InputVector;
TYPE *OutputVector;
chronometer_t parallelPrefixSumTime;
volatile TYPE partialSum[MAX_THREADS];

// -----------------------------------------

pthread_t threads[MAX_THREADS];
int threads_id[MAX_THREADS];

pthread_barrier_t barrier;

// -----------------------------------------

void verifyPrefixSum (const TYPE *InputVec, const TYPE *OutputVec, long nTotalElmts) {
    volatile TYPE last = InputVec[0];
    int ok = 1;
    for (long i = 1; i < nTotalElmts; i++) {
        if (OutputVec[i] != (InputVec[i] + last)) {
            fprintf (stderr, "In[%ld]= %ld\n"
                            "Out[%ld]= %ld (wrong result!)\n"
                            "Out[%ld]= %ld (ok)\n"
                            "last=%ld\n",
                    i, InputVec[i], i, OutputVec[i], i - 1, OutputVec[i - 1], last);
            ok = 0;
            break;
        }
        last = OutputVec[i];
    }
    if (ok) printf ("\nPrefix Sum verified correctly.\n");
    else printf ("\nPrefix Sum DID NOT compute correctly!!!\n");
}

void *prefixSum (void *idPointer) {
    int id, numberOfElements, begin, end, count;
    TYPE threadSum, partialPrefix;

    id = *((int *)idPointer);
    numberOfElements = nTotalElements / nThreads;

    begin = id * numberOfElements;
    end = (id + 1) == nThreads ? nTotalElements : (id + 1) * numberOfElements;
    end--;

    while (true) {
        threadSum = 0;
        for (count = begin; count <= end; ++count)
            threadSum += InputVector[count];

        partialSum[id] = threadSum;

        pthread_barrier_wait(&barrier);

        partialPrefix = 0;
        for (count = 0; count < id; ++ count)
            partialPrefix += partialSum[count];

        OutputVector[begin] = InputVector[begin] + partialPrefix;
        for (count = begin + 1; count <= end; ++count) 
            OutputVector[count] = InputVector[count] + OutputVector[count - 1];

        if(id == 0)
            return NULL; 
    }
}

void parallelPrefixSumPth (const TYPE *InputVec, const TYPE *OutputVec, long elements, int threadsQtd) {
    static int alreadyInit = 0;
    int count;

    nThreads = threadsQtd;
    nTotalElements = elements;

    if (alreadyInit == 0) {
        pthread_barrier_init (&barrier, NULL, threadsQtd);
        threads_id[0] = 0;
        for (count = 1; count < threadsQtd; ++count) {
            threads_id[count] = count;
            pthread_create (&threads[count], NULL, prefixSum, &threads_id[count]);
        }
        alreadyInit = 1;
    }

    prefixSum (&threads_id[0]);
}

int main(int argc, char *argv[]) {
    int random, threadsQtd, elements;
    long i;

    ///////////////////////////////////////
    ///// ATENCAO: NAO MUDAR O MAIN   /////
    ///////////////////////////////////////

    if (argc != 3) {
        printf ("usage: %s <nTotalElements> <nThreads>\n", argv[0]);
        return 0;
    } else {
        threadsQtd = atoi(argv[2]);
        if (threadsQtd == 0) {
            printf ("usage: %s <nTotalElements> <nThreads>\n", argv[0]);
            printf ("<nThreads> can't be 0\n");
            return 0;
        }
        if (threadsQtd > MAX_THREADS) {
            printf("usage: %s <nTotalElements> <nThreads>\n", argv[0]);
            printf("<nThreads> must be less than %d\n", MAX_THREADS);
            return 0;
        }
        elements = atoi(argv[1]);
        if (elements > MAX_TOTAL_ELEMENTS) {
            printf ("usage: %s <nTotalElements> <nThreads>\n", argv[0]);
            printf ("<nTotalElements> must be up to %d\n", MAX_TOTAL_ELEMENTS);
            return 0;
        }
    }

    // allocate InputVector AND OutputVector
    InputVector = (TYPE *)malloc (elements * sizeof(TYPE));
    if (InputVector == NULL)
        printf ("Error allocating InputVector of %d elements (size=%ld Bytes)\n", elements, elements * sizeof(TYPE));

    OutputVector = (TYPE *) malloc(elements * sizeof(TYPE));
    if (OutputVector == NULL)
        printf ("Error allocating OutputVector of %d elements (size=%ld Bytes)\n", elements, elements * sizeof(TYPE));

    TYPE myType;
    std::cout << "Using PREFIX SUM of TYPE ";

    if (typeid(myType) == typeid(int))
        std::cout << "int";
    else if (typeid(myType) == typeid(long))
        std::cout << "long";
    else if (typeid(myType) == typeid(float))
        std::cout << "float";
    else if (typeid(myType) == typeid(double))
        std::cout << "double";
    else if (typeid(myType) == typeid(long long))
        std::cout << "long long";
    else std::cout << " ?? (UNKNOWN TYPE)";

    std::cout << " elements (" << sizeof(TYPE)
              << " bytes each)\n"
              << std::endl;

    for (long i = 0; i < elements; i++) {
        random = rand ();
        InputVector[i] = (random % 1000) - 500;
        // InputVector[i] = 1; // i + 1;
    }
    printf ("\n\nwill use %d threads to calculate prefix-sum of %d total elements\n", threadsQtd, elements);

    chrono_reset (&parallelPrefixSumTime);
    chrono_start (&parallelPrefixSumTime);

    // call it N times
    for (int i = 0; i < NTIMES; i++)
        parallelPrefixSumPth (InputVector, OutputVector, elements, threadsQtd);

    chrono_stop (&parallelPrefixSumTime);
    chrono_reportTime (&parallelPrefixSumTime, "parallelPrefixSumTime");

    // calcular e imprimir a VAZAO (numero de operacoes/s)
    double total_time_in_seconds = (double)chrono_gettotal (&parallelPrefixSumTime) / ((double)1000 * 1000 * 1000);
    printf ("total_time_in_seconds: %lf s for %d somas de prefixos\n", total_time_in_seconds, NTIMES);

    double OPS = ((long)elements * NTIMES) / total_time_in_seconds;
    printf ("Throughput: %lf OP/s\n", OPS);

    verifyPrefixSum (InputVector, OutputVector, elements);
#if DEBUG >= 2
    // Print InputVector
    printf ("In: ");
    for (int i = 0; i < elements; i++)
        printf ("%ld ", InputVector[i]);
    printf ("\n");

    // Print OutputVector
    printf ("Out: ");
    for (int i = 0; i < elements; i++)
        printf ("%ld ", OutputVector[i]);
    printf ("\n");
#endif
    return 0;
}