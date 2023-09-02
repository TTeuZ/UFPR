#ifndef PESSOA_H
#define PESSOA_H

#include <cstdint>
#include <string>

class Pessoa {
   public:
    // Constructors
    Pessoa();
    Pessoa(std::string pessoa);
    Pessoa(std::string pessoa, uint64_t cpf, unsigned short idade);

    // Getters
    uint64_t getCpf();
    std::string getNome();
    unsigned short int getIdade();

    // Setters
    void setCpf(uint64_t cpf);
    void setNome(std::string nome);
    void setIdade(unsigned short idade);

   private:
    bool validarCPF(uint64_t teste);

    std::string nome;
    uint64_t cpf;
    uint8_t idade;
};
#endif