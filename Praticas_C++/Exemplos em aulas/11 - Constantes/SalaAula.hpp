#ifndef SALA_AULA_H
#define SALA_AULA_H

#include <list>
#include <string>

#include "Disciplina.hpp"

class SalaAula {
    friend void Disciplina::setSalaAula(SalaAula* salaAula);

   public:
    SalaAula(std::string nome, unsigned int capacidade);
    ~SalaAula();

    std::string getNome() const;
    void setNome(std::string nome);

    unsigned int getCapacidade() const;
    void setCapcidade(unsigned int capacidade);

    std::list<Disciplina*>& getDisciplinas();

   private:
    std::string nome;
    unsigned int capacidade;
    std::list<Disciplina*> disciplinasMinistradas;
};
#endif