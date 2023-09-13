#include "Pessoa.hpp"

Pessoa::Pessoa() {}

Pessoa::Pessoa(std::string nome) : nome{nome} {}

Pessoa::Pessoa(std::string nome, uint64_t cpf, uint8_t idade) : Pessoa{nome} {
    setCpf(cpf);
    setIdade(idade);
}

uint64_t Pessoa::getCpf() {
    // retorna uma cópia do cpf
    return this->cpf;
}

void Pessoa::setCpf(uint64_t cpf) {
    if (validarCPF(cpf)) {
        this->cpf = cpf;
        return;
    }
    this->cpf = 0;  // indica que não é um cpf válido
    return;
}

std::string Pessoa::getNome() { return this->nome; }

void Pessoa::setNome(std::string nome) { this->nome = nome; }

unsigned short Pessoa::getIdade() { return (unsigned short)this->idade; }

void Pessoa::setIdade(unsigned short idade) {
    if (idade < 120)
        this->idade = (unsigned char)idade;
    else
        this->idade = 0;  // indicar erro
}

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
