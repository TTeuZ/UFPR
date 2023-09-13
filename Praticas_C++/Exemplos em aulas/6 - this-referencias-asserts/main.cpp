#include <iostream>
#include <string>

#include "Disciplina.hpp"
#include "Pessoa.hpp"

int main() {
    Pessoa *p1{new Pessoa{"Irineu", 11111111111, 20}};

    delete p1;

    return 0;
}