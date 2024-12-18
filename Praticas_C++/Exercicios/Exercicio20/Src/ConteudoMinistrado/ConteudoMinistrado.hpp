#ifndef CONTEUDO_MINISTRADO_HPP
#define CONTEUDO_MINISTRADO_HPP

#include <cstdint>
#include <string>

namespace ufpr {
class ConteudoMinistrado {
   public:
    // Constructors
    ConteudoMinistrado(const std::string& descricao, const uint8_t cargaHorariaConteudo);

    // Destructor
    virtual ~ConteudoMinistrado() = default;

    // Getters
    const std::string& getDescricao() const;
    uint8_t getCargaHorariaConteudo() const;
    uint64_t getId() const;

   private:
    static uint64_t proxId;

    std::string descricao;
    uint8_t cargaHorariaConteudo;
    uint64_t id;
};
}  // namespace ufpr
#endif
