#include "biblioteca.h"
#include "quebrador-senha.h"

/* Funções internas */
/*--------------------------------------------------------------------------*/
/* Retorna 1 se o elemento for uma letra e 0 caso o contrario */
int eh_letra (char elemento) {
    if (elemento >= 97 && elemento <= 122) return 1;
    return 0;
}

/* Retorna 1 se o elemento for uma numeroe 0 caso o contrario */
int eh_numero (char elemento) {
    if (elemento >= 48 && elemento <= 57) return 1;
    return 0;
}

/* Retorna 1 se o elemento ja esta contido na senha e 0 caso o contrario */
int ja_contido (char *senha, int tamanho, char elemento) {
    int count;
    /* Passa por todos os caracteres existentes na senha */
    for (count = 0; count < tamanho; count ++) 
        if (senha[count] == elemento) return 1;
    return 0;
}

/* veririfca se cumpre a regra de possuir 2 letras e 2 numeros */
int libera_por_letra_numero (char *senha, int tamanho, char elemento) {
    int count;
    int qtd_letras = 0; /* countador da quantidad de letras */
    int qtd_numeros = 0; /* countador da quantidad de numeros */
    if (tamanho <= 3) return 1; /* Se o tamanho for menor a 3, não faz verificação */
    /* armazena a quantidade de letras e numeros da senha */
    for (count = 0; count < tamanho; count++) {
        if (eh_letra (senha[count])) qtd_letras++;
        else qtd_numeros++;
    }
    if (qtd_letras >= 4 && eh_letra (elemento)) return 0; /* Se a senha possui 4 ou mais letras é quer adicionarr outra, retorna 0 */
    if (qtd_numeros >= 4 && eh_numero (elemento)) return 0; /* Se a senha possui 4 ou mais numeros é quer adicionarr outr0, retorna 0 */
    if (qtd_letras >= 2 && qtd_numeros >= 2) return 1; /* se ja possuir 2 letras/numeros retorna 1 */
    return 1;
}
/*--------------------------------------------------------------------------*/
/* Funções geradoras */

/* Funções geradoras */
/*--------------------------------------------------------------------------*/
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
        return login (senha);
    }
    /* passa por todos os caracteres possiveis */
    for (count = 0; count < tamanho_caracteres; count++) {
        /* se o elemento ja esta na senha e se condiz com as demais especificacoes, nao o adiciona */
        if (!ja_contido (senha, tamanho_senha, caracteres[count]) && libera_por_letra_numero (senha, tamanho_senha, caracteres[count])) {
            senha[tamanho_senha] = caracteres[count]; /* Adiciona o caracter da vez na posição atual da senha */
            if (gerar_senhas_com_poda (senha, tamanho_senha + 1, caracteres, tamanho_caracteres)) return 1; /* Se encontrou a senha sai da função */
        }
    }
    return 0;
}
/*--------------------------------------------------------------------------*/
/* Funções geradoras */

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
