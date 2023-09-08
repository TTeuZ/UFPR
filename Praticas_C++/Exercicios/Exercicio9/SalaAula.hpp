#ifndef SALA_AULA_H
#define SALA_AULA_H

#include <list>
#include <string>

#include "Disciplina.hpp"

class SalaAula {
    friend void Disciplina::setSalaAula(SalaAula* aula);

   public:
    // Constructors
    SalaAula(std::string nome, uint16_t capacidade);

    // Getters
    std::string& getNome();
    uint16_t getCapacidade();
    std::list<Disciplina*>& getDisciplinas();

    // Setters
    void setNome(std::string nome);
    void setCapacidade(uint16_t capacidade);

    // Functions
    void adicionarDisciplina(Disciplina* disciplina);
    void removerDisciplina(Disciplina* disciplina);

   private:
    std::string nome;
    uint16_t capacidade;
    std::list<Disciplina*> disciplinasMinistradas;
};
#endif