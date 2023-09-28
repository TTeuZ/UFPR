#ifndef DISTANCIA_EUCLIDIANO_HPP
#define DISTANCIA_EUCLIDIANO_HPP

#include "../Trajeto/Trajeto.hpp"

class DistanciaEuclidiano final : public Trajeto {
   public:
    // Constructors
    using Trajeto::Trajeto;

    // Destructor
    ~DistanciaEuclidiano() = default;

    // Functions
    virtual double calcularDistanciaPontos(
        const Ponto* const p1, const Ponto* const p2) const override;
};

#endif