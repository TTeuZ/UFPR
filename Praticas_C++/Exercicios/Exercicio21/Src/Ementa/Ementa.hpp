#ifndef EMENTA_HPP
#define EMENTA_HPP

#include <list>
#include <memory>
#include <string>

#include "../Livro/Livro.hpp"

namespace ufpr {
class Ementa {
   public:
    // Constructors
    Ementa();
    explicit Ementa(const std::string descricao);
    Ementa(const Ementa& ementa);  // Copy constructor
    Ementa(Ementa&& ementa);       // Move constructor

    // Destructor
    virtual ~Ementa() = default;

    // Getters
    const std::string& getDescricao() const;
    const std::list<std::shared_ptr<const Livro>>* getLivros() const;

    // Setters
    void setDescricao(const std::string& descricao);

    // Functions
    void addLivro(std::shared_ptr<const Livro> livro);

    // operators
    const Ementa& operator=(const Ementa& ementa);
    Ementa& operator=(Ementa&& ementa);

   private:
    std::string descricao;
    std::unique_ptr<std::list<std::shared_ptr<const Livro>>> livros;
};
}  // namespace ufpr
#endif