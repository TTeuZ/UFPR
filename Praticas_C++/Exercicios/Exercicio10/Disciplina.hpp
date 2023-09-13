#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include <list>
#include <string>

#include "ConteudoMinistrado.hpp"
#include "Curso.hpp"
#include "Pessoa.hpp"
class SalaAula;  // Foward Declaration -> para resolver o include circular

class Disciplina {
    friend class SalaAula;

   public:
    // Constructor
    Disciplina(Curso& curso, std::string nome, SalaAula* sala);
    Disciplina(Curso& curso, std::string nome, Pessoa* professor,
               uint8_t cargaHoraria, SalaAula* sala);

    // Destructor
    ~Disciplina();

    // Getters
    Curso& getCurso();
    std::string& getNome();
    Pessoa* getProfessor();
    int getCargaHoraria();
    SalaAula* getSalaAula();
    std::list<Pessoa*>& getAlunos();
    std::list<ConteudoMinistrado*>& getConteudos();

    // Setters
    void setNome(std::string nome);
    void setProfessor(Pessoa* prof);
    void setCargaHoraria(int8_t cargaHoraria);
    void setSalaAula(SalaAula* sala);

    // Functions
    void imprimirDados(std::string& cabecalho, int8_t cargaTotalCurso);

    std::string getNomeProfessor();

    void adicionarAluno(Pessoa* aluno);
    bool removerAluno(Pessoa* aluno);
    bool removerAluno(uint64_t cpf);

    void adicionaConteudo(std::string descricao, uint8_t cargaHorariaConteudo);
    bool removerConteudoMinistrado(uint64_t id);

   private:
    void limparConteudos();

    Curso& curso;
    std::string nome;
    Pessoa* professor;
    uint8_t cargaHoraria;
    SalaAula* sala;
    std::list<Pessoa*> alunos;
    std::list<ConteudoMinistrado*> conteudos;
};
#endif