#ifndef CURSO_HPP
#define CURSO_HPP

#include <cstdint>
#include <string>

class Curso {
   public:
    // Constructors
    Curso(std::string nome, uint8_t anoCriacao, uint8_t cargaHorariaMinima);

    // Getters
    std::string& getNome();
    uint8_t getAnoCriacao();
    uint8_t getCargaHorariaMinima();

    // Setters
    void setNome(std::string nome);
    void setCargaHorariaMinima(uint8_t cargaHorariaMinima);

   private:
    std::string nome;
    uint8_t anoCriacao;
    uint8_t cargaHorariaMinima;
};

#endif