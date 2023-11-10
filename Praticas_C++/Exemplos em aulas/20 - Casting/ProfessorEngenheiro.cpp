#include "ProfessorEngenheiro.hpp"

using namespace ufpr;

ProfessorEngenheiro::ProfessorEngenheiro(const std::string& nome,
            const unsigned long cpf, const unsigned int valorHora,
            const unsigned short cargaHoraria, const unsigned int numeroCrea)
                   :Pessoa(nome, cpf),
                   Professor(nome, cpf, valorHora, cargaHoraria),
                   Engenheiro(nome, cpf, numeroCrea){
}

ProfessorEngenheiro::ProfessorEngenheiro(const std::string& nome,
            const CPF& cpf, const unsigned int valorHora,
            const unsigned short cargaHoraria, const unsigned int numeroCrea)
                   :Pessoa(nome, cpf),
                   Professor(nome, cpf, valorHora, cargaHoraria),
                   Engenheiro(nome, cpf, numeroCrea){
}

ProfessorEngenheiro::~ProfessorEngenheiro(){}

unsigned int ProfessorEngenheiro::getSalario() const{
    return Professor::getSalario() + Engenheiro::getSalario();
}