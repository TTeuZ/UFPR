#include "Pessoa.hpp"

#include <iostream>

// Constructors
Pessoa::Pessoa() {}

Pessoa::Pessoa(std::string nome) : nome{nome} {}

Pessoa::Pessoa(std::string nome, uint64_t cpf, uint8_t idade) : Pessoa{nome} {
    setCpf(cpf);
    setIdade(idade);
}

// Destructor
Pessoa::~Pessoa(){};

// Getters
std::string& Pessoa::getNome() { return this->nome; }

uint64_t Pessoa::getCpf() { return this->cpf; }

uint8_t Pessoa::getIdade() { return (int)this->idade; }

// Setters
void Pessoa::setNome(std::string nome) { this->nome = nome; }

void Pessoa::setCpf(uint64_t cpf) {
    if (validarCPF(cpf)) {
        this->cpf = cpf;
        return;
    }
    this->cpf = 0;
    return;
}

void Pessoa::setIdade(uint8_t idade) {
    if (idade < 120)
        this->idade = (uint8_t)idade;
    else
        this->idade = 0;
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
