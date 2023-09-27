#ifndef CURSO_HPP
#define CURSO_HPP

#include <cstdint>
#include <string>

class Curso {
   public:
    // Constructors
    Curso(const std::string& nome, const uint8_t anoCriacao,
          const uint8_t cargaHorariaMinima);

    // Destructor
    virtual ~Curso();

    // Getters
    const std::string& getNome() const;
    uint8_t getAnoCriacao() const;
    uint8_t getCargaHorariaMinima() const;

    // Setters
    void setNome(const std::string& nome);
    void setCargaHorariaMinima(const uint8_t cargaHorariaMinima);

   private:
    std::string nome;
    uint8_t anoCriacao;
    uint8_t cargaHorariaMinima;
};

#endif