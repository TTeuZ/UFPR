#ifndef CONTEUDO_MINISTRADO_HPP
#define CONTEUDO_MINISTRADO_HPP

#include <cstdint>
#include <string>

class ConteudoMinistrado {
   public:
    // Constructors
    ConteudoMinistrado(std::string descricao, uint8_t cargaHorariaConteudo);

    // Destructor
    ~ConteudoMinistrado();

    // Getters
    std::string& getDescricao();
    uint8_t getCargaHorariaConteudo();
    uint64_t getId();

   private:
    static uint64_t proxId;

    std::string descricao;
    uint8_t cargaHorariaConteudo;
    uint64_t id;
};
#endif
