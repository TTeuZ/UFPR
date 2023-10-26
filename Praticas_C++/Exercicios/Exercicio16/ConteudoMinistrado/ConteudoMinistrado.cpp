#include "ConteudoMinistrado.hpp"

uint64_t ConteudoMinistrado::proxId{1};

// Constructors
ConteudoMinistrado::ConteudoMinistrado(const std::string& descricao,
                                       const uint8_t cargaHorariaConteudo)
    : descricao(descricao),
      cargaHorariaConteudo(cargaHorariaConteudo),
      id{ConteudoMinistrado::proxId} {
    ConteudoMinistrado::proxId++;
}

// Getters
const std::string& ConteudoMinistrado::getDescricao() const {
    return this->descricao;
}

uint8_t ConteudoMinistrado::getCargaHorariaConteudo() const {
    return this->cargaHorariaConteudo;
}

uint64_t ConteudoMinistrado::getId() const { return this->id; }
