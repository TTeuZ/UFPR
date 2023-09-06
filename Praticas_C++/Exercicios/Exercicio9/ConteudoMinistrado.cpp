#include "ConteudoMinistrado.hpp"

unsigned int ConteudoMinistrado::proxId{1};

ConteudoMinistrado::ConteudoMinistrado(std::string descricao,
                                       unsigned short cargaHorariaConteudo)
    : descricao(descricao),
      cargaHorariaConteudo(cargaHorariaConteudo),
      id{ConteudoMinistrado::proxId} {
    ConteudoMinistrado::proxId++;
}

std::string& ConteudoMinistrado::getDescricao() { return this->descricao; }

unsigned short ConteudoMinistrado::getCargaHorariaConteudo() {
    return this->cargaHorariaConteudo;
}

unsigned int ConteudoMinistrado::getId() { return this->id; }
