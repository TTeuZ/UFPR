#ifndef PESSOA_H
#define PESSOA_H

#include <cstdint>
#include <string>

class Pessoa {
   public:
    Pessoa();
    Pessoa(std::string nomePessoa);
    Pessoa(std::string nomePessoa, uint64_t cpfPessoa, unsigned short idade);

    uint64_t getCpf() const;
    void setCpf(uint64_t novoCpf);

    std::string getNome() const;
    void setNome(std::string novoNome);

    unsigned short int getIdade() const;
    void setIdade(unsigned short novaIdade);

   private:
    bool validarCPF(uint64_t cpfTeste);

    std::string nome;
    uint64_t cpf;
    uint8_t idade;
};
#endif