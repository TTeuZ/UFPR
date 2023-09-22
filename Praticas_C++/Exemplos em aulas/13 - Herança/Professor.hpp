#ifndef PROFESSOR_HPP
#define PROFESSOR_HPP

#include "Pessoa.hpp"

class Professor : public Pessoa {
   public:
    // Constructors
    Professor(const std::string& nome, const uint64_t cpf,
              const uint16_t valorHora, const uint8_t cargaHoraria);

    // Destructor
    ~Professor();

    // Getters
    uint16_t getValorHora() const;
    uint8_t getCargaHoraria() const;

    // Setters
    void setValorHora(const uint16_t valorHora);
    void setCargaHoraria(const uint8_t cargaHoraria);

    // Functions
    uint16_t getSalario() const;

   private:
    uint16_t valorHora;
    uint8_t cargaHoraria;
};

#endif