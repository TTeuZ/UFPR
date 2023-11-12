#include "Disciplina.hpp"

#include <iostream>

#include "../SalaAula/SalaAula.hpp"

namespace ufpr {
// Constructors
Disciplina::Disciplina(const Curso& curso, const std::string& nome, const uint8_t cargaHoraria,
                       const enums::EnumTipoDisciplina tipo)
    : curso{curso}, nome{nome}, sala{nullptr}, tipo{tipo} {
    this->setCargaHoraria(cargaHoraria);
}

Disciplina::Disciplina(const Curso& curso, const std::string& nome, const Professor* professor,
                       const uint8_t cargaHoraria, SalaAula* sala, const enums::EnumTipoDisciplina tipo,
                       const Ementa& ementa)
    : curso{curso}, nome{nome}, professor{professor}, sala{nullptr}, tipo{tipo}, ementa{ementa} {
    this->setSalaAula(sala);
    this->setCargaHoraria(cargaHoraria);
}

Disciplina::Disciplina(const Disciplina& disciplina)
    : curso{disciplina.curso},
      nome{disciplina.nome},
      professor{disciplina.professor},
      sala{nullptr},
      tipo{disciplina.tipo},
      ementa{disciplina.ementa},
      alunos{disciplina.alunos} {
    std::list<ConteudoMinistrado*>::const_iterator it{disciplina.conteudos.begin()};
    for (; it != disciplina.conteudos.end(); ++it) {
        this->adicionaConteudo((*it)->getDescricao(), (*it)->getCargaHorariaConteudo());
    }
}

// Destructor
Disciplina::~Disciplina() {
    this->limparConteudos();
    this->setSalaAula(nullptr);
}

// Getters
const Curso& Disciplina::getCurso() const { return this->curso; }

const std::string& Disciplina::getNome() const { return this->nome; }

const Professor* Disciplina::getProfessor() const { return this->professor; }

int Disciplina::getCargaHoraria() const { return this->cargaHoraria; }

const SalaAula* Disciplina::getSalaAula() const { return this->sala; }

const enums::EnumTipoDisciplina Disciplina::getTipo() const { return this->tipo; }
const Ementa& Disciplina::getEmenta() const { return this->ementa; }

const std::list<const Aluno*>& Disciplina::getAlunos() const { return this->alunos; }

const std::list<ConteudoMinistrado*>& Disciplina::getConteudos() const { return this->conteudos; }

// Setters
void Disciplina::setNome(const std::string& nome) { this->nome = nome; }

void Disciplina::setProfessor(const Professor* professor) { this->professor = professor; }

void Disciplina::setCargaHoraria(const int8_t cargaHoraria) {
    if (this->tipo == enums::EnumTipoDisciplina::MANDATORIA && cargaHoraria < 30)
        throw std::invalid_argument("Disciplina mandatoria precisa ter mais de 30 horas");

    this->cargaHoraria = cargaHoraria;
}

void Disciplina::setSalaAula(SalaAula* sala) {
    if (this->sala == sala) return;
    if (this->sala != nullptr) this->sala->disciplinasMinistradas.remove(this);

    this->sala = sala;
    if (this->sala != nullptr) this->sala->disciplinasMinistradas.push_back(this);
}

void Disciplina::setTipo(const enums::EnumTipoDisciplina tipo) { this->tipo = tipo; }

void Disciplina::setEmenta(const Ementa& ementa) { this->ementa = ementa; }

// Operators
bool Disciplina::operator==(const Disciplina& outro) const {
    bool equal{this->nome == outro.nome};
    equal = equal && this->tipo == outro.tipo;

    // Seria interessante verificar se os conteudos e emanta são iguais, mas para isso teriamos que ou fazer um chunco
    // ou sobreescrever os operadores de comparaçao destas duas classes. Por momento foi deixado assim
    return equal;
}

bool Disciplina::operator!=(const Disciplina& outro) const { return !(*this == outro); }

// Functions
void Disciplina::imprimirDados(const std::string& cabecalho, const int8_t cargaTotalCurso) {
    double pctCurso = (double)this->cargaHoraria / cargaTotalCurso;
    pctCurso = pctCurso * 100;
    std::cout << cabecalho << std::endl;
    std::cout << "Disciplina: " << this->nome << std::endl;
    std::cout << "Carga: " << this->cargaHoraria << std::endl;
    std::cout << "Porcentagem do curso: " << pctCurso << "%" << std::endl;
    std::cout << "Professor: " << this->professor->getNome() << std::endl;
}

const std::string& Disciplina::getNomeProfessor() const { return this->professor->getNome(); }

void Disciplina::adicionarAluno(const Aluno* aluno) {
    if (aluno == nullptr) throw exceptions::NullPointerException{"Aluno não pode ser nulo"};
    this->alunos.push_back(aluno);
}

bool Disciplina::removerAluno(const Aluno* aluno) {
    std::list<const Aluno*>::const_iterator it{this->alunos.begin()};
    for (; it != this->alunos.end(); ++it) {
        if (*it == aluno) {
            this->alunos.erase(it);
            return true;
        }
    }
    return false;
}

bool Disciplina::removerAluno(const uint64_t cpf) {
    std::list<const Aluno*>::const_iterator it{this->alunos.begin()};
    for (; it != this->alunos.end(); ++it) {
        if ((*it)->getCpf().getNumero() == cpf) {
            this->alunos.erase(it);
            return true;
        }
    }
    return false;
}

void Disciplina::adicionaConteudo(const std::string& descricao, const uint8_t cargaHorariaConteudo) {
    try {
        ConteudoMinistrado* conteudo{new ConteudoMinistrado{descricao, cargaHorariaConteudo}};

        this->conteudos.push_back(conteudo);
    } catch (std::bad_alloc& e) {
        std::cout << "Erro na alocação do conteudo - " << e.what() << std::endl;
    }
}

bool Disciplina::removerConteudoMinistrado(const uint64_t id) {
    std::list<ConteudoMinistrado*>::iterator it{this->conteudos.begin()};
    for (; it != this->conteudos.end(); ++it) {
        if ((*it)->getId() == id) {
            ConteudoMinistrado* conteudo{*it};
            this->conteudos.erase(it);
            delete conteudo;
            return true;
        }
    }
    return false;
}

void Disciplina::limparConteudos() {
    while (!this->conteudos.empty()) {
        delete this->conteudos.back();
        this->conteudos.pop_back();
    }
}
}  // namespace ufpr