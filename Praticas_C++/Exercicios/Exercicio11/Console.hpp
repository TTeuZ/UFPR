#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "Disciplina.hpp"

class Console {
    // Destructor
    ~Console();

   public:
    static void imprimirDadosDisciplina(const Disciplina& disciplina);
};
#endif
