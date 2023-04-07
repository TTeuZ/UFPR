#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//função a ser executada quando uma thread for criada
void* PrintHello(void* thread_id) {
    pthread_t thread; // criando t1 e t2 do tipo thread
    long id;

    id = (long)thread_id; // conversão de void pra long
    printf("Thread %ld: Olá mundo!\n", id);

    pthread_exit(NULL); // finalização da thread
}

// int main() {
//     pthread_t t1, t2; // criando t1 e t2 do tipo thread
//     int create; // variável que recebe o retorno da função pthread_create()
//     long num; // identificador da thread

//     num = 1;
//     printf("Main: criando a thread %ld\n", num);
//     create = pthread_create(&t1, NULL, PrintHello, (void*)num); // criando thread 1

//     num = 2;
//     printf("Main: criando a thread %ld\n", num);
//     create = pthread_create(&t2, NULL, PrintHello, (void*)num); // criando thread 2

//     // Fazendo a thread main esperar as 2 threads criadas
//     pthread_join(t1, NULL);
//     pthread_join(t2, NULL);

//     printf("Main: finalizando\n");
//     return 0;
// }


int main() {
    pthread_t t1, t2; // criando t1 e t2 do tipo thread
    int create; // variável que recebe o retorno da função pthread_create()
    long num; // identificador da thread

    num = 1;
    printf("Main: criando a thread %ld\n", num);
    create = pthread_create(&t1, NULL, PrintHello, (void*)num); // criando thread 1

    printf("Main dando join na t1\n");
    pthread_join(t1, NULL);
    printf("Main ja passou pelo join na t1\n");

    num = 2;
    printf("Main: criando a thread %ld\n", num);
    create = pthread_create(&t2, NULL, PrintHello, (void*)num); // criando thread 2

    printf("Main dando join na t2\n");
    pthread_join(t2, NULL);
    printf("Main ja passou pelo join na t2\n");

    printf("Main: finalizando\n");
    return 0;
}

// usando o pthread_join podemos forçar uma "sincronização" entre as threads. Basicamente forçamos uma thread a esperar as que ela deu join acabarem para que ela possa continuar, ou seja ela fica travada no ponto do join
// até a as threads que foram joinadas terminarem.