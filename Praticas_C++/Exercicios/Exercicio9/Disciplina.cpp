#include "Disciplina.hpp"

#include <iostream>

#include "SalaAula.hpp"

// Constructors
Disciplina::Disciplina(Curso& curso, std::string nome, Pessoa* professor,
                       uint8_t cargaHoraria, SalaAula* salaa)
    : curso{curso},
      nome{nome},
      professor{professor},
      cargaHoraria{cargaHoraria},
      sala{nullptr} {
    this->setSalaAula(sala);
}

// Getters
Curso& Disciplina::getCurso() { return this->curso; };

std::string Disciplina::getNome() { return this->nome; }

Pessoa* Disciplina::getProfessor() { return this->professor; }

int Disciplina::getCargaHoraria() { return this->cargaHoraria; }

SalaAula* Disciplina::getSalaAula() { return this->sala; }

std::list<Pessoa*> Disciplina::getAlunos() { return this->alunos; }

std::list<ConteudoMinistrado*>& Disciplina::getConteudos() {
    return this->conteudos;
}

// Setters
void Disciplina::setNome(std::string nome) { this->nome = nome; }

void Disciplina::setProfessor(Pessoa* prof) { this->professor = prof; }

void Disciplina::setCargaHoraria(int8_t cargaHoraria) {
    this->cargaHoraria = cargaHoraria;
}

void Disciplina::setSalaAula(SalaAula* sala) {
    if (this->sala == sala) return;
    if (this->sala != nullptr) this->sala->disciplinasMinistradas.remove(this);

    this->sala = sala;
    if (this->sala != nullptr)
        this->sala->disciplinasMinistradas.push_back(this);
}

// Functions
void Disciplina::imprimirDados(std::string& cabecalho, int8_t cargaTotalCurso) {
    double pctCurso = (double)this->cargaHoraria / cargaTotalCurso;
    pctCurso = pctCurso * 100;
    std::cout << cabecalho << std::endl;
    std::cout << "Disciplina: " << this->nome << std::endl;
    std::cout << "Carga: " << this->cargaHoraria << std::endl;
    std::cout << "Porcentagem do curso: " << pctCurso << "%" << std::endl;
    std::cout << "Professor: " << this->professor->getNome() << std::endl;
}

std::string Disciplina::getNomeProfessor() {
    return this->professor->getNome();
}

void Disciplina::adicionarAluno(Pessoa* aluno) {
    this->alunos.push_back(aluno);
}

bool Disciplina::removerAluno(Pessoa* aluno) {
    std::list<Pessoa*>::iterator it{this->alunos.begin()};

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
    std::list<Pessoa*>::iterator it{this->alunos.begin()};

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

void Disciplina::adicionaConteudo(ConteudoMinistrado* conteudo) {
    this->conteudos.push_back(conteudo);
}

bool Disciplina::removerConteudoMinistrado(uint64_t id) {
    std::list<ConteudoMinistrado*>::iterator it{this->conteudos.begin()};
    for (; it != this->conteudos.end(); ++it) {
        if ((*it)->getId() == id) {
            ConteudoMinistrado* conteudo{*it};
            this->conteudos.erase(it);
            delete conteudo;

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

void Disciplina::limparConteudos() {
    while (!this->conteudos.empty()) {
        delete this->conteudos.back();
        this->conteudos.pop_back();
    }
}