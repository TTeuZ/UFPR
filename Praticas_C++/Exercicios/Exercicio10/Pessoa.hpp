#ifndef PESSOA_H
#define PESSOA_H

#include <cstdint>
#include <string>

class Pessoa {
   public:
    // Constructors
    Pessoa();
    Pessoa(std::string nome);
    Pessoa(std::string nome, uint64_t cpf, uint8_t idade);

    // Destructor
    ~Pessoa();

    // Getters
    std::string& getNome();
    uint64_t getCpf();
    uint8_t getIdade();

    // Setters
    void setNome(std::string nome);
    void setCpf(uint64_t cpf);
    void setIdade(uint8_t idade);

   private:
    bool validarCPF(uint64_t cpf);

    std::string nome;
    uint64_t cpf;
    uint8_t idade;
};
#endif