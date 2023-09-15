#include <iostream>

#include "Console.hpp"
#include "ConteudoMinistrado.hpp"
#include "Disciplina.hpp"
#include "Pessoa.hpp"
#include "SalaAula.hpp"

int main() {
    const Pessoa p1{"Maria"};
    const int valor{42};

    // Da erro de compilação, pois uma função de uma classe pode ter o direito
    // de modificar a classe
    // Para solucionar isso, precimos tornar a função const
    std::cout << p1.getNome() << std::endl;

    std::cout << valor << std::endl;

    return 0;
}