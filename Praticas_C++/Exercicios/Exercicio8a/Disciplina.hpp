#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include <string>

#include "Pessoa.hpp"
class SalaAula;  // Foward Declaration -> para resolver o include circular

class Disciplina {
   public:
    // Constructor
    Disciplina(std::string nome, unsigned short int cargaHoraria);

    // Getters
    std::string getNome();
    int getCargaHoraria();
    Pessoa* getProfessor();
    SalaAula* getSalaAula();

    // Setters
    void setNome(std::string nome);
    void setCargaHoraria(unsigned int carga);
    void setProfessor(Pessoa* prof);
    void setSalaAula(SalaAula* sala);

    // Functions
    void imprimirDados(std::string& cabecalho, unsigned int cargaTotalCurso);

   private:
    std::string nome;
    unsigned short int cargaHoraria;
    Pessoa* professor;
    SalaAula* sala;
};
#endif