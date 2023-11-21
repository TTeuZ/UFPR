#ifndef LIVRO_HPP
#define LIVRO_HPP

#include <list>
#include <memory>
#include <string>
#include <unordered_map>

namespace ufpr {
class Livro {
   public:
    static std::shared_ptr<const Livro> carregarLivro(const unsigned long ISBN);

    // Destructor
    virtual ~Livro() = default;

    // Getters
    const uint64_t getISBN() const;
    const std::string& getTitulo() const;
    const uint8_t getAno() const;
    const std::string& getAbstract() const;
    const std::list<std::string>& getAutores() const;

    // Setters
    void setAbstract(const std::string& abstract);

    // Functions
    void addAutor(const std::string& autor);

    // Operators
    bool operator==(const Livro& outro) const;
    bool operator!=(const Livro& outro) const;

   private:
    static std::unordered_map<uint64_t, std::weak_ptr<const Livro>> cache;

    // Constructor
    Livro(const uint64_t ISBN, const std::string& titulo, const uint8_t ano);

    const uint64_t ISBN;
    const std::string titulo;
    uint8_t ano;
    std::string abstract;
    std::list<std::string> autores;
};
}  // namespace ufpr
#endif