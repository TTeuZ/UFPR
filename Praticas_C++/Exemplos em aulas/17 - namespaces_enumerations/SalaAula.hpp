#ifndef SALA_AULA_H
#define SALA_AULA_H

#include <list>
#include <string>

#include "Disciplina.hpp"

namespace ufpr {
class SalaAula {
   public:
    SalaAula(std::string nome, unsigned int capacidade);
    virtual ~SalaAula();

    std::string getNome();
    void setNome(std::string nome);

    unsigned int getCapacidade();
    void setCapcidade(unsigned int capacidade);

    void adicionarDisciplina(Disciplina* disciplina);
    void removerDisciplina(Disciplina* disciplina);
    std::list<Disciplina*>& getDisciplinas();

   private:
    std::string nome;
    unsigned int capacidade;
    std::list<Disciplina*> disciplinasMinistradas;
};
}  // namespace ufpr
#endif
