#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include <list>
#include <string>

#include "../Aluno/Aluno.hpp"
#include "../ConteudoMinistrado/ConteudoMinistrado.hpp"
#include "../Curso/Curso.hpp"
#include "../Pessoa/Pessoa.hpp"
#include "../Professor/Professor.hpp"

class SalaAula;  // Foward Declaration -> para resolver o include circular

class Disciplina {
    friend class SalaAula;

   public:
    // Constructor
    Disciplina(const Curso& curso, const std::string& nome, SalaAula* sala);
    Disciplina(const Curso& curso, const std::string& nome,
               const Professor* professor, const uint8_t cargaHoraria,
               SalaAula* sala);

    // Destructor
    virtual ~Disciplina();

    // Getters
    const Curso& getCurso() const;
    const std::string& getNome() const;
    const Professor* getProfessor() const;
    int getCargaHoraria() const;
    const SalaAula* getSalaAula() const;
    const std::list<const Aluno*>& getAlunos() const;
    const std::list<ConteudoMinistrado*>& getConteudos() const;

    // Setters
    void setNome(const std::string& nome);
    void setProfessor(const Professor* professor);
    void setCargaHoraria(const int8_t cargaHoraria);
    void setSalaAula(SalaAula* sala);

    // Functions
    void imprimirDados(const std::string& cabecalho,
                       const int8_t cargaTotalCurso);

    const std::string& getNomeProfessor() const;

    void adicionarAluno(const Aluno* aluno);
    bool removerAluno(const Aluno* aluno);
    bool removerAluno(const uint64_t cpf);

    void adicionaConteudo(const std::string& descricao,
                          const uint8_t cargaHorariaConteudo);
    bool removerConteudoMinistrado(const uint64_t id);

   private:
    void limparConteudos();

    const Curso& curso;
    std::string nome;
    const Professor* professor;
    uint8_t cargaHoraria;
    SalaAula* sala;
    std::list<const Aluno*> alunos;
    std::list<ConteudoMinistrado*> conteudos;
};
#endif