#ifndef PESSOA_HPP
#define PESSOA_HPP

#include <cstdint>

class Pessoa {
   public:
    bool validarCPF(uint64_t cpfTeste);

    char nome[50];
    uint64_t cpf;
    uint8_t idade;
};
#endif