#ifndef PROFESSOR_ADJUNTO_HPP
#define PROFESSOR_ADJUNTO_HPP

#include "Professor.hpp"

class ProfessorAdjunto : public Professor {
   public:
    // Constructors
    using Professor::Professor;

    // Destructor
    // using Professor::~Professor;

    // Getters
    const std::string& getLinhaPesquisa() const;

    // Setters
    uint16_t getSalario() const;
    void setLinhaPesquisa(const std::string& linhaPesquisa);

   private:
    std::string linhaPesquisa;
};

#endif