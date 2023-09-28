#include <iostream>

#include "./Console/Console.hpp"
#include "./DistanciaEuclidiano/DistanciaEuclidiano.hpp"
#include "./DistanciaManhattan/DistanciaManhattan.hpp"
#include "./Ponto/Ponto.hpp"
#include "./Trajeto/Trajeto.hpp"

int main() {
    Trajeto *t1{new DistanciaEuclidiano};
    Trajeto *t2{new DistanciaManhattan};

    t1->adicionarPonto(1.0, 1.0);
    t1->adicionarPonto(1.0, 4.0);
    t1->adicionarPonto(2.0, 6.0);

    t2->adicionarPonto(2.0, 4.0);
    t2->adicionarPonto(7.0, 5.0);
    t2->adicionarPonto(8.0, 8.0);

    Console::detalhesTrajeto(*t1);
    Console::detalhesTrajeto(*t2);

    delete t1;
    delete t2;

    return 0;
}
