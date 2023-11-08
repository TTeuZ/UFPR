#ifndef ENGENHEIRO_HPP
#define ENGENHEIRO_HPP

#include "Pessoa.hpp"
#include "CPF.hpp"

namespace ufpr{
class Engenheiro : virtual public Pessoa{
	public:
		Engenheiro(const std::string& nome, const unsigned long cpf, const unsigned int numeroCrea);
		Engenheiro(const std::string& nome, const CPF& cpf, const unsigned int numeroCrea);
		virtual ~Engenheiro();

		unsigned int getNumeroCrea() const;
		void setNumeroCrea(const unsigned int numeroCrea);

		virtual unsigned int getSalario() const;

	private:
		constexpr static unsigned int salarioPadrao{9405};

		unsigned int numeroCrea;
};
}
#endif