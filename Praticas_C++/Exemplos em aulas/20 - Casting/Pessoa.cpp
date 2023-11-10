#include "Pessoa.hpp"

#include <iostream>
#include <stdexcept>

#include "CPFInvalidoException.hpp"

using namespace ufpr;

Pessoa::Pessoa(const std::string& nome, const CPF& cpf)
    : nome{nome}, cpf{cpf} {}

Pessoa::Pessoa(const std::string& nome, const CPF& cpf, const uint8_t idade)
    : Pessoa{nome, cpf} {
    this->setIdade(idade);
}

const CPF& Pessoa::getCpf() const { return this->cpf; }

void Pessoa::setCpf(const CPF& cpf) { this->cpf = cpf; }

std::string Pessoa::getNome() const { return this->nome; }

void Pessoa::setNome(const std::string& nome) { this->nome = nome; }

uint8_t Pessoa::getIdade() const { return static_cast<uint8_t>(idade); }

void Pessoa::setIdade(const uint8_t novaIdade) {
    if (novaIdade > 120) throw std::invalid_argument{"Idade Invalida."};
    idade = static_cast<uint8_t>(novaIdade);
}