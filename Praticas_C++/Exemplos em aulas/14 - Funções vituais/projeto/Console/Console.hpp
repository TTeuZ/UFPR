#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "../Disciplina/Disciplina.hpp"

class Console {
    // Destructor
    virtual ~Console();

   public:
    static void imprimirDadosDisciplina(const Disciplina& disciplina);
};
#endif
