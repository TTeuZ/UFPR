#ifndef PESSOA_HPP
#define PESSOA_HPP

#include <cstdint>
#include <string>

class Pessoa {
 public:
  std::string getName();
  void setName(std::string namePessoa);

  uint64_t getCpf();
  void setCpf(uint64_t cpfPessoa);

  unsigned short getAge();  // Como se fosse um cast por causa do uint8_8 ser
                            // cosiderado um unsigned char
  void setAge(unsigned short agePessoa);

 private:
  bool validarCPF(uint64_t cpfTeste);

  std::string name;
  uint64_t cpf;
  uint8_t age;
};
#endif