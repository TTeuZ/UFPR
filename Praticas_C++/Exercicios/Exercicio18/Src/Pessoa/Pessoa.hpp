#ifndef PESSOA_H
#define PESSOA_H

#include <cstdint>
#include <string>

#include "../../Exceptions/CPFInvalidoException/CPFInvalidoException.hpp"
#include "../CPF/CPF.hpp"

namespace ufpr {
class Pessoa {
   public:
    // Constructors
    Pessoa(const std::string& nome, const CPF& cpf);
    Pessoa(const std::string& nome, const CPF& cpf, const uint8_t idade);

    // Destructor
    virtual ~Pessoa() = default;

    // Getters
    const std::string& getNome() const;
    const CPF& getCpf() const;
    uint8_t getIdade() const;

    // Setters
    void setNome(const std::string& nome);
    void setCpf(const CPF& cpf);
    void setIdade(const uint8_t idade);

   protected:
    std::string nome;
    CPF cpf;
    uint8_t idade;
};
}  // namespace ufpr
#endif