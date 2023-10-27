#ifndef ENGENHEIRO_HPP
#define ENGENHEIRO_HPP

#include "Pessoa.hpp"

class Engenheiro : virtual public Pessoa {
   public:
    Engenheiro();
    Engenheiro(const unsigned int numeroCrea);
    virtual ~Engenheiro();

    unsigned int getNumeroCrea() const;
    void setNumeroCrea(const unsigned int numeroCrea);

    virtual unsigned int getSalario() const;

   private:
    constexpr static unsigned int salarioPadrâo{9405};
    unsigned int numeroCrea;
};
#endif