#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "Disciplina.hpp"

namespace ufpr{
class Console{
	public:
		Console() = delete;
		virtual ~Console() = default;

		static void imprimirDadosDisciplina(const Disciplina& disciplina);
};
}
#endif