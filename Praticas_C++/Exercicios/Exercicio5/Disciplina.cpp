#include "Disciplina.hpp"

// Constructors
Disciplina::Disciplina(std::string nomeDisciplina,
                       unsigned short int cargaHoraria, Pessoa* professor)
    : nome{nomeDisciplina},
      cargaHoraria{cargaHoraria},
      professor{professor},
      qtdAlunos{0} {
    alunos = new Pessoa*[50];
}

// Getters
std::string Disciplina::getNome() { return nome; }

int Disciplina::getCargaHoraria() { return cargaHoraria; }

Pessoa* Disciplina::getProfessor() { return professor; }

Pessoa** Disciplina::getVetorAlunos() { return alunos; }

unsigned short int Disciplina::getQtdAlunos() { return qtdAlunos; }

// Setters
void Disciplina::setNome(std::string novoNome) { nome = novoNome; }

void Disciplina::setCargaHoraria(unsigned int novaCarga) {
    cargaHoraria = novaCarga;
}

void Disciplina::setProfessor(Pessoa* novoProfessor) {
    professor = novoProfessor;
}

// Functions
std::string Disciplina::getNomeProfessor() { return professor->getNome(); }

bool Disciplina::adicionarAluno(Pessoa* aluno) {
    if (qtdAlunos == 50) return false;

    alunos[qtdAlunos] = aluno;
    qtdAlunos++;
    return true;
}

bool Disciplina::removerAluno(Pessoa* aluno) {
    unsigned int i{0};
    Pessoa* alunoAchado{nullptr};

    while (i < qtdAlunos && alunoAchado == nullptr) {
        if (alunos[i] == aluno) alunoAchado = alunos[i];
        i++;
    }
    if (alunoAchado == nullptr) return false;

    // Não é o melhor approach para remover, mas é o mais rapido =D
    alunos[i - 1] = alunos[qtdAlunos - 1];
    qtdAlunos--;

    delete alunoAchado;
    return true;
}

bool Disciplina::removerAluno(uint64_t cpf) {
    unsigned int i{0};
    Pessoa* alunoAchado{nullptr};

    while (i < qtdAlunos && alunoAchado == nullptr) {
        if (alunos[i]->getCpf() == cpf) alunoAchado = alunos[i];
        i++;
    }
    if (alunoAchado == nullptr) return false;

    // Não é o melhor approach para remover, mas é o mais rapido =D
    alunos[i - 1] = alunos[qtdAlunos - 1];
    qtdAlunos--;

    delete alunoAchado;
    return true;
}

void Disciplina::liberaAlunos() {
    for (unsigned short int i{0}; i < qtdAlunos; ++i) delete alunos[i];
    delete[] alunos;
}