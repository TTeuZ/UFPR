#include <iostream>
#include <string>
#include <vector>

#include "Curso.hpp"
#include "Disciplina.hpp"
#include "Pessoa.hpp"

int main() {
    Pessoa *professor{new Pessoa{"Irineu", 11111111111, 40}};
    Curso *curso{new Curso{"BCC", (char)1111, (char)3600}};
    Disciplina *disciplina{new Disciplina{
        "Praticas de desenvolvimento de software", 60, *curso, professor}};

    Pessoa *aluno0{new Pessoa{"Aluno 0", 00000000000, 20}};
    disciplina->adicionarAluno(aluno0);
    disciplina->adicionarAluno(new Pessoa{"Aluno 1", 11111111111, 20});
    disciplina->adicionarAluno(new Pessoa{"Aluno 2", 22222222222, 20});
    disciplina->adicionarAluno(new Pessoa{"Aluno 3", 33333333333, 20});
    disciplina->adicionarAluno(new Pessoa{"Aluno 4", 44444444444, 20});
    disciplina->adicionarAluno(new Pessoa{"Aluno 5", 55555555555, 20});
    disciplina->adicionarAluno(new Pessoa{"Aluno 6", 66666666666, 20});
    disciplina->adicionarAluno(new Pessoa{"Aluno 7", 77777777777, 20});

    std::cout << "Disciplina: " << disciplina->getNome() << std::endl;
    std::cout << "Curso: " << disciplina->getCurso().getNome() << std::endl;
    std::cout << "Professor: " << disciplina->getNomeProfessor() << std::endl;
    std::cout << "Alunos: " << std::endl;

    std::vector<Pessoa *> alunos{disciplina->getAlunos()};
    std::vector<Pessoa *>::iterator it{alunos.begin()};
    for (; it != alunos.end(); ++it)
        std::cout << '\t' << (*it)->getNome() << std::endl;

    std::cout << "Removendo aluno por cpf" << std::endl;
    disciplina->removerAluno(66666666666);

    alunos = disciplina->getAlunos();
    for (it = alunos.begin(); it != alunos.end(); ++it)
        std::cout << '\t' << (*it)->getNome() << std::endl;

    std::cout << "Removendo aluno por objeto" << std::endl;
    disciplina->removerAluno(aluno0);

    alunos = disciplina->getAlunos();
    for (it = alunos.begin(); it != alunos.end(); ++it)
        std::cout << '\t' << (*it)->getNome() << std::endl;

    disciplina->liberaAlunos();
    delete professor;
    delete curso;
    delete disciplina;
    return 0;
}