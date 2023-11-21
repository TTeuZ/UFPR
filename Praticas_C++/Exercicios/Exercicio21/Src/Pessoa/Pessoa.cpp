#include "Pessoa.hpp"

namespace ufpr {
// Constructors
Pessoa::Pessoa(const std::string& nome, const CPF& cpf) : nome{nome}, cpf{cpf} {}

Pessoa::Pessoa(const std::string& nome, const CPF& cpf, const uint8_t idade) : Pessoa{nome, cpf} {
    this->setIdade(idade);
}

// Getters
const std::string& Pessoa::getNome() const { return this->nome; }

const CPF& Pessoa::getCpf() const { return this->cpf; }

unsigned short int Pessoa::getIdade() const { return static_cast<unsigned short int>(this->idade); }

// Setters
void Pessoa::setNome(const std::string& nome) { this->nome = nome; }

void Pessoa::setCpf(const CPF& cpf) { this->cpf = cpf; }

void Pessoa::setIdade(const uint8_t idade) {
    if (idade > 120) throw std::invalid_argument{"Idade deve ser menor que 120"};
    this->idade = idade;
}

// Operators
bool Pessoa::operator==(const Pessoa& outro) const {
    bool equal{true};

    if (this->cpf != outro.cpf || this->nome != outro.nome) equal = false;
    return equal;
}

bool Pessoa::operator!=(const Pessoa& outro) const { return !(*this == outro); }
}  // namespace ufpr