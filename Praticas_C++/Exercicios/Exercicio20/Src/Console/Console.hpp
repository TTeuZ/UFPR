#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "../Disciplina/Disciplina.hpp"

namespace ufpr {
class Console {
    // Constructor
    Console() = delete;
    // Destructor
    virtual ~Console() = default;

   public:
    static void imprimirDadosDisciplina(const Disciplina& disciplina);
};
}  // namespace ufpr
#endif
