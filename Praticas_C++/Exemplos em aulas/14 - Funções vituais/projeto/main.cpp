#include <iostream>
#include <list>
#include <string>

#include "./Aluno/Aluno.hpp"
#include "./Console/Console.hpp"
#include "./ConteudoMinistrado/ConteudoMinistrado.hpp"
#include "./Curso/Curso.hpp"
#include "./Disciplina/Disciplina.hpp"
#include "./Pessoa/Pessoa.hpp"
#include "./Professor/Professor.hpp"
#include "./ProfessorAdjunto/ProfessorAdjunto.hpp"
#include "./SalaAula/SalaAula.hpp"

int main() {
    Pessoa* p{new ProfessorAdjunto{"Maria", 11111111111, 100, 40}};
    std::cout << p->getNome() << std::endl;
    delete p;

    // ProfessorAdjunto p{"Joao", 11111111111, 8500, 40};
    // Professor* ptr{&p};

    // std::cout << p.getSalario() << std::endl;
    // std::cout << ptr->getSalario() << std::endl;

    return 0;
}