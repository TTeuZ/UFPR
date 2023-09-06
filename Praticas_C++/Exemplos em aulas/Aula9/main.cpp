#include <iostream>
#include <list>

#include "Console.hpp"
#include "ConteudoMinistrado.hpp"
#include "Disciplina.hpp"
#include "Pessoa.hpp"
#include "SalaAula.hpp"

int main() {
    ConteudoMinistrado c1{"Ponteiros", 4};
    ConteudoMinistrado c2{"Referencias", 2};
    Pessoa prof1{"João", 11111111111, 40};
    Disciplina dis1{"Orientacao a Objetos"};
    dis1.setProfessor(&prof1);

    Pessoa prof2{"Maria", 22222222222, 30};
    Disciplina dis2{"Sistemas Operacionais"};
    dis2.setProfessor(&prof2);

    SalaAula sala{"Lab Info 1", 20};
    SalaAula sala2{"Lab Info 2", 20};

    dis1.setSalaAula(&sala);
    dis1.adicionaConteudo(&c1);
    dis1.adicionaConteudo(&c2);

    Console::imprimirDadosDisciplina(dis1);

    return 0;
}