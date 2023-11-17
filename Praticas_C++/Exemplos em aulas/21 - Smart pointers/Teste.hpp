#ifndef TESTE_HPP
#define TESTE_HPP

#include <memory>
#include <vector>

class Teste : : public std::enable_shared_from_this<Teste> {
    void processar() {
        std::vector<std::shared_ptr<Teste>> jaProcessados;

        //...
        loop {
            if (jaProcessados nao contem atual) {
                // processar
                if (atual == this) jaProcessados.emplace_back(this);
            }
        }
    }
};
#endif