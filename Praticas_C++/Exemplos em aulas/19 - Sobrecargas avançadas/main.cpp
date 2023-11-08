#include <iostream>
#include <list>

#include "Ementa.hpp"
int main() {
    std::list<ufpr::Ementa> ementas;
    ementas.push_back(ufpr::Ementa{"Ementa1"});
    ementas.push_back(ufpr::Ementa{"Ementa 2"});
    std::list<ufpr::Ementa>::const_iterator it{ementas.begin()};
    for (; it != ementas.end(); ++it) std::cout << it->getDescricao() << '\n';

    return 0;
}
