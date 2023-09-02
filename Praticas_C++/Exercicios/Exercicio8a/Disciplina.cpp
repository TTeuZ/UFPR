#include "Disciplina.hpp"

#include <iostream>

#include "SalaAula.hpp"

// Constructors
Disciplina::Disciplina(std::string nome, unsigned short int cargaHoraria)
    : nome{nome}, cargaHoraria{cargaHoraria}, sala{nullptr} {}

// Getters
std::string Disciplina::getNome() { return this->nome; }

int Disciplina::getCargaHoraria() { return this->cargaHoraria; }

Pessoa* Disciplina::getProfessor() { return this->professor; }

SalaAula* Disciplina::getSalaAula() { return this->sala; }

// Setters
void Disciplina::setNome(std::string nome) { this->nome = nome; }

void Disciplina::setCargaHoraria(unsigned int carga) {
    this->cargaHoraria = carga;
}

void Disciplina::setProfessor(Pessoa* prof) { this->professor = prof; }

void Disciplina::setSalaAula(SalaAula* sala) {
    if (this->sala == sala) return;
    if (sala == nullptr)
        this->sala = sala;
    else {
        if (this->sala != nullptr) this->sala->removerDisciplina(this);
        sala->adicionarDisciplina(this);
        this->sala = sala;
    }
}

// Functions
void Disciplina::imprimirDados(std::string& cabecalho,
                               unsigned int cargaTotalCurso) {
    double pctCurso = (double)this->cargaHoraria / cargaTotalCurso;
    pctCurso = pctCurso * 100;
    std::cout << cabecalho << std::endl;
    std::cout << "Disciplina: " << this->nome << std::endl;
    std::cout << "Carga: " << this->cargaHoraria << std::endl;
    std::cout << "Porcentagem do curso: " << pctCurso << "%" << std::endl;
    std::cout << "Professor: " << this->professor->getNome() << std::endl;
}