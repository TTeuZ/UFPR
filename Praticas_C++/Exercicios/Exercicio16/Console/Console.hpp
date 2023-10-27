#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "../Disciplina/Disciplina.hpp"

namespace ufpr {
class Console {
    // Destructor
    virtual ~Console() = default;

   public:
    static void imprimirDadosDisciplina(const Disciplina& disciplina);
};
}  // namespace ufpr
#endif
