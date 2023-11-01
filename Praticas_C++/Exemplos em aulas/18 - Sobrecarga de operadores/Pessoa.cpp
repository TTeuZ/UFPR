#include "Pessoa.hpp"

#include <iostream>
#include <stdexcept>

#include "CPFInvalidoException.hpp"

using namespace ufpr;

Pessoa::Pessoa(const std::string& nome, const CPF& cpf)
    : nome{nome}, cpf{cpf} {}

Pessoa::Pessoa(const std::string& nome, const CPF& cpf,
               const unsigned short int idade)
    : Pessoa{nome, cpf} {
    this->setIdade(idade);
}

const CPF& Pessoa::getCpf() const { return this->cpf; }

void Pessoa::setCpf(const CPF& cpf) { this->cpf = cpf; }

std::string Pessoa::getNome() const { return this->nome; }

void Pessoa::setNome(const std::string& nome) { this->nome = nome; }

unsigned short int Pessoa::getIdade() const {
    return (unsigned short int)idade;
}

void Pessoa::setIdade(const unsigned short int novaIdade) {
    if (novaIdade > 120) throw std::invalid_argument{"Idade Invalida."};
    idade = (unsigned char)novaIdade;
}