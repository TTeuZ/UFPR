#ifndef PESSOA_H
#define PESSOA_H

#include <cstdint>
#include <string>

#include "CPF.hpp"

namespace ufpr {
class Pessoa {
   public:
    Pessoa();
    Pessoa(const std::string& nomePessoa);
    Pessoa(const std::string& nomePessoa, const CPF& cpf);
    Pessoa(const std::string& nomePessoa, const CPF& cpf, uint8_t idade);

    const CPF& getCpf() const;
    void setCpf(const CPF& novoCpf);

    std::string getNome() const;
    void setNome(const std::string& novoNome);

    uint8_t getIdade() const;
    void setIdade(const uint8_t novaIdade);

   private:
    std::string nome;
    CPF cpf;
    uint8_t idade;
};
}  // namespace ufpr
#endif