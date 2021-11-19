#include <stdio.h>
#include <stdlib.h>
#include "liblista.h"

int main() {
    lista_t *list1, *list2; /* Declaração de 2 listas para teste */
    int count; /* contador para os loops */

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Testando a criação das listas...\n");
    printf("\n");

    list1 = cria_lista();
    printf("O endereço da primeira lista é: %p\n", &list1);
    list2 = cria_lista();
    printf("O endereço da primeira lista é: %p\n", &list2);

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Confirmando que as listas recem criadas estao vazias...\n");
    printf("\n");

    if (lista_vazia(list1))
        printf("A lista 1 esta vazia, seu tamanho é: %d\n", tamanho_lista(list1));
    else 
        printf("A lista 1 não esta vazia, seu tamanho é: %d\n", tamanho_lista(list1));

    if (lista_vazia(list2))
        printf("A lista 2 esta vazia, seu tamanho é: %d\n", tamanho_lista(list2));
    else 
        printf("A lista 2 não esta vazia, seu tamanho é: %d\n", tamanho_lista(list2));

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Inserindo elementos no inicio da lista...\n");
    printf("\n");

    for (count = 1; count <= 3; count++) {
        if (insere_inicio_lista(list1, count*2)) /* inserindo numeros multiplos de 2 */
            printf("o numero %d foi inserido corretamente na lista 1, o tamanho atual da lista é: %d\n", count*2, tamanho_lista(list1));
        else printf("não foi possivel inserir numero %d, o tamanho atual da lista 1 é: %d\n", count*2, tamanho_lista(list1));
        if (insere_inicio_lista(list2, count*3)) /* inserindo numeros multiplos de 3 */
            printf("o numero %d foi inserido corretamente na lista 2, o tamanho atual da lista é: %d\n", count*3, tamanho_lista(list1));
        else printf("não foi possivel inserir numero %d, o tamanho atual da lista 2 é: %d\n", count*3, tamanho_lista(list1));
        printf("------------------------------------------------------------------\n");
    }

    printf("\n"); 
    printf("------------------------------------------------------------------\n");
    printf("\n");

    printf("Liberando a memoria utilizada pela lista 1...\n");
    list1 = destroi_lista(list1);
    printf("lista 1 corretamente liberada, apontando para: %p\n", list1);
    printf("Liberando a memoria utilizada pela lista 2...\n");
    list2 = destroi_lista(list2);
    printf("lista 2 corretamente liberada, apontando para: %p\n", list2);

    printf("\n");
    printf("FIM DO TESTE\n");
    printf("------------------------------------------------------------------\n");
    printf("------------------------------------------------------------------\n");
    return 0;
}