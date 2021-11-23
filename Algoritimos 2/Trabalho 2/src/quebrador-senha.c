#include "biblioteca.h"
#include <stdio.h>
#include "quebrador-senha.h"

/* Funções internas */
/*--------------------------------------------------------------------------*/

void imprime_senha (char *senha, int tamanho) {
    int count;
    for (count = 0; count < tamanho; count++) {
        printf(" %c ", senha[count]);
    }
    printf("\n");
}

int ja_contido (char *senha, int tamanho, char elemento) {
    int count;
    for (count = 0; count < tamanho; count ++) {
        if (senha[count] == elemento) return 1;
    }
    return 0;
}

int gerar_senhas_forca_bruta (char *senha, int tamanho_senha, char *caracteres, int tamanho_caracteres) {
    int count;
    /* se o tamanho da senha chegar em 6 testa para ver se é valida */
    if (tamanho_senha == 6) {
        return login (senha);
    }
    /* passa por todos os caracteres possiveis */
    for (count = 0; count < tamanho_caracteres; count++) {
        senha[tamanho_senha] = caracteres[count]; /* Adiciona o caracter da vez na posição atual da senha */
        if (gerar_senhas_forca_bruta (senha, tamanho_senha + 1, caracteres, tamanho_caracteres)) return 1; /* Se encontrou a senha sai da função */
    }
    return 0;
}

int gerar_senhas_com_poda (char *senha, int tamanho_senha, char *caracteres, int tamanho_caracteres) {
    int count;
    /* se o tamanho da senha chegar em 6 testa para ver se é valida */
    if (tamanho_senha == 6) {
        // imprime_senha (senha, tamanho_senha);
        return login (senha);
    }
    /* passa por todos os caracteres possiveis */
    for (count = 0; count < tamanho_caracteres; count++) {
        /* se o elemento ja esta na senha, nao o adiciona */
        if (!ja_contido (senha, tamanho_senha, caracteres[count])) {
            senha[tamanho_senha] = caracteres[count]; /* Adiciona o caracter da vez na posição atual da senha */
            if (gerar_senhas_com_poda (senha, tamanho_senha + 1, caracteres, tamanho_caracteres)) return 1; /* Se encontrou a senha sai da função */
        }
    }
    return 0;
}


/*--------------------------------------------------------------------------*/
/* Funções internas */

/* Retorna 1 caso tenha encontrado a senha e 0 caso contrario */
int quebrador_senha_exaustivo(){
    /* Array com os possiveis caracteres com os codigos ASCII */
    char caracteres[36] = {97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57}; 
    char senha[7]; /* Array que armazena a senha */
    int tamanho_senha = 0; /* tamanho atual da senha */

    return gerar_senhas_forca_bruta (senha, tamanho_senha, caracteres, 36);
}

/* Retorna 1 caso tenha encontrado a senha e 0 caso contrario */
int quebrador_senha_poda(){
    /* Array com os possiveis caracteres com os codigos ASCII */
    char caracteres[36] = {97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57}; 
    char senha[7]; /* Array que armazena a senha */
    int tamanho_senha = 0; /* tamanho atual da senha */

    return gerar_senhas_com_poda (senha, tamanho_senha, caracteres, 36);
}
