#include <iostream>

#include "Pilha.hpp"

int main() {
    int retorno;
    Pilha<int, 5> p;
    p.push(1);
    p.push(2);
    p.push(3);
    p.push(4);

    while (!p.estaVazia()) {
        p.pop(&retorno);
        std::cout << retorno << "\n";
    }

    std::string s;
    Pilha<std::string, 8> p2;
    p2.push("Batata");
    p2.push("Pao de");

    while (!p2.estaVazia()) {
        p2.pop(&s);
        std::cout << s << "\n";
    }

    std::cout << "Fim\n";

    return 0;
}
