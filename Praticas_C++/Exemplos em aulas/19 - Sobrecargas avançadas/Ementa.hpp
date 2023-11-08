#ifndef EMENTA_HPP
#define EMENTA_HPP

#include <list>
#include <string>

#include "Livro.hpp"

namespace ufpr {
class Ementa {
   public:
    Ementa();
    Ementa(const std::string descricao);
    Ementa(const Ementa& ementa);  // Overload do construtor de copia
    Ementa(Ementa&& ementa);       // Move constructor
    virtual ~Ementa();

    void setDescricao(const std::string& descricao);
    const std::string& getDescricao() const;

    void addLivro(const Livro& livro);
    const std::list<Livro>* getLivros() const;

    // operators
    const Ementa& operator=(const Ementa& ementa);
    Ementa& operator=(Ementa&& ementa);

   private:
    std::string descricao;
    std::list<Livro>* livros;
};
}  // namespace ufpr
#endif