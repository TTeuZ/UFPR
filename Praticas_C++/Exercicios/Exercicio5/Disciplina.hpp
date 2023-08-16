#ifndef DISCIPLINA_HPP
#define DISCIPLINA_HPP

#include <string>

#include "Pessoa.hpp"

class Disciplina {
   public:
    Disciplina(std::string nomeDisciplina);

    std::string getNome();
    void setNome(std::string novoNome);

    int getCargaHoraria();
    void setCargaHoraria(unsigned int novaCarga);

    Pessoa* getProfessor();
    void setProfessor(Pessoa* novoProfessor);

    std::string getNomeProfessor();

   private:
    std::string nome;
    unsigned short int cargaHoraria;
    Pessoa* professor;
};
#endif
