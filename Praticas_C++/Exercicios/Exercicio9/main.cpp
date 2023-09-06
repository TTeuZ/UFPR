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
    Disciplina dis1{"Orientacao a Objetos", 60, bcc, &prof1, &sala};

    Pessoa prof2{"Maria", 22222222222, 30};
    Disciplina dis2{"Sistemas Operacionais", 60, bcc, &prof2, &sala2};

    ConteudoMinistrado* c1{new ConteudoMinistrado{"Ponteiros", 4}};
    ConteudoMinistrado* c2{new ConteudoMinistrado{"Referencias", 4}};
    dis1.adicionaConteudo(c1);
    dis1.adicionaConteudo(c2);

    ConteudoMinistrado* c3{new ConteudoMinistrado{"Strings", 4}};
    ConteudoMinistrado* c4{new ConteudoMinistrado{"Floats", 4}};
    dis2.adicionaConteudo(c3);
    dis2.adicionaConteudo(c4);

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

    dis1.limparConteudos();
    dis2.limparConteudos();

    return 0;
}