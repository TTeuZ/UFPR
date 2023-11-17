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

    virtual ~Livro();

    unsigned long getISBN() const;
    const std::string& getTitulo() const;

    void setAbstract(const std::string& abstract);
    const std::string& getAbstract() const;

    const short int getAno() const;

    void addAutor(const std::string& autor);
    const std::list<std::string>& getAutores() const;

   private:
    static std::unordered_map<unsigned long, std::weak_ptr<const Livro>>
        cache;

    Livro(const unsigned long ISBN, const std::string& titulo,
          const short int ano);

    const unsigned long ISBN;  // número de identificação único
    const std::string titulo;
    short int ano;
    std::string abstract;
    std::list<std::string> autores;
};
}  // namespace ufpr
#endif
