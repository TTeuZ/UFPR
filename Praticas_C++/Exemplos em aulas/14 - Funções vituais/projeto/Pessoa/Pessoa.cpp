#include "Pessoa.hpp"

#include <iostream>

// Constructors
Pessoa::Pessoa() {}

Pessoa::Pessoa(const std::string& nome) : nome{nome} {}

Pessoa::Pessoa(const std::string& nome, const uint64_t cpf)
    : nome{nome}, cpf{cpf} {}

Pessoa::Pessoa(const std::string& nome, const uint64_t cpf, const uint8_t idade)
    : Pessoa{nome} {
    setCpf(cpf);
    setIdade(idade);
}

// Destructor
Pessoa::~Pessoa() { std::cout << "Destruiu pessoa" << std::endl; };

// Getters
const std::string& Pessoa::getNome() const { return this->nome; }

uint64_t Pessoa::getCpf() const { return this->cpf; }

uint8_t Pessoa::getIdade() const { return (int)this->idade; }

// Setters
void Pessoa::setNome(const std::string& nome) { this->nome = nome; }

void Pessoa::setCpf(const uint64_t cpf) {
    this->cpf = cpf ? validarCPF(cpf) : 0;
}

void Pessoa::setIdade(const uint8_t idade) {
    this->idade = idade ? idade < 120 : 0;
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
