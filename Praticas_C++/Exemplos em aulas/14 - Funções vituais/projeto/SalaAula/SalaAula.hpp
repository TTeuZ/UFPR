#ifndef SALA_AULA_H
#define SALA_AULA_H

#include <list>
#include <string>

#include "../Disciplina/Disciplina.hpp"

class SalaAula {
    friend void Disciplina::setSalaAula(SalaAula* aula);

   public:
    // Constructors
    SalaAula(const std::string& nome, const uint16_t capacidade);

    // Constructors
    virtual ~SalaAula();

    // Getters
    const std::string& getNome() const;
    uint16_t getCapacidade() const;
    const std::list<Disciplina*>& getDisciplinas() const;

    // Setters
    void setNome(const std::string& nome);
    void setCapacidade(const uint16_t capacidade);

    // Functions
    void adicionarDisciplina(Disciplina* disciplina);
    void removerDisciplina(Disciplina* disciplina);

   private:
    std::string nome;
    uint16_t capacidade;
    std::list<Disciplina*> disciplinasMinistradas;
};
#endif