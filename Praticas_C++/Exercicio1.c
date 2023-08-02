#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define NAME_MAX 50
typedef struct person {
    char name[NAME_MAX];
    uint64_t cpf;
    uint8_t age;
} person_t;

void flush_stdin() {
    int buf = 0;
    while (buf != '\n' && buf != EOF) buf = getchar();
}

int countDigits(uint64_t cpf) {
    int count = 0;

    while (cpf != 0) {
        count++;
        cpf = cpf / 10;
    }
    return count;
}

int validarCPF(uint64_t cpf) {
    uint16_t d1, d2, d3, d4, d5, d6, d7, d8, d9, v1, v2, verifier;
    if (countDigits(cpf) < 10) return 0;

    // pegando cada digito
    d1 = countDigits(cpf) == 10 ? 0 : cpf / 10000000000;
    d2 = (cpf / 1000000000) % 10;
    d3 = (cpf / 100000000) % 10;
    d4 = (cpf / 10000000) % 10;
    d5 = (cpf / 1000000) % 10;
    d6 = (cpf / 100000) % 10;
    d7 = (cpf / 10000) % 10;
    d8 = (cpf / 1000) % 10;
    d9 = (cpf / 100) % 10;
    verifier = cpf % 100;

    v1 = ((d1 * 10) + (d2 * 9) + (d3 * 8) + (d4 * 7) + (d5 * 6) + (d6 * 5) +
          (d7 * 4) + (d8 * 3) + (d9 * 2)) %
         11;
    v1 = v1 <= 2 ? 0 : 11 - v1;

    v2 = ((d1 * 11) + (d2 * 10) + (d3 * 9) + (d4 * 8) + (d5 * 7) + (d6 * 6) +
          (d7 * 5) + (d8 * 4) + (d9 * 3) + (v1 * 2)) %
         11;
    v2 = v2 <= 2 ? 0 : 11 - v2;

    return (v1 * 10 + v2) == verifier;
}

int main() {
    person_t persons[3];
    int count, isValid, isNumber;

    fprintf(stdout, "Informe os dados das 3 pessoas:\n");
    for (count = 0; count < 3; ++count) {
        fprintf(stdout, "Pessoa %d: \n", count + 1);

        fprintf(stdout, "Nome: ");
        fscanf(stdin, "%[^\n]", persons[count].name);

        do {
            flush_stdin();
            fprintf(stdout, "Idade: ");
            isValid = fscanf(stdin, "%hhd", &persons[count].age);

            if (!isValid)
                fprintf(stdout, "Por favor, forneça uma idade válida! \n");
        } while (!isValid);

        do {
            flush_stdin();
            fprintf(stdout, "CPF (Apenas numeros): ");
            isNumber = fscanf(stdin, "%ld", &persons[count].cpf);
            if (isNumber) isValid = validarCPF(persons[count].cpf);

            if (!isNumber || !isValid)
                fprintf(stdout, "Por favor, forneça um cpf válido! \n");
        } while (!isNumber || !isValid);

        fprintf(stdout, "\n");
        flush_stdin();
    }

    fprintf(stdout, "As informações dadas foram:\n");
    for (count = 0; count < 3; ++count) {
        fprintf(stdout, "Pessoa %d: \n", count + 1);
        fprintf(stdout, "Nome: %s\n", persons[count].name);
        fprintf(stdout, "Idade: %d\n", persons[count].age);
        fprintf(stdout, "CPF: %s%ld\n",
                countDigits(persons[count].cpf) == 10 ? "0" : "",
                persons[count].cpf);
        fprintf(stdout, "\n");
    }

    return 0;
}