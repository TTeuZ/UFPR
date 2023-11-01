#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include <list>
#include <string>

#include "ConteudoMinistrado.hpp"
#include "Pessoa.hpp"
#include "Professor.hpp"
#include "EnumTipoDisciplina.hpp"

namespace ufpr{
class SalaAula;  // Forward Declaration
class Disciplina {
   public:
    Disciplina(const std::string &nome);
    Disciplina(const std::string &nome, SalaAula *const sala);
    Disciplina(const std::string &nome, SalaAula *const sala, const EnumTipoDisciplina tipo);

    virtual ~Disciplina();

    const std::string &getNome() const;
    void setNome(const std::string &nome);

    int getCargaHoraria() const;
    void setCargaHoraria(const unsigned int carga);

    const Professor *getProfessor() const;
    void setProfessor(Professor *const prof);

    void setSalaAula(SalaAula *const sala);
    const SalaAula *getSalaAula() const;
    void anularSalaAula();

    void imprimirDados(const std::string &cabecalho,
                       const unsigned int cargaTotalCurso) const;

    void adicionarConteudoMinistrado(const std::string &conteudo,
                                     const unsigned short cargaHorariaConteudo);
    void imprimirConteudosMinistrados() const;
    const std::list<ConteudoMinistrado *> &getConteudos() const;

    void adicionarAluno(Pessoa *const aluno);
    void removerAluno(Pessoa *const aluno);
    void removerAluno(const unsigned long cpf);
    const std::list<Pessoa *> &getAlunos() const;

   private:
    std::string nome;
    unsigned short int cargaHoraria;
    Professor *professor;
    SalaAula *sala;
    EnumTipoDisciplina tipo;

    std::list<ConteudoMinistrado *> conteudos;
    std::list<Pessoa *> alunos;
};
}  // namespace ufpr
#endif