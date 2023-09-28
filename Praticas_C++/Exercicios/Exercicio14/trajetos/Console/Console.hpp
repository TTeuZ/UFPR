#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "../Trajeto/Trajeto.hpp"

class Console {
   public:
    // Destructor
    ~Console() = default;

    // Functions
    static void detalhesTrajeto(const Trajeto& trajeto);
};

#endif