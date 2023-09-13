#include "Pessoa.hpp"

// Getters
std::string Pessoa::getName() { return name; }
uint64_t Pessoa::getCpf() { return cpf; }
unsigned short Pessoa::getAge() { return age; }

// Setters
void Pessoa::setName(std::string namePessoa) { name = namePessoa; }
void Pessoa::setCpf(uint64_t cpfPessoa) {
  cpf = validarCPF(cpfPessoa) ? cpfPessoa : 0;
}
void Pessoa::setAge(uint8_t agePessoa) { age = agePessoa; }

// Functions
bool Pessoa::validarCPF(uint64_t cpfTeste) {
  unsigned int somatorioValidaUltimo;
  unsigned int modulo;
  unsigned int somatorioValidaPenultimo{0};  // Iniciar variável com um valor já
  unsigned int ultimo{(unsigned int)(cpfTeste % 10)};
  cpfTeste = cpfTeste / 10;
  unsigned int penultimo{(unsigned int)(cpfTeste % 10)};
  cpfTeste = cpfTeste / 10;

  somatorioValidaUltimo = penultimo * 2;
  for (int i{2}; i <= 11; i++) {
    modulo = cpfTeste % 10;
    cpfTeste = cpfTeste / 10;
    somatorioValidaPenultimo += modulo * i;
    somatorioValidaUltimo += modulo * (i + 1);
  }

  modulo = somatorioValidaPenultimo % 11;
  if (modulo < 2) {
    if (penultimo != 0) return false;  // cpf invalido
  } else {
    if (penultimo != 11 - modulo) return false;  // cpf invalido
  }

  modulo = somatorioValidaUltimo % 11;
  if (modulo < 2) {
    if (!ultimo) return false;  // cpf invalido
  } else {
    if (ultimo != 11 - modulo) return false;  // cpf invalido
  }
  return true;  // cpf valido
}