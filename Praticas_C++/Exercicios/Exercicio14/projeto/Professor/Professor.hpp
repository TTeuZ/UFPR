#ifndef PROFESSOR_HPP
#define PROFESSOR_HPP

#include "../Pessoa/Pessoa.hpp"

class Professor : public Pessoa {
   public:
    // Constructors
    Professor(const std::string& nome, const uint64_t cpf,
              const uint16_t valorHora, const uint8_t cargaHoraria);

    // Destructor
    virtual ~Professor() = default;

    // Getters
    uint16_t getValorHora() const;
    uint8_t getCargaHoraria() const;

    // Setters
    void setValorHora(const uint16_t valorHora);
    void setCargaHoraria(const uint8_t cargaHoraria);

    // Functions
    virtual uint32_t getSalario() const;

   protected:
    uint16_t valorHora;
    uint8_t cargaHoraria;
};

#endif