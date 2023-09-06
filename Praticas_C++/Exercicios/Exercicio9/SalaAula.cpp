#include "SalaAula.hpp"

// Constructors
SalaAula::SalaAula(std::string nome, uint16_t capacidade)
    : nome{nome}, capacidade{capacidade} {}

// Getters
std::string SalaAula::getNome() { return this->nome; }

uint16_t SalaAula::getCapacidade() { return this->capacidade; }

std::list<Disciplina*>& SalaAula::getDisciplinas() {
    return this->disciplinasMinistradas;
}

// Setters
void SalaAula::setNome(std::string nome) { this->nome = nome; }

void SalaAula::setCapacidade(uint16_t capacidade) {
    this->capacidade = capacidade;
}

// Functions
void SalaAula::adicionarDisciplina(Disciplina* disciplina) {
    disciplina->setSalaAula(this);
}

void SalaAula::removerDisciplina(Disciplina* disciplina) {
    this->disciplinasMinistradas.remove(disciplina);
    disciplina->sala = nullptr;
}
