#include "ConteudoMinistrado.hpp"

uint64_t ConteudoMinistrado::proxId{1};

// Constructors
ConteudoMinistrado::ConteudoMinistrado(std::string descricao,
                                       uint8_t cargaHorariaConteudo)
    : descricao(descricao),
      cargaHorariaConteudo(cargaHorariaConteudo),
      id{ConteudoMinistrado::proxId} {
    ConteudoMinistrado::proxId++;
}

// Getters
std::string& ConteudoMinistrado::getDescricao() { return this->descricao; }

uint8_t ConteudoMinistrado::getCargaHorariaConteudo() {
    return this->cargaHorariaConteudo;
}

uint64_t ConteudoMinistrado::getId() { return this->id; }
