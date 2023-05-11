// TRABALHO1: CI1316 1o semestre 2023
// Aluno: Paulo Mateus Luza Alves
// GRR: GRR20203945

#include <iostream>
#include <typeinfo>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "chrono.c"

#define DEBUG 0
#define MAX_THREADS 64
#define MAX_TOTAL_ELEMENTS (500 * 1000 * 1000)
#define NTIMES 1000										   
#define TYPE long

int nThreads;
int nTotalElements;
TYPE* InputVector;
TYPE* OutputVector;
chronometer_t parallelPrefixSumTime;
volatile TYPE partialSum[MAX_THREADS];

// -----------------------------------------

pthread_t threads[MAX_THREADS];
int threads_id[MAX_THREADS];
int globalThreadsNumber, globalTotalElements;

pthread_barrier_t thread_barrier;

// -----------------------------------------

int min (int a, int b) {
    if (a < b) return a;
    else return b;
}

void verifyPrefixSum (const TYPE* InputVec, const TYPE* OutputVec, long nTotalElmts) {
    volatile TYPE last = InputVec[0];
    int ok = 1;
    for (long i = 1; i < nTotalElmts; i++) {
        if (OutputVec[i] != (InputVec[i] + last)) {
            fprintf(stderr, "In[%ld]= %ld\n" "Out[%ld]= %ld (wrong result!)\n" "Out[%ld]= %ld (ok)\n" "last=%ld\n", i, InputVec[i], i, OutputVec[i], i - 1, OutputVec[i - 1], last);
            ok = 0;
            break;
        }
        last = OutputVec[i];
    }
    if (ok) printf("\nPrefix Sum verified correctly.\n");
    else printf("\nPrefix Sum DID NOT compute correctly!!!\n");
}

void *prefixSum (void *id) {

}

void parallelPrefixSumPth (const TYPE* InputVec, const TYPE* OutputVec, long nTotalElmts, int nThreads) {
    static int alreadyInit;
    int count;

    alreadyInit = 0;
    if (!alreadyInit) {
        pthread_barrier_init (&thread_barrier, NULL, nThreads);
        threads_id[0] = 0;
        for (count = 1; count < nThreads; ++count) {
            threads_id[count] = count;
            pthread_create (&threads[count], NULL, prefixSum, &threads_id[count]);
        }
        alreadyInit = 1;
    }

    prefixSum(&threads_id[0]);
}

int main (int argc, char* argv[]) {
    long i;

    ///////////////////////////////////////
    ///// ATENCAO: NAO MUDAR O MAIN   /////
    ///////////////////////////////////////

    if (argc != 3) {
        printf("usage: %s <nTotalElements> <nThreads>\n", argv[0]);
        return 0;
    } else {
        nThreads = atoi(argv[2]);
        if (nThreads == 0) {
            printf("usage: %s <nTotalElements> <nThreads>\n", argv[0]);
            printf("<nThreads> can't be 0\n");
            return 0;
        }
        if (nThreads > MAX_THREADS) {
            printf("usage: %s <nTotalElements> <nThreads>\n", argv[0]);
            printf("<nThreads> must be less than %d\n", MAX_THREADS);
            return 0;
        }
        nTotalElements = atoi(argv[1]);
        if (nTotalElements > MAX_TOTAL_ELEMENTS) {
            printf("usage: %s <nTotalElements> <nThreads>\n", argv[0]);
            printf("<nTotalElements> must be up to %d\n", MAX_TOTAL_ELEMENTS);
            return 0;
        }
    }

    // allocate InputVector AND OutputVector
    InputVector = (TYPE*)malloc(nTotalElements * sizeof(TYPE));
    if (InputVector == NULL)
        printf("Error allocating InputVector of %d elements (size=%ld Bytes)\n", nTotalElements, nTotalElements * sizeof(TYPE));

    OutputVector = (TYPE*)malloc(nTotalElements * sizeof(TYPE));
    if (OutputVector == NULL)
        printf("Error allocating OutputVector of %d elements (size=%ld Bytes)\n", nTotalElements, nTotalElements * sizeof(TYPE));

    // #if DEBUG >= 2 
    // Print INFOS about the reduction
    TYPE myType;
    long l;
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
        << " bytes each)\n" << std::endl;

    /*printf("reading inputs...\n");
    for (int i = 0; i < nTotalElements; i++)
        scanf("%d", &InputVector[i]);
    */

    // initialize InputVector
    // srand(time(NULL));   // Initialization, should only be called once.

    int r;
    for (long i = 0; i < nTotalElements; i++) {
        r = rand();  // Returns a pseudo-random integer
        // between 0 and RAND_MAX.
        InputVector[i] = (r % 1000) - 500;
        // InputVector[i] = 1; // i + 1;
    }
    printf("\n\nwill use %d threads to calculate prefix-sum of %d total elements\n", nThreads, nTotalElements);

    chrono_reset(&parallelPrefixSumTime);
    chrono_start(&parallelPrefixSumTime);

    // call it N times
    TYPE globalSum;
    TYPE* InVec = InputVector;
    for (int i = 0; i < NTIMES; i++) {
        // globalSum = parallel_reduceSum( InputVector, nTotalElements, nThreads );
        parallelPrefixSumPth(InputVector, OutputVector, nTotalElements, nThreads);
        // InputVector += (nTotalElements % MAX_TOTAL_ELEMENTS);                                
        // wait 50 us == 50000 ns
        // nanosleep((const struct timespec[]){{0, 50000L}}, NULL);                                
    }

    // Measuring time of the parallel algorithm 
    // including threads creation and joins...
    chrono_stop(&parallelPrefixSumTime);
    chrono_reportTime(&parallelPrefixSumTime, "parallelPrefixSumTime");

    // calcular e imprimir a VAZAO (numero de operacoes/s)
    double total_time_in_seconds = (double)chrono_gettotal(&parallelPrefixSumTime) / ((double)1000 * 1000 * 1000);
    printf("total_time_in_seconds: %lf s for %d somas de prefixos\n", total_time_in_seconds, NTIMES);

    double OPS = ((long)nTotalElements * NTIMES) / total_time_in_seconds;
    printf("Throughput: %lf OP/s\n", OPS);

    verifyPrefixSum(InputVector, OutputVector, nTotalElements);
    //#if NEVER
#if DEBUG >= 2 
    // Print InputVector
    printf("In: ");
    for (int i = 0; i < nTotalElements; i++)
        printf("%d ", InputVector[i]);
    printf("\n");

    // Print OutputVector
    printf("Out: ");
    for (int i = 0; i < nTotalElements; i++)
        printf("%d ", OutputVector[i]);
    printf("\n");
#endif
    return 0;
}