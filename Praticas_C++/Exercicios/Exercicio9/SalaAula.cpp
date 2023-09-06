#include "SalaAula.hpp"

// Constructors
SalaAula::SalaAula(std::string nome, unsigned int capacidade)
    : nome{nome}, capacidade{capacidade} {}

// Getters
std::string SalaAula::getNome() { return this->nome; }

unsigned int SalaAula::getCapacidade() { return this->capacidade; }

std::list<Disciplina*>& SalaAula::getDisciplinas() {
    return this->disciplinasMinistradas;
}

// Setters
void SalaAula::setNome(std::string nome) { this->nome = nome; }

void SalaAula::setCapcidade(unsigned int capacidade) {
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
