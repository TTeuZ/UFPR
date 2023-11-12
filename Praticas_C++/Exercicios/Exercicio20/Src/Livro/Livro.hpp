#ifndef LIVRO_HPP
#define LIVRO_HPP

#include <list>
#include <string>

namespace ufpr {
class Livro {
   public:
    // Constructor
    Livro(const std::string& titulo, const uint8_t ano);

    // Destructor
    virtual ~Livro() = default;

    // Getters
    const std::string& getTitulo() const;
    const uint8_t getAno() const;
    const std::string& getAbstract() const;
    const std::list<std::string>& getAutores() const;

    // Setters
    void setAbstract(const std::string& abstract);

    // Functions
    void addAutor(const std::string& autor);

   private:
    std::string titulo;
    uint8_t ano;
    std::string abstract;
    std::list<std::string> autores;
};
}  // namespace ufpr
#endif