#ifndef DISCIPLINA_HPP
#define DISCIPLINA_HPP

#include <cstdint>
#include <string>
#include <vector>

#include "Curso.hpp"
#include "Pessoa.hpp"

class Disciplina {
   public:
    // constructors
    Disciplina(std::string nome, unsigned short int cargaHoraria, Curso& curso,
               Pessoa* professor);

    // Getters
    std::string getNome();
    int getCargaHoraria();
    Curso& getCurso();
    Pessoa* getProfessor();
    std::vector<Pessoa*> getAlunos();

    // Setters
    void setNome(std::string nome);
    void setCargaHoraria(unsigned int cargaHoraria);
    void setProfessor(Pessoa* professor);

    // Functions
    std::string getNomeProfessor();
    void adicionarAluno(Pessoa* aluno);
    bool removerAluno(Pessoa* aluno);
    bool removerAluno(uint64_t cpf);
    void liberaAlunos();

   private:
    std::string nome;
    unsigned short int cargaHoraria;
    Curso& curso;
    Pessoa* professor;
    std::vector<Pessoa*> alunos;
};
#endif
