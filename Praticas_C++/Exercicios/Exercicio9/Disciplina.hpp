#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include <list>
#include <string>

#include "ConteudoMinistrado.hpp"
#include "Pessoa.hpp"
class SalaAula;  // Foward Declaration -> para resolver o include circular

class Disciplina {
    friend class SalaAula;

   public:
    // Constructor
    Disciplina(std::string nome, unsigned short int cargaHoraria,
               SalaAula* sala);

    // Getters
    std::string getNome();
    int getCargaHoraria();
    Pessoa* getProfessor();
    SalaAula* getSalaAula();
    std::list<ConteudoMinistrado*>& getConteudos();

    // Setters
    void setNome(std::string nome);
    void setCargaHoraria(unsigned int carga);
    void setProfessor(Pessoa* prof);
    void setSalaAula(SalaAula* sala);

    // Functions
    void imprimirDados(std::string& cabecalho, unsigned int cargaTotalCurso);
    void adicionaConteudo(ConteudoMinistrado* conteudo);
    void removerConteudoMinistrado(unsigned long id);
    void limparConteudos();

   private:
    std::string nome;
    unsigned short int cargaHoraria;
    Pessoa* professor;
    SalaAula* sala;
    std::list<ConteudoMinistrado*> conteudos;
};
#endif