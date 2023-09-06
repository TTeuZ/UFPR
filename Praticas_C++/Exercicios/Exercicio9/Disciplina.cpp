#include "Disciplina.hpp"

#include <iostream>

#include "SalaAula.hpp"

// Constructors
Disciplina::Disciplina(std::string nome, unsigned short int cargaHoraria,
                       SalaAula* sala)
    : nome{nome}, cargaHoraria{cargaHoraria}, sala{nullptr} {
    this->setSalaAula(sala);
}

// Getters
std::string Disciplina::getNome() { return this->nome; }

int Disciplina::getCargaHoraria() { return this->cargaHoraria; }

Pessoa* Disciplina::getProfessor() { return this->professor; }

SalaAula* Disciplina::getSalaAula() { return this->sala; }

std::list<ConteudoMinistrado*>& Disciplina::getConteudos() {
    return this->conteudos;
}

// Setters
void Disciplina::setNome(std::string nome) { this->nome = nome; }

void Disciplina::setCargaHoraria(unsigned int carga) {
    this->cargaHoraria = carga;
}

void Disciplina::setProfessor(Pessoa* prof) { this->professor = prof; }

void Disciplina::setSalaAula(SalaAula* sala) {
    if (this->sala == sala) return;
    if (this->sala != nullptr) this->sala->disciplinasMinistradas.remove(this);

    this->sala = sala;
    if (this->sala != nullptr)
        this->sala->disciplinasMinistradas.push_back(this);
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

void Disciplina::adicionaConteudo(ConteudoMinistrado* conteudo) {
    this->conteudos.push_back(conteudo);
}

void Disciplina::removerConteudoMinistrado(unsigned long id) {
    std::list<ConteudoMinistrado*>::iterator it{this->conteudos.begin()};
    for (; it != this->conteudos.end(); ++it) {
        if ((*it)->getId() == id) {
            ConteudoMinistrado* conteudo{*it};
            this->conteudos.erase(it);
            delete conteudo;

            return;
        }
    }
}

void Disciplina::limparConteudos() {
    while (!this->conteudos.empty()) {
        delete this->conteudos.back();
        this->conteudos.pop_back();
    }
}