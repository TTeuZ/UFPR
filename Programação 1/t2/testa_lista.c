#include <stdio.h>
#include <stdlib.h>
#include "liblista.h"

int main() {
    lista_t *list1, *list2, *list3; /* Declaração de 3 listas para teste */
    int elemento; /* Variavel que recebe os elementos removidos das listas */
    int count; /* contador para os loops */

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Testando a criacao das listas...\n");
    printf("\n");

    list1 = cria_lista ();
    printf("O endereço da primeira lista eh: %p\n", &list1);
    list2 = cria_lista ();
    printf("O endereço da primeira lista eh: %p\n", &list2);
    list3 = cria_lista ();
    printf("O endereço da primeira lista eh: %p\n", &list3);

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Confirmando que as listas recem criadas estao vazias...\n");
    printf("\n");

    if (lista_vazia (list1))
        printf("A lista 1 esta vazia, seu tamanho eh: %d\n", tamanho_lista (list1));
    else 
        printf("A lista 1 nao esta vazia, seu tamanho eh: %d\n", tamanho_lista (list1));

    if (lista_vazia (list2))
        printf("A lista 2 esta vazia, seu tamanho eh: %d\n", tamanho_lista (list2));
    else 
        printf("A lista 2 nao esta vazia, seu tamanho eh: %d\n", tamanho_lista (list2));

    if (lista_vazia (list3))
        printf("A lista 2 esta vazia, seu tamanho eh: %d\n", tamanho_lista (list3));
    else 
        printf("A lista 2 nao esta vazia, seu tamanho eh: %d\n", tamanho_lista (list3));

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Inserindo elementos pelo inicio da lista 1...\n");
    printf("\n");

    for (count = 1; count <= 3; count++) {
        if (insere_inicio_lista (list1, count*2)) /* inserindo numeros multiplos de 2 */
            printf("O numero %d foi inserido corretamente na lista 1, o tamanho atual da lista é: %d\n", count*2, tamanho_lista (list1));
        else printf("Nao foi possivel inserir numero %d, o tamanho atual da lista 1 é: %d\n", count*2, tamanho_lista (list1));
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Inserindo elementos pelo fim da lista 2...\n");
    printf("\n");

    for (count = 1; count <= 3; count++) {
        if (insere_fim_lista (list2, count*3)) /* inserindo numeros multiplos de 3 */
            printf("O numero %d foi inserido corretamente na lista 2, o tamanho atual da lista é: %d\n", count*3, tamanho_lista (list2));
        else printf("Nao foi possivel inserir numero %d, o tamanho atual da lista 2 é: %d\n", count*3, tamanho_lista (list2));
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Verificando que os elementos recem adicionados realmente estão na lista...\n");
    printf("\n");

    for (count = 1; count <= 3; count++) {
        if (pertence_lista (list1, count*2)) /* inserindo numeros multiplos de 2 */
            printf("O numero %d esta presente na lista 1!\n", count*2);
        else printf("O numero %d nao esta presente na lista 1!\n", count*2);
    }
    printf("------------------------------------------------------------------\n");
    for (count = 1; count <= 3; count++) {
        if (pertence_lista (list2, count*3)) /* inserindo numeros multiplos de 2 */
            printf("O numero %d esta presente na lista 2!\n", count*3);
        else printf("O numero %d nao esta presente na lista 2!\n", count*3);
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Inserindo elementos pelo fim da lista 1 (continuando a contagem)...\n");
    printf("\n");

    for (count = 4; count <= 6; count++) {
        if (insere_fim_lista (list1, count*2)) /* inserindo numeros multiplos de 2 */
            printf("O numero %d foi inserido corretamente na lista 1, o tamanho atual da lista é: %d\n", count*2, tamanho_lista (list1));
        else printf("Nao foi possivel inserir numero %d, o tamanho atual da lista 1 é: %d\n", count*2, tamanho_lista (list1));
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Inserindo elementos pelo inicio da lista 2 (continuando a contagem)...\n");
    printf("\n");

    for (count = 4; count <= 6; count++) {
        if (insere_inicio_lista (list2, count*3)) /* inserindo numeros multiplos de 3 */
            printf("O numero %d foi inserido corretamente na lista 2, o tamanho atual da lista é: %d\n", count*3, tamanho_lista (list2));
        else printf("Nao foi possivel inserir numero %d, o tamanho atual da lista 2 é: %d\n", count*3, tamanho_lista (list2));
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Verificando que todos os elementos adicionados ate o momentos estao na lista...\n");
    printf("\n");

    for (count = 1; count <= 6; count++) {
        if (pertence_lista (list1, count*2)) /* inserindo numeros multiplos de 2 */
            printf("O numero %d esta presente na lista 1!\n", count*2);
        else printf("O numero %d nao esta presente na lista 1!\n", count*2);
    }
    printf("------------------------------------------------------------------\n");
    for (count = 1; count <= 6; count++) {
        if (pertence_lista (list2, count*3)) /* inserindo numeros multiplos de 2 */
            printf("O numero %d esta presente na lista 2!\n", count*3);
        else printf("O numero %d nao esta presente na lista 2!\n", count*3);
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Verificando se elementos nao adicionados estao na lista...\n");
    printf("\n");

    for (count = 1; count <= 3; count++) {
        if (pertence_lista (list1, count*11)) /* inserindo numeros multiplos de 11 */
            printf("O numero %d esta presente na lista 2!\n", count*11);
        else printf("O numero %d nao esta presente na lista 2!\n", count*11);
    }
    printf("------------------------------------------------------------------\n");
    for (count = 1; count <= 3; count++) {
        if (pertence_lista (list2, count*11)) /* inserindo numeros multiplos de 11 */
            printf("O numero %d esta presente na lista 2!\n", count*11);
        else printf("O numero %d nao esta presente na lista 2!\n", count*11);
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Inserindo elementos de maneira ordenada na lista 3...\n");
    printf("\n");

    printf("Inserindo elementos 25 e 30 na lista 3...\n");
    for (count = 5; count <= 6; count++) {
        if (insere_ordenado_lista (list3, count*5)) /* inserindo numeros multiplos de 5 */
            printf("O numero %d foi inserido corretamente na lista 3, o tamanho atual da lista é: %d\n", count*5, tamanho_lista (list3));
        else printf("Nao foi possivel inserir numero %d, o tamanho atual da lista 3 é: %d\n", count*5, tamanho_lista (list3));
    }
    printf("------------------------------------------------------------------\n");
    printf("Inserindo elementos 5 e 10 na lista 3...\n");
    for (count = 1; count <= 2; count++) {
        if (insere_ordenado_lista (list3, count*5)) /* inserindo numeros multiplos de 5 */
            printf("O numero %d foi inserido corretamente na lista 3, o tamanho atual da lista é: %d\n", count*5, tamanho_lista (list3));
        else printf("Nao foi possivel inserir numero %d, o tamanho atual da lista 3 é: %d\n", count*5, tamanho_lista (list3));
    }
    printf("------------------------------------------------------------------\n");
    printf("Inserindo elementos 15 e 20 na lista 3...\n");
    for (count = 3; count <= 4; count++) {
        if (insere_ordenado_lista (list3, count*5)) /* inserindo numeros multiplos de 5 */
            printf("O numero %d foi inserido corretamente na lista 3, o tamanho atual da lista é: %d\n", count*5, tamanho_lista (list3));
        else printf("Nao foi possivel inserir numero %d, o tamanho atual da lista 3 é: %d\n", count*5, tamanho_lista (list3));
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Verificando que todos os elementos adicionados ate o momento estao na lista 3...\n");
    printf("\n");

    for (count = 1; count <= 6; count++) {
        if (pertence_lista (list3, count*5)) /* inserindo numeros multiplos de 5 */
            printf("O numero %d esta presente na lista 2!\n", count*5);
        else printf("O numero %d nao esta presente na lista 2!\n", count*5);
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Retirando os 3 primeiros elementos da lista 1...\n");
    printf("\n");

    for (count = 1; count <= 3; count++) {
        if (retira_inicio_lista (list1, &elemento)) /* inserindo numeros multiplos de 5 */
            printf("O numero %d foi removido da lista 1! O tamanhao da lista eh: %d\n", elemento, tamanho_lista (list1));
        else printf("Nao foi possivel remover o numero %d da lista 1\n", elemento);
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Retirando os 3 ultimos elementos da lista 2...\n");
    printf("\n");

    for (count = 1; count <= 4; count++) {
        if (retira_fim_lista (list2, &elemento)) /* inserindo numeros multiplos de 5 */
            printf("O numero %d foi removido da lista 2! O tamanhao da lista eh: %d\n", elemento, tamanho_lista (list2));
        else printf("Nao foi possivel remover o numero %d da lista 2\n", elemento);
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Retirando os 3 ultimos elementos da lista 1...\n");
    printf("\n");

    for (count = 1; count <= 4; count++) {
        if (retira_fim_lista (list1, &elemento)) /* inserindo numeros multiplos de 5 */
            printf("O numero %d foi removido da lista 1! O tamanhao da lista eh: %d\n", elemento, tamanho_lista (list1));
        else printf("Nao foi possivel remover o numero, lista 1 zerada\n");
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Retirando os 3 primeiros elementos da lista 2...\n");
    printf("\n");

    for (count = 1; count <= 3; count++) {
        if (retira_inicio_lista (list2, &elemento)) /* inserindo numeros multiplos de 5 */
            printf("O numero %d foi removido da lista 2! O tamanhao da lista eh: %d\n", elemento, tamanho_lista (list2));
        else printf("Nao foi possivel remover o numero, lista 2 zerada\n");
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Validando que a lista 1 e 2 estao vazias...\n");
    printf("\n");

    if (lista_vazia (list1))
        printf("A lista 1 esta vazia, seu tamanho eh: %d\n", tamanho_lista (list1));
    else 
        printf("A lista 1 nao esta vazia, seu tamanho eh: %d\n", tamanho_lista (list1));

    if (lista_vazia (list2))
        printf("A lista 2 esta vazia, seu tamanho eh: %d\n", tamanho_lista (list2));
    else 
        printf("A lista 2 nao esta vazia, seu tamanho eh: %d\n", tamanho_lista (list2));

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("retirando elementos alternados na lista 3...\n");
    printf("\n");

    for (count = 3; count <= 4; count++) {
        if (retira_elemento_lista (list3, count*5)) /* inserindo numeros multiplos de 5 */
            printf("O numero %d foi removido corretamente da lista 3, o tamanho atual da lista é: %d\n", count*5, tamanho_lista (list3));
        else printf("Nao foi possivel remover o numero, lista 3 zerada\n");
    }
    printf("------------------------------------------------------------------\n");
    for (count = 5; count <= 6; count++) {
        if (retira_elemento_lista (list3, count*5)) /* inserindo numeros multiplos de 5 */
            printf("O numero %d foi removido corretamente da lista 3, o tamanho atual da lista é: %d\n", count*5, tamanho_lista (list3));
        else printf("Nao foi possivel remover o numero, lista 3 zerada\n");
    }
    printf("------------------------------------------------------------------\n");
    for (count = 1; count <= 3; count++) {
        if (retira_elemento_lista (list3, count*5)) /* inserindo numeros multiplos de 5 */
            printf("O numero %d foi removido corretamente da lista 3, o tamanho atual da lista é: %d\n", count*5, tamanho_lista (list3));
        else printf("Nao foi possivel remover o numero, lista 3 zerada\n");
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Validando que a lista 3 esta vazia...\n");
    printf("\n");

    if (lista_vazia (list3))
        printf("A lista 3 esta vazia, seu tamanho eh: %d\n", tamanho_lista (list3));
    else 
        printf("A lista 3 nao esta vazia, seu tamanho eh: %d\n", tamanho_lista (list3));

    printf("\n"); 
    printf("------------------------------------------------------------------\n");
    printf("\n");

    printf("Liberando a memoria utilizada pela lista 1...\n");
    list1 = destroi_lista (list1);
    printf("lista 1 corretamente liberada, apontando para: %p\n", list1);
    printf("Liberando a memoria utilizada pela lista 2...\n");
    list2 = destroi_lista (list2);
    printf("lista 2 corretamente liberada, apontando para: %p\n", list2);
    printf("Liberando a memoria utilizada pela lista 3...\n");
    list3 = destroi_lista (list3);
    printf("lista 2 corretamente liberada, apontando para: %p\n", list3);

    printf("\n");
    printf("FIM DO TESTE\n");
    printf("------------------------------------------------------------------\n");
    printf("------------------------------------------------------------------\n");
    return 0;
}