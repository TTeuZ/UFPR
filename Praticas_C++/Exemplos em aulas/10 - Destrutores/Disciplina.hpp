#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include <list>
#include <string>

#include "ConteudoMinistrado.hpp"
#include "Pessoa.hpp"

class SalaAula;  // Forward Declaration

class Disciplina {
   public:
    Disciplina(std::string nome);
    Disciplina(std::string nome, SalaAula* sala);

    ~Disciplina();

    std::string getNome();
    void setNome(std::string nome);

    int getCargaHoraria();
    void setCargaHoraria(unsigned int carga);

    Pessoa* getProfessor();
    void setProfessor(Pessoa* prof);

    void setSalaAula(SalaAula* sala);
    SalaAula* getSalaAula();

    void imprimirDados(std::string& cabecalho, unsigned int cargaTotalCurso);

    void adicionarConteudoMinistrado(std::string conteudo,
                                     unsigned short cargaHorariaConteudo);
    void imprimirConteudosMinistrados();
    std::list<ConteudoMinistrado*>& getConteudos();

   private:
    std::string nome;
    unsigned short int cargaHoraria;
    Pessoa* professor;
    SalaAula* sala;

    std::list<ConteudoMinistrado*> conteudos;
};
#endif