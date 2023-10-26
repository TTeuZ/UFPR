#include "SalaAula.hpp"

// Constructors
SalaAula::SalaAula(const std::string& nome, const uint16_t capacidade)
    : nome{nome} {
    this->setCapacidade(capacidade);
}

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
    if (capacidade <= 0)
        throw NaoPositivoException{
            "Capacidade nâo pode ser menor ou igual a zero"};

    this->capacidade = capacidade;
}

// Functions
void SalaAula::adicionarDisciplina(Disciplina* disciplina) {
    if (disciplina == nullptr)
        throw NullPointerException{"Disciplina não pode ser nula"};

    disciplina->setSalaAula(this);
}

void SalaAula::removerDisciplina(Disciplina* disciplina) {
    if (disciplina == nullptr)
        throw NullPointerException{"Disciplina não pode ser nula"};

    this->disciplinasMinistradas.remove(disciplina);
    disciplina->sala = nullptr;
}
