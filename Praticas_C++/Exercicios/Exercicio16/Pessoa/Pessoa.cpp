#include "Pessoa.hpp"

using namespace ufpr;

// Constructors
Pessoa::Pessoa(const std::string& nome) : nome{nome} {}

Pessoa::Pessoa(const std::string& nome, const uint64_t cpf) : nome{nome} {
    this->setCpf(cpf);
}

Pessoa::Pessoa(const std::string& nome, const uint64_t cpf, const uint8_t idade)
    : Pessoa{nome, cpf} {
    this->setIdade(idade);
}

// Getters
const std::string& Pessoa::getNome() const { return this->nome; }

uint64_t Pessoa::getCpf() const { return this->cpf; }

uint8_t Pessoa::getIdade() const { return (int)this->idade; }

// Setters
void Pessoa::setNome(const std::string& nome) { this->nome = nome; }

void Pessoa::setCpf(const uint64_t cpf) {
    if (!this->validarCPF(cpf)) throw CPFInvalidoException{cpf};
    this->cpf = cpf;
}

void Pessoa::setIdade(const uint8_t idade) {
    if (idade > 120)
        throw std::invalid_argument{"Idade deve ser menor que 120"};
    this->idade = idade;
}

// Functions
bool Pessoa::validarCPF(uint64_t cpf) {
    unsigned int somatorioValidaUltimo;
    unsigned int modulo;
    unsigned int somatorioValidaPenultimo{0};
    unsigned int ultimo{(unsigned int)(cpf % 10)};
    cpf = cpf / 10;
    unsigned int penultimo{(unsigned int)(cpf % 10)};
    cpf = cpf / 10;

    somatorioValidaUltimo = penultimo * 2;
    for (int i{2}; i <= 11; i++) {
        modulo = cpf % 10;
        cpf = cpf / 10;
        somatorioValidaPenultimo += modulo * i;
        somatorioValidaUltimo += modulo * (i + 1);
    }
    modulo = somatorioValidaPenultimo % 11;
    if (modulo < 2) {
        if (penultimo != 0) return false;  // cpf invalido
    } else {
        if (penultimo != 11 - modulo) return false;  // cpf invalido
    }
    modulo = somatorioValidaUltimo % 11;
    if (modulo < 2) {
        if (!ultimo) return false;  // cpf invalido
    } else {
        if (ultimo != 11 - modulo) return false;  // cpf invalido
    }
    return true;  // cpf valido
}
