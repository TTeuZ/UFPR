#include <iostream>
#include <list>
#include <string>

#include "Disciplina.hpp"
#include "Pessoa.hpp"
#include "SalaAula.hpp"

int main() {
    Pessoa prof1{"João", 11111111111, 40};
    Disciplina dis1{"Orientacao a Objetos", 60};
    dis1.setProfessor(&prof1);

    Pessoa prof2{"Maria", 22222222222, 30};
    Disciplina dis2{"Sistemas Operacionais", 60};
    dis2.setProfessor(&prof2);

    SalaAula sala{"Lab Info 1", 20};
    SalaAula sala2{"Lab Info 2", 20};

    // ----------------------------------------------------------------

    std::cout << "Adicionando dis1 na sala 1\n\n";
    dis1.setSalaAula(&sala);
    std::string cabecalho = "Sala: " + dis1.getSalaAula()->getNome();
    dis1.imprimirDados(cabecalho, 3600);

    std::list<Disciplina*>::iterator it;

    std::cout << "\nDisciplinas da sala 1: " << std::endl;
    std::list<Disciplina*> disciplinas = sala.getDisciplinas();
    for (it = disciplinas.begin(); it != disciplinas.end(); ++it)
        std::cout << '\t' << (*it)->getNome() << std::endl;

    std::cout << "\nDisciplinas da sala 2: " << std::endl;
    disciplinas = sala2.getDisciplinas();
    for (it = disciplinas.begin(); it != disciplinas.end(); ++it)
        std::cout << '\t' << (*it)->getNome() << std::endl;

    // ----------------------------------------------------------------

    std::cout << "\n-----------------------------------------------------------"
                 "-----\n\n";

    std::cout << "Adicionando dis1 na sala 2\n\n";
    dis1.setSalaAula(&sala2);
    cabecalho = "Sala: " + dis1.getSalaAula()->getNome();
    dis1.imprimirDados(cabecalho, 3600);

    std::cout << "\nDisciplinas da sala 1: " << std::endl;
    disciplinas = sala.getDisciplinas();
    for (it = disciplinas.begin(); it != disciplinas.end(); ++it)
        std::cout << '\t' << (*it)->getNome() << std::endl;

    std::cout << "\nDisciplinas da sala 2: " << std::endl;
    disciplinas = sala2.getDisciplinas();
    for (it = disciplinas.begin(); it != disciplinas.end(); ++it)
        std::cout << '\t' << (*it)->getNome() << std::endl;

    // ----------------------------------------------------------------

    std::cout << "\n-----------------------------------------------------------"
                 "-----\n\n";

    std::cout << "Movendo a dis1 para a sala 1 via sala1\n\n";
    sala.adicionarDisciplina(&dis1);
    cabecalho = "Sala: " + dis1.getSalaAula()->getNome();
    dis1.imprimirDados(cabecalho, 3600);

    std::cout << "\nDisciplinas da sala 1: " << std::endl;
    disciplinas = sala.getDisciplinas();
    for (it = disciplinas.begin(); it != disciplinas.end(); ++it)
        std::cout << '\t' << (*it)->getNome() << std::endl;

    std::cout << "\nDisciplinas da sala 2: " << std::endl;
    disciplinas = sala2.getDisciplinas();
    for (it = disciplinas.begin(); it != disciplinas.end(); ++it)
        std::cout << '\t' << (*it)->getNome() << std::endl;

    // ----------------------------------------------------------------

    std::cout << "\n-----------------------------------------------------------"
                 "-----\n\n";

    std::cout << "Removendo a dis1 para a sala 1 via sala1\n\n";
    sala.removerDisciplina(&dis1);
    cabecalho = "Sala: ";
    dis1.imprimirDados(cabecalho, 3600);

    std::cout << "\nDisciplinas da sala 1: " << std::endl;
    disciplinas = sala.getDisciplinas();
    for (it = disciplinas.begin(); it != disciplinas.end(); ++it)
        std::cout << '\t' << (*it)->getNome() << std::endl;

    std::cout << "\nDisciplinas da sala 2: " << std::endl;
    disciplinas = sala2.getDisciplinas();
    for (it = disciplinas.begin(); it != disciplinas.end(); ++it)
        std::cout << '\t' << (*it)->getNome() << std::endl;

    return 0;
}