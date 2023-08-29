#ifndef CURSO_HPP
#define CURSO_HPP

#include <cstdint>
#include <string>

class Curso {
   public:
    // Constructors
    Curso(std::string nome, int8_t anoCriacao, int8_t cargaHorariaMinima);

    // Getters
    std::string getNome();
    int8_t getAnoCriacao();
    int8_t getCargaHorariaMinima();

    // Setters
    void setNome(std::string nome);
    void setCargaHorariaMinima(int8_t cargaHorariaMinima);

   private:
    std::string nome;
    int8_t anoCriacao;
    int8_t cargaHorariaMinima;
};

#endif