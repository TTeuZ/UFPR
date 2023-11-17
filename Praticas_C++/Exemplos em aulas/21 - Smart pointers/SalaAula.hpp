#ifndef SALA_AULA_H
#define SALA_AULA_H

#include <string>
#include <list>

#include "Disciplina.hpp"

namespace ufpr{
class SalaAula{
	friend void Disciplina::setSalaAula(SalaAula* salaAula);

	public:
		SalaAula(std::string nome, unsigned int capacidade);
		virtual ~SalaAula();
		
		std::string getNome();
		void setNome(std::string nome);

		unsigned int getCapacidade();
		void setCapcidade(unsigned int capacidade);

        std::list<Disciplina*>& getDisciplinas();
	private:
		std::string nome;
		unsigned int capacidade;
		std::list<Disciplina*> disciplinasMinistradas;
};
}
#endif