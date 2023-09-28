#include "DistanciaManhattan.hpp"

#include <cmath>

double DistanciaManhattan::calcularDistanciaPontos(
    const Ponto* const p1, const Ponto* const p2) const {
    const double x = p1->getCoordX() - p2->getCoordX();
    const double y = p1->getCoordY() - p2->getCoordY();

    return std::abs(x) + std::abs(y);
}