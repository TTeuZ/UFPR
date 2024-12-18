#include "SalaAula.hpp"

SalaAula::SalaAula(std::string nome, unsigned int capacidade)
    : nome{nome}, capacidade{capacidade} {}

std::string SalaAula::getNome() { return this->nome; }

void SalaAula::setNome(std::string nome) { this->nome = nome; }

unsigned int SalaAula::getCapacidade() { return this->capacidade; }

void SalaAula::setCapcidade(unsigned int capacidade) {
    this->capacidade = capacidade;
}

// void SalaAula::adicionarDisciplina(Disciplina* disciplina) {
//     this->disciplinasMinistradas.push_back(disciplina);
// }

// void SalaAula::removerDisciplina(Disciplina* disciplina) {
//     this->disciplinasMinistradas.remove(disciplina);
// }

std::list<Disciplina*>& SalaAula::getDisciplinas() {
    return this->disciplinasMinistradas;
}