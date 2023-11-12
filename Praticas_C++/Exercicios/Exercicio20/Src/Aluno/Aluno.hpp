#ifndef ALUNO_HPP
#define ALUNO_HPP

#include <cstdint>
#include <string>

#include "../Pessoa/Pessoa.hpp"
#include "../CPF/CPF.hpp"

namespace ufpr {
class Aluno : public Pessoa {
   public:
    // Constructors
    Aluno(const std::string& nome, const CPF& cpf, const uint64_t grr, const double ira);

    // Destructor
    virtual ~Aluno() = default;

    // Getters
    uint64_t getGrr() const;
    double getIra() const;

    // Setters
    void setGrr(const uint64_t grr);
    void setIra(const double ira);

   private:
    uint64_t grr;
    double ira;
};
}  // namespace ufpr

#endif