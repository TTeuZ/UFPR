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
    Disciplina(Curso& curso, const std::string& nome, SalaAula* sala);
    Disciplina(Curso& curso, const std::string& nome, Pessoa* professor,
               const uint8_t cargaHoraria, SalaAula* sala);

    // Destructor
    ~Disciplina();

    // Getters
    const Curso& getCurso() const;
    const std::string& getNome() const;
    const Pessoa* getProfessor() const;
    int getCargaHoraria() const;
    const SalaAula* getSalaAula() const;
    const std::list<Pessoa*>& getAlunos() const;
    const std::list<ConteudoMinistrado*>& getConteudos() const;

    // Setters
    void setNome(const std::string& nome);
    void setProfessor(Pessoa* professor);
    void setCargaHoraria(const int8_t cargaHoraria);
    void setSalaAula(SalaAula* sala);

    // Functions
    void imprimirDados(const std::string& cabecalho,
                       const int8_t cargaTotalCurso);

    const std::string& getNomeProfessor() const;

    void adicionarAluno(Pessoa* aluno);
    bool removerAluno(Pessoa* aluno);
    bool removerAluno(const uint64_t cpf);

    void adicionaConteudo(const std::string& descricao,
                          const uint8_t cargaHorariaConteudo);
    bool removerConteudoMinistrado(const uint64_t id);

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