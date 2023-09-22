#ifndef PESSOA_H
#define PESSOA_H

#include <cstdint>
#include <string>

class Pessoa {
   public:
    // Constructors
    Pessoa();
    Pessoa(const std::string& nome);
    Pessoa(const std::string& nome, const uint64_t cpf);
    Pessoa(const std::string& nome, const uint64_t cpf, const uint8_t idade);

    // Destructor
    ~Pessoa();

    // Getters
    const std::string& getNome() const;
    uint64_t getCpf() const;
    uint8_t getIdade() const;

    // Setters
    void setNome(const std::string& nome);
    void setCpf(const uint64_t cpf);
    void setIdade(const uint8_t idade);

   protected:
    bool validarCPF(uint64_t cpf);

    std::string nome;
    uint64_t cpf;
    uint8_t idade;
};
#endif