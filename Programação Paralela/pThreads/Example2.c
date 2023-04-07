#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int count = 0;
#define COUNT_MAX 10

pthread_mutex_t mutexsum;

// Primeira funçao de contar, op problema aqui é que o prinf esta dentro do lock, o que faz com que o processo de lock dure muito
// pois o printf é um funçao lenta
// void* countSum(void* tid) {
//     long id = (long)tid;

//     while (count < COUNT_MAX) {
//         pthread_mutex_lock(&mutexsum);
//         count = count + 1;
//         printf("Thread %ld: contador em %d\n", id, count);
//         pthread_mutex_unlock(&mutexsum);

//         sleep(rand() % 3);
//     } 
//     pthread_exit(NULL);
// }

void* countSum(void* tid) {
    long id = (long)tid;
    int temp;

    while (count < COUNT_MAX) {
        pthread_mutex_lock(&mutexsum);
        temp = ++count;
        pthread_mutex_unlock(&mutexsum);

        printf("Thread %ld: contador em %d\n", id, temp);

        sleep(rand() % 3);
    }
    pthread_exit(NULL);
}


int main() {
    pthread_t t1, t2; // criando t1 e t2 do tipo thread
    int create; // variável que recebe o retorno da função pthread_create()
    long num; // identificador da thread

    pthread_mutex_init(&mutexsum, NULL);

    num = 1;
    printf("Main: criando a thread %ld\n", num);
    create = pthread_create(&t1, NULL, countSum, (void*)num); // criando thread 1

    num = 2;
    printf("Main: criando a thread %ld\n", num);
    create = pthread_create(&t2, NULL, countSum, (void*)num); // criando thread 2


    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("Main: finalizando\n");

    pthread_mutex_destroy(&mutexsum);

    return 0;
}

// usando as mutex temos outra alterniativa de pseudo-sincronização das thereads. Basicamente, por meio de um lock, podemos restringir uma ared de codigo que não pode ser acessado simultaneamente
// em um thread, ou seja, se outra thread chegar neste ponto e estiver travado, ela fica esperando (acordada) o unlock para que ela possa acessar essa região.
// Isso serve muito bem para regiões que não podem ter modificações simultaneas, mas acaba deixando o processo de paralelização mais lento.