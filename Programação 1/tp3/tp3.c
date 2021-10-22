#include <stdio.h>

#define MAX 100

/* Função que recebe um vetor e o preenche com os valores inputados pelo usuário e retorna o tamanho dele */
int read_array(int vetor[]) {
    int entrance_array_length, count;

    scanf("%d", &entrance_array_length);

    if (entrance_array_length > MAX) return 0;
    for (count = 0; count < entrance_array_length; count++) {
        scanf("%d", &vetor[count]);
    }
    return entrance_array_length;
}

/* Função que preenche os numeros que serão validados como possivel seguencia e retorna seu tamanho*/
int fill_sequence_array(int sequence[], int vetor[], int initial_pos, int max) {
    int count;
    for (count = 0; count < max; count++) {
        sequence[count] = vetor[count+initial_pos];
    }
    return count+initial_pos; // retorna seu tamanho
}

/* Função que verifica se a seguencia indicada possui uma equivalencia nas proximas posições do array */
int has_double_sequence(int sequence[], int vetor[], int pos, int max) {
    int count;
    int equal_numbers = 0;
    for (count = 0; count < max; count++) {
        if (sequence[count] == vetor[pos+count]) ++equal_numbers; // verifica apenas as casas posteriores a posição final do array da seguencia escolhida
    }

    if (equal_numbers == count) return 0; // se a soma for igual ao numero de casas do array retorna que achou a seguencia.
    return -1;
}

/* Função que verifica cada subsequencia que pode ser criada com as proximas casas do array, buscando uma equivalencia */
int find_sequence(int vetor[], int sequence_max_lenght, int array_length) {
    int pos = 0;
    int count_by_beggining = 0;
    int final_pos, has_sequence;
    int sequence[MAX];

    while (count_by_beggining <= array_length) { // laço que verifica se o tamanho do array que vai ser testado não ultrapassa o tamanho total do array inputado pelo usuario
        int count_by_ending = sequence_max_lenght;
        final_pos = fill_sequence_array(sequence, vetor, pos, sequence_max_lenght); // preenche o array da vez e armazena seu tamanho
        
        while (count_by_ending <= array_length) { // Laço para verificar se o ultimo array possivel foi testado entre o tamanho disponivel
            if (has_double_sequence(sequence, vetor, final_pos, sequence_max_lenght) == 0) return pos; // caso encontre uma seguencia ele ja encerra o looping
            final_pos++; // caso não encontre, testa para o proximo array, caso ele 'caiba' dentro do array inputado
            count_by_ending += sequence_max_lenght - 1;
        }
        pos++; // Caso não tenha encontrado uma seguencia, testa novamente agora criando a subseguencia a partir da proxima casa do array.
        count_by_beggining = count_by_beggining + sequence_max_lenght - 1;
    }
    return -1;
}

void main() {
    int vetor[MAX];
    int array_length, sequence_lenght, sequence_position, count;

    array_length = read_array(vetor);
    if (array_length <= 0) { // verifica se o vetor indicado é vaziou ou extrapolou o limite de 100
        printf ("O array é vazio ou ultrapassou o limite de tamanho\n");
        return;
    }

    sequence_lenght = array_length / 2; // inicia o valor maximo da primeira subsequencia como sendo a metade do tamanho do array inputado (arredondando para baixo)
    count = sequence_lenght; 
    while (count >= 2) { // caso a sequencia seja menor que 2, encerra o algoritimo
        sequence_position = find_sequence(vetor, sequence_lenght, array_length);
        if (sequence_position != -1) count = 0; // se a função retornar um valor diferente de -1, significa que uma seguencia foi encontrada.

        sequence_lenght = sequence_lenght - 1;
        count = count - 1;
    }
    // Printa  a resposta do algoritimo
    if (sequence_position == -1) printf("nenhuma\n");
    else printf ("%d %d\n", sequence_position+1, sequence_lenght+1); // soma + 1 por conta dos arrays começarem em 0
}