#include <stdio.h>
#include <stdlib.h>
#include "libfila.h"

int main() {
    fila_t *fila1, *fila2; /* Declaração de 2 filas para teste */
    int elemento; /* Variavel que recebe os elementos removidos das filas */
    int count; /* contador para os loops */

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Testando a criacao das filas..\n");
    printf("\n");

    fila1 = cria_fila ();
    printf("O endereço da primeira fila eh: %p\n", &fila1);
    fila2 = cria_fila ();
    printf("O endereço da primeira fila eh: %p\n", &fila2);

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Inserindo elementos nas filas...\n");
    printf("\n");

    for (count = 1; count <= 6; count++) {
        if (insere_fila (fila1, count*2)) /* inserindo numeros multiplos de 2 */
            printf("O numero %d foi inserido corretamente na fila 1, o tamanho atual da fila é: %d\n", count*2, tamanho_fila (fila1));
        else printf("Nao foi possivel inserir numero %d, o tamanho atual da fila 1 é: %d\n", count*2, tamanho_fila (fila1));
    }
    printf("------------------------------------------------------------------\n");
    for (count = 1; count <= 6; count++) {
        if (insere_fila (fila2, count*3)) /* inserindo numeros multiplos de 3 */
            printf("O numero %d foi inserido corretamente na fila 2, o tamanho atual da fila é: %d\n", count*3, tamanho_fila (fila2));
        else printf("Nao foi possivel inserir numero %d, o tamanho atual da fila 2 é: %d\n", count*3, tamanho_fila (fila2));
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Retirando elementos das filas...\n");
    printf("\n");

    for (count = 1; count <= 7; count++) {
        if (retira_fila (fila1, &elemento)) /* inserindo numeros multiplos de 5 */
            printf("O numero %d foi removido da fila 1! O tamanhao da fila eh: %d\n", elemento, tamanho_fila (fila1));
        else printf("Nao foi possivel remover o numero, fila 1 zerada\n");
    }
    printf("------------------------------------------------------------------\n");
    for (count = 1; count <= 7; count++) {
        if (retira_fila (fila2, &elemento)) /* inserindo numeros multiplos de 5 */
            printf("O numero %d foi removido da fila 2! O tamanhao da fila eh: %d\n", elemento, tamanho_fila (fila2));
        else printf("Nao foi possivel remover o numero, fila 2 zerada\n");
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Tentando iniciar o atual com a fila vazia...\n");
    printf("\n");

    if (inicializa_atual_fila (fila1)) {
        consulta_atual_fila (fila1, &elemento);
        printf("Atual da fila 1 inicalizado corretamente, apontando para: %d\n", elemento);
    } else {
        printf("Nao foi possivel inicializar o 'atual' da fila 1, fila zerada\n");
    }
    if (inicializa_atual_fila (fila2)) {
        consulta_atual_fila (fila2, &elemento);
        printf("Atual da fila 2 inicalizado corretamente, apontando para: %d\n", elemento);
    } else {
        printf("Nao foi possivel inicializar o 'atual' da fila 2, fila zerada\n");
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Preenchendo as filas novamente...\n");
    printf("\n");

    for (count = 1; count <= 6; count++) {
        if (insere_fila (fila1, count*2)) /* inserindo numeros multiplos de 2 */
            printf("O numero %d foi inserido corretamente na fila 1, o tamanho atual da fila é: %d\n", count*2, tamanho_fila (fila1));
        else printf("Nao foi possivel inserir numero %d, o tamanho atual da fila 1 é: %d\n", count*2, tamanho_fila (fila1));
    }
    printf("------------------------------------------------------------------\n");
    for (count = 1; count <= 6; count++) {
        if (insere_fila (fila2, count*3)) /* inserindo numeros multiplos de 3 */
            printf("O numero %d foi inserido corretamente na fila 2, o tamanho atual da fila é: %d\n", count*3, tamanho_fila (fila2));
        else printf("Nao foi possivel inserir numero %d, o tamanho atual da fila 2 é: %d\n", count*3, tamanho_fila (fila2));
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Inicializando o atual das filas...\n");
    printf("\n");

    if (inicializa_atual_fila (fila1)) {
        consulta_atual_fila (fila1, &elemento);
        printf("Atual da fila 1 inicalizado corretamente, apontando para: %d\n", elemento);
    } else {
        printf("Nao foi possivel inicializar o 'atual' da fila 1, fila zerada\n");
    }
    if (inicializa_atual_fila (fila2)) {
        consulta_atual_fila (fila2, &elemento);
        printf("Atual da fila 2 inicalizado corretamente, apontando para: %d\n", elemento);
    } else {
        printf("Nao foi possivel inicializar o 'atual' da fila 2, fila zerada\n");
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Incrementando o 'atual' até o fim da fila...\n");
    printf("\n");

    for (count = 1; count <= 6; count++) {
        incrementa_atual_fila (fila1);
        if (consulta_atual_fila (fila1, &elemento)) {
            printf("Atual da fila 1 incrementado corretamente, apontando para: %d\n", elemento);
        } else {
            printf("Iterador chegou ao fim da fila 1!\n");
        }
        incrementa_atual_fila (fila2);
        if (consulta_atual_fila (fila2, &elemento)) {
            printf("Atual da fila 2 incrementado corretamente, apontando para: %d\n", elemento);
        } else {
            printf("Iterador chegou ao fim da fila 2!\n");
        }
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("retirando elementos a partir do ponteiro 'atual' apontando para o fim das filas...\n");
    printf("\n");

    for (count = 1; count <= 2; count ++) {
        if (retira_atual_fila (fila1, &elemento))
            printf("Elemento removido corretamente da fila 1!, numero removido eh: %d e o tamanho da fila 1 agora eh: %d\n", elemento, tamanho_fila (fila1));
        else
            printf("Não foi possivel remover o elemento da fila 1!\n");
    }
    printf("------------------------------------------------------------------\n");
    for (count = 1; count <= 2; count ++) {
        if (retira_atual_fila (fila2, &elemento))
            printf("Elemento removido corretamente da fila 2!, numero removido eh: %d e o tamanho da fila 2 agora eh: %d\n", elemento, tamanho_fila (fila2));
    else
        printf("Não foi possivel remover o elemento da fila 2!\n");
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Reiniciando o ponteiro 'atual' das filas...\n");
    printf("\n");

    if (inicializa_atual_fila (fila1)) {
        consulta_atual_fila (fila1, &elemento);
        printf("Atual da fila 1 inicalizado corretamente, apontando para: %d\n", elemento);
    } else {
        printf("Nao foi possivel inicializar o 'atual' da fila 1, fila zerada\n");
    }
    if (inicializa_atual_fila (fila2)) {
        consulta_atual_fila (fila2, &elemento);
        printf("Atual da fila 2 inicalizado corretamente, apontando para: %d\n", elemento);
    } else {
        printf("Nao foi possivel inicializar o 'atual' da fila 2, fila zerada\n");
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("retirando elementos a partir do ponteiro 'atual' apontando para o inicio das filas...\n");
    printf("\n");

    for (count = 1; count <= 2; count ++) {
        if (retira_atual_fila (fila1, &elemento))
            printf("Elemento removido corretamente da fila 1!, numero removido eh: %d e o tamanho da fila 1 agora eh: %d\n", elemento, tamanho_fila (fila1));
        else
            printf("Não foi possivel remover o elemento da fila 1!\n");
    }
    printf("------------------------------------------------------------------\n");
    for (count = 1; count <= 2; count ++) {
        if (retira_atual_fila (fila2, &elemento))
            printf("Elemento removido corretamente da fila 2!, numero removido eh: %d e o tamanho da fila 2 agora eh: %d\n", elemento, tamanho_fila (fila2));
    else
        printf("Não foi possivel remover o elemento da fila 2!\n");
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("retirando os demais elementos das filas...\n");
    printf("\n");

    for (count = 1; count <= 2; count++) {
        if (retira_fila (fila1, &elemento)) /* inserindo numeros multiplos de 5 */
            printf("O numero %d foi removido da fila 1! O tamanhao da fila eh: %d\n", elemento, tamanho_fila (fila1));
        else printf("Nao foi possivel remover o numero, fila 1 zerada\n");
    }
    printf("------------------------------------------------------------------\n");
    for (count = 1; count <= 2; count++) {
        if (retira_fila (fila2, &elemento)) /* inserindo numeros multiplos de 5 */
            printf("O numero %d foi removido da fila 2! O tamanhao da fila eh: %d\n", elemento, tamanho_fila (fila2));
        else printf("Nao foi possivel remover o numero, fila 2 zerada\n");
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Preenchendo as filas novamente...\n");
    printf("\n");

    for (count = 1; count <= 6; count++) {
        if (insere_fila (fila1, count*2)) /* inserindo numeros multiplos de 2 */
            printf("O numero %d foi inserido corretamente na fila 1, o tamanho atual da fila é: %d\n", count*2, tamanho_fila (fila1));
        else printf("Nao foi possivel inserir numero %d, o tamanho atual da fila 1 é: %d\n", count*2, tamanho_fila (fila1));
    }
    printf("------------------------------------------------------------------\n");
    for (count = 1; count <= 6; count++) {
        if (insere_fila (fila2, count*3)) /* inserindo numeros multiplos de 3 */
            printf("O numero %d foi inserido corretamente na fila 2, o tamanho atual da fila é: %d\n", count*3, tamanho_fila (fila2));
        else printf("Nao foi possivel inserir numero %d, o tamanho atual da fila 2 é: %d\n", count*3, tamanho_fila (fila2));
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Inicializando o atual das filas...\n");
    printf("\n");

    if (inicializa_atual_fila (fila1)) {
        consulta_atual_fila (fila1, &elemento);
        printf("Atual da fila 1 inicalizado corretamente, apontando para: %d\n", elemento);
    } else {
        printf("Nao foi possivel inicializar o 'atual' da fila 1, fila zerada\n");
    }
    if (inicializa_atual_fila (fila2)) {
        consulta_atual_fila (fila2, &elemento);
        printf("Atual da fila 2 inicalizado corretamente, apontando para: %d\n", elemento);
    } else {
        printf("Nao foi possivel inicializar o 'atual' da fila 2, fila zerada\n");
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("Incrementando o 'atual' até o meio da fila...\n");
    printf("\n");

    for (count = 1; count <= 2; count++) {
        incrementa_atual_fila (fila1);
        if (consulta_atual_fila (fila1, &elemento)) {
            printf("Atual da fila 1 incrementado corretamente, apontando para: %d\n", elemento);
        } else {
            printf("Iterador chegou ao fim da fila 1!\n");
        }
        incrementa_atual_fila (fila2);
        if (consulta_atual_fila (fila2, &elemento)) {
            printf("Atual da fila 2 incrementado corretamente, apontando para: %d\n", elemento);
        } else {
            printf("Iterador chegou ao fim da fila 2!\n");
        }
    }

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("retirando elementos a partir do ponteiro 'atual' apontando para o meio das filas...\n");
    printf("\n");

    for (count = 1; count <= 2; count ++) {
        if (retira_atual_fila (fila1, &elemento))
            printf("Elemento removido corretamente da fila 1!, numero removido eh: %d e o tamanho da fila 1 agora eh: %d\n", elemento, tamanho_fila (fila1));
        else
            printf("Não foi possivel remover o elemento da fila 1!\n");
    }
    printf("------------------------------------------------------------------\n");
    for (count = 1; count <= 2; count ++) {
        if (retira_atual_fila (fila2, &elemento))
            printf("Elemento removido corretamente da fila 2!, numero removido eh: %d e o tamanho da fila 2 agora eh: %d\n", elemento, tamanho_fila (fila2));
    else
        printf("Não foi possivel remover o elemento da fila 2!\n");
    }

    printf("\n"); 
    printf("------------------------------------------------------------------\n");
    printf("\n");

    printf("Liberando a memoria utilizada pela fila 1...\n");
    fila1 = destroi_fila (fila1);
    printf("fila 1 corretamente liberada, apontando para: %p\n", fila1);
    printf("Liberando a memoria utilizada pela fila 2...\n");
    fila2 = destroi_fila (fila2);
    printf("fila 2 corretamente liberada, apontando para: %p\n", fila2);

    printf("\n");
    printf("FIM DO TESTE\n");
    printf("------------------------------------------------------------------\n");
    printf("------------------------------------------------------------------\n");
    return 0;
}