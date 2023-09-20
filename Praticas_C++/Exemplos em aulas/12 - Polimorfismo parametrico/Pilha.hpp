#ifndef PILHA_HPP
#define PILHA_HPP

#include <unistd.h>

#include <cstdlib>

template <typename T = int, ssize_t MAX_PILHA = 10>
class Pilha {
   public:
    Pilha() : topo{-1} { static_assert(MAX_PILHA >= 1); }

    ~Pilha() {}

    bool push(const T valor) {
        if (this->estaCheia()) return false;
        this->topo++;
        this->pilha[this->topo] = valor;
        return true;
    }

    bool pop(T* const retorno) {
        if (!this->estaVazia()) {
            *retorno = this->pilha[topo];
            this->topo--;
            return true;
        }
        return false;
    }

    bool estaVazia() const {
        if (topo < 0) return true;
        return false;
    }

    bool estaCheia() const {
        if (topo >= MAX_PILHA - 1) return true;
        return false;
    }

   private:
    T pilha[MAX_PILHA];
    ssize_t topo;
};
#endif
