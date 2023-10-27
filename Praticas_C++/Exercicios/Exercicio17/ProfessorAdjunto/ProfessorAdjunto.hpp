#ifndef PROFESSOR_ADJUNTO_HPP
#define PROFESSOR_ADJUNTO_HPP

#include "../Professor/Professor.hpp"

namespace ufpr {
class ProfessorAdjunto : public Professor {
   public:
    // Constructors
    using Professor::Professor;

    // Destructor
    virtual ~ProfessorAdjunto() = default;

    // Getters
    const std::string& getLinhaPesquisa() const;

    // Setters
    void setLinhaPesquisa(const std::string& linhaPesquisa);

    // functions
    virtual uint32_t getSalario() const override;

   private:
    std::string linhaPesquisa;
};
}  // namespace ufpr

#endif