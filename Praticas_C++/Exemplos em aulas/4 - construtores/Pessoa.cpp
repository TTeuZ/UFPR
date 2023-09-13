#include "Pessoa.hpp"

#include <iostream>

// Constructor lista de inicializaçao de membros
// Se tiver alguma propriedade que precisa de logica para inicializar, colocamos
// no corpo do construtor caso nâo, colocamos na lista de membros
// Isso serve para otimizar

Pessoa::Pessoa() : name{"Padrao"}, cpf{0} {};

Pessoa::Pessoa(std::string newName, uint8_t newAge) : name{newName} {
    setAge(newAge);
}

// Constructor delegating
Pessoa::Pessoa(std::string newName, uint8_t newAge, uint64_t cpf)
    : Pessoa{newName, newAge} {
    setCpf(cpf);
}

// Getters
std::string Pessoa::getName() { return name; }
uint64_t Pessoa::getCpf() { return cpf; }
unsigned short Pessoa::getAge() { return age; }

// Setters
void Pessoa::setName(std::string namePessoa) { name = namePessoa; }
void Pessoa::setCpf(uint64_t cpfPessoa) {
    cpf = validarCPF(cpfPessoa) ? cpfPessoa : 0;
}
void Pessoa::setAge(unsigned short agePessoa) { age = agePessoa; }

// Functions
bool Pessoa::validarCPF(uint64_t cpfTeste) {
    unsigned int somatorioValidaUltimo;
    unsigned int modulo;
    unsigned int somatorioValidaPenultimo{
        0};  // Iniciar variável com um valor já
    unsigned int ultimo{(unsigned int)(cpfTeste % 10)};
    cpfTeste = cpfTeste / 10;
    unsigned int penultimo{(unsigned int)(cpfTeste % 10)};
    cpfTeste = cpfTeste / 10;

    somatorioValidaUltimo = penultimo * 2;
    for (int i{2}; i <= 11; i++) {
        modulo = cpfTeste % 10;
        cpfTeste = cpfTeste / 10;
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