#ifndef ALUNO_HPP
#define ALUNO_HPP

#include "../Pessoa/Pessoa.hpp"

class Aluno : public Pessoa {
   public:
    // Constructors
    Aluno(const std::string& nome, const uint64_t cpf, const uint64_t grr,
          const double ira);

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

#endif