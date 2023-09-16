#include <iostream>
#include <list>
#include <string>

#include "Console.hpp"
#include "ConteudoMinistrado.hpp"
#include "Curso.hpp"
#include "Disciplina.hpp"
#include "Pessoa.hpp"
#include "SalaAula.hpp"

int main() {
    Curso bcc{"Ciência da Computação", (char)1111, (char)3600};

    SalaAula sala{"Lab Info 1", 20};
    SalaAula sala2{"Lab Info 2", 20};

    Pessoa prof1{"João", 11111111111, 40};
    Disciplina dis1{bcc, "Orientacao a Objetos", &prof1, 60, &sala};

    Pessoa prof2{"Maria", 22222222222, 30};
    Disciplina dis2{bcc, "Sistemas Operacionais", &prof2, 60, &sala2};

    dis1.adicionaConteudo("Ponteiros", 4);
    dis1.adicionaConteudo("Referencias", 4);
    dis2.adicionaConteudo("Strings", 4);
    dis2.adicionaConteudo("Floats", 4);

    Console::imprimirDadosDisciplina(dis1);

    std::cout << "-------------------------------------------\n" << std::endl;

    Console::imprimirDadosDisciplina(dis2);

    std::cout << "-------------------------------------------\n" << std::endl;
    std::cout << "Removendo conteudos\n\n";

    dis1.removerConteudoMinistrado(1);
    dis2.removerConteudoMinistrado(3);

    std::cout << "-------------------------------------------\n" << std::endl;

    Console::imprimirDadosDisciplina(dis1);

    std::cout << "-------------------------------------------\n" << std::endl;

    Console::imprimirDadosDisciplina(dis2);

    return 0;
}