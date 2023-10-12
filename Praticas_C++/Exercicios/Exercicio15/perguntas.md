# O que é equivalente a uma interface (c#/java) em C++
Podemos dizer que o equivalente a uma interface em C++ seriam as classes abstratas. 

Como Java/C# não possuem o conceito de herança multipla, houve a necessidade de construir as interfaces para, de certa forma, contornar este problema
fornecendo um 'tipo de herança multipla' por meio da utilização de interfaces.

Como o C++ possui o conceito de herança multipla, não se fez necessidade de adicionar interfaces a linguagem.

Podemos também, de certa forma, considerar os .hpp como 'pequenas interfaces' porem exclusivas por classe.

# Que tipos de problemas uma interface não resolve, e que podemos resolver apenas com herança múltipla?
Com uma interface você não consegue herdar funcionalidades, pois quando uma classe implemente uma interface, ela precisa reescrever o código para as funções que ela
esta implementando. Ja, com a herança multipla, teriamos verdadeiramente uma herença de funcionalidades, não sendo necessário essa re-implementação.