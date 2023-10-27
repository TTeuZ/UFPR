#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "Disciplina.hpp"
namespace ufpr {
class Console {
   public:
    virtual ~Console() = default;
    static void imprimirDadosDisciplina(Disciplina& disciplina);
};
}  // namespace ufpr
#endif
