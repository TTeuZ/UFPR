#ifndef CONTEUDO_MINISTRADO_HPP
#define CONTEUDO_MINISTRADO_HPP

#include <string>

class ConteudoMinistrado {
   public:
    // Constructors
    ConteudoMinistrado(std::string descricao,
                       unsigned short cargaHorariaConteudo);

    // Getters
    std::string& getDescricao();
    unsigned short getCargaHorariaConteudo();
    unsigned int getId();

   private:
    static unsigned int proxId;

    std::string descricao;
    unsigned short cargaHorariaConteudo;
    unsigned int id;
};
#endif
