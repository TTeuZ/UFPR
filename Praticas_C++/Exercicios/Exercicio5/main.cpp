#include <iostream>
#include <string>

#include "Disciplina.hpp"
#include "Pessoa.hpp"

int main() {
    Pessoa *professor{new Pessoa{"Irineu", 11111111111, 40}};
    Disciplina *d1{new Disciplina{"Praticas de desenvolvimento de software", 60,
                                  professor}};

    // Dava pra encapsular essa 'introduçao' mas deixei na main pra usar a
    // getVetorAlunos();
    std::cout << "Disciplina: " << d1->getNome() << std::endl;
    std::cout << "Professor: " << d1->getNomeProfessor() << std::endl;
    std::cout << "Alunos: " << std::endl;

    Pessoa **alunos = d1->getVetorAlunos();
    for (unsigned short int i{0}; i < d1->getQtdAlunos(); ++i)
        std::cout << '\t' << alunos[i]->getNome() << std::endl;

    // ------------------------------------------------------------------------------------------------

    std::cout << "\nAdicionando 3 alunos\n" << std::endl;
    Pessoa *aluno1{new Pessoa{"Aluno 1", 11111111111, 20}};
    Pessoa *aluno2{new Pessoa{"Aluno 2", 22222222222, 20}};
    Pessoa *aluno3{new Pessoa{"Aluno 3", 33333333333, 20}};
    d1->adicionarAluno(aluno1);
    d1->adicionarAluno(aluno2);
    d1->adicionarAluno(aluno3);

    std::cout << "Disciplina: " << d1->getNome() << std::endl;
    std::cout << "Professor: " << d1->getNomeProfessor() << std::endl;
    std::cout << "Alunos: " << std::endl;

    alunos = d1->getVetorAlunos();
    for (unsigned short int i{0}; i < d1->getQtdAlunos(); ++i)
        std::cout << '\t' << alunos[i]->getNome() << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------------------------------------

    std::cout << "\nRemovendo 1 aluno\n" << std::endl;
    d1->removerAluno(aluno1);

    std::cout << "Disciplina: " << d1->getNome() << std::endl;
    std::cout << "Professor: " << d1->getNomeProfessor() << std::endl;
    std::cout << "Alunos: " << std::endl;

    alunos = d1->getVetorAlunos();
    for (unsigned short int i{0}; i < d1->getQtdAlunos(); ++i)
        std::cout << '\t' << alunos[i]->getNome() << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------------------------------------

    std::cout << "\nRemovendo 1 aluno por cpf\n" << std::endl;
    d1->removerAluno(aluno2->getCpf());

    std::cout << "Disciplina: " << d1->getNome() << std::endl;
    std::cout << "Professor: " << d1->getNomeProfessor() << std::endl;
    std::cout << "Alunos: " << std::endl;

    alunos = d1->getVetorAlunos();
    for (unsigned short int i{0}; i < d1->getQtdAlunos(); ++i)
        std::cout << '\t' << alunos[i]->getNome() << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------------------------------------

    std::cout << "\nRemovendo 1 aluno ja removida\n" << std::endl;
    d1->removerAluno(aluno2);

    std::cout << "Disciplina: " << d1->getNome() << std::endl;
    std::cout << "Professor: " << d1->getNomeProfessor() << std::endl;
    std::cout << "Alunos: " << std::endl;

    alunos = d1->getVetorAlunos();
    for (unsigned short int i{0}; i < d1->getQtdAlunos(); ++i)
        std::cout << '\t' << alunos[i]->getNome() << std::endl;
    std::cout << std::endl;

    d1->liberaAlunos();
    delete professor;
    delete d1;
    return 0;
}