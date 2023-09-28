#ifndef TRAJETO_HPP
#define TRAJETO_HPP

#include <list>

#include "../Ponto/Ponto.hpp"

class Trajeto {
   public:
    // Constructors
    Trajeto();

    // Destructor
    virtual ~Trajeto();

    // Functions
    void adicionarPonto(const double coordX, const double coordY);
    void imprimirTrajeto() const;
    double getDistanciaPercorrida() const;

   protected:
    virtual double calcularDistanciaPontos(const Ponto* const p1,
                                           const Ponto* const p2) const = 0;

   private:
    std::list<const Ponto*>* pontos;
};
#endif
