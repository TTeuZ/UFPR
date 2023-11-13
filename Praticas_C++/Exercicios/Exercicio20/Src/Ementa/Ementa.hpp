#ifndef EMENTA_HPP
#define EMENTA_HPP

#include <list>
#include <string>

#include "../Livro/Livro.hpp"

namespace ufpr {
class Ementa {
   public:
    // Constructors
    Ementa();
    explicit Ementa(const std::string descricao);
    explicit Ementa(const Ementa& ementa);  // Copy constructor
    explicit Ementa(Ementa&& ementa);       // Move constructor

    // Destructor
    virtual ~Ementa();

    // Getters
    const std::string& getDescricao() const;
    const std::list<Livro>* getLivros() const;

    // Setters
    void setDescricao(const std::string& descricao);

    // Functions
    void addLivro(const Livro& livro);

    // operators
    const Ementa& operator=(const Ementa& ementa);
    Ementa& operator=(Ementa&& ementa);

   private:
    std::string descricao;
    std::list<Livro>* livros;
};
}  // namespace ufpr
#endif