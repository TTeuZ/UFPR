#include <iostream>

#include "./Aluno/Aluno.hpp"
#include "./Console/Console.hpp"
#include "./ConteudoMinistrado/ConteudoMinistrado.hpp"
#include "./Curso/Curso.hpp"
#include "./Disciplina/Disciplina.hpp"
#include "./Engenheiro/Engenheiro.hpp"
#include "./Pessoa/Pessoa.hpp"
#include "./Professor/Professor.hpp"
#include "./ProfessorAdjunto/ProfessorAdjunto.hpp"
#include "./ProfessorEngenheiro/ProfessorEngenheiro.hpp"
#include "./SalaAula/SalaAula.hpp"

int main() {
    ProfessorEngenheiro pe{"Maria", 11111111111, 85, 40, 1234};
    std::cout << "nome: " << pe.getNome() << "\n";
    std::cout << "Salario: " << pe.getSalario() << "\n";

    return 0;
}