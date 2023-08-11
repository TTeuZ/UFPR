#ifndef PESSOA_HPP
#define PESSOA_HPP

#include <cstdint>
#include <string>

class Pessoa {
   public:
    // Podemos ter multiplos construtores validados por tipo / quantidade de
    // oarametros
    Pessoa();
    Pessoa(std::string newName, uint8_t newAge);
    Pessoa(std::string newName, uint8_t newAge, uint64_t cpf);

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
    uint8_t age;
    uint64_t cpf;
};
#endif