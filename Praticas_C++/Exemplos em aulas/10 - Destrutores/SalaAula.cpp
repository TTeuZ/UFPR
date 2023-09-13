#include "SalaAula.hpp"

#include <iostream>

SalaAula::SalaAula(std::string nome, unsigned int capacidade)
    : nome{nome}, capacidade{capacidade} {}

SalaAula::~SalaAula() {
    // COncertar depoiso seg fault da sequncia de deletes fazendo a disciplina
    // sair de todas as aulas
    std::cerr << "Sala de aula: " << this->getNome() << " Destruida"
              << std::endl;
}

std::string SalaAula::getNome() { return this->nome; }

void SalaAula::setNome(std::string nome) { this->nome = nome; }

unsigned int SalaAula::getCapacidade() { return this->capacidade; }

void SalaAula::setCapcidade(unsigned int capacidade) {
    this->capacidade = capacidade;
}

std::list<Disciplina*>& SalaAula::getDisciplinas() {
    return disciplinasMinistradas;
}