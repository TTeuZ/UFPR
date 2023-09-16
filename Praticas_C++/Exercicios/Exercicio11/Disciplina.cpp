#include "Disciplina.hpp"

#include <iostream>

#include "SalaAula.hpp"

// Constructors
Disciplina::Disciplina(Curso& curso, const std::string& nome, SalaAula* sala)
    : curso{curso}, nome{nome}, sala{nullptr} {
    this->setSalaAula(sala);
}

Disciplina::Disciplina(Curso& curso, const std::string& nome, Pessoa* professor,
                       const uint8_t cargaHoraria, SalaAula* sala)
    : curso{curso},
      nome{nome},
      professor{professor},
      cargaHoraria{cargaHoraria},
      sala{nullptr} {
    this->setSalaAula(sala);
}

// Destructor
Disciplina::~Disciplina() {
    this->limparConteudos();
    this->setSalaAula(nullptr);
}

// Getters
const Curso& Disciplina::getCurso() const { return this->curso; }

const std::string& Disciplina::getNome() const { return this->nome; }

const Pessoa* Disciplina::getProfessor() const { return this->professor; }

int Disciplina::getCargaHoraria() const { return this->cargaHoraria; }

const SalaAula* Disciplina::getSalaAula() const { return this->sala; }

const std::list<Pessoa*>& Disciplina::getAlunos() const { return this->alunos; }

const std::list<ConteudoMinistrado*>& Disciplina::getConteudos() const {
    return this->conteudos;
}

// Setters
void Disciplina::setNome(const std::string& nome) { this->nome = nome; }

void Disciplina::setProfessor(Pessoa* professor) {
    this->professor = professor;
}

void Disciplina::setCargaHoraria(const int8_t cargaHoraria) {
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
void Disciplina::imprimirDados(const std::string& cabecalho,
                               const int8_t cargaTotalCurso) {
    double pctCurso = (double)this->cargaHoraria / cargaTotalCurso;
    pctCurso = pctCurso * 100;
    std::cout << cabecalho << std::endl;
    std::cout << "Disciplina: " << this->nome << std::endl;
    std::cout << "Carga: " << this->cargaHoraria << std::endl;
    std::cout << "Porcentagem do curso: " << pctCurso << "%" << std::endl;
    std::cout << "Professor: " << this->professor->getNome() << std::endl;
}

const std::string& Disciplina::getNomeProfessor() const {
    return this->professor->getNome();
}

void Disciplina::adicionarAluno(Pessoa* aluno) {
    this->alunos.push_back(aluno);
}

bool Disciplina::removerAluno(Pessoa* aluno) {
    std::list<Pessoa*>::iterator it{this->alunos.begin()};
    for (; it != this->alunos.end(); ++it) {
        if (*it == aluno) {
            this->alunos.erase(it);
            return true;
        }
    }
    return false;
}

bool Disciplina::removerAluno(const uint64_t cpf) {
    std::list<Pessoa*>::iterator it{this->alunos.begin()};
    for (; it != this->alunos.end(); ++it) {
        if ((*it)->getCpf() == cpf) {
            this->alunos.erase(it);
            return true;
        }
    }
    return false;
}

void Disciplina::adicionaConteudo(const std::string& descricao,
                                  const uint8_t cargaHorariaConteudo) {
    ConteudoMinistrado* conteudo{new ConteudoMinistrado{"Ponteiros", 4}};
    this->conteudos.push_back(conteudo);
}

bool Disciplina::removerConteudoMinistrado(const uint64_t id) {
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

void Disciplina::limparConteudos() {
    while (!this->conteudos.empty()) {
        delete this->conteudos.back();
        this->conteudos.pop_back();
    }
}