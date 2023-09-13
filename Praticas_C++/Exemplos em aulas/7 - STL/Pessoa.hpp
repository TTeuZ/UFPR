#ifndef PESSOA_HPP
#define PESSOA_HPP

#include <cstdint>
#include <string>

class Pessoa {
   public:
    // Constructors
    Pessoa();
    Pessoa(std::string nome);
    Pessoa(std::string nome, uint64_t cpf, uint8_t idade);

    // Getters
    std::string getNome();
    uint64_t getCpf();
    unsigned short getIdade();

    // Setters
    void setNome(std::string nome);
    void setCpf(uint64_t cpf);
    void setIdade(unsigned short idade);

   private:
    bool validarCPF(uint64_t cpf);

    std::string nome;
    uint64_t cpf;
    uint8_t idade;
};
#endif