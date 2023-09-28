#include "Console.hpp"

#include <iostream>

void Console::detalhesTrajeto(const Trajeto& trajeto) {
    std::cout << "Pontos do trajeto: \n" << std::endl;

    trajeto.imprimirTrajeto();
    std::cout << std::endl;

    const double distancia = trajeto.getDistanciaPercorrida();
    std::cout << "Tamanho do trajeto: " << distancia << std::endl;
}