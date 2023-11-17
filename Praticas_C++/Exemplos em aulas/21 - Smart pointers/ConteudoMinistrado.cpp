#include "ConteudoMinistrado.hpp"

using namespace ufpr;

unsigned int ConteudoMinistrado::proxId{0};

ConteudoMinistrado::ConteudoMinistrado(const std::string& descricao, const unsigned short cargaHorariaConteudo):
    descricao(descricao), cargaHorariaConteudo(cargaHorariaConteudo), id{ConteudoMinistrado::proxId}{
        ConteudoMinistrado::proxId++;
}

const std::string& ConteudoMinistrado::getDescricao() const{
	return descricao;
}

unsigned short ConteudoMinistrado::getCargaHorariaConteudo() const{
	return cargaHorariaConteudo;
}

unsigned int ConteudoMinistrado::getId() const{
	return id;
}