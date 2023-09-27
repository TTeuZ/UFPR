#include "SalaAula.hpp"

// Constructors
SalaAula::SalaAula(const std::string& nome, const uint16_t capacidade)
    : nome{nome}, capacidade{capacidade} {}

// Destructor
SalaAula::~SalaAula() {
    Disciplina* temp;
    while (!this->disciplinasMinistradas.empty()) {
        temp = this->disciplinasMinistradas.back();
        this->disciplinasMinistradas.pop_back();
        temp->sala = nullptr;
    }
}

// Getters
const std::string& SalaAula::getNome() const { return this->nome; }

uint16_t SalaAula::getCapacidade() const { return this->capacidade; }

const std::list<Disciplina*>& SalaAula::getDisciplinas() const {
    return this->disciplinasMinistradas;
}

// Setters
void SalaAula::setNome(const std::string& nome) { this->nome = nome; }

void SalaAula::setCapacidade(const uint16_t capacidade) {
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
