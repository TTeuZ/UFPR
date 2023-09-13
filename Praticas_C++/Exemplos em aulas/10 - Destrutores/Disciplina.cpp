#include "Disciplina.hpp"

#include <iostream>

#include "SalaAula.hpp"

Disciplina::Disciplina(std::string nome) : nome{nome}, sala{nullptr} {}

Disciplina::Disciplina(std::string nome, SalaAula* sala) : Disciplina{nome} {
    this->setSalaAula(sala);
}

Disciplina::~Disciplina() {
    std::cerr << "Disciplina: " << this->getNome() << " Destruida" << std::endl;

    std::list<ConteudoMinistrado*>::iterator it;
    for (it = conteudos.begin(); it != conteudos.end(); ++it) delete *it;
    this->setSalaAula(nullptr);
}

std::string Disciplina::getNome() { return nome; }

void Disciplina::setNome(std::string nome) { this->nome = nome; }

int Disciplina::getCargaHoraria() { return this->cargaHoraria; }

void Disciplina::setCargaHoraria(unsigned int carga) {
    this->cargaHoraria = carga;
}

Pessoa* Disciplina::getProfessor() { return this->professor; }

void Disciplina::setProfessor(Pessoa* prof) { this->professor = prof; }

void Disciplina::setSalaAula(SalaAula* sala) {
    if (this->sala !=
        nullptr)  // se já existia uma sala, remover a disciplina dessa sala
        this->sala->disciplinasMinistradas.remove(this);
    this->sala = sala;
    if (this->sala != nullptr)
        this->sala->disciplinasMinistradas.push_back(
            this);  // adicionar a disciplina na nova sala
}

SalaAula* Disciplina::getSalaAula() { return this->sala; }

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

void Disciplina::adicionarConteudoMinistrado(
    std::string conteudo, unsigned short cargaHorariaConteudo) {
    this->conteudos.push_back(
        new ConteudoMinistrado{conteudo, cargaHorariaConteudo});
}

void Disciplina::imprimirConteudosMinistrados() {
    std::list<ConteudoMinistrado*>::iterator it;
    for (it = conteudos.begin(); it != conteudos.end(); it++) {
        std::cout << "Id: " << (*it)->getId() << std::endl
                  << "Conteudo: " << (*it)->getDescricao() << std::endl
                  << "Carga: " << (*it)->getCargaHorariaConteudo() << std::endl
                  << std::endl;
    }
}

std::list<ConteudoMinistrado*>& Disciplina::getConteudos() {
    return this->conteudos;
}