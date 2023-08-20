#include <iostream>
#include <string>

#include "Curso.hpp"
#include "Disciplina.hpp"
#include "Pessoa.hpp"

int main() {
    Pessoa *professor{new Pessoa{"Irineu", 11111111111, 40}};
    Curso *curso{new Curso{"BCC", (char)1111, (char)3600}};
    Disciplina *disciplina{new Disciplina{
        "Praticas de desenvolvimento de software", 60, *curso, professor}};

    Pessoa *aluno1{new Pessoa{"Aluno 1", 11111111111, 20}};
    Pessoa *aluno2{new Pessoa{"Aluno 2", 22222222222, 20}};
    Pessoa *aluno3{new Pessoa{"Aluno 3", 33333333333, 20}};
    disciplina->adicionarAluno(aluno1);
    disciplina->adicionarAluno(aluno2);
    disciplina->adicionarAluno(aluno3);

    // Dava pra encapsular essa 'introduçao' mas deixei na main pra usar a
    // getVetorAlunos();
    std::cout << "Disciplina: " << disciplina->getNome() << std::endl;
    std::cout << "Curso: " << disciplina->getCurso().getNome() << std::endl;
    std::cout << "Professor: " << disciplina->getNomeProfessor() << std::endl;
    std::cout << "Alunos: " << std::endl;

    Pessoa **alunos = disciplina->getVetorAlunos();
    for (unsigned short int i{0}; i < disciplina->getQtdAlunos(); ++i)
        std::cout << '\t' << alunos[i]->getNome() << std::endl;

    disciplina->liberaAlunos();
    delete professor;
    delete curso;
    delete disciplina;
    return 0;
}