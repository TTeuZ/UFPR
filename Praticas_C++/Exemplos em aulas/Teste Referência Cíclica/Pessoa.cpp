#include "Pessoa.hpp"

#include <iostream>

Pessoa::Pessoa(const std::string& nome) : nome{nome} {};
Pessoa::~Pessoa() { std::cout << "Destruindo " << nome << '\n'; }