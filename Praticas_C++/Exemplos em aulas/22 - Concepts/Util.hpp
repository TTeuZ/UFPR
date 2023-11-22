#ifndef UTIL_HPP
#define UTIL_HPP

#include <concepts>
#include <list>

template <typename T>
concept Numerico = std::integral<T> || std::floating_point<T>;

template <Numerico T>
class Util {
   public:
    Util() = default;
    virtual ~Util() = default;

    static T somar(const std::list<T> lista) {
        T soma{0};
        // a partir do C++ 11, podemos fazer um foreach
        for (T const& valor : lista) soma += valor;
        return soma;
    }
};
#endif
