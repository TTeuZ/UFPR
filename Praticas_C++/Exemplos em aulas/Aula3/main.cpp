#include <cstdint>
#include <iostream>
#include <string>

#include "Pessoa.hpp"

int main() {
  Pessoa p1;
  int age;
  std::string name;
  uint64_t cpf;

  std::cout << "Nome: ";
  std::cin >> name;
  p1.setName(name);

  std::cout << "Idade: ";
  std::cin >> age;
  p1.setAge(age);

  bool valido = false;
  while (!valido) {
    std::cout << "CPF: ";
    std::cin >> cpf;
    p1.setCpf(cpf);
    valido = p1.getCpf() != 0;
  }

  std::cout << "Dados da pessoa: " << p1.getName() << "\t"
            << (unsigned short int)p1.getAge() << "\t" << p1.getCpf() << '\n';

  return 0;
}