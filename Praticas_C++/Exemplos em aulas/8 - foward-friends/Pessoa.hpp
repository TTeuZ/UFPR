#ifndef PESSOA_H
#define PESSOA_H

#include <cstdint>
#include <string>

class Pessoa {
   public:
    Pessoa();
    Pessoa(std::string pessoa);
    Pessoa(std::string pessoa, uint64_t cpf, unsigned short idade);

    uint64_t getCpf();
    void setCpf(uint64_t cpf);

    std::string getNome();
    void setNome(std::string nome);

    unsigned short int getIdade();
    void setIdade(unsigned short idade);

   private:
    bool validarCPF(uint64_t teste);

    std::string nome;
    uint64_t cpf;
    uint8_t idade;
};
#endif