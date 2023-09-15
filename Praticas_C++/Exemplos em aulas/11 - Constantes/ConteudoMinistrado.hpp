#ifndef CONTEUDO_MINISTRADO_HPP
#define CONTEUDO_MINISTRADO_HPP

#include <string>

class ConteudoMinistrado {
   public:
    ConteudoMinistrado(std::string descricao,
                       unsigned short cargaHorariaConteudo);

    std::string& getDescricao();
    unsigned short getCargaHorariaConteudo() const;
    unsigned int getId() const;

   private:
    static unsigned int proxId;

    std::string descricao;
    unsigned short cargaHorariaConteudo;
    unsigned int id;
};
#endif