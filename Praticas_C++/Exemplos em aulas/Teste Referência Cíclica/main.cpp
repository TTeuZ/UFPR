#include <iostream>
#include <memory>

#include "Pessoa.hpp"

int main() {
    std::shared_ptr<Pessoa> ptrJoao{std::make_shared<Pessoa>("Joao")};
    std::shared_ptr<Pessoa> ptrMaria{std::make_shared<Pessoa>("Maria")};

    ptrJoao->irmao = ptrMaria;
    ptrMaria->irmao = ptrJoao;

    std::cout << "Fim!\n";

    return 0;
}