#ifndef PESSOA_HPP
#define PESSOA_HPP

#include <cstdint>
#include <string>

class Pessoa {
   public:
    // Constructors
    Pessoa();
    Pessoa(std::string nomePessoa);
    Pessoa(std::string nomePessoa, uint64_t cpfPessoa, uint8_t idade);

    // Getters
    std::string getNome();
    uint64_t getCpf();
    unsigned short getIdade();

    // Setters
    void setNome(std::string novoNome);
    void setCpf(uint64_t novoCpf);
    void setIdade(unsigned short novaIdade);

   private:
    bool validarCPF(uint64_t cpfTeste);

    std::string nome;
    uint64_t cpf;
    uint8_t idade;
};
#endif