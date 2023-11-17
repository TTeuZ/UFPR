#ifndef PESSOA_HPP
#define PESSOA_HPP

#include <memory>
#include <string>

class Pessoa {
   public:
    Pessoa(const std::string& nome);
    virtual ~Pessoa();

    std::shared_ptr<Pessoa> irmao;
    std::string nome;
};
#endif