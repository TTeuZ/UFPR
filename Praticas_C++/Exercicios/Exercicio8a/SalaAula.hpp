#ifndef SALA_AULA_H
#define SALA_AULA_H

#include <list>
#include <string>

#include "Disciplina.hpp"

class SalaAula {
   public:
    // Constructors
    SalaAula(std::string nome, unsigned int capacidade);

    // Getters
    std::string getNome();
    unsigned int getCapacidade();

    // Setters
    void setNome(std::string nome);
    void setCapcidade(unsigned int capacidade);

    // Functions
    void adicionarDisciplina(Disciplina* disciplina);
    void removerDisciplina(Disciplina* disciplina);
    std::list<Disciplina*>& getDisciplinas();

   private:
    std::string nome;
    unsigned int capacidade;
    std::list<Disciplina*> disciplinasMinistradas;
};
#endif