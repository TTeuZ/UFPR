#include "Disciplina.hpp"

// Constructors
Disciplina::Disciplina(std::string nome, unsigned short int cargaHoraria,
                       Pessoa* professor)
    : nome{nome},
      cargaHoraria{cargaHoraria},
      professor{professor},
      qtdAlunos{0} {}

// Getters
std::string Disciplina::getNome() { return this->nome; }

int Disciplina::getCargaHoraria() { return this->cargaHoraria; }

Pessoa* Disciplina::getProfessor() { return this->professor; }

Pessoa** Disciplina::getVetorAlunos() { return this->alunos; }

unsigned short int Disciplina::getQtdAlunos() { return this->qtdAlunos; }

// Setters
void Disciplina::setNome(std::string nome) { this->nome = nome; }

void Disciplina::setCargaHoraria(unsigned int cargaHoraria) {
    this->cargaHoraria = cargaHoraria;
}

void Disciplina::setProfessor(Pessoa* professor) {
    this->professor = professor;
}

// Functions
std::string Disciplina::getNomeProfessor() {
    return this->professor->getNome();
}

bool Disciplina::adicionarAluno(Pessoa* aluno) {
    if (this->qtdAlunos == 50) return false;

    this->alunos[qtdAlunos] = aluno;
    this->qtdAlunos++;
    return true;
}

bool Disciplina::removerAluno(Pessoa* aluno) {
    unsigned int i{0};
    Pessoa* alunoAchado{nullptr};

    while (i < this->qtdAlunos && alunoAchado == nullptr) {
        if (this->alunos[i] == aluno) alunoAchado = this->alunos[i];
        i++;
    }
    if (alunoAchado == nullptr) return false;

    // Não é o melhor approach para remover, mas é o mais rapido =D
    this->alunos[i - 1] = this->alunos[qtdAlunos - 1];
    this->qtdAlunos--;

    delete alunoAchado;
    return true;
}

bool Disciplina::removerAluno(uint64_t cpf) {
    unsigned int i{0};
    Pessoa* alunoAchado{nullptr};

    while (i < this->qtdAlunos && alunoAchado == nullptr) {
        if (this->alunos[i]->getCpf() == cpf) alunoAchado = this->alunos[i];
        i++;
    }
    if (alunoAchado == nullptr) return false;

    // Não é o melhor approach para remover, mas é o mais rapido =D
    this->alunos[i - 1] = this->alunos[qtdAlunos - 1];
    this->qtdAlunos--;

    delete alunoAchado;
    return true;
}

void Disciplina::liberaAlunos() {
    for (short int i{0}; i < this->qtdAlunos; ++i) delete this->alunos[i];
}