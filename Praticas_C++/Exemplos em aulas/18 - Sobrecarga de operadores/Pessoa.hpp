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
    Pessoa(const std::string& nomePessoa, const CPF& cpf, unsigned short idade);

    const CPF& getCpf() const;
    void setCpf(const CPF& novoCpf);

    std::string getNome() const;
    void setNome(const std::string& novoNome);

    unsigned short int getIdade() const;
    void setIdade(const unsigned short novaIdade);

   private:
    std::string nome;
    CPF cpf;
    uint8_t idade;
};
}  // namespace ufpr
#endif