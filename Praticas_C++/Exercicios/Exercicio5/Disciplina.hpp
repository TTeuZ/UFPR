#ifndef DISCIPLINA_HPP
#define DISCIPLINA_HPP

#include <cstdint>
#include <string>

#include "Pessoa.hpp"

class Disciplina {
   public:
    // constructors
    Disciplina(std::string nomeDisciplina, unsigned short int cargaHoraria,
               Pessoa* professor);

    // Getters
    std::string getNome();
    int getCargaHoraria();
    Pessoa* getProfessor();
    Pessoa** getVetorAlunos();
    unsigned short int getQtdAlunos();

    // Setters
    void setNome(std::string novoNome);
    void setCargaHoraria(unsigned int novaCarga);
    void setProfessor(Pessoa* novoProfessor);

    // Functions
    std::string getNomeProfessor();
    bool adicionarAluno(Pessoa* aluno);
    bool removerAluno(Pessoa* aluno);
    bool removerAluno(uint64_t cpf);
    void liberaAlunos();

   private:
    std::string nome;
    unsigned short int cargaHoraria;
    Pessoa* professor;
    Pessoa** alunos;
    unsigned short int qtdAlunos;
};
#endif
