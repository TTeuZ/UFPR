#include "Trajeto.hpp"

#include <iostream>

// Constructors
Trajeto::Trajeto() : pontos{new std::list<const Ponto*>} {}

// Destructor
Trajeto::~Trajeto() {
    std::list<const Ponto*>::iterator it = this->pontos->begin();
    for (; it != pontos->end(); it++) delete *it;
    delete this->pontos;
}

// Functions
void Trajeto::adicionarPonto(const double coordX, const double coordY) {
    this->pontos->push_back(new Ponto{coordX, coordY});
}

void Trajeto::imprimirTrajeto() const {
    std::list<const Ponto*>::const_iterator it = this->pontos->begin();
    for (; it != pontos->end(); it++) {
        std::cout << (*it)->getCoordX() << "\t" << (*it)->getCoordY()
                  << std::endl;
    }
}

/*
 * No calculo da distância total temos a inversâo de controle, pois neste
 * caso em especifico, a classe Trajeto perde o controle do calculo da
 * distancia, pois a função carcularDistanciaPontos é definida nas classes
 * filhas.
 */
double Trajeto::getDistanciaPercorrida() const {
    if (this->pontos->size() < 1) return 0;

    std::list<const Ponto*>::const_iterator it = pontos->begin();
    const Ponto* anterior = (*it);
    const Ponto* proximo;
    it++;
    double distanciaTotal = 0.0;

    for (; it != pontos->end(); it++) {
        proximo = (*it);
        distanciaTotal += this->calcularDistanciaPontos(anterior, proximo);
        anterior = proximo;
    }
    return distanciaTotal;
}
