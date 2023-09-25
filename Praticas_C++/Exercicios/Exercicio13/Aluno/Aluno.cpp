#include "Aluno.hpp"

// Constructors
Aluno::Aluno(const std::string& nome, const uint64_t cpf, const uint64_t grr,
             const double ira)
    : Pessoa{nome, cpf}, grr{grr}, ira{ira} {}

// Destructor
Aluno::~Aluno() {}

// Getters
uint64_t Aluno::getGrr() const { return this->grr; }

double Aluno::getIra() const { return this->ira; }

// Setters
void Aluno::setGrr(const uint64_t grr) { this->grr = grr; }

void Aluno::setIra(const double ira) { this->ira = ira; }