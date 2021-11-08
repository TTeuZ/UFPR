#include <stdio.h>
#include <stdlib.h>
#include "libconjunto.h"

int main () {
    conjunto_t *conj, *conj2, *conj3; /* Declaração dos 3 conjuntos */
    int count; /* Contador para as iterações */
    int ret; /* variavel para armazenar retornos de funcoes */

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Testando a criação dos conjuntos...\n");
    printf("\n");

    /* Testando as possibilidades de criações de conjuntos com valor passando do max
     e valor coerente */
    conj = cria_conjunto(100);
    printf("O endereço do primeiro conjunto é: %p\n", &conj);
    conj2 = cria_conjunto(50);
    printf("O endereço do segundo conjunto é: %p\n", &conj2);
    conj3 = cria_conjunto(10);
    printf("O endereço do terceiro conjunto é: %p\n", &conj3);

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("validando que o conjunto está vazio...\n");
    printf("\n");

    if (eh_vazio(conj) == 1) 
        printf("O Conjunto 1 está vazio!, sua cardinalidade é %d\n", cardinalidade(conj));
    else printf("O Conjunto 1 não está vazio!, sua cardinalidade é %d\n", cardinalidade(conj));
    if (eh_vazio(conj2) == 1) 
        printf("O Conjunto 2 está vazio!, sua cardinalidade é %d\n", cardinalidade(conj2));
    else printf("O Conjunto 2 não está vazio!, sua cardinalidade é %d\n", cardinalidade(conj2));
    if (eh_vazio(conj3) == 1) 
        printf("O Conjunto 3 está vazio!, sua cardinalidade é %d\n", cardinalidade(conj3));
    else printf("O Conjunto 3 não está vazio!, sua cardinalidade é %d\n", cardinalidade(conj3));

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("inserindo a primeira metade de elementos dos conjuntos...\n");
    printf("\n");

    /* Iniciando a inserção da primeira metade de elementos no vetor */
    for (count = 0; count < (conj->max/2); count++)  /* inserindo elemento somando de 1 em 1 */
        insere(count, conj);
    for (count = 0; count < (conj2->max/2); count++) /* inserindo elemento somando de 2 em 2 */
        insere(count*2, conj2);
    for (count = 0; count < (conj3->max/2); count++)  /* inserindo elemento somando de 5 em 5 */
        insere(count*5, conj3);

    printf("------------------------------------------------------------------\n");
    printf("validando que o conjunto não está vazio...\n");
    printf("\n");

    if (eh_vazio(conj) == 1) 
        printf("O Conjunto 1 está vazio!, sua cardinalidade é %d\n", cardinalidade(conj));
    else printf("O Conjunto 1 não está vazio!, sua cardinalidade é %d\n", cardinalidade(conj));
    if (eh_vazio(conj2) == 1) 
        printf("O Conjunto 2 está vazio!, sua cardinalidade é %d\n", cardinalidade(conj2));
    else printf("O Conjunto 2 não está vazio!, sua cardinalidade é %d\n", cardinalidade(conj2));
    if (eh_vazio(conj3) == 1) 
        printf("O Conjunto 3 está vazio!, sua cardinalidade é %d\n", cardinalidade(conj3));
    else printf("O Conjunto 3 não está vazio!, sua cardinalidade é %d\n", cardinalidade(conj3));

    printf("------------------------------------------------------------------\n");
    printf("Imprimindo conjuntos apos a inserção da primeira metade...\n");
    printf("\n");

    printf("Conjunto 1: ");
    imprime(conj);
    printf("Conjunto 2: ");
    imprime(conj2);
    printf("Conjunto 3: ");
    imprime(conj3);

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("tentativas de adicionar elementos já existentes...\n");
    printf("\n");

    for (count = 0; count < 2; count++) { /* inserindo elementos diferentes */
        ret = insere(count, conj);
        if (ret == -1) 
            printf("Não é possivel adicionar o elemento, conjunto cheio, retorno: %d\n", ret);
        else if(ret == 0)
            printf("Não é possivel adicionar o elemento, elemento ja existente, retorno: %d\n", ret);
    }
    for (count = 0; count < 2; count++) { /* inserindo elementos diferentes */
        ret = insere(count*2, conj2);
        if (ret == -1) 
            printf("Não é possivel adicionar o elemento, conjunto cheio, retorno: %d\n", ret);
        else if(ret == 0)
            printf("Não é possivel adicionar o elemento, elemento ja existente, retorno: %d\n", ret);
    }
    for (count = 0; count < 2; count++) { /* inserindo elementos diferentes */
        ret = insere(count*5, conj3);
        if (ret == -1) 
            printf("Não é possivel adicionar o elemento, conjunto cheio, retorno: %d\n", ret);
        else if(ret == 0)
            printf("Não é possivel adicionar o elemento, elemento ja existente, retorno: %d\n", ret);
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("removendo a primeira metade de elementos dos conjuntos...\n");
    printf("\n");

    /* Iniciando a remoção da primeira metade de elementos no vetor */
    for (count = 0; count < (conj->max/2); count++)  /* retirando elemento somando de 1 em 1 */
        retira(count, conj);
    for (count = 0; count < (conj2->max/2); count++)  /* retirando elemento somando de 1 em 1 */
        retira(count*2, conj2);
    for (count = 0; count < (conj3->max/2); count++)  /* retirando elemento somando de 1 em 1 */
        retira(count*5, conj3);

    printf("------------------------------------------------------------------\n");
    printf("validando que o conjunto está novamente vazio...\n");
    printf("\n");

    if (eh_vazio(conj) == 1) 
        printf("O Conjunto 1 está vazio!, sua cardinalidade é %d\n", cardinalidade(conj));
    else printf("O Conjunto 1 não está vazio!, sua cardinalidade é %d\n", cardinalidade(conj));
    if (eh_vazio(conj2) == 1) 
        printf("O Conjunto 2 está vazio!, sua cardinalidade é %d\n", cardinalidade(conj2));
    else printf("O Conjunto 2 não está vazio!, sua cardinalidade é %d\n", cardinalidade(conj2));
    if (eh_vazio(conj3) == 1) 
        printf("O Conjunto 3 está vazio!, sua cardinalidade é %d\n", cardinalidade(conj3));
    else printf("O Conjunto 3 não está vazio!, sua cardinalidade é %d\n", cardinalidade(conj3));

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Imprimindo conjuntos apos a remoção da primeira metade...\n");
    printf("\n");

    printf("Conjunto 1: ");
    imprime(conj);
    printf("Conjunto 2: ");
    imprime(conj2);
    printf("Conjunto 3: ");
    imprime(conj3);

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("inserindo elemento até o max do conjunto...\n");
    printf("\n");

    /* Iniciando a inserção dos elementoss no conjunto */
    for (count = 0; count < (conj->max); count++)  /* inserindo elemento somando de 1 em 1, soma */
        insere(count, conj);
    for (count = 0; count < (conj2->max); count++) /* inserindo elemento somando de 2 em 2, soma */
        insere(count*2, conj2);
    for (count = 0; count < (conj3->max); count++)  /* inserindo elemento somando de 5 em 5, soma */
        insere(count*5, conj3);

    printf("------------------------------------------------------------------\n");
    printf("validando que o conjunto não está novamente vazio...\n");
    printf("\n");

    if (eh_vazio(conj) == 1) 
        printf("O Conjunto 1 está vazio!, sua cardinalidade é %d\n", cardinalidade(conj));
    else printf("O Conjunto 1 não está vazio!, sua cardinalidade é %d\n", cardinalidade(conj));
    if (eh_vazio(conj2) == 1) 
        printf("O Conjunto 2 está vazio!, sua cardinalidade é %d\n", cardinalidade(conj2));
    else printf("O Conjunto 2 não está vazio!, sua cardinalidade é %d\n", cardinalidade(conj2));
    if (eh_vazio(conj3) == 1) 
        printf("O Conjunto 3 está vazio!, sua cardinalidade é %d\n", cardinalidade(conj3));
    else printf("O Conjunto 3 não está vazio!, sua cardinalidade é %d\n", cardinalidade(conj3));

    printf("------------------------------------------------------------------\n");
    printf("Imprimindo conjuntos apos o preenchimento total...\n");
    printf("\n");

    printf("Conjunto 1: ");
    imprime(conj);
    printf("Conjunto 2: ");
    imprime(conj2);
    printf("Conjunto 3: ");
    imprime(conj3);

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("tentativas de adicionar elementos com os conjuntos cheios (Elementos diferentes)...\n");
    printf("\n");

    for (count = 0; count < 2; count++) { /* inserindo elementos diferentes */
        ret = insere((count+1)*100, conj);
        if (ret == -1) 
            printf("Não é possivel adicionar o elemento, conjunto cheio, retorno: %d\n", ret);
        else if(ret == 0)
            printf("Não é possivel adicionar o elemento, elemento ja existente, retorno: %d\n", ret);
    }
    for (count = 0; count < 2; count++) { /* inserindo elementos diferentes */
        ret = insere((count+1)*100, conj2);
        if (ret == -1) 
            printf("Não é possivel adicionar o elemento, conjunto cheio, retorno: %d\n", ret);
        else if(ret == 0)
            printf("Não é possivel adicionar o elemento, elemento ja existente, retorno: %d\n", ret);
    }
    for (count = 0; count < 2; count++) { /* inserindo elementos diferentes */
        ret = insere((count+1)*100, conj3);
        if (ret == -1) 
            printf("Não é possivel adicionar o elemento, conjunto cheio, retorno: %d\n", ret);
        else if(ret == 0)
            printf("Não é possivel adicionar o elemento, elemento ja existente, retorno: %d\n", ret);
    }
        
    printf("------------------------------------------------------------------\n");
    printf("\n");

    /* Liberando a memoria alocada dinamicamente para os 3 conjuntos durante a execução do teste */
    printf("Liberando a memoria utilizada pelo conjunto 1...\n");
    destroi_conjunto(conj);
    printf("Liberando a memoria utilizada pelo conjunto 2...\n");
    destroi_conjunto(conj2);
    printf("Liberando a memoria utilizada pelo conjunto 3...\n");
    destroi_conjunto(conj3);

    printf("\n");
    printf("FIM DO TESTE\n");
    printf("------------------------------------------------------------------\n");
    printf("------------------------------------------------------------------\n");
    return 0;
}