#ifndef PESSOA_HPP
#define PESSOA_HPP

#include <cstdint>
#include <string>

class Pessoa {
 public:
  bool validarCPF(uint64_t cpfTeste);

  std::string name;
  uint64_t cpf;
  uint8_t idade;
};
#endif