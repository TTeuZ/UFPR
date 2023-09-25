#ifndef PROFESSOR_ADJUNTO_HPP
#define PROFESSOR_ADJUNTO_HPP

#include "../Professor/Professor.hpp"

class ProfessorAdjunto : public Professor {
   public:
    // Constructors
    using Professor::Professor;

    // Destructor
    // using Professor::~Professor;

    // Getters
    const std::string& getLinhaPesquisa() const;

    // Setters
    void setLinhaPesquisa(const std::string& linhaPesquisa);

    // functions
    uint16_t getSalario() const;

   private:
    std::string linhaPesquisa;
};

#endif