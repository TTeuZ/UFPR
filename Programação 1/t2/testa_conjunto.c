#include <stdio.h>
#include <stdlib.h>
#include "libconjunto.h"

int main () {
    conjunto_t *conj, *conj2, *conj3, *conj4, *conj5; /* Declaração dos 5 conjuntos */
    conjunto_t *conj_copy1, *conj_copy2; /* Declaração de 2 conjuntos par armazenarem copias */
    conjunto_t *subconj1, *subconj2, *subconj3; /* Declaração de 3 conjuntos par armazenarem os subconjuntos */
    conjunto_t *conj_intersec1, *conj_intersec2; /* Declaração de 2 conjuntos para intersecções */
    conjunto_t *conj_uni1, *conj_uni2; /* Declaração de 2 conjuntos para uniões */
    conjunto_t *conj_diff1, *conj_diff2; /* Declaração de 2 conjuntos para as diferencas */
    int count; /* Contador para as iterações */
    int ret; /* variavel para armazenar retornos de funcoes */
    int elemento1, elemento2; /* inteiro utilizado para receber o retorno do ponteiro ptr */

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

    if (conjunto_vazio(conj) == 1) 
        printf("O Conjunto 1 está vazio!, sua cardinalidade é %d\n", cardinalidade(conj));
    else printf("O Conjunto 1 não está vazio!, sua cardinalidade é %d\n", cardinalidade(conj));
    if (conjunto_vazio(conj2) == 1) 
        printf("O Conjunto 2 está vazio!, sua cardinalidade é %d\n", cardinalidade(conj2));
    else printf("O Conjunto 2 não está vazio!, sua cardinalidade é %d\n", cardinalidade(conj2));
    if (conjunto_vazio(conj3) == 1) 
        printf("O Conjunto 3 está vazio!, sua cardinalidade é %d\n", cardinalidade(conj3));
    else printf("O Conjunto 3 não está vazio!, sua cardinalidade é %d\n", cardinalidade(conj3));

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("inserindo a primeira metade de elementos dos conjuntos...\n");
    printf("\n");

    /* Iniciando a inserção da primeira metade de elementos no vetor */
    for (count = 0; count < 50; count++)  /* inserindo elemento somando de 1 em 1 */
        insere_conjunto (conj, count);
    for (count = 0; count < 25; count++) /* inserindo elemento somando de 2 em 2 */
        insere_conjunto (conj2, count*2);
    for (count = 0; count < 5; count++)  /* inserindo elemento somando de 5 em 5 */
        insere_conjunto (conj3, count*5);

    printf("------------------------------------------------------------------\n");
    printf("validando que o conjunto não está vazio...\n");
    printf("\n");

    if (conjunto_vazio(conj) == 1) 
        printf("O Conjunto 1 está vazio!, sua cardinalidade é %d\n", cardinalidade(conj));
    else printf("O Conjunto 1 não está vazio!, sua cardinalidade é %d\n", cardinalidade(conj));
    if (conjunto_vazio(conj2) == 1) 
        printf("O Conjunto 2 está vazio!, sua cardinalidade é %d\n", cardinalidade(conj2));
    else printf("O Conjunto 2 não está vazio!, sua cardinalidade é %d\n", cardinalidade(conj2));
    if (conjunto_vazio(conj3) == 1) 
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
        ret = insere_conjunto (conj, count);
        if (ret == -1) 
            printf("Não é possivel adicionar o elemento, conjunto cheio, retorno: %d\n", ret);
        else if(ret == 0)
            printf("Não é possivel adicionar o elemento, elemento ja existente, retorno: %d\n", ret);
    }
    for (count = 0; count < 2; count++) { /* inserindo elementos diferentes */
        ret = insere_conjunto (conj2, count*2);
        if (ret == -1) 
            printf("Não é possivel adicionar o elemento, conjunto cheio, retorno: %d\n", ret);
        else if(ret == 0)
            printf("Não é possivel adicionar o elemento, elemento ja existente, retorno: %d\n", ret);
    }
    for (count = 0; count < 2; count++) { /* inserindo elementos diferentes */
        ret = insere_conjunto (conj3,count*5);
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
        insere_conjunto (conj2, count);
        count = count + 2;
    } 
    for (count = 1; count <= 5; count++)  /* Adicionando numeros multiplos de 6 */
        insere_conjunto (conj3, count*6);

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
        retira_conjunto (conj2, count);
        count = count + 2;
    } 
    for (count = 1; count <= 5; count++)  /* removendo numeros multiplos de 6 */
        retira_conjunto (conj3, count*6);

    printf("------------------------------------------------------------------\n");
    printf("Imprimindo conjuntos apos a remocao dos elementos extras...\n");
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
        retira_conjunto (conj, count);
    for (count = 0; count < 25; count++)  /* retirando elemento somando de 2 em 2 */
        retira_conjunto (conj2, count*2);
    for (count = 0; count < 5; count++)  /* retirando elemento somando de 5 em 5 */
        retira_conjunto (conj3, count*5);

    printf("------------------------------------------------------------------\n");
    printf("validando que o conjunto está novamente vazio...\n");
    printf("\n");

    if (conjunto_vazio(conj) == 1) 
        printf("O Conjunto 1 está vazio!, sua cardinalidade é %d\n", cardinalidade(conj));
    else printf("O Conjunto 1 não está vazio!, sua cardinalidade é %d\n", cardinalidade(conj));
    if (conjunto_vazio(conj2) == 1) 
        printf("O Conjunto 2 está vazio!, sua cardinalidade é %d\n", cardinalidade(conj2));
    else printf("O Conjunto 2 não está vazio!, sua cardinalidade é %d\n", cardinalidade(conj2));
    if (conjunto_vazio(conj3) == 1) 
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
    printf("Tentando remover elementos com o conjunto vazio...\n");
    printf("\n");

    for (count = 0; count < 2; count++) {
        if (retira_conjunto(conj, count))
            printf("Elemento retirado com sucesso!\n");
        else printf("Impossivel retirar! Conjunto vazio ou elemento inexistente!\n");
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Criando subconjunto com o conjunto vazio...\n");
    printf("\n");

    subconj1 = cria_subconjunto(conj, 10);
    printf("validando que o conjunto retornado é vazio...\n");
    if (conjunto_vazio(conj) == 1) 
        printf("O Sub-conjunto 1 está vazio!, sua cardinalidade é %d\n", cardinalidade(subconj1));

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("inserindo elemento até o max do conjunto...\n");
    printf("\n");

    /* Iniciando a inserção dos elementoss no conjunto */
    for (count = 0; count < 100; count++)  /* inserindo elemento somando de 1 em 1, soma */
        insere_conjunto (conj, count);
    for (count = 0; count < 50; count++) /* inserindo elemento somando de 2 em 2, soma */
        insere_conjunto (conj2, count*2);
    for (count = 0; count < 10; count++)  /* inserindo elemento somando de 5 em 5, soma */
        insere_conjunto (conj3, count*5);

    printf("------------------------------------------------------------------\n");
    printf("validando que o conjunto não está novamente vazio...\n");
    printf("\n");

    if (conjunto_vazio(conj) == 1) 
        printf("O Conjunto 1 está vazio!, sua cardinalidade é %d\n", cardinalidade(conj));
    else printf("O Conjunto 1 não está vazio!, sua cardinalidade é %d\n", cardinalidade(conj));
    if (conjunto_vazio(conj2) == 1) 
        printf("O Conjunto 2 está vazio!, sua cardinalidade é %d\n", cardinalidade(conj2));
    else printf("O Conjunto 2 não está vazio!, sua cardinalidade é %d\n", cardinalidade(conj2));
    if (conjunto_vazio(conj3) == 1) 
        printf("O Conjunto 3 está vazio!, sua cardinalidade é %d\n", cardinalidade(conj3));
    else printf("O Conjunto 3 não está vazio!, sua cardinalidade é %d\n", cardinalidade(conj3));

    printf("\n");
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
        ret = insere_conjunto (conj, (count+1)*100);
        if (ret == -1) 
            printf("Não é possivel adicionar o elemento, conjunto cheio, retorno: %d\n", ret);
        else if(ret == 0)
            printf("Não é possivel adicionar o elemento, elemento ja existente, retorno: %d\n", ret);
    }
    for (count = 0; count < 2; count++) { /* inserindo elementos diferentes */
        ret = insere_conjunto (conj2, (count+1)*100);
        if (ret == -1) 
            printf("Não é possivel adicionar o elemento, conjunto cheio, retorno: %d\n", ret);
        else if(ret == 0)
            printf("Não é possivel adicionar o elemento, elemento ja existente, retorno: %d\n", ret);
    }
    for (count = 0; count < 2; count++) { /* inserindo elementos diferentes */
        ret = insere_conjunto (conj3, (count+1)*100);
        if (ret == -1) 
            printf("Não é possivel adicionar o elemento, conjunto cheio, retorno: %d\n", ret);
        else if(ret == 0)
            printf("Não é possivel adicionar o elemento, elemento ja existente, retorno: %d\n", ret);
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Criando subconjunto com n maior que a cardinalidade do conjunto 2...\n");
    printf("\n");

    subconj2 = cria_subconjunto(conj2, 51);
    printf("validando que o conjunto retornado é uma copia do conjunto 2...\n");
    if (sao_iguais(conj2, subconj2) == 1)
        printf("O subconjunto 2 é igual ao conjunto 2!\n");
    else printf("O subconjunto 2 não é igual ao conjunto 2!\n");

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Criando subconjunto com n menor que a cardinalidade do conjunto 3...\n");
    printf("\n");

    subconj3 = cria_subconjunto(conj3, 5);
    printf("printando o conjunto para validar que ele possui elementos aleatorios do conjunto 3...\n");
    imprime(subconj3);

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Criando copias dos conjuntos...\n");
    printf("\n");

    printf("copiando conjunto 1...\n");
    conj_copy1 = cria_copia(conj);
    printf("copiando conjunto 2...\n");
    conj_copy2 = cria_copia(conj2);
    printf("\n");
    printf("Verificando que as copias são iguais...\n");
    if (sao_iguais(conj, conj_copy1) == 1)
        printf("O conjuto 1 é igual a sua copia!\n");
    else printf("O conjunto 1 não é igual a sua copia!\n");
    if (sao_iguais(conj2, conj_copy2) == 1)
        printf("O conjuto 2 é igual a sua copia!\n");
    else printf("O conjunto 2 não é iqual a sua copia!\n");

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
        if (pertence(conj, count) == 1)
            printf("O elemento %d pertence ao conjunto 1!\n", count);
        else printf("O elemento %d não pertence ao conjunto 1!\n", count);
        if (pertence(conj2, count) == 1)
            printf("O elemento %d pertence ao conjunto 2!\n", count);
        else printf("O elemento %d não pertence ao conjunto 2!\n", count);
        if (pertence(conj3, count) == 1)
            printf("O elemento %d pertence ao conjunto 3!\n", count);
        else printf("O elemento %d não pertence ao conjunto 3!\n", count);
    }

    printf("------------------------------------------------------------------\n");

       for (count = 1; count <= 2; count ++) { /* Testando o pertecimento de elementos em seguencia 2,4 */
        if (pertence(conj, count*2) == 1)
            printf("O elemento %d pertence ao conjunto 1!\n", count*2);
        else printf("O elemento %d não pertence ao conjunto 1!\n", count*2);
        if (pertence(conj2, count*2) == 1)
            printf("O elemento %d pertence ao conjunto 2!\n", count*2);
        else printf("O elemento %d não pertence ao conjunto 2!\n", count*2);
        if (pertence(conj3, count*2) == 1)
            printf("O elemento %d pertence ao conjunto 3!\n", count*2);
        else printf("O elemento %d não pertence ao conjunto 3!\n", count*2);
    }

    printf("------------------------------------------------------------------\n");

       for (count = 1; count <= 2; count ++) { /* Testando o pertecimento de elementos em seguencia 5,10 */
        if (pertence(conj, count*5) == 1)
            printf("O elemento %d pertence ao conjunto 1!\n", count*5);
        else printf("O elemento %d não pertence ao conjunto 1!\n", count*5);
        if (pertence(conj2, count*5) == 1)
            printf("O elemento %d pertence ao conjunto 2!\n", count*5);
        else printf("O elemento %d não pertence ao conjunto 2!\n", count*5);
        if (pertence(conj3, count*5) == 1)
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
        insere_conjunto (conj4, count);
        insere_conjunto (conj5, count);
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
    printf("Realocando o tamanho dos conjuntos...\n");
    printf("\n");

    if (redimensiona(conj2) == 1) 
        printf("Conjunto 2 realocado corretamente!\n");
    else printf("Falha ao realocar o conjunto 2!\n");
    if (redimensiona(conj3) == 1) 
        printf("Conjunto 3 realocado corretamente!\n");
    else printf("Falha ao realocar o conjunto 3!\n");

    printf("\n"); 
    printf("Preenchendo o conjunto 2 até seu novo limite...\n");

    for (count = 50; count < 101; count++) /* inserindo elemento somando de 2 em 2, soma */
        if (insere_conjunto (conj2, count*2) == -1)
            printf("Espaço maximo ultrapassado!, a cardinalidade atual do conjunto 2 é: %d\n", cardinalidade(conj2));

    printf("\n"); 
    printf("Preenchendo o conjunto 3 até seu novo limite...\n");
    
    for (count = 10; count < 21; count++)  /* inserindo elemento somando de 5 em 5, soma */
        if (insere_conjunto (conj3, count*5) == -1)
            printf("Espaço maximo ultrapassado!, a cardinalidade atual do conjunto 3 é: %d\n", cardinalidade(conj3));

    printf("\n"); 
    printf("Imprimindo o conjunto pos a inserção...\n");

    printf("Conjunto 2: ");
    imprime(conj2);
    printf("Conjunto 3: ");
    imprime(conj3);

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Inicializando os ponteiros dos conjuntos...\n");
    printf("\n");

    iniciar_iterador(conj);
    iniciar_iterador(conj2);
    printf("Ponteiros inicializados!\n");

    printf("\n");
    printf("Incrementando os ponteiros dos conjuntos e imprimindo seus respectivos elementos...\n");
    printf("\n");

    for (count = 0; count <= 10; count++) {
        incrementar_iterador(conj, &elemento1);
        printf("Iterador do conjunto 1 em %d, o elemento respectivo eh: %d\n", count+1, elemento1);
        incrementar_iterador(conj2, &elemento2);
        printf("Iterador do conjunto 2 em %d, o elemento respectivo eh: %d\n", count+1, elemento2);
    }

    printf("\n");
    printf("Incrementando os ponteiros até o limite...\n");
    printf("\n");

    for (count = 1; count <= 90; count++) {
        if (!incrementar_iterador(conj2, &elemento1)) {
            printf("Chegou ao fim do conjunto!\n");
        }
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Removendo elementos aleatorios do conjunto...\n");
    printf("\n");

    for (count = 0; count < 2; count ++)
        if (retirar_um_elemento(conj3)) {
            printf("Imprimindo o conjunto 3 apos a remoção aleatoria...\n");
            imprime (conj3);
        }
        
    printf("\n"); 
    printf("------------------------------------------------------------------\n");
    printf("\n");

    /* Liberando a memoria alocada dinamicamente para os 3 conjuntos durante a execução do teste */
    printf("Liberando a memoria utilizada pelo conjunto 1...\n");
    conj = destroi_conjunto(conj);
    printf("Liberando a memoria utilizada pelo conjunto 2...\n");
    conj2 = destroi_conjunto(conj2);
    printf("Liberando a memoria utilizada pelo conjunto 3...\n");
    conj3 = destroi_conjunto(conj3);
    printf("Liberando a memoria utilizada pelo conjunto 4...\n");
    conj4 = destroi_conjunto(conj4);
    printf("Liberando a memoria utilizada pelo conjunto 5...\n");
    conj5 = destroi_conjunto(conj5);
    printf("Liberando a memoria utilizada pelo conjunto_copia 1...\n");
    conj_copy1 = destroi_conjunto(conj_copy1);
    printf("Liberando a memoria utilizada pelo conjunto_copia 2...\n");
    conj_copy2 = destroi_conjunto(conj_copy2);
    printf("Liberando a memoria utilizada pelo subconjunto 1...\n");
    subconj1 = destroi_conjunto(subconj1);
    printf("Liberando a memoria utilizada pelo subconjunto 2...\n");
    subconj2 = destroi_conjunto(subconj2);
    printf("Liberando a memoria utilizada pelo subconjunto 3...\n");
    subconj3 = destroi_conjunto(subconj3);
    printf("Liberando a memoria utilizada pelo conjunto_interseccao 1...\n");
    conj_intersec1 = destroi_conjunto(conj_intersec1);
    printf("Liberando a memoria utilizada pelo conjunto_interseccao 2...\n");
    conj_intersec2 = destroi_conjunto(conj_intersec2);
    printf("Liberando a memoria utilizada pelo conjunto_uniao 1...\n");
    conj_uni1 = destroi_conjunto(conj_uni1);
    printf("Liberando a memoria utilizada pelo conjunto_uniao 2...\n");
    conj_uni2 = destroi_conjunto(conj_uni2);
    printf("Liberando a memoria utilizada pelo conjunto_diff 1...\n");
    conj_diff1 = destroi_conjunto(conj_diff1);
    printf("Liberando a memoria utilizada pelo conjunto_diff 2...\n");
    conj_diff2 = destroi_conjunto(conj_diff2);

    printf("\n");
    printf("FIM DO TESTE\n");
    printf("------------------------------------------------------------------\n");
    printf("------------------------------------------------------------------\n");
    return 0;
}