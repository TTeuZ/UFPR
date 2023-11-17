#include <iostream>
#include <memory>

#include "Ementa.hpp"
#include "Livro.hpp"
int main() {
    ufpr::Ementa* ementa1{new ufpr::Ementa{"Paradigmas de programação"}};
    ufpr::Ementa* ementa2{new ufpr::Ementa{"Orientação a Objetos"}};
    ementa1->addLivro(ufpr::Livro::carregarLivro(1234));
    ementa1->addLivro(ufpr::Livro::carregarLivro(5678));
    ementa2->addLivro(ufpr::Livro::carregarLivro(1234));
    delete ementa1;
    std::cout << "Ementa 1 deletada, deletando ementa 2\n";
    delete ementa2;

    return 0;
}
