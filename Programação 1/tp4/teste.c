#include <stdio.h>
#include <stdlib.h>
#include "libconjunto.h"

int main () {
    conjunto_t *conj, *conj2, *conj3, *conj4, *conj5; /* Declaração dos 5 conjuntos */
    conjunto_t *conj_intersec1, *conj_intersec2; /* Declaração de 2 conjuntos para intersecções */
    conjunto_t *conj_uni1, *conj_uni2; /* Declaração de 2 conjuntos para uniões */
    conjunto_t *conj_diff1, *conj_diff2; /* Declaração de 2 conjuntos para as diferencas */
    int count; /* Contador para as iterações */
    int ret; /* variavel para armazenar retornos de funcoes */

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Testando a criação dos conjuntos...\n");
    printf("\n");

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
    for (count = 0; count < 50; count++)  /* inserindo elemento somando de 1 em 1 */
        insere(count, conj);
    for (count = 0; count < 25; count++) /* inserindo elemento somando de 2 em 2 */
        insere(count*2, conj2);
    for (count = 0; count < 5; count++)  /* inserindo elemento somando de 5 em 5 */
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
    printf("Adicionar elementos fora de ordem para averiguar que mantem ordenado...\n");
    printf("\n");

    count = 1;
    while (count <= 10) { /* Adicionando numeros inpares 1-3-5-7... */
        insere(count, conj2);
        count = count + 2;
    } 
    for (count = 0; count < 5; count++)  /* Adicionando numeros multiplos de 2 */
        insere(count*2, conj3);

    printf("------------------------------------------------------------------\n");
    printf("Imprimindo conjuntos apos a inserção dos elementos extras...\n");
    printf("\n");

    printf("Conjunto 2: ");
    imprime(conj2);
    printf("Conjunto 3: ");
    imprime(conj3);

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("removendo elementos fora de ordem para averiguar que mantem ordenado...\n");
    printf("\n");

    count = 1;
    while (count <= 10) { /* Adicionando numeros inpares 1-3-5-7... */
        retira(count, conj2);
        count = count + 2;
    } 
    for (count = 0; count < 5; count++)  /* Adicionando numeros multiplos de 2 */
        retira(count*2, conj3);

    printf("------------------------------------------------------------------\n");
    printf("Imprimindo conjuntos apos a remoca dos elementos extras...\n");
    printf("\n");

    printf("Conjunto 2: ");
    imprime(conj2);
    printf("Conjunto 3: ");
    imprime(conj3);

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("removendo a primeira metade de elementos dos conjuntos...\n");
    printf("\n");

    /* Iniciando a remoção da primeira metade de elementos no vetor */
    for (count = 0; count < 50; count++)  /* retirando elemento somando de 1 em 1 */
        retira(count, conj);
    for (count = 0; count < 25; count++)  /* retirando elemento somando de 2 em 2 */
        retira(count*2, conj2);
    for (count = 0; count < 5; count++)  /* retirando elemento somando de 5 em 5 */
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
    for (count = 0; count < 100; count++)  /* inserindo elemento somando de 1 em 1, soma */
        insere(count, conj);
    for (count = 0; count < 50; count++) /* inserindo elemento somando de 2 em 2, soma */
        insere(count*2, conj2);
    for (count = 0; count < 10; count++)  /* inserindo elemento somando de 5 em 5, soma */
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

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Testando se os conjutos atuais estão contidos...\n");
    printf("\n");

    if (contido(conj, conj2) == 1)
        printf("O conjuto 1 esta contido no conjuto 2!\n");
    else printf("O conjunto 1 não está contido no conjunto 2!\n");
    if (contido(conj, conj3) == 1)
        printf("O conjuto 1 esta contido no conjuto 3!\n");
    else printf("O conjunto 1 não está contido no conjunto 3!\n");
    if (contido(conj2, conj) == 1)
        printf("O conjuto 2 esta contido no conjuto 1!\n");
    else printf("O conjunto 2 não está contido no conjunto 1!\n");
    if (contido(conj2, conj3) == 1)
        printf("O conjuto 2 esta contido no conjuto 3!\n");
    else printf("O conjunto 2 não está contido no conjunto 3!\n");
    if (contido(conj3, conj2) == 1)
        printf("O conjuto 3 esta contido no conjuto 2!\n");
    else printf("O conjunto 3 não está contido no conjunto 2!\n");
    if (contido(conj3, conj) == 1)
        printf("O conjuto 3 esta contido no conjuto 1!\n");
    else printf("O conjunto 3 não está contido no conjunto 1!\n");

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Testando pertencimentos de elementos nos conjutos...\n");
    printf("\n");

    for (count = 1; count <= 2; count ++) { /* Testando o pertecimento de elementos em seguencia 1,2 */
        if (pertence(count, conj) == 1)
            printf("O elemento %d pertence ao conjunto 1!\n", count);
        else printf("O elemento %d não pertence ao conjunto 1!\n", count);
        if (pertence(count, conj2) == 1)
            printf("O elemento %d pertence ao conjunto 2!\n", count);
        else printf("O elemento %d não pertence ao conjunto 2!\n", count);
        if (pertence(count, conj3) == 1)
            printf("O elemento %d pertence ao conjunto 3!\n", count);
        else printf("O elemento %d não pertence ao conjunto 3!\n", count);
    }

    printf("------------------------------------------------------------------\n");

       for (count = 1; count <= 2; count ++) { /* Testando o pertecimento de elementos em seguencia 2,4 */
        if (pertence(count*2, conj) == 1)
            printf("O elemento %d pertence ao conjunto 1!\n", count*2);
        else printf("O elemento %d não pertence ao conjunto 1!\n", count*2);
        if (pertence(count*2, conj2) == 1)
            printf("O elemento %d pertence ao conjunto 2!\n", count*2);
        else printf("O elemento %d não pertence ao conjunto 2!\n", count*2);
        if (pertence(count*2, conj3) == 1)
            printf("O elemento %d pertence ao conjunto 3!\n", count*2);
        else printf("O elemento %d não pertence ao conjunto 3!\n", count*2);
    }

    printf("------------------------------------------------------------------\n");

       for (count = 1; count <= 2; count ++) { /* Testando o pertecimento de elementos em seguencia 5,10 */
        if (pertence(count*5, conj) == 1)
            printf("O elemento %d pertence ao conjunto 1!\n", count*5);
        else printf("O elemento %d não pertence ao conjunto 1!\n", count*5);
        if (pertence(count*5, conj2) == 1)
            printf("O elemento %d pertence ao conjunto 2!\n", count*5);
        else printf("O elemento %d não pertence ao conjunto 2!\n", count*5);
        if (pertence(count*5, conj3) == 1)
            printf("O elemento %d pertence ao conjunto 3!\n", count*5);
        else printf("O elemento %d não pertence ao conjunto 3!\n", count*5);
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Testando igualdade de conjuntos...\n");
    printf("\n");

    if (sao_iguais(conj, conj2) == 1)
        printf("O conjuto 1 é igual 2!\n");
    else printf("O conjunto 1 não é igual ao conjunto 2!\n");
    if (sao_iguais(conj, conj3) == 1)
        printf("O conjuto 1 é igual conjuto 3!\n");
    else printf("O conjunto 1 não é iqual ao conjunto 3!\n");
    if (sao_iguais(conj2, conj) == 1)
        printf("O conjuto 2 é igual conjuto 1!\n");
    else printf("O conjunto 2 não é iqual ao conjunto 1!\n");
    if (sao_iguais(conj2, conj3) == 1)
        printf("O conjuto 2 é igual conjuto 3!\n");
    else printf("O conjunto 2 não é iqual ao conjunto 3!\n");
    if (sao_iguais(conj3, conj2) == 1)
        printf("O conjuto 3 é igual conjuto 2!\n");
    else printf("O conjunto 3 não é iqual ao conjunto 2!\n");
    if (sao_iguais(conj3, conj) == 1)
        printf("O conjuto 3 é igual conjuto 1!\n");
    else printf("O conjunto 3 não é iqual ao conjunto 1!\n");

    printf("\n");

    printf("Construindo e preenchendo 2 conjuntos de maneira igual...\n");
    conj4 = cria_conjunto(10);
    conj5 = cria_conjunto(10);

    for (count = 0; count < 10; count++) {
        insere(count, conj4);
        insere(count, conj5);
    }
    printf("\n");

    printf("Testando se estes são iguais...\n");
    if (sao_iguais(conj4, conj5) == 1)
        printf("O conjuto 4 é igual 5!\n");
    else printf("O conjunto 4 não é igual ao conjunto 5!\n");

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Criando intersecção de conjuntos...\n");
    printf("\n");

    conj_intersec1 = cria_interseccao (conj, conj2);
    conj_intersec2 = cria_interseccao (conj2, conj3);

    printf("Printando a intersecção do conjunto 1 com o 2...\n");
    imprime (conj_intersec1);
    printf("Printando a intersecção do conjunto 2 com o 3...\n");
    imprime (conj_intersec2);

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Criando união de conjuntos...\n");
    printf("\n");

    conj_uni1 = cria_uniao (conj, conj2);
    conj_uni2 = cria_uniao (conj2, conj3);

    printf("Printando a união do conjunto 1 com o 2...\n");
    imprime (conj_uni1);
    printf("Printando a união do conjunto 2 com o 3...\n");
    imprime (conj_uni2);

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Criando a diferença de conjuntos...\n");
    printf("\n");

    conj_diff1 = cria_diferenca (conj, conj2);
    conj_diff2 = cria_diferenca (conj, conj3);

    printf("Printando a diferença do conjunto 1 com o 2...\n");
    imprime (conj_diff1);
    printf("Printando a diferença do conjunto 1 com o 3...\n");
    imprime (conj_diff2);

    printf("\n"); 
    printf("------------------------------------------------------------------\n");
    printf("\n");

    /* Liberando a memoria alocada dinamicamente para os 3 conjuntos durante a execução do teste */
    printf("Liberando a memoria utilizada pelo conjunto 1...\n");
    destroi_conjunto(conj);
    printf("Liberando a memoria utilizada pelo conjunto 2...\n");
    destroi_conjunto(conj2);
    printf("Liberando a memoria utilizada pelo conjunto 3...\n");
    destroi_conjunto(conj3);
    printf("Liberando a memoria utilizada pelo conjunto 4...\n");
    destroi_conjunto(conj4);
    printf("Liberando a memoria utilizada pelo conjunto 5...\n");
    destroi_conjunto(conj5);
    printf("Liberando a memoria utilizada pelo conjunto_interseccao 1...\n");
    destroi_conjunto(conj_intersec1);
    printf("Liberando a memoria utilizada pelo conjunto_interseccao 2...\n");
    destroi_conjunto(conj_intersec2);
    printf("Liberando a memoria utilizada pelo conjunto_uniao 1...\n");
    destroi_conjunto(conj_uni1);
    printf("Liberando a memoria utilizada pelo conjunto_uniao 2...\n");
    destroi_conjunto(conj_uni2);
    printf("Liberando a memoria utilizada pelo conjunto_diff 1...\n");
    destroi_conjunto(conj_diff1);
    printf("Liberando a memoria utilizada pelo conjunto_diff 2...\n");
    destroi_conjunto(conj_diff2);

    printf("\n");
    printf("FIM DO TESTE\n");
    printf("------------------------------------------------------------------\n");
    printf("------------------------------------------------------------------\n");
    return 0;
}