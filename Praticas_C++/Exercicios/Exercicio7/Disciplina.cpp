#include "Disciplina.hpp"

#include <iostream>

// Constructors
Disciplina::Disciplina(std::string nome, unsigned short int cargaHoraria,
                       Curso& curso, Pessoa* professor)
    : nome{nome},
      cargaHoraria{cargaHoraria},
      curso{curso},
      professor{professor} {}

// Getters
std::string Disciplina::getNome() { return this->nome; }

int Disciplina::getCargaHoraria() { return this->cargaHoraria; }

Curso& Disciplina::getCurso() { return this->curso; };

Pessoa* Disciplina::getProfessor() { return this->professor; }

std::vector<Pessoa*> Disciplina::getAlunos() { return this->alunos; }

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

void Disciplina::adicionarAluno(Pessoa* aluno) {
    this->alunos.push_back(aluno);
}

bool Disciplina::removerAluno(Pessoa* aluno) {
    std::vector<Pessoa*>::iterator it{this->alunos.begin()};

    for (; it != this->alunos.end(); ++it) {
        if (*it == aluno) {
            Pessoa* alunoAchado{*it};
            this->alunos.erase(it);
            delete alunoAchado;

            return true;
        }
    }
    return false;
}

bool Disciplina::removerAluno(uint64_t cpf) {
    std::vector<Pessoa*>::iterator it{this->alunos.begin()};

    for (; it != this->alunos.end(); ++it) {
        if ((*it)->getCpf() == cpf) {
            Pessoa* alunoAchado{*it};
            this->alunos.erase(it);
            delete alunoAchado;

            return true;
        }
    }
    return false;
}

void Disciplina::liberaAlunos() {
    while (!this->alunos.empty()) {
        delete this->alunos.back();
        this->alunos.pop_back();
    }
}