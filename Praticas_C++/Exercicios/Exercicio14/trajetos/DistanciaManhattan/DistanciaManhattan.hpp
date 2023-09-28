#ifndef DISTANCIA_MANHATTAN_HPP
#define DISTANCIA_MANHATTAN_HPP

#include "../Trajeto/Trajeto.hpp"

class DistanciaManhattan final : public Trajeto {
   public:
    // Constructors
    using Trajeto::Trajeto;

    // Destructor
    ~DistanciaManhattan() = default;

    // Functions
    virtual double calcularDistanciaPontos(
        const Ponto* const p1, const Ponto* const p2) const override;
};

#endif